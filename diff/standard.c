#include<stdio.h>
#include<stdlib.h>

int max(int a, int b){
    return a > b ? a : b;
}

int solution(char *s1, int n1, char *s2, int n2){
    int *dp = malloc((n2 + 1) * sizeof(int));
    dp[0] = 0;

    for (int i=1; i<=n1; i++){
        int dia = dp[0];
        for (int j=1; j<=n2; j++){
            if (s1[i-1] == s2[j-1]){
                int temp = dp[j];
                dp[j] = dia + 1;
                dia = temp;
            } else {
                dia = dp[j];
                dp[j] = max(dp[j-1], dp[j]);
            }
        }
        printf("进度：%lf\n", (double)i/n1);
    }

    int res = dp[n2];
    free(dp);

    return res;
}

int main(){
    int n1, n2;
    scanf("%d %d\n", &n1, &n2);

    char *s1 = malloc((n1 + 1) * sizeof(char)), *s2 = malloc((n2 + 1) * sizeof(char));
    scanf("%s", s1);
    scanf("%s", s2);

    int res = solution(s1, n1, s2, n2);

    printf("%d\n", res);

    free(s1);
    free(s2);

    return 0;
}
