#include <iostream>
#include <string>
#include <fstream>
#include "member.h"
#include "member.h"

using namespace std;

void file_check(string file_name){
    try{
        fstream fileptr;
        fileptr.open(file_name);
        if(!fileptr)
            throw 10;
        else if (fileptr)
            fileptr.close();
    }
    catch(int x)
    {
        ofstream newfile(file_name);
        newfile.close();
    }

}


int row_counter(string file_name){
    fstream in (file_name); //openning the file
        char data;
        int rows=1;                      //count the rows so we will know how many rows exist to allocat enough memory for array of object
        while(!in.eof())
        {
            in.get(data);
            if(data=='\n')
            rows++;
        }

        // cout<<'\n'<<rows<<endl;
        in.close();
        return rows;
}

void read_member(member* Member,int rows){
        fstream in;
        in.open("Data.txt");
        string buffer;
        for(int x=0;x<rows;x++)
        {
            getline(in,buffer,' ');
            Member[x].set_username(buffer);

            getline(in,buffer,' ');
            Member[x].set_password(buffer);

            getline(in,buffer,'\n');
            Member[x].set_nickname(buffer);
        }
        in.close();

}

void read_log(log* logs,int rows){
        fstream in;
        in.open("message_logs.txt");

        string buffer;
        for(int x=0;x<rows;x++)
        {
            getline(in,buffer,' ');
            logs[x].set_time(buffer);

            getline(in,buffer,' ');
            logs[x].set_sender(buffer);

            getline(in,buffer,' ');
            logs[x].set_target(buffer);

            getline(in,buffer,'\n');
            logs[x].set_message(buffer);
        }
        in.close();

}
void addaccount(member* Member,const string filename,int rows){
    fstream fileptr;
    fileptr.open(filename,ios::app);
    string user;
    string pass;
    string nickname;
    bool ok;


    do{
    ok = true;
    cout<<endl<<"Enter a username:";
    cin>>user;

    for(int x=0;x<rows;x++)
    {
        if(user==Member[x].get_username())
        {
            ok=false;
            cout<<endl<<"!!!!Error This Username EXIST !!!!";
        }
    }
    }while(!ok);


    cout <<endl<<"Enter a password:";
    cin >>pass;

    cout<< endl<< "Enter a nickname:";
    cin>> nickname;
    if(ok)
        fileptr<<user<<' '<<pass<<' '<<nickname<<'\n';




}
void admin(member* Member){
    const string logfile="message_logs.txt";
    int rows=row_counter(logfile);
    log* logs= new log[rows];
    read_log(logs,rows);
    system("cls");
    cout<<endl<<"----Logs----";
    for(int x=0;x<rows;x++){
                cout<<endl<<logs[x].get_time()<<' '<<
                            logs[x].get_sender()<<' '<<
                            logs[x].get_target()<<' '<<
                            logs[x].get_message()<<endl;
            }
    cout<<endl<<"----Accounts----";
    string datafile= "Data.txt";
    rows = row_counter(datafile);
    for(int x=0;x<rows;x++){
        cout<<endl<<Member[x].get_username()<<' '<<
        Member[x].get_password()<<' '<<
        Member[x].get_nickname()<<'\n';
    }
    delete[] logs;
}

