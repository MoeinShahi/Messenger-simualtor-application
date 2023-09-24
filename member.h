#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <string>
#include "message_logs.h"

using namespace std;

class member{
    string username;
    string password;
    string nickname;
    public:
    void print_all_members_(){
        cout << endl <<
        username <<' ' <<
        password <<' ' <<
        nickname <<' '<<endl;
    }
    bool u_p_is_match(string input_user,string input_pass){ //checks if the incoming username and password matches its object attributes

        if(input_user==username && input_pass == password){
        return true;
        }
        else
        return false;


    }
    void set_username(string user){username=user;}
    void set_password(string pass){password=pass;}
    void set_nickname(string nick){nickname=nick;}
    string get_nickname(){return nickname;}
    string get_username(){return username;}
    string get_password(){return password;}
};

