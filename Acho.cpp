#include<iostream>
#include<string.h>
#include "SplayTree.h"

using namespace std;
struct account{
    string website;
    string username;
    int* password;
};
class AccountHolder{
    private:
        SplayTree<account> holder;
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
};
int main()
{
    
}