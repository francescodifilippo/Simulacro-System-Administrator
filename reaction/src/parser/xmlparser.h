#include <stdio.h>
#include <string.h>
#include <libxml/xmlwriter.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
static int ELEMENT=0;

typedef struct XmlParseBase
{
        const char *xmlid;
        const char *xmlvalue;
}XmlParse;

#if defined(LIBXML_WRITER_ENABLED) && defined(LIBXML_OUTPUT_ENABLED) \
&& defined(LIBXML_READER_ENABLED) && defined(LIBXML_TREE_ENABLED)




#else
int main(void) {
    printf(stderr, "Writer or output support not compiled in\n");
    exit(1);
}
#endif
