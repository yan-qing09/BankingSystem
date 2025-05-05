#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

#define MAX 6

class CheckAccount;

class ServiceCharges{
    private:
        double charges;

    public:
        ServiceCharges()
        {   charges = 0;  }
        
        void plusCharges(double num)
        {   charges += num;   }
        
        void setServiceCharges(double num)
        {   charges = num;    }
        
        double getServiceCharges() const
        {   return charges; }  
};

class Account{
    protected:
        double balance;
        int no_deposit;
        int no_withdrawals;
        double a_interestrate;
        char typeacc;
        ServiceCharges servicecharge;
    
    public:
        string accno;
        Account()
        {   balance = 0.00;
            no_deposit = 0;
            no_withdrawals = 0;
            a_interestrate = 0.00; }

        void deposit(double d)
        {   balance += d;
            no_deposit++;   }

        void withdraw(double w)
        {   balance -= w;
            no_withdrawals++;   }

        void calcInt()
        {   double m_interest, m_interestrate;
            m_interestrate = (a_interestrate/1200);
            m_interest = balance * m_interestrate;
            balance += m_interest;  }

        void monthlyProc()
        {   balance -= servicecharge.getServiceCharges();
            calcInt();
            no_deposit = 0;
            no_withdrawals = 0;
            servicecharge.setServiceCharges(0); }

        void setAccno(string a)
        {   accno = a;  }
        
        void setBalance(double l)
        {   balance = l;    }

        void setInterestRate(double i)
        {   a_interestrate = i; }

        void setNo_Deposit(double b)
        {   no_deposit = b; }

        void setNo_Withdrawals(double w)
        {   no_withdrawals = w; }
        
        void setTypeacc(char t)
        {   typeacc = t;    }

        void setServiceCharges(double sc)
        {   servicecharge.setServiceCharges(sc);    }

        string getAccno() const
        {   return accno;   }

        double getBalance() const
        {   return balance; }

        double getInterestRate() const
        {   return a_interestrate; }
        
        int getNo_Deposit() const
        {   return no_deposit;  }

        int getNo_Withdrawals()const
        {   return no_withdrawals;  }

        char getTypeacc() const
        {   return typeacc; }

        double getServiceCharges() const
        {   return servicecharge.getServiceCharges();   }
};

class SavingsAccount: public Account{
    private:
        bool status;
    
    public:
        void setStatus()
        {   if (balance < 25)
                status = 0;
            else
                status = 1; }

        void withdraw(double number)
        {   setStatus();
            if(balance < 25){
                status = 0;
                cout<<"Account is inactive. No withdrawals allowed."<<endl;
            }
            else if(balance >= 25){
                Account::withdraw(number);
            }
        }

        void deposit(double number)
        {   setStatus();
            if (status == 0 && balance + number >= 25) {
                status = 1;
                cout<< "Account is now active." <<endl;
            }
            Account::deposit(number);
        }

        void monthlyProc()
        {   servicecharge.plusCharges(1.0);
            if (balance < 25){
                status = 0;
                Account::monthlyProc();
            }
        }

        Account& operator=(const SavingsAccount &a)
        {   this->balance = a.getBalance();
            this->no_deposit = a.getNo_Deposit();
            this->no_withdrawals = a.getNo_Withdrawals();
            return *this;   }
};

class CheckAccount: public Account{
    public:
        void withdraw(double _w)
        {   double tempbalance = balance - _w;
            if(tempbalance<0)
            {
                balance -= 5;
                cout<<"Insufficient balance. Your account will be deducted RM 5."<<endl;
            }
            else 
            {
                Account::withdraw(_w);
            }
        }
    
        void monthlyProc()
        { 
            servicecharge.plusCharges(0.1);
        }

        Account& operator=(CheckAccount& c)
        {   this->balance = c.getBalance();
            this->no_deposit = c.getNo_Deposit();
            this->no_withdrawals = c.getNo_Withdrawals();
            return *this;
        }
};

void cSetAll(Account customer[MAX],CheckAccount& c, int i)
{
    c.setTypeacc(customer[i].getTypeacc());
    c.setAccno(customer[i].getAccno());
    c.setBalance(customer[i].getBalance());
    c.setInterestRate(customer[i].getInterestRate());
    c.setNo_Deposit(customer[i].getNo_Deposit());
    c.setNo_Withdrawals(customer[i].getNo_Withdrawals());
    c.setServiceCharges(customer[i].getServiceCharges());
}

void sSetAll(Account customer[MAX],SavingsAccount& s, int i)
{
    s.setTypeacc(customer[i].getTypeacc());
    s.setAccno(customer[i].getAccno());
    s.setBalance(customer[i].getBalance());
    s.setInterestRate(customer[i].getInterestRate());
    s.setNo_Deposit(customer[i].getNo_Deposit());
    s.setNo_Withdrawals(customer[i].getNo_Withdrawals());
    s.setServiceCharges(customer[i].getServiceCharges());
}

