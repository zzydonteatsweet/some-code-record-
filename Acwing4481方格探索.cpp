/*给定一个 n 行 m 列的方格矩阵。行坐标从上到下为 1∼n，列坐标从左到右为 1∼m

其中的每个方格，要么是空格（用 . 表示），要么包含障碍物（用 * 表示）。

初始时，一个人位于第 r
行第 c列的空格之中。
他可以沿上下左右四个方向进行移动，每次移动一格距离。

对于他的移动，有如下限制：

他不能进入到包含障碍物的方格中，也不能走出矩阵的边界。
在整个移动过程中，他向左移动的总次数不能超过 x次。
在整个移动过程中，他向右移动的总次数不能超过 y次。
请问，一共有多少个空格是此人可以抵达的？

注意，初始空格视为此人可达。
输入格式

第一行包含两个整数 n,m
第二行包含两个整数 r,c
第三行包含两个整数 x,y
接下来 n行，每行包含一个长度为 m

的由 . 和 * 组成的字符串，用来描述方格矩阵。

输入保证第 r
行第 c

列的方格一定是空格。
输出格式

一个整数，表示可达空格数量。
数据范围

前三个测试点满足 1≤n,m≤5
。
所有测试点满足 1≤n,m≤2000，1≤r≤n，1≤c≤m，0≤x,y≤109。


这是一个好题。原本以为是简单的bfs问题。但是因为有些点只能从左边走到，如果从右边走并且在路径途中先达到的话就会出现有些能够到达的点没有办法达到
分析过程：
  首先我们先定义每一个点能否到达用一个四位布尔数组来表示f(i,j,a,b)代表左边走了a次，右边走了b次能否到达（i，j）
  我们希望向右走的次数和向左走的次数最小所以可以向下这样优化
  优化：
   我们将b带入到值中。f(i,j,a)其中的值就是b
  优化：
    我们将我们可以得到j - sy = b - a。所以就可以去掉a这一维变量让变量变成两维。
   这样这就变成了最短路问题。最短路，权值都是正的可以用djkstra，有负权用spfa，都是一用bfs有0,1用双端队列广搜
   我们可以用双端队列来求。这样得到的每一个点都是向右走的步数最小的点。这样向左走的此数也会是最小的点。*/
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
#define x first
#define y second
const int N = 2005 ;
typedef pair<int, int> PII;

char map[N][N];
int dist[N][N] ;
bool st[N][N] ;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int n, m, sx, sy, a, b ;

void bfs() {
    deque<PII> q ;
    memset(dist, 0x3f, sizeof dist) ;
    dist[sx][sy] = 0 ;
    q.push_back({sx, sy}) ;
    while(q.size()) {
        auto t = q.front() ;
        q.pop_front() ;
        auto [x, y] = t ;
        if(st[x][y]) continue ;
        st[x][y] = true ;
        
        for(int i = 0 ; i < 4 ; i ++) {
            int tx = x + dx[i], ty = y + dy[i] ;
            if(tx < 0 || tx >= n || ty < 0 || ty >= m || map[tx][ty] == '*') continue ;
            int w = 0 ;
            if(i == 1) w = 1 ;
            
            if(dist[tx][ty] > dist[x][y] + w) {
                dist[tx][ty] = dist[x][y] + w ;
                if(w) q.push_back({tx, ty}) ;
                else q.push_front({tx, ty}) ;
            }
        }
    }
}

int main() {
    cin >> n >> m >> sx >> sy >> a >> b ;
    
    sx --, sy -- ;
    for(int i = 0 ; i < n ; i ++) {
        cin >> map[i] ;   
    }
    
    bfs() ;
    
    int res = 0;
    for(int i = 0 ; i < n ; i ++) {
        for(int j = 0 ; j < m ; j ++) {
            int t = dist[i][j] ;
            // cout << t << " " ;
            if(t <= b && t - (j - sy) <= a) {
                res ++ ;
            }
        }
        // puts("") ;
    }
    
    cout << res << endl ;
}
