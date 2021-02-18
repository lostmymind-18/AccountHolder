#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
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
        void rEmove(string website, string username)
        {
            vector<account*> vector;
            try{
                search(vector, website, username);
                int key = holder.findKey(*vector[0]);
                holder.remove(key);
                cout<<"Removed"<<endl;
            }
            catch(...){cerr<<"Not found";};

        }
        void search(vector<account*>& vector, string website = "*", string username = "*")
        {
            if(website != "*" && username == "*")
            {
                account* a;
                for(int i = 1; i <= holder.size(); i++)
                {
                    a = holder.search(i);
                    if(a->website == website)
                        vector.push_back(a);
                }
                if(vector.size() == 0) throw"not found";
            }
            if(website == "*" && username != "*")
            {
                account* a;
                for(int i = 1; i <= holder.size(); i++)
                {
                    a = holder.search(i);
                    if(a->username == username)
                        vector.push_back(a);
                }
                if(vector.size() == 0) throw"not found";
            }
            if(website != "*" && username != "*")
            {
                account* a;
                for(int i = 1; i <= holder.size(); i++)
                {
                    a = holder.search(i);
                    if(a->website == website && a->username == username)
                        vector.push_back(a);
                }
                if(vector.size() == 0) throw"not found";
            }
        }
        void display(account* acc)
        {
            cout<<"website: "<<acc->website<<endl;
            cout<<"username: "<<acc->username<<endl;
            cout<<"password: "<<acc->username<<endl; 
            cout<<"------------------------------------"<<endl;
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
        }
        AccountHolder()
        {
            readFile("D:\\Projects\\AccountHolder\\data.txt");
        }
        ~AccountHolder()
        {
            writeFile("D:\\Projects\\AccountHolder\\data.txt");
        }
};
void AccountHolder::readFile(const char* fileName)
{
    ifstream in(fileName);
    while(!in.eof())
    {
        account addAccount;
        in>>addAccount.website;
        if(addAccount.website == "") break;
        in>>addAccount.username;
        in>>addAccount.password;
        add(addAccount);
    }
    in.close();
}
void AccountHolder::writeFile(const char* fileName)
{
    remove(fileName);
    ofstream outFile(fileName);
    account* acc;
    for(int i = 1; i <= holder.size(); i++)
    {
        acc = holder.search(i);
        outFile<<acc->website<<endl; outFile<<acc->username<<endl; outFile<<acc->password<<endl;
    }
}
int main(int argc, char* argv[])
{
    if(argc == 1) cout<<"Hello Dung, have a good time =))"<<endl;
    AccountHolder holder;
    //Display all accounts
    if((string)argv[1] == "ls")
    {
        holder.displayAll();
    }
    if((string)argv[1] == "add")
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
    if((string)argv[1] == "search")
    {
        string website;
        string username;
        vector<account*> vector;
        while(1)
        {
        cout<<"Enter website: ";
        cin>>website;
        cout<<"Enter username: ";
        cin>>username;
        if(website!="" && username !="") break;
        else cout<<"Please fill in the blank!"<<endl;
        }
        holder.search(vector, website);
        for(int i = 0; i < (int)vector.size(); i ++)
            holder.display(vector[i]);
    }
    if((string)argv[1] == "remove")
    {
        cout<<"Enter website: "<<endl;
        string website; cin>>website;
        cout<<"Enter username: "<<endl;
        string account; cin>>account;
        holder.rEmove(website, account);
    }
    if((string)argv[1] == "change")
    {
        string website, username;
        cout<<"Enter website: "; cin>>website;
        cout<<"Enter username: "; cin>>username;
        vector<account*> vector;
        try{
            holder.search(vector, website, username); 
            string newpass;
            cout<<"Enter new pass: "; cin>>newpass;
            vector[0]->password = newpass;
            }
        catch(...){cout<<"Not found";}

    }

}