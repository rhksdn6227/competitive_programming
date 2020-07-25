#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAX_N = 100; // 최대 N, M
const int MAX_V = 2*(MAX_N+1); // 최대 정점 개수
const int S = MAX_V-2; // 소스 정점 번호
const int E = MAX_V-1; // 싱크 정점 번호
const int INF = 1000000000;
 
int main(){
    // 정점 번호: 0~MAX_N: 서점, MAX_N~MAX_N*2: 사람
    int N, M;
    int c[MAX_V][MAX_V] = {0}; // 각 간선의 용량
    int d[MAX_V][MAX_V] = {0}; // 각 간선의 비용
    int f[MAX_V][MAX_V] = {0}; // 각 간선에 흐르는 중인 유량
    vector<int> adj[MAX_V]; // 각 정점의 인접 리스트
 
    scanf("%d %d", &N, &M);
    // 각 사람 정점과 싱크 정점 사이 간선 추가 (비용 0)
    for(int i=MAX_N; i<MAX_N+N; i++){
        cin>>c[i][E];
        adj[E].push_back(i);
        adj[i].push_back(E);
    }
    // 소스 정점과 각 서점 정점 사이 간선 추가 (비용 0)
    for(int i=0; i<M; i++){
        cin>>c[S][i];
        adj[S].push_back(i);
        adj[i].push_back(S);
    }
    // 서점과 사람 사이 간선 추가 (비용 C_ij)
    for(int i=0; i<M; i++){
        for(int j=MAX_N; j<MAX_N+N; j++){
            cin>>d[i][j];
            d[j][i] = -d[i][j]; // 역방향 간선의 비용: 순방향의 -1배
            c[i][j] = INF; // 순방향 간선만 용량이 1 이상
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }
 
    int result = 0; // 최소 비용
    // MCMF 시작
    while(1){
        int prev[MAX_V], dist[MAX_V];
        bool inQ[MAX_V] = {0}; // 해당 정점이 큐 안에 있는가?
        queue<int> Q;
        fill(prev, prev+MAX_V, -1);
        fill(dist, dist+MAX_V, INF);
        dist[S] = 0;
        inQ[S] = true;
        Q.push(S);
 
        while(!Q.empty()){
            int curr = Q.front();
            Q.pop();
            inQ[curr] = false; // 큐에서 꺼냄
            for(int next: adj[curr]){
                // 최단 경로를 찾는 중이지만, 여전히 여유 용량 있어야 함
                if(c[curr][next]-f[curr][next] > 0 && dist[next] > dist[curr]+d[curr][next]){
                    dist[next] = dist[curr] + d[curr][next];
                    prev[next] = curr;
                    // 큐에 들어있지 않다면 큐에 넣음
                    if(!inQ[next]){
                        Q.push(next);
                        inQ[next] = true;
                    }
                }
            }
        }
        // 더 이상 경로가 없다면 루프 탈출
        if(prev[E] == -1) break;
 
        // 경로상에서 가장 residual이 작은 간선을 찾아 최대 흘릴 수 있는 flow 찾음
        int flow = INF;
        for(int i=E; i!=S; i=prev[i])
            flow = min(flow, c[prev[i]][i] - f[prev[i]][i]);
 
        // 경로상의 모든 간선에 flow만큼의 유량을 흘림
        for(int i=E; i!=S; i=prev[i]){
            result += flow * d[prev[i]][i]; // 총 비용이 각 간선 비용만큼 증가
            f[prev[i]][i] += flow;
            f[i][prev[i]] -= flow;
        }
    }
    // 정답 출력
    cout<<result;
}
