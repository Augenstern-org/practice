#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// 边的结构：to 表示目标节点，weight 表示边权
struct Edge {
    int to;
    int weight;
};

// 用于优先队列的元素：距离和节点编号
// 我们需要小顶堆，所以定义 operator> 或使用 greater<> 比较器
struct State {
    int dist;   // 从源点到该节点的当前最短距离
    int node;   // 节点编号

    // 自定义比较：距离小的优先级高（小顶堆）
    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

vector<int> dijkstra(int start, int n, const vector<vector<Edge>>& graph) {
    // dist[i] 记录从 start 到 i 的最短距离，初始化为无穷大
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    // 小顶堆：存储 State，按 dist 从小到大排序
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, start});

    // 可选：visited 数组避免重复处理（但非必须，因为堆中旧条目会被跳过）
    // vector<bool> visited(n, false);

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        int u = cur.node;
        int d = cur.dist;

        // 如果这个距离已经大于记录的最短距离，说明是过时的旧条目，跳过
        if (d != dist[u]) continue;

        // 遍历 u 的所有邻居
        for (const Edge& e : graph[u]) {
            int v = e.to;
            int w = e.weight;
            // 松弛操作：如果通过 u 到达 v 的距离更短，则更新
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// 示例用法
int main() {
    // 节点数
    int n = 5;
    // 邻接表，graph[u] 存放从 u 出发的边
    vector<vector<Edge>> graph(n);

    // 添加边 (u, v, weight)
    // 无向图示例（若为有向图只加一条即可）
    auto add_edge = [&](int u, int v, int w) {
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // 无向
    };

    add_edge(0, 1, 2);
    add_edge(0, 2, 4);
    add_edge(1, 2, 1);
    add_edge(1, 3, 7);
    add_edge(2, 4, 3);
    add_edge(3, 4, 1);

    int start = 0;
    vector<int> dist = dijkstra(start, n, graph);

    cout << "从节点 " << start << " 出发到各点的最短距离：" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "节点 " << i << " : ";
        if (dist[i] == INT_MAX) cout << "不可达" << endl;
        else cout << dist[i] << endl;
    }

    return 0;
}