#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "Functions.h"
using namespace std;

int main(){
    string file_member = "Data.txt";
    string file_log = "message_logs.txt";

    file_check(file_member);// if the file does not exist at all it will create a new file as database
    file_check(file_log);
    menu();
    return 0;
}
