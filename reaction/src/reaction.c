/*  This file is part of the RE-ACTION (BScript) project
    Copyright (C) 1999-2004 Marcello Russo - Ariya Hidayat <ariya@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>

#include "reaction.h"
#include "intern.h"
#include "blib.h"
#include "bsmt.h"

int initServer(void);
void test_pointer(void *retval, char *text);
void test_int(int retval,char *text);
void ServCleanup(void *args);
void *BSServer(void *args);

static int my_socket;
static struct sockaddr_in sockaddr_local;
static struct sockaddr_in sockaddr_remote;
static pthread_mutex_t list_mutex;
static int maxthreads=0;
extern int errno;
static int tcpport=TCPPORT;
Thread_List lista=NULL, coda=NULL;



int main (int argc, char *argv[])
{
	int r_socket;
	socklen_t socklen_remote;
	int testvar;

	Thread_List elem;

	/* creiamo il socket */
	my_socket = initServer();

	/* mettiamoci in ascolto */
	testvar=listen(my_socket, 10);
	test_int(testvar,"Impossibile eseguire il listen");

	while(1)
        {
                socklen_remote=sizeof(sockaddr_remote);
                r_socket = accept(my_socket, (struct sockaddr *) &sockaddr_remote, &socklen_remote);
                if (r_socket<0)
                {
                        exit(1);
                }

                if (maxthreads < MAXTHREADS)
                {
                        elem = malloc(sizeof(Thread_Elem));
                        test_pointer(elem, "Impossibile allocare spazio per elem");

                        pthread_mutex_lock(&list_mutex);

                        /* Inizio Corsa Critica */
                        elem->socket = r_socket;
                        elem->next = NULL;
                        elem->prev = coda;      /* il predecessore di elem e' coda! */
  
                        /* inseriamo il nuovo elemento in coda agli altri */
                        if (lista)
                        {
                                /* l'elemento non e' il primo */
                                coda->next = elem;
                        }
                        else
                        {
                                /* l'elemento e' il primo */
                                lista = elem;
                        }
                        coda = elem;

                        /* aumentiamo il numero di threads attivi */
                        maxthreads ++;

                        /* Fine Corsa Critica */
                        pthread_mutex_unlock(&list_mutex);

                        /* creiamo il nuovo thread */
                        pthread_create(&elem->thread, NULL, BSServer, elem);
                }
                else
                {
                        /* abbiamo raggiunto il numero massimo di threads */
                        close (r_socket);
                }
        }

	return 0;
}


/* funzione di Test su interi */
void test_int(int retval,char *text)
{
        FILE *fd_error;

        if (retval < 0)
        {
                perror(text);

                fd_error=fopen("error", "w");
                if (fd_error==NULL)
                {
                        fprintf(fd_error,"impossibile creare dump_list!");
                }
                else
                {
                        fprintf(fd_error,"%s\n",text);
                        fclose(fd_error);
                }
                exit(1);
        }
}



/* funzione di Test su Puntatori */
void test_pointer(void *retval, char *text)
{
        if (retval == NULL)
        {
                perror(text);
                exit(1);
        }
}


void ServCleanup(void *args)
{
        Thread_List th_list;

        th_list = args;
        close(th_list->socket);
        pthread_mutex_lock(&list_mutex);
        /* Inizio Corsa Critica */
        if(th_list->prev)
        {
                th_list->prev->next = th_list->next;
        }
                         
        if(th_list->next)
        {
                th_list->next->prev = th_list->prev;
        }
        else if(th_list->prev)
        {
                coda = th_list->prev;
        }
        if(lista==th_list)
        {
                lista = th_list->next;
        }

        /* liberiamo lo spazio allocato */
        free(th_list);

        /* diminuiamo il numero di threads attivi */
        maxthreads--;

        /* Fine Corsa Critica */
        pthread_mutex_unlock(&list_mutex);
}


