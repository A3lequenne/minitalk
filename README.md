# Minitalk: Simple Client-Server Messaging Program

## Overview

`Minitalk` is a simple client-server messaging program implemented in C using UNIX signals for communication. The program consists of two parts: a server that receives messages and a client that sends messages to the server. This project is a demonstration of inter-process communication (IPC) using signals, allowing two processes to exchange messages without using traditional network sockets or shared memory.

## Functionality

- **Server**: The server program (`server.c`) receives messages from clients and prints them to the standard output. It displays its process ID (PID), which clients use to send messages.
- **Client**: The client program (`client.c`) sends messages to the server by specifying the server's PID and the message to send. It encodes each character of the message bit by bit, and sends it to the server using signals.

### Key Components

- **Server (`server.c`)**:
  - **`get_sign()`**: Handles incoming signals and reconstructs the characters bit by bit. When a character is fully received, it is printed to the standard output.
  - **`show_pid()`**: Displays the server's PID so clients can send messages to it.
  - **`main()`**: Initializes the server, sets up signal handlers, and waits for incoming messages.

- **Client (`client.c`)**:
  - **`send_c()`**: Sends each character to the server by converting it to bits and sending the appropriate signal (`SIGUSR1` or `SIGUSR2`) for each bit.
  - **`send_msg()`**: Sends the entire message, character by character, to the server.
  - **`check_pid()`**: Checks if the provided PID is valid by sending a test signal to the server.
  - **`main()`**: Parses command-line arguments, validates the PID, and sends the message to the server.

### Example Usage

To use the `Minitalk` project, first compile the server and client programs, then start the server and use the client to send a message.

1. **Compile the Programs**

```sh
make
```

2. **Run the Server**

```sh
./server
```
This command will start the server and display its PID, which is needed by the client to send messages.

3. **Run the Client**

```sh
./client [server-pid] [message]
```
Replace `[server-pid]` with the PID displayed by the server and `[message]` with the message you want to send.

Example:

```sh
./client 12345 "Hello, World!"
```
This command will send the message "Hello, World!" to the server with PID `12345`.

### How It Works

- **Signal-Based Communication**: The server and client communicate using UNIX signals (`SIGUSR1` and `SIGUSR2`). The client sends a sequence of signals representing the bits of each character in the message.
- **Bitwise Encoding**: Each character is broken into its individual bits, and the client sends one signal per bit. The server reconstructs the character from these bits and prints it to the output.
- **Acknowledgment**: After receiving each bit, the server sends an acknowledgment signal (`SIGUSR2`) to inform the client that the bit has been received.

### Compilation and Execution

Use the provided `Makefile` to compile both the server and client programs:

```sh
make
```

After compilation, you will have two executables: `server` and `client`. Run `server` first, note the PID, and use `client` to send messages to the server.

## Bonus Features

In the bonus version, the program includes support for sending and receiving Unicode characters. Interestingly, Unicode support was effectively handled by default, even though no specific adjustments were made to address it. This means that messages containing Unicode characters, such as emojis or accented characters, are correctly transmitted from the client to the server without any additional modifications.

## Conclusion

`Minitalk` is a simple but effective project for demonstrating inter-process communication using UNIX signals. It shows how to encode and decode data for transmission between processes, and how to use signals to synchronize the sending and receiving of messages. This project is a great way to understand low-level IPC and signal handling in C.

