#include <stdio.h>
#define MAX 100
//最优置换OPT
int OPT(int list[],int n,int block)
{
    int mem[MAX]={0},cnt=0,lack=0;
    int i,j,k,flag,far,pos;
    for(i=0;i<n;i++)
    {
        flag=0;
        //查找是否已在内存
        for(j=0;j<block;j++){
            if(mem[j]==list[i]){flag=1;break;}
        }
        if(flag==1) continue;
        lack++;
        //内存有空位
        if(cnt<block){mem[cnt++]=list[i];continue;}
        //找未来最远出现的页面淘汰
        far=-1;pos=0;
        for(j=0;j<block;j++)
        {
            int next=n;
            for(k=i+1;k<n;k++)
            {
                if(list[k]==mem[j]){next=k;break;}
            }
            if(next>far){far=next;pos=j;}
        }
        mem[pos]=list[i];
    }
    printf("OPT缺页次数:%d 缺页率:%.2f%%\n",lack,lack*100.0/n);
    return lack;
}
//先进先出FIFO
int FIFO(int list[],int n,int block)
{
    int mem[MAX]={0},cnt=0,lack=0,p=0;
    int i,j,flag;
    for(i=0;i<n;i++)
    {
        flag=0;
        for(j=0;j<block;j++){
            if(mem[j]==list[i]){flag=1;break;}
        }
        if(flag) continue;
        lack++;
        if(cnt<block){mem[cnt++]=list[i];continue;}
        mem[p]=list[i];
        p=(p+1)%block;
    }
    printf("FIFO缺页次数:%d 缺页率:%.2f%%\n",lack,lack*100.0/n);
    return lack;
}
//最近最少LRU
int LRU(int list[],int n,int block)
{
    int mem[MAX]={0},cnt=0,lack=0;
    int i,j,k,flag,min,pos;
    int use[MAX]={0};//记录上次访问下标
    for(i=0;i<n;i++)
    {
        flag=0;
        for(j=0;j<block;j++){
            if(mem[j]==list[i]){
                flag=1;use[j]=i;break;
            }
        }
        if(flag) continue;
        lack++;
        if(cnt<block){mem[cnt]=list[i];use[cnt]=i;cnt++;continue;}
        //淘汰最久没使用
        min=9999;pos=0;
        for(j=0;j<block;j++){
            if(use[j]<min){min=use[j];pos=j;}
        }
        mem[pos]=list[i];use[pos]=i;
    }
    printf("LRU缺页次数:%d 缺页率:%.2f%%\n",lack,lack*100.0/n);
    return lack;
}

int main()
{
    int page[MAX],num,block,i;
    printf("输入页面访问序列长度：");
    scanf("%d",&num);
    printf("依次输入页面号：");
    for(i=0;i<num;i++) scanf("%d",&page[i]);
    printf("输入内存物理块数量：");
    scanf("%d",&block);
    FIFO(page,num,block);
    LRU(page,num,block);
    OPT(page,num,block);
    return 0;
}
