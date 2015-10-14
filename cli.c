// Example of client using TCP protocol.

#include "inet.h"

void str_cli(register FILE *fp, register int sockfd);

int main(int argc, char *argv[]) {
  int sockfd;
  struct sockaddr_in serv_addr;
  pname = argv[0];

  //
  // Fill in the structure "serv_addr" with the address of
  // the server that we want to connect with
  //

  memset((char *) &serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
  serv_addr.sin_port = htons(SERV_TCP_PORT);

  //
  // Open a TCP socket (an Internet stream socket)
  //
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    err_dump("client : can't open stream socket");
  }

  //
  // Connect the server
  //
  if (connect(sockfd, (
      struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    err_dump("client : can't connect to server");
  }

  str_cli(stdin, sockfd);
  close(sockfd);

  return EXIT_SUCCESS;
}

void str_cli(register FILE *fp, register int sockfd) {
  int n;
  char sendline[MAXLINE];
  char recvline[MAXLINE + 1];

  while (fgets(sendline, MAXLINE, fp) != NULL) {
    n = strlen(sendline);

    if (writen(sockfd, sendline, n) != n) {
      printf("MAXLINE: %d, n: %d\n", MAXLINE, n);
      err_dump("str_cli : written error on socket");
    }

    n = readline(sockfd, recvline, MAXLINE);

    if (n < 0) {
      err_dump("str_cli : reading error");
    }
    recvline[n] = '\0';
    printf("Received string from Server: ");
    fputs(recvline, stdout);
  }

  if (ferror(fp)) {
    err_dump("str_cli : error reading file");
  }
}
