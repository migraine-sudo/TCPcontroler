#include <stdio.h>
#include <stdlib.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
    WSADATA data;
    WORD v=MAKEWORD(2,0);
    WSAStartup(v,&data);
    char str[20]="";
    char str2[100]="ping$";
    //1.�����׽���
    SOCKET s1=socket(AF_INET,SOCK_STREAM,0);
    //2.�󶨵�ַ
    SOCKADDR_IN addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(70);
    addr.sin_addr.S_un.S_addr=inet_addr("172.20.10.3");// the BEcontroller's ip
    printf("������������\n");
    //����
    connect(s1,(SOCKADDR *)&addr,sizeof(addr));
  /***********************���Ĳ���****************************/
    while(1)
    {
        printf("shell-$:");
        gets(str2);//scanf�����ַ������׳������Ի�����gets()
        //printf("str2=%s",str2);//������
        strcat(str2,"$");//�ڷ��͵��ļ��������$���ţ���Ϊ������ʶ��
        // printf("str2=%s",str2);//������
        send(s1,str2,sizeof(str2),0);
    }
/***********************************************************/

    closesocket(s1);
    WSACleanup();
    if(getchar())
    {
        return 0;
    }
    else
    {
        Sleep(100);
    }
    return 0;
}
