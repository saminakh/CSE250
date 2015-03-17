// ============================================================================ 
// main.cpp
// ~~~~~~~~
// ============================================================================ 
#include <cstdlib>   // for exit(0)
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <stdexcept>

#include "UBHeap.h"
#include "error_handling.h"
#include "term_control.h"

using namespace std; // BAD PRACTICE

void prompt();
typedef void (*cmd_t)(istringstream&);
void bye(istringstream&);
void new_cmd(istringstream&);
void print_cmd(istringstream&);

void top_cmd(istringstream&);
void pop_cmd(istringstream&);
void push_cmd(istringstream&);

map<string, UBHeap> list_table; // our "symbol table"

const string usage_msg = "UBHeap";

int main() 
{
    map<string,cmd_t> cmd_map;
    cmd_map["exit"]   = &bye;
    cmd_map["bye"]    = &bye;
    cmd_map["quit"]   = &bye;
    cmd_map["new"]    = &new_cmd;
    cmd_map["print"]  = &print_cmd;

    cmd_map["top"]    = &top_cmd;
    cmd_map["pop"]    = &pop_cmd;
    cmd_map["push"]   = &push_cmd;

    cout << term_cc(YELLOW) << usage_msg << endl;

    istringstream iss;
    string cmd, line;
    while (cin) {
        prompt(); 
        getline(cin, line);
        iss.clear();
        iss.str(line);
        if (!(iss >> cmd))
            continue;

        if (cmd_map.find(cmd) != cmd_map.end()) {
            try {
                cmd_map[cmd](iss);
            } catch (runtime_error &e) {
                error_return(e.what());
            }
        } else {
            error_return("Unknown command");
        }
    }
    return 0;
}

void bye(istringstream& iss)
{
    exit(0);
}

void new_cmd(istringstream& iss)
{
    string list_name;
    char a;
    int member;
    if (!(iss >> list_name) || !(iss >> a) || a != '=') {
        throw runtime_error("Syntax: new heapName = [list of ints]");
    }
    vector<int> int_list;
    while (iss >> member)             // sloppy with error checking here
        int_list.push_back(member);

    UBHeap ubheap = UBHeap(int_list);

    list_table[list_name] = ubheap; // assignment operator called!
}

void print_cmd(istringstream& iss)
{
    string list_name, tmp;
    if (!(iss >> list_name) || (iss >> tmp))
        throw runtime_error("Syntax: print heapName");
    if (list_table.find(list_name) == list_table.end())
        throw runtime_error(string("Heapname ") + list_name + " not found");
    cout << term_cc(YELLOW) << list_table[list_name].toString() 
         << endl << term_cc();
}

void top_cmd(istringstream& iss)
{
    string name, tmp;
    if (!(iss >> name) || (iss >> tmp))
        throw runtime_error("Syntax: top [heapname]");
    if (list_table.find(name) == list_table.end())
        throw runtime_error(string("Heap ") + name + " not found");
    cout << term_cc(YELLOW) << list_table[name].top()
         << endl << term_cc();
}

void pop_cmd(istringstream& iss)
{
    string name, tmp;
    if (!(iss >> name) || (iss >> tmp))
        throw runtime_error("Syntax: pop [heapname]");
    if (list_table.find(name) == list_table.end())
        throw runtime_error(string("Heap ") + name + " not found");
    list_table[name].pop();

}

void push_cmd(istringstream& iss)
{
    int element;
    string name, tmp;
    if (!(iss >> name) || !(iss >> element) || (iss >> tmp))
        throw runtime_error("Syntax: push [someheap] [someint]");
    if (list_table.find(name) == list_table.end())
        throw runtime_error(string("Heapname ") + name + " not found");
    list_table[name].push(element);
}



void prompt() 
{
    cout << term_cc(BLUE) << "> " << term_cc() << flush;
}
