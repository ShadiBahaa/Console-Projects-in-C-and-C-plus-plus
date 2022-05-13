#include <stdio.h>
#include <string.h>
unsigned int bookId = 0;
char bookNames[500][500];
char bookDepartment[500][500];
int userBooks[500]= {0};
int Bookborrower[500]= {0};
int found[500]= {0};
//int cnt = 0;
//char depView [500][500];
void checkID()
{
    int id;
    scanf("%d",&id);
    if (id<1 || id>bookId || !found[id-1])
    {
        puts("There is no book with such id");
        return;
    }
    puts("There is a book with such id");
}
void returnBook()
{
    int id;
    char gc;
    do
    {
        puts("Enter a valid user id: ");
        scanf("%d",&id);
        gc = getchar();
    }
    while (gc!='\n' || id<1 || id>500 || !userBooks[id-1]);
    int book_id = userBooks[id-1];
    printf("Book with id %d returned successfully. Now you can borrow again\n", book_id);
    userBooks[id-1]=0;
    Bookborrower[book_id-1]=0;
}
void viewBook()
{
    int id;
    scanf("%d",&id);
    if (id<1 || id>bookId || !found[id-1])
    {
        puts("Invalid id");
        return;
    }
    printf(" - The book full name is %s\n",bookNames[id-1]);
    printf(" - The book main department is %s\n",bookDepartment[id-1]);
    if (Bookborrower[id-1])
    {
        printf(" - The book is borrowed by user of id: %d\n",Bookborrower[id-1]);
    }
}
void ListBooks()
{
    if (bookId==0)
    {
        puts("No data yet");
        return;
    }
    int cnt = 0;
    char bookDepartment_sorted [500][500];
    for (int i = 0; i<bookId; ++i)
    {
        if (!found[i])continue;
        int fnd = -1;
        for (int j = 0; j<i; ++j)
        {
            if (!found[j])continue;
            if (!strcmp(bookDepartment[i],bookDepartment_sorted[j]))
            {
                fnd = 1;
                break;
            }
        }
        if (fnd ==-1)
        {
            strcpy(bookDepartment_sorted[cnt],bookDepartment[i]);
            cnt++;
        }
    }
    puts("This is the list of departments: ");
    for (int i = 0; i<cnt; ++i)
    {
        printf("\t%d - %s\n",i+1,bookDepartment_sorted[i]);
    }
    unsigned int choice;
    char gc;
    do
    {
        printf("Enter a valid number between 1 and %d\n", cnt);
        scanf("%d",&choice);
        gc = getchar();
    }
    while (gc!='\n' || choice<1 || choice>cnt);
    char books_sorted[500][500];
    cnt = 0;
    for (int i = 0; i<bookId; ++i)
    {
        if (!found[i]||strcmp(bookDepartment[i],bookDepartment_sorted[choice-1]))continue;
        int fnd = -1;
        for (int j = 0; j<i; ++j)
        {
            if (!found[j]||strcmp(bookDepartment[j],bookDepartment_sorted[choice-1]))continue;
            if (!strcmp(bookNames[i],bookNames[j]))
            {
                fnd =1;
                break;
            }
        }
        if (fnd == -1)
        {
            strcpy(books_sorted[cnt],bookNames[i]);
            cnt++;
        }
    }
    char tmp[500];
    for (int i =0; i<cnt; ++i)
    {
        for (int j = 0; j<cnt; ++j)
        {
            if (strcmp(books_sorted[j],books_sorted[i])>0)
            {
                strcpy(tmp,books_sorted[j]);
                strcpy(books_sorted[j],books_sorted[i]);
                strcpy(books_sorted[i],tmp);
            }
        }
    }
    puts("This is the list of books: ");
    for (int i =0; i<cnt; ++i)
    {
        printf("\t%d - %s\n",i+1,books_sorted[i]);
    }
}
void issueBook()
{
    if (bookId==0)
    {
        puts("No data yet");
        return;
    }
    int user;
    int book;
    char gc;
    do
    {
        puts("Enter valid book id: ");
        scanf("%d",&book);
        gc = getchar();
    }
    while (gc!='\n' || !found[book-1] || Bookborrower[book-1] || book<1 || book>bookId);
    do
    {
        puts("Enter valid user id: ");
        scanf("%d",&user);
        gc = getchar();
    }
    while (gc!='\n' || userBooks[user-1] || user<1 || user>500);
    userBooks[user-1] = book;
    Bookborrower[book-1]= user;
}
void searchBook()
{
    if (bookId==0)
    {
        puts("No data yet");
        return;
    }
    char c[500];
    puts("Enter a valid book name: ");
    scanf("%s[^\n]",c);
    for (int i = 0; i<bookId; ++i)
    {
        if (found[i] &&!strcmp(c,bookNames[i]))
        {
            puts("Book is found!");
            return;
        }
    }
    puts("There is no such book.");
}
void editBook()
{
    if (bookId==0)
    {
        puts("No data yet");
        return;
    }
    unsigned int choice;
    char gc;
    do
    {
        puts("Enter a valid ID to edit: ");
        scanf("%d",&choice);
        gc = getchar();
    }
    while (gc!='\n' || choice<1 || choice>bookId || !found[choice-1]);
    puts("Enter the new name and specialization respectively separated by a line: ");
    scanf("\n%s[^\n]",bookNames[choice-1]);
    scanf("\n%s[^\n]",bookDepartment[choice-1]);
}
void delete_id()
{
    if (bookId==0)
    {
        puts("No data yet");
        return;
    }
    unsigned int choice;
    char gc;
    do
    {
        puts("Enter a valid id: ");
        scanf("%d",&choice);
        gc = getchar();
    }
    while (gc!='\n' || choice<1 || choice>bookId || !found[choice-1]);
    found[choice-1]=0;
}
void delete_name()
{
    if (bookId==0)
    {
        puts("No names yet");
        return;
    }
    puts("Enter a valid name: ");
    char name[500];
    scanf("%s[^\n]",&name);
    for (int i = 0; i<bookId; ++i)
    {
        if (found[i]&&!strcmp(bookNames[i],name))
        {
            puts("Deletion occurred successfully");
            found[i]=0;
            return;
        }
    }
    puts("It is not a valid name.");
}
void delete_dep()
{
    if (bookId==0)
    {
        puts("No departments yet");
        return;
    }
    puts("Choose a department to remove from: ");
    char dep[500];
    scanf("%s[^\n]",&dep);
    for (int i = 0; i<bookId; ++i)
    {
        if (found[i] && !strcmp(bookDepartment[i],dep))
        {
            puts("All books in this department are here");
            //const int sz = bookId;
            int numbers[bookId];
            memset(numbers,0,sizeof(numbers));
            int cnt = 0;
            for (int j = i; j<bookId; ++j)
            {
                if (found[j]&&!strcmp(bookDepartment[j],dep))
                {
                    printf("\t%d - %s\n",j+1,bookNames[j]);
                    numbers[j]=1;
                }
            }
            unsigned int choice;
            char cg;
            do
            {
                puts("Enter an id to remove a book:");
                scanf("%d",&choice);
                cg = getchar();
            }
            while (cg!='\n' || !numbers[choice-1]);
            found [choice-1] = 0;
            return;
        }
    }
    puts("There is no department with that name");
}
void addBooks()
{
    puts("Please enter the book name and the book department respectively separated by a new line: ");
    scanf("\n%s[^\n]",&bookNames[bookId]);
    scanf("%s[^\n]",&bookDepartment[bookId]);
    found[bookId]=1;
    printf("The book with name: %s and department: %s inserted successfully with id: %d\n .",bookNames[bookId],bookDepartment[bookId],bookId+1);
    bookId++;
}
void deleteBook()
{
    unsigned short int choice;
    int gc;
    do
    {
        puts("Please enter a choice from 1 to 3: ");
        puts("      1- Delete by department");
        puts("      2- Delete by book name");
        puts("      3- Delete by book ID");
        scanf("%d",&choice);
        gc = getchar();
    }
    while (choice<1 || choice>3 || gc!='\n');
    switch(choice)
    {
    case 1:
        delete_dep();
        break;
    case 2:
        delete_name();
        break;
    case 3:
        delete_id();
        break;
    }
}
void menu ()
{
    puts("");
    //printf("");
    unsigned short int choice;
    //int response;
    int gc;
    do
    {
        //sleep(1);
        puts("Please insert a choice from 1 to 9 to continue, 10 to exit: ");
        puts("    1 - Add new book");
        puts("    2 - Delete a book");
        puts("    3 - Edit a book");
        puts("    4 - Search a book");
        puts("    5 - Issue a book");
        puts("    6 - List books");
        puts("    7 - View book information");
        puts("    8 - Return a book");
        puts("    9 - Check book availability");
        puts("    10 - Exit");
        scanf("%d",&choice);
        gc = getchar();
        //printf("%d",response);
    }
    while (choice<1 || choice>10 || gc!='\n');
    switch(choice)
    {
    case 1:
        addBooks();
        menu();
        break;
    case 2:
        deleteBook();
        menu();
        break;
    case 3:
        editBook();
        menu();
        break;
    case 4:
        searchBook();
        menu();
        break;
    case 5:
        issueBook();
        menu();
        break;
    case 6:
        ListBooks();
        menu();
        break;
    case 7:
        viewBook();
        menu();
        break;
    case 8:
        returnBook();
        menu();
        break;
    case 9:
        checkID();
        menu();
        break;
    case 10:
        break;
    }
}
void welcome()
{
    puts("                    #####################################################");
    puts("  ## Welcome to our program which is designed for helping you in dealing with our great library ##");
    puts("                    #####################################################");
    puts("");
}
int main()
{
    welcome();
    menu();
}
