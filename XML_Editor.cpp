#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>

using namespace std;

void Print_XML(vector<string> Spaces, const vector<string> &XML_string, int size)   // Passed constant by reference to save memory and time
{
	for (int i = 0; i < size; i++)
		cout << Spaces[i] << XML_string[i] << "\n";
}



void XML_Parser(vector<string> &OpenTags, int &lines, vector<string> &XML_Original, vector<string> &XML_Fix)
{

	int OpenTagIndex=0;
	string temp;
	string t;
	stack <string> OpenAngleStack;

	char start;
	char end;
	char anotherend;
	bool info = false;


	ifstream indata;
	indata.open("Trial.txt");

	do
	{
		getline(indata, temp);
		XML_Original[lines] = temp;
		XML_Fix[lines] = temp;

		/* CHECK FOR INPUT WE DON'T WANT TO ADJUST */
		if  ( (( (temp[1] == '?') || (temp[1] == '!')) && temp[0] == '<') || (temp.find("<") == -1) || (temp.find(">") == -1) || ( temp == "" ))
 		{
			XML_Original[lines]= temp;
			XML_Fix[lines] = temp;
			lines++;

			if( !OpenAngleStack.empty() && (temp.find("<") == -1) && ( temp != "" ) && OpenTags[OpenTagIndex-1] == OpenAngleStack.top() )
			{	info = true; }

			continue;
		}


		start = temp.find("<") + 1;
		end = temp.find(">");

		if (temp[start] == '/')
		{
			info = false;
			t = temp.substr((start + 1), end - (start + 1)); 				// we want the string without '/' to compare with the top of the stack

			if (t != OpenAngleStack.top())
			{
				XML_Original[lines] += " \t \t  <----error here";				// Indicate Error
				XML_Fix[lines] = ("</" + OpenAngleStack.top() + ">");			// To Fix Errors
				OpenAngleStack.pop();											// Pop stack to indicate new errors
			}
			else
				OpenAngleStack.pop();											// No errors angles match !!

		}


		else
		{

			/* In Case the opening tag contains information in a new line and there was no closed tag ( missing closed tag ) SPECIAL CASE FOR ERRORS */

			if (info == true)
			{
				XML_Original[lines-1] += " \t \t   <----error here";			// Indicate Error
				XML_Fix[lines-1] = ("</" + OpenAngleStack.top() + ">");			// To Fix Errors
				OpenAngleStack.pop();											// Pop stack to indicate new errors
				lines++;
				continue;
			}


			/* Only push keyword in the stack for example "synset type="a" id=a00001740" ( Only push synset ) */
			anotherend = temp.find(" ");
			if (anotherend > start && anotherend < end)
				OpenTags[OpenTagIndex] = temp.substr(start, anotherend - start);

			else
				OpenTags[OpenTagIndex] = temp.substr(start, end - start);

			if (OpenTags[OpenTagIndex] == "frame")						// Self Closing Tags
			{
				lines++;
				continue;
			}

			OpenAngleStack.push(OpenTags[OpenTagIndex++]);


			/* Check if the closing angle is in the same string if so parse it and check for errors */

			temp = temp.substr(end + 1);

			if (temp != "") {
				start = temp.find("<") + 1;
				end = temp.find(">");
				t = temp.substr(start + 1, end - (start + 1));

				if (temp.find("<") == -1 || temp.find(">") == -1)					// Closed angle is missing
				{
					XML_Original[lines] += " \t \t  <----error here";					// Indicate Error
					XML_Fix[lines] += ("</" + OpenAngleStack.top() + ">");		// Fix
					OpenAngleStack.pop();											// Pop stack to indicate new errors in next iteration
				}

				else if (t != OpenAngleStack.top())
				{
					XML_Original[lines] += "  \t \t <----error here";													// Indicate Error
					XML_Fix[lines] = XML_Fix[lines].substr(0, start) + ("</" + OpenAngleStack.top() + ">");		// Fix ( Remove wrong tag and place correct tag )
					OpenAngleStack.pop();																			// Pop stack to indicate new errors in next iteration
				}

				else
					OpenAngleStack.pop();											// No errors angles match !!

			}
		}

		lines++;

	} while (!indata.eof());		// while the file isn't empty keep taking inputs

	while (OpenAngleStack.empty() == false)
	{
		XML_Original[lines] = " \t \t    <----error here";					// Last angle missing  ( ERROR )
		XML_Fix[lines] += ("</" + OpenAngleStack.top() + ">");				// Fix
		OpenAngleStack.pop();
		lines++;														// Increase size of lines
	}

}


void indent(vector<string> &space, int &index, int NumOfSpaces)
{
	for (int i = 0; i < NumOfSpaces; i++)
	{
		space[index] = space[index] + " ";
	}
	index++;
}


