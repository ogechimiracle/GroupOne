#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class ATM {
private:
    string full_name;
    int pin;
    int amt;
    int acc_num;

public:
    void get_item(void); // defining the member function of class ATM
    void put_item (void);
    int get_code(void){
        return pin;
    }

    int get_amt(void){
        return amt;
    }

    void update_amt(int num){
        amt = amt - num;

    }


};

 void ATM::get_item(void){
        cout<<"Choose ATM Pin: "; cin>>pin;
        fflush(stdin);
        cout<<"Enter Account Name: "; cin>>full_name;
        cout<<"Enter Account Number: "; cin>>acc_num;
        cout<<"Enter Amount: "; cin>> amt;
}

void ATM::put_item(void){
        cout<<setw(15)<<pin
        <<setw(15)<<full_name
        <<setw(15)<<acc_num
        <<setw(15)<<amt<< endl;
}

void create_acc(void);
void view_balance(void);
void withdraw(void);
void login(void);


ATM opr; // we cerate an instance of ATM class
fstream file;

int main()
{
    int opt;
    char lg;
    cout<<"........... GROUP ONE ATOUMATED TELLER MACHINE .......................\n";
    cout<<"______________________________________________________________________\n";

    lblLogin:
    cout<<" press any key to Login or press N to create new account: ";cin>>lg;

    if(lg=='n' || lg=='N'){
        cout<<"Provide details to enable create account..\n";
        create_acc();
        goto lblLogin;

    }
    else{
        login();

    }

        while(1){
              system("cls");
            cout<<"********** You Are Now Logged in to Our Machine *********************\n";
            cout<<"***** Welcome User *********\n";
            cout<<"**********************************************************************\n";
            cout<<"1. WithDraw"<<endl;
            cout<<"2. View Balance"<<endl;
            cout<<"3. Exit"<<endl;
            cout<<"**********************************************************************\n";

            cout<<"Enter menu option: ";cin>>opt;
            switch(opt){

                case 1:{
                     withdraw();
                    cout<<"Press any key to return to main menu......";
                    getch();
                    break;
                }

                case 2:{
                    view_balance();
                    cout<<"incorrect Menu Option, press any key to show Main Menu.....";
                    getch();
                    break;
                }
                case 3: {
                    exit(0);
                }
                default:{
                cout<<"incorrect Menu Option, press any key to show Main Menu.....";
                getch();
                break;
                }

            }
        }


    return 0;
}

 void create_acc(){
    char ch = 'y';
    file.open("account.txt",ios::app | ios::binary);
    while(ch=='y' || ch=='Y'){
        opr.get_item();
        //write object into a file
        file.write((char*)&opr, sizeof(opr));
        cout<<"Press n to login now....(y/n)?";
        cin>>ch;
    }
    file.close();
}

void login(void){
int no, flag = 0;
    file.open("account.txt", ios::in | ios::binary);
    if(! file){
       cout<<"Opps! File Record do not exist";
       exit(0);
    }
    else{
        cout<<"Enter Pin: ";
        cin>> no;
        // now reading from a file into object
        file.read((char*)&opr, sizeof(opr));
        while(!file.eof()){
            if(no == opr.get_code()){
                flag =1;

                break;
            }
            file.read((char*)&opr, sizeof(opr));
        }
        if(flag==0){
            cout<<"Incorrect Pin.....\n";
        }
    }
    file.close();
}

void view_balance(void){
    int no, flag = 0;
    file.open("account.txt", ios::in | ios::binary);
    if(! file){
       cout<<"Opps! file not found";
       exit(0);
    }
    else{
        cout<<"Enter pin: ";
        cin>> no;
        // now reading from a file into object
        file.read((char*)&opr, sizeof(opr));
        while(!file.eof()){
            if(no == opr.get_code()){
                flag =1;
                cout<<"----------------------------------------------------------------\n";
        cout<<setw(15)<<"PIN"<<setw(15)<<"ACCOUNT NAME"<<setw(15)<<"ACC_NUMBER"<<setw(15)<<"AMOUNT"<<endl;
                cout<<"----------------------------------------------------------------\n";
                opr.put_item();
                cout<<"----------------------------------------------------------------\n";
                break;
            }
            file.read((char*)&opr, sizeof(opr));
        }
        if(flag==0){
            cout<<"Account Not Found.....\n";
        }
    }
    file.close();
}

void withdraw(){
    char ch = 'y';
    int no, num;
    cout<<"Enter pin to continue: "; cin>>no;
    cout<<"Enter Amount withdraw: "; cin>>num;
    file.open("account.txt", ios::in | ios::out |ios::binary);
    if (! file){
        cout<<"Opps! acc number not found";
        exit(0);
    }
    while(file.read((char*)&opr, sizeof(opr))){
        if(opr.get_code() == no){
            while(ch =='y' || ch=='Y'){
                if(opr.get_amt()<num){
                cout<<"Opps! Insufficient Balance....\n";

                break;
            }
            else{
            opr.update_amt(num); // updating the initial value of account number
            int pos = sizeof(opr);
            file.seekp(-pos, ios::cur);
            // next is to write the object to our acc.dat file
            file.write((char*)&opr, sizeof(opr));
            cout<<"Do you want to perform another transaction....(y/n)?";
            cin>>ch;
            }

            }
        }
    }

    file.close();

}
