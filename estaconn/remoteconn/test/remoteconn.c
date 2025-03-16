#include <stdio.h>
#include <stdlib.h>
#include <expect.h>
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
#define BUFFER_TIMEOUT 1
#define EXPECT_TIMEOUT 15

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

	exp_loguser = 1;
	exp_timeout = EXPECT_TIMEOUT;
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
					write(fd_expect,"yes\r",strlen("yes\r"));
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
}



void ctrl_prompt (int fd_expect)
{
	char *lprompt=NULL;
	int retval=1;
	int maxfd;
	struct timeval tv;
	fd_set rfds;
	int counter=MAXCOUNT;
	int foundit=0;

	while ((counter) && (foundit < LEAST_TRUE))
	{
		printf ("- Start reading from fd %d\n", fd_expect);
               	exp_expectl(fd_expect, exp_regexp, PROMPT_CONN, PROMPT_ID, exp_end);
		if ((strstr (exp_buffer, "ermission")) || (strstr (exp_buffer, "assword:")) || (strstr (exp_buffer, "orry.")) || (strstr (exp_buffer, "uthentication failure")))
		{
			printf ("ERROR BUFFER: %s\n",exp_buffer);
			exit (1);
		}
		else
		{
			printf ("\n-LPROMPT----------------------------------\n");
			printf ("%s\n",lprompt);
			printf ("------------------------------------------\n\n");
			
			printf ("-EXP_MATCH--------------------------------\n");
			printf ("%s\n", exp_match);
			printf ("------------------------------------------\n");

			printf ("-EXP_BUFFER--------------------------------\n");
			printf ("%s\n", exp_buffer);
			printf ("------------------------------------------\n");

		        if ((lprompt) && (strlen(lprompt) > MIN_PROMPT ) && (strcmp(lprompt, exp_match)==0))
               		{
				foundit++;
				printf ("FOUND PROMPT: %s - %d\n", lprompt, foundit);	
               		}
               		else
               		{
				foundit=0;
				printf ("RESET foundit\n");
			}
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
			do
			{
	           		tv.tv_sec = BUFFER_TIMEOUT;
			        tv.tv_usec = 0;

				maxfd=(fd_expect+1);
	                       	FD_ZERO(&rfds);
                	       	FD_SET(fd_expect, &rfds);
                        	retval = select(maxfd, &rfds, NULL, NULL, &tv);
/*				if (retval)
				{
					char s[2];
					read(fd_expect,s,1);
					s[1]='\0';
					printf ("%s\n",s);
				}
*/
			}
			while (retval);
		}
		printf ("\n- End reading from fd: %d,  counter: %d - retval: %d\n", fd_expect, counter, retval);
		/* scriviamo newline sul fd */
                write(fd_expect, "\n",  1);
		counter --;
	}


	if (foundit)
	{
		printf ("FOUND PROMPT: %s\n", lprompt);
	}
}
