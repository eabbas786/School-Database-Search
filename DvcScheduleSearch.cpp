//
//
//  SchoolScheduleSearch
//
//  Created by Elsa Abbas
//  This Program searches through DVC schedule text and displays information about a course.

//C++ libraries
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <string>
using namespace std;

//C libraries
#include <cstring>

int main(int argc, const char * argv[])
{

    
    //variable defintion
    map<string, set<int> > allClass;
    char* token; //to allow parsing file
    char buf[100];  //to store input from file for parsing
    const char* const tab = "\t";
    string course;

    //open input file
    ifstream fin;
    fin.open("dvc-schedule.txt");
    //check if file opened
    if (!fin.good())
        cout << "I/O error. Can't find file!\n";
    
    //read the input file
    while (fin.good())
    {
        //read the line
        string line; //to hold input from file
        getline(fin, line);
        strcpy(buf, line.c_str()); //copy line to buff
        if (buf[0] == 0) continue; //skip blank lines
        //parse line
        const string term(token = strtok(buf, tab));
        const string section((token = strtok(0, tab)) ? token: "");
        const string course((token = strtok(0, tab)) ? token: "");
        const string instructor((token = strtok(0, tab)) ? token: "");
        const string whenWhere((token = strtok(0, tab)) ? token: "");
        if (course.find('-') == string:: npos) continue; //invalid line if no dash in
                                                         //course name
        //copy subject code from course
        const string subjectCode(course.begin(), course.begin() + course.find('-'));
        string classCode = term + section; //combine term and section to make class code
        
        //convert string term into an int
        int pos = term.find(' ');
        const string season = term.substr(0, pos);
        const string year = term.substr(term.find('2'), string::npos);
        int termNum;
        if (season == "Spring")
            termNum = stoi(year) * 10 + 1;
        else if (season == "Summer")
            termNum = stoi(year) * 10 + 2;
        else
            termNum = stoi(year) * 10 + 3;
        
        //add termNum to course
        allClass[course].insert(termNum);
    }
    
   while (course != "X" && course != "x")
   {
       cout << "Enter a course name [like COMSC-210] to search for the first";
       cout << “and last semester offered [X/x to exit]:\n";
       cin >> course;
       
       if (course == "X" || course == "x") break;
       if(allClass.find(course) == allClass.end())
           cout << "Could not find " << course << endl << endl;
       else
       {
           //find first term course was offered
           set<int>::iterator it;
           it = allClass[course].begin();
           cout << course << " was first offered in ";
           if ((*it % 10) == 1) cout << "Spring " << *it / 10;
           else if ((*it % 10) == 2) cout << "Summer " << *it / 10;
           else cout << "Fall " << *it / 10;
           cout << endl;
           
           //find last term course was offered
           set<int>::reverse_iterator rit;
           rit = allClass[course].rbegin();
           cout << course << " was last offered in ";
           if ((*rit % 10) == 1) cout << "Spring " << *rit / 10;
           else if ((*rit % 10) == 2) cout << "Summer " << *rit / 10;
           else cout << "Fall " << *rit / 10;
           cout << endl << endl;
           
           
       }
       
   }
    
    return 0;
}
