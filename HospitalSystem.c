    #include <stdio.h>
#include <stdlib.h>
#include <string.h>

//data management functions
void initializer();
void reallocator();
void patientSwaper();
void deallocator();

//input management functions
int intInput();
void stringInput(char *stringPtr);

//program's driver functions
void menu();
void welcome();
void thx();
//adding functions
void add();
//displaying functions
void display();
void displayByID(int i);
//searching functions
void searchP();
void search_id();
void search_name();
//deleting functions
void deleteP();
void delete_id();
void delete_name();
//editing functions
void edit(int i);
//listing functions
void list();
void list_id();
void list_name();

//global variables
short int *** patients = NULL;
int patientsCounter = 1;
int deletedPatientsCounter = 0;


int main()
{
    initializer();
    welcome();
    menu();
    thx();
    deallocator();
    return 0;
}


void welcome()
{
    puts("                    #####################################################");
    puts("  ## Welcome to our program which is designed for helping you in dealing with our great hospital ##");
    puts("                    #####################################################");
    puts("");
}


void thx()
{
    puts("                    #####################################################");
    puts("                             ## Thanks for using our application ##");
    puts("                    #####################################################");
    puts("");
}


void menu()
{
    //local variables
    int choice1=0;

    void (*fun[5])()= {add,display,searchP,list,deleteP};
    puts("Please insert a choice from 1 to 5 to continue, 6 to exit: ");
    puts("    1 - Add new patient");
    puts("    2 - Display all Patients data");
    puts("    3 - search and edit Patient information");
    puts("    4 - list Patients");
    puts("    5 - Delete patient");
    puts("    6 - Exit");

    choice1 = intInput();
    while (!(choice1 < 7 && choice1 > 0))
    {
        puts("Please enter a valid input.");
        choice1 = intInput();
    }
    if (choice1 == 6)
    {
        puts("");
        return;
    }
    fun[choice1-1]();
    menu();
}


void add()
{
    //local variables
    int sexa, choice2;

    //inputting the service
    printf("%s","please choose the service you want \n 1- Neurologist \n 2- psychiatrist \n 3- surgeon \n 4- internist\n ");
    choice2 = intInput();
    while (!(choice2 < 5 && choice2 > 0))
    {
        puts("Please enter a valid input.");
        choice2 = intInput();
    }
    *patients[patientsCounter-1][5] = choice2;

    //inputting the name
    printf("%s","Please add the patient name: ");
    stringInput(patients[patientsCounter-1][1]);

    //inputting the age
    printf("%s","Please add the patient age: ");
    *patients[patientsCounter-1][3] = intInput();
    while (!(*patients[patientsCounter-1][3]>0 && *patients[patientsCounter-1][3]<200))
    {
        puts("Please enter a valid input.");
        *patients[patientsCounter-1][3] = intInput();
    }

    //inputting the address
    printf("%s","Please add the patient address: ");
    stringInput(patients[patientsCounter-1][2]);

    //inputting the sex
    printf("%s","Please select the patient sex \n 1- male \n 2- female \n ");
    sexa = intInput();
    while (sexa != 1 && sexa != 2)
    {
        puts("Please enter a valid input.");
        sexa = intInput();
    }
    *patients[patientsCounter-1][4] = sexa;

    //inputting the description
    printf("%s","Please describe the disease: ");
    stringInput(patients[patientsCounter-1][6]);

    //inputting the charge
    printf("%s","Please add the total charge for this patient: ");
    *patients[patientsCounter-1][8] = intInput();
    while(*patients[patientsCounter-1][8] < 0)
    {
        puts("Please enter a valid input.");;
        printf("%s","Please add the total charge: ");
        *patients[patientsCounter-1][8]=intInput();
    }

    //inputting the deposit
    printf("%s","Please add the total deposited: ");
    *patients[patientsCounter-1][9]=intInput();
    while(*patients[patientsCounter-1][9] < 0)
    {
        puts("Please enter a valid input.");;
        printf("%s","Please add the total deposited: ");
        *patients[patientsCounter-1][9] = intInput();
    }

    //inputting the return
    *patients[patientsCounter-1][10] = *patients[patientsCounter-1][9]- *patients[patientsCounter-1][8];

    //displaying the data of the newly added patient
    puts("");
    if (*patients[patientsCounter-1][9] - *patients[patientsCounter-1][8] >= 0)
        printf("%s %d %s\n%s %d\n%s %d\n%s %d\n",
               "New patient with ID ",
               patientsCounter,
               "has been added",
               "Total charge is: ",
               *patients[patientsCounter-1][8],
               "Total deposited is: ",
               *patients[patientsCounter-1][9],
               "He should receive: ",
               *patients[patientsCounter-1][10]
              );
    else
        printf("%s %d %s\n%s %d\n%s %d\n%s %d\n",
               "New patient with ID ",
               patientsCounter,
               "has been added",
               "Total charge is: ",
               *patients[patientsCounter-1][8],
               "Total deposited is: ",
               *patients[patientsCounter-1][9],
               "He should pay: ",
               (*patients[patientsCounter-1][10]- 2 * (*patients[patientsCounter-1][10]))
              );
    puts("");
    reallocator();
    return;
}


