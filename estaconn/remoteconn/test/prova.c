#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main (void)
{
        char **argv;
        char *path="/usr/local/bin/ssh";
	char *arg1="ssh";
        char *arg2="-l";
        char *arg3="testuser";
        char *arg4="localhost";
	char **mainargv;
	int pid=0;
	int fildes[2];
	
	argv=(char **) malloc (sizeof(char)*10);

	mainargv=argv;
        *argv=arg1;
        argv++;
        *argv=arg2;
        argv++;
        *argv=arg3;
        argv++;
	*argv=arg4;
        argv++;
        *argv='\0';
	argv=mainargv;

     	if (pipe(fildes))
	{
		printf ("can't pipe\n");
		exit (1);
	}

        pid=fork();
        if (pid==0)
        {
		printf ("trying to send data from father....\n");
		write (fildes[1], "prova\n\n", 7);
		printf ("done\n");
        }
	else if (pid>0)
        {
		printf ("Launching ssh from child....\n");

		if (fildes[0] != 0) 
		{
			dup2(fildes[0], 0);
			(void)close(fildes[0]);
		}

		close(1);
		open(_PATH_DEVNULL, O_RDWR);
		close(2);
		open(_PATH_DEVNULL, O_RDWR);
		close(fildes[1]);

		if (!(execve(path, argv, (char **)0)))
                {
                        printf ("can't run\n");
                        exit (1);
                }
                else
                {
                        printf ("OK\n");
                }
        }
	else
	{
		printf ("can't fork\n");
	}

        return 0;
}
