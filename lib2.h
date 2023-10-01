#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
using namespace std;

void debug()
{
    cout<<"Dhruv\n";
}

string getdatetime()
{
    time_t now = time(0);
    string x = ctime(&now);
    return x;
}


string searchresults[100];
int result = 0;
int xy = -1;

void emptysearchresults();

class ITems{
    private:
    int items_count;
    string item_id;
    public:
    ITems(){}
    ITems(const std::string& id, int itemcount) : item_id(id), items_count(itemcount) {
        setitemcount(itemcount);
    }

    string GetIdentifier() {
        return item_id;
    }
    int getitemcount()
    {
        return items_count;
    }
    void setitemcount(int x)
    {
        items_count = x;
    }
    string gettitle()
    {
        return item_id;
    }

};

string getdatetimeafter7Days() {
    // Get the current system time
    auto currentTime = std::chrono::system_clock::now();

    // Add 7 days (7 * 24 hours)
    std::chrono::duration<int> sevenDays(7 * 24 * 60 * 60);  // 7 days in seconds

    // Calculate the time after 7 days
    auto newTime = currentTime + sevenDays;

    // Convert to time_t for formatting
    std::time_t newTimeC = std::chrono::system_clock::to_time_t(newTime);

    // Convert to string in a specific format (e.g., "YYYY-MM-DD HH:MM:SS")
    std::string formattedDateTime = std::ctime(&newTimeC);
    formattedDateTime.pop_back();  // Remove the newline character

    return formattedDateTime;
}


class PhysicalItem : public ITems {
protected:
    int duration; // in days

public:
    PhysicalItem(){}
    PhysicalItem(const std::string& id, int& itemcount, int duration) : ITems(id, itemcount), duration(duration) {
        //setitemcount(itemcount);
    }

    int getDuration() {
        return duration;
    }
};

class ElectronicITems : public ITems {
public:
    ElectronicITems(){}
    ElectronicITems(const std::string& itemid,int item_count) : ITems(itemid, 10000) {}

    bool isReturnRequired() const {
        return false;  // Electronic items don't need to be returned
    }
};

class Book : public PhysicalItem {
    private:
    int location;
    string title;
    string author;
    string ISBN;
    int noofbooks {0};
    public:
    Book(){}
    Book(const string& id, int itemcount, int duration,string x,string y,int l,string z)
        : PhysicalItem(id, itemcount, duration),author(x),ISBN(y),location(l),title(z) {   
        }
    
    int book_no()
    {
        return noofbooks;
    }
    void setnoofbooks(int x)
    {
        noofbooks = x;
    }
    string gettitle()
    {
        return title;
    }
    string getauthor()
    {
        return author;
    }
    string getisbn()
    {
        return ISBN;
    }
    int getlocation()
    {
        return location;
    }
    // void getInfo() const override {
    //     std::cout << "Book Title: " << title << "\nAuthor: " << author << "\nISBN: " << ISBN << std::endl;
    // }
};

class Magazine : public PhysicalItem {
    int noofmagazines {0};
    int location;
public:
    Magazine (){}
    Magazine(const std::string& id, int count, int duration,int l)
        : PhysicalItem(id, count, duration) ,location(l) {}

    void set_Mag(int x)
    {
        noofmagazines = x;
    }
    int Cou_mag()
    {
        return noofmagazines;
    }
    int getlocation()
    {
        return location;
    }
    // void getMagazineInfo() {
    //     getInfo();
    //     std::cout << "Type: Magazine, Duration: " << duration << " days\n";
    // }
};

class Journal : public ElectronicITems  {
    int noofjournals {0};
public:
    Journal (){}
    Journal(const std::string& title, int count)
        : ElectronicITems (title, count) {}

    int getnoofjournals()
    {
        return noofjournals;
    }
    void setnoofjournals(int x)
    {
        noofjournals = x;
    }
    // bool isReturnRequired() override {
    //     return false;
    // }

    // void getJournalArticleInfo() {
    //     getInfo();
    //     std::cout << "Type: Journal Article\n";
    // }
};

// USer Class
class LibraryUser{
    private:

    // user details
    string name;
    bool type;
    int user_count {0} ;
    string user_id;

    string ubook[20][2]; // [0] reperesents book id [1] represents issue date
    string umagazine[20][2];
    string ujournal[20];

    int books_issued {0};
    int magazine_issued {0};
    int journal_issued {0};


    public:

    // constructors
    LibraryUser(){}
    LibraryUser(string name,bool type,string uid)
    {
        this->name = name;
        this->type = type;
        this->user_id = uid;
    }

    // member functions
    void DisplayUserBorrowInfo()
    {
        cout<<"ITEMs Issued\n";
        for(int i=0;i<books_issued;i++)
        {
            cout<<ubook[i][0]<<"\n";
            cout<<ubook[i][1]<<"\n";
        }

        for(int i=0;i<magazine_issued;i++)
        {
            cout<<umagazine[i][0]<<"\n";
            cout<<umagazine[i][1]<<"\n";
        }

        for(int i=0;i<journal_issued;i++)
        cout<<ujournal[i]<<"\n";

    }
    string getname()
    {
        return name;
    }
    string getuserid()
    {
        return user_id;
    }
    string gettype()
    {
        if(type==0)
        return "Student";
        else
        return "Faculty";
    }
    void setusercount(int x)
    {
        user_count = x;
    }
    int getnoofusers()
    {
        return user_count;
    }
    int getbooksissued()
    {
        return books_issued;
    }
    int getmagazinesissued()
    {
        return magazine_issued;
    }
    int getjournalsissued()
    {
        return journal_issued;
    }
    void assignuserid(int x)
    {
        user_id = x;
    }
    void issuebook(string id)
    {
        int x = books_issued;
        ubook[x][0] = id;
        ubook[x][1] = getdatetime();
        books_issued++;
    }
    void isu_mag(string id)
    {
        int x = magazine_issued;
        umagazine[x][0] = id;
        umagazine[x][1] = getdatetime();
        magazine_issued++;
    }
    void issuejournal(string id)
    {
        ujournal[journal_issued++] = id;
    }
    
    
};

class Temp
{

    Book B[150],book_obj;
    Magazine M[150],magazine_obj;
    Journal J[150],journal_obj;
    LibraryUser User[100],user_obj;

    public:

    Temp(){}
    
    void loadfile();
    void load_mag_jour();

    void show_item();
    void showbook();
    void showmagazine();
    void show_journal();
    
    bool searchitem();
    bool searchbook();
    bool searchmagazine();
    bool searchjournal();

    void itemborrow();

    void AddUser();
    void showuser();
    int checkuser();

    void AddBook();
};


