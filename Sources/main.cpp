#include "mainwindow.h"

#include <QApplication>


using namespace std;

unsigned int NumOfLines = 0;
unsigned int sizeOfXML =0;
unsigned int sizeOfJSON =0;

vector<string> XML_ReadFile;
vector<string> XML_original;
vector<string> XML_FixedErrors;
vector<string> Spaces;
vector<string> JSON;


int main(int argc, char *argv[])
{
    /*Application*/
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

/*Functions Definitions*/

void Output_File( const vector<string> &XML_string, int size)	  // Passed constant by reference to save memory and time
{
    fstream newfile;
    newfile.open("TEXTOUTPUT.xml",ios::out);
    if(newfile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            newfile << XML_string[i] << "\n";
        }
    }
}


void Output_File(const vector<string> &Spaces, const vector<string> &XML_string, int size,string caller)	  // Passed constant by reference to save memory and time
{
    fstream newfile;
    string fname;
    if(caller == "Format")
    {
        fname = "Format.xml";
    }
    else if(caller == "Error")
    {
        fname = "ERROR.xml";
    }
    newfile.open(fname,ios::out);
    if(newfile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            newfile << Spaces[i] << XML_string[i] << "\n";
        }
    }
}

void Print_XML( const vector<string> &XML_string, int size)   // Passed constant by reference to save memory and time
{
    for (int i = 0; i < size; i++)
        cout <<  XML_string[i] << "\n";

}



void Print_XML(const vector<string> &Spaces, const vector<string> &XML_string, int size)   // Passed constant by reference to save memory and time
{
    for (int i = 0; i < size; i++)
        cout << Spaces[i] << XML_string[i] << "\n";

}
