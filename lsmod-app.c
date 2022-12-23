#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static enum module_state {
    MODULE_STATE_LIVE,
    MODULE_STATE_COMING,
    MODULE_STATE_GOING,
};

static struct lsmod_module_info {
    unsigned int size;
    int references_count;
    char name[64 - sizeof(unsigned long)];
};


static void print_module(struct lsmod_module_info **mod, long amount, char** references) {
    printf("Module:                    Size:    Used:    By:\n");

    for (size_t current = 0; current < amount; current++) {
        printf("%-25s  %-10u %-10d %-10s", mod[current]->name,
               mod[current]->size, mod[current]->references_count, references[current]);
        printf("\n");
    }
}

int main(int argc, char **argv) {
    long *modules_amount = (long *) malloc(sizeof(long));

    long ret_amount = syscall(442, modules_amount);

    if (ret_amount < 0) {
        printf("System call lsmod_amount_modules error %s\n", strerror(-ret_amount));
        free(modules_amount);
        return -1;
    }

    char**  references = malloc(
            sizeof(char*) * (*modules_amount));
    struct lsmod_module_info **modules_info = (struct lsmod_module_info **) malloc(
            sizeof(struct lsmod_module_info *) * (*modules_amount));
    for (size_t i = 0; i < (*modules_amount); i++) {
        modules_info[i] = malloc(sizeof(struct lsmod_module_info));
        references[i] = malloc(sizeof(char) * (64 - sizeof(unsigned long)) * (*modules_amount) + (*modules_amount));
    }

    long ret_info = syscall(441, modules_info, references);
    if (ret_info < 0) {
        printf("System call lsmod_info error %s\n", strerror(-ret_info));
        free(modules_info);
        free(modules_amount);
        return -1;
    }

    print_module(modules_info, (*modules_amount), references);

    for (size_t i = 0; i < (*modules_amount); i++) {

        free(references[i]);
        free(modules_info[i]);
    }

    free(references);

    free(modules_info);
    free(modules_amount);

    return 0;
}
