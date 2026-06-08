#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;  // 读写锁

// 读者线程
void *reader(void *arg) {
    int id = *(int*)arg;
    while(1) {
        pthread_rwlock_rdlock(&rwlock);  // 加读锁
        printf("读者 %d 正在读取数据\n", id);
        sleep(1);
        printf("读者 %d 读取结束\n", id);
        pthread_rwlock_unlock(&rwlock);  // 解锁
        sleep(1);
    }
}

// 写者线程
void *writer(void *arg) {
    int id = *(int*)arg;
    while(1) {
        pthread_rwlock_wrlock(&rwlock);  // 加写锁
        printf("写者 %d 正在写入数据\n", id);
        sleep(2);
        printf("写者 %d 写入结束\n", id);
        pthread_rwlock_unlock(&rwlock);  // 解锁
        sleep(2);
    }
}

int main() {
    pthread_t r1, r2, w1;
    int id1 = 1, id2 = 2, id3 = 1;

    pthread_rwlock_init(&rwlock, NULL);

    // 创建读者、写者
    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&r2, NULL, reader, &id2);
    pthread_create(&w1, NULL, writer, &id3);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    pthread_rwlock_destroy(&rwlock);
    return 0;
}
