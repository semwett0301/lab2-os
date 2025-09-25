# Operating Systems

This repository contains implementations for the second lab of the Operating Systems course, featuring:

- **lsmod emulation** via Linux kernel syscalls
- **dentry structure extraction** via syscalls  
- **Threading implementation**

All implementations are written in C.

## Project Structure

```
├── lsmod-app.c          # lsmod emulation implementation
├── lsmod-app            # Compiled lsmod application
├── dentry-app.c         # dentry structure extraction implementation
├── dentry               # Compiled dentry application
├── threads.c            # Threading implementation
├── threads              # Compiled threading application
├── Makefile             # Build configuration
```

## Components

### 1. lsmod Emulation (`lsmod-app.c`)
Emulates the functionality of the Linux `lsmod` command using kernel syscalls to list loaded kernel modules.

### 2. Dentry Structure Extraction (`dentry-app.c`)
Extracts and analyzes dentry (directory entry) structures from the Linux kernel using syscalls.

### 3. Threading (`threads.c`)
Demonstrates threading concepts and implementation in C.

## Building

To compile all components:

```bash
make
```

To compile individual components:

```bash
make lsmod-app
make dentry-app  
make threads
```

## Usage

Run the compiled applications:

```bash
./lsmod-app      # List kernel modules
./dentry          # Extract dentry structures
./threads         # Run threading demonstration
```

## Requirements

- Linux environment with changed syscalls ([modified version](https://github.com/semwett0301/linux-5.8.1))
- GCC compiler
- Root privileges may be required for some syscalls
