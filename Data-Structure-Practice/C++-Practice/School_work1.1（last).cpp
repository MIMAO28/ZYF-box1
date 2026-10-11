//School_work1.1(最后)

#include <bits/stdc++.h>
using namespace std;
#define MAXSIZE 100  //定义最大存储学生信息数量为100
#define COURSES 3 //定义课程成绩数量为3

typedef struct 
{
    char id[12];
    char name[20];
    float score[COURSES]={0};
    float total=0;
}Student;  //定义结构体：学生

typedef struct
{
    Student data[MAXSIZE]; //学生表
    int length=0; //当前存储学生数量
}StuList; //定义存储学生信息的顺序表


bool ListInsert(StuList *L)
{
    Student e;
    cout<<"请按顺序输入学生id，姓名，各科成绩："<<endl;
    cin>>e.id;
    cin>>e.name;
    for(int i=0;i<COURSES;i++)
    {
        cin>>e.score[i];
        e.total+=e.score[i];
    }
    if(L->length>=MAXSIZE)
    {
        return false;
    }
    L->data[L->length]=e;
    L->length++;

    return true;    
}

int LocateByID(StuList *L,char *id) //按学号查找，找到返回下标（0开始），找不到返回-1
{
    for(int i=0;i<L->length;i++)
    {
        if(strcmp(L->data[i].id,id)==0)
        {
            return i;
        }
    }
    return -1;
}

bool ListDelete(StuList *L,char *id) //按学号删除，成功返回true，没找到返回false
{
    int pos=LocateByID(L,id); //先找到这个学生在第几个
    if(pos==-1)
    {
        return false;
    }
    for(int i=pos;i<L->length-1;i++) //把后面的学生全部往前挪一格，把洞填上
    {
        L->data[i]=L->data[i+1];
    }
    L->length--; //人数减一

    return true;
}

void PrintList(StuList *L) //打印全表
{
    if(L->length==0)
    {
        cout<<"表中无数据"<<endl;
        return;
    }
    cout<<"学号        姓名        各科                总分"<<endl;
    for(int i=0;i<L->length;i++)
    {
        cout<<left<<setw(12)<<L->data[i].id<<setw(12)<<L->data[i].name;
        for(int j=0;j<COURSES;j++)
        {
            cout<<setw(7)<<L->data[i].score[j];
        }
        cout<<setw(8)<<L->data[i].total<<endl;
    }
}

//课程统计：以课程号为参数，一次遍历同时求最高分、最低分与平均分
//改进点：原来把同一段逻辑复制了三份，现在只保留一份，靠 course 参数区分课程
bool CourseStat(StuList *L,int course,float &mx,float &mn,float &av)
{
    if(L->length==0)
    {
        return false; //空表无法统计
    }
    mx=L->data[0].score[course]; //用第一个学生初始化，避免用0初值导致全负数时出错
    mn=L->data[0].score[course];
    float all=L->data[0].score[course];
    for(int i=1;i<L->length;i++)
    {
        float v=L->data[i].score[course];
        if(v>mx) mx=v;
        if(v<mn) mn=v;
        all+=v;
    }
    av=all/L->length;
    return true;
}

//课程分析：统计某门课的及格人数、及格率与分数段分布
bool CourseAnalysis(StuList *L,int course)
{
    if(L->length==0)
    {
        return false;
    }
    int seg[4]={0}; //分数段：<60、60-69、70-79、>=80
    int pass=0;
    for(int i=0;i<L->length;i++)
    {
        float v=L->data[i].score[course];
        if(v>=60) pass++;
        if(v<60) seg[0]++;
        else if(v<70) seg[1]++;
        else if(v<80) seg[2]++;
        else seg[3]++;
    }
    cout<<"第 "<<course+1<<" 门课分析："<<endl;
    cout<<"  及格人数："<<pass<<" / "<<L->length
        <<"    及格率："<<fixed<<setprecision(1)<<100.0*pass/L->length<<"%"<<endl;
    cout<<"  分数段分布：  不及格(<60) "<<setw(3)<<seg[0]<<" 人"
        <<"   60-69 "<<setw(3)<<seg[1]<<" 人"
        <<"   70-79 "<<setw(3)<<seg[2]<<" 人"
        <<"   80 以上 "<<setw(3)<<seg[3]<<" 人"<<endl;
    return true;
}

