#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <windows.h>
#include <conio.h>

using namespace std;
class inventory
{
	public : string fname1="book_final.csv";
			 string fname2="login_details.csv";
			 vector<vector<string>> content1;
			 vector<string> row1;
			 string line1, word1;
			 vector<vector<string>> content2;
			 vector<string> row2;
			 string line2, word2;
			 int index[100],d_count=0,borrowed[100],b_count=0;
	public: void readfile1()
			{
				fstream file (fname1, ios::in);
				if(file.is_open())
				{
					while(getline(file, line1))
					{
						row1.clear();
						stringstream str(line1);
						while(getline(str, word1, ','))
						{
							row1.push_back(word1);
						}
						content1.push_back(row1);
					}
				}
				else
					cout<<"Could not open the file\n";
				file.close();
			}
			void readfile2()
			{
				fstream file (fname2, ios::in);
				if(file.is_open())
				{
					while(getline(file, line2))
					{
						row2.clear();
						stringstream str(line2);
						while(getline(str, word2, ','))
						{
							row2.push_back(word2);
						}
						content2.push_back(row2);
					}
				}
				else
					cout<<"Could not open the file\n";
				file.close();
			}
			int compare_substring(string str,string s)
			{
    			int len1, len2, i, j, flag = 0;
    			len1 = str.size();
    			len2 = s.size();
    			for(int i=0;i<len1;i++)
				{
					str[i]=tolower(str[i]);
				}
    			for(int i=0;i<len2;i++)
				{
					s[i]=tolower(s[i]);
				}
    			for (i = 0; i <= len1 - len2; i++)
    			{
        			for (j = 0; j < len2; j++)
        			{
            			if (s[i + j] != str[j])
            			{
                			break;
            			}
        			}
        			if (j == len2)
        			{
            			flag = 1;
            			return 1;
            			break;
        			}
    			}
    			if (flag == 0)
    			{
        			return -1;
    			}
			}
};

class operations:public inventory
{
	private: string name;
			 string usn;
			 string password;

	public : int login();
			 int create_account();
			 void search_by_book();
			 void search_by_author();
			 int borrow_book();
			 int return_book();
			 void display_book_list();
			 void logout();
};

void progress_bar()
{
	char a=177,b=219;
	cout<<"Loading results please wait..."<<endl;
	for(int i=0;i<50;i++)
	{
		cout<<a;
	}
	cout<<"\r";
	for(int i=0;i<20;i++)
	{
		cout<<b;
		Sleep(250);
	}
	for(int i=0;i<15;i++)
	{
		cout<<b;
		cout<<b;
		Sleep(250);
	}
	cout<<endl;
}

string input_password(char sp='*')
{
	string passwd="";
	char ch_ipt;
	while (true)
	{
		ch_ipt=getch();
		if (ch_ipt==13 && passwd.length()==0)
		{
			continue;
		}
		else if (ch_ipt==13)
		{
			cout<<endl;
			return passwd;
		}
		else if (ch_ipt==8 && passwd.length()!=0)
		{
			passwd.pop_back();
			cout<<"\b";
			continue;
		}
		else if (ch_ipt==8 && passwd.length()==0)
		{
			continue;
		}
		passwd.push_back(ch_ipt);
		cout << sp;
	}
}

void operations::search_by_book()
{
	int f=0,m=0,x;
	string s,book;
	cout<<"enter the name of the book you want to search:"<<endl;
	cin.ignore();
	getline(cin,book);
	d_count=0;
	for(int i=0;i<content1.size();i++)
	{

		s=content1[i][1];
		f=compare_substring(s,book);
		if(f==1)
		{
			index[d_count]=i;
			d_count++;
		}
		f=-1;
	}
	progress_bar();
	if(d_count==0)
	{
		cout<<"the book you are searching for is not available"<<endl;
		return;
	}
	else
	{
		cout<<"ISBN\tBook details"<<endl;
		for(int i=0;i<content1.size();i++)
		{
			for(int j=0;j<content1[i].size();j++)
			{
				x=index[m];
				cout<<content1[x][j]<<"\t";
			}
			m++;
			if(m==d_count)
			{
				break;
			}
			cout<<endl;
		}
	}
	cout<<endl;
}