int login(member* Member,int rows){
        bool access;
        int member_id= -1;
        string input_user;
        string input_pass;
        int choise=0;
        do
        {
            access=false;
            system("cls");
            cout<<endl<<"\t\t\tPlease enter your information";
            cout<<endl<<"------Username:";
            cin >>input_user;
            cout<<endl<<"------Password:";
            cin >>input_pass;
            if(input_user=="admin"&& input_pass =="admin"){
                admin(Member);
            access=true;
            system("pause");
            }


            for(int x=0;x<rows;x++){
                if(Member[x].u_p_is_match(input_user,input_pass)){
                        access = true;
                        member_id = x;
                        return member_id;
                }
            }

            if(access== false){
                cout <<endl <<'\t'<< "Error input"<<endl;
                cout<<"1.Try again"<<endl<<"2.Create new account"<<endl<<"0.Exit program"<<endl;
                cin>>choise;

                switch(choise){
            case 1:
                access=false;
                break;
            case 2:
                addaccount(Member,"Data.txt",rows);
                break;
            case 0:
                return -1;
                break;
                }
            }

        } while (access==false);
        return member_id;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
string currentDateTime(){
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

int sendmessage(string username,member* Member)
{
    string memberfile= "Data.txt";
    int rows =row_counter(memberfile);
    if(rows==0){
        cout <<endl <<"No users exist";
        return 0;
    }
    else
    {
        cout<<endl<<"\t\t List of all available users choose one to send message to !";
        string buffer;
        for(int x=0;x<rows;x++)
        {
            buffer = Member[x].get_username();
            cout<<endl<<x<<"."<<buffer;
        }


    }
    int choise;
    cout<<endl;
    cin>>choise;

    if(username==Member[choise].get_username())
    {
        cout<<endl<<"Can't send message to yourself !\t Please try again";
        sendmessage(username,Member);
        return 0;
    }
    else if(choise>=0 && choise<rows)
    {
        cout<<endl<<"Write your message:";
        string message;
        cin.ignore();
        getline(cin,message);

        fstream file;
        file.open("message_logs.txt",ios::app);
        string date= currentDateTime();
        string target =Member[choise].get_username();
        file << date <<' '<<username<<' '<<target<<' '<<message<<'\n';
        file.close();
        cout<<endl<<"Message sent to "<<target <<" Successfully";

    }
    else
    {
        cout<<endl<<"error input"<<endl;
        return 0;
    }
}

int Dashboard(member* Member,int member_id){ //id is the index of array where the username and password was matched
    const string logfile ="message_logs.txt";

    system("cls");
    int rows=row_counter(logfile);
    log* logs= new log[rows];
    read_log(logs,rows);
    int choise;
    int log_id;
    int message_counter;
        do
        {
            message_counter=0;
            cout<<endl<<"-------- Welcome "<<Member[member_id].get_nickname()<<" --------";
            string buffer1;
            string buffer2;
            for(int x=0;x<rows;x++){
                    buffer1= logs[x].get_target();
                    buffer2= Member[member_id].get_username();
                    if(buffer1 == buffer2)
                    {
                        message_counter++;
                        if(message_counter==1)
                            cout<<endl<<endl<<endl<<"***Inbox***";
                        cout<<endl<<"---"<<logs[x].get_time() << "\t"<<logs[x].get_sender() << ":"<< logs[x].get_message()<<endl;
                    }
            }
            cout <<endl<<"\t\t\tTotal of "<<message_counter <<" messages founded !";
            choise=0;
            cout<<endl<<"1.Send message to a user \n0.exit"<<endl;
            cin >> choise;
            system("cls");
            if(choise==1){
                    if(sendmessage(Member[member_id].get_username(),Member)==0)
                        return 0;
            }
                else
                return 0;
        } while (choise!=0);
        delete[] logs;
}

int menu(){
    int choise=0;
    const string datafile="Data.txt";


    do
    {

    int rows = row_counter(datafile);


        member* Member = new member[rows];
        read_member(Member,rows);


         //for(int x=0;x<rows;x++){
         //Member[x].print_all_members_();
         //}

        cout<<endl<<"------------- Welcome to messenger Application -------------"<<'\n';
        cout<<"1.login to your account"<<'\n'<<"2.Add new account"<<'\n'<<"0.To exit the program"<<endl;
        cin >> choise;


        switch (choise){
        case 1:
            system("cls");
        int member_id;
        member_id = login(Member,rows);
        if(member_id == -1)
            return 0;
        if (Dashboard(Member,member_id)==0)
            return 0;
            break;
        case 2:
            system("cls");
            addaccount(Member,datafile,rows);
            break;
        case 0:
            break;
        default:
            cout<<endl<<"Error input!";
            break;
        }
        delete[] Member;

    } while (choise != 0);
    return 0;
}
