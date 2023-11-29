#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main ()
{
pid_t child_pid;
int x;
printf ("the main program process ID is %d\n", (int) getpid ());
child_pid = fork ();
if (child_pid != 0) {
	x=10;
printf ("this is the parent process, with id %d\n", (int) getpid ());
printf ("the child’s process ID is %d\n", (int) child_pid);
printf("Value of x is %d inside parent\n",x);
}
else{
	x=20;
printf ("this is the child process, with id %d\n", (int) getpid ());
printf ("this is the parent process, with id %d\n", (int) getpid ());
printf("Value of x is %d inside child\n",x);
}
return 0;
}
