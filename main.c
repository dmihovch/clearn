#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/inotify.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
//a chage
//one more

//another change
int main(int argc, char** argv)
{
 
  int fd = inotify_init();
  if(fd == -1)
  {
    printf("Unable to init inotify\n");
    return 1;
  }
  //a lchange

  char* dir_path = ".";
  int dir_path_length = strlen(dir_path);


  int wd = inotify_add_watch(fd,dir_path,IN_CLOSE_WRITE | IN_MODIFY | IN_MOVED_TO);
  if(wd == -1)
  {
    printf("Unable to watch %s dir\n","dir_path");
    return 1;
  }
  int buf_cap = 4096;
  char buf[buf_cap];
  int buf_size;


  //making a change
//antother one?
  
  while(1)
  {
    buf_size = read(fd,buf,buf_cap);
    for (char *p = buf; p < buf + buf_size; ) {
          struct inotify_event *e = (struct inotify_event *)p;
            if (e->len > 0 && strcmp(e->name, "test.c") == 0 && (e->mask & IN_CLOSE_WRITE)) 
            {
              int pid = fork();

              if (pid == 0) {
                execlp("gcc", "gcc", "test.c", "-o", "test", NULL);
                printf("exec gcc failed\n");
                _exit(1);
              }

              int status;
              waitpid(pid, &status, 0);

              if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                goto compilation_failed;
              }

              pid = fork();
              if (pid == 0) {
                execl("./test", "./test", NULL);
                _exit(1);
              }

              waitpid(pid, &status, 0);
            }
            compilation_failed:
            p += sizeof(struct inotify_event) + e->len;
        }
  }

  inotify_rm_watch(fd, wd);

  
  return 0;
  
}
