#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// ˳���Ľṹ��
typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqList;

// �Ӽ��̶������ݣ�����˳���
void CreateSeqList(SeqList* L) {
    int n, i;
    printf("������˳���ĳ��ȣ�");
    scanf_s("%d", &n);
    if (n > MAX_SIZE) {
        printf("˳����ȳ���������ơ�\n");
        exit(1);
    }
    printf("������ %d ��Ԫ�أ�\n", n);
    for (i = 0; i < n; i++) {
        scanf_s("%d", &L->data[i]);
    }
    L->length = n;
}

// ���˳����е�����Ԫ��
void PrintSeqList(SeqList L) {
    int i;
    for (i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

// ��˳���ĳ���
int LengthOfSeqList(SeqList L) {
    return L.length;
}

// ����ָ������ȡԪ��
int GetElement(SeqList L, int position) {
    if (position < 1 || position > L.length) {
        printf("λ�ò��Ϸ���\n");
        return -1;
    }
    return L.data[position - 1];
}

// �޸�Ԫ��
void SetElement(SeqList* L, int position, int value) {
    if (position < 1 || position > L->length) {
        printf("λ�ò��Ϸ���\n");
        return;
    }
    L->data[position - 1] = value;
}

// ��ָ��λ�ò���Ԫ��
void InsertElement(SeqList* L, int position, int value) {
    if (position < 1 || position > L->length + 1 || L->length == MAX_SIZE) {
        printf("����λ�ò��Ϸ���˳���������\n");
        return;
    }
    for (int i = L->length; i >= position; i--) {
        L->data[i] = L->data[i - 1];
    }
    L->data[position - 1] = value;
    L->length++;
}

// ɾ��ָ��λ�õ�Ԫ��
void DeleteElement(SeqList* L, int position) {
    if (position < 1 || position > L->length) {
        printf("λ�ò��Ϸ���\n");
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
        printf("\n˳�������˵���\n");
        printf("1. ����˳���\n");
        printf("2. ���˳���\n");
        printf("3. ��˳�����\n");
        printf("4. ȡԪ��\n");
        printf("5. �޸�Ԫ��\n");
        printf("6. ����Ԫ��\n");
        printf("7. ɾ��Ԫ��\n");
        printf("8. �˳�\n");
        printf("���������ѡ��");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            CreateSeqList(&L);
            break;
        case 2:
            PrintSeqList(L);
            break;
        case 3:
            printf("˳�����Ϊ��%d\n", LengthOfSeqList(L));
            break;
        case 4:
            printf("������Ҫȡ��Ԫ�ص�λ�ã�");
            scanf_s("%d", &position);
            printf("Ԫ��ֵΪ��%d\n", GetElement(L, position));
            break;
        case 5:
            printf("������Ҫ�޸ĵ�Ԫ��λ�ú���ֵ��");
            scanf_s("%d %d", &position, &value);
            SetElement(&L, position, value);
            break;
        case 6:
            printf("������Ҫ�����Ԫ��λ�ú�ֵ��");
            scanf_s("%d %d", &position, &value);
            InsertElement(&L, position, value);
            break;
        case 7:
            printf("������Ҫɾ����Ԫ��λ�ã�");
            scanf_s("%d", &position);
            DeleteElement(&L, position);
            break;
        case 8:
            printf("�˳�����\n");
            break;
        default:
            printf("��Ч��ѡ��\n");
        }
    } while (choice != 8);

    return 0;
}