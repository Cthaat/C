#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define MAX_STUDENTS 100
#define MAX_NAME_LEN 50
#define TABLE_SIZE 7 // 散列表大小（质数）
 
// 学生结构体，包含学生ID和姓名
typedef struct {
    int id;                    // 学生ID
    char name[MAX_NAME_LEN];   // 学生姓名
} Student;
 
// 链表节点结构体，包含学生数据和指向下一个节点的指针
typedef struct Node {
    Student data;
    struct Node* next;
} Node;
 
// 散列表，数组中每个元素是链表的头指针
Node* hashTable[TABLE_SIZE] = {NULL};
 
// 散列函数，计算学生ID对应的散列表索引
int hashFunction(int id) {
    return id % TABLE_SIZE;
}
 
// 插入学生信息到散列表
void insertStudent(Student s) {
    int index = hashFunction(s.id);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = s;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}
 
// 删除学生信息
void deleteStudent(int id) {
    int index = hashFunction(id);
    Node* curr = hashTable[index];
    Node* prev = NULL;
 
    while (curr) {
        if (curr->data.id == id) {
            if (prev) prev->next = curr->next;
            else hashTable[index] = curr->next;
            free(curr);
            printf("学生信息删除成功。\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("未找到该学生信息。\n");
}
 
// 修改学生信息
void updateStudent(int id) {
    int index = hashFunction(id);
    Node* curr = hashTable[index];
 
    while (curr) {
        if (curr->data.id == id) {
            printf("输入新的姓名：");
            scanf("%s", curr->data.name);
            printf("学生信息修改成功。\n");
            return;
        }
        curr = curr->next;
    }
    printf("未找到该学生信息。\n");
}
 
// 查询学生信息
void queryStudent(int id) {
    int index = hashFunction(id);
    Node* curr = hashTable[index];
 
    while (curr) {
        if (curr->data.id == id) {
            printf("学生ID: %d, 姓名: %s\n", curr->data.id, curr->data.name);
            return;
        }
        curr = curr->next;
    }
    printf("未找到该学生信息。\n");
}
 
// 保存学生信息到文件
void saveToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("文件打开失败");
        return;
    }
 
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = hashTable[i];
        while (curr) {
            fprintf(file, "%d %s\n", curr->data.id, curr->data.name);
            curr = curr->next;
        }
    }
    fclose(file);
    printf("数据保存成功。\n");
}
// 从文件读取
void loadFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("文件打开失败");
        return;
    }

    Student s;
    while (fscanf(file, "%d %s", &s.id, s.name) != EOF) {
        insertStudent(s);
    }
    fclose(file);
    printf("数据读取成功。\n");
}

// 打印学生信息
void printAllStudents() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = hashTable[i];
        while (curr) {
            printf("ID: %d, Name: %s\n", curr->data.id, curr->data.name);
            curr = curr->next;
        }
    }
}

// 生成随机数组
void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }
}

// 排序算法实现
void insertionSort(int arr[], int size, int* comparisons, int* moves) {
    *comparisons = 0;
    *moves = 0;
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            (*comparisons)++;
            (*moves)++;
        }
        arr[j + 1] = key;
        (*moves)++;
    }
}

// 选择排序算法实现
void selectionSort(int arr[], int size, int* comparisons, int* moves) {
    *comparisons = 0;
    *moves = 0;
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) {
            (*comparisons)++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            (*moves) += 3;
        }
    }
}

// 快速排序的辅助函数
void quickSortHelper(int arr[], int low, int high, int* comparisons, int* moves) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            (*comparisons)++;
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                (*moves) += 3;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        (*moves) += 3;

        int pi = i + 1;
        quickSortHelper(arr, low, pi - 1, comparisons, moves);
        quickSortHelper(arr, pi + 1, high, comparisons, moves);
    }
}

// 快速排序算法实现
void quickSort(int arr[], int size, int* comparisons, int* moves) {
    *comparisons = 0;
    *moves = 0;
    quickSortHelper(arr, 0, size - 1, comparisons, moves);
}

// 希尔排序算法实现
void shellSort(int arr[], int size, int* comparisons, int* moves) {
    *comparisons = 0;
    *moves = 0;
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
                (*comparisons)++;
                (*moves)++;
            }
            arr[j] = temp;
            (*moves)++;
        }
    }
}

// 比较多种排序算法
void compareSortingAlgorithms() {
    int size = 20;
    int arr[20], temp[20];
    int comparisons, moves;

    for (int i = 0; i < 3; i++) {
        printf("测试组 %d:\n", i + 1);
        generateRandomArray(arr, size);
        memcpy(temp, arr, size * sizeof(int));
        insertionSort(temp, size, &comparisons, &moves);
        printf("直接插入排序: 比较次数=%d, 移动次数=%d\n", comparisons, moves);

        memcpy(temp, arr, size * sizeof(int));
        selectionSort(temp, size, &comparisons, &moves);
        printf("简单选择排序: 比较次数=%d, 移动次数=%d\n", comparisons, moves);

        memcpy(temp, arr, size * sizeof(int));
        quickSort(temp, size, &comparisons, &moves);
        printf("快速排序: 比较次数=%d, 移动次数=%d\n", comparisons, moves);

        memcpy(temp, arr, size * sizeof(int));
        shellSort(temp, size, &comparisons, &moves);
        printf("希尔排序: 比较次数=%d, 移动次数=%d\n", comparisons, moves);

        printf("\n");
    }
}

// 主程序
int main() {
    srand(time(NULL));
    int choice, id;
    Student s;
    char filename[100];

    while (1) {
        printf("\n1. 增加学生\n2. 删除学生\n3. 修改学生\n4. 查询学生\n5. 保存到文件\n6. 读取文件\n7. 显示所有学生\n8. 排序算法比较\n9. 退出\n");
        printf("选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("输入学生ID和姓名: ");
                scanf("%d %s", &s.id, s.name);
                insertStudent(s);
                break;
            case 2:
                printf("输入学生ID: ");
                scanf("%d", &id);
                deleteStudent(id);
                break;
            case 3:
                printf("输入学生ID: ");
                scanf("%d", &id);
                updateStudent(id);
                break;
            case 4:
                printf("输入学生ID: ");
                scanf("%d", &id);
                queryStudent(id);
                break;
            case 5:
                printf("输入保存文件名: ");
                scanf("%s", filename);
                saveToFile(filename);
                break;
            case 6:
                printf("输入读取文件名: ");
                scanf("%s", filename);
                loadFromFile(filename);
                break;
            case 7:
                printAllStudents();
                break;
            case 8:
                compareSortingAlgorithms();
                break;
            case 9:
                return 0;
            default:
                printf("无效选择，请重新输入。\n");
        }
    }
}