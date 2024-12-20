#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100     // 最大节点数
#define MAX_CODE_LEN 100  // 最大编码长度

typedef struct {
    int weight;         // 权值
    int parent;         // 父节点索引
    int left;           // 左子节点索引
    int right;          // 右子节点索引
} HuffmanNode;

typedef struct {
    char character;         // 对应的字符
    char code[MAX_CODE_LEN]; // 哈夫曼编码
} HuffmanCode;

// 构建哈夫曼树
void createHuffmanTree(HuffmanNode huffTree[], int weights[], int n) {
    int totalNodes = 2 * n - 1; // 哈夫曼树节点总数

    // 初始化哈夫曼树
    for (int i = 0; i < totalNodes; i++) {
        huffTree[i].weight = (i < n) ? weights[i] : 0;
        huffTree[i].parent = -1;
        huffTree[i].left = -1;
        huffTree[i].right = -1;
    }

    // 构建哈夫曼树
    for (int i = n; i < totalNodes; i++) {
        int min1 = -1, min2 = -1;

        // 找出权值最小的两个节点
        for (int j = 0; j < i; j++) {
            if (huffTree[j].parent == -1) { // 未被选中的节点
                if (min1 == -1 || huffTree[j].weight < huffTree[min1].weight) {
                    min2 = min1;
                    min1 = j;
                } else if (min2 == -1 || huffTree[j].weight < huffTree[min2].weight) {
                    min2 = j;
                }
            }
        }

        // 合并两个最小权值的节点
        huffTree[i].weight = huffTree[min1].weight + huffTree[min2].weight;
        huffTree[i].left = min1;
        huffTree[i].right = min2;
        huffTree[min1].parent = i;
        huffTree[min2].parent = i;
    }
}

// 生成哈夫曼编码
void generateHuffmanCodes(HuffmanNode huffTree[], HuffmanCode huffCodes[], int n) {
    char tempCode[MAX_CODE_LEN];
    for (int i = 0; i < n; i++) {
        int current = i;
        int parent = huffTree[current].parent;
        int codeLen = 0;

        while (parent != -1) {
            if (huffTree[parent].left == current) {
                tempCode[codeLen++] = '0';
            } else {
                tempCode[codeLen++] = '1';
            }
            current = parent;
            parent = huffTree[current].parent;
        }

        // 反转编码
        tempCode[codeLen] = '\0';
        for (int j = 0; j < codeLen; j++) {
            huffCodes[i].code[j] = tempCode[codeLen - j - 1];
        }
        huffCodes[i].code[codeLen] = '\0';
    }
}

// 打印哈夫曼编码
void printHuffmanCodes(char characters[], int weights[], HuffmanCode huffCodes[], int n) {
    printf("字符\t权值\t哈夫曼编码\n");
    for (int i = 0; i < n; i++) {
        printf("%c\t%d\t%s\n", characters[i], weights[i], huffCodes[i].code);
    }
}

// 测试主程序
int main() {
    char characters[MAX_NODES];
    int weights[MAX_NODES];
    int n;

    printf("输入字符数量：");
    scanf("%d", &n);
    getchar(); // 吸收换行符

    printf("输入字符和权值（格式：字符 权值）：\n");
    for (int i = 0; i < n; i++) {
        scanf("%c %d", &characters[i], &weights[i]);
        getchar(); // 吸收换行符
    }

    HuffmanNode huffTree[MAX_NODES];
    HuffmanCode huffCodes[MAX_NODES];

    createHuffmanTree(huffTree, weights, n);
    generateHuffmanCodes(huffTree, huffCodes, n);
    printHuffmanCodes(characters, weights, huffCodes, n);

    return 0;
}
