#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define n 10 /*����ϵͳ���������ҵΪ n=10*/ 
#define m 10 /*����ϵͳ����Ŀ����������Ϊ m=10*/ 
#define minisize 100 

struct 
{ 
    float address; /*�ѷַ�������ʼ��ַ*/ 
    float length; /*�ѷַ����ĳ��ȣ���λΪ�ֽ�*/ 
    int flag; /*�ѷ�������Ǽ����ı�־����"0"��ʾ����Ŀ*/ 
}used_table[n]; /*�ѷ�������*/ 

struct 
{
    float address; /*��������ʼ��ַ*/ 
    float length; /*���������ȣ���λΪ�ֽ�*/ 
    int flag; /*��������Ǽ�����־����"0"��ʾ����Ŀ����"1"��ʾδ����*/ 
}free_table[m]; /*��������*/ 

int allocate(char J,float xk)  /*�������ŷ����㷨����xk��С�Ŀռ�*/ 
{ 
    int i,k; 
    float ad; 
    k=-1; 
    for(i=0;i<m;i++) /*Ѱ�ҿռ����xk����С�������Ǽ���k*/ 
    if(free_table[i].length>=xk&&free_table[i].flag==1) 
    if(k==-1||free_table[i].length<free_table[k].length) 
    k=i; 
    if(k==-1)/*δ�ҵ����ÿ�����������*/ 
    { 
        printf("Cannot find the idle partition\n"); 
        return 0; 
    }       
    /*�ҵ����ÿ���������ʼ���䣺����������С��Ҫ�����Ŀռ��С��msize��С���������ȫ�����䣻����������С��Ҫ�����Ŀռ�����minisize��С����ӿ���������һ���ַ���*/ 
    if(free_table[k].length-xk<=minisize) 
    { 
        free_table[k].flag=0; 
        ad=free_table[k].address; 
        xk=free_table[k].length; 
    } 
    else 
    { 
        free_table[k].length=free_table[k].length-xk; 
        ad=free_table[k].address+free_table[k].length; 
    } 
    /*�޸��ѷ�������*/ 
    i=0; 
    while(used_table[i].flag!=0&&i<n) /*Ѱ�ҿ���Ŀ��*/ 
    i++; 
    if(i>=n) /*�ޱ�Ŀ��д�ѷַ���*/ 
    { 
        printf("�ޱ�Ŀ��д�ѷַ���������\n"); 
        /*�������б�*/ 
        if(free_table[k].flag==0) 
    /*�ҵ����ǿ��з���*/ 
       free_table[k].flag=1; 
       else 
       {/*ǰ���ҵ�����ĳ�����з�����һ����*/ 
          free_table[k].length=free_table[k].length+xk; 
          return 0; 
       } 
    } 

    else 
    {/*�޸��ѷ����*/ 
        used_table[i].address=ad; 
        used_table[i].length=xk; 
        used_table[i].flag=J; 
    } 
    return 0; 
}/*������亯������*/ 

