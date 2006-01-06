/* compile: gcc `xml2-config --cflags --libs` -o xml2simulacro xml2simulacro.c */

#include "xmlparser.h"

int count_element(xmlNode * a_node);
int  deparse(const char *);

int main(int argc, char **argv) 
{

	if (argc != 2)
		return(1);

	LIBXML_TEST_VERSION

	xmlDoc *doc = NULL;
	xmlNode *root_element = NULL;

	doc = xmlReadMemory(argv[1],strlen(argv[1]),"",NULL, 0);

	if (doc == NULL) 
	{
        	return(1);
	}

	root_element = xmlDocGetRootElement(doc);

	count_element(root_element);

	xmlFreeDoc(doc);

	deparse(argv[1]);

	xmlCleanupParser();

	xmlMemoryDump();

	return(0);
}

int count_element(xmlNode * a_node)
{
	int element_count=0;
	xmlNode *cur_node = NULL;

	
	for (cur_node = a_node; cur_node; cur_node = cur_node->next) 
	{
		if (cur_node->type == XML_ELEMENT_NODE) 
		{
			ELEMENT++;
		}

			count_element(cur_node->children);
	}
}


int deparse(const char *sBuffer) 
{
	int ret;
	int check;
	int element=ELEMENT -1;
        const char *module=NULL;

        const xmlChar *name, *value;
	xmlTextReaderPtr reader;
	xmlBufferPtr buf;

	XmlParse *xmlhead;
        XmlParse *xmlelems;
	xmlelems=(XmlParse *) malloc (sizeof (XmlParse) * element);
        xmlhead=xmlelems;
	xmlelems->xmlid=NULL;
	xmlelems->xmlvalue=NULL;


	reader = xmlReaderForMemory (sBuffer, strlen(sBuffer), "", NULL, 0);

	if (reader != NULL) 
	{
		element=element+element;
		ret = xmlTextReaderRead(reader);
		while (ret == 1) 
		{
			name = xmlTextReaderConstName(reader);
    			if (name == NULL)
        			name = BAD_CAST "--";
    			value = xmlTextReaderConstValue(reader);
    			check=xmlTextReaderDepth(reader)+xmlTextReaderNodeType(reader);
			if (check == 1)
			{
				module=name;
			}
			if (check == 2 && element)
			{
				xmlelems->xmlid = (char *) malloc ((sizeof (char)) * strlen(name));
				memset((char *) xmlelems->xmlid,0,strlen(name));
                                strcpy((char *) xmlelems->xmlid,name);
				element--;
			}
			if (check == 5 && element)
			{
				xmlelems->xmlvalue = (char *) malloc ((sizeof (char)) * strlen(value));
				memset((char *) xmlelems->xmlvalue,0,strlen(value));
                                strcpy((char *) xmlelems->xmlvalue,value);
				element--;
				xmlelems++;
			}
			ret = xmlTextReaderRead(reader);
		}
		xmlelems=NULL;
		xmlFreeTextReader(reader);
		if (ret != 0) 
		{
			return (1);
		}
	} 
	else 
	{
		return (1);
	}
	printf ("%s",module);
	while(xmlhead->xmlid)
    	{
		printf (" %s %s",xmlhead->xmlid,xmlhead->xmlvalue);

        *xmlhead++;
   	}
	printf("\n");

}
