#include "XML_Minify.h"

void XML_Minify(const vector<string> &XML_fixed, int size)
{
    fstream newfile;
    newfile.open("xml_minify.xml",ios::out);

    if(newfile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            if ((XML_fixed[i]) == " " || (XML_fixed[i] == "") )   continue;			// if empty string skip

            newfile << XML_fixed[i] << "\n";
        }
    }

}
