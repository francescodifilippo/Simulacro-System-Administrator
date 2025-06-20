#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <expect.h>
#include <regex.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

#define VERBOSE 1
#define MAXCOUNT 60

#define ACCEPT_CONN "re you sure you want to continue connecting"
#define PASSWD_CONN "assword:"
#define REMOTE_CONN "remote host"
#define TIMEOUT_CONN "timeout"
#define PROMPT_CONN "\n.+$"
#define MIN_PROMPT 3
#define LEAST_TRUE 3
#define BUFFER_TIMEOUT 50000
#define MAX_BUFFER_TIMEOUT 1000000
#define MAX_NEWLINE 2
#define EXPECT_TIMEOUT 15

#define ACCEPT_ID 1
#define PASSWD_ID 2
#define REMOTE_ID 3
#define TIMEOUT_ID 4
#define PROMPT_ID 5


void timedout(void);
void expect_auth(int, char*);
void ctrl_eod(int);
void exec_cmd(int);


int main(void)
{
	char *server = "localhost";
	char *login = "testuser";
	char *password ="cambiami\n";
	int fd;

	exp_loguser = 0;
	exp_timeout = EXPECT_TIMEOUT;

	if ((fd=exp_spawnl("ssh","ssh","-l", login, server,(char *)0)) < 0)
	{
		perror("can't spawn!");
		exit(1);
	}

	expect_auth(fd, password);

	write(fd,"ls -l /tmp/\n",strlen("ls -l /tmp/\n"));
	ctrl_eod (fd);
	write(fd,"uname -a\n",strlen("uname -a\n"));
	ctrl_eod (fd);

	write(fd,"find / -name zito \n",strlen("find / -name zito \n"));
        ctrl_eod (fd);

	write(fd,"uname -a\n",strlen("uname -a\n"));
        ctrl_eod (fd);
	
	return 0;
}

	

void timedout(void)
{
   fprintf(stderr,"timed out\n");
   exit(-1);
}



void expect_auth(int fd_expect, char *password)
{
	int conn_type;
	int doauth=1;

	if (VERBOSE)
	{
		printf ("- Controllo espressione nello streaming\n");	
	}

	while (doauth)
	{
		if ((conn_type=exp_expectl(fd_expect, exp_glob, ACCEPT_CONN, ACCEPT_ID, exp_glob, PASSWD_CONN, PASSWD_ID, exp_glob, REMOTE_CONN, REMOTE_ID, exp_glob, TIMEOUT_CONN, TIMEOUT_ID, exp_end)) < 0)
		{
			printf ("- Espressione NON confermata\n");
			exit (1);
		}
		else
		{
			if (VERBOSE)
			{
				printf ("- Espressione confermata\n");
			}
		
			switch (conn_type)
                	{
            			case ACCEPT_ID:
					printf ("ACCEPT_ID\n");
					write(fd_expect,"yes\n",strlen("yes\n"));
                 		break;

	            		case PASSWD_ID:
                                        write(fd_expect,password,strlen(password));                                     
                                        ctrl_eod(fd_expect);
					doauth=0;
                	 	break;

	            		case REMOTE_ID:
					printf ("REMOTE_ID\n");
				break;

	            		case TIMEOUT_ID:
					printf ("TIMEOUT_ID\n");
                	 	break;

	            		default:
					printf ("PROBLEMI......\n");
			}
		}
	}
}



void ctrl_eod (int fd_expect)
{
	char *actualbuffer=NULL;
	char *previousbuffer=NULL;
	char *appbuffer=NULL;
	char *fullbuffer=NULL;
	int retval=1;
	int maxfd=0;
	int counter=MAXCOUNT;
	int foundit=0;
	int numofnewline=0;
	char smallbuffer[1];
	int sizeactualbuffer=0;
	struct timeval tv;
	fd_set rfds;

	while ((counter) && (foundit < LEAST_TRUE))
	{
		if (VERBOSE)
		{
			printf ("- Start reading from fd %d\n", fd_expect);
		}

		{
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
			previousbuffer=(char *) malloc (sizeof (char) * sizeactualbuffer);

                        if (previousbuffer)
                        {
				if (sizeactualbuffer==0)
				{
					previousbuffer=NULL;
				}
				else
				{
                                	strncpy(previousbuffer, actualbuffer, sizeactualbuffer);
				}
                        }
                        else
                        {
                              	printf ("Impossibile allocare previousbuffer\n");
                               	exit (1);
                        }

			sizeactualbuffer=0;
                        free (actualbuffer);

			do
			{
				maxfd=(fd_expect+1);
	                       	FD_ZERO(&rfds);
                	       	FD_SET(fd_expect, &rfds);
                        	retval = select(maxfd, &rfds, NULL, NULL, &tv);
				if (retval)
				{
					if (sizeactualbuffer)
					{
						actualbuffer=(char *) realloc (actualbuffer,sizeof (char) * sizeactualbuffer);
						if (!actualbuffer)
                                        	{
                                                	exit (1);
                                        	}
                                        }
					else
					{
						sizeactualbuffer=2;
                                                actualbuffer=(char *) malloc (sizeof (char) * sizeactualbuffer);
						if (!actualbuffer)
                                        	{
                                                	exit (1);
                                        	}
						memset(actualbuffer,0,sizeactualbuffer);
                                        }
					sizeactualbuffer=sizeactualbuffer+2;

					read(fd_expect,smallbuffer,1);
					smallbuffer[1]='\0';
					strncat (actualbuffer,smallbuffer,2);
				}
			}
			while (retval);
		}


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
                		exit (1);
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


	numofnewline=0;
	appbuffer=fullbuffer;

        appbuffer=appbuffer+strlen(fullbuffer)-1;

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

	printf ("FULLBUFFER: %s\n", fullbuffer);
}
