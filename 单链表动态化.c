#include <stdio.h>
#include <stdlib.h>

// 链表节点的结构体
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// 带头结点的单链表的结构体
typedef struct {
    ListNode* head;
    int length;
} LinkedList;

// 创建带头结点的单链表
void CreateLinkedList(LinkedList* L) {
    int n, data;
    L->head = (ListNode*)malloc(sizeof(ListNode));
    if (L->head == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    L->head->next = NULL;
    L->length = 0;

    printf("请输入链表的长度：");
    scanf_s("%d", &n);

    printf("请输入 %d 个元素（以空格分隔）：\n", n);
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &data);
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        if (newNode == NULL) {
            printf("内存分配失败\n");
            exit(1);
        }
        newNode->data = data;
        newNode->next = L->head->next;
        L->head->next = newNode;
        L->length++;
    }
}

// 输出单链表中的数据元素
void PrintLinkedList(LinkedList L) {
    ListNode* current = L.head->next;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 求单链表的长度
int GetLength(LinkedList L) {
    return L.length;
}

// 根据指定条件取元素
int GetElement(LinkedList L, int position) {
    if (position < 1 || position > L.length) {
        printf("位置不合法。\n");
        return -1;
    }
    ListNode* current = L.head->next;
    for (int i = 1; i < position; i++) {
        current = current->next;
    }
    return current->data;
}

// 修改元素
void SetElement(LinkedList* L, int position, int value) {
    if (position < 1 || position > L->length) {
        printf("位置不合法。\n");
        return;
    }
    ListNode* current = L->head->next;
    for (int i = 1; i < position; i++) {
        current = current->next;
    }
    current->data = value;
}

// 在指定位置插入元素
void InsertElement(LinkedList* L, int position, int value) {
    if (position < 1 || position > L->length + 1) {
        printf("插入位置不合法。\n");
        return;
    }
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    ListNode* current = L->head;
    for (int i = 1; i < position; i++) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    L->length++;
}

// 删除指定位置的元素
void DeleteElement(LinkedList* L, int position) {
    if (position < 1 || position > L->length) {
        printf("位置不合法。\n");
        return;
    }
    ListNode* current = L->head;
    for (int i = 1; i < position; i++) {
        current = current->next;
    }
    ListNode* temp = current->next;
    current->next = temp->next;
    free(temp);
    L->length--;
}

// 释放链表内存
void FreeLinkedList(LinkedList* L) {
    ListNode* current = L->head;
    ListNode* temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    L->head = NULL;
    L->length = 0;
}

// 主函数
int main() {
    LinkedList L;
    int choice, position, value;

    CreateLinkedList(&L);
    printf("链表创建成功，元素为：\n");
    PrintLinkedList(L);

    do {
        printf("\n单链表操作菜单：\n");
        printf("1. 输出单链表\n");
        printf("2. 求单链表长度\n");
        printf("3. 取元素\n");
        printf("4. 修改元素\n");
        printf("5. 插入元素\n");
        printf("6. 删除元素\n");
        printf("7. 释放链表内存\n");
        printf("8. 退出\n");
        printf("请输入你的选择：");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            PrintLinkedList(L);
            break;
        case 2:
            printf("链表长度为：%d\n", GetLength(L));
            break;
        case 3:
            printf("请输入要取得元素的位置：");
            scanf_s("%d", &position);
            printf("元素值为：%d\n", GetElement(L, position));
            break;
        case 4:
            printf("请输入要修改的元素位置和新值：");
            scanf_s("%d %d", &position, &value);
            SetElement(&L, position, value);
            break;
        case 5:
            printf("请输入要插入的元素位置和值：");
            scanf_s("%d %d", &position, &value);
            InsertElement(&L, position, value);
            break;
        case 6:
            printf("请输入要删除的元素位置：");
            scanf_s("%d", &position);
            DeleteElement(&L, position);
            break;
        case 7:
            FreeLinkedList(&L);
            printf("链表内存已释放。\n");
            break;
        case 8:
            printf("退出程序。\n");
            break;
        default:
            printf("无效的选择。\n");
        }
    } while (choice != 8);

    return 0;
}