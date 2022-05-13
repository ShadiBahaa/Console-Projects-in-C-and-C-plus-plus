#include <stdio.h>
#include <stdlib.h>
struct book
{
    int id;
    char name[1000];
    int status;
};
typedef struct book Book;
struct listNode
{
    Book data;
    struct listNode* nextPtr;
};
typedef struct listNode ListNode;
typedef ListNode* ListNodePtr;
int isEmpty(ListNodePtr startPtr)
{
    return startPtr == NULL;
}
void insert(ListNodePtr* startPtr, Book value)
{
    ListNodePtr newPtr;
    ListNodePtr previousPtr;
    ListNodePtr currentPtr;

    newPtr = malloc(sizeof(ListNode));

    if (newPtr != NULL)
    {
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        previousPtr = NULL;
        currentPtr = *startPtr;

        while (currentPtr != NULL && value.id > (currentPtr->data).id)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if (previousPtr == NULL)
        {
            newPtr->nextPtr = *startPtr;
            *startPtr = newPtr;
        }
        else
        {
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }
    else
    {
        printf("not inserted. No memory avaliable.\n");
    }
}
void printList(ListNodePtr startPtr)
{
    ListNodePtr currentPtr;
    if (isEmpty(startPtr))
    {
        printf("List is empty\n");
    }
    else
    {
        printf("The list is : \n");
        currentPtr = startPtr;
        while (currentPtr != NULL)
        {
            printf("%-10d %-10s %-10d \n", (currentPtr->data).id,(currentPtr->data).name,(currentPtr->data).status);
            currentPtr = currentPtr->nextPtr;
        }
    }
}
int search(ListNodePtr head,int id)
{
    if (head==NULL)
    {
        return -1;
    }
    ListNodePtr tmp = head;
    while (tmp!=NULL)
    {
        if ((tmp->data).id==id)
        {
            if ((tmp->data).status==0)return 0;
            else return 1;
        }
        tmp = tmp->nextPtr;
    }
    return -1;
}
int delete(ListNodePtr* startPtr, int value)
{
    ListNodePtr previousPtr;
    ListNodePtr currentPtr;
    ListNodePtr tempPtr;

    if (value == ((*startPtr)->data).id)
    {
        tempPtr = *startPtr;
        *startPtr = (*startPtr)->nextPtr;
        free(tempPtr);
        return value;
    }
    else
    {
        previousPtr = *startPtr;
        currentPtr = (*startPtr)->nextPtr;

        while (currentPtr != NULL && (currentPtr->data).id != value)
        {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if (currentPtr != NULL)
        {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return value;
        }
        return -1;
    }
}
void lend(ListNodePtr *head,int id)
{
    if (search(*head,id)==1)
    {
        ListNodePtr tmp = *head;
        while (tmp!=NULL)
        {
            if ((tmp->data).id==id)
            {
                (tmp->data).status = 0;
                return;
            }
            tmp = tmp->nextPtr;
        }
    }
}
void printFile(char *name, ListNodePtr head){
    FILE *ptr = fopen(name,"w");
    if (ptr==NULL)return;
    ListNodePtr tmp = head;
    while (tmp!=NULL){
        fprintf(ptr,"%-10d %-10s %-10d\n",(tmp->data).id,(tmp->data).name,(tmp->data).status);
        tmp = tmp->nextPtr;
    }
    fclose(ptr);
}
int main()
{
    // testing part

    /*ListNodePtr head = NULL;
    printList(head);
    Book first = {1,"shadi",1};
    insert(&head,first);
    printList(head);
    Book second = {2,"reham",0};
    insert(&head,second);
    printList(head);
    printf("%d\n",search(head,1));
    printf("%d\n",search(head,2));
    printf("%d\n",search(head,3));
    delete(&head,2);
    printList(head);
    insert(&head,second);
    lend(&head,1);
    printList(head);
    printFile("exam.txt",head);*/
}
