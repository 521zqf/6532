#include <stdio.h>
#include <stdlib.h>

// ����ڵ�Ľṹ��
typedef struct ListNode {
    int data;
    struct ListNode* next;
} ListNode;

// ��ͷ���ĵ�����Ľṹ��
typedef struct {
    ListNode* head;
    int length;
} LinkedList;

// ������ͷ���ĵ�����
void CreateLinkedList(LinkedList* L) {
    int n, data;
    L->head = (ListNode*)malloc(sizeof(ListNode));
    if (L->head == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    L->head->next = NULL;
    L->length = 0;

    printf("����������ĳ��ȣ�");
    scanf_s("%d", &n);

    printf("������ %d ��Ԫ�أ��Կո�ָ�����\n", n);
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &data);
        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        if (newNode == NULL) {
            printf("�ڴ����ʧ��\n");
            exit(1);
        }
        newNode->data = data;
        newNode->next = L->head->next;
        L->head->next = newNode;
        L->length++;
    }
}

// ����������е�����Ԫ��
void PrintLinkedList(LinkedList L) {
    ListNode* current = L.head->next;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// ������ĳ���
int GetLength(LinkedList L) {
    return L.length;
}

// ����ָ������ȡԪ��
int GetElement(LinkedList L, int position) {
    if (position < 1 || position > L.length) {
        printf("λ�ò��Ϸ���\n");
        return -1;
    }
    ListNode* current = L.head->next;
    for (int i = 1; i < position; i++) {
        current = current->next;
    }
    return current->data;
}

// �޸�Ԫ��
void SetElement(LinkedList* L, int position, int value) {
    if (position < 1 || position > L->length) {
        printf("λ�ò��Ϸ���\n");
        return;
    }
    ListNode* current = L->head->next;
    for (int i = 1; i < position; i++) {
        current = current->next;
    }
    current->data = value;
}

// ��ָ��λ�ò���Ԫ��
void InsertElement(LinkedList* L, int position, int value) {
    if (position < 1 || position > L->length + 1) {
        printf("����λ�ò��Ϸ���\n");
        return;
    }
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("�ڴ����ʧ��\n");
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

// ɾ��ָ��λ�õ�Ԫ��
void DeleteElement(LinkedList* L, int position) {
    if (position < 1 || position > L->length) {
        printf("λ�ò��Ϸ���\n");
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

// �ͷ������ڴ�
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

// ������
int main() {
    LinkedList L;
    int choice, position, value;

    CreateLinkedList(&L);
    printf("�������ɹ���Ԫ��Ϊ��\n");
    PrintLinkedList(L);

    do {
        printf("\n����������˵���\n");
        printf("1. ���������\n");
        printf("2. ��������\n");
        printf("3. ȡԪ��\n");
        printf("4. �޸�Ԫ��\n");
        printf("5. ����Ԫ��\n");
        printf("6. ɾ��Ԫ��\n");
        printf("7. �ͷ������ڴ�\n");
        printf("8. �˳�\n");
        printf("���������ѡ��");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            PrintLinkedList(L);
            break;
        case 2:
            printf("������Ϊ��%d\n", GetLength(L));
            break;
        case 3:
            printf("������Ҫȡ��Ԫ�ص�λ�ã�");
            scanf_s("%d", &position);
            printf("Ԫ��ֵΪ��%d\n", GetElement(L, position));
            break;
        case 4:
            printf("������Ҫ�޸ĵ�Ԫ��λ�ú���ֵ��");
            scanf_s("%d %d", &position, &value);
            SetElement(&L, position, value);
            break;
        case 5:
            printf("������Ҫ�����Ԫ��λ�ú�ֵ��");
            scanf_s("%d %d", &position, &value);
            InsertElement(&L, position, value);
            break;
        case 6:
            printf("������Ҫɾ����Ԫ��λ�ã�");
            scanf_s("%d", &position);
            DeleteElement(&L, position);
            break;
        case 7:
            FreeLinkedList(&L);
            printf("�����ڴ����ͷš�\n");
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