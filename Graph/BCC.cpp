#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
 
const int MAX = 100000;
typedef pair<int, int> P;
 
int V, E, dcnt, dfsn[MAX];
vector<int> adj[MAX];
stack<P> S;
vector<vector<P>> bcc;
 
int DFS(int curr, int prev = -1){
    // 이 정점에 dfsn 부여
    // result는 DFS 트리상에서 트리, 역방향 간선으로 도달 가능한 최소의 dfsn
    int result = dfsn[curr] = ++dcnt;
 
    // 인접한 정점 순회
    for(int next: adj[curr]){
        // DFS 트리상에서 자신의 부모면 스킵
        if(next == prev) continue;
 
        // 아직 방문하지 않은 간선이면 스택에 간선 (curr, next)을 넣음
        if(dfsn[curr] > dfsn[next]) S.push(P(curr, next));
        // 역방향 간선
        if(dfsn[next] > 0) result = min(result, dfsn[next]);
        // 트리 간선
        else{
            // DFS로 이어서 탐색
            int temp = DFS(next, curr);
            result = min(result, temp);
            // next가 DFS 트리상에서 curr의 조상 노드로 갈 수 없음: 새 BCC 발견
            if(temp >= dfsn[curr]){
                // 여태 스택에 쌓여있던 간선을 빼서 BCC 구성
                // 이때, 간선 (curr, next)까지만 빼내야 함
                vector<P> currBCC;
                while(!S.empty() && S.top() != P(curr, next)){
                    currBCC.push_back(S.top());
                    S.pop();
                }
                currBCC.push_back(S.top());
                S.pop();
                bcc.push_back(currBCC);
            }
        }
    }
 
    // 최소 도달 가능 dfsn을 리턴
    return result;
}
 
int main(){
    // 그래프 입력받기
    scanf("%d %d", &V, &E);
    for(int i = 0; i < E; ++i){
        int u, v;
        scanf("%d %d", &u, &v);
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    // DFS 시도하며 BCC별로 분리
    for(int i = 0; i < V; ++i)
        if(dfsn[i] == 0) DFS(i);
 
    // BCC의 개수
    printf("%d\n", bcc.size());
    // 각 BCC에 속하는 간선 목록 출력
    for(auto &c: bcc){
        for(auto &p: c)
            printf("(%d, %d) ", p.first+1, p.second+1);
        puts("");
    }
}
[출처] 이중 연결 요소(Biconnected Component) (수정: 2019-02-13)|작성자 라이

