#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "lib2.h"
using namespace std;

string fre[1000];
int f_count = 0;


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

void getfrequentjournals()
{
    ifstream file("Searchjournalhistory.txt");
    string line;

    int line_no = 0;
    while(getline(file,line))
    {
        if(line_no==0)
        {
            fre[f_count++] = line;
        }
        else
        {
            bool f=0;
            for(int i=0;i<f_count;i++)
            {
                f = f | (fre[i]==line);
            }
            if(!f)
            fre[f_count++] = line;
        }
    }
    file.close();
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
    cout<<"Press 1 to display books\n";
    cout<<"Press 2 to display magazines\n";
    cout<<"Press 3 to display journals\n";

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
        cout<<"Enter a valid choice\n";
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
    cout<<"No Journal found with the given title\n";
    file.close();
    return f;
}

bool Temp:: searchbook()
{
    xy = 0;
    //opening file to save search history
    ofstream  file("Searchbookhistory.txt");
    int x = book_obj.book_no();
    int key;
    cout<<"Press 1 to search by Title\n";
    cout<<"Press 2 to search by Author\n";
    cout<<"Press 3 to search by ISBN\n";
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
    return ;

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

// class JournalSubscriptionRequest {
// public:
//     JournalSubscriptionRequest() : journalTitle(""), subscriptionYear(0), cost(0) {}
//     JournalSubscriptionRequest(string title, int year, double cost)
//         : journalTitle(title), subscriptionYear(year), cost(cost) {}

//     double getCost() const {
//         return cost;
//     }

//     string getJournalTitle() const {
//         return journalTitle;
//     }

//     int getSubscriptionYear() const {
//         return subscriptionYear;
//     }

// private:
//     string journalTitle;
//     int subscriptionYear;
//     double cost;
// };


// class Institute {
// public:
//     Institute() : budget(1000), currentYear(2023) {}

//     void setBudget(double budget) { this->budget = budget; }
//     void setCurrentYear(int year) { this->currentYear = year; }

//     double getRemainingBudget() const { return budget - getTotalSubscriptionCost(); }

//     void addJournalSubscriptionRequest(string journalTitle, int year, double cost) {
//         JournalSubscriptionRequest request(journalTitle, year, cost);
//         if (subscriptionRequestCount < 1000) {
//             subscriptionRequests[subscriptionRequestCount] = request;
//             subscriptionRequestCount++;
//         } else {
//             cout << "Error: Maximum subscription request limit reached." << endl;
//         }
//     }

//     void makeSubscriptionDecisions() {
//         sort(subscriptionRequests, subscriptionRequests + subscriptionRequestCount, [](const JournalSubscriptionRequest& a, const JournalSubscriptionRequest& b) {
//             return a.getCost() > b.getCost();
//         });

//     void subscribeJournals(Institute& institute)
//     {
//         string journalTitle;
//         int subscriptionYear;
//         double cost;

//         cout << "Enter journal title: ";
//         cin.ignore();
//         getline(cin, journalTitle);

//         cout << "Enter subscription year: ";
//         cin >> subscriptionYear;

//         cout << "Enter subscription cost: ";
//         cin >> cost;

//         institute.addJournalSubscriptionRequest(journalTitle, subscriptionYear, cost);
//     }

    



//         for (int i = 0; i < subscriptionRequestCount; i++) {
//             const JournalSubscriptionRequest& request = subscriptionRequests[i];
//             if (getRemainingBudget() >= request.getCost()) {
//                 if (subscribedJournalCount < 1000) {
//                     subscribedJournals[subscribedJournalCount] = request;
//                     cout << "Subscribed to journal '" << request.getJournalTitle() << "' for year " << request.getSubscriptionYear() << " for $" << request.getCost() << endl;
//                     budget -= request.getCost();
//                     subscribedJournalCount++;
//                 } else {
//                     cout << "Error: Maximum subscribed journal limit reached." << endl;
//                 }
//             } else {
//                 cout << "Insufficient budget to subscribe to journal '" << request.getJournalTitle() << "' for year " << request.getSubscriptionYear() << endl;
//             }
//         }

//         subscriptionRequestCount = 0;
//     }

//     void listSubscribedJournals() {
//         cout << "Subscribed Journals for Year " << currentYear << ": ";
//         for (int i = 0; i < subscribedJournalCount; i++) {
//             cout << subscribedJournals[i].getJournalTitle() << " ";
//         }
//         cout << endl;
//     }

//     int getCurrentYear() const {
//         return currentYear;
//     }

// private:
//     double budget;
//     int currentYear;
//     JournalSubscriptionRequest subscriptionRequests[1000];
//     JournalSubscriptionRequest subscribedJournals[1000];
//     int subscriptionRequestCount = 0;
//     int subscribedJournalCount = 0;

//     double getTotalSubscriptionCost() const {
//         double totalCost = 0;
//         for (int i = 0; i < subscriptionRequestCount; i++) {
//             totalCost += subscriptionRequests[i].getCost();
//         }
//         return totalCost;
//     }
// };

class JournalSubscriptionRequest {
public:
    JournalSubscriptionRequest() : journalTitle(""), subscriptionYear(0), cost(0) {}
    JournalSubscriptionRequest(std::string title, int year, double cost)
        : journalTitle(title), subscriptionYear(year), cost(cost) {}

    double getCost() const {
        return cost;
    }

    std::string getJournalTitle() const {
        return journalTitle;
    }

    int getSubscriptionYear() const {
        return subscriptionYear;
    }

private:
    std::string journalTitle;
    int subscriptionYear;
    double cost;
};

class Institute {
public:
    Institute() : budget(1000), currentYear(2023) {}

    void setBudget(double budget) { this->budget = budget; }
    void setCurrentYear(int year) { this->currentYear = year; }

    double getRemainingBudget() const { return budget - getTotalSubscriptionCost(); }

    void addJournalSubscriptionRequest(std::string journalTitle, int year, double cost) {
        JournalSubscriptionRequest request(journalTitle, year, cost);
        if (subscriptionRequestCount < 1000) {
            subscriptionRequests[subscriptionRequestCount] = request;
            subscriptionRequestCount++;
        } else {
            std::cout << "Error: Maximum subscription request limit reached." << std::endl;
        }
    }

    void makeSubscriptionDecisions() {
        std::sort(subscriptionRequests, subscriptionRequests + subscriptionRequestCount, [](const JournalSubscriptionRequest& a, const JournalSubscriptionRequest& b) {
            return a.getCost() > b.getCost();
        });

        for (int i = 0; i < subscriptionRequestCount; i++) {
            const JournalSubscriptionRequest& request = subscriptionRequests[i];
            if (getRemainingBudget() >= request.getCost()) {
                if (subscribedJournalCount < 1000) {
                    subscribedJournals[subscribedJournalCount] = request;
                    std::cout << "Subscribed to journal '" << request.getJournalTitle() << "' for year " << request.getSubscriptionYear() << " for $" << request.getCost() << std::endl;
                    budget -= request.getCost();
                    subscribedJournalCount++;
                } else {
                    std::cout << "Error: Maximum subscribed journal limit reached." << std::endl;
                }
            } else {
                std::cout << "Insufficient budget to subscribe to journal '" << request.getJournalTitle() << "' for year " << request.getSubscriptionYear() << std::endl;
            }
        }

        subscriptionRequestCount = 0;
    }

    void listSubscribedJournals() {
        std::cout << "Subscribed Journals for Year " << currentYear << ": ";
        for (int i = 0; i < subscribedJournalCount; i++) {
            std::cout << subscribedJournals[i].getJournalTitle() << " ";
        }
        std::cout << std::endl;
    }

    int getCurrentYear() const {
        return currentYear;
    }

private:
    double budget;
    int currentYear;
    JournalSubscriptionRequest subscriptionRequests[1000];
    JournalSubscriptionRequest subscribedJournals[1000];
    int subscriptionRequestCount = 0;
    int subscribedJournalCount = 0;

    double getTotalSubscriptionCost() const {
        double totalCost = 0;
        for (int i = 0; i < subscriptionRequestCount; i++) {
            totalCost += subscriptionRequests[i].getCost();
        }
        return totalCost;
    }
};




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
    //GetUserInfo(name,type);
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
        //cout<<"Books issued\n";
        //cout<<User[i].getbooksissued()<<"\n";
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
    Institute myInstitute;
    
    while(1)
    {
        int key;
        cout<<"Press 1 to display items\n";
        cout<<"Press 2 to search for an item\n";
        cout<<"Press 3 to borrow item\n";
        cout<<"Press 4 for buy book\n";
        cout<<"Press 5 for show user\n";
        cout<<"Press 6 for add user\n";
        cout<< "Press 7 to request for journal\n"; 
        cout<< "Press 8 to check the condition:\n";
        cout<< "Press 9 To print \n";


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
            case 7:
                //t.subscribeJournals(institute); // Call the method to subscribe to journals
                //myInstitute.setBudget(10000.0); // Set your budget
                //myInstitute.setCurrentYear(2023); // Set the current year
                // myInstitute.addJournalSubscriptionRequest("Journal Title 1", 2023, 500.0);
                // myInstitute.makeSubscriptionDecisions();
                if (myInstitute.getCurrentYear() == 0) {
                    cout << "Please set the current year first." << endl;
                } else {
                    cout << "Enter journal title: ";
                    string journalTitle;
                    cin >> journalTitle;
                    getline(cin, journalTitle);
                    cout << "Enter cost: $";
                    double cost;
                    cin >> cost;
                    cin.ignore();
                    myInstitute.addJournalSubscriptionRequest(journalTitle, myInstitute.getCurrentYear(), cost);
                    cout << "Journal subscription request added for year " << myInstitute.getCurrentYear() << endl;
                }
                break;

            case 8:
                if (myInstitute.getCurrentYear() == 0) {
                    cout << "Please set the current year first." << endl;
                } else {
                    myInstitute.makeSubscriptionDecisions();
                    cout << "Subscription decisions made for year " << myInstitute.getCurrentYear() << endl;
                }
                break;

            case 9 :
                myInstitute.listSubscribedJournals();
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