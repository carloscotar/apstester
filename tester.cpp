#include <iostream>
#include <string>
#include <sstream>


#ifdef _WIN32
    const bool win = true;
    #include <windows.h>
    #define UTF SetConsoleOutputCP(CP_UTF8)
    #define ELSE false
#else 
    const bool win = false;
    #define UTF ""
    #define ELSE ""
#endif
using namespace std;

int main(int argv, char *argc[]) {

    win ? UTF : ELSE;
    int stTestov;
    cout << "Vnesi stevilo testov: ";
    cin >> stTestov;

    string program = argc[1];
    string test = argc[2];
    string compare = win ? "fc " : "diff -w -q ";
    string compareEnd = win ? " > nul" : "> /dev/null 2>&1";
    string slash = win ? "\\" : "/";

    for (int i = 1; i <= stTestov; i++)
    {
        ostringstream s;
        s << test<<slash<<"test" << i << ".in";
        string inputFile = s.str();
        s.str("");
        s << "output" << i << ".txt";
        string rezFilename = s.str();
        s.str("");
        s << program << " < " << inputFile << " > " << rezFilename;
        string ukaz = s.str();
        s.str("");
        int run = system(ukaz.c_str());
        if (run != 0)
        {
            cout << "neki ne dela" << endl;
            break;
        }
        s << test <<slash<< "test" << i << ".out";
        string expectedResult = s.str();
        s.str("");
        s << compare << expectedResult << " " << rezFilename << compareEnd;
        string diffUkaz = s.str();
        s.str("");
        int diffRun = system(diffUkaz.c_str());
        if (diffRun == 0)
        {
            cout << "test " << i << ": "<< "\033[32m" << "\u2713" << "\033[0m"<<endl;
        } else if(win ? diffRun == 1 : diffRun == 256) {
            cout << "test " << i << ": " << "\033[31m"<< "\u2717"<<"\033[0m" <<endl;
        } else {
            cout << "program ne dela" << endl;
        }
    }
    return 0;
}