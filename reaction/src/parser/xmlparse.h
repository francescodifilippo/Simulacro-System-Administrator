#include <stdio.h>
#include <string.h>
#include <libxml/xmlwriter.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>

#ifndef __PARSE_H
#define __PARSE_H


#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

#if defined(LIBXML_WRITER_ENABLED) && defined(LIBXML_OUTPUT_ENABLED) \
&& defined(LIBXML_READER_ENABLED) && defined(LIBXML_TREE_ENABLED)
#else
int main(void) {
    printf(stderr, "Writer or output support not compiled in\n");
    exit(1);
}
#endif

/* Parse/Deparse  */
typedef struct XmlParseBase
{
        const char *xmlid;
        const char *xmlvalue;
}XmlParse;

/* parsing stream */
int xmlparse(char *,XmlParse *);

/* deparsing stream */
int count_element(xmlNode * a_node);
int  xmldeparse(const char *);

static int ELEMENT=0;

#endif

