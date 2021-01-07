#include <iostream>
#include <string>
#include <string>
#include <getopt.h>

using namespace std;

typedef struct Cmd {
    string cpOption;
    string XjreOption;
    string _class;
} Cmd;

void printUsage()
{
    cerr<<endl;
    cerr<<"cppJVM"<<endl;
}

void startJVM()
{
    cerr<<endl;
}

int main(int argc, char *argv[])
{
    Cmd *cmd = new Cmd();
    static const struct option loptions[] = 
    {
        {"classpath", required_argument, NULL, 'C'},
        {"Xjre", required_argument, NULL, 'X'},
        {"version", no_argument, NULL, 'v'},
        {"hlep", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };
    int opt;
    while ((opt = getopt_long(argc, argv, "v:h", loptions, NULL)) > 0)
    {
        switch (opt)
        {
            case 'C':cmd->cpOption = string(optarg);break;
            case 'X':cmd->XjreOption = string(optarg);break;
            case 'v':cerr<<"version 0.0.1"<<endl;return 1;
            case 'h':printUsage();return 1;
            default: printUsage();return 1;
        }
    }
    delete cmd;
    return 1;
}
