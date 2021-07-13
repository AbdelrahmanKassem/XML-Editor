/*
 * XML_Parser.h
 *
 *  Created on: Jul 13, 2021
 *      Author: arahm
 */

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
void Text_to_Vector(string file_data,vector<string> &XML_Vector, unsigned int &XML_Size);
void XML_Parser(vector<string> &tags, unsigned int &lines, vector<string> &XML_Original, vector<string> &XML_Fix , vector<string> &XML_ReadFile , unsigned int &XML_Size);

void Output_File(const vector<string> &Spaces, const vector<string> &XML_string, int size);
void Print_XML(const vector<string> &Spaces, const vector<string> &XML_string, int size);

#endif /* XML_PARSER_H_ */
