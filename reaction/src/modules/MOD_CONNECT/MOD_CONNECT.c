#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h> 
#include "../../reaction.h"
#include "../../intern.h"
#include "../../blib.h"
#define BUFFSIZE 64 

/* function for manage buffer */
extern char *buffer_load(int); 


BVariant* function_MOD_CONNECT( BSContext *context, BList *args )
{
	int narg;
	BVariant *arg1, *arg2, *arg3;
	BVariant *result=NULL;
	
	int n;
	int sockfd, i;
	int check_connection=0;
	char *full_buffer=NULL;
	char ch;
	char *ipaddress=NULL;
	char *login=NULL;
	char *password=NULL;
	char *buffer;
    	struct sockaddr_in serv_addr;
    	struct hostent *server;

        /* server information */
	/* To DO*/
	int portno=80;
	char *servername = "www.tin.it";

	/* check number of arguments */
	narg = blist_length( args );
	if( narg == 3 )
	{

		/* get the arguments */
		arg1 = bvariant_copy( (BVariant*) blist_nth_data( args, 0 ) );
		arg2 = bvariant_copy( (BVariant*) blist_nth_data( args, 1 ) );
		arg3 = bvariant_copy( (BVariant*) blist_nth_data( args, 2 ) );

		bvariant_cast( arg1, BV_STRING );
		bvariant_cast( arg2, BV_STRING );
		bvariant_cast( arg3, BV_STRING );

		ipaddress = b_strdup( bvariant_as_string( arg1 ) );
		login = b_strdup( bvariant_as_string( arg2 ) );
		password = b_strdup( bvariant_as_string( arg3 ) );

		bvariant_free( arg1 );
		bvariant_free( arg2 );
		bvariant_free( arg3 );

        
        	/* open socket */
    		sockfd = socket(AF_INET, SOCK_STREAM, 0);
    		if (sockfd)
		{
        		/* resolv server name */
    			server = gethostbyname(servername);
			if (server) 
			{
				/* connect on server */
    				bzero((char *) &serv_addr, sizeof(serv_addr));
    				serv_addr.sin_family = AF_INET;
    				bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    				serv_addr.sin_port = htons(portno);
				check_connection=connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
        			if (check_connection >= 0)
				{
					/* request connection ID */
					buffer = (char *)malloc(sizeof(char)*BUFFSIZE);
 					snprintf(buffer,BUFFSIZE,"GET /\n\n");
    					i = write(sockfd,buffer,strlen(buffer));
    					if (n)
					{
						/* adjust the result request */
						full_buffer=buffer_load(sockfd);
					}		
				}
			}
		}
	}

	/* set the result */
	result = bvariant_new();
	bvariant_set_string( result, full_buffer );
	b_free( full_buffer );
	b_free( password );
	b_free( ipaddress );
	b_free( login );
	return result;
}
