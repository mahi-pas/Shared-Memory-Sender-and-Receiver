# Shared-Memory-Sender-and-Receiver
2 C programs that will attach to shared memory. One will send an integer, and the other will read it.

## How to use
Compile shm-sender.c and shm-receiver.c separately. Run them in separate terminals.

For shm-sender.c to work, shared memory of that key must not exist. To remove shared memory, run `ipcrm -a` in your terminal.
