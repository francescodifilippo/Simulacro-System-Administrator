#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <expect.h>
#include <regex.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

#define VERBOSE 0
#define MAXCOUNT 60

#define MIN_PROMPT 3
#define LEAST_TRUE 3
#define BUFFER_TIMEOUT 50000
#define MAX_BUFFER_TIMEOUT 1000000
#define AUTH_TIMEOUT 1000000
#define MAX_NEWLINE 2


int authentication(int, char*);
char *readfromfd(int, struct timeval*);
char *ctrl_eod(int);
char *myrealloc(char *, int);


int main(void)
{
	char *server = "localhost";
	char *login = "testuser";
	char *password ="cambiami\n";
	int fd;

	if ((fd=exp_spawnl("ssh","ssh","-l", login, server,(char *)0)) < 0)
	{
		perror("can't spawn!");
		exit(1);
	}

	if ((authentication(fd, password)))
	{
		write(fd,"ls -l /tmp/\n",strlen("ls -l /tmp/\n"));
		printf ("OUT:%s\n", ctrl_eod (fd));

		write(fd,"uname -a\n",strlen("uname -a\n"));
		printf ("OUT:%s\n", ctrl_eod (fd));

		write(fd,"uname -a\n",strlen("uname -a\n"));
	        printf ("OUT:%s\n", ctrl_eod (fd));
	}
	else
	{
		printf ("Can't connect\n");
	}
	return 0;
}

	


