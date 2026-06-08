#include <stdio.h>
#include <string.h>

#define MAX 20          // 最大分区数
#define MEM_SIZE 1024   // 总内存大小 1024KB

// 定义内存分区结构体
struct Partition {
    int start;          // 起始地址
    int size;           // 分区大小
    int used;           // 1=已分配 0=空闲
} part[MAX];

int count = 1;          // 当前分区数量

// 初始化内存
void initMem() {
    part[0].start = 0;
    part[0].size = MEM_SIZE;
    part[0].used = 0;
}

// 首次适应算法 FF
int FF(int size) {
    for (int i = 0; i < count; i++) {
        if (!part[i].used && part[i].size >= size) {
            // 找到足够大的空闲分区
            if (part[i].size == size) {
                part[i].used = 1;
                return part[i].start;
            } else {
                // 拆分分区
                part[count].start = part[i].start + size;
                part[count].size = part[i].size - size;
                part[count].used = 0;

                part[i].size = size;
                part[i].used = 1;
                count++;
                return part[i].start;
            }
        }
    }
    return -1; // 分配失败
}

// 最佳适应算法 BF
int BF(int size) {
    int idx = -1;
    int min = 99999;

    for (int i = 0; i < count; i++) {
        if (!part[i].used && part[i].size >= size && part[i].size < min) {
            min = part[i].size;
            idx = i;
        }
    }

    if (idx == -1) return -1;

    if (part[idx].size == size) {
        part[idx].used = 1;
    } else {
        part[count].start = part[idx].start + size;
        part[count].size = part[idx].size - size;
        part[count].used = 0;

        part[idx].size = size;
        part[idx].used = 1;
        count++;
    }
    return part[idx].start;
}

// 回收内存
void freeMem(int start) {
    for (int i = 0; i < count; i++) {
        if (part[i].start == start) {
            part[i].used = 0;
            printf("回收起始地址为 %d 的分区成功\n", start);
            return;
        }
    }
    printf("未找到该分区\n");
}

// 显示内存状态
void showMem() {
    printf("\n======= 内存分区状态 =======\n");
    printf("起始地址\t大小\t\t状态\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t\t%d\t\t%s\n",
               part[i].start,
               part[i].size,
               part[i].used ? "已分配" : "空闲");
    }
}

int main() {
    initMem();
    int op, size, addr;

    while (1) {
        printf("\n===== 动态分区分配 =====\n");
        printf("1. FF 首次适应分配\n");
        printf("2. BF 最佳适应分配\n");
        printf("3. 回收内存\n");
        printf("4. 查看内存\n");
        printf("0. 退出\n");
        printf("请输入操作：");
        scanf("%d", &op);

        if (op == 1) {
            printf("请输入分配大小：");
            scanf("%d", &size);
            addr = FF(size);
            if (addr == -1)
                printf("分配失败！无足够空闲分区\n");
            else
                printf("分配成功，起始地址：%d\n", addr);
        }
        else if (op == 2) {
            printf("请输入分配大小：");
            scanf("%d", &size);
            addr = BF(size);
            if (addr == -1)
                printf("分配失败！无足够空闲分区\n");
            else
                printf("分配成功，起始地址：%d\n", addr);
        }
        else if (op == 3) {
            printf("请输入要回收的起始地址：");
            scanf("%d", &addr);
            freeMem(addr);
        }
        else if (op == 4) {
            showMem();
        }
        else if (op == 0) {
            printf("退出程序\n");
            break;
        }
        else {
            printf("输入错误！\n");
        }
    }
    return 0;
}
