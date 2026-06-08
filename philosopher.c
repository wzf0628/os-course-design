#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // 5个哲学家

pthread_mutex_t forks[N];  // 5根叉子
pthread_t phi[N];
int id[N] = {0,1,2,3,4};

// 哲学家行为
void *philosopher(void *arg) {
    int i = *(int*)arg;

    while(1) {
        printf("哲学家 %d 正在思考\n", i);
        sleep(1);

        // 拿左边叉子
        pthread_mutex_lock(&forks[i]);
        // 拿右边叉子
        pthread_mutex_lock(&forks[(i+1)%N]);

        printf("哲学家 %d 开始吃饭\n", i);
        sleep(2);
        printf("哲学家 %d 吃完了\n", i);

        // 放下叉子
        pthread_mutex_unlock(&forks[i]);
        pthread_mutex_unlock(&forks[(i+1)%N]);
    }
}

int main() {
    // 初始化互斥锁
    for(int i=0; i<N; i++)
        pthread_mutex_init(&forks[i], NULL);

    // 创建哲学家线程
    for(int i=0; i<N; i++)
        pthread_create(&phi[i], NULL, philosopher, &id[i]);

    // 等待
    for(int i=0; i<N; i++)
        pthread_join(phi[i], NULL);

    // 销毁
    for(int i=0; i<N; i++)
        pthread_mutex_destroy(&forks[i]);

    return 0;
}