int authentication(int fd_expect, char *password)
{
	struct timeval tv;
	char *authstr;
	
	tv.tv_sec = 0;
        tv.tv_usec = AUTH_TIMEOUT;

	if ((authstr=readfromfd(fd_expect, &tv)))
	{
		free (authstr);
	}
	else
	{
		return (0);
	}

	write (fd_expect, password, strlen (password));

	if ((authstr=ctrl_eod (fd_expect)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



char *readfromfd(int fd_expect, struct timeval *timeout)
{
	char *readbuffer=NULL;
	char smallbuffer[2];
	int retval=1;
        int maxfd=0;
        int sizereadbuffer=2;
        fd_set rfds;

	do
        {
        	maxfd=(fd_expect+1);
                FD_ZERO(&rfds);
                FD_SET(fd_expect, &rfds);
                retval = select(maxfd, &rfds, NULL, NULL, timeout);
                if (retval)
                {
                        if (read(fd_expect, smallbuffer, 1) > 0)
			{
				smallbuffer[1]='\0';

				readbuffer=myrealloc(readbuffer, sizereadbuffer);

				if ((readbuffer=myrealloc(readbuffer, sizereadbuffer)))
                        	{
					strncat(readbuffer,smallbuffer,2);
                                	sizereadbuffer++;
				}
				else
				{
                                	return (NULL);
                        	}
			}
			else
			{
				return (NULL);
			}
                }
	}
	while (retval);
	return (readbuffer);
}



char *ctrl_eod (int fd_expect)
{
	char *actualbuffer=NULL;
	char *previousbuffer=NULL;
	char *appbuffer=NULL;
	char *fullbuffer=NULL;
	int retval=1;
	int counter=MAXCOUNT;
	int foundit=0;
	int numofnewline=0;
	int sizeactualbuffer=0;
	struct timeval tv;

	while ((counter) && (foundit < LEAST_TRUE))
	{
		if (VERBOSE)
		{
			printf ("- Start reading from fd %d\n", fd_expect);
		}

		if (VERBOSE)	
		{
			printf ("-ACTUALBUFFER----------------------------\n");
                       	printf ("%s\n", actualbuffer); 
                       	printf ("------------------------------------------\n");
		}

		if (previousbuffer)
                {
			if (VERBOSE)
			{	
				printf ("\n-PREVIOUSBUFFER------------------------\n");
                       		printf ("%s\n",previousbuffer);
                       		printf ("------------------------------------------\n\n");
			}

                        numofnewline=0;
                        appbuffer=previousbuffer;
                        while (appbuffer[0]!='\0')
                        {
                        	if (*appbuffer=='\n')
                                {
                        		numofnewline++;
                                }
                                appbuffer ++;
                        }
			if (VERBOSE)
			{		
                              	printf ("- Number of newline: %d\n",numofnewline);
			}
		}

	        if (( previousbuffer ) && ( strlen(previousbuffer) > MIN_PROMPT ) && ( numofnewline > 0 ) && ( numofnewline <= MAX_NEWLINE ) && ( strcmp( previousbuffer, actualbuffer ) == 0 ))
        	{
			if (VERBOSE)
			{	
				printf ("- Minimizing timeout window(%d millisec)\n", BUFFER_TIMEOUT);
			}
			tv.tv_sec = 0;
                        tv.tv_usec = BUFFER_TIMEOUT; 
			foundit++;
			if (VERBOSE)
			{
				printf ("- Prompt found (already found: %d)\n", foundit);	
			}
               	}
		else
        	{
			if (VERBOSE)
			{
				printf ("- Maximizing timeout window(%d millisec)\n", MAX_BUFFER_TIMEOUT);
			}
			tv.tv_sec = 0;
	       	       	tv.tv_usec = MAX_BUFFER_TIMEOUT;

			if (VERBOSE)
			{
				printf ("- Resetting foundit\n");
			}
			foundit=0;
		}

		free (previousbuffer);
		previousbuffer=(char *) malloc (sizeof (char) * sizeactualbuffer+1);
		memset(previousbuffer, 0, sizeactualbuffer);

        	if (previousbuffer)
        	{
			if (sizeactualbuffer==0)
			{
				previousbuffer=NULL;
			}
			else
			{
                      		memcpy(previousbuffer, actualbuffer, sizeactualbuffer);
			}
        	}
        	else
        	{
               		printf ("Impossibile allocare previousbuffer\n");
			return (NULL);
        	}

        	free (actualbuffer);

		if ((actualbuffer=readfromfd(fd_expect, &tv)))
		{
			sizeactualbuffer=strlen(actualbuffer)+1;

			if (sizeactualbuffer>0)
			{
				if (fullbuffer)
				{
					fullbuffer=(char *) realloc (fullbuffer,sizeof (char) * (sizeactualbuffer + strlen (fullbuffer)));
				}
				else
				{
					fullbuffer=(char *) malloc (sizeof (char) * (sizeactualbuffer));
					memset (fullbuffer,0,sizeactualbuffer);
				}
               			if (!fullbuffer)
               			{
					printf ("Impossibile allocare fulbuffer\n");
               				return (NULL);
               			}
				strncat (fullbuffer, actualbuffer, sizeactualbuffer);
			}
	
			if (VERBOSE)
			{	
				printf ("\n- End reading from fd: %d,  counter: %d - retval: %d\n", fd_expect, counter, retval);
			}
			/* scriviamo newline sul fd */
        		write(fd_expect, "\n",  1);
			counter --;
		}
		else
		{
			return (NULL);
		}
	}

	numofnewline=0;
	appbuffer=fullbuffer;

        appbuffer=appbuffer+strlen(fullbuffer);

	while (appbuffer!=fullbuffer)
        {
		if (appbuffer[0]=='\n')
		{	
			numofnewline++;
		}

		if (numofnewline == MAXCOUNT - counter)
                {
                	*appbuffer='\0';
                        appbuffer=fullbuffer;
                }
		else
		{	
                	appbuffer --;
		}
        }

	if (VERBOSE)
	{
		printf ("FULLBUFFER: %s\n", fullbuffer);
	}

	return (fullbuffer);
}



char * myrealloc (char * sourcestr, int amount)
{
	char * deststr = NULL;

	if (amount >0)
	{
		deststr = (char *) malloc (sizeof (char) * amount);
		if (deststr)
		{
			memset (deststr,0,amount);
			if (sourcestr)
			{
				strncat (deststr, sourcestr, strlen(sourcestr));
			}
		}
	}

	return (deststr);
}
