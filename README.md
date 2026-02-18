# IPC Project

## Overview
This project demonstrates various Inter-Process Communication (IPC) mechanisms in Linux. The codebase is organized into directories, each representing a different IPC method:

- **message_queue/**: Implements message queue-based communication.
- **mmap/**: Demonstrates memory-mapped file communication.
- **named_pipe/**: Uses named pipes (FIFOs) for communication.
- **shared_memory/**: Implements shared memory communication.
- **sigaction/**: Uses signals with `sigaction` for communication.
- **signal/**: Demonstrates basic signal-based communication.
- **tcp_socket/**: Implements communication over TCP sockets.
- **udp_socket/**: Implements communication over UDP sockets.
- **unix_domain_socket/**: Demonstrates communication using Unix domain sockets.
- **pipe/**: Demonstrates communication using pipes.

Each directory contains separate implementations for the sender/writer and receiver/reader components.

## How to Build
- Use `g++` to compile individual components. For example:
  ```bash
  g++ -o named_pipe_reader named_pipe/reader.cpp
  g++ -o named_pipe_writer named_pipe/writer.cpp
  ```
- Ensure you have the necessary development tools installed (e.g., `build-essential` on Ubuntu).

## How to Run Examples
- Navigate to the respective directory and compile the sender and receiver programs.
- Example for `named_pipe`:
  ```bash
  mkfifo named_pipe/myfifo
  g++ -o writer named_pipe/writer.cpp
  g++ -o reader named_pipe/reader.cpp
  ./reader & ./writer
  ```

## Debugging
- Use `gdb` for debugging individual components. For example:
  ```bash
  gdb ./named_pipe_reader
  ```
- Add `#define DEBUG` in the source files to enable debug-specific code sections (if applicable).

## External Dependencies
This project relies on standard Linux system libraries, such as:
- `<sys/ipc.h>`
- `<sys/shm.h>`
- `<sys/socket.h>`

## Examples of IPC Patterns
- **Named Pipes**:
  - Writer opens the FIFO in write-only mode, while the reader opens it in read-only mode.
  - Example:
    ```cpp
    int fd = open("myfifo", O_WRONLY);
    write(fd, "Hello", 5);
    ```
- **Shared Memory**:
  - Use `shmget` to allocate shared memory and `shmat` to attach it to the process's address space.
  - Example:
    ```cpp
    int shmid = shmget(key, size, IPC_CREAT | 0666);
    char* data = (char*) shmat(shmid, NULL, 0);
    ```