void XML_indent(vector<string> &OutputSpaces, vector<string> &XML_Fixed)
{
	char start;
	char end;
	char anotherend;
	bool flag = false;
	unsigned int LineIndex = 0;
	int size = 0;

	ifstream indata;
	indata.open("Trial.txt");
	string temp;
	string t;
	int j = 0;
	stack <string> OpenAngleStack;

	while (LineIndex < XML_Fixed.size())
	{
		temp = XML_Fixed[(LineIndex)];
		LineIndex++;

		if ((temp == "") || (((temp[1] == '?') || (temp[1] == '!')) && temp[0] == '<') || ((temp.find("<") == -1) && (temp.find(">") != -1)) || ((temp.find(">") == -1) && (temp.find("<") != -1)))
		{
			indent(OutputSpaces, size, j);
			continue;
		}

		start = temp.find("<") + 1;
		end = temp.find(">");
		if (temp[start] == '/')
		{
			t = temp.substr(start, end - start);
			OpenAngleStack.pop();
			j = j - 4;

		}

		else
		{
			anotherend = temp.find(" ");
			if (anotherend > start && anotherend < end)
			{
				t = temp.substr(start, anotherend - start);
			}
			else
			{
				t = temp.substr(start, end - start);
			}
			if (t == "frame")
			{
				indent(OutputSpaces, size, j);
				continue;
			}
			OpenAngleStack.push(t);
			j = j + 4;
			temp = temp.substr(end + 1);

			if (temp != "") {										// check if the closing angle is in the same string if so parse it

				start = temp.find("<") + 1;
				end = temp.find(">");
				t = temp.substr(start + 1, end - (start + 1));
				OpenAngleStack.pop();
				j = j - 4;

			}
			else
			{
				indent(OutputSpaces, size, j - 4);
				flag = true;
			}
		}
		if (flag == false)
		{
			indent(OutputSpaces, size, j);
		}
		else
		{
			flag = false;
		}

	}
}

void xml_json(vector<string>&xml, vector<string>&json, vector<string>&newspaces, vector<string>&tagnames, int spacesize)
{
	int j = 4;
	string previous;
	string temp;
	string t;
	int repeated = 0;
	bool flag = false;
	stack <string> st;
	int start, end, anotherend;
	int index = 1;


	json[0] = "{";
	for (int i = 0; i < xml.size(); i++)
	{
		temp = xml[i];
		if ((temp == "") || (((temp[1] == '?') || (temp[1] == '!')) && temp[0] == '<') || ((temp.find("<") == -1) && (temp.find(">") != -1)) || ((temp.find(">") == -1) && (temp.find("<") != -1)))
		{
			continue;
		}
		start = temp.find("<") + 1;
		end = temp.find(">");
		if (temp[start] == '/')
		{
			t = temp.substr(start+1, end - (start+1));
			if (repeated==0)
			{
				json[index] = "]";
			}
			else
			{
				json[index] = "}";
			}
			st.pop();
			j = j - 4;

		}

		else
		{
			anotherend = temp.find(" ");
			if (anotherend > start && anotherend < end)
			{
				t = temp.substr(start, anotherend - start);
			}
			else
			{
				t = temp.substr(start, end - start);
			}
			if (t == "frame")
			{
				continue;
			}
			st.push(t);
			j = j + 4;
			if (i!=tagnames.size() && (tagnames[i]==tagnames[i+1]))
			{
				json[index] = "'" + t + "'" + ":" + "[";
			}
			else
			{
				json[index] = "'" + t + "'" + ":" + "{";
			}
			temp = temp.substr(end + 1);

			if (temp != "") {										// check if the closing angle is in the same string if so parse it

				start = temp.find("<") + 1;
				end = temp.find(">");
				t = temp.substr(start + 1, end - (start + 1));
				st.pop();
				j = j - 4;

			}
			else
			{
				previous = t;
				indent(newspaces, spacesize, j - 4);
				flag = true;
			}
		}
		if (flag == false)
		{
			indent(newspaces, spacesize, j);
		}
		else
		{
			flag = false;
		}
		index++;
	}
	json[index] = "}";
}

int main()
{
	int NumOfLines = 0;
	vector<string> Tags(2000);
	vector<string> XML_original(2000);
	vector<string> XML_FixedErrors(2000);
	vector<string> Spaces(2000);
	vector<string> json(2000);


	ifstream in("Trial.txt");				// READ FROM Trial.txt file

	XML_Parser(Tags, NumOfLines, XML_original, XML_FixedErrors);		// FIND ERRORS AND FIX THEM

	XML_indent(Spaces, XML_FixedErrors);									// TO GET INDENTION LEVELS TO PRINT OUT XML LINES CORRECTLY


	cout << "-----------------------------      BEFORE FIX  WITH INDENTION     -----------------------------" << " \n \n ";
	Print_XML(Spaces, XML_original, NumOfLines);


	cout << "-----------------------------      AFTER FIX  WITH INDENTION     -----------------------------" << " \n \n ";
	Print_XML(Spaces, XML_FixedErrors, NumOfLines);

	cout << "------------------------------      XML TO JSON    ------------------------------------" << " \n \n ";


	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
