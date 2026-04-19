#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/inotify.h>

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    printf("usage: ./clearn <dir-name>\n");
    return 1;
  }

  int fd = inotify_init();
  if(fd == -1)
  {
    printf("Unable to init inotify\n");
    return 1;
  }

  int wd = inotify_add_watch(fd,argv[1],IN_CLOSE_WRITE | IN_MODIFY | IN_MOVED_TO);
  if(wd == -1)
  {
    printf("Unable to watch %s dir\n",argv[1]);
    return 1;
  }
  int buf_size = 4096;
  char buf[buf_size];

  while(1)
  {
    read(fd,buf,buf_size);
    printf("something happened\n");
  }

  inotify_rm_watch(fd, wd);

  
  return 0;
  
}
