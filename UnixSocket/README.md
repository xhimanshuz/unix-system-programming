# Unix System Programming
SEND AND RECEIVER with unix socket api

Socket allow a process on connected network to exchange data

## FILES
- send.cpp - Send message over TCP socker on given host and port
- recv.cpp - Receive message over TCP socket on given port

# Instruction
## SENDER
```shell
g++  send.cpp -o send
./send -h hostname -p portNumber
```

## RECEIVER
```shell
g++  recv.cpp -o recv
./recv -p portNumber
```
