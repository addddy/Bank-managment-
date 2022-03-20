#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;
class bank
{
public:
    char name[100];
    int acno;
    char type;
    int deposit;
    void createac()
    {
        cout << "\nEnter The account No. :";
        cin >> acno;
        cout << "\n\nEnter The Name of The account Holder : ";
        cin.ignore();
        cin.getline(name, 100);
        cout << "\nEnter Type of The account (C/S) : ";
        cin >> type;
        cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
        cin >> deposit;
        cout << "\n\n\nAccount Created..";
    }
    void show_account()
    {
        cout << "\nAccount No. : " << acno;
        cout << "\nAccount Holder Name : ";
        cout << name;
        cout << "\nType of Account : " << type;
        cout << "\nBalance amount : " << deposit;
    }
    void modify()
    {
        cout<<"\nAccount No. : ";cin>>acno;
	 cout<<"\nModify Account Holder Name : ";
     cin.ignore();
	 cin.getline(name,100);
	 cout<<"\nModify Type of Account : ";
	 cin>>type;
	 cout<<"\nModify Balance amount : ";
	 cin>>deposit;
    }
    void dep(int x)
    {
        deposit += x;
    }
    int retacno()
    {
        return acno;
    }
    void draw(int x)
    {
        deposit -= x;
    }
    void report()
    {
        cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(10) << deposit << endl;
    }
    int retdeposit()
    {
        return deposit;
    }
    char rettype()
    {
        return type;
    }
};
void writeac();
void readfile(int);
void deposit_withdraw(int, int);
void displayall();
void deleteac(int);
void modifyac(int);

int main()
{
    int ch, num;

    cout << "\n\n\n\t****************" << endl;
    cout << "\n\n\n\t          BANK MANAGEMENT SYSTEM" << endl;
    cout << "\n\n\n\t****************" << endl;
    cout<<"MADE BY : - ADITYA SAINI "<<endl;
    cin.get();
    system("cls");
    while (ch != 8)
    {
        cout << "\n\n\tMAIN MENU";
        cout << "\n\n\t01. create account";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8) ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case 1:
            writeac();
            break;
        case 2:
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            deposit_withdraw(num, 1);
            break;
        case 3:
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            deposit_withdraw(num, 2);
            break;
        case 4:
            cout<<"\n\n\tEnter The account No. : "; cin>>num;
			readfile(num);
            break;
        case 5:
            displayall();
            break;
        case 6:
            cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deleteac(num);
            break;
        case 7:
            cout<<"\n\n\tEnter The account No. : "; cin>>num;
            modifyac(num);
            break;
        case 8:
            cout <<"\n\n\tThanks for using bank managemnt system"<< endl;
            break;
        default: cout<<"YOu have entered out of range plz enter the number [1-8] .";
        }
        cout << endl;
        cin.ignore();
        cin.get();
    }

    return 0;
}
void writeac()
{
    bank ac;
    fstream outfile;
    outfile.open("bankdata.dat",ios::app|ios::out);
    ac.createac();
    outfile.write((char*)&ac, sizeof(ac));
    outfile.close();
}
void readfile(int s)
{
    fstream infile;
    bank ac;
    
    infile.seekg(0);
    infile.open("bankdata.dat", ios::in | ios::out);
    if(!infile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
    cout<<"\nBALANCE DETAILS\n";
    while (infile.read((char*)&ac, sizeof(ac)))
    {
        if (ac.acno == s )
        {
           
            ac.show_account();
            //flag==1;
        }
    }
    
    /*infile.close();
    if(flag==0)
    {
        cout<<"\n\nAccount number does not exist";
    }*/
}
void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    bank ac;
    fstream File;
    File.seekg(0);
    File.open("bankdata.dat", ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read((char *)&ac, sizeof(ac));
        if (ac.retacno() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\tTO DEPOSITE AMOUNT ";
                cout << "\n\nEnter The amount to be deposited : ";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2)
            {
                cout << "\n\n\tTO WITHDRAW AMOUNT ";
                cout << "\n\nEnter The amount to be withdraw : ";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
                    cout << "Insufficience balance";
                else
                    ac.draw(amt);
            }
            File.seekp(-sizeof(ac), ios::cur);
            File.write((char *)&ac, sizeof(ac));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}
void displayall()
{
    bank ac;
    fstream infile;
    infile.open("bankdata.dat",ios::in);
    if(!infile)
    {
        cout<<"File could not be open !! Press any Key...";
    }
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
    while(infile.read((char*)&ac,sizeof(ac)))
    {
        ac.report();
    }
    infile.close();
}
void deleteac(int x)
{
    bank ac;
	fstream inFile,outFile;
	inFile.open("bankdata.dat",ios::in);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
	}
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char*)&ac, sizeof(ac)))
	{
		if(ac.retacno()!=x)
		{
			outFile.write((char*)&ac, sizeof(ac));
		}
	}
	inFile.close();
	outFile.close();
	remove("bankdata.dat");
	rename("Temp.dat","bankdata.dat");
	cout<<"\n\n\tRecord Deleted ..";
}
void modifyac(int x)
{
    bool found=false;
	bank ac;
	fstream File;
	File.open("bankdata.dat",ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
	}
	while(!File.eof() && found==false)
	{
		File.read((char*)&ac, sizeof(ac));
		if(ac.retacno()==x)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			File.seekp(-sizeof(ac),ios::cur);
			File.write((char*)&ac, sizeof(ac));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}