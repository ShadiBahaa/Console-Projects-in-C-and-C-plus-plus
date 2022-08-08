#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    int index;
    Node* next;
    Node* prev;
    Node (int val, int index)
    {
        this->data = val;
        this->index = index;
        this->next = nullptr;
        this->prev = nullptr;
    }
    ~Node()
    {
        cout<<"Node at index "<<this->index<<" with value "<<this->data<<" destroyed succefully"<<endl;
    }
};
class ArrayLinkedList
{
private:
    int length = 0;
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    ArrayLinkedList(int length)
    {
        this->length = length;
    }
    ~ArrayLinkedList()
    {
        while (head)
        {
            Node* cur = head->next;
            delete head;
            head = cur;
        }
        tail = nullptr;
        cout<<"Done"<<endl;
    }
    Node* set_value(int val, int index)
    {
        assert(index<length && index>=0);
        Node* tmp= new Node(val,index);
        if (head==nullptr)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            Node *cur = head;
            while (cur)
            {
                if (cur->index>=index)
                {
                    break;
                }
                cur = cur->next;
            }
            if (cur && cur->prev==nullptr && cur->index!=index)
            {
                tmp->next = head;
                head->prev = tmp;
                head = tmp;
            }
            else if (cur==nullptr)
            {
                tail->next= tmp;
                tmp->prev = tail;
                tail = tmp;
            }
            else if (cur->index==index)
            {
                cur->data = val;
            }
            else
            {
                Node *pre = cur->prev;
                tmp->prev = pre;
                pre->next = tmp;
                tmp->next = cur;
                cur->prev = tmp;
            }
        }
        return tmp;
    }
    int get_value(int index)
    {
        assert(index>=0 && index<length);
        for (Node* cur= head; cur; cur= cur->next)
        {
            if (cur->index == index)return cur->data;
        }
        return 0;
    }
    void print_array_nonzero()
    {
        Node*tmp = head;
        while (tmp)
        {
            cout<<tmp->data<<" ";
            tmp = tmp->next;
        }
        cout<<endl;
    }
    void print()
    {
        int cnt = 0;
        Node*tmp = head;
        while (tmp)
        {
            while (cnt<tmp->index)
            {
                cout<<0<<" ";
                cnt++;
            }
            cout<<tmp->data<<" ";
            tmp = tmp->next;
            cnt++;
        }
        while (cnt<length)
        {
            cout<<0<<" ";
            cnt++;
        }
        cout<<endl;
    }
    void add(const ArrayLinkedList &other)
    {
        assert(length==other.length);
        Node *ohead = other.head;
        Node *chead = head;
        int index = 0;
        while (index<length)
        {
            if (chead && ohead && chead->index==index && ohead->index==index)
            {
                chead->data+=ohead->data;
                chead = chead->next;
                ohead = ohead->next;
            }
            else if (chead && chead->index==index)
            {
                chead = chead->next;
            }
            else if (ohead && ohead->index==index)
            {
                chead = set_value(ohead->data,index);
                chead = chead->next;
                ohead = ohead->next;
            }
            index++;
        }
    }
};
struct ArrayNode
{
    ArrayLinkedList arr;
    ArrayNode* next = nullptr;
    int len = 0;
    int num = 0;
    ArrayNode(int length, int num):arr(length),len(length),num(num)
    {
    }
    ~ArrayNode()
    {
        cout<<"An array of index "<<num<<" has been destroyed"<<endl;
    }
};
class SparseMatrix
{
private:
    int row = 0;
    int col = 0;
    ArrayNode *head = nullptr;
    ArrayNode *tail = nullptr;
public:
    SparseMatrix(int row, int col)
    {
        this->row = row;
        this->col = col;
    }
    ~SparseMatrix()
    {
        while (head)
        {
            ArrayNode *tmp = head->next;
            delete head;
            head = tmp;
        }
        head = nullptr;
        tail = head;
    }
    ArrayNode* set_value(int val, int r, int c)
    {
        assert(r>=0 && r<row && c>=0 && c<col);
        ArrayNode *tmp = new ArrayNode(col,r);
        if (head==nullptr)
        {
            (tmp->arr).set_value(val,c);
            head = tmp;
            tail = tmp;
        }
        else
        {
            ArrayNode *cur = head;
            ArrayNode *prev = nullptr;
            while (cur)
            {
                if (cur->num>=r)
                {
                    break;
                }
                prev = cur;
                cur = cur->next;
            }
            if (prev==nullptr && cur->num!=r)
            {
                tmp->next = head;
                head = tmp;
                (head->arr).set_value(val,c);
            }
            else if (cur==nullptr)
            {
                tail->next = tmp;
                tail = tmp;
                (tail->arr).set_value(val,c);
            }
            else if (cur->num==r)
            {
                (cur->arr).set_value(val,c);
            }
            else
            {
                prev->next = tmp;
                tmp->next = cur;
                (tmp->arr).set_value(val,c);
            }
        }
        return tmp;
    }
    void print_matrix()
    {
        cout<<row<<" x "<<col<<endl;
        ArrayNode *tmp = head;
        for (int i = 0; i<row; ++i)
        {
            if (tmp && tmp->num==i)
            {
                tmp->arr.print();
                tmp = tmp->next;
            }
            else
            {
                for (int j = 0; j<col; ++j)
                {
                    cout<<0<<" ";
                }
                cout<<endl;
            }
        }
    }
    void add(const SparseMatrix &other)
    {
        assert(row==other.row && col==other.col);
        ArrayNode *ohead = other.head;
        ArrayNode *chead = head;
        int index = 0;
        ArrayNode *prev = nullptr;
        while (index<row)
        {
            //cout<<index<<endl;
            if (chead && ohead && chead->num==index && ohead->num==index)
            {
                //cout<<"1 "<<index<<endl;
                (chead->arr).add(ohead->arr);
                prev = chead;
                chead = chead->next;
                ohead = ohead->next;
            }
            else if (chead && chead->num==index)
            {
                //cout<<"2 "<<index<<endl;
                prev = chead;
                chead = chead->next;
            }
            else if (ohead && ohead->num==index)
            {
                ArrayNode *tmp = new ArrayNode(col,ohead->num);
                tmp->next = chead;
                if (!tmp->next)tail = tmp;
                if (prev)prev->next = tmp;
                else head = tmp;
                (tmp->arr).add(ohead->arr);
                chead = tmp->next;
                ohead = ohead->next;
            }
            index++;
        }
    }
    void print_array_nonzero()
    {
        ArrayNode*tmp = head;
        while (tmp)
        {
            tmp->arr.print_array_nonzero();
            tmp = tmp->next;
        }
        //cout<<endl;
    }
    int get_value(int r, int c)
    {
        assert(r>=0 && r<row && c>=0 && c<col);
        for (ArrayNode* cur= head; cur; cur= cur->next)
        {
            if (cur->num==r){
                return cur->arr.get_value(c);
            }
        }
        return 0;
    }
};
int main()
{
    /*ArrayLinkedList arr(10);
    arr.set_value(50,5);
    arr.set_value(20,2);
    arr.set_value(70,7);
    arr.set_value(40,4);
    arr.print();
    arr.print_array_nonzero();
    cout<<arr.get_value(7)<<endl;
    ArrayLinkedList arr2(10);
    arr2.set_value(1,4);
    arr2.set_value(3,7);
    arr2.set_value(4,6);
    arr.add(arr2);
    arr.print();
    SparseMatrix mat(10,10);
    mat.set_value(5,3,5);
    mat.set_value(7,3,7);
    mat.set_value(2,3,2);
    mat.set_value(0,3,2);
    mat.set_value(6,5,6);
    mat.set_value(4,5,4);
    mat.set_value(3,7,3);
    mat.set_value(1,7,1);
    mat.print_matrix();
    mat.print_array_nonzero();
    SparseMatrix mat2(10,10);
    mat2.set_value(5,1,9);
    mat2.set_value(6,3,8);
    mat2.set_value(9,9,9);
    mat.add(mat2);
    mat.print_array_nonzero();
    cout<<mat.get_value(7,3)<<endl;*/
    SparseMatrix mat(10, 10);
	mat.set_value(5, 3, 5);
	mat.set_value(7, 3, 7);
	mat.set_value(2, 3, 2);
	mat.set_value(0, 3, 2);
	mat.set_value(6, 5, 6);
	mat.set_value(4, 5, 4);
	mat.set_value(3, 7, 3);
	mat.set_value(1, 7, 1);
	//mat.set_value(1, 70, 1);
	mat.print_matrix();
	mat.print_array_nonzero();

	SparseMatrix mat2(10, 10);
	mat2.set_value(5, 1, 9);
	mat2.set_value(6, 3, 8);
	mat2.set_value(9, 9, 9);
	mat.add(mat2);
	mat.print_array_nonzero();
}
