#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define VERBOSE 1
#define MAXCOUNT 60

#define ACCEPT_CONN "re you sure you want to continue connecting"
#define PASSWD_CONN "assword:"
#define REMOTE_CONN "remote host"
#define TIMEOUT_CONN "timeout"
#define PROMPT_CONN "\n.+$"
#define MIN_PROMPT 3
#define LEAST_TRUE 3
#define BUFFER_TIMEOUT 100000
#define MAX_BUFFER_TIMEOUT 3000000
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
	char *cmd ="/usr/local/bin/ssh -ltestuser localhost";

	FILE *fd;

        if ((fd = popen(cmd, "w")) == NULL)
	{
		perror("can't spawn!");
		exit(1);
	}

	/*
	write(fd,"ls -l /tmp/\n",strlen("ls -l /tmp/\n"));
	ctrl_eod (fd);
	write(fd,"uname -a\n",strlen("uname -a\n"));
	ctrl_eod (fd);
	write(fd,"find / -name tinmr305\n",strlen("find / -name tinmr305\n"));
	ctrl_eod (fd);
	write(fd,"ps -aux\n", strlen("ps -aux\n"));
	ctrl_eod (fd);
	write(fd,"top -s1\n", strlen("top -s1\n"));
        ctrl_eod (fd);
	*/

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
		/*if ((conn_type=exp_expectl(fd_expect, exp_glob, ACCEPT_CONN, ACCEPT_ID, exp_glob, PASSWD_CONN, PASSWD_ID, exp_glob, REMOTE_CONN, REMOTE_ID, exp_glob, TIMEOUT_CONN, TIMEOUT_ID, exp_end)) < 0)
		{
			printf ("- Espressione NON confermata\n");
			exit (1);
		}
		else
		*/
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
	char *lprompt=NULL;
	char *apprompt=NULL;
	int retval=1;
	int maxfd=0;
	struct timeval tv;
	fd_set rfds;
	int counter=MAXCOUNT;
	int foundit=0;
	int numofnewline=0;
	char smallbuffer[1];
	char *donebuffer=NULL;
	int sizedonebuffer=0;

	while ((counter) && (foundit < LEAST_TRUE))
	{
		printf ("- Start reading from fd %d\n", fd_expect);

		{
			
			printf ("-DONEBUFFER-(actual)----------------------\n");
                        printf ("%s\n", donebuffer);
                        printf ("------------------------------------------\n");

			printf ("\n-LPROMPT-(previous------------------------\n");
			printf ("%s\n",lprompt);
			printf ("------------------------------------------\n\n");

			if (lprompt)
                        {
                                numofnewline=0;
                                apprompt=lprompt;
                                while (apprompt[0]!='\0')
                                {
                                        if (*apprompt=='\n')
                                        {
                                                numofnewline++;
                                        }
                                        apprompt ++;
                                }
                                printf ("- Number of newline: %d\n",numofnewline);
                        }

		        if (( lprompt ) && ( strlen(lprompt) > MIN_PROMPT ) && ( numofnewline > 0 ) && ( numofnewline <= MAX_NEWLINE ) && ( strcmp( lprompt, donebuffer ) == 0 ))
               		{
				printf ("- Minimizing timeout window(%d millisec)\n", BUFFER_TIMEOUT);
				tv.tv_sec = 0;
                                tv.tv_usec = BUFFER_TIMEOUT; 
				foundit++;
				printf ("- Prompt found (already found: %d)\n", foundit);	
               		}
               		else
               		{
				printf ("- Maximazing timeout window(%d millisec)\n", MAX_BUFFER_TIMEOUT);
				tv.tv_sec = 0;
                                tv.tv_usec = MAX_BUFFER_TIMEOUT;

				printf ("- Resetting foundit\n");
				foundit=0;
			}

			if (lprompt)
			{
				free (lprompt);
			}

			lprompt=NULL;
			lprompt=(char *) malloc (sizeof (char) * sizedonebuffer);

                        if (lprompt)
                        {
                                memset (lprompt,0,sizedonebuffer);
                                strncpy(lprompt, donebuffer, sizedonebuffer);
                        }
                        else
                        {
                              	printf ("Impossibile allocare lprompt\n");
                               	exit (1);
                        }

			sizedonebuffer=0;
			if (donebuffer)
                        {
                        	free (donebuffer);
                        }

			do
			{
				maxfd=(fd_expect+1);
	                       	FD_ZERO(&rfds);
                	       	FD_SET(fd_expect, &rfds);
                        	retval = select(maxfd, &rfds, NULL, NULL, &tv);
				if (retval)
				{
					if (sizedonebuffer)
					{
						donebuffer=(char *) realloc (donebuffer,sizeof (char) * sizedonebuffer);
						if (!donebuffer)
                                        	{
                                                	exit (1);
                                        	}
                                        }
					else
					{
						sizedonebuffer=2;
                                                donebuffer=(char *) malloc (sizeof (char) * sizedonebuffer);
						if (!donebuffer)
                                        	{
                                                	exit (1);
                                        	}
						memset(donebuffer,0,sizedonebuffer);
                                        }
					sizedonebuffer=sizedonebuffer+2;

					read(fd_expect,smallbuffer,1);
					smallbuffer[1]='\0';
					strncat (donebuffer,smallbuffer,2);
				}
			}
			while (retval);

		}
		printf ("\n- End reading from fd: %d,  counter: %d - retval: %d\n", fd_expect, counter, retval);
		/* scriviamo newline sul fd */
                write(fd_expect, "\n",  1);
		counter --;
	}
}
