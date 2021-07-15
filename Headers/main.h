#ifndef MAIN_H_
#define MAIN_H_

#include "XML_Parser.h"
#include "XML_Pretify.h"
#include "XML_Minify.h"
#include "XML_JSON.h"
#include "XML_Parser.h"

#define MAX_SIZE 6000


/* GLOBAL VARIABLES */

extern unsigned int NumOfLines ;
extern unsigned int sizeOfXML ;
extern unsigned int sizeOfJSON ;

/* GLOBAL VECTORS */

extern vector<string> XML_original;
extern vector<string> XML_FixedErrors;
extern vector<string> Spaces;
extern vector<string> JSON;
extern vector<string> XML_ReadFile;


/* FUNCTION PROTOTYPES */

void Output_File( const vector<string> &XML_string, int size);
void Output_File(const vector<string> &Spaces, const vector<string> &XML_string, int size,string caller);
void Print_XML( const vector<string> &XML_string, int size);
void Print_XML(const vector<string> &Spaces, const vector<string> &XML_string, int size);




#endif /* MAIN_H_ */
