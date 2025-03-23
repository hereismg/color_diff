#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


typedef struct {
    char* s1;
    char* s2;
    int n1;
    int n2;

    int **dp;
    int p_counter;
}DP_Table;

typedef struct {
    DP_Table *table;
    int order;
} Arg;

DP_Table create_DP_Table(){
    DP_Table table;
    scanf("%d %d\n", &table.n1, &table.n2);

    table.s1 = malloc((table.n1 + 1) * sizeof(char));
    table.s2 = malloc((table.n2 + 1) * sizeof(char));
    scanf("%s", table.s1);
    scanf("%s", table.s2);

    // 确保 n1 > n2
    if (table.n1 < table.n2) {
        char *temp_s = table.s1;
        table.s1 = table.s2;
        table.s2 = temp_s;

        int temp_n = table.n1;
        table.n1 = table.n2;
        table.n2 = temp_n;

    }

    table.dp = malloc((table.n1 + 1) * sizeof(int*));
    for (int i=0; i<=table.n1; i++) table.dp[i] = malloc((table.n2 + 1) * sizeof(int));

    for (int i=0; i<=table.n1; i++) table.dp[i][0] = 0;
    for (int j=0; j<=table.n2; j++) table.dp[0][j] = 0;
    for (int i=1; i<=table.n1; i++){
        for (int j=1; j<=table.n2; j++){
            table.dp[i][j] = -1;
        }
    }

    return table;
}

int thread_counter = 1;

int max(int a, int b){
    return a > b ? a : b;
}

void* core_fun(void* arg){
    int order = ((Arg*)arg)->order;
    DP_Table *table = ((Arg*)arg)->table;

    int **dp = table->dp;
    char *s1 = table->s1, *s2 = table->s2;
    int n1 = table->n1, n2 = table->n2;

    for (int i=order; i <= n1; i+=table->p_counter){
        for (int j=1; j <= n2; j++){
            while(dp[i-1][j] == -1); // 如果上一层位置的数据没有计算完成，则循环。

            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }
}

// int solution(char *s1, int n1, char *s2, int n2){
//     int **dp = malloc((n1 + 1) * sizeof(int*));
//     for (int i=0; i<=n1; i++) dp[i] = malloc((n2 + 1) * sizeof(int));

//     for (int i=0; i<=n1; i++) dp[i][0] = 0;
//     for (int j=0; j<=n2; j++) dp[0][j] = 0;

//     pthread_t *p_arr = malloc(sizeof(pthread_t) * thread_counter);
//     if (p_arr == NULL) {
//         printf("malloc error!");
//         exit(-1);
//     }

//     pthread_create()

//     for (int i=1; i<=n1; i++){
//         for (int j=1; j<=n2; j++){
//             if (s1[i-1] == s2[j-1]) {
//                 dp[i][j] = dp[i-1][j-1] + 1;
//             } else {
//                 dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
//             }
//         }
//     }

//     int res = dp[n1][n2];
//     free(dp);

//     return res;
// }

int main(){
    DP_Table table = create_DP_Table();
    table.p_counter = 2;

    pthread_t *p_arr = table 

    for (int i=0; i<table.p_counter; i++){
        pthread_create()
    }

    return 0;
}
