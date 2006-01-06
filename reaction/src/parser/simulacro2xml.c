
/* compile: gcc `xml2-config --cflags --libs` -o simulacro2xml simulacro2xml.c */

#include <stdio.h>
#include <string.h>
#include <libxml/xmlwriter.h>
#include "xmlparser.h"


int moduleXmlwriter(char *,XmlParse *);

int main(int argc, char **argv)
{
     
      	char *module="prova";
	int count;
	int varcount;

	XmlParse *xmlhead;
	XmlParse *xmlelems;

	count=(argc / 2);
	xmlelems=(XmlParse *) malloc (sizeof (XmlParse) * count + 1);
	xmlhead=xmlelems;
	for (varcount=0;varcount<count;varcount++)
	{
		xmlelems->xmlid=*argv;
		**argv++;
		xmlelems->xmlvalue=*argv;
		**argv++;
		xmlelems++;
	}

	xmlelems=NULL;

	
      	LIBXML_TEST_VERSION

	/* the memory version */
   	moduleXmlwriter(module,xmlhead);


    /*
     * Cleanup function for the XML library.
     */
    xmlCleanupParser();
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
    return (0);
}


int moduleXmlwriter(char *module, XmlParse *xmlhead)
{
   int rc;
   xmlTextWriterPtr writer;
   xmlBufferPtr buf;

   buf = xmlBufferCreate();
   if (buf == NULL) 
   {
      return (1);
   }

   writer = xmlNewTextWriterMemory(buf, 0);
   if (writer == NULL) 
   {
      return (1);
   }

   rc = xmlTextWriterStartElement(writer, BAD_CAST module);
   if (rc < 0) 
   {
      return (1);
   }

    while(xmlhead->xmlid)
    {

         rc = xmlTextWriterWriteElement(writer, BAD_CAST xmlhead->xmlid, BAD_CAST xmlhead->xmlvalue);
         if (rc < 0) 
         {
            return (1);
         }
	*xmlhead++;
   }

   rc = xmlTextWriterEndElement(writer);
   if (rc < 0) 
   {
      return (1);
   } 
   rc = xmlTextWriterEndDocument(writer);
   if (rc < 0) 
   {
      return (1);
   }
    xmlFreeTextWriter(writer);
    printf ("%s\n", (const char *) buf->content);
    xmlBufferFree(buf);
}
