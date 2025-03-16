/***************************************************************************
 * Simulacro System Administrator SourceForge Project                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                         *
 *   Licensed under the GNU GPL                                            *
 ***************************************************************************/

/***************************************************************************
 *      Module Name:   xmlparse.h 
 *
 *      Abstract:
 *
 *      Revision History:
 *      Who             When            What
 *      --------        ----------      -------------------------------
 *      Name            Date            Modification logs
 *      Fabio Zito      06-01-2006      First release alpha0.1
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <libxml/xmlwriter.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>

#if defined(LIBXML_WRITER_ENABLED) && defined(LIBXML_OUTPUT_ENABLED) \
&& defined(LIBXML_READER_ENABLED) && defined(LIBXML_TREE_ENABLED)

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

#else
int main(void) {
    printf(stderr, "Writer or output support not compiled in\n");
    exit(1);
}
#endif
