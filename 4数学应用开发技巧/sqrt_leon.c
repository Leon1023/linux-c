/*这里给出实现32位无符号整数开方得到16位无符号整数的C语言代码。*/

/****************************************/
/*Function: 开根号处理                  */
/*入口参数：被开方数，长整型            */
/*出口参数：开方结果，整型              */
/****************************************/
#include <stdio.h>
unsigned int sqrt_leon(unsigned long M)
{
    unsigned int N, i;      // 结果、循环计数
    unsigned long tmp, ttp;       
    if (M == 0)               // 被开方数，开方结果也为0
        return 0;

    N = 0;
    tmp = (M >> 30);          // 获取最高位：B[m-1]
    M <<= 2;
    if (tmp > 1){              // 最高位为1
        N++;                 // 结果当前位为1，否则为默认的0
        tmp -= N;
    }

    for (i=15; i>0; i--){      // 求剩余的15位
        N <<= 1;              // 左移一位
        tmp <<= 2;
        tmp += (M >> 30);     // 假设

        ttp = N;
        ttp = (ttp<<1)+1;

        M <<= 2;
        if (tmp >= ttp){       // 假设成立
            tmp -= ttp;
            N ++;
        }
    }
    return N;
}


int main(void){
    printf("%u\n",sqrt_leon(0UL));
    printf("%u\n",sqrt_leon(100UL));
    printf("%u\n",sqrt_leon(10000));
    return 0;
}