void operations::search_by_author()
{
	int f=0,m=0,x;
	string s,author;
	cout<<"enter the name of the author you want to search:"<<endl;
	cin.ignore();
	getline(cin,author);
	d_count=0;
	for(int i=0;i<content1.size();i++)
	{

		s=content1[i][2];
		f=compare_substring(s,author);
		if(f==1)
		{
			index[d_count]=i;
			d_count++;
		}
		f=-1;
	}
	progress_bar();
	if(d_count==0)
	{
		cout<<"the book you are searching for is not available"<<endl;
		return;
	}
	else
	{
		cout<<"ISBN\tBook details"<<endl;
		for(int i=0;i<content1.size();i++)
		{
			for(int j=0;j<content1[i].size();j++)
			{

				x=index[m];
				cout<<content1[x][j]<<"\t";
			}
			m++;
			if(m==d_count)
			{
				break;
			}
			cout<<endl;
		}
	}
	cout<<endl;
}

int operations::borrow_book()
{
	int isbn,check=0;
	string status="Borrowed";
	if(d_count==0)
	{
		return 1;
	}
	cout<<"Enter the isbn of the book you want to borrow:"<<endl;
	cin>>isbn;
	if(content1[isbn-1][3]==status)
	{
		cout<<"Sorry!!The book has been already borrowed :("<<endl;
		cout<<endl;
		return 0;
	}
	for(int i=0;i<d_count;i++)
	{
		if(isbn-1==index[i])
		{
			check=1;
			break;
		}
	}
	if(check==1)
	{
		content1[isbn-1][3]=status;
		for(int i=0;i<content1[isbn-1].size();i++)
		{
			cout<<content1[isbn-1][i]<<"\t";
		}
		cout<<endl;
		borrowed[b_count]=isbn-1;
		b_count++;
		cout<<"You have borrowed this book....Happy reading :)"<<endl;
		cout<<endl;
		return 1;
	}
	else
	{
		cout<<"It seems that the book you are searching for does not match the displayed books..."<<endl;
		cout<<endl;
		return -1;
	}
	cout<<endl;
}

int operations::return_book()
{
	int index,isbn,check=0,pos,m=0,x;
	string status="Not Borrowed";
	if(b_count==0)
	{
		cout<<"You have not borrowed any books!!"<<endl;
		return 1;
	}
	cout<<"Name: "<<name<<endl;
	cout<<"Usn: "<<usn<<endl;
	cout<<"the books that you have borrowed are:"<<b_count<<endl;
	cout<<"ISBN\tBook details"<<endl;
	for(int i=0;i<content1.size();i++)
	{
		for(int j=0;j<content1[i].size();j++)
		{
			x=borrowed[m];
			cout<<content1[x][j]<<"\t";
		}
		m++;
		if(m==b_count)
		{
			break;
		}
		cout<<endl;;
	}
	cout<<endl;
	cout<<"Enter the isbn of the book you would like to return:"<<endl;
	cin>>isbn;
	for(int k=0;k<b_count;k++)
	{
		if(isbn-1==borrowed[k])
		{
			check=1;
			pos=k;
			break;
		}
	}
	if(check==0)
	{
		cout<<"Seems like you have not borrowed this book.."<<endl;
		cout<<endl;
		return -1;
	}
	else
	{
		content1[isbn-1][3]=status;
		for(int i=0;i<content1[isbn-1].size();i++)
		{
			cout<<content1[isbn-1][i]<<"\t";
		}
		cout<<endl;
		cout<<"The book has been returned"<<endl;
		for(int k=pos;k<b_count;k++)
		{
				borrowed[k]=borrowed[k+1];
		}
		b_count--;
		return 1;
	}
}

void operations::display_book_list()
{
	if(b_count==0)
	{
		cout<<"You seem to have not borrowed any books!!"<<endl;
		return;
	}
	int m=0,x;
	cout<<"Name: "<<name<<endl;
	cout<<"Usn: "<<usn<<endl;
	cout<<"the books that you have borrowed are:"<<b_count<<endl;
	cout<<"ISBN\tBook details"<<endl;
	for(int i=0;i<content1.size();i++)
	{
		for(int j=0;j<content1[i].size();j++)
		{
			x=borrowed[m];
			cout<<content1[x][j]<<"\t";
		}
		m++;
		if(m==b_count)
		{
			break;
		}
		cout<<endl;
	}
	cout<<endl;
}

