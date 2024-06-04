#include <sys/socket.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>

void main(){
    int s = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8070);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *) &addr, sizeof(addr));

    listen(s, 10);

    int client_fd = accept(s, 0, 0);

    char buffer[256] = {0};
    recv(client_fd, buffer, 256, 0);

    //GET
    char* f = buffer + 5;
    *strchr(f, ' ') = 0;
    int opened_fd = open(f, O_RDONLY);
    sendfile(client_fd, opened_fd, 0 , 256);
    close(opened_fd);
    close(client_fd);
    close(s);
}