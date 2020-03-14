# 01 Lernaean Hydra

### Steps to create **server**:

1. Use [socket() function](http://man7.org/linux/man-pages/man2/socket.2.html) to create socket
2. Use [bind() fucntion](http://man7.org/linux/man-pages/man2/bind.2.html) to assign the address to the socket
3. Use [listen() function](http://man7.org/linux/man-pages/man2/listen.2.html) to listen for connections
4. Use [accept() fucntion](http://man7.org/linux/man-pages/man2/accept.2.html) to accept connection.
5. Receive and send datia
6. Close socket

### Steps to create **client**

1. Create socket
2. Use [connect() fucntion](to connect to the address of the server)
3. Send and receiv data
4. Close socket

- - -

### Usage

#### Server

```
./server [port]
``` 

or

```
./server
```
*Default port 8080*

#### Client

```
./client [hostname] [port] [option]
```

[hostname]	the name of the host on which the server is running, on single mashine use "localhost", mandatory argument
[port]		port number on which the server is listening for connections (by default port is 8080), not mandatory argument
[Option] 	**-d** -   ping server (by default manual communication), not mandatory argument.
