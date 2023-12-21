#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>


void main(int argc, char **argv)
{
  char buff[255];
  int fp = open("./os09_07.txt", O_RDONLY);

long offset, lpos;

if (fp<0)
    return;
offset = 0L;
lpos = lseek(fp, offset, SEEK_SET);
printf("Текущая позиция=%ld\n", lpos);
offset = 10L;
lpos = lseek(fp, offset, SEEK_CUR);
printf("Текущая позиция=%ld\n", lpos);

close(fp);
}