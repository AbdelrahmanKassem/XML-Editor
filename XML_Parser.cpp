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

void Text_to_Vector(string file_data,vector<string> &XML_Vector , unsigned int &XML_Size)
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

void XML_Parser(vector<string> &tags, unsigned int &lines, vector<string> &XML_Original, vector<string> &XML_Fix , vector<string> &XML_ReadFile , unsigned int &XML_Size)
{

	char start;
	char end;
	char anotherend;

	int NumOpenTags=0;
	string temp;
	string t;
	stack <string> OpenAngleStack;

	string file_data = read_file(); //this line will be removed when we implement the function with gui
	Text_to_Vector(file_data,XML_ReadFile, XML_Size);

	while( lines < XML_Size)
	{
		temp = XML_ReadFile[lines];
		XML_Original[lines] = temp;
		XML_Fix[lines] = temp;

		/* CHECK FOR INPUT WE DON'T WANT TO ADJUST */
		if  ( (( (temp[1] == '?') || (temp[1] == '!')) && temp[0] == '<') || (temp.find("<") == -1) || (temp.find(">") == -1) || ( temp == "" ))
 		{
			XML_Original[lines]= temp;
			XML_Fix[lines] = temp;
			lines++;
			continue;
		}


		start = temp.find("<") + 1;
		end = temp.find(">");

		if (temp[start] == '/')
		{
			t = temp.substr((start + 1), end - (start + 1)); 				// we want the string without '/' to compare with the top of the stack

			if (t != OpenAngleStack.top())
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
			/* Only push keyword in the stack for example "synset type="a" id=a00001740" ( Only push synset ) */
			anotherend = temp.find(" ");
			if (anotherend > start && anotherend < end)
				tags[NumOpenTags] = temp.substr(start, anotherend - start);

			else
				tags[NumOpenTags] = temp.substr(start, end - start);

			if (tags[NumOpenTags] == "frame")						// Self Closing Tags
			{
				lines++;
				continue;
			}

			OpenAngleStack.push(tags[NumOpenTags++]);

		}
		lines++;

	}

	while (OpenAngleStack.empty() == false)
	{
		XML_Original[lines] = "    <----error here";					// Last angle missing  ( ERROR )
		XML_Fix[lines] += ("</" + OpenAngleStack.top() + ">");		    // Fix
		OpenAngleStack.pop();
		lines++;														// Increase size of lines
	}

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
