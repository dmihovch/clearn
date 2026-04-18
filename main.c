#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
  if(argc < 2)
  {
    printf("usage: ./clearn <file-name>\n");
    return 1;
  }
  FILE* fp = fopen(argv[1],"r+");
  if(fp == NULL)
  {
    return 1;
  }
  int buffer_cap = 256;
  int buffer_size = 0;
  char* buffer = malloc(sizeof(char)*buffer_cap);
  char* tmp_buf;
  char ch;
  if(buffer == NULL)
  {
    fclose(fp);
    return 1;
  }

  while(1)
  {
    ch = fgetc(fp);
    if(ch == EOF)
    {
      break;
    }

    if(buffer_size >= buffer_cap)
    {
      tmp_buf = realloc(buffer, sizeof(char) * buffer_cap * 2);
      if(tmp_buf == NULL)
      {
        free(buffer);
        fclose(fp);
        return 1;
      }
      buffer = tmp_buf;
    }

    buffer[buffer_size] = ch;
    buffer_size++;

  }

  printf("got here!\n");


  for(int i = 0; i<buffer_size; i++)
  {
    putchar(buffer[i]);
  }

  

  fclose(fp);

  return 0;
  
}
