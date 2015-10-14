int readn(register int fd, register char *ptr, register int nbytes) {
  int nleft;
  int nread;

  nleft = nbytes;
  while (nleft > 0) {
    nread = read(fd, ptr, nleft);

    if (nread < 0) {
      return nread;  // error, return < 0
    } else if (nread == 0) {
      break;  // EOF
    }

    nleft -= nread;
    ptr += nread;
  }

  return nbytes - nleft;  // return >= 0
}