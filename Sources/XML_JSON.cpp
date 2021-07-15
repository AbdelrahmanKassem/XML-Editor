#include "XML_JSON.h"
using namespace std;


string AdjustSpaces(int NumOfSpaces)
{
	string Numspace;
	for (int i = 0; i < NumOfSpaces; i++)
	{
		Numspace += " ";
	}

	return Numspace;
}



void xml_json(vector<string>&xml, vector<string>&json, unsigned int &size , unsigned int &index )
{
	string previous;
	string temp;
	string t;
	string text;
	bool empty = false;

	stack <int> WordLength;
	stack <string> st;

	int start, end, anotherend;
	index = 1;

	json[0] = "{";

	for (int i = 0; i < size; i++)
	{
		temp = xml[i];

		if ((temp == "") || (((temp[1] == '?') || (temp[1] == '!')) && temp[0] == '<') || ((temp.find("<") == -1) && (temp.find(">") != -1)) || ((temp.find(">") == -1) && (temp.find("<") != -1)))
		{
			continue;
		}


		start = temp.find("<") + 1;
		end = temp.find(">");
		if (start == 0 && end == -1)
		{
			if (empty == true)
				json[index] = AdjustSpaces(WordLength.top()) + temp;

			else
				continue;

		}
		else if (temp[start] == '/')
		{
			t = temp.substr(start + 1, end - (start + 1));
			previous = t;

			json[index] = AdjustSpaces(WordLength.top()) + "}";
			st.pop();
			WordLength.pop();
		}

		else
		{
			anotherend = temp.find(" ");
			if (anotherend > start && anotherend < end)
				t = temp.substr(start, anotherend - start);

			else
				t = temp.substr(start, end - start);


			st.push(t);
			empty = true;

			if (t != previous)
				json[index] = "'" + t + "'" + ":" + "{";

			else
				json[index] = AdjustSpaces(WordLength.top()-2) + ", {";


			WordLength.push(json[index].length());
		}

		index++;
	}
	json[index++] = "}";
}
