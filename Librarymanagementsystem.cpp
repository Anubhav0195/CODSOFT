#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

class Date
{
    private:
      int dd;
      int mm;
      int yy;
      void rectifydate()
      {
        if(dd>30)
        {
            dd-=30;
            mm++;
        }
        if(mm>12)
        {
            mm-=12;
            yy++;
        }
      }
      public:
        Date()
        {
            dd=1;
            mm=1;
            yy=2018;

        }
        void SetDate(Date temp)
        {
            dd=temp.dd+15;
            mm=temp.mm;
            yy=temp.yy;
            rectifydate();
        }
        void showDate()
        {
            cout<<dd<<"/"<<mm<<"/"<<yy;
        }
};
class Menu
{
    private:
    public:
        void mainmenu();
        void studentMenu();
        void bookMenu();
        void issueBook();
        void returnBook();
};
void Menu :: mainmenu()
{
    cout<<"########################### Main Menu ###############################"<<endl;
    cout<<"1.Student Menu"<<endl;
    cout<<"2.Book Menu"<<endl;
    cout<<"3.Issue Menu"<<endl;
    cout<<"4.Return Menu"<<endl;
    cout<<"5.Exit"<<endl;
}
void Menu :: studentMenu()
{
    cout<<"########################### Student Menu #############################"<<endl;
    cout<<"1.New Entry"<<endl;
    cout<<"2.Modify Entry"<<endl;
    cout<<"3.Search Entry"<<endl;
    cout<<"4.Delete Entry"<<endl;
    cout<<"5.View student details"<<endl;
    cout<<"6.Go back to previous menu"<<endl;
}
void Menu :: bookMenu()
{
    cout<<"############################ Book Menu #################################"<<endl;
     cout<<"1.New Entry"<<endl;
     cout<<"2.Modify Entry"<<endl;
     cout<<"3.Search Entry"<<endl;
     cout<<"4.Delete Entry"<<endl;
     cout<<"5.View all books details"<<endl;
     cout<<"6.Go back to previous menu"<<endl;

}
class BookData
{
    public:
        char title[30];
        char author[30];
        char publisher[30];
        int status;
        float price;
        int issuedrollno;
        Date issueDate;
        Date returnDate;
        BookData()
        {
            status =0;
            issuedrollno = -9999;
        }

};
class StudentData
{
    public:
      int rollno;
      char name[30];
      char address[30];
      char branch[30];
      int status;
      char booktitle[30];
      StudentData()
      {
          status =0;
      }
};
class Book
{
    public:
       void inputDetails();
       void modifyDetails();
       void searchDetails();
       void deleteDetails();
       void viewAllbookDetails();
};
void Book :: inputDetails()
{
    fstream ofp;
    ofp.open("bookDatabase.dat",ios :: out | ios :: binary | ios ::app);
    if(!ofp)
    {
        cout<<"Unable to open file"<<endl;
        return;
    }

    BookData book;
    cout<<"Enter book title:"<<endl;
    cin>>book.title;
    cout<<"Enter author's name:"<<endl;
    cin>>book.author;
    cout<<"Enter book publisher:"<<endl;
    cin>>book.publisher;
    cout<<"Enter book price:"<<endl;
    cin>>book.price;

    ofp.write((char*)&book,sizeof(BookData));
    ofp.close();

}
void Book :: modifyDetails()
{
    fstream file;
    file.open("bookDatabase.dat",ios :: binary | ios :: in | ios :: out | ios :: ate);
    if(!file)
    {
        cout<<"Unable to open file "<<endl;
        return;
    }
    file.seekg(0,ios :: beg);
    BookData book;
    char title[25];
    cout<<"Enter book title of the book you want to modify:";
    cin>>title;
    while(file.read((char*)&book,sizeof(BookData)))
    {
        if(strcmp(book.title,title)==0)
        {
            int position =(-1)*sizeof(BookData);
            file.seekp(position,ios::cur);

            cout<<"Enter new book title:";
            cin>>book.title;
            cout<<"Enterr new author's name:";
            cin>>book.author;
            cout<<"Enter new book publisher:";
            cin>>book.publisher;
            cout<<"Enter new book price:";
            cin>>book.price;

            cout<<"Record updated:";
            cin.get();
            cin.get();
            return;
        }
    }
    cout<<"Book not found!";
    cin.get();
    cin.get();
}
void Book :: searchDetails()
{
    fstream file;
    file.open("bookDatabase.dat",ios :: in | ios :: binary);
    if(!file)
    {
        cout<<"Unable to open file!"<<endl;
        cin.get();
        cin.get();
        return;
    }
    BookData book;
    char title[30];
    cout<<"Enter book title of the book you want to modify:";
    cin>>title;
    while(file.read((char*)&book,sizeof(BookData)))
    {
        if(strcmp(book.title,title)== 0)
        {
            cout<<"Book title :"<<book.title<<endl;
            cout<<"Book author :"<<book.author<<endl;
            cout<<"Book publisher :"<<book.publisher<<endl;
            cout<<"Book price :"<<book.price<<endl;
            if(book.status ==1)
            {
                cout<<"Issued status :"<<book.issuedrollno<<endl;
                cout<<"Issued date:";
                book.issueDate.showDate();
                cout<<endl<<"Return Date:";
                book.returnDate.showDate();
                cout<<endl;

            }
            else
            {
                cout<<"Issued Status :None"<<endl;
            }
            cin.get();
            cin.get();
            return;
        }
    }
    cout<<"Book not found"<<endl;
    cin.get();
    cin.get();
    return;
}
void Book :: deleteDetails()
{
    fstream file,temp;
    file.open("bookData.dat",ios :: binary | ios :: in);
    temp.open("temp.dat",ios :: binary | ios :: out);

    char title[25];
    BookData book;
    int flag=0;
    cout<<"Enter book title to remove:";
    cin>>title;
    while(file.read((char*)&book,sizeof(BookData)))
    {
        if(strcmp(book.title,title)==0)
        {
            flag++;
            continue;
        }
        temp.write((char*)&book,sizeof(BookData));
    }
    file.close();
    temp.close();
    remove("bookDatabase.dat");
    rename("temp.dat","bookDatabase.dat");
    if(flag ==1)
      cout<<"Record Deleted"<<endl;
      else
       cout<<"Record not found"<<endl;
    cin.get();
    cin.get();
    return;   
}
void Book ::viewAllbookDetails()
{
    fstream file;
    file.open("bookDatabase.dat",ios :: binary | ios :: in);
    BookData book;
    int choice =1;
    while(file.read((char*)&book,sizeof(BookData)) && choice)
    {
        system("clear");
        cout<<"Book title :"<<book.title<<endl;
        cout<<"Book author :"<<book.author<<endl;
        cout<<"Book publisher :"<<book.publisher<<endl;
        cout<<"Book price :"<<book.price<<endl;
        if(book.status ==1)
        {
            cout<<"Issued status:"<<book.issuedrollno<<endl;
            cout<<"issued date:";
            book.issueDate.showDate();
            cout<<"endl"<<"return Date :";
            book.returnDate.showDate();
        }   
        else
        {
            cout<<"Issued status : None"<<endl;
        }
        cout<<"Press 1 to view the next book else press 0:";
        cin>>choice;

    }
    cin.get();
    cin.get();
    return;
}
class Student
{
    public:
      void inputDetails();
      void modifyDetails();
      void searchDetails();
      void deleteDetails();
      void viewAllStudentDetails();
};
void Student :: inputDetails()
{
    fstream ofp;
    ofp.open("StudentDatabase.dat",ios :: out | ios :: app | ios :: binary);
    if(!ofp)
    {
        cerr<<"unable to open file"<<endl;
        return;

    }
    StudentData student;
    cout<<"Enter Student's roll no:"<<endl;
    cin>>student.rollno;
    cout<<"Enter student's name:"<<endl;
    cin>>student.name;
    cout<<"Enter student's address:"<<endl;
    cin>>student.address;
    cout<<"Enter student's branch:"<<endl;
    cin>>student.branch;
    
    cout<<"Record added to database!"<<endl;
    ofp.write((char*)&student,sizeof(StudentData));
    ofp.close();
}
void Student :: modifyDetails()
{
    fstream fp;
    fp.open("StudentDatabase.dat",ios :: binary | ios :: in | ios :: ate);
    if(!fp)
    {
        cerr<<"Unable to open file !";
        return;
    }
    fp.seekg(0,ios :: beg);
    int target;
    cout<<"Enter student roll no. to modify:";
    cin>>target;
    StudentData student;
    while(fp.read((char*)&student,sizeof(student)))
    {
       if(target == student.rollno)
       {
            int position =(-1)*sizeof(StudentData);
            fp.seekp(position,ios :: cur);

            cout<<"Enter student'snew roll no.:"<<endl;
            cin>>student.rollno;
            cout<<"Enter student's new name:"<<endl;
            cin>>student.name;
            cout<<"Enter student's new address:"<<endl;
            cin>>student.address;
            cout<<"Enter student;s new branch:"<<endl;
            cin>>student.branch;
            fp.write((char*)&student,sizeof(StudentData));
            fp.close();
            
            cout<<"Record Updated"<<endl;
            return;
            

       }
       
    }
    cout<<"Roll no. not found !"<<endl;
    return;
}
void Student :: searchDetails()
{
    fstream ifp;
    ifp.open("StudentDatabase.dat",ios :: in | ios :: binary);
     if(!ifp)
     {
        cerr<<"Unable to open file !"<<endl;
        return;
     }
     int target;
     cout<<"Enter roll no. to search:";
     cin>>target;
     StudentData student;
     while(ifp.read((char*)&student,sizeof(student)))
     {
        if(target == student.rollno)
        {
            cout<<"Record Found!"<<endl;
            cout<<"Student's name:"<<student.name<<endl;
            cout<<"Student's roll no:"<<student.rollno<<endl;
            cout<<"Student's Branch :"<<student.branch<<endl;
            cout<<"Student's Address:"<<student.address<<endl;
            if(student.status == 1)
            {
                cout<<"Issued bok name is :"<<student.booktitle<<endl;
            }
            else
            {
                cout<<"No book is issued for this roll no."<<endl;
            }
            cin.get();
            cin.get();
            return;

        }
     }
     cout<<"Record not found !"<<endl;
     return;

}
void Student :: viewAllStudentDetails()
{
     system("clear");
     fstream ifp;
     ifp.open("studentDatabase.dat",ios :: in | ios :: binary);
     if(!ifp)
     {
        cerr<<"Unable to open file!"<<endl;
        return;
     }
     StudentData student;
     int choice =1;
     while(ifp.read((char*)&student,sizeof(student))&& choice)
     {
        system("clear");
        cout<<"Student's name:"<<student.name<<endl;
        cout<<"Student's roll no:"<<student.rollno<<endl;
        cout<<"Student's branch:"<<student.branch<<endl;
        cout<<"Student's Address:"<<student.address<<endl;

        if(student.status == 1)
        {
            cout<<"Issued book name is :"<<student.booktitle<<endl;
        }
        else{
            cout<<"No book is issued for this roll no:"<<endl;
        }
        cout<<"To view next student press 1 else press 0";
        cin>>choice;
     }
     return;
}
void Student :: deleteDetails()
{
    fstream file;
    file.open("studentDatabase.dat",ios :: in| ios :: binary);
    fstream temp;
    temp.open("temp.dat",ios :: out | ios :: binary);
    StudentData student;
    int target;
    int flag =0;
    while(file.read((char*)&student,sizeof(Student)))
    {
        if(student.rollno ==target)
        {
            flag++;
            continue;
        }
        temp.write((char*)&student,sizeof(Student));
    }
    file.close();
    temp.close();
    remove("studentDatabase.dat");
    remove("temp.dat,studentDatabase.dat");
    if(flag == 1)
    {
        cout<<"Record Deleted:"<<endl;
    }
    else
    {
        cout<<"Roll no.not found"<<endl;
    }
    cin.get();
    cin.get();

    return;

}
void Menu :: issueBook()
{
    fstream sp,bp;
    sp.open("studentDatabase.dat",ios :: in | ios :: out | ios ::ate | ios :: binary);
    bp.open("bookDatabase.dat",ios :: in | ios :: out | ios :: ate | ios :: binary);
    bp.seekg(0,ios :: beg);
    sp.seekg(0,ios :: beg);

    int rollno,flagS=0,flagB=0,position;
    char title[30];
    StudentData student;
    BookData book;

    cout<<"Enter student's roll no to issue book:";
    cin>>rollno;
    while(sp.read((char*)&student,sizeof(StudentData)))
    {
        if(student.rollno == rollno)
        {
            position =(-1)*sizeof(StudentData);
            sp.seekp(position,ios :: cur);
            flagS++;
            break;

        }
    }
    if(flagS !=1)
    {
        cout<<"Record not found!"<<endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    cout<<"Enter book title you want to issue:";
    cin>>title;
    while(bp.read((char*)&book,sizeof(BookData)))
    {
        if(strcmp(book.title,title)==0)
        {
            position =(-1)*sizeof(BookData);
            bp.seekp(position,ios:: cur);
            flagB++;
            break;
        }
    }
    if(flagB !=1)
    {
        cout<<"Record not found!"<<endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    if(student.status != 1 && book.status !=1)
    {
        strcmp(student.booktitle,title);
        student.status =1;
        book.status =1;
        book.issuedrollno = student.rollno;
        book.issueDate.SetDate(book.issueDate);
        book.returnDate.SetDate(book.issueDate);
        sp.write((char*)&student,sizeof(StudentData));
        bp.write((char*)&book,sizeof(BookData));
        sp.close();
        bp.close();

    }
    else
    {
        if(student.status ==1)
        {
            cout<<"Student's account is already full!"<<endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
        else
        {
            cout<<"Book is already issued !"<<endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
    }

}
void Menu :: returnBook()
{
    fstream sp,bp;
    sp.open("studentDatabase.dat",ios :: in | ios :: out | ios :: ate | ios :: binary);
    bp.open("bookDatabase.dat",ios :: in | ios :: out | ios :: ate | ios :: binary);
    bp.seekg(0,ios :: beg);
    sp.seekg(0,ios :: beg);
    int rollno,flagS=0,flagB=0,position;
    char title[30];
    StudentData student;
    BookData book;
    cout<<"Enter student's roll no to return book:"<<endl;
    cin>>rollno;
    while(sp.read((char*)&student,sizeof(StudentData)))
    {
        if(student.rollno == rollno)
        {
            position =(-1)*sizeof(StudentData);
            sp.seekp(position,ios :: cur);
            flagS++;
            break;

        }
    }
    if(flagS !=1)
    {
        cout<<"Record not found !"<<endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    while(bp.read((char*)&book,sizeof(BookData)))
    {
        if(strcmp(book.title,student.booktitle)== 0)
        {
            position =(-1)*sizeof(BookData);
            bp.seekp(position,ios :: cur);
            flagB++;
            break;
        }
    }
    if(flagB!=1)
    {
        cout<<"Record not found !"<<endl;
        cin.get();
        cin.get();
        sp.close();
        bp.close();
        return;
    }
    if(student.status ==1 && book.status ==1)
    {
        student.status =0;
        book.status =0;
        book.issuedrollno =-9999;
        sp.write((char*)&student,sizeof(StudentData));
        bp.write((char*)&book,sizeof(BookData));
        sp.close();
        bp.close();
    }
    else
    {
        if(student.status ==0)
        {
            cout<<"Student's account is already full !"<<endl;
            cin.get();
            cin.get();
            sp.close();
            bp.close();
            return;
        }
    }
}
int main()
{
    Menu menu;
    int quit =0;
    char choice[3];
    
    while(!quit)
    {
        system("clear");
        menu.mainmenu();
        cout<<"Please enter your choice:"<<endl;
        cin>>choice;
        switch(atoi(choice))
        {
            case 1:
            {
                system("Clear");
                menu.studentMenu();
                cout<<"Please enter your choice :"<<endl;
                cin>>choice;
                Student s1;
                switch(atoi(choice))
                {
                    case 1: s1.inputDetails();
                            break;
                    case 2: s1.modifyDetails();
                            break;
                    case 3: s1.searchDetails();
                            break;
                    case 4: s1.deleteDetails();
                            break;
                    case 5: s1.viewAllStudentDetails();
                            break;
                    case 6: break;

                    default : cout<<"Wrong Input received:";

                }
                break;

            }
            case 2:
            {
                system("clear");
                menu.bookMenu();
                cout<<"please enter your choice:"<<endl;
                cin>>choice;
                Book b1;
                switch(atoi(choice))
                {
                    case 1: b1.inputDetails();
                            break;
                    case 2: b1.modifyDetails();
                            break;
                    case 3: b1.searchDetails();
                            break;
                    case 4: b1.deleteDetails();
                            break;
                    case 5: b1.viewAllbookDetails();
                            break;
                    case 6: break;

                    default:cout<<"Wrong input received!"<<endl;
                }
                break;
            }
            case 3:menu.issueBook();
                   break;
            case 4:menu.returnBook();
                   break;
            case 5:quit++;
                   break;
            default: cerr<<"Please Enter correct input !"<<endl;
                     cin>>choice;;
            
            
        }
    }
    return 0;
}
