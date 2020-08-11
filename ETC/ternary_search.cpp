int N, x[100000];
 
// 전봇대 간의 간격을 x0으로 할 때 필요한 이동거리 합
inline long long f(int x0){
    long long result = 0;
    for(int i = 1; i < N; ++i)
        result += abs(1LL*x0*i - x[i]);
    return result;
}
 
int main(){
    // 입력받기
    scanf("%d", &N);
    for(int i = 0; i < N; ++i)
        scanf("%d", x+i);
 
    // 삼분 탐색
    int lo = 0, hi = x[N-1];
    while(hi-lo >= 3){
        int p = (lo*2 + hi)/3, q = (lo + hi*2)/3;
        if(f(p) <= f(q)) hi = q;
        else lo = p;
    }
 
    // 최종 구간 [lo, hi] 안에서 최솟값을 찾아냄
    long long result = INF;
    for(int i = lo; i <= hi; ++i)
        result = min(f(i), result);
 
    // 결과 출력
    printf("%lld\n", result);
}

[출처] 삼분 탐색(Ternary Search)|작성자 라이