/* Inizializzazione del Server */
int initServer(void)
{       
        int optval=1;
        int nsocket, nbind;
        
        /* Crea il socket */
        nsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
        setsockopt(nsocket, SOL_SOCKET, SO_REUSEADDR,(const void *)&optval , sizeof(int));
         
        test_int(nsocket, "non posso creare il socket!");
        
        /* Inizializzazione socket */
        sockaddr_local.sin_family = AF_INET;
        sockaddr_local.sin_port   = htons(tcpport);
        sockaddr_local.sin_addr.s_addr = INADDR_ANY;
                
        sockaddr_remote.sin_family = AF_INET;
        sockaddr_remote.sin_family = htons(tcpport);
                        
        /* bind Socket */
        nbind = bind(nsocket, (struct sockaddr *) &sockaddr_local, sizeof(sockaddr_local));
        test_int(nbind, "Non posso eseguire il bind sul socket!");
                        
        return nsocket;
}
                

void *BSServer(void *args)
{                               
        BSModule* module;

	Script_List script_head=NULL;
	Script_List script_current=NULL;
	Script_List script_tail=NULL;
	Script_List script_app=NULL;
	int script_line=1;
	int script_size=0;
	int script_pos=1;

        Thread_List th_list;
        char searchstr[SMALLBUF];
        char buf[BUFSIZE];
        char writebuffer[BUFSIZE];
	
        
        int len;
	int buflen;
        fd_set fds;
        int maxfd;
        int retval;
        struct timeval tv;
        int setexit=0;
	char *totalbuffer=NULL;
	char *testpos;
	char strline2remove[MICROBUF];
	double line2remove;
	int mypos=1;

        signal(SIGPIPE, SIG_IGN);
        th_list=args;

	/* impostiamo la dimensione massima del nostro script */
	totalbuffer=(char *) malloc ((sizeof (char)) * MAXSCRIPTLEN);
	memset (totalbuffer, 0, MAXSCRIPTLEN);

        pthread_setcanceltype(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, NULL);
        pthread_testcancel();

	write(th_list->socket, welcome, strlen(welcome));

	while(setexit==0)
        {
                /* reimposta ad ogni loop il timeout sulla select */
                tv.tv_sec = 180;
                tv.tv_usec = 0;

                memset(buf, 0, BUFSIZE);
                memset(writebuffer, 0, BUFSIZE);
                memset(searchstr, 0, SMALLBUF);

                maxfd = (th_list->socket + 1);
                FD_ZERO(&fds);
                FD_SET(th_list->socket,&fds);
                retval = select(maxfd, &fds, NULL, NULL, &tv);
                if(retval)
                {
                        len = read(th_list->socket, buf, BUFSIZE);
			buflen=strlen(buf);
			
			/* se la dimensione del buffer e' uguale a 0 e accaduto qualcosa dall'altra parte..... */
                        if (len <=0)
                        {
                                setexit=1;
                                break;
                        }
			if (strstr(buf,"run"))
                        {
				/* inseriamo tutta la lista nella zona di memoria puntata da totalbuffer */
				totalbuffer=malloc (sizeof (char) * script_size+1);
				if (totalbuffer)
				{
					memset (totalbuffer,0,script_size+1);
					script_app=script_head;
                                	while (script_app)
                                	{
						strcat(totalbuffer,script_app->line);
                                        	script_app=script_app->next;
                                	}
				
					/* creiamo/eseguiamo/chiuduamo il modulo */
					module = bs_module_create( "test" );
					bs_module_set_code( module, totalbuffer, th_list->socket );
					bs_module_execute( module, th_list->socket );
					bs_module_destroy( module );
					
					/* liberiamo il buffer */
					free( totalbuffer );
                                	totalbuffer=NULL;

					write(th_list->socket, okprompt,sizeof(okprompt));
				}
				else
				{
					write(th_list->socket, nokprompt,sizeof(nokprompt));
				}
			}
			/* HELP */
                        else if (strstr(buf,"help"))
                        {
                                write(th_list->socket, help, strlen(help));
                        }
                        /* QUIT */
                        else if (strstr(buf,"quit"))
                        {
                                setexit=1;
                        }
			/* LIST */
			else if (strstr(buf,"list"))
			{
				script_pos=1;
				script_app=script_head;
                        	while (script_app)
                        	{
					snprintf(writebuffer,BUFSIZE,"%d: %s",script_pos, script_app->line);
                                	write(th_list->socket,writebuffer, strlen(writebuffer));
					script_app=script_app->next;
					script_pos++;
				}
				write(th_list->socket, okprompt,sizeof(okprompt));	
			}
			else if ((testpos=strstr(buf,"delete")))
                        {
				strncpy(strline2remove, testpos+6, MICROBUF);
				line2remove=strtol(strline2remove,NULL,10);

				script_app=script_head;
				mypos=1;
                                while ((script_app) && (line2remove))
				{
                			if (mypos==line2remove)
                			{
                        			if(script_app->prev)
                        			{
                               				script_app->prev->next = script_app->next;
                        			}
                        			if(script_app->next)
                        			{
                               				script_app->next->prev = script_app->prev;
                        			}

                        			/* Controlliamo se stiamo modificando la testa */
                        			if(script_head==script_app)
                        			{
                                			script_head = script_app->next;
                        			}

                        			/* Controlliamo se stiamo modificando la coda */
                        			if(script_tail==script_app)
                        			{
                                			script_tail = script_app->prev;
                        			}

                        			/* liberiamo lo spazio allocato dall struttura */
                        			free(script_app);
                			}
                			/* controlliamo l'elemento successivo */
                			script_app=script_app->next;
					mypos++;
        			}
				write(th_list->socket, okprompt,sizeof(okprompt));
			}
			/* RESET */
                        else if (strstr(buf,"reset"))
                        {
				script_app=script_head;
                                while (script_app)
                                {
					/* liberiamo lo spazio allocato dall struttura */
                                	free (script_app->line);
					script_app->line=NULL;

					/* liberiamo l'elemento precedente, se esiste */
					if (script_app->prev)
					{
                        			free(script_app->prev);
						script_app->prev=NULL;
					}

                                        script_app=script_app->next;
                                }
				script_head=NULL;
				script_tail=NULL;
				script_current=NULL;
				script_size=0;
                                script_line=1;
				write(th_list->socket, okprompt,sizeof(okprompt));
                        }
			/* NEWLINE - ps e' uguale a 0 perche' e stato rimosso all'inizio ....*/
                        else if (len<=2)
                        {
                                write(th_list->socket, okprompt,sizeof(okprompt));
                        }
                        /* LIST */
                        else
                        {
				script_current = NULL;
				script_current = malloc(sizeof(Script_Elem));
				if (script_current)
				{
					script_current->line = (char *) malloc ((sizeof (char)) * buflen);
					if (script_current->line)
					{
						/* riempimento struttura */
						memset(script_current->line,0,buflen);
						strcpy(script_current->line,buf);
                        			script_current->next = NULL;
                        			script_current->prev = script_tail;
						
						/* inseriamo il nuovo elemento in coda agli altri */
                        			if (script_head)
                        			{
                                			/* l'elemento non e' il primo */
                                			script_tail->next = script_current;
                        			}
                        			else
                        			{
                                			/* l'elemento e' il primo */
                                			script_head = script_current;
                        			}
						script_tail = script_current;

						/* parametri script */
                                                script_size+=buflen;
                                                script_line ++;
					}
					else
					{
						write(th_list->socket, nokprompt,sizeof(nokprompt));
					}
				}
				else
				{
					write(th_list->socket, nokprompt,sizeof(nokprompt));
				}
                        }
		}
		else
                {
                        setexit=1; /* timeout sulla select */
                } /* end select */
	}
	/* eseguiamo il cleanup */
	free (totalbuffer);
	totalbuffer=NULL;

	ServCleanup(th_list);
	return NULL;
}
