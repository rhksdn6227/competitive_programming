int N, c[MAX_V][MAX_V], f[MAX_V][MAX_V];
int level[MAX_V]; // 레벨 그래프에서 정점의 레벨(S가 0)
int work[MAX_V]; // dfs 중, 이 정점이 몇 번째 간선까지 탐색했는지 기억하는 용도
vector<int> adj[MAX_V];
 
// 디닉 전용 bfs 함수
bool bfs(){
    // 레벨값 초기화
    fill(level, level+MAX_V, -1);
    level[S] = 0;
    
    queue<int> Q;
    Q.push(S);
    while(!Q.empty()){
        int curr = Q.front();
        Q.pop();
        for(int next: adj[curr]){
            // 레벨값이 설정되지 않았고, 간선에 residual이 있을 때만 이동
            if(level[next] == -1 && c[curr][next]-f[curr][next] > 0){
                level[next] = level[curr] + 1; // next의 레벨은 curr의 레벨 + 1
                Q.push(next);
            }
        }
    }
    // 싱크에 도달 가능하면 true, 아니면 false를 리턴
    return level[E] != -1;
}
 
// 디닉 전용 dfs 함수: curr에서 dest까지 최대 flow만큼의 유량을 보낼 것
int dfs(int curr, int dest, int flow){
    // base case: dest에 도달함
    if(curr == dest) return flow;
 
    // 현재 정점에서 인접한 정점들을 탐색
    // 이때, 이번 단계에서 이미 쓸모없다고 판단한 간선은 다시 볼 필요가 없으므로
    // work 배열로 간선 인덱스를 저장해 둠
    for(int &i=work[curr]; i<adj[curr].size(); i++){
        int next = adj[curr][i];
        // next의 레벨이 curr의 레벨 + 1이고, 간선에 residual이 남아있어야만 이동
        if(level[next] == level[curr]+1 && c[curr][next]-f[curr][next] > 0){
            // df: flow와 다음 dfs함수의 결과 중 최소값
            // 결과적으로 경로상의 간선들 중 가장 작은 residual이 됨
            int df = dfs(next, dest, min(c[curr][next]-f[curr][next], flow));
            // 증가 경로가 있다면, 유량을 df만큼 흘리고 종료
            if(df > 0){
                f[curr][next] += df;
                f[next][curr] -= df;
                return df;
            }
        }
    }
    // 증가 경로를 찾지 못함: 유량 0 흘림
    return 0;
}
 
 
 
int main(){
    // 그래프 정보 입력받기
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        int team;
        scanf("%d", &team);
        if(team == 1){
            c[S][i] = INF;
            adj[S].push_back(i);
            adj[i].push_back(S);
        }
        else if(team == 2){
            c[i][E] = INF;
            adj[i].push_back(E);
            adj[E].push_back(i);
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &c[i][j]);
            if(i != j) adj[i].push_back(j);
        }
    }
 
    // 디닉 알고리즘 수행
    int total = 0;
    // 레벨 그래프를 구축하여 싱크가 도달 가능한 동안 반복
    while(bfs()){
        fill(work, work+MAX_V, 0);
        // 차단 유량(blocking flow) 구하기
        while(1){
            int flow = dfs(S, E, INF); // dfs를 사용해 각 경로를 찾음
            if(flow == 0) break; // 더 이상 경로가 없으면 종료
            total += flow; // 총 유량에 이번에 구한 유량 더함
        }
    }
    printf("%d\n", total); // 슬픔의 정도의 최소 합 출력
 
    // 각 진영에 속한 사람을 판단하기 위해 소스에서의 도달가능성 판별
    bool visited[MAX_V] = {false};
    visited[S] = true;
    queue<int> Q;
    Q.push(S);
    while(!Q.empty()){
        int curr = Q.front();
        Q.pop();
        for(int next: adj[curr]){
            // 여유 용량이 남아있는 간선만을 이용
            if(!visited[next] && c[curr][next]-f[curr][next] > 0){
                visited[next] = true;
                Q.push(next);
            }
        }
    }
 
    // A진영에 속한 사람들: 소스에서 도달 가능
    for(int i=0; i<N; i++)
        if(visited[i]) printf("%d ", i+1);
    puts("");
    // B진영에 속한 사람들: 소스에서 도달 불가능
    for(int i=0; i<N; i++)
        if(!visited[i]) printf("%d ", i+1);
    puts("");
}
