#define BUFSIZE 1024
#define MICROBUF 32
#define SMALLBUF 256

#define TCPPORT 1234
#define MAXTHREADS 64
#define MAXSCRIPTLEN 131072

static char *okprompt="OK\n";
static char *nokprompt="NOK\n";
static char *welcome="REACTION 0.1-alfa Server Ready\n";
static char *help="valid command: help list run reset delete\nOK\n";

typedef struct Thread_Element
{
        struct Thread_Element *next;
        struct Thread_Element *prev;
        int socket;
        pthread_t thread;
}Thread_Elem;

typedef struct Script_Element
{
        struct Script_Element *next;
        struct Script_Element *prev;
        char *line;
}Script_Elem;

typedef Thread_Elem * Thread_List;

typedef Script_Elem * Script_List;
