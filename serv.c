//
// Example of server using TCP protocol.

#include <ctype.h>
#include "inet.h"
void str_echo(int sockfd);
void ConvertLowerToUpper(char* line, int length);  // 소문자를 대문자로 바꾸는 함수

int main(int argc, char *argv[]) {
  int sockfd;
  int newsockfd;
  int clilen;
  int childpid;
  struct sockaddr_in cli_addr;
  struct sockaddr_in serv_addr;

  pname = argv[0];

  // Open a TCP socket (an Internet stream socket)
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    err_dump("server : can't open stream socket");
  }

  // Bind our local address so that the client can send us
  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(SERV_TCP_PORT);

  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    err_dump("server : can't bind local address");
  }

  listen(sockfd, 5);
  for (; ;) {
    // Wait for a connection from a client process.
    // This is an example of a concurrent server.

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
      err_dump("server : accept error");
    }

    if ((childpid = fork()) < 0) {
      err_dump("server : fork error");
    } else if (childpid == 0) {  // child process
      close(sockfd);
      str_echo(newsockfd);
      exit(0);
    }
    close(newsockfd);
  }
}

//
// Reads a stream socket one line at a time, and write each
// line back to the sender.
// Return when the connection is terminated.
//
void str_echo(int sockfd) {
  int n;
  char line[MAXLINE];
  char* convertedLine = "From Server: ";

  for (; ;) {
    n = readline(sockfd, line, MAXLINE);

    if (n == 0) {
      return;  // connection terminated
    } else if (n < 0) {
      err_dump("str_echo : readline error");
    }

    printf("Received string from Client: %s", line);
    ConvertLowerToUpper(line, strlen(line));
    if (write(sockfd, line, n) != n) {
      err_dump("str_echo : writen error");
    }
  }
}

void ConvertLowerToUpper(char* line, int length) {
  int i = 0;
  for (i = 0; i < length; ++i) {
    line[i] = toupper(line[i]);
  }
}
