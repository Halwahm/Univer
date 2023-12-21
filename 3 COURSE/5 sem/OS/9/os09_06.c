#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#define SIZE 2048
char read_el[SIZE];
void printlines(char *filename, char *arg);

void main(int argc, char **argv)
{
  printlines("./OS09_05.txt", argv[1]);         
}


void printlines(char *filename, char* arg)
{
  char read_el[SIZE];
  int div = (int)*arg % 2;      
  FILE *fp = fopen(filename,"r");
  FILE *out ;
  if(div == 1)
   out = fopen("./os09_06_01.txt","w+");
  else
   out = fopen("./os09_06_02.txt","w+");
  int ch=0;
  int lines=0;
  while (fgets(read_el, SIZE, fp) != NULL) {
    lines++;
    if(lines % 2 == div) {
    	fputs(read_el, out);
       }	
    }
  
  fclose(fp);
}