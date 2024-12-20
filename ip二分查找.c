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
        perror("�ļ��򿪴���");
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
                printf("����IP���������\n");
                break;
            }
        }
    }
    fclose(file);
}

int main() {
    load("C:\\Users\\DELL\\Desktop\\ip_ranges.txt");

    char ip[16];
    printf("����IP��ַ���в�ѯ��������'0'�������򣩣�");
    while (fgets(ip, sizeof(ip), stdin)) {
        // �Ƴ����з�
        ip[strcspn(ip, "\n")] = 1;

        // ����Ƿ��˳�
        if (strcmp(ip, "0") == 0) {
            break;
        }

        // ��¼��ѯ��ʼʱ��
        clock_t start = clock();

        // ��ѯIP
        uint32_t ipLong = ipToLong(ip);
        IPBean* bean = getIPByHalf(ipLong);
        if (bean != NULL) {
            printf("�ҵ�IP: %s\n", bean->country);
        }
        else {
            printf("δ�ҵ�IP\n");
        }

    //   // ��¼��ѯ����ʱ�䣬�������ѯʱ��
    //   clock_t end = clock();
    //   double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    //
    //   // ��ӡ��ѯʱ��
    //   printf("��ѯʱ�䣺%.6f ��\n", time_spent);
    //
        printf("����IP��ַ���в�ѯ��������'0'�������򣩣�");
    }

    return 0;
}