#include<iostream>
#include<string.h>
#include<fstream>
#include "SplayTree.h"

using namespace std;

struct account{
    string website;
    string username;
    string password;
    account(){}
    account(string a, string b, string c)
    {
        website = a; username = b; password = c;
    }
    bool operator==(account& compare)
    {
        if(this->website == compare.website && this->username == compare.username
            && this->password == compare.password)
            return true;
        return false;
    }
};

class AccountHolder{
    private:
        
        SplayTree<account> holder;
        void readFile(const char* fileName);
        void writeFile(const char* fileName);
    public:
        bool add(account newAcc)
        {
            try{
            holder.add(newAcc);
            }
            catch(...){
                cerr<<"Unsuccess";
            }
            return true;
        }
        /*bool remove(account reAcc)
        {
            int a = holder.key(reAcc);
            if(a >= 0)
            {
            holder.remove(a);
            return true;
            }
            return false;
        }*/
        void search()
        {

        }
        void display(account* acc)
        {
            cout<<"website: "<<acc->website<<endl;
            cout<<"username: "<<acc->username<<endl;
            cout<<"password: "<<acc->username<<endl; 
        }
        void displayAll()
        {
            account* acc;
            cout<<"All of your accounts: "<<endl;
            for(int i = 1; i <= holder.size(); i++)
            {
                acc = holder.search(i);
                display(acc);
            }
            delete acc;
            acc = NULL;
        }
        AccountHolder()
        {
            readFile("data.txt");
        }
        ~AccountHolder()
        {
            writeFile("data.txt");
        }
};
void AccountHolder::readFile(const char* fileName)
{
    ifstream in(fileName);
    while(!in.eof())
    {
        account addAccount;
        in>>addAccount.website;
        in>>addAccount.username;
        in>>addAccount.password;
        add(addAccount);
    }
}
void AccountHolder::writeFile(const char* fileName)
{

}
int main(int argc, char* argv[])
{
    if(argc == 1) cout<<"Hello Dung, have a good time =))"<<endl;
    AccountHolder holder;
    //Display all accounts
    if((string)argv[1] == "-dis")
    {
        holder.displayAll();
    }
    if((string)argv[1] == "-add")
    {
        string a, b, c;
        cout<<"Enter website: ";
        cin>>a;
        cout<<"Enter username: "; cin>>b;
        cout<<"Enter password: "; cin>>c;
        account newAccount(a, b, c);
        if(holder.add(newAccount))
        {
            cout<<"Added!"<<endl;
        }
    }
    if((string)argv[1] == "-search")
    {
        holder.search();
    }
    


}