//按总分排名：先复制一份再排序，不打乱原始录入顺序（插入排序，稳定）
void SortByTotal(StuList *L)
{
    if(L->length==0)
    {
        cout<<"表中无数据"<<endl;
        return;
    }
    Student tmp[MAXSIZE];
    for(int i=0;i<L->length;i++)
    {
        tmp[i]=L->data[i]; //复制一份，保证原表顺序不变
    }
    for(int i=1;i<L->length;i++) //插入排序
    {
        Student key=tmp[i];
        int j=i-1;
        while(j>=0&&tmp[j].total<key.total) //按总分从高到低，严格小于保证并列时保持原顺序
        {
            tmp[j+1]=tmp[j];
            j--;
        }
        tmp[j+1]=key;
    }
    cout<<"名次  学号        姓名        总分"<<endl;
    for(int i=0;i<L->length;i++)
    {
        cout<<setw(4)<<i+1<<"  "<<left<<setw(12)<<tmp[i].id<<setw(12)<<tmp[i].name
            <<setw(8)<<tmp[i].total<<endl;
    }
}

void ShowGoals(StuList *L)
{
    if(L->length==0)
    {
        cout<<"暂无学生信息"<<endl;
        return;
    }
    cout<<"请输入要查询的科目:1.数学 2.英语 3.C++ 4.退出"<<endl;

    bool ow=true;
    while(ow)
    {
        char op;
        cin>>op;
        if(op=='4')
        {
            ow=false;
            break;
        }
        int course=-1;
        if(op=='1') course=0;
        else if(op=='2') course=1;
        else if(op=='3') course=2;
        if(course==-1)
        {
            cout<<"输入无效，请输入1-4"<<endl;
            continue;
        }
        float mx,mn,av;
        CourseStat(L,course,mx,mn,av);
        cout<<"最高分："<<mx<<"  最低分："<<mn<<"  平均分："<<av<<endl;
    }
}

void ShowAnalysis(StuList *L)
{
    if(L->length==0)
    {
        cout<<"暂无学生信息"<<endl;
        return;
    }
    cout<<"请输入要分析的科目:1.数学 2.英语 3.C++ 4.退出"<<endl;
    bool ow=true;
    while(ow)
    {
        char op;
        cin>>op;
        if(op=='4')
        {
            ow=false;
            break;
        }
        int course=-1;
        if(op=='1') course=0;
        else if(op=='2') course=1;
        else if(op=='3') course=2;
        if(course==-1)
        {
            cout<<"输入无效，请输入1-4"<<endl;
            continue;
        }
        CourseAnalysis(L,course);
    }
}

int main(void)
{
    StuList list;

    cout<<"当前存储学生数:"<<list.length<<endl;
    bool ow=true;
    while(ow)
    {
        cout<<"请选择操作：1.添加学生信息 2.查看科目最高分/最低分/平均分 3.删除学生信息"<<endl;
        cout<<"4.按总分排名 5.课程分析(及格率/分数段) 6.打印全表 7.退出系统"<<endl;
        char op;
        cin>>op;
        switch(op)
        {
            case '1':
            {
                bool x=ListInsert(&list);
                if(x) cout<<"添加成功"<<endl;
                else  cout<<"添加失败"<<endl;
                PrintList(&list);
                break;
            }
            case '2':
            {
                ShowGoals(&list);
                break;
            }
            case '3':
            {
                char did[12];
                cout<<"请输入要删除的学生学号："<<endl;
                cin>>did;
                bool z=ListDelete(&list,did);
                if(z) cout<<"删除成功"<<endl;
                else  cout<<"未找到该学号，删除失败"<<endl;
                PrintList(&list);
                break;
            }
            case '4':
            {
                SortByTotal(&list);
                break;
            }
            case '5':
            {
                ShowAnalysis(&list);
                break;
            }
            case '6':
            {
                PrintList(&list);
                break;
            }
            case '7':
            {
                cout<<"退出系统"<<endl;
                ow=false;
                break;
            }
            default:
            {
                cout<<"输入无效，请输入1-7"<<endl;
                break;
            }
        }
    }
    return 0;
}