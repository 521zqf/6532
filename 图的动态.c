#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20

// ͼ�Ľṹ��
typedef struct {
    int vertexNum; // ������
    int edgeNum;   // ����
    int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // �ڽӾ���
} Graph;

// ����BFS�Ķ��нṹ��
typedef struct {
    int data[MAX_VERTEX_NUM];
    int front;
    int rear;
} Queue;

// ��ʼ������
void InitQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// ���
void EnQueue(Queue* q, int value) {
    if (q->rear == MAX_VERTEX_NUM - 1) {
        printf("��������\n");
    }
    else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->data[q->rear] = value;
    }
}

// ����
int DeQueue(Queue* q) {
    int value;
    if (q->front == -1) {
        printf("����Ϊ��\n");
        return -1;
    }
    else {
        value = q->data[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1; // ���ö���
        }
        return value;
    }
}

// �������Ƿ�Ϊ��
int IsQueueEmpty(Queue* q) {
    return q->front == -1;
}

// ��ʼ��ͼ
void InitGraph(Graph* G, int vertexNum) {
    int i, j;
    G->vertexNum = vertexNum;
    G->edgeNum = 0;
    for (i = 0; i < vertexNum; i++) {
        for (j = 0; j < vertexNum; j++) {
            G->matrix[i][j] = 0; // ��ʼ���ڽӾ���
        }
    }
}

// ��ӱ�
void AddEdge(Graph* G, int start, int end) {
    G->matrix[start][end] = 1;
    G->matrix[end][start] = 1; // ����ͼ
    G->edgeNum++;
}

// �������������DFS��
void DFS(Graph* G, int v, int visited[]) {
    int i;
    visited[v] = 1; // ���Ϊ�ѷ���
    printf("%d ", v);
    for (i = 0; i < G->vertexNum; i++) {
        if (G->matrix[v][i] == 1 && !visited[i]) {
            DFS(G, i, visited);
        }
    }
}

// �������������BFS��
void BFS(Graph* G, int start) {
    int visited[MAX_VERTEX_NUM] = { 0 }; // ���ʱ������
    Queue q;
    InitQueue(&q);
    visited[start] = 1; // �����ʼ����Ϊ�ѷ���
    EnQueue(&q, start); // ���

    while (!IsQueueEmpty(&q)) {
        int current = DeQueue(&q);
        printf("%d ", current);
        for (int i = 0; i < G->vertexNum; i++) {
            if (G->matrix[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                EnQueue(&q, i);
            }
        }
    }
}

// ������
// ������
int main() {
    Graph G;
    int vertexNum, edgeNum, start, end;

    // ��ʼ��ͼ
    printf("�����붥������");
    scanf_s("%d", &vertexNum);
    InitGraph(&G, vertexNum);

    // ��ӱ�
    printf("�����������");
    scanf_s("%d", &edgeNum);
    for (int i = 0; i < edgeNum; i++) {
        printf("������ߵ���ʼ�ͽ������㣨�Կո�ָ�����");
        scanf_s("%d %d", &start, &end);
        AddEdge(&G, start, end);
    }

    // �����������
    int visited[MAX_VERTEX_NUM] = { 0 }; // ���ʱ������
    printf("�Ӷ���0��ʼ���������������DFS����\n");
    DFS(&G, 0, visited);
    printf("\n");

    // �����������
    printf("�Ӷ���0��ʼ�Ĺ������������BFS����\n");
    BFS(&G, 0);
    printf("\n");

    return 0;
}