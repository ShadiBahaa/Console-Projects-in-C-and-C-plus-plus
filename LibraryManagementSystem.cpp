#include <bits/stdc++.h>
using namespace std;
struct User
{
    string name;
    int national_id = 0;
    User(string _name,int _national_id = 0)
    {
        national_id = _national_id;
        name = _name;
    }
    User() {}
};
struct Book
{
    int id;
    string name;
    int quantity = 0;
    string borrow [100];
    int total_borrowed = 0;
    Book(string _name,int _id =0,int _quantity = 0, int _total_borrowed = 0)
    {
        id = _id;
        name = _name;
        quantity = _quantity;
        total_borrowed = _total_borrowed;
    }
    Book() {}
};
Book books[100];
User users[100];
int users_count = 0;
int index = 0;
bool by_id (Book a, Book b)
{
    return a.id <b.id;
}
bool by_name (Book a, Book b)
{
    return a.name <b.name;
}
void add_book()
{
    cout<<"Enter book info: id & name & total quantity: ";
    //cin>>book.id>>book.name>>book.quantity;
    cin>>books[index].id>>books[index].name>>books[index].quantity;
    ++index;
    cout<<endl;
}
void search_books_by_prefix()
{
    cout<<"Enter book name prefix: ";
    string c;
    cin>>c;
    bool found = false;
    for (int i =0; i<index; i++)
    {
        string q = books[i].name.substr(0,c.size());
        if (q==c)
        {
            cout<<books[i].name<<endl;
            found = true;
        }
    }
    if (!found)
    {
        cout<<"No books with such prefix"<<endl;
    }
    cout<<endl;
}
void print_library_by_id()
{
    sort(books,books+index,by_id);
    for (int i =0; i<index; i++)
    {
        cout<<"id = "<<books[i].id<<" name = "<<books[i].name<<" total_quantity "<<books[i].quantity<<" total borrowed "<<books[i].total_borrowed<<endl;
    }
    cout<<endl;
}
void print_library_by_name()
{
    sort(books,books+index,by_name);
    for (int i =0; i<index; i++)
    {
        cout<<"id = "<<books[i].id<<" name = "<<books[i].name<<" total_quantity "<<books[i].quantity<<" total borrowed "<<books[i].total_borrowed<<endl;
    }
    cout<<endl;
}
void print_who_borrowed_book_by_name()
{
    cout<<"Enter book name: ";
    string book_name;
    cin>>book_name;
    int tarj = -1;
    for (int i = 0; i<index; i++)
    {
        if (books[i].name == book_name)
        {
            tarj = i;
        }
    }
    if (tarj!=-1)
    {
        bool found = false;
        for (int i = 0; i<books[tarj].total_borrowed; i++)
        {
            cout<<books[tarj].borrow[i]<<endl;
            found = true;
        }
        if (!found)
        {
            cout<<"No one borrowed this book"<<endl;
        }
    }
    else
    {
        cout<<"Invalid book name."<<endl;
    }
    cout<<endl;
}
void add_user()
{
    cout<<"Enter your name & national id: ";
    cin>>users[users_count].name>>users[users_count].national_id;
    users_count++;
    cout<<endl;
}
void user_borrow_book()
{
    cout<<"Enter user name & book name: ";
    string user_name;
    string book_name;
    cin>>user_name>>book_name;
    for (int i = 0; i<index ; i++)
    {
        if (books[i].name == book_name )
        {
            if (books[i].quantity > 0)
            {
                books[i].borrow[books[i].total_borrowed]= user_name;
                books[i].total_borrowed++;
                books[i].quantity--;
                return;
            }
            else
            {
                cout<<"There are no available copies."<<endl;
            }
        }
    }
    cout<<endl;
}
void user_return_book()
{
    cout<<"Enter user name & book name: ";
    string user_name;
    string book_name;
    cin>>user_name>>book_name;
    int tarj = -1;
    for (int i = 0; i<index ; i++)
    {
        if (books[i].name==book_name)
        {
            tarj = i;
            break;
        }
    }
    if (tarj == -1)
    {
        cout<<"Invalid book name"<<endl;
        return;
    }
    int tari = -1;
    for (int i = 0; i<books[tarj].total_borrowed; i++)
    {
        if (books[tarj].borrow[i]==user_name)
        {
            tari = i;
            break;
        }
    }
    if (tari == -1)
    {
        cout<<"Invalid user name"<<endl;
        return;
    }
    for (int i = tari; tari<books[tarj].total_borrowed-1; i++)
    {
        books[tarj].borrow[i] = books[tarj].borrow[i+1];
    }
    --books[tarj].total_borrowed;
    ++books[tarj].quantity;
    cout<<endl;
}
void print_users()
{
    for (int i = 0 ; i<users_count; i++)
    {
        cout<<"user "<<users[i].name<<" id "<<users[i].national_id<<" borrowed books ids: ";
        for (int j = 0; j<index ; j++)
        {
            for (int k =0; k<books[j].total_borrowed; k++)
            {
                if (users[i].name == books[j].borrow[k])
                {
                    cout<<books[j].id<<" ";
                    break;
                }
            }
        }
        cout<<endl;
    }
    cout<<endl;
}
void menu ()
{
    cout<<"Enter Your menu choice [1-10]: ";
    int choice;
    cin>>choice;
    switch(choice)
    {
    case 1:
        add_book();
        menu();
        break;
    case 2:
        search_books_by_prefix();
        menu();
        break;
    case 3:
        print_who_borrowed_book_by_name();
        menu();
        break;
    case 4:
        print_library_by_id();
        menu();
        break;
    case 5:
        print_library_by_name();
        menu();
        break;
    case 6:
        add_user();
        menu();
        break;
    case 7:
        user_borrow_book();
        menu();
        break;
    case 8:
        user_return_book();
        menu();
        break;
    case 9:
        print_users();
        menu();
        break;
    case 10:
        return;
    default:
        cerr<<"You entered a wrong choice please try again."<<endl;
        menu();
    }

}
int main()
{
    cout<<"Library Menu: "<<endl;
    cout<<"1)  add_book"<<endl;
    cout<<"2)  search_books_by_prefix"<<endl;
    cout<<"3)  print_who_borrowed_book_by_name"<<endl;
    cout<<"4)  print_library_by_id"<<endl;
    cout<<"5)  print_library_by_name"<<endl;
    cout<<"6)  add_user"<<endl;
    cout<<"7)  user_borrow_book"<<endl;
    cout<<"8)  user_return_book"<<endl;
    cout<<"9)  print_users"<<endl;
    cout<<"10) Exit"<<endl<<endl;
    menu();

}
