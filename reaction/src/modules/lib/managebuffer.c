#include <stdio.h>
#define BUFFSIZE 64 


char *buffer_load( int fd_buffer )
{
	char *full_buffer=NULL;
	char *buffer=NULL;
        int buffer_len=0;
	int total_buffer=0;

	typedef struct Page_Element
	{
        	struct Page_Element *next;
		char *page;
	}Page_Elem;

	typedef Page_Elem * Page_List;
	Page_List Page_Head=NULL;
	Page_List Page_Current=NULL;
	Page_List Page_Previus=NULL;
	Page_List Page_App=NULL;

	buffer = (char *)malloc(sizeof(char)*BUFFSIZE);
	if (! buffer)
	{
		return (NULL);
	}
	memset (buffer,0,BUFFSIZE);

    	while (read(fd_buffer,buffer,BUFFSIZE))
	{	
		buffer_len=strlen(buffer);
		Page_Current=(Page_List) malloc(sizeof(Page_List));
		if (Page_Current)
		{
			Page_Current->next=NULL;
			Page_Current->page=(char *)malloc(sizeof(char)*buffer_len+1);
			if (Page_Current->page)
			{
				memset(Page_Current->page,0,buffer_len);
				strcpy(Page_Current->page,buffer);
				if (Page_Head)
				{
					Page_Previus->next=Page_Current;
				}
				else
				{
					Page_Head=Page_Current;
				}
				Page_Previus=Page_Current;
				total_buffer+=buffer_len;
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
		memset(buffer,0,BUFFSIZE);
	}		

	Page_App=Page_Head;
	full_buffer=(char *) malloc (sizeof(char)*total_buffer+1);

	if(!full_buffer)
	{
		return (NULL);
	}
	memset(full_buffer,0,total_buffer);
	while (Page_App)
	{
		strcat(full_buffer,Page_App->page);
		free (Page_App->page);
		Page_App=Page_App->next;
	}

	return (full_buffer);
}
