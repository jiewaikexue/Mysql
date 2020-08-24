#include<stdio.h>
#include<unistd.h>
#include <iostream>
#include <mysql/mysql.h>
#include<string>
using namespace std;
int main()
{ 
    //初始化一个mysql实例对象
    MYSQL * mysql=mysql_init(NULL);
    //记得释放 mysql_close()
    if(mysql==NULL)
    {
        cout<<"mysql实例初始化失败,暨 mysql_init函数"<<endl;
        return 0;
    }
    MYSQL * ms_res=NULL;
    ms_res= mysql_real_connect(mysql,"localhost","root","123456","xx",0,NULL,0);
    //ms_res= mysql_real_connect(mysql,"192.168.43.96","root","Shenjun@523","xxxx",3306,NULL,0);
    //设定字符集
    //函数:mysql_set_character_set(mysql句柄,字符集)
    if(ms_res==NULL)
    {
        cout<<"链接失败\n"<<mysql_error(mysql)<<endl;
        mysql_close(mysql);
        mysql=NULL;
        return 0;
    }
    cout<<"连上了"<<endl;

    //在此处添加业务代码:
    //    char *rSql="insert into test (id) values (1)";
    //    if(mysql_query(mysql,rSql))
    //    {
    //        cout<<"mysql_query  error"<<endl;
    //        mysql_close(mysql);
    //        mysql=NULL;
    //        return 0;
    //        
    //    }
    //查询相关
    //1.执行查询
    if(mysql_query(mysql,"select * from test"))
    {
        cout<<"mysql_query eror "<<endl;
        mysql_close(mysql);
        mysql=NULL;
        return 0;

    }
    //2.处理结果集:
    //取回结果集
    //关函mysql_store_result(操作句柄)  返回一个结果集:mysql_res
    // 对取回的结果集
    //mysql_row mysql_fetch_row(mysql *mysql_res)来获取结果集中的行
    //该函数的返回值,是下一行的结构
    //一旦完成了对结果集的操作,还要用mysql_free_result释放一下;
    //
    //
    //三步走占率
    //1.取回结果集
    MYSQL_RES * result=mysql_store_result(mysql);
    MYSQL_ROW  row;
    if(result!=NULL)//代表有结果集
    {
        cout<<"进入循环"<<endl;
        //处理结果集
        //获取列的个数:
        unsigned int i=0;
        MYSQL_FIELD * fields;
        unsigned int num_fields=0;
        //获取列数
        num_fields=mysql_num_fields(result);
        //获取字段名称结构体
        fields=mysql_fetch_fields(result);
        for(;i<num_fields;i++)
        {
            cout<<fields[i].name<<"\t";
        }
        cout<<endl;
        while((row=mysql_fetch_row(result)))
        {
            //这里来一个针对列的循环
            //printf(xxx, row[i])
            //mysql_free_result(result)释放结果集

            //一下代码是针对于test的
            //-----------------------------------low逼写法
            //for(int i=0;i<1;i++)
            // cout<<row[i]<<endl;
            //-------------------------------------


            //表头,格式,自动确定列数
            //
            //表头 mysql_fetch_fields(MYSQL_RES *result) 提供表头
            //列的个数:mysql_num_fileds(MYSQL_RES *result)
            //格式
            //1.结果集查询完成之后,会显示的那个1 row in set (0.00 sec)
            // 函数 mysql_affected_rows(mysql)
            // 2.结果集的多少秒
            for(int x=0;x<num_fields;x++)
            {

        
                //cout<<row[x];这样在打印null时会错
                printf("%s",row[x]);
                    if(x!=num_fields-1)
                printf("\t");
            }
            cout<<endl;

        }

        mysql_free_result(result);
    }

}

