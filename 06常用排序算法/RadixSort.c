/* 基数排序(Radix Sort)

基数排序的发明可以追溯到1887年赫尔曼·何乐礼在打孔卡片制表机上的贡献。
它是这样实现的：将所有待比较正整数统一为同样的数位长度，数位较短的数前面补零。
然后，从最低位开始进行基数为10的计数排序，一直到最高位计数排序完后，数列就变
成一个有序序列（利用了计数排序的稳定性）。

基数排序的时间复杂度是O(n * dn)，其中n是待排序元素个数，dn是数字位数。
这个时间复杂度不一定优于O(n log n)，dn的大小取决于数字位的选择（比如比特位数），
和待排序数据所属数据类型的全集的大小；dn决定了进行多少轮处理，而n是每轮处理的
操作数目。

如果考虑和比较排序进行对照，基数排序的形式复杂度虽然不一定更小，但由于不进行比较
，因此其基本操作的代价较小，而且如果适当的选择基数，dn一般不大于log n，所以基数排
序一般要快过基于比较的排序，比如快速排序。由于整数也可以表达字符串（比如名字或日
期）和特定格式的浮点数，所以基数排序并不是只能用于整数排序。

基数排序的实现代码如下：
*/
#include<iostream>
using namespace std;
 
// 分类 ------------- 内部非比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n * dn)
// 最优时间复杂度 ---- O(n * dn)
// 平均时间复杂度 ---- O(n * dn)
// 所需辅助空间 ------ O(n * dn)
// 稳定性 ----------- 稳定
 
const int dn = 3;                // 待排序的元素为三位数及以下
const int k = 10;                // 基数为10，每一位的数字都是[0,9]内的整数
int C[k];
 
int GetDigit(int x, int d)          // 获得元素x的第d位数字
{
    int radix[] = { 1, 1, 10, 100 };// 最大为三位数，所以这里只要到百位就满足了
    return (x / radix[d]) % 10;
}
 
void CountingSort(int A[], int n, int d)// 依据元素的第d位数字，对A数组进行计数排序
{
    for (int i = 0; i < k; i++)
    {
        C[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        C[GetDigit(A[i], d)]++;
    }
    for (int i = 1; i < k; i++)
    {
        C[i] = C[i] + C[i - 1];
    }
    int *B = (int*)malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--)
    {
        int dight = GetDigit(A[i], d);  // 元素A[i]当前位数字为dight  
        B[--C[dight]] = A[i];           // 根据当前位数字，把每个元素A[i]放到它在输出数组B中的正确位置上
        // 当再遇到当前位数字同为dight的元素时，会将其放在当前元素的前一个位置上保证计数排序的稳定性
    }
    for (int i = 0; i < n; i++)
    {
        A[i] = B[i];
    }
    free(B);
}
 
void LsdRadixSort(int A[], int n)     // 最低位优先基数排序
{
    for (int d = 1; d <= dn; d++)     // 从低位到高位
        CountingSort(A, n, d);        // 依据第d位数字对A进行计数排序
}
 
int main()
{
    int A[] = { 20, 90, 64, 289, 998, 365, 852, 123, 789, 456 };// 针对基数排序设计的输入
    int n = sizeof(A) / sizeof(int);
    LsdRadixSort(A, n);
    printf("基数排序结果：");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}