void displayByID(int i)
{
    //minus one to match the indexing
    i--;

    //local variables
    int choice1, choice2;

    //make sure the patient is not deleted
    if(*patients[i][0] == -1)
    {
        puts("there is no patients with this ID");
        puts("");
    }
    if(*patients[i][0] != -1)
    {
        //displaying the data of the patient with given id
        //printing the patient number
        printf("%s %d %s\n", "Patient Number", i+1, "data");

        //printing the name
        printf("%s %s\n", "patient name: ", patients[i][1]);

        //printing the service
        choice1 = *patients[i][5];
        switch(choice1)
        {
        case 1:
            printf("%s\n", "patient service:  Neurologist");
            break;
        case 2:
            printf("%s\n", "patient service:  Psychiatrist");
            break;
        case 3:
            printf("%s\n", "patient service:  Surgeon");
            break;
        case 4:
            printf("%s\n", "patient service:  Internist");
            break;
        }

        //printing the room
        printf("%s %d\n", "patient room: ", i+1);

        //printing the age
        printf("%s %d\n", "patient age: ", *patients[i][3]);

        //printing the address
        printf("%s %s\n", "patient address: ", patients[i][2]);

        //printing the sex
        choice2 = *patients[i][4];
        switch(choice2)
        {
        case 1:
            printf("%s\n", "patient sex:  Male");
            break;
        case 2:
            printf("%s\n", "patient sex:  Female");
            break;
        }

        //printing the description
        printf("%s %s\n", "patient disease description: ", patients[i][6]);

        //printing the charge
        printf("%s %d\n", "patient total charge: ", *patients[i][8]);

        //printing the deposit
        printf("%s %d\n", "patient total deposit: ", *patients[i][9]);

        //printing the return / pay
        if (*patients[i][9] - *patients[i][8] >= 0)
            printf("%s %d\n","He received: ", *patients[i][10]);

        else
        {
            printf("%s %d\n", "patient total needed to be payed: ", *patients[i][10] - 2 * (*patients[i][10]) );
        }

        puts("");
    }
    return;
}


