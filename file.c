#include <stdio.h>
#include <string.h>

#define MAX_FILES 20   // 最大文件数
#define MAX_DATA 1024  // 每个文件最大大小

// 定义文件控制块结构
typedef struct {
    char name[20];    // 文件名
    int size;         // 文件大小
    char data[MAX_DATA]; // 文件内容
    int exist;        // 是否存在 1=存在 0=不存在
} File;

File disk[MAX_FILES]; // 模拟磁盘

// 创建文件
void createFile(char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (disk[i].exist == 0) {
            strcpy(disk[i].name, name);
            disk[i].size = 0;
            disk[i].exist = 1;
            printf("✅ 文件 %s 创建成功\n", name);
            return;
        }
    }
    printf("❌ 目录已满，无法创建\n");
}

// 写入文件
void writeFile(char *name, char *content) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (disk[i].exist == 1 && strcmp(disk[i].name, name) == 0) {
            strcpy(disk[i].data, content);
            disk[i].size = strlen(content);
            printf("✅ 写入成功\n");
            return;
        }
    }
    printf("❌ 文件不存在\n");
}

// 读取文件
void readFile(char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (disk[i].exist == 1 && strcmp(disk[i].name, name) == 0) {
            printf("📄 文件内容：%s\n", disk[i].data);
            return;
        }
    }
    printf("❌ 文件不存在\n");
}

// 删除文件
void deleteFile(char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (disk[i].exist == 1 && strcmp(disk[i].name, name) == 0) {
            disk[i].exist = 0;
            printf("✅ 文件删除成功\n");
            return;
        }
    }
    printf("❌ 文件不存在\n");
}

// 显示所有文件
void listFiles() {
    printf("\n===== 文件列表 =====\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (disk[i].exist == 1) {
            printf("文件名：%s\t大小：%d\n", disk[i].name, disk[i].size);
        }
    }
}

int main() {
    int op;
    char name[20];
    char content[MAX_DATA];

    while (1) {
        printf("\n===== 简单文件系统 =====\n");
        printf("1. 创建文件\n");
        printf("2. 写入文件\n");
        printf("3. 读取文件\n");
        printf("4. 删除文件\n");
        printf("5. 显示所有文件\n");
        printf("0. 退出\n");
        printf("请输入操作：");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                printf("输入文件名：");
                gets(name);
                createFile(name);
                break;
            case 2:
                printf("输入文件名：");
                gets(name);
                printf("输入内容：");
                gets(content);
                writeFile(name, content);
                break;
            case 3:
                printf("输入文件名：");
                gets(name);
                readFile(name);
                break;
            case 4:
                printf("输入文件名：");
                gets(name);
                deleteFile(name);
                break;
            case 5:
                listFiles();
                break;
            case 0:
                printf("退出文件系统\n");
                return 0;
            default:
                printf("输入错误！\n");
        }
    }
    return 0;
}
