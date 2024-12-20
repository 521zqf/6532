#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20

// 图的结构体
typedef struct {
    int vertexNum; // 顶点数
    int edgeNum;   // 边数
    int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵
} Graph;

// 用于BFS的队列结构体
typedef struct {
    int data[MAX_VERTEX_NUM];
    int front;
    int rear;
} Queue;

// 初始化队列
void InitQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// 入队
void EnQueue(Queue* q, int value) {
    if (q->rear == MAX_VERTEX_NUM - 1) {
        printf("队列已满\n");
    }
    else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->data[q->rear] = value;
    }
}

// 出队
int DeQueue(Queue* q) {
    int value;
    if (q->front == -1) {
        printf("队列为空\n");
        return -1;
    }
    else {
        value = q->data[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1; // 重置队列
        }
        return value;
    }
}

// 检查队列是否为空
int IsQueueEmpty(Queue* q) {
    return q->front == -1;
}

// 初始化图
void InitGraph(Graph* G, int vertexNum) {
    int i, j;
    G->vertexNum = vertexNum;
    G->edgeNum = 0;
    for (i = 0; i < vertexNum; i++) {
        for (j = 0; j < vertexNum; j++) {
            G->matrix[i][j] = 0; // 初始化邻接矩阵
        }
    }
}

// 添加边
void AddEdge(Graph* G, int start, int end) {
    G->matrix[start][end] = 1;
    G->matrix[end][start] = 1; // 无向图
    G->edgeNum++;
}

// 深度优先搜索（DFS）
void DFS(Graph* G, int v, int visited[]) {
    int i;
    visited[v] = 1; // 标记为已访问
    printf("%d ", v);
    for (i = 0; i < G->vertexNum; i++) {
        if (G->matrix[v][i] == 1 && !visited[i]) {
            DFS(G, i, visited);
        }
    }
}

// 广度优先搜索（BFS）
void BFS(Graph* G, int start) {
    int visited[MAX_VERTEX_NUM] = { 0 }; // 访问标记数组
    Queue q;
    InitQueue(&q);
    visited[start] = 1; // 标记起始顶点为已访问
    EnQueue(&q, start); // 入队

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

// 主函数
// 主函数
int main() {
    Graph G;
    int vertexNum, edgeNum, start, end;

    // 初始化图
    printf("请输入顶点数：");
    scanf_s("%d", &vertexNum);
    InitGraph(&G, vertexNum);

    // 添加边
    printf("请输入边数：");
    scanf_s("%d", &edgeNum);
    for (int i = 0; i < edgeNum; i++) {
        printf("请输入边的起始和结束顶点（以空格分隔）：");
        scanf_s("%d %d", &start, &end);
        AddEdge(&G, start, end);
    }

    // 深度优先搜索
    int visited[MAX_VERTEX_NUM] = { 0 }; // 访问标记数组
    printf("从顶点0开始的深度优先搜索（DFS）：\n");
    DFS(&G, 0, visited);
    printf("\n");

    // 广度优先搜索
    printf("从顶点0开始的广度优先搜索（BFS）：\n");
    BFS(&G, 0);
    printf("\n");

    return 0;
}