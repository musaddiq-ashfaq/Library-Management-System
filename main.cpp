#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
class Library_database;//declaring to make association with Account class
class Account
{
    Library_database *ptr;//making 1 to many association of account and Library_database class
public:
    int no_borrowed_books,no_reserved_books,no_returned_books,no_lost_books,fine_amount;
    int Calculate_fine();//function to calculate fine of user
};
class Book;//declaring Book class to make its association with Librarian class
class Librarian
{
    Book *ptr[1000];//making 1 to many association(Books in library 1000)
public:
    bool verify_librarian();//function to identify librarian
    void Search();//function to facilitate librarian to check an user account
private:
    string Name,ID,Password,SearchString;
};
class User;//declaring to make association with Book class
class Library_database;//declaring to make association with Book class
class Book
{
    User *ptr[800];//making many to many association(800 users of library)
    Librarian *ptr2;//making 1 to many association
    Library_database *ptr3;//making 1 to many association
public:
    void show_duedt(),Reservation_status(),Feedback(),Book_request(),Renw_info();
    string Title,Author,ISBN,Publication;
};
class User
{
    Book *ptr[1000];//making many to many association with book class(10000 books in library)
public:
    string Name,ID;
    Account account_obj;//making object of Account class in User class for composition
    bool Verify();//function to identify user
    void CheckAccount();//function to check user account
    void get_book_info(string Name);//function to show the books of a specific department
};
class Library_Management_System//class to login,logout and for registration of user
{
public:
    string Password,UserType;
    User user_object;//making aggregation with user class
    string UserName;
    Librarian librarian_obj;//making aggregation with librarian class
    Book book_obj;//making aggregation with Book class
    void login();//function to login to library portal
    void Registar();//function to register an account in library
    bool logout();//function to logout from library portal
};
class Library_database//class accessed by librarian for organization of books
{
    Book *ptr[1000];//making 1 to many association(1000 books in library)
    Account *ptr1[800];//making 1 to many association
public:
    string List_of_books;
    void Add(),Delete(),update(),Display(),Search();
    Book book_obj;//making object of book class to access its members
};
class staff:public User//child class staff inherited from User base class
{
public:
    string Dept;
};
class Student:public User
{
public:
    string Class;
};
int a=0;//Global variable declared for increment in different functions
fstream file;//Global file obj for file handling
string f[1000];//Global string array for file handling
int main()
{

    cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    cout<<"|                                                                                                 |\n";
    cout<<"*                                                                                                 *\n";
    cout<<"|                                     LIBRARY APP                                                 |\n";
    cout<<"*                                                                                                 *\n";
    cout<<"|                                                                                                 |\n";
    cout<<"*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n";
    Library_Management_System obj;//making object of Library_Management_System class
    Library_database obj2;
    string choice;
//if user doesn't want to logout then again start the program
label:
    {
        cout<<"\nWelcome to Library Catalogue \n";
        cout<<"\n\t\t\t _____________________________________________\n\n";
        cout<<"\t\t\t|              1-Login                         |\n";
        cout<<"\t\t\t|              2-Register                      |\n";
        cout<<"\t\t\t|              3-Logout                        |\n";
        cout<<"\t\t\t _____________________________________________\n\n";
        cout<<"Enter your choice(1,2,3) : ";
        getline(cin,choice);
        if(choice=="1")
        {
            obj.login();//If user enters 1 then show Login portal
        }
        else if(choice=="2")
            obj.Registar();//If user enters 2 then show start registration process
        else if(choice=="3")
        {
            if(obj.logout()==0)//If user enters 2 then ask if he/she wanted to logout or not
            {
                system("cls");
                goto label;//If user doesn't want to logout then again show the home screen
            }
        }
        else//if user entered wrong keyword then again show the home screen
        {
            system("cls");//Used to clear screen
            cout<<"Error: Wrong input!! Enter correct keyword.";
            goto label;//point to home screen
        }
    }
    if(obj.UserType=="True")//If Librarian Identification is true then it is accessed by librarian
    {
        do//loop will repeat until user logout
        {
            system("pause");//command to pause code until user enter any keyword
            system("cls");
            cout<<"\t\t\t*****Librarian Portal*****\n\n";
            cout<<"1-Add Record   \t\t2-Delete Record\n";
            cout<<"3-Update Record\t\t4-Display\n5-Search book\n6-Search Library member record\n";
            cout<<"7-Logout\n\n";
            cout<<"Enter the keyword of your desired work(1-7) : ";
            a=0;//set value of a, zero
label1://form repetition until librarion doesn't log out
            getline(cin,choice);
            if(choice=="1")
                obj2.Add();//add books
            else if(choice=="2")
                obj2.Delete();//delete book records
            else if(choice=="3")
                obj2.update();//update book record
            else if(choice=="4")
                obj2.Display();//to show all books of library
            else if(choice=="5")
                obj2.Search();//to search a specific book
            else if(choice=="6")
                obj.librarian_obj.Search();//to search a library member(librarian class obj is in LibraryManagement class)
            else if(choice=="7")
            {
                system("cls");
                if(obj.logout())//to ensure logout command
                    a++;
            }
            else//
            {
                cout<<"Error: Wrong input!! Kindly choose between 1 to 7 \n";
                goto label1;
            }
        }
        while(a==0);//if user doesn't want to log out then a=0
    }
    return 0;
}

