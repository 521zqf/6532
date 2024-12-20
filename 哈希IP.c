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
    struct IPBean* next; // ָ����һ��IPBean�����ڴ����ϣ��ͻ
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
    return ip % HASH_TABLE_SIZE; // ����IP�����ϣֵ
}

void insertHashTable(IPBean* bean) {
    uint32_t index = hashFunction(bean->begin); // ��ȡ��ϣͰ����
    bean->next = hashTable[index]; // ���½ڵ��nextָ��ǰ��ϣͰ��ͷ��
    hashTable[index] = bean; // ����ϣͰ��ͷ��ָ���½ڵ�
}

IPBean* getIPByHash(uint32_t iplong) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        IPBean* current = hashTable[i];
        while (current != NULL) {
            if (iplong >= current->begin && iplong <= current->end) {
                return current; // �ҵ�ƥ���IP��Χ
            }
            current = current->next; // �ƶ�����һ���ڵ�
        }
    }
    return NULL; // δ�ҵ�ƥ���IP��Χ
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
                ipBeans[ipBeansCount] = bean;
                insertHashTable(&ipBeans[ipBeansCount]);
                ipBeansCount++;
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
        ip[strcspn(ip, "\n")] = '\0';

        // ����Ƿ��˳�
        if (strcmp(ip, "0") == 0) {
            break;
        }

        // ��ѯIP
        uint32_t ipLong = ipToLong(ip);
        IPBean* bean = getIPByHash(ipLong);
        if (bean != NULL) {
            printf("�ҵ�IP: %s\n", bean->country);
        }
        else {
            printf("δ�ҵ�IP\n");
        }

        printf("����IP��ַ���в�ѯ��������'0'�������򣩣�");
    }

    return 0;
}




