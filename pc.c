#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define BUF_SIZE 5    //缓冲区大小
#define PROD_NUM 2    //生产者数量
#define CONS_NUM 3    //消费者数量

//信号量下标：empty空槽、full满产品、mutex互斥锁
#define EMPTY 0
#define FULL  1
#define MUTEX 2

//PV操作封装
static void P(int semid, int idx)
{
    struct sembuf op = {idx, -1, SEM_UNDO};
    semop(semid, &op, 1);
}
static void V(int semid, int idx)
{
    struct sembuf op = {idx, 1, SEM_UNDO};
    semop(semid, &op, 1);
}

//共享内存结构体：环形缓冲区
typedef struct{
    int buf[BUF_SIZE];
    int in,out;
}ShmBuf;

//生产者函数
void producer(int semid, ShmBuf *sh, int id)
{
    int item=0;
    while(item<12){ //每个生产者生产12个产品退出
        sleep(rand()%2);
        P(semid,EMPTY);
        P(semid,MUTEX);

        sh->buf[sh->in]=item++;
        printf("【生产者%d】生产：%d，存入位置：%d\n",id,item-1,sh->in);
        sh->in=(sh->in+1)%BUF_SIZE;

        V(semid,MUTEX);
        V(semid,FULL);
    }
    printf("生产者%d结束\n",id);
}

//消费者函数
void consumer(int semid, ShmBuf *sh, int id)
{
    int data;
    while(1){
        sleep(rand()%3);
        P(semid,FULL);
        P(semid,MUTEX);

        data=sh->buf[sh->out];
        printf("【消费者%d】取出：%d，取出位置：%d\n",id,data,sh->out);
        sh->out=(sh->out+1)%BUF_SIZE;

        V(semid,MUTEX);
        V(semid,EMPTY);
    }
}

int main()
{
    int semid,shmid,i;
    pid_t pid;
    unsigned short init_sem[3]={BUF_SIZE,0,1};//empty=5,full=0,mutex=1

    //创建信号量集
    semid=semget(IPC_PRIVATE,3,IPC_CREAT|0666);
    semctl(semid,0,SETALL,init_sem);

    //创建共享内存
    shmid=shmget(IPC_PRIVATE,sizeof(ShmBuf),IPC_CREAT|0666);
    ShmBuf *sh=(ShmBuf*)shmat(shmid,NULL,0);
    sh->in=sh->out=0;

    //创建生产者子进程
    for(i=0;i<PROD_NUM;i++){
        pid=fork();
        if(pid==0){
            producer(semid,sh,i);
            exit(0);
        }
    }
    //创建消费者子进程
    for(i=0;i<CONS_NUM;i++){
        pid=fork();
        if(pid==0){
            consumer(semid,sh,i);
            exit(0);
        }
    }

    //等待所有子进程结束
    while(wait(NULL)>0);

    //释放资源
    shmdt(sh);
    shmctl(shmid,IPC_RMID,NULL);
    semctl(semid,0,IPC_RMID);
    return 0;
}