int operations::login()
{
	readfile2();
	string s;
	int index=-1,check=0;
	cout<<"Enter your usn:"<<endl;
	cin>>usn;
	for(int i=0;i<content2.size();i++)
	{

		s=content2[i][0];
		if(s==usn)
		{
			index=i;
		}
	}
	if(index==-1)
	{
		cout<<"You don't seem to have an account...Please create one"<<endl;
		return 0;
	}
	else
	{
		cout<<"Enter the password:"<<endl;
		password=input_password();
		if(password==content2[index][1])
		{
			check=1;
		}
		if(check==1)
		{
			name=content2[index][2];
			cout<<"Welcome to the library "<<name<<endl;
			return 1;
		}
		else
		{
			cout<<"Wrong password!!"<<endl;
			return 0;
		}
	}
}

int operations::create_account()
{
	int acc_present=0;
	string s;
	fstream file;
	file.open(fname2, ios::out | ios::app);
	readfile2();
	cout<<"Enter your usn:"<<endl;
	cin>>usn;
	for(int i=0;i<content2.size();i++)
	{

		s=content2[i][0];
		if(s==usn)
		{
			acc_present=1;
			break;
		}
	}
	if(acc_present==1)
	{
		cout<<"You already have an account...Please login using that"<<endl;
		return 0;
	}
	cout<<"Enter your name:"<<endl;
	cin.ignore();
	getline(cin,name);
	cout<<"Enter your password:"<<endl;
	password=input_password();
	file << usn << ","
         << password << ","
         << name << ","
         << "\n";
    cout<<"Account created successfully!!"<<endl;
    return 1;
}

void operations::logout()
{
	if(b_count==0)
	{
		cout<<"Thank you :) "<< name <<". Hope you find your books next time!!"<<endl;
	}
	else
	{
		display_book_list();
		cout<<"Thank you :) "<< name <<". Hope you enjoy the books!!"<<endl;
	}
}

int main()
{
	system("color 0A");
	operations library;
	int choice,choice2,choice3,loop1=0,loop2=0,login_successful=0;
	char continue_borrowing='y';
	cout<<"\t\t\t\t\t\tWelcome To the Library"<<endl;
	while(1)
	{
		cout<<endl;
		cout<<"============= LOGIN MENU ============="<<endl;
		cout<<"1.Login\t   2.Create account\t3.exit"<<endl;
		cout<<"enter your choice:"<<endl;
		cin>>choice3;
		switch(choice3)
		{
			case 1: login_successful=library.login();
					break;

			case 2: login_successful=library.create_account();
					break;

			case 3: cout<<"Thank you :)...Visit again!!"<<endl;
					exit(0);

			default:cout<<"Please enter the correct choice!!"<<endl;
					break;
		}
		while(login_successful==1)
		{
			library.readfile1();
			cout<<endl;
			cout<<"==================== MENU ====================="<<endl;
			cout<<"1.Borrow Book\t2.Return Book\t3.Borrowed Books\t4.Logout"<<endl;
			cout<<"Enter your choice:"<<endl;
			cin>>choice;
			switch(choice)
			{
				case 1: cout<<"How would like to search for your book??"<<endl;
						cout<<"1.By Book Name\t2.By Author Name"<<endl;
						cout<<"enter your choice:"<<endl;
						cin>>choice2;
						switch(choice2)
						{
							case 1: library.search_by_book();
									cout<<endl;
									while(continue_borrowing=='y'||continue_borrowing=='Y')
									{
										while(loop1!=1)
										{
											loop1=library.borrow_book();
										}
										loop1=0;
										cout<<endl;
										if(library.d_count==0)
										{
											break;
										}
										cout<<"Would you like to borrow another book from this list?[Y/N]"<<endl;
										cin>>continue_borrowing;
									}
									continue_borrowing='y';
									break;

							case 2: library.search_by_author();
									cout<<endl;
									while(continue_borrowing=='y'||continue_borrowing=='Y')
									{
										while(loop2!=1)
										{
											loop2=library.borrow_book();
										}
										loop2=0;
										cout<<endl;
										if(library.d_count==0)
										{
											break;
										}
										cout<<"Would you like to borrow another book from this list?[Y/N]"<<endl;
										cin>>continue_borrowing;
									}
									continue_borrowing='y';
									break;

							default:cout<<"Enter the correct choice!!"<<endl;
									break;
						}
						break;

				case 2: while(loop2!=1)
						{
							loop2=library.return_book();
						}
						loop2=0;
						break;

				case 3: library.display_book_list();
						break;

				case 4: library.logout();
						cout<<"Thank you for visiting :)"<<endl;
						login_successful=0;
						break;

				default:cout<<"Enter the right choice!!"<<endl;
						break;
			}
		}
	}
	return 0;
}