void display()
{
    //local variables
    int choice1, choice2;

    //check if there are not patients yet
    if (patientsCounter-1-deletedPatientsCounter == 0) puts("There are no patients");
    else
    {
        //print the total number of patients which is the number of patients minus the number of deleted patients
        printf("\n%s %d\n\n","The number of patients is", patientsCounter - 1 - deletedPatientsCounter);

        //displaying each patient data
        for (int i=0; i<patientsCounter-1; i++)
        {
            //if the patient is deleted skip him
            if(*patients[i][0] == -1)continue;

            //else continue printing patients data
            //printing the patient number
            printf("%s %d %s\n", "Patient Number", i+1, "data:");

            //printing the name
            printf("%s %s\n", "patient name: ", patients[i][1]);

            //printing the service
            choice1 = *patients[i][5];
            switch(choice1)
            {
            case 1:
                printf("%s\n", "patient service:  Neurologist");
                break;
            case 2:
                printf("%s\n", "patient service:  Psychiatrist");
                break;
            case 3:
                printf("%s\n", "patient service:  Surgeon");
                break;
            case 4:
                printf("%s\n", "patient service:  Internist");
                break;
            }

            //printing the room number
            printf("%s %d\n", "patient room: ",i+1);

            //printing the age
            printf("%s %d\n", "patient age: ", *patients[i][3]);

            //printing the address
            printf("%s %s\n", "patient address: ",patients[i][2]);

            //printing the sex
            choice2 = *patients[i][4];
            switch(choice2)
            {
            case 1:
                printf("%s\n", "patient sex:  Male");
                break;
            case 2:
                printf("%s\n", "patient sex:  Female");
                break;
            }

            //printing the description
            printf("%s %s\n", "patient disease description: ", patients[i][6]);

            //printing the charge
            printf("%s %d\n", "patient total charge: ", *patients[i][8]);

            //printing the deposit
            printf("%s %d\n", "patient total deposit: ", *patients[i][9]);

            //printing the return / pay
            if (*patients[i][9]- *patients[i][8]>=0)
                printf("%s %d\n","patient received: ", *patients[i][10]);
            else
            {
                printf("%s %d\n", "patient should pay: ", *patients[i][10] - 2 * (*patients[i][10]));
            }
            puts("");
        }
        puts("");
    }
    return;
}


void searchP()
{
    //local variables
    int choice;

    do
    {
        puts("Please enter a choice from 1 to 2: ");
        puts("      1- search by patient name");
        puts("      2- search by patient ID");
        choice = intInput();
    }
    while (choice < 1 || choice > 2);

    switch(choice)
    {
    case 1:
        search_name();
        break;
    case 2:
        search_id();
        break;
    }
    return ;
}


void search_id()
{
    //local variables
    int choice, choice1, choice3;

    //check if there are not patients yet
    if (patientsCounter-1-deletedPatientsCounter == 0)
    {
        puts("No patients yet");
        return;
    }

    //take the id from the user and display the data of the patient with given id
    puts("Please enter the ID: ");
    choice = intInput();
    while (choice < 1 || choice > patientsCounter-1 || *patients[choice-1][0] == -1)
    {
        puts("There are no records available. Enter a valid id: ");
        choice = intInput();
    }
    displayByID(choice);

    //see if the user want to edit the data of the patient with the given id
    printf("%s\n","if you want to edit press 1 else press 2");
    choice1 = intInput();
    while(choice1 != 1 && choice1 != 2)
    {
        puts("enter Valid input");
        choice1= intInput();
    }
    if (choice1==1)
    {
        edit(choice);
    }
    puts("");
    return;
}


