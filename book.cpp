#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>
 
using namespace std;
 
class book
{
          char book_number[30];
          char book_name[50];
          char author_name[20];
          int num_copies;
 
  public:
          void get_book_details()
          {
          cout<<"\nEnter the Details of Book \n";
                    cout<<"\nEnter The Book Id: ";
                    cin>>book_number;
                    cout<<"\nEnter The Name of The Book: ";
                     cin.ignore();
                    cin.getline(book_name,50);
                    cout<<"\nEnter The Author's Name: ";
                    cin.ignore();
                    cin.getline(author_name,50);
                    fflush(stdin);
            cout<<"\nEnter No. Of Copies : ";
    cin>>num_copies;
          }
 
          void show_book()
          {
                    cout<<"\nBook Id: "<<book_number;
                    cout<<"\nBook Name: "<<book_name;
                    cout<<"\nAuthor's Name: "<<author_name;
                    cout<<"\nCOPIES : "<<num_copies;
          }
          void modify_book()
          {
                    cout<<"\nBook Id : "<<book_number;
                    cout<<"\nModify Book Id : ";
                    cin.ignore();
                    cin.getline(book_name,50);
                    cout<<"\nModify Author's Name: ";
                    cin.ignore();
                    cin.getline(author_name,50);
                    fflush(stdin);
        cout<<"\nEnter No. Of Copies : ";
    cin>>num_copies;
          }
          char* getbooknumber()
          {
                    return book_number;
          }
          void report()
          {cout<<book_number<<setw(30)<<book_name<<setw(25)<<author_name<<setw(15)<<num_copies<<endl;}
 
};        
 
       
 
fstream fp;
book bk;
void write_book()
{
          system("cls");
          int more_or_main;
          fp.open("book.dat",ios::out|ios::app);
          do
          {
                    bk.get_book_details();
                    fp.write((char*)&bk,sizeof(book));
                    cout<<"\nPress 1 to add more books.";
                    cout<<"\nPress 2 to return to main menu.\n";
                    cout<<"Enter: ";
                    cin>>more_or_main;
          }while(more_or_main == 1);
          fp.close();
}
 
void display_a_book(char n[])
{
          system("cls");
          cout<<"\nBOOK DETAILS\n";
          int check=0;
          fp.open("book.dat",ios::in);
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    if(strcmpi(bk.getbooknumber(),n)==0)
                    {
                               bk.show_book();
                              check=1;
                    }
          }
          fp.close();
          if(check==0)
                    cout<<"\n\nBook does not exist";
        getch();
}
 
void modify_book()
{
          system("cls");
          char n[20];
          int found=0;
          cout<<"\n\n\tMODIFY BOOK";
          cout<<"\n\n\tEnter The book Id: ";
          cin>>n;
          fp.open("book.dat",ios::in|ios::out);
          while(fp.read((char*)&bk,sizeof(book)) && found==0)
          {
                    if(strcmpi(bk.getbooknumber(),n)==0)
                    {
                               bk.show_book();
                               cout<<"\nEnter The New Details of book"<<endl;
                               bk.modify_book();
                               int pos=-1*sizeof(bk);
                              fp.seekp(pos,ios::cur);
                              fp.write((char*)&bk,sizeof(book));
                              cout<<"\n\n\t Record Updated Successfully...";
                              found=1;
                    }
          }
          fp.close();
          if(found==0)
                    cout<<"\n\n Record Not Found ";
          getch();
}
 
void delete_book()
{
          system("cls");
          char n[20];
          int flag=0;
          cout<<"\n\n\n\tDELETE BOOK";
          cout<<"\n\nEnter The Book's Id You Want To Delete: ";
          cin>>n;
          fp.open("book.dat",ios::in|ios::out);
          fstream fp2;
          fp2.open("Temp.dat",ios::out);
          fp.seekg(0,ios::beg);
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    if(strcmpi(bk.getbooknumber(),n)!=0)  
                    {
                               fp2.write((char*)&bk,sizeof(book));
                    }
                    else
                              flag=1;
          }
          fp2.close();
          fp.close();
          remove("book.dat");
          rename("Temp.dat","book.dat");
          if(flag==1)
                    cout<<"\n\n\tRecord Deleted ..";
          else
                    cout<<"\n\nRecord not found";
          getch();
}
 
void display_allb()
{
          system("cls");
          fp.open("book.dat",ios::in);
          if(!fp)
          {
                    cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
                    getch();
                    return;
          }
          cout<<"\n\n\t\tBook LIST\n\n";
         cout<<"----------------------------------------------------------------\n";
          cout<<"Book Number"<<setw(15)<<"Book Name"<<setw(15)<<"Author"<<setw(15)<<"Copies"<<endl;
          cout<<"----------------------------------------------------------------\n";
          while(fp.read((char*)&bk,sizeof(book)))
          {
                    bk.report();
          }
          fp.close();
          getch();
}
 
void intro()
{
    // system("color 06");
     system("cls");
 
}
 
 
int main()
{
          int option = 0;
          for(;;)
          {
               intro();
            cout<<"------------------------------------------";
                cout<<"\nPress 1 to TO ADD BOOK";
                cout<<"\nPress 2 to SHOW ALL BOOKS";
                cout<<"\nPress 3 to VIEW BOOK";
                cout<<"\nPress 4 to MODIFY BOOKS";
                cout<<"\nPress 5 to DELETE BOOKS";
                cout<<"\nPress 6 to Exit";
  cout<<"\n---------------------------------------------\n";
  cout<<"\nEnter Option: ";
  cin>>option;
  switch(option)
          {
                    case 1:  system("cls");
                                         write_book();
                                                   break;
                               case 2: display_allb();
                                 break;
                    case 3:
                              char num[20];
                               system("cls");
                              cout<<"\n\n\tPlease Enter The book ID. ";
                              cin>>num;
                              display_a_book(num);
                              break;
                    case 4: modify_book();break;
                    case 5: delete_book();break;
                    case 6: exit(0);
                               break;
                    default:cout<<"\a";
          }    
           
          }
}