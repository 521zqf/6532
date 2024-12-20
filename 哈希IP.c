#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define MAX_IP_BEANS 1000000
#define HASH_TABLE_SIZE 10000
typedef struct IPBean {
    uint32_t begin;
    uint32_t end;
    char country[256];
    struct IPBean* next; // 指向下一个IPBean，用于处理哈希冲突
} IPBean;

IPBean ipBeans[MAX_IP_BEANS];
int ipBeansCount = 0;
IPBean* hashTable[HASH_TABLE_SIZE] = { 0 };

uint32_t ipToLong(const char* strIp) {
    unsigned long ip = 0;
    int section;
    char* endPtr;
    for (section = 0; section < 4; section++) {
        unsigned long val = strtoul(strIp, &endPtr, 10);
        ip += val << (24 - section * 8);
        if (section < 3) {
            if (*endPtr != '.') {
                return 0;
            }
            strIp = endPtr + 1;
        }
    }
    return (uint32_t)ip;
}

uint32_t hashFunction(uint32_t ip) {
    return ip % HASH_TABLE_SIZE; // 根据IP计算哈希值
}

void insertHashTable(IPBean* bean) {
    uint32_t index = hashFunction(bean->begin); // 获取哈希桶索引
    bean->next = hashTable[index]; // 将新节点的next指向当前哈希桶的头部
    hashTable[index] = bean; // 将哈希桶的头部指向新节点
}

IPBean* getIPByHash(uint32_t iplong) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        IPBean* current = hashTable[i];
        while (current != NULL) {
            if (iplong >= current->begin && iplong <= current->end) {
                return current; // 找到匹配的IP范围
            }
            current = current->next; // 移动到下一个节点
        }
    }
    return NULL; // 未找到匹配的IP范围
}

void load(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        perror("文件打开错误");
        return;
    }
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char* token;
        IPBean bean = { 0 };
        uint32_t begin, end;
        token = strtok(line, ",");
        if (token != NULL) {
            begin = ipToLong(token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                end = ipToLong(token);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strncpy(bean.country, token, sizeof(bean.country) - 1);
                    token = strtok(NULL, ",");
                }
            }
            bean.begin = begin;
            bean.end = end;
            if (ipBeansCount < MAX_IP_BEANS) {
                ipBeans[ipBeansCount] = bean;
                insertHashTable(&ipBeans[ipBeansCount]);
                ipBeansCount++;
            }
            else {
                printf("超过IP的最大数量\n");
                break;
            }
        }
    }
    fclose(file);
}

int main() {
    load("C:\\Users\\DELL\\Desktop\\ip_ranges.txt");

    char ip[16];
    printf("输入IP地址进行查询（或输入'0'结束程序）：");
    while (fgets(ip, sizeof(ip), stdin)) {
        // 移除换行符
        ip[strcspn(ip, "\n")] = '\0';

        // 检查是否退出
        if (strcmp(ip, "0") == 0) {
            break;
        }

        // 查询IP
        uint32_t ipLong = ipToLong(ip);
        IPBean* bean = getIPByHash(ipLong);
        if (bean != NULL) {
            printf("找到IP: %s\n", bean->country);
        }
        else {
            printf("未找到IP\n");
        }

        printf("输入IP地址进行查询（或输入'0'结束程序）：");
    }

    return 0;
}