void edit(int i)
{
    //minus one to match the indexing
    i--;

    //local variables
    int sexa, choice1, choice2, choice3;

    //ask the user what he wants to change
    puts("Please insert a choice from 1 to 8 to continue, 9 to exit: ");
    puts("    1 - Edit Name");
    puts("    2 - Edit address");
    puts("    3 - Edit age");
    puts("    4 - Edit sex");
    puts("    5 - Edit service");
    puts("    6 - Edit disease description");
    puts("    7 - Edit total charge");
    puts("    8 - Edit total deposit");
    puts("    9 - Exit");
    choice3 = intInput();
    while (!(choice3 < 10 && choice3 > 0))
    {
        puts("Please enter a valid input.");
        choice3 = intInput();
    }

    //do what the user wants :)
    switch (choice3)
    {
    //editing the name
    case 1 :
        printf("%s", "Please add the patient name: ");
        stringInput(patients[i][1]);
        break;

    //editing the address
    case 2:
        printf("%s", "Please add the patient address: ");
        stringInput(patients[i][2]);
        break;

    //editing the age
    case 3 :
        printf("%s", "Please add the patient age: ");
        *patients[i][3] = intInput();
        while (!(*patients[i][3] > 0 && *patients[i][3] < 200))
        {
            puts("Please enter a valid input.");
            *patients[i][3] = intInput();
        }
        break;

    //editing the sex
    case 4 :
        printf("%s","Please select the patient sex \n 1- male \n 2- female \n ");
        sexa = intInput();
        while (sexa!= 1 && sexa != 2)
        {
            puts("Please enter a valid input.");
            sexa = intInput();
        }
        *patients[i][4] = sexa;
        break;

    //editing the service
    case 5 :
        printf("%s","please choose the service you want \n 1- Neurologist \n 2- psychiatrist \n 3- surgeon \n 4- internist\n ");
        choice2 = intInput();
        while (!(choice2 < 5 && choice2 > 0))
        {
            puts("Please enter a valid input.");
            choice2 = intInput();
        }
        *patients[i][5] = choice2;
        break;

    //editing the description
    case 6 :
        printf("%s","Please describe the disease: ");
        stringInput(patients[i][6]);
        break;

    //editing the charge
    case 7 :
        printf("%s","Please add the total charge for this patient: ");
        *patients[i][8] = intInput();
        while(*patients[i][8] < 0)
        {
            puts("Please enter a valid input.");;
            printf("%s","Please add the total charge: ");
            *patients[i][8]=intInput();
        }
        break;

    //editing the deposit
    case 8:
        printf("%s","Please add the total deposited: ");
        *patients[i][9] = intInput();
        while(*patients[i][9] < 0)
        {
            puts("Please enter a valid input.");;
            printf("%s","Please add the total deposited: ");
            *patients[i][9] = intInput();
        }
        break;

    //exit
    case 9:
        return;
        break;
    }

    //editing the return
    *patients[i][10]= *patients[i][9] - *patients[i][8];

    //displaying the patient's data after it has been edited
    displayByID(i+1);
    puts("");

    //edit again if the user wants to. If not he can choose to exit
    edit(i+1);
}


void search_name()
{
    //local variables
    int choice;
    char name[500];

    //check if there are not patients yet
    if (patientsCounter-1-deletedPatientsCounter == 0)
    {
        puts("No patients yet");
        return;
    }

    //take the name from the user to search by it in the patients
    puts("Enter a valid name: ");
    stringInput(name);

    //searching for that given name
    for (int i = 0; i < patientsCounter-1; ++i)
    {
        //if we found a patient with the given name
        if (*patients[i][0] != -1 && !strcmp(patients[i][1],name))
        {
            //display his data and ask the user if he wants to edit
            displayByID(i+1);
            printf("%s\n","if you want to edit press 1 else press 2");
            choice = intInput();
            while(choice!= 1 && choice!=2)
            {
                puts("enter Valid input");
                choice = intInput();
            }
            if (choice == 1)
            {
                edit(i+1);
                puts("");
                return;
            }
            if (choice == 2)
            {
                puts("");
                return;
            }
        }
    }
    //if we did not find a patient with the given name
    puts("It is not a valid name.");
    puts("");
    return;
}


void deleteP()
{
    //local variables
    int choice;

    //ask the user whether to delete patients by name or patient's number
    do
    {
        puts("Please enter a choice from 1 to 2: ");
        puts("      1- Delete by patient name");
        puts("      2- Delete by patient ID");
        choice = intInput();
    }
    while (choice < 1 || choice > 2);

    switch(choice)
    {
    case 1:
        delete_name();
        break;
    case 2:
        delete_id();
        break;
    }
    return ;
}


void delete_id()
{
    //local variables
    int choice, choice1;

    //check if there are not patients yet
    if (patientsCounter-1-deletedPatientsCounter == 0)
    {
        puts("No patients yet");
        return;
    }

    //take the id from the user and display its data
    do
    {
        puts("Enter a valid id: ");
        choice = intInput();
    }
    while (choice < 1 || choice > patientsCounter || *patients[choice-1][0] == -1);
    displayByID(choice);
    //ask the user if he wants to delete the patient with the given id
    printf("%s\n","if you want to delete press 1 else press 2");
    choice1 = intInput();
    while(choice1 != 1 && choice1 != 2)
    {
        puts("enter Valid input");
        choice1 = intInput();
    }
    if (choice1 == 1)
    {
        *patients[choice-1][0] = -1;
        puts("The data has been deleted successfully");
        deletedPatientsCounter++;
    }
    puts("");
    return;
}


