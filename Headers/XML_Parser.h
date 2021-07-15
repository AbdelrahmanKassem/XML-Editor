#ifndef XML_PARSER_H_
#define XML_PARSER_H_

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

string read_file(void);
void XML_Parser(string file_data,vector<string> &XML_Vector, unsigned int &XML_Size);
void XML_FixErrors( unsigned int &lines, vector<string> &XML_Original, vector<string> &XML_Fix , vector<string> &XML_ReadFile , unsigned int &XML_Size);

#endif /* XML_PARSER_H_ */
