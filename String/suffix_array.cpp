const int MAX = 1<<19;
 
char S[MAX];
int N, d, sa[MAX], pos[MAX]; // pos: 그룹 번호
 
// 접미사 비교에 사용할 비교 함수
bool cmp(int i, int j){
    // 먼저 자신의 위치의 문자를 비교
    if(pos[i] != pos[j]) return pos[i] < pos[j];
    // 문자가 같으면 d칸 뒤의 문자끼리 비교
    i += d;
    j += d;
    return (i < N && j < N) ? (pos[i] < pos[j]) : (i > j);
}
 
// S를 사용해 sa 배열을 만드는 함수
void constructSA(){
    N = strlen(S);
    // 전처리
    for(int i=0; i<N; i++){
        sa[i] = i;
        pos[i] = S[i]; // 제일 첫 번째 루프에서는 제자리 문자로 비교
    }
    // d를 2배씩 늘려가면서 매번 앞에서부터 d*2글자만 보고 접미사 정렬
    for(d=1; ; d*=2){
        sort(sa, sa+N, cmp);
 
        // temp: 새로운 그룹 번호
        int temp[MAX] = {0};
        // 앞에서부터 훑으면서 각 접미사가 서로 다른 그룹에 속할 때마다 그룹 번호 증가시킴
        for(int i=0; i<N-1; i++)
            temp[i+1] = temp[i] + cmp(sa[i], sa[i+1]);
        // pos 배열을 temp 배열로 대체
        for(int i=0; i<N; i++)
            pos[sa[i]] = temp[i];
 
        // 모든 접미사가 다른 그룹으로 나뉘어졌다면 종료
        if(temp[N-1] == N-1) break;
    }
}

 // SA가 주어지면 LCP를 만드는 함수
void constructLCP(){
    // pos[i] = S[i:]가 sa의 몇 번째에 있는가 (pos[sa[i]] = i)
    // 제일 긴 접미사(S)부터 시작한다.
    // 매 루프마다 k>0이면 k--
    for(int i=0, k=0; i<N; i++, k=max(k-1, 0)){
        // 마지막 접미사(길이 1)면 아무것도 안 함
        if(pos[i] == N-1) continue;
 
        // 바로 아래 인접한 접미사와 비교하여 앞에서부터 몇 개의 글자가 일치하는지 센다
        for(int j=sa[pos[i]+1]; S[i+k]==S[j+k]; k++);
        lcp[pos[i]] = k;
    }
}
 
int main(){
    scanf("%s", S);
    constructSA();
    for(int i=0; i<N; i++)
        printf("%d ", sa[i]+1);
}

[출처] 접미사 배열(Suffix Array) (수정: 2018-03-03)|작성자 라이
