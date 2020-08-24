#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
#define SET_TRAN "set autocommit=0" //把自动提交关掉
#define UNSET_TRAN "set autocommit=1" //自动提交开启
#define _HOST_ "127.0.0.1"
#define _USER_ "root"
#define _PASSWD_ "123456"
#define _DBNAME_ "test"

//设置事务为手动提交

int mysql_OperationTran(MYSQL *mysql)
{
    //开启事务
    int ret =mysql_query(mysql,"start transaction");
    if(ret !=0)
    {
        printf("mysql_operationTran  query statrt 失败: %s\n",mysql_error(mysql));
        return ret;
    }

    //设置事务为手动提交
    ret =mysql_query(mysql,SET_TRAN);
    if(ret!=0)
    {
        printf("mysql_OperationTran  set_tran error %s",mysql_error(mysql));
        return ret;
    }
    return ret;
}

int mysql_AutoTran(MYSQL * mysql)
{
    //开启事务
    int ret =mysql_query(mysql,"start transaction");
    if(ret !=0)
    {
        printf("mysql_AutoTran query start error %s",mysql_error(mysql));
        return ret;

    }
    //设置自动提交
    ret=mysql_query(mysql,UNSET_TRAN);
    if(ret!=0)
    {
        printf("mysql_AutoTran query UNSET_TRAN error %s",mysql_error(mysql));
        return ret;
    }
    return ret;
}

//手动提交的commit:
int mysql_Commit(MYSQL *mysql)
{
    int ret=mysql_query(mysql,"COMMIT");
    if(ret!=0)
    {
        printf("commit err: %s", mysql_error(mysql));
        return ret;
    }
    return ret;
}
//自动提交的不需要commit
//自动提交的无法回滚

//手动提交的回滚
int mysql_Rollback(MYSQL * mysql)
{
    int ret=mysql_query(mysql,"rollback");
    if(ret!=0)
    {
        printf("rollback  error %s",mysql_error(mysql));
        return ret;
    }
    return ret;
}
//此处再来一个重载, 回滚到某个save point


