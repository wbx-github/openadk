#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() 
{
  pid_t pid;

  printf("Started OpenADK miniinit\n");
  putenv("TERM=vt102");

  // Redirect stdio to /dev/console
  close(0);
  close(1);
  close(2);
  open("/dev/console", O_RDWR); // stdin
  dup(0); // stdout
  dup(0); // stderr

  pid = vfork();
  if (pid == 0) {
    setsid(); //new session
    putenv("HOME=/");
    putenv("PATH=/sbin:/usr/sbin:/bin:/usr/bin");
    putenv("SHELL=/bin/sh");
    putenv("USER=root");
    // Child: start a shell (e.g., /bin/sh)
    execl("/bin/sh", "/bin/sh", "-l", NULL);
    perror("execl");
    exit(1);
  } else if (pid > 0) {
    // Parent: wait for child to exit
    int status;
    waitpid(pid, &status, 0);
    printf("Shell exited, shutting down\n");	  
  } else if (pid < 0) {
    printf("vfork failed");
    sleep(1);
    return 0;
  }
  _exit(0);
}
