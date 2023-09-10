//            Program to enter the details of item purchased and
//                           generate the bill
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<fstream.h>
class Shop
{
	protected:
		char name[20];        // Name of product purchased
		int usp,qty;    // usp = unit selling price of the product
		static int total;  // a static variable for all the objects
	public:
		void read()
		{
			cout<<"\nName of item : ";
			cin>>name;
			cout<<"Price of each item : ";
			cin>>usp;
			cout<<"How much quantity purchased : ";
			cin>>qty;
		}
		void calculate() //calculting total bill
		{
			total = total + (usp*qty);
		}
		void display(int clm, int row)
		{                        // This function displays only the
			gotoxy(clm,row); // name of product, quantity purchased
			cout<<name;      // and individual total of each
			gotoxy(clm+17,row); // product
			cout<<qty;
			gotoxy(clm+28,row);
			cout<<usp*qty;
		}
		static void disp_total(int clm, int row)
		{                          // This function displays the
			gotoxy(clm,row);   // complete total amount to
			cout<<total;       // be paid
		}
};
int Shop :: total = 0;
char name[20],sname[20],pswd[8],timebuf[9],datebuf[9];
char oripwd[8] = "softech"; // The password user should enter during authentication
class Database : public Shop // The class Database will store the details of
{               // Name of item purchased quantity and total amount
	public:
		void store(ofstream *fout) // Argument-> pointer of obect ofstream class
		{
			*fout<<name<<"\t"<<qty<<"\t"<<qty*usp<<"\n";
		}
};
void design()  // This function alone does the designing part of the bill
{                           // to be printed
	int clm, row;
	char topleft=201, topright=187, bottomright=188, bottomleft=200;
	char horizontal=205, vertical=186;
	gotoxy(20,1);    // Following borders are printed with the help of special symbols
	cout<<topleft;    // printing top left corner of border of bill
	gotoxy(60,1);
	cout<<topright;   // printing top right corner of border of bill
	gotoxy(60,25);
	cout<<bottomright; // printing botton right corner of border of bill
	gotoxy(20,25);
	cout<<bottomleft; // printing bottom left corner of border of bill
	row = 1;
	for(clm=21; clm<60; clm++)
	{
		gotoxy(clm,row);
		cout<<horizontal; // printing upper border of the bill
		gotoxy(clm,row+5);
		cout<<"-";           // Drawing some horizontal lines
		gotoxy(clm,row+7);   // to create partition like
		cout<<"-";           // structute on the bill
		gotoxy(clm,row+22);
		cout<<"-";
		gotoxy(clm,row+24); // printing lower border of the bill
		cout<<horizontal;
	}
	clm = 20;
	for(row=2; row<25; row++)
	{
		gotoxy(clm,row);
		cout<<vertical; // Printing left border of the bill
		gotoxy(clm+40,row);
		cout<<vertical; // Printing right border of the bill
	}
	gotoxy(22,2);
	cout<<"************* BIG BAZAAR ************";
	clm=22;
	row=3;
	gotoxy(clm,row);
	cout<<"Bill No";
	gotoxy(clm,row+1);
	cout<<2526;
	clm=36;
	row=3;
	_strtime(timebuf); // Taking current time in string format
	_strdate(datebuf); // Taking todays date in string format
	gotoxy(clm,row);
	cout<<"Date";
	gotoxy(clm,row+1);
	cout<<datebuf;    // Printing the date of on which this bill is
	gotoxy(50,3);     // generated
	cout<<"Time";
	gotoxy(50,4);
	cout<<timebuf;   // Printing time of billing
	gotoxy(22,5);
	cout<<"Customer's name : "<<name<<" "<<sname;
	gotoxy(22,7);
	cout<<"Name";   // Printing "Name" as heading of a coloumn
	gotoxy(39,7);
	cout<<"Qty";    // Printing "Qty" as heading of a coloumn
	gotoxy(50,7);
	cout<<"Amt";    // Printing "Amt" as heading of a coloumn
	gotoxy(22,24);
	cout<<"Total";  // Printing "Total" at the last row of the bill
	gotoxy(47,24);
	cout<<"Rs.";
}
void main()
{
	Database items[16];
	int i=0,j,clm,row,choice;
	char another = 'y';
	char ch;
	ofstream fout;
again:
	clrscr();
	_strtime(timebuf);
	_strtime(datebuf);
	cout<<"Enter your full name -> ";
	cin>>name;
	cin>>sname;
	fout.open("customer.txt");  // A text file will be generated here
	fout<<datebuf<<"\t"<<timebuf<<"\n"<<"Customer's name : "<<name<<" "<<sname<<"\n\n";
	// Storing date, time and name of customer as heading in the text file
	cout<<"Password -> ";
	gotoxy(13,3);
	cout<<"(only 7 charecters)";
	gotoxy(13,2);
	for(j=0; j<7; j++)
	{
		ch = getch();   // Collecting each charecters in var ch
		pswd[j] = ch;   // Storing the charecter in string but in a sequence manner
		cout<<"*";      // Echoing * for each charecter entered through keyboard
	}
	pswd[j] = '\0';   // Explicitly storing the end of string charecter(\0) at the end of string
	getch();
	if(strcmp(pswd,oripwd) != 0)
	{
		cout<<"\n\n\nIncorrect Password Entered!";
	choice:
		cout<<"\nPress 1 to retry and\n      0 to exit ";
		cin>>i;
		switch(i)
		{
			case 0:
				exit(0);
			case 1:
				goto again;
			default:
				cout<<"\nInvalid option selected";
				goto choice;
		}

	}
	clrscr();
	while(1)
	{
	gotoxy(20,1);
	cout<<"Mr "<<name<<" "<<sname<<" please enter your choice";
	gotoxy(25,3);
	cout<<"1. Enter item details";        // Menu that will appear on
	gotoxy(25,4);                         // user's screen
	cout<<"2. Print details with bill";
	gotoxy(25,5);
	cout<<"3. exit";
	gotoxy(25,6);
	cout<<"Your choice... ";
	cin>>choice;
	switch(choice)
	{
		case 1:
			clrscr();
			gotoxy(1,1);
			cout<<"Enter the details of purchased products";
			gotoxy(1,2);
			cout<<"---------------------------------------\n";
			while(another == 'y')
			{
/*Reading the detais of item.*/	items[i].read();
/*Calculating total amount.*/	items[i].calculate();
				items[i].store(&fout); //Calling function "store" to store the details of an object.
/*Though its an odd loop but*/	i++;
/*i've specified a maximum*/	if(i==16)
/*limit of 15 items that can*/	{
/*be billed in a bill. But if*/		cout<<"\nYou reached the maximum limit of items that can be mentioned in a bill.\n";
/*there is still more items remaining*/ cout<<"If you have more items left in your cart then please make a separate  bill for that.\n";
/*in the cart then customer need*/	cout<<"Press any key to view the bill";
/*to generate a separate bill for*/     getch();
/*those products*/			break;
				}
				cout<<"Do you wish to continue[y/n] ? ";
				cin>>another;
			}
			i--;
			clrscr();
			break;
		case 2:
			clrscr();
			design();
			clm = 22;
			row = 9;
			for(; i>=0; i--)
			{
/*Printing the items  */        items[i].display(clm,row);
/*details on the bill*/		row++;
			}
			Shop :: disp_total(50,24); // The complete total amount
			_setcursortype(_NOCURSOR); //Hiding the corsor as
			getch();       // as there is no sense in showing
			clrscr();      // a cursor on the bill.
			break;
		case 3:
			fout.close();// Closing the text file, closing can also
			//be termed as storing the file(from RAM into HARD DISK)
			exit(0);
	}
	}
}
//Developer : Deepak kumar