int Account::Calculate_fine()//To calculate fine of a user
{
    fine_amount=(no_lost_books*500)+fine_amount;
    return fine_amount;
}
void Library_Management_System::login()
{
    Student obj;
    staff obj2;
    a=0;
label:
    {
        cout<<"Library Memberships:\n\n\t\t1-Student\n\t\t2-Faculty\n\t\t3-Librarian\n\n";
        cout<<"Enter your membership(1,2,3) : ";
        getline(cin,UserType);
        if(UserType=="1" || UserType=="2")
        {
            if(user_object.Verify()==1)
            {
label3:
                {
                    if(UserType=="1")
                    {
                        cout<<"\n\t\tEnter your department(EE,CS,MATH,BBA) : ";
                        getline(cin,obj.Class);
                    }
                    if(UserType=="2")
                    {
                        cout<<"\n\t\tEnter your department(EE,CS,MATH,BBA) : ";
                        getline(cin,obj2.Dept);
                    }
                    if(obj2.Dept=="EE"||obj2.Dept=="CS"||obj2.Dept=="MATH"||obj2.Dept=="BBA"||obj.Class=="EE"||obj.Class=="MATH"||obj.Class=="CS"||obj.Class=="BBA")
                    {

                    }
                    else
                    {
                        cout<<"\nError: Wrong input!! Please, Enter correct department \n";
                        goto label3;
                    }
                }
label2:
                {
                    do
                    {
                        system("pause");
                        system("cls");
                        cout<<"____________________________________________________________________________________________________\n\n";
                        cout<<"                                  Library Account\n";
                        cout<<"____________________________________________________________________________________________________\n\n";
                        cout<<"1-Check Account\t\t\t2-Your Department books\n3-Reservation Status\t\t4-Show due dates of your reserved books\n5-Renew book\t\t\t"
                            <<"6-Book request\n7-Book feedback\t\t\t8-Logout\n\n";
                        cout<<"Enter code of your desired work : ";
                        getline(cin,Password);//storing in it to shorten program size
                        if(Password=="1")
                        {
                            system("cls");
                            user_object.CheckAccount();
                        }
                        else if(Password=="2")
                        {
                            if(UserType=="1")
                                user_object.get_book_info(obj.Class);

                            else if(Password=="2")
                                user_object.get_book_info(obj2.Dept);
                        }

                        else if(Password=="3")
                            book_obj.Reservation_status();
                        else if(Password=="4")
                            book_obj.show_duedt();
                        else if(Password=="5")
                            book_obj.Renw_info();
                        else if(Password=="6")
                            book_obj.Book_request();
                        else if(Password=="7")
                            book_obj.Feedback();
                        else if(Password=="8")
                        {
                            system("cls");
                            if(logout())
                                a++;
                        }
                        else
                        {
                            system("cls");
                            cout<<"Error: Wrong input, Choose correct keyword(1-7)\n\n";
                            goto label2;
                        }
                    }
                    while(a==0);

                }
            }
            else
            {
                cout<<"Error: Wrong ID!! Do you want to login again(y/n) ? ";
                getline(cin,UserType);//storing in it to shorten program size
                if(UserType=="y")
                    goto label;
            }
        }
        else if(UserType=="3")
        {
            if(librarian_obj.verify_librarian()==1)
            {
                UserType="True";
            }

        }
        else
        {
            cout<<"Error: Wrong input!! Do you want to login again(y/n) ? ";
            getline(cin,UserType);
            if(UserType=="y")
                goto label;
        }
    }
}
bool Library_Management_System::logout()//function to logout any time
{
    cout<<"Are you sure to logout(y/n) : ";
    getline(cin,Password);//storing in this variable to shorten the program size
    if(Password=="y")//if user want then log out process will complete
    {
        cout<<"\n\t\t\tLogout Successfully!!\n\n";
        return true;
    }
    else//to tell that user doesn't want to log out
        return false;
}
void Library_Management_System::Registar()//to make account in library
{
    file.open("Login_Detection.csv",ios::out|ios::app);//file open for write and append
    system("cls");
    cout<<"\t\t\t\t*****Registration Portal*****\n\n";
    cout<<"\t\tEnter your Name : ";
    getline(cin,UserName);
    cout<<"\t\tPassword : ";
    getline(cin,Password);
    cout<<"\nLibrary Memberships:\n\n\t\t1-Student\n\t\t2-Faculty\n\n";
label://repeat until user enter correct keyword
    cout<<"Enter your post(1,2) : ";
    getline(cin,UserType);
    if(UserType=="1" || UserType=="2")//to specify student and faculty
    {
        cout<<"\t\tEnter your Email ID : ";
        getline(cin,UserType);
        cout<<"\n\tRegistration Completed Successfully!! Now you are a member of Library.\n\n";
        file<<UserName<<","<<Password<<","<<UserType<<",0,0,0,0,0"<<endl;
    }
    else//to signify wrong input
    {
        cout<<"\nError:Wrong input!! Enter again\n\n";
        goto label;
    }
    file.close();
}
void User::CheckAccount()//to check Library account
{
    file.open("Login_Detection.csv",ios::in);//open file for reading
    for(int i=1; !file.eof(); i++) //loop to detect the user is a member of library or not
    {
        for(int j=i; j<i+7; j++)
        {
            getline(file,f[j],',');
        }
        getline(file,f[i+7],'\n');
        if(Name==f[i])
        {
            //converting strings to int variables
            account_obj.no_borrowed_books=atoi(f[i+3].c_str());
            account_obj.no_reserved_books=atoi(f[i+4].c_str());
            account_obj.no_returned_books=atoi(f[i+5].c_str());
            account_obj.no_lost_books=atoi(f[i+6].c_str());
            account_obj.fine_amount=atoi(f[i+7].c_str());
        }
        i=i+7;//one row contain eight columns in file so next time next row
    }
    cout<<"\n\t\t\t_______________________________________________________________\n\n";
    cout<<"\t\t\t|                  ****(Account Details)****                         \n";
    cout<<"\t\t\t|    1-No. of Borrowed Books = "<<account_obj.no_borrowed_books<<endl;
    cout<<"\t\t\t|    2-No. of Reserved Books = "<<account_obj.no_reserved_books<<endl;
    cout<<"\t\t\t|    3-No. of Returned Books = "<<account_obj.no_returned_books<<endl;
    cout<<"\t\t\t|    4-No. of Lost Books = "<<account_obj.no_lost_books<<endl;
    cout<<"\t\t\t|    5-Fine amount = "<<account_obj.Calculate_fine()<<endl;
    cout<<"\n\t\t\t_______________________________________________________________\n";
    file.close();
}
bool User::Verify()
{
    string password;
    cout<<"\t\tEnter your Name : ";
    getline(cin,Name);
    cout<<"\t\tEnter your Email ID : ";
    getline(cin,ID);
    cout<<"\t\tEnter your Password : ";
    getline(cin,password);
    fstream file;
    file.open("Login_Detection.csv",ios::in);
    for(int i=1; !file.eof(); i++) //loop to detect the user is a member of library or not
    {
        for(int j=i; j<i+7; j++)
        {
            getline(file,f[j],',');
        }
        getline(file,f[i+7],'\n');
        i=i+7;
    }
    for(int i=1; i<200; i++) //loop to detect the user is a member of library or not
    {
        if(Name==f[i] && password==f[i+1] && ID==f[i+2])
        {
            cout<<"Login Successfully \n\n";
            return 1;
        }
        i=i+7;
    }
    return 0;
}
void Book::show_duedt()//show the due date of reserved books
{
    User obj;
    a=0;//setting value of a, zero
    cout<<"Enter your email ID to check your reserved books : ";
    cin>>obj.ID;
    file.open("books.csv",ios::in);//open file to read
    for(int i=0; !file.eof(); i++)//loop to read from file
    {
        getline(file,f[i],',');
        getline(file,f[i+1],',');
        getline(file,f[i+2],'\n');
        i=i+2;//one row contain 3 columns filled so next time next row will be called
    }
    for(int i=0; i<100; i++)//loop to detect the user has any reserved book or not
    {
        if(obj.ID==f[i])//Identify that ID exist or not
        {
            cout<<"\nReserver ID : "<<f[i]<<"\nBook : "<<f[i+1]<<"\nDue date(Days Left) : "<<f[i+2]<<endl;
            a++;
        }
        i=i+2;
    }
    if(a==0)//Clearify that user have not any reserved book
        cout<<"\n\t\tYou haven't any reserved book \n";
        a=0;
}