void Info(Account customer[MAX], SavingsAccount& s, CheckAccount& c)
{
    int selection;
    string accno;
    double deposit, withdraw;
    cout<<"Please enter your Account Number: ";
    getline(cin,accno);
    for(int i=0;i<MAX;i++)
    {
        if(accno==customer[i].accno)
        { 
            cout << "***BANK ACCOUNT MENU***" << endl;
            cout << "1. Savings Account Deposit" << endl;
            cout << "2. Checking Account Deposit" << endl;
            cout << "3. Savings Account Withdrawal" << endl;
            cout << "4. Checking Account Withdrawal" << endl;
            cout << "5. Display Account Statistics" << endl;
            cout << "6. Exit" << endl << endl << endl;
            cout << "Your choice, please (1-6) ";
            cin >> selection;
        
            if(customer[i].getTypeacc()=='S')
            {   
                switch (selection) {
                case 1:
                    cout << "Enter amount to deposit: RM ";
                    cin >> deposit;
                    sSetAll(customer,s,i);
                    s.deposit(deposit);
                    customer[i] = s;
                    customer[i].setServiceCharges(s.getServiceCharges());
                    cout << "Your balance is RM " << fixed << setprecision(2) << customer[i].getBalance() << endl;
                    break;
           
                case 3:
                    cout << "Enter amount to withdraw: RM ";
                    cin >> withdraw;
                    sSetAll(customer,s,i);
                    s.withdraw(withdraw);
                    if (s.getNo_Withdrawals() > 4){
                    s.monthlyProc();
                    }
                    customer[i].setBalance((customer[i].getBalance() - 1));
                    customer[i] = s;
                    customer[i].setServiceCharges(s.getServiceCharges());
                    cout << "Your balance is RM " << fixed << setprecision(2) << customer[i].getBalance() << endl;
                    break;

                case 5:
                    sSetAll(customer,s,i);
                    customer[i] = s;
                    customer[i].setServiceCharges(s.getServiceCharges());
                    cout << "ACCOUNT MONTHLY STATISTICS:" << endl;
                    cout << "Ending Balance:   RM " << fixed << setprecision(2) << customer[i].getBalance()<< endl;
                    cout << "Withdrawals:   " << customer[i].getNo_Withdrawals() << " time(s) " << endl;
                    cout << "Deposits:   " << customer[i].getNo_Deposit() << " time(s) " << endl;
                    cout << "Service Charges:   RM " << customer[i].getServiceCharges() << endl;
                    break;
            
                case 6 :
                    exit(1);
                    break;

                default:
                    cout<<"This account does not exist"<<endl;
                }
            }
            else
            {
                switch (selection) {
                case 2:
                    cout << "Enter amount to deposit: RM ";
                    cin >> deposit;
                    customer[i].deposit(deposit);
                    cout << "Your balance is RM " << fixed << setprecision(2) << customer[i].getBalance() << endl;
                    break;
            
                case 4:
                    cout << "Enter amount to withdraw: RM ";
                    cin >> withdraw;
                    cSetAll(customer,c,i);
                    c.withdraw(withdraw);
                    c.monthlyProc();
                    customer[i] = c;
                    customer[i].setServiceCharges(c.getServiceCharges());
                    cout << "Your balance is RM " << fixed << setprecision(2) << customer[i].getBalance()<< endl;
                    break;
            
                case 5:
                    cSetAll(customer,c,i);
                    customer[i] = c;
                    customer[i].setServiceCharges(c.getServiceCharges());
                    cout << "ACCOUNT MONTHLY STATISTICS:" << endl;
                    cout << "Ending Balance:   RM " << fixed << setprecision(2) << customer[i].getBalance() << endl;
                    cout << "Withdrawals:   " << customer[i].getNo_Withdrawals() << " time(s) " << endl;
                    cout << "Deposits:   " << customer[i].getNo_Deposit() << " time(s) " << endl;
                    cout << "Service Charges:   RM " << customer[i].getServiceCharges() << endl;
                    break;

                case 6 :
                    exit(1);
                    break;

                default:
                    cout<<"This account does not exist"<<endl;
                }
            }
        }
    }
}

int main() 
{   
    Account customer[MAX];
    SavingsAccount s;
    CheckAccount c;
    string word;
    char alpha;
    double number;
    
    ifstream infile;
    infile.open("Customer.txt");
    
    if(!infile)
    {
        cout<<"Error!";
    }

    for(int i =0;i<MAX;i++)
    {
        infile>>alpha;
        customer[i].setTypeacc(alpha);
        infile>>word;
        customer[i].setAccno(word);
        infile>>number;
        customer[i].setBalance(number);
        infile>>number;
        customer[i].setInterestRate(number);
        infile>>number;
        customer[i].setNo_Deposit(number);
        infile>>number;
        customer[i].setNo_Withdrawals(number);
        infile>>number;
        customer[i].setServiceCharges(number); 
    }
     
    Info(customer,s,c);

    ofstream outfile;
    outfile.open("Customer.txt");
    
    for(int j=0;j<MAX;j++)
    {
        outfile<< fixed << setprecision(2) << customer[j].getTypeacc()<<" "<<customer[j].getAccno()<<" "<<customer[j].getBalance()<<" "<<customer[j].getInterestRate()<<" "
        <<customer[j].getNo_Deposit()<<" "<<customer[j].getNo_Withdrawals()<<" " << customer[j].getServiceCharges()<<" "<<endl;
    } 

    infile.close();
    outfile.close();

    return 0;  
}
