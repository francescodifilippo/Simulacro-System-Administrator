#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h> 
#include <regex.h> 
#include "../../reaction.h"
#include "../../intern.h"
#include "../../blib.h"
/* function for check regular expresion */
int reg_exp(char *, char *);


BVariant* function_MOD_REG( BSContext *context, BList *args )
{
	int narg;
	BVariant *arg1, *arg2;
	BVariant *result=NULL;
	
	int status=0;
	char *string=NULL;
	char *regexp=NULL;

	/* check number of arguments */
	narg = blist_length( args );
	if( narg == 2 )
	{

		/* get the arguments */
		arg1 = bvariant_copy( (BVariant*) blist_nth_data( args, 0 ) );
		arg2 = bvariant_copy( (BVariant*) blist_nth_data( args, 1 ) );

		bvariant_cast( arg1, BV_STRING );
		bvariant_cast( arg2, BV_STRING );

		string = b_strdup( bvariant_as_string( arg1 ) );
		regexp = b_strdup( bvariant_as_string( arg2 ) );

		bvariant_free( arg1 );
		bvariant_free( arg2 );

        	/* check regular expresion */
		status=reg_exp(string,regexp);
	}	

	/* set the result */
	result = bvariant_new();
	bvariant_set_double(result,status);
	b_free( string );
	b_free( regexp );
	return result;
}
int reg_exp(char *string, char *pattern)
{
        int status;
        regex_t re;

        if(regcomp(&re, pattern,REG_EXTENDED|REG_NOSUB)!=0)
        {
                return(0); 
        }

        status=regexec(&re, string, (size_t) 0, NULL, 0);

        regfree(&re);

        if(status!=0)
        {
                return(0);
        }
	return(1);
        
}
