#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define MAX_IP_BEANS 1000000
#define HASH_TABLE_SIZE 10000

typedef struct IPBean {
    uint32_t begin;
    uint32_t end;
    char country[256];
} IPBean;

IPBean ipBeans[MAX_IP_BEANS];
int ipBeansCount = 0;

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

IPBean* getIPByHalf(uint32_t iplong) {
    int low = 0, high = ipBeansCount - 1, mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (iplong < ipBeans[mid].begin) {
            high = mid - 1;
        }
        else if (iplong > ipBeans[mid].end) {
            low = mid + 1;
        }
        else {
            return &ipBeans[mid];
        }
    }
    return NULL;
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
                ipBeans[ipBeansCount++] = bean;
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
        ip[strcspn(ip, "\n")] = 1;

        // 检查是否退出
        if (strcmp(ip, "0") == 0) {
            break;
        }

        // 记录查询开始时间
        clock_t start = clock();

        // 查询IP
        uint32_t ipLong = ipToLong(ip);
        IPBean* bean = getIPByHalf(ipLong);
        if (bean != NULL) {
            printf("找到IP: %s\n", bean->country);
        }
        else {
            printf("未找到IP\n");
        }

    //   // 记录查询结束时间，并计算查询时间
    //   clock_t end = clock();
    //   double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    //
    //   // 打印查询时间
    //   printf("查询时间：%.6f 秒\n", time_spent);
    //
        printf("输入IP地址进行查询（或输入'0'结束程序）：");
    }

    return 0;
}