#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES 100   // 最大城市数量
#define INF INT_MAX      // 无穷大定义

// 交通图结构体定义
typedef struct {
    int numCities;               // 城市数量
    int graph[MAX_CITIES][MAX_CITIES]; // 邻接矩阵，表示城市之间的距离
} TrafficGraph;  // 交通图的数据结构定义

// 初始化交通图
void initGraph(TrafficGraph* g, int numCities) {  // 该函数用于初始化一个交通图
    g->numCities = numCities;  // 设置城市数量
    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            // 初始化邻接矩阵：如果是同一个城市，距离为0；否则为无穷大
            g->graph[i][j] = (i == j) ? 0 : INF; 
        }
    }
}

// 添加边
void addEdge(TrafficGraph* g, int city1, int city2, int distance) {  // 该函数用于添加城市之间的边
    g->graph[city1][city2] = distance;  // 设置城市1到城市2的距离
    g->graph[city2][city1] = distance;  // 设置城市2到城市1的距离（假设为无向图）
}

// 打印路径
void printPath(int prev[], int city) {  // 该函数用于打印从起点到给定城市的路径
    if (prev[city] == -1) {  // 如果没有前驱，说明已到达起点
        printf("%d", city);
        return;
    }
    printPath(prev, prev[city]);  // 递归打印前驱城市
    printf(" -> %d", city);  // 打印当前城市
}

// 使用 Dijkstra 算法计算最短路径
void dijkstra(TrafficGraph* g, int start, int end) {  // 该函数实现 Dijkstra 算法以计算最短路径
    int dist[MAX_CITIES];    // 用于存储起点到各城市的最短距离
    int visited[MAX_CITIES]; // 用于标记城市是否已访问
    int prev[MAX_CITIES];    // 用于存储每个城市的前驱
    int numCities = g->numCities; // 获取城市数量

    // 初始化
    for (int i = 0; i < numCities; i++) {
        dist[i] = INF;      // 初始化所有距离为无穷大
        visited[i] = 0;     // 初始化所有城市为未访问
        prev[i] = -1;       // 初始化所有前驱为-1（无前驱）
    }
    dist[start] = 0; // 起点到起点的距离为0

    // Dijkstra 主循环
    for (int i = 0; i < numCities; i++) {
        // 找到未访问节点中距离最近的节点
        int minDist = INF, u = -1; // 初始化最小距离和节点
        for (int j = 0; j < numCities; j++) {
            if (!visited[j] && dist[j] < minDist) {  // 找到未访问且距离最小的城市
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break; // 如果没有可访问的城市，结束循环

        visited[u] = 1; // 标记城市u为已访问

        // 更新邻接节点的距离
        for (int v = 0; v < numCities; v++) {
            if (!visited[v] && g->graph[u][v] != INF && dist[u] + g->graph[u][v] < dist[v]) {
                dist[v] = dist[u] + g->graph[u][v]; // 更新城市v的最短距离
                prev[v] = u; // 更新城市v的前驱为u
            }
        }
    }

    // 输出结果
    if (dist[end] == INF) { // 如果终点的距离仍为无穷大，则说明没有路径
        printf("城市 %d 和城市 %d 之间没有路径。\n", start, end);
    } else {
        printf("城市 %d 到城市 %d 的最短路径为：\n", start, end);
        printPath(prev, end); // 打印从起点到终点的路径
        printf("\n总距离：%d\n", dist[end]); // 打印总距离
    }
}

// 主程序
int main() {  // 主函数，程序入口
    TrafficGraph g; // 定义交通图
    int numCities, numEdges, city1, city2, distance;
    int startCity, endCity;

    // 输入城市数量
    printf("输入城市数量：");
    scanf("%d", &numCities);
    initGraph(&g, numCities); // 初始化交通图

    // 输入边的数量
    printf("输入边的数量：");
    scanf("%d", &numEdges);

    // 输入每条边的信息
    printf("输入每条边（城市1 城市2 距离）：\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &city1, &city2, &distance);
        addEdge(&g, city1, city2, distance); // 添加边
    }

    // 输入起点城市和终点城市
    printf("输入起点城市和终点城市：");
    scanf("%d %d", &startCity, &endCity);

    dijkstra(&g, startCity, endCity); // 调用Dijkstra算法计算最短路径

    return 0; // 结束程序
}
