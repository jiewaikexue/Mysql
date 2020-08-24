#include<time.h>
#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
void Replace_Now_time(string &str)
{
    int pos;
    pos = str.find(" ");
    while(pos != -1){
        // str.length()求字符的长度，注意str必须是string类型
        str.replace(pos,string(" ").length(),"_");
        pos = str.find(" ");
    }
}

int My_Popen(string &commond)
{
    //FILE *pp=popen("touch /home/jie/000_数据库课设暂时性/2_定时备份相关/cpp/c","w");
    FILE *pp=popen(commond.c_str(),"w");

    if(pp==NULL)
    {
        cout<<"popen erroe r"<<endl;
        return 0;
    }
    pclose(pp);
    return 0;
}

int main()
{
    time_t timep;

    time(&timep); //获取从1970至今过了多少秒，存入time_t类型的timep
    //printf("%s", ctime(&timep));//用ctime将秒数转化成字符串格式，输出：Thu Feb 28 14:14:17 2019

    string now_time=ctime(&timep);
    Replace_Now_time(now_time);
    cout<<now_time<<endl;
    string commond="mysqldump -uroot -p123456 test4 my_test ";
    commond.append("> ");
    //指向一个存放记录的文件夹:
    string target_dir="/home/jie/000_数据库课设暂时性/2_定时备份相关/9_定时备份文件所在地/";
    commond+=target_dir; 
    now_time.erase(now_time.end()-1);
    commond.append(now_time);
    commond.append(".sql");
    cout<<commond;
    
    My_Popen(commond);
    return 0;
}
