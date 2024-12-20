#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 顺序表的结构体
typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqList;

// 从键盘读入数据，建立顺序表
void CreateSeqList(SeqList* L) {
    int n, i;
    printf("请输入顺序表的长度：");
    scanf_s("%d", &n);
    if (n > MAX_SIZE) {
        printf("顺序表长度超出最大限制。\n");
        exit(1);
    }
    printf("请输入 %d 个元素：\n", n);
    for (i = 0; i < n; i++) {
        scanf_s("%d", &L->data[i]);
    }
    L->length = n;
}

// 输出顺序表中的数据元素
void PrintSeqList(SeqList L) {
    int i;
    for (i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

// 求顺序表的长度
int LengthOfSeqList(SeqList L) {
    return L.length;
}

// 根据指定条件取元素
int GetElement(SeqList L, int position) {
    if (position < 1 || position > L.length) {
        printf("位置不合法。\n");
        return -1;
    }
    return L.data[position - 1];
}

// 修改元素
void SetElement(SeqList* L, int position, int value) {
    if (position < 1 || position > L->length) {
        printf("位置不合法。\n");
        return;
    }
    L->data[position - 1] = value;
}

// 在指定位置插入元素
void InsertElement(SeqList* L, int position, int value) {
    if (position < 1 || position > L->length + 1 || L->length == MAX_SIZE) {
        printf("插入位置不合法或顺序表已满。\n");
        return;
    }
    for (int i = L->length; i >= position; i--) {
        L->data[i] = L->data[i - 1];
    }
    L->data[position - 1] = value;
    L->length++;
}

// 删除指定位置的元素
void DeleteElement(SeqList* L, int position) {
    if (position < 1 || position > L->length) {
        printf("位置不合法。\n");
        return;
    }
    for (int i = position - 1; i < L->length - 1; i++) {
        L->data[i] = L->data[i + 1];
    }
    L->length--;
}

int main() {
    SeqList L;
    int choice, position, value;

    do {
        printf("\n顺序表操作菜单：\n");
        printf("1. 创建顺序表\n");
        printf("2. 输出顺序表\n");
        printf("3. 求顺序表长度\n");
        printf("4. 取元素\n");
        printf("5. 修改元素\n");
        printf("6. 插入元素\n");
        printf("7. 删除元素\n");
        printf("8. 退出\n");
        printf("请输入你的选择：");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            CreateSeqList(&L);
            break;
        case 2:
            PrintSeqList(L);
            break;
        case 3:
            printf("顺序表长度为：%d\n", LengthOfSeqList(L));
            break;
        case 4:
            printf("请输入要取得元素的位置：");
            scanf_s("%d", &position);
            printf("元素值为：%d\n", GetElement(L, position));
            break;
        case 5:
            printf("请输入要修改的元素位置和新值：");
            scanf_s("%d %d", &position, &value);
            SetElement(&L, position, value);
            break;
        case 6:
            printf("请输入要插入的元素位置和值：");
            scanf_s("%d %d", &position, &value);
            InsertElement(&L, position, value);
            break;
        case 7:
            printf("请输入要删除的元素位置：");
            scanf_s("%d", &position);
            DeleteElement(&L, position);
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