#include <stdio.h>
#include <stdlib.h>


// 找出所有質數
int main(void) {
    int i = 0, j = 0;   // 設置雙層迴圈
    int count = 0;      // 設置計數器
    int result = 0;     // 結果
    int max_num = 100;        // 最大整數
    
    printf("%d 的質數有：\n", max_num);

    for (i = 1; i <= max_num; i++) {
        count = 0;      // 計數器歸0

     /* 當因數只有兩個，可以確認該整數為質數 */
        for (j = 1; j <= max_num; j++) {
            if (i % j == 0)
                count += 1;
        }
        
        if (count == 2) {
            result = i;
            printf("%d\t", result);
        }
    }

    printf("\n");
}
