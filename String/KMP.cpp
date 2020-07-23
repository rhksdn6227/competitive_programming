#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int MAX = 1000000;
 
int main(){
    char W[MAX+1], S[MAX+1];
    int M, N;
    gets(S);
    gets(W);
    N = strlen(S);
    M = strlen(W);
 
    int fail[MAX] = {...};
 
    // S, W의 일치하는 지점을 result에 모음
    vector<int> result;
    for(int i=0, j=0; i<N; i++){
        // 현재 글자가 불일치하면 fail 값을 계속 따라감
        while(j > 0 && S[i] != W[j]) j = fail[j-1];
        // 현재 글자가 일치
        if(S[i] == W[j]){
            // W를 S[i:i+M-1]에서 찾음
            if(j == M-1){
                // i=0부터 시작한다면 i-M+1. 문제 조건에 따라 1을 더함
                result.push_back(i-M+2);
                // 찾지 못한 것처럼 j를 이동시키면 됨
                j = fail[j];
            }
            else j++;
        }
    }
 
    // 결과 출력
    printf("%d\n", result.size());
    for(int i: result)
        printf("%d ", i);
}
[출처] KMP 알고리즘(Knuth–Morris–Pratt Algorithm) (수정: 2019-09-01)|작성자 라이

