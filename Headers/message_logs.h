#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>


using namespace std;


class log{
    string time;
    string sender_user;
    string target_user;
    string message;
public:
    void set_time(string time_input){time =time_input ;}
    void set_sender(string sender_input){   sender_user    = sender_input ;}
    void set_target(string target_input){   target_user    = target_input;}
    void set_message(string message_input){ message        = message_input;}

    string get_time(){return time;}
    string get_sender(){return sender_user;}
    string get_target(){return target_user;}
    string get_message(){return message;}
};
