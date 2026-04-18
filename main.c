#include <stdio.h>
#include <stdlib.h>

//need to switch to just use open and read

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
  if(buffer == NULL)
  {
    fclose(fp);
    return 1;
  }
  //this is a change
  char ch;
  while(1)
  {
    ch = fgetc(fp);
    if(ch == EOF)
    {
      break;
    }

    if(buffer_size >= buffer_cap)
    {
      buffer_cap *= 2;
      tmp_buf = realloc(buffer, sizeof(char) * buffer_cap);
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

  for(int i = 0; i<buffer_size; i++)
  {
    putchar(buffer[i]);
  }

  int buf_idx = 0;
  while(1)
  {
    ch = fgetc(fp);
    if(ch == EOF)
    {
      rewind(fp);
      buf_idx = 0;
      continue;
    }

    if(ch != buffer[buf_idx])
    {
      printf("file changed!\n");
      break;
    }
    buf_idx++;
  }

  fclose(fp);

  return 0;
  
}
