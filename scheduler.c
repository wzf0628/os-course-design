#include<stdio.h>
#include<stdlib.h>
#define N 10
typedef struct{
    int id;
    int arrive;
    int burst;
    int prio;
    int rest;
}PCB;
PCB p[N];
int n;

void FCFS(){
    int now=0,sum=0;
    printf("\n====FCFS调度====\n");
    for(int i=0;i<n;i++){
        if(now < p[i].arrive) now=p[i].arrive;
        printf("进程%d运行[%d~%d]\n",p[i].id,now,now+p[i].burst);
        sum += now+p[i].burst-p[i].arrive;
        now+=p[i].burst;
    }
    printf("平均周转时间：%.2f\n",1.0*sum/n);
}

void SJF(){
    int vis[N]={0},cnt=0,now=0,sum=0;
    printf("\n====SJF调度====\n");
    while(cnt<n){
        int sel=-1,minb=9999;
        for(int i=0;i<n;i++){
            if(!vis[i]&&p[i].arrive<=now&&p[i].burst<minb){
                minb=p[i].burst;sel=i;
            }
        }
        if(sel==-1){now++;continue;}
        vis[sel]=1;cnt++;
        printf("进程%d运行[%d~%d]\n",p[sel].id,now,now+p[sel].burst);
        sum += now+p[sel].burst-p[sel].arrive;
        now+=p[sel].burst;
    }
    printf("平均周转时间：%.2f\n",1.0*sum/n);
}

void RR(int q){
    int rest[N],now=0,sum=0,finish=0;
    for(int i=0;i<n;i++) rest[i]=p[i].burst;
    printf("\n====RR时间片轮转(q=%d)====\n",q);
    while(finish<n){
        int run=0;
        for(int i=0;i<n;i++){
            if(rest[i]>0&&p[i].arrive<=now){
                run=1;
                int t= rest[i]>q ? q:rest[i];
                printf("进程%d运行[%d~%d]\n",p[i].id,now,now+t);
                rest[i]-=t; now+=t;
                if(rest[i]==0){
                    finish++;
                    sum+=now-p[i].arrive;
                }
            }
        }
        if(!run) now++;
    }
    printf("平均周转时间：%.2f\n",1.0*sum/n);
}

void PRIO(){
    int vis[N]={0},cnt=0,now=0,sum=0;
    printf("\n====优先级调度====\n");
    while(cnt<n){
        int sel=-1,minp=9999;
        for(int i=0;i<n;i++){
            if(!vis[i]&&p[i].arrive<=now&&p[i].prio<minp){
                minp=p[i].prio;sel=i;
            }
        }
        if(sel==-1){now++;continue;}
        vis[sel]=1;cnt++;
        printf("进程%d运行[%d~%d]\n",p[sel].id,now,now+p[sel].burst);
        sum += now+p[sel].burst-p[sel].arrive;
        now+=p[sel].burst;
    }
    printf("平均周转时间：%.2f\n",1.0*sum/n);
}

int main(){
    printf("输入进程数量：");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        printf("进程%d：到达 服务 优先级：",i);
        scanf("%d%d%d",&p[i].arrive,&p[i].burst,&p[i].prio);
        p[i].id=i;
    }
    FCFS();
    SJF();
    RR(2);
    PRIO();
    return 0;
}
