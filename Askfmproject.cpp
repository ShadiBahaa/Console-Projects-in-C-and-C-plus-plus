#include <bits/stdc++.h>
using namespace std;
struct User
{
    string id;
    string password;
    string name;
    string email;
    string anonymous;
};
struct Question
{
    string id;
    string from;
    string to;
    string txt;
    string ans;
    string parent;
    string anonymous;
};

void signUp(vector<User> &);
void ask(string &,string &,vector<User> &, vector<Question> &);
void listFeed(string &,string &,vector<User> &,vector<Question> &);
void listUsers(string &,string &,vector<User> &,vector<Question> &);
void answer(string &,string &,vector<User> &,vector<Question> &);
void delet(string &,string &,vector<User> &,vector<Question> &);
void printFromMe(string &,string &,vector<User> &,vector<Question> &);
void printToMe(string &,string &,vector<User> &,vector<Question> &);
void login(vector<User>&,vector<Question>&);
void loadVectors(vector<User>&,vector<Question>&);
void logOut();
void menu(string &,string &,vector<User> &, vector<Question> &que);
void updateUser(vector<User> &);
void updateQues(vector<Question> &);
vector<string> split(string);
int main()
{
    vector<User> users;
    vector<Question> questions;
    loadVectors(users,questions);
    cout<<"Menu: "<<endl;
    cout<<"\t1: Login"<<endl;
    cout<<"\t2: Sign Up"<<endl;
    cout<<"Enter 1 or 2"<<endl;
    int choice;
    cin>>choice;
    cin.ignore();
    switch (choice)
    {
    case 1:
        login(users,questions);
        break;
    case 2:
        signUp(users);
        break;
    default:
        cout<<"Not a correct choice."<<endl;
        break;
    }
}
vector<string> split(string str)
{
    vector<string> ans;
    size_t initial = 0;
    size_t index = str.find(",");
    while (index!=string::npos)
    {
        ans.push_back(str.substr(initial,index-initial));
        initial = index+1;
        index = str.find(",",initial);
    }
    ans.push_back(str.substr(initial));
    return ans;
}
void loadVectors(vector<User> &use, vector<Question>& que)
{
    ifstream ustr("user.txt");
    ifstream qstr("questions.txt");
    string line;
    while (getline(ustr,line))
    {
        if (line.size())
        {
            vector<string> v = split(line);
            use.push_back({v[0],v[1],v[2],v[3],v[4]});
        }

    }
    while (getline(qstr,line))
    {
        if (line.size())
        {
            vector<string> v = split(line);
            que.push_back({v[0],v[1],v[2],v[3],v[4],v[5],v[6]});
        }
    }
    ustr.close();
    qstr.close();
}
void login(vector<User> &use, vector<Question> &que)
{
    //cin.ignore();
    cout<<"Enter name and password"<<endl;
    string name,password;
    getline(cin,name);
    //cin.ignore();
    getline(cin,password);
    for (auto user:use)
    {
        if (user.name==name && user.password==password)
        {
            cout<<"Menu:"<<endl;
            cout<<"\t 1:Print questions to me"<<endl;
            cout<<"\t 2:Print questions from me"<<endl;
            cout<<"\t 3:Answer question"<<endl;
            cout<<"\t 4:Delete question"<<endl;
            cout<<"\t 5:Ask question"<<endl;
            cout<<"\t 6:List system users"<<endl;
            cout<<"\t 7:Feed"<<endl;
            cout<<"\t 8:Logout"<<endl;
            menu(user.anonymous,user.id,use, que);
            return;
        }
    }
    cout<<"No such user"<<endl;
    main();
}
void signUp(vector<User> &use)
{
    //cin.ignore();
    User account;
    cout<<"Enter user name: "<<endl;
    getline(cin,account.name);
    cout<<"Enter password: "<<endl;
    //cin.ignore();
    getline(cin,account.password);
    cout<<"Enter email: "<<endl;
    //cin.ignore();
    getline(cin,account.email);
    cout<<"Allow Anonymous questions? (0 or 1): "<<endl;
    //cin.ignore();
    string ano;
    getline(cin,ano);
    if (ano!="0" && ano!="1")
    {
        cout<<ano<<endl;
        cout<<"Wrong choice"<<endl;
        account.anonymous = "";
        main();
        return;
    }
    else
    {
        account.anonymous = ano;
    }
    if (use.size())account.id =  to_string((stoi(use[use.size()-1].id)+1));
    else account.id = "0";
    use.push_back(account);
    updateUser(use);
    main();
}
void menu(string &anonymous,string &id,vector<User> &use, vector<Question> &que)
{
    //cin.ignore();
    cout<<"Enter a number between 1 and 8"<<endl;
    int choice;
    cin>>choice;
    cin.ignore();
    switch(choice)
    {
    case 1:
        printToMe(anonymous,id,use, que);
        break;
    case 2:
        printFromMe(anonymous,id,use, que);
        break;
    case 3:
        answer(anonymous,id,use,que);
        break;
    case 4:
        delet(anonymous,id,use,que);
        break;
    case 5:
        ask(anonymous,id,use,que);
        break;
    case 6:
        listUsers(anonymous,id,use,que);
        break;
    case 7:
        listFeed(anonymous,id,use,que);
        break;
    case 8:
        logOut();
        break;
    default:
        cout<<"Error! Invalid answer"<<endl;
        menu(anonymous,id,use,que);
        break;
    }
}
void printToMe(string &ano,string &id,vector<User> &use,vector<Question> &que)
{
    //cin.ignore();
    for (int i = 0; i<que.size(); ++i)
    {
        //cout<<id<<endl;
        if (que[i].to == id && que[i].parent=="-1")
        {
            cout<<"Question Id ("<<que[i].id<<")";
            if (que[i].anonymous!="1")
            {
                cout<<"from user id("<<que[i].from<<")";
            }
            cout<<endl;
            cout<<"Question: "<<que[i].txt<<endl;
            if (que[i].ans.size())cout<<"Answer: "<<que[i].ans<<endl;
            for (int j = i+1; j<que.size(); ++j)
            {
                if (que[j].to == id && que[j].parent==que[i].id)
                {
                    cout<<"\t Thread:"<<endl;
                    cout<<"\t\t Question Id ("<<que[j].id<<")";
                    if (que[j].anonymous=="0")
                    {
                        cout<<"from user id("<<que[j].from<<")";
                    }
                    cout<<endl;
                    cout<<"\t\t Question: "<<que[j].txt<<endl;
                    if (que[j].ans.size())cout<<"\t\t Answer: "<<que[j].ans<<endl;
                }
            }
            cout<<endl;
        }
    }
    menu(ano,id,use, que);
}
void printFromMe(string &ano,string & id,vector<User> &use,vector<Question> & que)
{
    //cin.ignore();
    for (int i = 0; i<que.size(); ++i)
    {
        //cout<<que[i].parent<<endl;
        if (que[i].from == id && que[i].parent=="-1")
        {
            cout<<"Question Id ("<<que[i].id<<")";
            if (que[i].anonymous!="1")
            {
                cout<<" !AQ ";
            }
            cout<<"to user id("<<que[i].to<<")";
            cout<<endl;
            cout<<"Question: "<<que[i].txt<<endl;
            if (que[i].ans.size())cout<<"Answer: "<<que[i].ans<<endl;
            for (int j = i+1; j<que.size(); ++j)
            {
                if (que[j].from == id && que[j].parent==que[i].id)
                {
                    cout<<"\t Thread:"<<endl;
                    cout<<"\t\t Question Id ("<<que[j].id<<")";
                    if (que[j].anonymous=="0"){
                        cout<<" !AQ ";
                    }
                    cout<<"to user id("<<que[j].to<<")";
                    cout<<endl;
                    cout<<"\t\t Question: "<<que[j].txt<<endl;
                    if (que[j].ans.size())cout<<"\t\t Answer: "<<que[j].ans<<endl;
                }
            }
            cout<<endl;
        }
    }
    menu(ano,id,use, que);
}
void answer(string &ano,string &id,vector<User> &use,vector<Question> &que)
{
    //cin.ignore();
    cout<<"Enter question id or -1 to cancel: "<<endl;
    string queId;
    cin>>queId;
    cin.ignore();
    if (queId=="-1")
    {
        menu(ano,id,use, que);
        return;
    }
    bool found = false;
    for (int i = 0; i<que.size(); ++i)
    {
        if (que[i].id==queId && que[i].to==id)
        {
            found = true;
            cout<<"Question Id ("<<que[i].id<<")";
            if (que[i].anonymous!="1")
            {
                cout<<"from user id("<<que[i].from<<")";
            }
            cout<<endl;
            cout<<"Question: "<<que[i].txt<<endl;
            if (que[i].ans.size())cout<<"Answer: "<<que[i].ans<<endl;
            if (que[i].ans.size())
            {
                cout<<"Warning already answered. You will overwrite the original answer"<<endl;
            }
            //cin.ignore();
            cout<<"Enter answer: "<<endl;
            //Question* q = &question;
            getline(cin,que[i].ans);
            updateQues(que);
            answer(ano,id,use,que);
            break;
        }
    }
    if (!found)
    {
        //cin.ignore();
        cout<<"You don't have any question with that id!"<<endl;
        answer(ano,id,use,que);
    }
}
void delet(string &ano,string &id,vector<User> &use, vector<Question> &que)
{
    //cin.ignore();
    cout<<"Enter question id or -1 to cancel: "<<endl;
    string queId;
    cin>>queId;
    cin.ignore();
    if (queId=="-1")
    {
        menu(ano,id,use, que);
        return;
    }
    for (int i = 0; i<que.size(); ++i)
    {
        if (que[i].id==queId)
        {
             i = que.erase(que.begin()+i)-que.begin();
            for (int j = i+1; j<que.size(); ++j)
            {
                if (que[j].parent== queId)
                {
                    j = (que.erase(que.begin()+j))-que.begin();
                }
            }
            updateQues(que);
            menu(ano,id,use, que);
            return;
        }
    }
    cout<<"No such id found"<<endl;
    delet(ano,id,use,que);
}
void listUsers(string &ano,string &id,vector<User> &use,vector<Question> &que)
{
    for (auto account:use)
    {
        cout<<"ID: "<<account.id<<"\t\t Name: "<<account.name<<endl;
    }
    menu(ano,id,use,que);
}
void ask(string &anonymous,string &id,vector<User> &use, vector<Question> &que)
{
    //cin.ignore();
    cout<<"Enter user id or -1 to cancel: "<<endl;
    string userId;
    getline(cin,userId);
    //cin.ignore();
    bool an = true;
    if (userId=="-1")
    {
        menu(anonymous,id,use, que);
        return;
    }
    bool exist = false;
    for (int i = 0; i<use.size(); ++i)
    {
        if (use[i].id==userId)
        {
            exist = true;
            if (use[i].anonymous=="0")
            {
                an = false;
                cout<<"Note: Anonymous questions aren't allowed"<<endl;
            }
        }
    }
    if (!exist)
    {
        //cin.ignore();
        cout<<"There is no such user!"<<endl;
        menu(anonymous,id,use, que);
        return;
    }
    //cin.ignore();
    cout<<"For thread question, Enter question number or -1 for new question: "<<endl;
    string choice;
    //cin.ignore();
    getline(cin,choice);
    //cout<<choice<<endl;
    if (choice=="-1")
    {
        Question question;
        if (que.size())question.id = to_string((stoi(que[que.size()-1].id)+1));
        else question.id = "0";
        question.from = id;
        question.to = userId;
        if (an)
        {
            cout<<"do you the question to be anonymous? 1 for yes other no"<<endl;
            int num;
            cin>>num;
            cin.ignore();
            if (num==1)
            {
                question.anonymous = "1";
            }
            else
            {
                question.anonymous = "0";
            }
        }
        else
        {
            question.anonymous = "0";
        }
        question.parent = "-1";
        cout<<"Enter question text: "<<endl;
        getline(cin,question.txt);
        que.push_back(question);
        updateQues(que);
        ask(anonymous,id,use,que);
    }
    else
    {
        bool found = false;
        for (int i = 0; i<que.size(); ++i)
        {
            if (que[i].id==choice)
            {
                found = true;
                Question question;
                question.id = to_string((stoi(que[que.size()-1].id)+1));
                if (an)
                {
                    cout<<"do you the question to be anonymous? 1 for yes other no"<<endl;
                    int num;
                    cin>>num;
                    cin.ignore();
                    if (num==1)
                    {
                        question.anonymous = "1";
                    }
                    else
                    {
                        question.anonymous = "0";
                    }
                }
                else
                {
                    question.anonymous = "0";
                }
                question.from = id;
                question.to = userId;
                question.parent = choice;
                cout<<question.parent<<endl;
                cout<<"Enter question text: "<<endl;
                getline(cin,question.txt);
                que.push_back(question);
                updateQues(que);
                ask(anonymous,id,use,que);
            }
        }
        if (!found)
        {
            cout<<"It is not a valid id!"<<endl;
            menu(anonymous,id,use, que);
        }
    }

}
void listFeed(string &ano,string &id,vector<User> &use,vector<Question> &que)
{
    for (int i = 0; i<que.size(); ++i)
    {
        bool par = false;
        if (que[i].parent!="-1")continue;
        for (int j = i+1; j<que.size(); ++j)
        {
            if (que[j].parent==que[i].id)
            {
                par = true;
                break;
            }
        }
        if (par)
        {
            cout<<"Thread parent ";
        }
        cout<<"Qusetion Id ("<<que[i].id<<")";
        if (que[i].anonymous!="1")
        {
            cout<<" from user id("<<que[i].from<<")";
        }
        cout<<" To user id ("<<que[i].to<<")"<<endl;
        cout<<"Question: "<<que[i].txt<<endl;
        if (que[i].ans.size())cout<<"Answer: "<<que[i].ans<<endl;
        cout<<endl;
    }
    menu(ano,id,use, que);
}
void logOut()
{
    main();
}
void updateUser(vector<User> &use)
{
    ofstream ustr ("user.txt", ios::out | ios::trunc);
    for (auto account:use)
    {
        string record = account.id+","+account.password+","+account.name+","+account.email+","+account.anonymous;
        ustr<<record<<endl;
    }
    ustr.close();
}
void updateQues(vector<Question> &que)
{
    ofstream qstr ("questions.txt", ios::out | ios::trunc);
    for (auto question:que)
    {
        string record = question.id+","+question.from+","+question.to+","+question.txt+","+question.ans+","+question.parent+","+question.anonymous;
        qstr<<record<<endl;
    }
    qstr.close();
}
