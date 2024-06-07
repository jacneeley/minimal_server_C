## Minimal Server
### Why?
I want to learn more about backend, networking and servers. I have worked on a lot of flask servers to make APIs, but flask does a lot of the work for you. While I have learned a lot using flask, I want to learn more. Why not code a server from scratch using C? I also want to learn more about C.

**THIS CODE IS NOT FOR PRODUCTION**

### Setup
**compile code and print useful info:**

```
gcc minimal_server.c
strace ./a.out
```

**get html file and read its contents:**
```
#open new terminal
mkdir tmp
cd tmp
wget localhost:8070/index.html
cat index.html
```

## Deep Dive
To start, the socket function from ```<sys/socket.h>``` is needed. 

Synopsis: ```int socket(int domain, int type, int protocol);```

Descriptions:<br>
Socket creates an endpoint for communication and returns a file descriptor that refers to that endpoint.

The first argument is domain. Domain argument specifies a communication domain; this selects the protocol family which will be used to communicate. For this project ```AF_INET``` for regular IPv4 Internet protocols is all that is needed.

The second argument is type. The socket type specifies the communication semantics. ```SOCK_STREAM``` will be used to provide a two-way, connection based, byte stream.

The last argument is protocol. ```0``` will be used to leave it as default.

**socket:**

```
int s = socket(AF_INET, SOCK_STREAM, 0);
```

The bind function will be used to bind the socket to a certain address.

Synopsis:<br>
```#include <sys/socket.h>```

```
int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
```

Description:<br>
sockfd is the socket file descriptor, in this case ```s```. sockaddr is a structure tht will take an address to bind. addrlen can be retrieved using sizeof(addr).

**bind:**

First, addr needs to be defined.
```
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = htons(8070);
addr.sin_addr.s_addr = INADDR_ANY;
```
```sockaddr_in``` indicates that the socked will be used for the internet. sockaddr_in uses many different attributes
- sin_family
- sin_port
- sin_addr.s_addr


Now the bind can be initialized.

```
bind(s, (struct sockaddr *) &addr, sizeof(addr));
```

```listen()``` will initialize the socket for incoming connections.

Synopsis:<br>
```
listen(int sockfd, int backlog)
```

Description:<br>
```s``` will be passed as the sockfd again, ```backlog``` represents the number of connections that can be waiting at the same time. This value doesn't really matter because this server won't be used in production. ```10``` will be used.

**listen:**
```
listen(s, 10)
```

```accept``` will actually accept connections coming from clients.

Synopsis:<br>
```
int accept(int sockfd, struct sockaddr *_Nullable restrict addr, socklen_t *_Nullable restrict addrlen);
```
Description:<br>
For this simple server a lot of the arguments in ```accept()``` are not needed. ```s``` can be used for sockfd again and ```0``` can be passed into the other two. They can provide additional client info if values other than 0 are used, but that is not needed.

**accept:**
```
int client_fd = accept(s,0,0);
```
```accept()``` will actually return the file descriptor of the client socket, so ```accept()``` will be declared as ```client_fd``` so that it can be reference later.

Now the string that the client is receiving can be retrieved. To do this ```recv()``` will be called.

Synopsis:<br>

```
recv(int sockfd, void buf[.len], size_t len, int flags)
```

**recv:**<br>
```
char buffer[256] = {0};
recv(client_fd, buffer, 256, 0);
``` 
