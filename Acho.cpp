#include<iostream>
#include<string.h>
#include<fstream>
#include "SplayTree.h"

using namespace std;

class AccountHolder{
    private:
        struct account{
            string website;
            string username;
            string password;
        };
        SplayTree<account> holder;
        void readFile(const char* fileName);
        void writeFile(const char* fileName);
    public:
        bool add(account newAcc)
        {
            holder.add(newAcc);
            return true;
        }
        bool remove(account reAcc)
        {
            int a = holder.key(reAcc);
            if(a >= 0)
            {
            holder.remove(a);
            return true;
            }
            return false;
        }
        void display()
        {

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
    AccountHolder holder;
    if(argc == 2)
    {
        if(argv[1] == "dis")
        {
            
        }
    }
}