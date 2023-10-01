#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "lib2.h"
using namespace std;


void Temp::load_mag_jour()
{
    fstream f("magazine.csv");
    string line;
    getline(f,line); // read header line

    int x = magazine_obj.Cou_mag();

    while(getline(f,line))
    {
        stringstream ss(line);
        getline(ss,line,'"');
        getline(ss,line,'"');
        Magazine m(line,1,30,100+x);
        M[x++] = m;
        magazine_obj.set_Mag(x);
    }

    f.close();

    fstream f1("journals.csv");
    getline(f1,line); // read header line
    x = journal_obj.getnoofjournals();

    while(getline(f1,line))
    {
        Journal j(line,1000);// assuming journals are infinite
        J[x++] = j;
        journal_obj.setnoofjournals(x);
    }

    f1.close();

}

void Temp::showbook()
{
    int x = book_obj.book_no();
    cout<<left<<setw(95)<<setfill(' ')<<"TITLE";
    cout<<left<<setw(95)<<setfill(' ')<<"AUTHOR";
    cout<<left<<setw(13)<<setfill(' ')<<"ISBN";
    for(int i=0;i<x;i++)
    {
        cout<<left<<setw(95)<<setfill(' ')<<B[i].gettitle();
        cout<<left<<setw(95)<<setfill(' ')<<B[i].getauthor();
        cout<<left<<setw(13)<<setfill(' ')<<B[i].getisbn();
        cout<<"\n";
    }
    
}

void Temp::loadfile()
{
    ifstream file("books.csv");
    if (!file.is_open()) {
        cout << "Error: Could not open file \n"; 
        return;
    }

    string line;
    getline(file, line); 

    int line_number = 1;
    while (getline(file, line)) {
        

        int n = line.size();
        string temp;
        string id;
        int book_count;
        string isbn,author,title;
        int col_count = 0;
        for(int i=0;i<n;)
        {
            if(line[i]=='"')
            {
                i++;
                while(line[i]!='"')
                {
                    temp.push_back(line[i]);
                    i++;
                }
                if(col_count==7)
                {
                    author = temp;
                }
                else if(col_count==10)
                {
                    title = temp;
                }
                i++;
            }
            if(line[i]==',')
            {
                if(col_count==0)
                {
                    id = "BK" + temp;
                }
                else if(col_count==4)
                {
                    book_count = stoi(temp);
                }
                else if(col_count==5)
                {
                    long double y = stod(temp);
                    long long int x = y;
                    isbn = to_string(x);
                }
                else if(col_count==7)
                {
                    author = temp;
                }
                else if(col_count==10)
                {
                    title = temp;
                }
                temp = "";
                col_count++;
                i++;
            }
            else
            {
                temp.push_back(line[i]);
                i++;
            }
        }
        

        Book book(id, book_count, 1,author,isbn,line_number,title);
        int x = book_obj.book_no();
        B[x++] = book;
        
        book_obj.setnoofbooks(x);
        line_number++;
        
    }
    file.close();
}

void Temp::showmagazine()
{
    int x = magazine_obj.Cou_mag();
    for(int i=0;i<x;i++)
    {
        cout<<M[i].gettitle()<<"\n";
    }
}

void Temp::show_journal()
{
    int x = journal_obj.getnoofjournals();
    for(int i=0;i<x;i++)
    {
        cout<<J[i].gettitle()<<"\n";
    }
}

void Temp::show_item()
{
    int key;
    cout<<"1 to show books\n";
    cout<<"2 for show magazines\n";
    cout<<"3 for show journals\n";

label: cin>>key;

    switch(key)
    {
        case 1:
        showbook();
        break;
        case 2:
        showmagazine();
        break;
        case 3:
        show_journal();
        break;
        default:
        cout<<"Enter correct choice\n";
        goto label;
        break;
    }
}

bool Temp:: searchjournal()
{
    xy = 2;
    int x = journal_obj.getnoofjournals();
    fstream file("Searchjournalhistory.txt",ios::app);
    string s;
    bool f=0;
    cout<<"Enter title\n";
    getchar();
    getline(cin,s);
    for(int i=0;i<x;i++)
    {
        string x = J[i].gettitle();
        transform(x.begin(), x.end(), x.begin(), ::tolower);
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        if(x.find(s)!=string::npos)
        {
            f=1;
            file << J[i].gettitle()<<"\n";
            searchresults[result++] = J[i].gettitle();
            cout<<"Title : "<<J[i].gettitle()<<"\n";

        }
    }
    if(!f)
    cout<<"No Journal found\n";
    file.close();
    return f;
}

