#include "XML_Parser.h"

string read_file(void)
{
	//this part will be replaced with string sent directly from GUI
	ifstream indata;
	indata.open("Trial.txt"); //opening file with input mode
	string file_data;

	if(indata.is_open()) //check if file if correctly opened
	{
		string line;
		while(getline(indata,line))
		{
			file_data = file_data + line; //put all the lines in one string
		}
	}
	return file_data;
}

void XML_Parser(string file_data,vector<string> &XML_Vector , unsigned int &XML_Size)
{
	int str_start;
	int str_end;
	int file_data_index=0;
	while(file_data[file_data_index] != '\0')
	{
		string line="";
		while(file_data[file_data_index] == ' ')
		{
			file_data_index++;
		}
		if(file_data[file_data_index] == '<')
			{
				str_start = file_data_index;
				str_end = file_data_index+1;
				while(file_data[str_end] != '>' && file_data[str_end] != '\0')
				{
					str_end++;
				}
				if(file_data[str_end] == '\0')
				{
					break;
				}
			}
			else //normal input(not tags)
			{
				str_start = file_data_index;
				str_end = file_data_index+1;
				while(file_data[str_end] != '<' && file_data[str_end] != '\0')
				{
					str_end++;
				}
				str_end--; //So we dont take "<" with us
				if(file_data[str_end] == '\0')
				{
					break;
				}
			}

		file_data_index = str_end+1;
		XML_Vector[XML_Size++]=(file_data.substr(str_start, str_end - str_start +1));
	}
}

void XML_FixErrors( unsigned int &lines, vector<string> &XML_Original, vector<string> &XML_Fix , vector<string> &XML_ReadFile , unsigned int &XML_Size)
{

	char start;
	char end;
	char anotherend;
	int Index=0;
	int NumOpenTags=0;
	string temp;
	string t;
	stack <string> OpenAngleStack;
	string pushedTag;
	bool info = false;

	string file_data = read_file(); //this line will be removed when we implement the function with gui
	XML_Parser(file_data,XML_ReadFile, XML_Size);

	while( lines <  ( XML_Size + (lines-Index) )  )			// lines can be bigger than XML_Size in some cases to solve this (line-index) difference
	{
		temp = XML_ReadFile[Index++];
		XML_Original[lines] = temp;
		XML_Fix[lines] = temp;

		/* CHECK FOR INPUT WE DON'T WANT TO ADJUST */
		if  ( (( (temp[1] == '?') || (temp[1] == '!')) && temp[0] == '<') || (temp.find("<") == -1) || (temp.find(">") == -1) || ( temp == "" ))
 		{
			XML_Original[lines]= temp;
			XML_Fix[lines] = temp;

			if( ( temp != "" ) && !OpenAngleStack.empty() && (temp.find("<") == -1)  && pushedTag == OpenAngleStack.top() )
				info = true;


			lines++;
			continue;
		}


		start = temp.find("<") + 1;
		end = temp.find(">");

		if (temp[start] == '/')
		{
			info = false;
			t = temp.substr((start + 1), end - (start + 1)); 				// we want the string without '/' to compare with the top of the stack

			if( OpenAngleStack.empty() )
			{
				lines++;
				continue;
			}


			if (t != OpenAngleStack.top() )
			{
				XML_Original[lines] += "    <----error here";					// Indicate Error
				XML_Fix[lines] = ("</" + OpenAngleStack.top() + ">");			// To Fix Errors
				OpenAngleStack.pop();											// Pop stack to indicate new errors
			}
			else
				OpenAngleStack.pop();											// No errors angles match !!

		}

		else
		{

			/* In Case the opening tag contains information in a new line and there was no closed tag ( missing closed tag ) SPECIAL CASE FOR ERRORS */

			if ((end!=-1) && (temp[end - 1] == '/'))				// SELF CLOSING TAGS
			{
				lines++;		continue;
			}

			if (info == true)
			{
				info =false;

				/* SAVE THE NEW OPEN TAG IN A NEW LINE */
				XML_Original[lines+1] = XML_Original[lines];
				XML_Fix[lines+1] = 	XML_Fix[lines];

				/* MAKE AN EMPTY LINE WHERE WE'LL INDICATE THE ERROR AND FIX IT */
				XML_Original[lines] = " \t \t   <----error here";			// Indicate Error
				XML_Fix[lines] = ("</" + OpenAngleStack.top() + ">");			// To Fix Errors

				OpenAngleStack.pop();											// Pop stack to indicate new errors
				lines++;
			}


			/* Only push keyword in the stack for example "synset type="a" id=a00001740" ( Only push synset ) */
			anotherend = temp.find(" ");
			if (anotherend > start && anotherend < end)
				pushedTag = temp.substr(start, anotherend - start);

			else
				pushedTag= temp.substr(start, end - start);


			OpenAngleStack.push(pushedTag);


		}
		lines++;

	}

	while (OpenAngleStack.empty() == false)
	{
		XML_Original[lines] = "    <----error here";					// Last closed tag missing  ( ERROR )
		XML_Fix[lines] += ("</" + OpenAngleStack.top() + ">");		    // Fix
		OpenAngleStack.pop();
		lines++;														// Increase size of lines
	}

}
