/*
 * XML_Pretify.h
 *
 *  Created on: Jul 13, 2021
 *      Author: arahm
 */

#ifndef XML_PRETIFY_H_
#define XML_PRETIFY_H_

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;


void indent(vector<string> &space, int &index, int NumOfSpaces);
void XML_indent(vector<string> &OutputSpaces, vector<string> &XML_Fixed , unsigned int SizeOfXML);

#endif /* XML_PRETIFY_H_ */