bool Temp:: searchbook()
{
    xy = 0;
    ofstream  file("Searchbookhistory.txt");
    int x = book_obj.book_no();
    int key;
    cout<<"1 for search by Title\n";
    cout<<"2 for search by Author\n";
    cout<<"3 for search by ISBN\n";
    label: cin>>key;
    bool f=0;
    string s;
    switch(key)
    {
        case 1:
        cout<<"Enter title\n";
        getchar();
        getline(cin,s);
        for(int i=0;i<x;i++)
        {
            string x = B[i].gettitle();
            transform(x.begin(), x.end(), x.begin(), ::tolower);
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            if(x.find(s)!=string::npos)
            {
                f=1;
                file << B[i].getauthor() << ", " << B[i].gettitle() <<"\n"; 
                searchresults[result++] = B[i].ITems::gettitle();
                cout<<"Author : "<<B[i].getauthor()<<"\n";
                cout<<"Title : "<<B[i].gettitle()<<"\n";
                cout<<"Isbn : "<<B[i].getisbn()<<"\n";
                cout<<"Shelf Number : "<<B[i].getlocation()<<"\n";
            }
        }
        break;
        case 2:
        cout<<"Enter Author\n";
        getchar();
        getline(cin,s);
        for(int i=0;i<x;i++)
        {
            string x = B[i].getauthor();
            transform(x.begin(), x.end(), x.begin(), ::tolower);
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            if(x.find(s)!=string::npos)
            {
                f=1;
                file << B[i].getauthor() << ", " << B[i].gettitle() <<"\n"; 
                searchresults[result++] = B[i].ITems::gettitle();
                cout<<"Author : "<<B[i].getauthor()<<"\n";
                cout<<"Title : "<<B[i].gettitle()<<"\n";
                cout<<"Isbn : "<<B[i].getisbn()<<"\n";
                cout<<"Shelf Number  : "<<B[i].getlocation()<<"\n";
            }
        }
        break;
        case 3:
        cout<<"Enter ISBN\n";
        getchar();
        getline(cin,s);
        for(int i=0;i<x;i++)
        {
            if(B[i].getisbn()==s)
            {
                f=1;
                file << B[i].getauthor() << ", " << B[i].gettitle() <<"\n"; 
                searchresults[result++] = B[i].ITems::gettitle();
                cout<<"Author : "<<B[i].getauthor()<<"\n";
                cout<<"Title : "<<B[i].gettitle()<<"\n";
                cout<<"Isbn : "<<B[i].getisbn()<<"\n";
                cout<<"Shelf Number : "<<B[i].getlocation()<<"\n";
            }
        }
        break;
        default:
        cout<<"Enter a valid choice\n";
        goto label;
        break;
    }
    if(!f)
    cout<<"Book is not available in the library\n";

    file.close();
    return f;
}

bool Temp:: searchmagazine()
{
    xy = 1;
    ofstream file("Searchmagazinehistory.txt");
    int x = magazine_obj.Cou_mag();
    string s;
    bool f=0;
    cout<<"Enter title\n";
    getchar();
    getline(cin,s);
    for(int i=0;i<x;i++)
    {
        string x = M[i].gettitle();
        transform(x.begin(), x.end(), x.begin(), ::tolower);
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        if(x.find(s)!=string::npos && M[i].getitemcount()>=1)
        {
            f=1;
            file << M[i].gettitle()<<"\n";
            searchresults[result++] = M[i].gettitle();
            cout<<"Title : "<<M[i].gettitle()<<"\n";
            cout<<"Shelf number : "<<M[i].getlocation()<<"\n";

        }
    }
    if(!f)
    cout<<"Magazine is not available in the library\n";
    file.close();
    return f;
}

bool Temp:: searchitem()
{
    bool f=0;
    int key;
    cout<<"Press 1 to search for book\n";
    cout<<"Press 2 to search for magazine\n";
    cout<<"Press 3 to search for journal\n";

label: cin>>key;

    switch(key)
    {
        case 1:
        f = f | searchbook();
        break;
        case 2:
        f = f | searchmagazine();
        break;
        case 3:
        f = f | searchjournal();
        break;
        default:
        cout<<"Enter a valid choice\n";
        goto label;
        break;
    }
    return f;
}

int Temp::checkuser()
{
    string x;
    cout<<"Enter your user id\n";
    cin>>x;

    int index=-1;
    int n = user_obj.getnoofusers();
    for(int i=0;i<n;i++)
    {
        if(User[i].getuserid()==x)
        {
            index=i;
            break;
        }
    }
    return index;
}

