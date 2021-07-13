#include "XML_JSON.h"
using namespace std;

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