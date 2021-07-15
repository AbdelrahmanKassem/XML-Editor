// xml_file.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>

using namespace std;

void indent(vector<string> &s, int &index, int in, string p)
{
	for (int i = 0; i < in; i++)
	{
		s[index] = s[index] + " ";
	}
	s[index] = s[index] + p;
	index++;
}

void XML_indent(vector<string> &tags, int &size, vector<string> &s, int *i)
{
	char start;
	char end;
	char anotherend;
	bool flag = false;

	ifstream indata;
	indata.open("Trial.txt");
	string temp;
	string t;
	//int i = 0;
	int j = 0;
	stack <string> st;

	do
	{
		getline(indata, temp);
		s[(*i)] = temp;
		//haserror[(*i)] = false;
		(*i)++;
		//indata.ignore();
		//cout << temp << endl;

		if ((temp == "") || (((temp[1] == '?') || (temp[1] == '!')) && temp[0] == '<') || ((temp.find("<")==-1)&&(temp.find(">")!=-1)) || ((temp.find(">")==-1)&&(temp.find("<") != -1)))
		{
			indent(tags, size, j, temp);
			continue;
		}

		start = temp.find("<") + 1;
		end = temp.find(">");
		if (temp[start] == '/')
		{
			t = temp.substr(start, end - start);
			st.pop();
			j = j - 4;
			/*if (t != st.top())
			{
				error[(*e)++] = *i;
				haserror[*i - 1] = true;
				//cout << "    <----error";
			}
			else
			{
				st.pop();
			}*/

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
			if (end !=-1 && temp[end - 1] == '/')
				continue;
			st.push(t);
			j = j + 4;
			temp = temp.substr(end + 1);

			if (temp != "") {										// check if the closing angle is in the same string if so parse it
				start = temp.find("<") + 1;
				end = temp.find(">");
				t = temp.substr(start + 1, end - (start + 1));
				st.pop();
				j = j - 4;
				/*if (t != st.top())
				{
					error[(*e)++] = *i;
					haserror[*i - 1] = true;
					//cout << "    <----error";
				}
				else
				{
					st.pop();
				}*/
			}
			else
			{
				indent(tags, size, j - 4, s[(*i) - 1]);
				flag = true;
			}
		}
		if (flag == false)
		{
			indent(tags, size, j, s[(*i) - 1]);
		}
		else
		{
			flag = false;
		}

	} while (!indata.eof());		// while the file isn't empty keep taking inputs

}

int main()
{
	//vector<string> Tags(2000);
	int size = 0;
	vector <string> s(2000);
	vector <int> error(2000);
	vector <bool> haserror(2000);
	vector <string> output(2000);
	int e = 0;
	int index = 0;

	ifstream in("Trial.txt");				// READ FROM Trial.txt file


	XML_indent(output, size, s, &index);

	for (int i = 0; i < size; i++)
	{
		cout << output[i] << endl;
	}

	//Print_Tags(Tags,size);

	//XML_ErrorChecker(Tags, size);


	//Print_Tags(Tags, size);
	//cout << s[0];
	/*for (int i = 0; i < e; i++)
	{
		cout << error[i] << endl;
	}*/
	/*for (int i = 0; i < index; i++)
	{
		if (haserror[i] == true)
		{
			cout << s[i] << "    <----error here" << endl;
		}
		else
		{
			cout << s[i] << endl;
		}
	}*/

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
