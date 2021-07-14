
#include "XML_Parser.h"
#include "XML_Pretify.h"
#include "XML_Minify.h"
#include "XML_JSON.h"
#include "XML_Parser.h"
using namespace std;

#define MAX_SIZE 6000

void Output_File(const vector<string> &Spaces, const vector<string> &XML_string, int size);
void Print_XML(const vector<string> &Spaces, const vector<string> &XML_string, int size);


int main()
{
	unsigned int NumOfLines = 0;
	unsigned int sizeOfXML =0;
	vector<string> Tags(MAX_SIZE);
	vector<string> XML_ReadFile(MAX_SIZE);
	vector<string> XML_original(MAX_SIZE);
	vector<string> XML_FixedErrors(MAX_SIZE);
	vector<string> Spaces(MAX_SIZE);
	vector<string> json(MAX_SIZE);

	XML_FixErrors(Tags, NumOfLines, XML_original, XML_FixedErrors,XML_ReadFile , sizeOfXML);		// FIND ERRORS AND FIX THEM

	XML_indent(Spaces, XML_FixedErrors , NumOfLines );												// TO GET INDENTION LEVELS TO PRINT OUT XML LINES CORRECTLY

	cout << "-----------------------------      BEFORE FIX  WITH INDENTION     -----------------------------" << " \n \n ";
	 Print_XML(Spaces, XML_original, NumOfLines);
//	 Output_File(Spaces, XML_original, NumOfLines);

	cout << "-----------------------------      AFTER FIX  WITH INDENTION     -----------------------------" << " \n \n ";
	 Print_XML(Spaces, XML_FixedErrors, NumOfLines);
	//Output_File(Spaces, XML_FixedErrors, NumOfLines);

	cout << "------------------------------      XML TO JSON    ------------------------------------" << " \n \n ";



	cout << "------------------------------      MINIFYING    ------------------------------------" << " \n \n ";
	XML_Minify(XML_FixedErrors,NumOfLines);



	return 0;
}


void Output_File(const vector<string> &Spaces, const vector<string> &XML_string, int size)	  // Passed constant by reference to save memory and time
{
	fstream newfile;
	newfile.open("TEXTOUTPUT.xml",ios::out);
	if(newfile.is_open())
	{
		for (int i = 0; i < size; i++)
		{
			newfile << Spaces[i] << XML_string[i] << "\n";
		}
	}
}



void Print_XML(const vector<string> &Spaces, const vector<string> &XML_string, int size)   // Passed constant by reference to save memory and time
{
	for (int i = 0; i < size; i++)
		cout << Spaces[i] << XML_string[i] << "\n";

}
