/*
    开始
    │
    ├─ 初始化 dis[s]=0，其余 dis=∞，vis 全 false
    ├─ 将 (0, s) 压入优先队列
    │
    └─► 优先队列为空？──是──► 结束
        │否
        │弹出堆顶 (d, u)
        │
        ├─ vis[u] == true？──是──► 忽略，继续循环（惰性删除）
        │否
        │标记 vis[u] = true  （确定 u 的最短距离 = d）
        │
        └─► 遍历 u 的所有邻接边 (v, w)
                │
                └─► 如果 dis[v] > dis[u] + w
                    │是
                    │更新 dis[v] = dis[u] + w
                    │将 (dis[v], v) 压入堆中
                    │否 → 跳过
        │
        └─► 回到循环顶部
*/
#include <cstring>
#include <queue>
#include <vector>

#define MAXN 50

struct Edge {
    int v, w;
};

struct Node {
    int dis, u;

    bool operator>(const Node& a) const { return dis > a.dis; }
};

std::vector<Edge> e[MAXN];
int dis[MAXN], vis[MAXN];

std::priority_queue<Node, std::vector<Node>, std::greater<Node>> q;

void dijkstra(int n, int s) {
    memset(dis, 0x3f, (n + 1) * sizeof(int));
    memset(vis, 0   , (n + 1) * sizeof(int));
    q.push({0,s});
    dis[s] = 0;
    while(!q.empty()){
        int curr_u = q.top().u;
        q.pop();
        if(vis[curr_u]) continue;
        vis[curr_u] = 1;
        for(Edge curr_edge : e[curr_u]){
            int cv = curr_edge.v, cw = curr_edge.w;
            if(dis[cv] > dis[curr_u] + cw){
                dis[cv] = dis[curr_u] + cw;
                q.push({dis[cv], cv});
            }
        }
    }
}