int reclaim(char J)  /*������ҵ��ΪJ����ҵ��ռ�Ŀռ�*/ 
{ 
    int i,k,j,s,t; 
    float S,L; 
    /*Ѱ���ѷ�����ж�Ӧ�Ǽ���*/ 
    s=0; 
    while((used_table[s].flag!=J||used_table[s].flag==0)&&s<n) 
    {
    s++; 
    if(s>=n)/*���ѷ�������Ҳ�������ΪJ����ҵ*/ 
    { 
        printf("can not find that job"); 
        return 0; 
    }
    }
    /*�޸��ѷ����*/ 
    used_table[s].flag=0; 
    /*ȡ�ù黹��������ʼ��ַS�ͳ���L*/ 
    S=used_table[s].address; 
    L=used_table[s].length; 
    j=-1;k=-1;i=0; 
    /*Ѱ�һ��շ����Ŀ��������ڣ����ڱ�Ŀk�����ڱ�Ŀj*/ 
    while(i<m&&(j==-1||k==-1)) 
    { 
        if(free_table[i].flag==1) 
        { 
            if(free_table[i].address+free_table[i].length==S) k=i;
            /*�ҵ�����*/ 
            if(free_table[i].address==S+L) j=i;/*�ҵ�����*/ 
        }    
        i++; 
    } 

    if(k!=-1)
    { 
        if(j!=-1) 
        /* ���ڿ����������ڿ�����������ϲ�*/ 
        { 
            free_table[k].length=free_table[j].length+free_table[k].length+L; 
            free_table[j].flag=0; 
        } 
        else 
        /*���ڿ����������ڷǿ������������ںϲ�*/ 
        free_table[k].length=free_table[k].length+L;
    } 
    else 
    {
        if(j!=-1) 
        /*���ڷǿ�����������Ϊ�������������ںϲ�*/ 
        { 
            free_table[j].address=S; 
            free_table[j].length=free_table[j].length+L; 
        } 
        else 
        /*�����ھ�Ϊ�ǿ���������������ֱ�����������ھ�Ϊ�ǿ���������������ֱ������*/ 
        {    
            /*�ڿ���������Ѱ�ҿ���Ŀ*/
            t=0; 
            while(free_table[t].flag==1&&t<m) 
            {
            t++; 
            if(t>=m)/*����������,���տռ�ʧ��,���ѷ����ԭ*/ 
            { 
                printf("������б�û�пռ�,���տռ�ʧ��\n"); 
                used_table[s].flag=J; 
                return 0; 
            }
            } 
            free_table[t].address=S; 
            free_table[t].length=L; 
            free_table[t].flag=1; 
        } 
    }
    return 0; 
}/*������պ�������*/ 

int main( ) 
{ 
    int i,a; 
    float xk; 
    char J; 
    /*���з������ʼ��*/ 
    free_table[0].address=1000; 
    free_table[0].length=300; 
    free_table[0].flag=1; 
    /*�������з���*/
    free_table[1].address=1301; 
    free_table[1].length=250; 
    free_table[1].flag=1;
    free_table[2].address=1552; 
    free_table[2].length=500; 
    free_table[2].flag=1;
    free_table[3].address=2500; 
    free_table[3].length=150; 
    free_table[3].flag=1;
    free_table[4].address=3000; 
    free_table[4].length=450; 
    free_table[4].flag=1;
    free_table[5].address=10240; 
    free_table[5].length=102400; 
    free_table[5].flag=1;
    for(i=6;i<m;i++) 
    free_table[i].flag=0; 
/*�ѷ�����ʼ����*/ 
    for(i=0;i<n;i++) 
    used_table[i].flag=0; 
    while(1) 
    { 
        printf("Functions: 0-exit,1-allocate the main memory,2-reclaim the main memory,3-display main memory\n"); 
        printf("please select functions(0~3) :"); 
        scanf("%d",&a); 
        switch(a) 
        { 
            case 0: exit(0); /*a=0�������*/ 

            case 1: /*a=1��������ռ�*/ 
            printf("input job name J and job required length xk: "); 
            scanf("%*c%c%f",&J,&xk); 
            allocate(J,xk);/*��������ռ�*/ 
            break;

            case 2: /*a=2��������ռ�*/ 
            printf("please input the job name which needs to be reclaimed"); 
            scanf("%*c%c",&J); 
            reclaim(J);/*��������ռ�*/ 
            break;

            case 3: /*a=3��ʾ�������*/ 
            /*�������������ѷ���������*/ 
            printf("display idle partition table:  \naddress length     flag\n"); 
            for(i=0;i<m;i++) 
            printf("%6.0f%9.0f%6d\n",free_table[i].address,free_table[i].length, free_table[i].flag); 
            printf(" press random button to display allocated table\n"); 
            getch(); 
            printf(" Display allocated partition table:  \naddress  length     flag\n"); 
            for(i=0;i<n;i++) 
            if(used_table[i].flag!=0) 
            printf("%6.0f%9.0f%6c\n",used_table[i].address,used_table[i].length, used_table[i].flag); 
            else 
            printf("%6.0f%9.0f%6d\n",used_table[i].address,used_table[i].length, used_table[i].flag); 
            break;

            default:printf("Selection fault \n"); 
        }/*case*/ 
    }/*while*/ 
}/*����������*/