void delete_name()
{
    //local variables
    int choice;
    char name[500];

    //check if there are not patients yet
    if (patientsCounter-1-deletedPatientsCounter == 0)
    {
        puts("No patients yet");
        return;
    }
    //take the name from the user and display its data
    puts("Enter a valid name: ");
    stringInput(name);
    for (int i = 0; i < patientsCounter; ++i)
    {
        if (*patients[i][0] != -1 && !strcmp(patients[i][1],name))
        {
            displayByID(i+1);
            //ask the user if he wants to delete the patient with the given name
            printf("%s\n","if you want to delete press 1 else press 2");
            choice = intInput();
            while(choice != 1 && choice != 2)
            {
                puts("enter Valid input");
                choice= intInput();
            }
            if (choice == 1)
            {
                *patients[i][0] = -1;
                puts("The data has been deleted successfully");
                puts("");
                deletedPatientsCounter++;
                return;
            }
            if (choice==2)
            {
                puts("");
                return;
            }
        }
    }

    //if we did not find a patient with the given name
    puts("It is not a valid name.");
    puts("");
    return;
}


void list()
{
    //local variables
    int choice;

    //ask the user whether to delete patients by name or patient's number
    do
    {
        puts("Please enter a choice from 1 to 2: ");
        puts("      1- list by patient name");
        puts("      2- list by patient ID");
        choice = intInput();
    }
    while (choice < 1 || choice > 2);

    switch(choice)
    {
    case 1:
        list_name();
        break;
    case 2:
        list_id();
        break;
    }
    return ;
}



void list_id()
{
    //local variables
    int cnt = 0, choice;

    //check if there are not patients yet
    if (patientsCounter-1-deletedPatientsCounter == 0)
    {
        puts("No patients yet");
        return;
    }

    //list the patients sorted according to patient number
    puts("This is the list of patients: ");
    for (int i =1; i < patientsCounter; ++i)
    {
        if (*patients[i-1][0]==-1)
        {
            continue;
        }
        cnt++;
        printf("\t%d - %s\n", i, patients[i-1][1]);
    }
    cnt+=deletedPatientsCounter+1;

    //ask the user if he wants to show the full data of any of the listed patients
    printf("%s %d %s\n","if you want to reach patient data please enter his number, enter", cnt, "to exit");
    choice = intInput();
    while (!(choice < cnt+1 && choice > 0))
    {
        puts("Please enter a valid input.");
        choice = intInput();
    }
    if (choice == cnt)
    {
        puts("");
        return;
    }

    //display the data of the choosed id
    displayByID(choice);
}

void list_name()
{
    //local variables
    int cnt = 0, choice;
    char patient_sorted[500][500], tmp[500];

    //check if there are not patients yet
    if (patientsCounter-1-deletedPatientsCounter == 0)
    {
        puts("No patients yet");
        return;
    }

    //sort the patients according to their names
    for (int i = 0; i < patientsCounter; ++i)
    {
        if (*patients[i][0] == -1) continue;
        strcpy(patient_sorted[cnt], patients[i][1]);
        cnt++;
    }
    for (int i = 0; i < cnt; ++i)
    {
        for (int j = 0; j < cnt; ++j)
        {
            if (strcmp(patient_sorted[j], patient_sorted[i]) > 0)
            {
                strcpy(tmp, patient_sorted[j]);
                strcpy(patient_sorted[j], patient_sorted[i]);
                strcpy(patient_sorted[i], tmp);
            }
        }
    }

    //list the patients sorted according to patients' names
    puts("This is the list of patients: ");
    for (int i = 1; i < cnt; ++i)
    {
        printf("\t%d - %s\n", i, patient_sorted[i]);
    }

    //ask the user if he wants to show the full data of any of the listed patients
    printf("%s %d %s\n","if you want to reach patient data please enter his number, enter", cnt, "to exit");
    choice = intInput();
    while (!(choice < cnt+1 && choice > 0))
    {
        puts("Please enter a valid input.");
        choice = intInput();
    }
    if (choice == cnt)
    {
        puts("");
        return;
    }

    //search for name that the user has choosed to show its data
    for (int i = 0; i < patientsCounter-1; ++i)
    {
        //if we found a patient with the given name
        if (*patients[i][0] != -1 && !strcmp(patients[i][1], patient_sorted[choice]))
        {
            //display his data
            displayByID(i+1);
        }
    }
}


