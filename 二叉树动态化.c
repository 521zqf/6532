#include <stdio.h>
#include <stdlib.h>

typedef struct BTNode {
    char data;
    struct BTNode* lChild;
    struct BTNode* rChild;
} BiTNode;

// 先序创建二叉树
void CreateBiTree(BiTNode** T) {
    char ch;
    scanf_s(" %c", &ch); // 使用%c来读取字符
    if (ch == '0') { // 假设'0'表示空节点
        *T = NULL;
        return;
    }
    else {
        *T = (BiTNode*)malloc(sizeof(BiTNode));
        (*T)->data = ch;
        printf("输入%c的左子节点：", ch);
        CreateBiTree(&((*T)->lChild));
        printf("输入%c的右子节点：", ch);
        CreateBiTree(&((*T)->rChild));
    }
    return;
}

// 先序遍历二叉树
void PreOrderBiTree(BiTNode* T) {
    if (T == NULL) {
        return;
    }
    else {
        printf("%c ", T->data);
        PreOrderBiTree(T->lChild);
        PreOrderBiTree(T->rChild);
    }
}

// 中序遍历二叉树
void MiddleOrderBiTree(BiTNode* T) {
    if (T == NULL) {
        return;
    }
    else {
        MiddleOrderBiTree(T->lChild);
        printf("%c ", T->data);
        MiddleOrderBiTree(T->rChild);
    }
}

// 后序遍历二叉树
void PostOrderBiTree(BiTNode* T) {
    if (T == NULL) {
        return;
    }
    else {
        PostOrderBiTree(T->lChild);
        PostOrderBiTree(T->rChild);
        printf("%c ", T->data);
    }
}

// 层次遍历二叉树
void LevelOrderBiTree(BiTNode* T) {
    if (T == NULL) return;
    BiTNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = T;
    while (front < rear) {
        BiTNode* node = queue[front++];
        printf("%c ", node->data);
        if (node->lChild != NULL) queue[rear++] = node->lChild;
        if (node->rChild != NULL) queue[rear++] = node->rChild;
    }
}

// 交换左右子树
void SwapChildren(BiTNode* T) {
    if (T != NULL) {
        BiTNode* temp = T->lChild;
        T->lChild = T->rChild;
        T->rChild = temp;
        SwapChildren(T->lChild);
        SwapChildren(T->rChild);
    }
}

// 二叉树的深度
int TreeDeep(BiTNode* T) {
    if (T != NULL) {
        int leftdeep = TreeDeep(T->lChild);
        int rightdeep = TreeDeep(T->rChild);
        return leftdeep > rightdeep ? leftdeep + 1 : rightdeep + 1;
    }
    else {
        return 0;
    }
}

// 叶子节点个数
int LeafCount(BiTNode* T) {
    if (T == NULL) {
        return 0;
    }
    else if (T->lChild == NULL && T->rChild == NULL) {
        return 1;
    }
    else {
        return LeafCount(T->lChild) + LeafCount(T->rChild);
    }
}

// 节点数
int NodeCount(BiTNode* T) {
    if (T == NULL) {
        return 0;
    }
    else {
        return NodeCount(T->lChild) + NodeCount(T->rChild) + 1;
    }
}

// 主函数
int main() {
    BiTNode* T;
    int depth, leafCount, nodeCount;
    printf("请输入第一个节点的值，'0'表示没有子节点：\n");
    CreateBiTree(&T);

    printf("先序遍历二叉树：");
    PreOrderBiTree(T);
    printf("\n");

    printf("中序遍历二叉树：");
    MiddleOrderBiTree(T);
    printf("\n");

    printf("后序遍历二叉树：");
    PostOrderBiTree(T);
    printf("\n");

    printf("层次遍历二叉树：");
    LevelOrderBiTree(T);
    printf("\n");

    depth = TreeDeep(T);
    printf("树的深度为：%d\n", depth);

    leafCount = LeafCount(T);
    printf("叶子节点个数:%d\n", leafCount);

    nodeCount = NodeCount(T);
    printf("节点数:%d\n", nodeCount);

    SwapChildren(T);
    printf("交换左右子树后的先序遍历：");
    PreOrderBiTree(T);
    printf("\n");

    return 0;
}