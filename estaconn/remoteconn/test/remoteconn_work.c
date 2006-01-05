#include <stdio.h>
#include <stdlib.h>
#include <expect.h>
#include <regex.h>

#define VERBOSE 1
#define MAXCOUNT 5

#define ACCEPT_CONN "re you sure you want to continue connecting"
#define PASSWD_CONN "assword:"
#define REMOTE_CONN "remote host"
#define TIMEOUT_CONN "timeout"
#define PROMPT_CONN ".*\n"

#define ACCEPT_ID 1
#define PASSWD_ID 2
#define REMOTE_ID 3
#define TIMEOUT_ID 4
#define PROMPT_ID 5


void timedout(void);
void expect_auth(int, char*);
void ctrl_prompt(int);


int main(void)
{
	char *server = "localhost";
	char *login = "testuser";
	char *password ="cambiami\n";

	exp_loguser = 0;
	exp_timeout = 30;
	int fd;

	if ((fd=exp_spawnl("ssh","ssh","-l", login, server,(char *)0)) < 0)
	{
		perror("can't spawn!");
		exit(1);
	}

	expect_auth(fd, password);

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
                                        ctrl_prompt(fd_expect);
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

	if (VERBOSE)
	{
		printf ("BUFFER: %s\n",exp_buffer);
	}
}



void ctrl_prompt (int fd_expect)
{
	char *lprompt=NULL;
	int retval=1;
	int maxfd;
	struct timeval tv;
	fd_set fds;
	int counter=MAXCOUNT;
	int foundit=0;


	printf ("PROMPT SEARCH:\n");
	while (counter>0)
	{
		
		printf ("EXT counter: %d - retval: %d\n", counter, retval);
		do
		{
			printf ("INT counter: %d - retval: %d\n", counter, retval);
			exp_expectl(fd_expect, exp_regexp, PROMPT_CONN, PROMPT_ID, exp_end);
			if ((strstr (exp_buffer, "ermission")) || (strstr (exp_buffer, "assword:")) || (strstr (exp_buffer, "orry.")) || (strstr (exp_buffer, "uthentication failure")))
			{
				printf ("ERROR BUFFER: %s\n",exp_buffer);
				exit (1);
			}
			else
			{
				printf ("LPROMPT: %s\n",lprompt);
				printf ("EXP_MATCH: %s\n", exp_match);
			        if ((lprompt) && (strlen(lprompt) > 2 ) && (strcmp(lprompt, exp_match)==0))
                		{
					foundit=1;
					printf ("FOUND PROMPT: %s\n", lprompt);	
					exit (1);
                		}
                		else
                		{
					lprompt=(char *) realloc (lprompt, sizeof (char) * strlen (exp_match)+1);
                                       	if (lprompt)
                                       	{
                                               	memset (lprompt,0,strlen (exp_match));
                                               	strcpy(lprompt, exp_match);
                                       	}
                                       	else
                                       	{
                                      		printf ("Impossibile allocare lprompt\n");
                                               	exit (1);
                                      	}

           				/*tv.tv_sec = 2;
			                tv.tv_usec = 0;
                        		maxfd = (fd_expect + 1);
                        		FD_ZERO(&fds);
                        		FD_SET(fd_expect,&fds);
                        		retval = select(maxfd, &fds, NULL, NULL, &tv);
					*/
					printf ("INT2 counter: %d - retval: %d\n", counter, retval);
                		}

			}
		}
		while (retval>0);
		counter --;
		/* proviamo a controllare il prompt */
                printf ("--- sending new line --- \n");
                write(fd_expect, "\n",  strlen ("\n"));
	}


	if (foundit)
	{
		printf ("FOUND PROMPT: %s\n", lprompt);
	}
}