void initializer()
{
    patients  = calloc(patientsCounter, sizeof(short int**));
    for(int i = 0; i < patientsCounter; ++i)
    {
        patients[i] = calloc(11, sizeof(short int*));
        patients[i][0] = calloc(1, sizeof(short int));      //patient number
        patients[i][1] = calloc(100, sizeof(short int));    //name
        patients[i][2] = calloc(150, sizeof(short int));    //address
        patients[i][3] = calloc(1, sizeof(short int));      //age
        patients[i][4] = calloc(1, sizeof(short int));      //sex
        patients[i][5] = calloc(1, sizeof(short int));      //service
        patients[i][6] = calloc(300, sizeof(short int));    //description
        patients[i][7] = calloc(1, sizeof(short int));      //room
        patients[i][8] = calloc(1, sizeof(short int));      //total charge
        patients[i][9] = calloc(1, sizeof(short int));      //total deposited
        patients[i][10] = calloc(1, sizeof(short int));     //total return
    }
}


void reallocator()
{
    //increase the number of patients
    patientsCounter++;

    //reallocate the patients data with the new size
    patients  = realloc(patients, sizeof(short int**) * patientsCounter);
    if(patients == NULL)
    {
        printf("Failed to reallocate");
        return ;
    }

    //initialize the newly added patient
    int i = patientsCounter - 1;
    patients[i] = calloc(11, sizeof(short int*));
    patients[i][0] = calloc(1, sizeof(short int));      //patient number
    patients[i][1] = calloc(100, sizeof(short int));    //name
    patients[i][2] = calloc(150, sizeof(short int));    //address
    patients[i][3] = calloc(1, sizeof(short int));      //age
    patients[i][4] = calloc(1, sizeof(short int));      //sex
    patients[i][5] = calloc(1, sizeof(short int));      //service
    patients[i][6] = calloc(300, sizeof(short int));    //description
    patients[i][7] = calloc(1, sizeof(short int));      //room
    patients[i][8] = calloc(1, sizeof(short int));      //total charge
    patients[i][9] = calloc(1, sizeof(short int));      //total deposited
    patients[i][10] = calloc(1, sizeof(short int));     //total return
}


void patientSwaper(short int** patient1, short int** patient2)
{
    short int* temp = NULL;
    for(int i = 0; i< 11; ++i)
    {
        temp = patient1[i];
        patient1[i] = patient2[i];
        patient2[i] = temp;
    }
}


void deallocator()
{
    //free all the memory used by the patients data
    for(int i = 0; i < patientsCounter; ++i)
    {
        for(int j = 0; j < 11; ++j)
        {
            free(patients[i][j]);
            patients[i][j] = NULL;
        }
        free(patients[i]);
        patients[i] = NULL;
    }
    free(patients);
    patients = NULL;
}


void stringInput(char *stringPtr)
{
    while (1)
    {
        static char string[200];
        fgets(string, 200, stdin);
        int n = strlen(string);
        if(n > 1)
        {
            for(int i = 0; i < n - 1; ++i)
            {
                stringPtr[i] = string[i];
            }
            stringPtr[n - 1] = '\0';
            return;
        }
        else
        {
            puts("Please enter a valid input.");
        }
    }

}


int intInput()
{
    while(1)
    {
        char input[100], c;
        int i;
        fgets(input, 100, stdin);
        if(sscanf(input, "%i %c", &i, &c) == 1)
        {
            return i;
        }
        else
        {
            puts("Please enter a valid input.");
        }
    }
}