bool Librarian::verify_librarian()
{
    string k,l,m;
    cout<<"\t\tEnter your Name : ";
    getline(cin,Name);
    cout<<"\t\tEnter your Email ID : ";
    getline(cin,ID);
    cout<<"\t\tEnter your Password : ";
    getline(cin,Password);
    file.open("Librarian_Detection.csv",ios::in);
    while(!file.eof())//loop to detect the user is a member of library or not
    {
        getline(file,k,',');
        getline(file,l,',');
        getline(file,m,'\n');
        if(Name==k && Password==l && ID==m)//to identify user
        {
            cout<<"Login Successfully \n\n";
            file.close();
            return 1;

        }
    }
    file.close();//close the opened file
    return 0;
}
void Library_database::Add()//to add a book record
{
    // opens an existing csv file or creates a new file
    file.open("DATABASE.csv", ios::out | ios::app);
    string a,b,c,d;
    cout<<"Enter details of book : \n\n";
    cout<<"Name = ";
    getline(cin,book_obj.Title);
    cout<<"Author = ";
    getline(cin,book_obj.Author);
    cout<<"ISBN = ";
    getline(cin,book_obj.ISBN);
    cout<<"Publication = ";
    getline(cin,book_obj.Publication);
    // Insert the data to file
    file<<book_obj.Title<<","<<book_obj.Author<<","<<book_obj.ISBN<<","<<book_obj.Publication<<","<<"n"<<","<<"good book"<<endl;
    cout<<"\nBook data saved successfully \n";
    file.close();
}
void Library_database::Delete()
{
    fstream fin, fout;
    fin.open("DATABASE.csv", ios::in);// Open the existing file to read
    fout.open("DATABASEnew.csv", ios::out);// Create a new file to store the non-deleted data
    vector<string> row;
    cout << "\nEnter the name of book to be deleted : ";
    getline(cin,book_obj.Title);
    // Check if this record exists, If exists, leave it and add all other data to the new file
    while (!fin.eof())
    {
        row.clear();
        getline(fin, book_obj.Publication);
        stringstream s(book_obj.Publication);

        while (getline(s, book_obj.Author, ','))
        {
            row.push_back(book_obj.Author);
        }

        int row_size = row.size();
        // List_of_books = atoi(row[0].c_str());
        // writing all records,
        // except the record to be deleted, into the new file DATABASEnew.csv using fout pointer
        if (row[0] != book_obj.Title)
        {
            if (!fin.eof())
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else
        {
            a = 1;
        }
        if (fin.eof())
            break;
    }
    if (a == 1)//ensure record deletion
        cout << "\n\tRecord deleted\n";
    else
        cout << "\n\tRecord not found\n";
    fin.close();
    fout.close();
    // removing the existing file
    remove("DATABASE.csv");
    // renaming the new file with the existing file name
    rename("DATABASEnew.csv", "DATABASE.csv");
    a=0;
}
void Library_database::update()
{
    cout<<"\t\tEnter book name : ";
    getline(cin,List_of_books);
    file.open("DATABASE.csv",ios::in);//open file to read
    for(int i=1; !file.eof(); i++) //loop to detect the user is a member of library or not
    {
        for(int j=i; j<i+5; j++)
        {
            getline(file,f[j],',');
        }
        getline(file,f[i+5],'\n');
        i=i+5;
    }
    for(int i=1; i<500; i++) //loop to detect the user is a member of library or not
    {
        if(List_of_books==f[i])//identify book exist or not
        {
            fstream fin, fout;
            // Open an existing record
            fin.open("DATABASE.csv", ios::in);
            // Create a new file to store updated data
            fout.open("DATABASEnew.csv", ios::out);
            int index;
            string line, word;
            vector<string> row;
            // Get the roll number from the user
            book_obj.Title=List_of_books;
            // Get the data to be updated
            cout<<"\nWhat do you want to update : \n";
            cout<<"1-Author name\t\t\t2-ISBN\n3-Publication\t\t\t4-Reservation Status\n5-Feedback\n";
            cout << "Enter the serial number of your desire work : ";
            getline(cin,List_of_books);
            if (List_of_books == "1" ) // Determine the index of the subject
                index = 1;
            else if (List_of_books == "2")
                index = 2;
            else if (List_of_books == "3")
                index = 3;
            else if (List_of_books == "4")
                index = 4;
            else if (List_of_books == "5")
                index = 5;
            else
            {
                cout << "Wrong choice.Enter again\n";
                update();//if wrong input then repeat the process
            }
            int count=0;
            cout << "Enter data : ";
            getline(cin,book_obj.ISBN);
            // Traverse the file
            while (!fin.eof())
            {
                row.clear();
                getline(fin, line);
                stringstream s(line);
                while (getline(s,book_obj.Publication, ','))//read from file
                {
                    row.push_back(book_obj.Publication);
                }
                int row_size = row.size();
                if (row[0] == book_obj.Title)//check the record exist or not
                {
                    count = 1;
                    stringstream convert;
                    convert << book_obj.ISBN;// sending a number as a stream into output string
                    row[index] = convert.str();//to convert number into string
                    if (!fin.eof())
                    {
                        for (int i = 0; i < row_size - 1; i++)
                        {
                            // write the updated data into a new file 'reportcardnew.csv using fout
                            fout << row[i] << ",";
                        }
                        fout << row[row_size - 1] << "\n";
                    }
                }
                else
                {
                    if (!fin.eof())
                    {
                        for (int i = 0; i < row_size - 1; i++)
                        {
                            fout << row[i] << ",";// writing other existing records into the new file using fout.
                        }
                        fout << row[row_size - 1] << "\n";// the last column data ends with a '\n'
                    }
                }
                if (fin.eof())
                    break;
            }
            if (count != 0)//check record exist or not
            {
                cout<<"\n\tRecord updated \n";
            }
            if (count == 0)
                cout << "\n\tError:Record not found!!\n";
            fin.close();
            fout.close();
            remove("DATABASE.csv");// removing the existing file
            rename("DATABASEnew.csv", "DATABASE.csv");// renaming the updated file with the existing file name
            a++;
        }
        i=i+5;//one row with six columns data
    }
    if(a==0)//tell if book not found
        cout<<"\n\nSorry!! book not found\n\n";
    a=0;//setting value of a zero to repeat the main menu screen display process
    file.close();
}
void Library_database::Search()//function to search a book
{
    a=0;//setting value of a, zero
    cout<<"\t\tEnter book name : ";
    getline(cin,List_of_books);
    file.open("DATABASE.csv",ios::in);//open file to read
    for(int i=1; !file.eof(); i++) //loop to detect the user is a member of library or not
    {
        for(int j=i; j<i+5; j++)
        {
            getline(file,f[j],',');
        }
        getline(file,f[i+5],'\n');
        i=i+5;
    }
    for(int i=1; i<500; i++) //loop to detect the user is a member of library or not
    {
        if(List_of_books==f[i])//identify book exist or not
        {
            cout<<"\n--------------------------------------------------------------------------------------------\n\n";
            cout<<"Book Name = "<<f[i]<<"\n"
                "Author = "<<f[i+1]<<"\nISBN = "<<f[i+2]<<"\nPublication = "<<f[i+3]<<"\nReservation status = "<<f[i+4]
                <<"\nFeedback = "<<f[i+5]<<"\n";
            cout<<"\n--------------------------------------------------------------------------------------------\n";
            a++;
        }
        i=i+5;//one row with six columns data
    }
    if(a==0)//tell if book not found
        cout<<"\n\nSorry!! book not found\n\n";
    a=0;//setting value of a zero to repeat the main menu screen display process
    file.close();
}
void Library_database::Display()//to display all books record
{
    file.open("DATABASE.csv",ios::in);//open file to read
    for(int i=1; !file.eof(); i++)//loop to read from file
    {
        for(int j=i; j<i+5; j++)
        {
            getline(file,f[j],',');
        }
        getline(file,f[i+5],'\n');
        i=i+5;//one row six columns data
    }
    cout<<"\n----------------------------------------------------------------------------------------------------\n";
    for(int i=1; i<1000; i++)//show the record
    {
        if(f[i+1]=="")
            break;
        cout<<"Book Name = "<<f[i]<<"\n"
            "Author = "<<f[i+1]<<"\nISBN = "<<f[i+2]<<"\nPublication"<<f[i+3]<<"\nReservation status = "<<f[i+4]
            <<"\nFeedback = "<<f[i+5]<<"\n\n";
        if(f[i+1]=="")
            break;
        cout<<"----------------------------------------------------------------------------------------------------\n";
        i=i+5;
    }
    file.close();
}
void Librarian::Search()//to search a library member record
{
    a=0;//set value of a, zero

    cout<<"Enter the name of member you want to search : ";
    getline(cin,SearchString);
    file.open("Login_Detection.csv",ios::in);
    for(int i=1; !file.eof(); i++) //loop to read from file
    {
        for(int j=i; j<i+7; j++)
        {
            getline(file,f[j],',');
        }
        getline(file,f[i+7],'\n');
        i=i+7;
    }
    for(int i=1; i<200; i++) //loop to detect the user is a member of library or not and then show the record
    {
        if(SearchString==f[i])//identify user
        {
            cout<<"\n--------------------------------------------------------------------------------------------\n";
            cout<<"\n\nName = "<<f[i]<<"\nBorrowed books = "<<f[i+3]<<"\nReserved books = "<<f[i+4]
                <<"\nReturned Books = "<<f[i+5]<<"\nBooks lost = "<<f[i+6]<<"\nFine amount = "<<f[i+7]<<endl;
            cout<<"\n--------------------------------------------------------------------------------------------\n\n";
            a++;//if user not found then a=0
        }
        i=i+7;
    }
    if(a==0)//to check record not found
        cout<<"\n\nSorry!! Record not found\n\n";
    a=0;//setting value of a zero to repeat the main menu screen display process
    file.close();
}
void Book::Reservation_status()//to show reserved books of user
{
    a=0;//set value of a, zero
    User obj;//making obj of User class to use its attributes
    cout<<"Enter your email ID to check your reserved books : ";
    getline(cin,obj.ID);
    file.open("Books.csv",ios::in);
    for(int i=0; !file.eof(); i++)//reading from file
    {
        getline(file,f[i],',');
        getline(file,f[i+1],',');
        getline(file,f[i+2],'\n');
        i=i+2;
    }
    for(int i=0; i<200; i++)//identify the specific record
    {
        if(obj.ID==f[i])//show the specific record
        {
            cout<<"\nReservation Status : Yes \n";
            cout<<"\nDetails : ";
            cout<<"\nReserver ID : "<<f[i]<<"\nBook : "<<f[i+1]<<endl;
            a++;//if record not found a remain 0
        }
        i=i+2;
    }
    if(a==0)
        cout<<"\n\n\tNo reserved books found!!\n\n";
    file.close();
    a=0;
}
void Book::Renw_info()//to renew due date of a book
{
    a=0;//set value of a, zero
    User obj;
    cout<<"Enter your email ID to check your reserved books : ";
    getline(cin,obj.ID);
    file.open("books.csv",ios::in);//open file to read
    for(int i=1; !file.eof(); i++)//loop to read from file
    {
        getline(file,f[i],',');
        getline(file,f[i+1],',');
        getline(file,f[i+2],'\n');
        i=i+2;
    }
    for(int i=1; i<100; i++)//to check the user ID
    {
        if(obj.ID==f[i])//identify user ID
        {
            cout<<"Reserved book found : ";
            cout<<"\nBook : "<<f[i+1];
            cout<<"\nDue date(Days Left) : "<<f[i+2];
            cout<<"\n\nDo you want to extend your due date(y/n) : ";
            getline(cin,Title);//storing in Title because no new variables are allowed
            if(Title=="y")
            {
                cout<<"\tDue date is renewed. Now it is available for 14 days \n\n";
                break;
            }
            else
                cout<<"Book date not changed!!\n";
            a++;//if no reserved book found then a remain zero
            break;
        }
        i=i+2;
    }
    if(a==0)//identify user has not any reserved book
        cout<<"\n\t\tYou haven't any reserved book \n";
    file.close();
    a=0;
}
void Book::Book_request()//allow user to ask librarians for a book that isn't available in Library
{
    system("pause");
    system("cls");
    file.open("Book_request.csv",ios::out|ios::app);
    cout<<"\t\t\t*-*-*Book Request*-*-*\n\n";
    cout<<"Book Request portal: You can request for any book that isn't available in library. Your"
        <<" desired book will be available after one month.\n\n";
    cout<<"Enter book name : ";
    getline(cin,Title);
    cout<<"Enter Author's name : ";
    getline(cin,Author);
    file<<Title<<","<<Author<<endl;//store the book record
    cout<<"Thank you, We will get this book for you ASAP!!\n";
    file.close();//close the opened file
}
void Book::Feedback()
{
    system("pause");//wait for user command to proceed
    system("cls");//clear the screen
    fstream fin, fout;
    cout<<"\t\t\t*-*-*Feedback of book*-*-*\n\n";
    // Open an existing record
    fin.open("DATABASE.csv", ios::in);
    // Create a new file to store updated data
    fout.open("DATABASEnew.csv", ios::out);
    int index;
    string line, word;
    vector<string> row;
    cout << "Enter the name of book: ";
    getline(cin,Title);
    index = 5;
    int count=0;
    cout << "\nProvide Feedback : ";
    getline(cin,ISBN);
    // Traverse the file
    while (!fin.eof())
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while (getline(s,Publication, ','))//read from file
        {
            row.push_back(Publication);
        }
        int row_size = row.size();
        if (row[0] == Title)//check the record exist or not
        {
            count = 1;
            stringstream convert;
            convert << ISBN;// sending a number as a stream into output string
            row[index] = convert.str();//to convert number into string
            if (!fin.eof())
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    // write the updated data into a new file 'reportcardnew.csv using fout
                    fout << row[i] << ",";
                }
                fout << row[row_size - 1] << "\n";
            }
        }
        else
        {
            if (!fin.eof())
            {
                for (int i = 0; i < row_size - 1; i++)
                {
                    fout << row[i] << ",";// writing other existing records into the new file using fout.
                }
                fout << row[row_size - 1] << "\n";// the last column data ends with a '\n'
            }
        }
        if (fin.eof())
            break;
    }
    if (count != 0)//check record exist or not
    {
        cout<<"\n\tFeedback added \n";
    }
    if (count == 0)
        cout << "\n\tError:Record not found!!\n";
    fin.close();
    fout.close();
    remove("DATABASE.csv");// removing the existing file
    rename("DATABASEnew.csv", "DATABASE.csv");// renaming the updated file with the existing file name
}
void User::get_book_info(string Name)//function to show specific department books
{
    a=0;//set value of a, zero
    file.open("DATABASE.csv",ios::in);
    for(int i=1; !file.eof(); i++)//reading from file
    {
        for(int j=i; j<i+5; j++)
        {
            getline(file,f[j],',');
        }
        getline(file,f[i+5],'\n');
        i=i+5;//one row six columns, so next time next row
    }
    cout<<"\n----------------------------------------------------------------------------------------------------\n";
    if(Name=="EE")
    {
        for(int i=1; i<30; i++)//show books according of specific department
        {
            cout<<"Book Name = "<<f[i]<<"\n"
                "Author = "<<f[i+1]<<"\nISBN = "<<f[i+2]<<"\nPublication"<<f[i+3]<<"\nReservation status = "<<f[i+4]
                <<"\nFeedback = "<<f[i+5]<<"\n";
            i=i+5;
            cout<<"\n----------------------------------------------------------------------------------------------------\n";
            a++;
        }
    }
    else if(Name=="CS")
    {
        for(int i=31; i<60; i++)//show books according of specific department
        {
            cout<<"Book Name = "<<f[i]<<"\n"
                "Author = "<<f[i+1]<<"\nISBN = "<<f[i+2]<<"\nPublication"<<f[i+3]<<"\nReservation status = "<<f[i+4]
                <<"\nFeedback = "<<f[i+5]<<"\n";
            i=i+5;
            cout<<"\n----------------------------------------------------------------------------------------------------\n";
            a++;
        }
    }
    else if(Name=="MATH")
    {
        for(int i=61; i<90; i++)//show books according of specific department
        {
            cout<<"Book Name = "<<f[i]<<"\n"
                "Author = "<<f[i+1]<<"\nISBN = "<<f[i+2]<<"\nPublication"<<f[i+3]<<"\nReservation status = "<<f[i+4]
                <<"\nFeedback = "<<f[i+5]<<"\n";
            i=i+5;
            cout<<"\n----------------------------------------------------------------------------------------------------\n";
            a++;
        }
    }
    else if(Name=="BBA")
    {
        for(int i=91; i<120; i++)//show books according of specific department
        {
            cout<<"Book Name = "<<f[i]<<"\n"
                "Author = "<<f[i+1]<<"\nISBN = "<<f[i+2]<<"\nPublication"<<f[i+3]<<"\nReservation status = "<<f[i+4]
                <<"\nFeedback = "<<f[i+5]<<"\n";
            i=i+5;
            cout<<"\n----------------------------------------------------------------------------------------------------\n";
            a++;
        }
    }
    if(a==0)
    {
        cout<<"Error: Wrong department chosen!!";
    }
    file.close();//close the opened file
    a=0;
}
