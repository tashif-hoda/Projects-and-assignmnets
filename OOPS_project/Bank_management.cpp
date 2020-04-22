//You may use and modify this code as you please. I have tried to keep it easy to understand.
#include<iostream>
#include<fstream>
#include<string>
#include<limits>
using namespace std;

class account
{
protected:
    string agent_ID;

private:

    string name;
    unsigned int acc_number;
    long long int balance;
    int acc_type;   //0=savings, 1=current
    bool verification_state; //false by default
    string out_path;
    string verifying_agent;
    ofstream file;

public:

    account()   //constructor for prompt based input
    {
        cout<<"\nenter details as prompted\n";
        while(true)
        {
            try{
                cout<<"\nenter name\t:\n";
                string dummy;
                getline(cin,dummy);
                getline(cin,name);
                cout<<"\nenter account number\t:\n";
                while(!(cin>>acc_number))
                {
                    cout << "\nInvalid Input for account number!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout<<"\nenter balance\t:\n";
                while(!(cin>>balance))
                {
                    cout << "\nInvalid Input for balance! Balance should be an integer!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout<<"\nenter account type: 0 = saving and 1 = current\t:\n";
                while(cin>>acc_type)
                {
                    if(acc_type==0 || acc_type==1)
                        break;
                    cout << "\nInvalid Input for account type! Only 0 or 1 accepted!\n";
                }
                verification_state = false;
                out_path = "";
                //This has been kept as default for now, however code maybe added to fetch this information from a separate server containing a list of agents
                agent_ID = "default"; 
                cout<<"\naccount created successfully!\n";
                break;
            }
            catch(...)
            {
                cout<<"\nUnknown error! Try again from the beginning\n";
            }
        }
    }

    void deposit(long long int amt)
    {
        if(amt>100000 && !verification_state)
            cout<<"Amount not deposited, account not verified! Deposit below Rs 1,00,000 or verify account\n";
        else
            balance+= amt;
    }

    void deposit()
    {
        cout<<"\nEnter amount to be deposited\n";
        long long int amt;
        cin>>amt;
        if(amt>100000 && !verification_state)
            cout<<"Amount not deposited, account not verified! Deposit below Rs 1,00,000 or verify account\n";
        else
            balance+= amt;
    }

    long long int withdraw(long long int amt)   //also returns the withdrawn amount
    {
        if (amt>100000 && verification_state)
        {
            cout<<"Amount can't be withdrawn, account not verified!\n";
            return 0;
        }
        else if(balance>=amt)
        {
            balance-= amt;
            cout<<"Your remaining balance is : Rs "<<balance<<"\n";
            return amt;
        }
        else
            cout<<"Not enough balance!\n";
            return 0;
        return 0;
    }

    long long int withdraw()   //also returns the withdrawn amount
    {
        cout<<"\nEnter amount to be withdrawn\n";
        long long int amt;
        cin>>amt;
        if (amt>100000 && verification_state)
        {
            cout<<"Amount can't be withdrawn, account not verified!\n";
            return 0;
        }
        else if( balance >= amt )
        {
            balance-= amt;
            cout<<"Your remaining balance is : Rs "<<balance<<"\n";
            return amt;
        }
        else
        {
            cout<<"Not enough balance!\n";
            return 0;
        }
        return 0;
    }

    long long int show_balance()            //shows and returns the balance amount into variable for processing
    {
        cout<<"Your account has Rs "<<balance<<" in it!\n";
        return balance;
    }
    void show_info()
    {
        string act="savings";
        if(acc_type)
            act = "current";

        cout<<"Account holder details as follows:\nName\t:\t"<<name<<"\nAccount Number\t:\t"<<acc_number<<"\nBalance\t:\t"<<balance<<"\n";
        cout<<"Account type\t:\t"<<act<<"\nverified\t:\t"<<verification_state<<"\n";
    }

    void verify()       //method for verifying account
    {
        cout<<"\nEnter verification agent ID :\n";
        cin>>verifying_agent;
        if(verifying_agent==agent_ID)
        {
            verification_state = true;
            cout<<"\nAccount Verified!\n";
        }
        else
            cout<<"\nAccount not verified! Try again!\n";
    }

    void save_details()
    {
        while(true)
        {
            try{
                file.open(out_path, ios::out|ios::binary|ios::app);
                //code to store file written here
                if(file.is_open())
                {
                    file<<name<<"\n"<<acc_number<<"\n"<<balance<<"\n"<<acc_type<<"\n"<<verification_state<<"\n";
                    cout<<"\nSaved successfully!\n";
                }
                else
                    throw 0;
                break;
            }

            catch(int e)
            {
                cout<<"\nenter a valid path to store the details\t:\n";
                cin>>out_path;
            }
        }
    }

    void setpath()
    {
        string path;
        cout<<"\nEnter path:\n";
        cin>>path;
        out_path = path;
        cout<<"\npath set to \""<<out_path<<"\"\n";
    }

    void close_file()
    {
        if(file.is_open())
        {
            file.close();
            cout<<"\nFile closed\n";
        }
    }

};

int main()
{

    account* o1;
    int choice;
    do
    {

        cout<<"\n\nBANK SYSTEM\n\n";
        cout<<"____________________________\n";
        cout<<"|1) To assign Initial Value|\n";
        cout<<"|__________________________|\n";
        cout<<"|2) To Deposit             |\n";
        cout<<"|__________________________|\n";
        cout<<"|3) To Withdraw            |\n";
        cout<<"|__________________________|\n";
        cout<<"|4) To Display the Balance |\n";
        cout<<"|__________________________|\n";
        cout<<"|5) To Verify Account      |\n";
        cout<<"|__________________________|\n";
        cout<<"|6) To Display All Details |\n";
        cout<<"|__________________________|\n";
        cout<<"|7) Set output path        |\n";
        cout<<"|__________________________|\n";
        cout<<"|8) Save details to file   |\n";
        cout<<"|__________________________|\n";
        cout<<"|9) Delete Account         |\n";
        cout<<"|__________________________|\n";
        cout<<"|10) EXIT                  |\n";
        cout<<"|__________________________|\n";
        cout<<"Enter your choice :";
        cin>>choice;

        switch(choice)
        {
            case 1: o1 = new account();
                    break;
            case 2: o1->deposit();
                    break;
            case 3: o1->withdraw();
                    break;
            case 4: o1->show_balance();
                    break;
            case 5: o1->verify();
                    break;
            case 6: o1->show_info();
                    break;
            case 7: o1->setpath();
                    break;
            case 8: o1->save_details();
                    o1->close_file();
                    break;
            case 9: delete o1; o1=NULL; cout<<"\nAccount Deleted!\n";
                    break;
            case 10: exit(0);
            default:cout<<"Invalid choice!!";
        }
    }while(choice!=10);

    return 0;
}