void Temp::itemborrow()
{
    int f1 = checkuser();
    if(f1==-1) 
    {
        cout<<"Invalid UserID !!! \n Register as a new User\n";
        return ;
    }

    emptysearchresults();
    bool f2 = searchitem();
    if(!f2) 
    {
        ofstream file("BorrowBooks.txt",ios::app);
        if(xy==0)
        {
            string name,isbn,author;
            cout<<"Enter name of the book\n";
            getchar();
            getline(cin,name);
            cout<<"Enter author of the book\n";
            getline(cin,author);
            cout<<"Enter isbn of the book\n";
            cin>>isbn;
            file << name <<","<<author<<","<<isbn<<"\n";

            User[f1].issuebook(name);
        }
        else if(xy==1)
        {
            string name;
            cout<<"Enter name of the magazine\n";
            getchar();
            getline(cin,name);
            file << name<<"\n";
            
            User[f1].isu_mag(name);
        }
        else
        {
            string name;
            cout<<"Enter name of the journal\n";
            getchar();
            getline(cin,name);
            file << name << "\n";
        }
        file.close();
        return ;
    }

    if(result>1)
    {
        int key;
        cout<<"Which one of the books you want to borrow \n";
        cout<<"Press digits from 1 to "<<result<<" to borrow the i th book\n";
label:        cin>>key;

        while(key<=0 || key>result)
        {
            cout<<"Enter a valid item selection number\n";
            goto label;
        }
        
        User[f1].issuebook(searchresults[key-1]);
        
        int x = book_obj.book_no();
        for(int i=0;i<x;i++)
        {
            if(B[i].gettitle()==searchresults[key-1])
            {
                int y = B[i].getitemcount();
                y--;
                B[i].setitemcount(y);
                break;
            }
        }
    }
    else{

        if(xy==0) 
        {
            User[f1].issuebook(searchresults[0]);
            int x = book_obj.book_no();
            for(int i=0;i<x;i++)
            {
                if(B[i].gettitle()==searchresults[0])
                {
                    int y = B[i].getitemcount();
                    y--;
                    B[i].setitemcount(y);
                    break;
                }
            }
        }
        else if(xy==1) 
        {
            User[f1].isu_mag(searchresults[0]);
            int x = magazine_obj.Cou_mag();
            for(int i=0;i<x;i++)
            {
                if(M[i].gettitle()==searchresults[0])
                {
                    int y = M[i].getitemcount();
                    y--;
                    M[i].setitemcount(y);
                    break;
                }
            }
        }
        else
        {
            User[f1].issuejournal(searchresults[0]);
        }
    }

    

}

void Temp::AddUser()
{
    string id;
    string name;
    bool type;
    string profession;
    cout<<"Enter your name: ";
    getchar();
    getline(cin,name);

    cout<<"Enter your profession - Student or a faculty .\n";
    cin>>profession;

    transform(profession.begin(), profession.end(), profession.begin(), ::tolower);

    if(profession=="student")
    type = 0;  // for student use 0
    else
    type = 1;   // for faculty use 1
    int x = user_obj.getnoofusers();
    x++; 
    id = "User" + to_string(x);
    LibraryUser lu = LibraryUser(name,type,id);
    User[x-1] = lu;
    user_obj.setusercount(x);

    cout<<"Your User ID is "<<id<<"\n";
}

void Temp::showuser()
{
    int x = user_obj.getnoofusers();
    for(int i=0;i<x;i++)
    {
        cout<<"Name : "<<User[i].getname()<<"\n";
        cout<<"Type : "<<User[i].gettype()<<"\n";
        cout<<"USER ID : "<<User[i].getuserid()<<"\n";
        User[i].DisplayUserBorrowInfo();
    }

}

void emptysearchresults()
{
    for(int i=0;i<result;i++)
    searchresults[i].clear();

    result=0;
}

void Temp::AddBook()
{
    string pwd;
    cout<<"For Adding New Book to the library , Enter Admin Password\n";
    cin>>pwd;

    if(pwd!="Dhruv")
    {
        cout<<"Password entered is wrong\n";
        return;
    }

    string name,author,isbn;
    cout<<"Enter Book name\n";
    getchar();
    getline(cin,name);
    cout<<"Enter Author name\n";
    getline(cin,author);
    cout<<"Enter isbn\n";
    cin>>isbn;

    int x = book_obj.book_no();
    string id = "BK" + to_string(x);

    Book b(id,100,1,author,isbn,x,name);
    B[x++] = b;
    book_obj.setnoofbooks(x);
}

int main()
{
    Temp t;
    t.loadfile();
    t.load_mag_jour();

    while(1)
    {
        int key;
        cout<<"Press 1 to display items\n";
        cout<<"Press 2 to search for an item\n";
        cout<<"Press 3 to borrow item\n";
        cout<<"Press 4 for buy book\n";
        cout<<"Press 5 for show user\n";
        cout<<"Press 6 for add user\n";
label:  cin>>key;

        switch(key)
        {
            case 1:
                t.show_item();
                break;
            case 2:
                emptysearchresults();
                t.searchitem();
                break;
            case 3:
                t.itemborrow();
                break;
            case 4:
                t.AddBook();
                break;
            case 5:
                t.showuser();
                break;
            case 6:
                t.AddUser();
                break; 
            default:
                cout<<"Press a valid key\n";
            goto label;
            break;
        }

        char valu;
        cout<<"Press Y for continue or any other key for exit\n";
        cin>>valu;
        if(valu!='y' && valu!='Y')
        break;

    }

    return 0;
}