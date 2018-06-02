/********************************
01.霍夫曼编码树及其编码的产生算法
   该方法用于将几种特定的状态信息(a,b,c……)用最少的二进制编码予以分别表示。
   该编码方案称为霍夫曼编码。它形成了一个霍夫曼编码树，节点结构体包含代表
   频率的权值和状态值。从根节点出发，凡是向左子树节点方向的路径值为零，向
   右子树节点方向的路径值为1。到达叶子节点即到达终点。此时叶子节点的状态值
   代表我们需要编码的状态，从根结点到它的路径值就为它的霍夫曼编码。
********************************/
#include <stdio.h>
#include <math.h>
#define MAX 10 //最大状态值个数数
#define MAXS (MAX*4)//二进制霍夫曼编码的最大长度
#define MAX_NUM 100 //最大权值数，应该取值为所有权值之和(即概率1)

int n;//实际待编码的字符个数
char C2b[MAX],c2B[MAXS];//待编码字符串存放在前者，编码后的二进制串放在后者
char B2c[MAXS],b2C[MAX];//待译码的霍夫曼编码存放在前者，译码后的字符串放在后者
typedef struct{//霍夫曼树的节点结构体
	char c;//代表编码对象的字符
	float weight;//字符状态出现的频率
	int parent,lchild,rchild;
}HfmNode;

HfmNode HT[2*MAX-1];//节点数组，MAX个待编码状态(叶节点)的霍夫曼树，共有2*MAX-1个节点
char Code[MAX][MAX];//存放MAX个状态的霍夫曼编码表

void HfmTreeCreat(void)//霍夫曼树创建和编码表生成函数
{
	int i,j,k,min,p,q;
	char tmp[MAX];//存放临时霍夫曼编码
	for(i=n;i<2*n-1;i++){//为每一个非叶节点寻找左右子节点(路径最长的叶节点代表频度最小的状态)
		min=MAX_NUM;//初始化最小频度
		for(j=0;j<i;j++)//在所有当前节点中寻找频度最小的那个
			if(HT[j].parent==0&&HT[j].weight<min){
				min=HT[j].weight;//刷新最小频度值
				p=j;//记录下最小频度节点位置
			}
		min=MAX_NUM;//重置最小频度值
		for(j=0;j<i;j++)//寻找第二小的
			if(HT[j].parent==0&&j!=p&&HT[j].weight<min){
				min=HT[j].weight;
				q=j;
			}
		HT[p].parent=i;//将找到的p,q节点分别作为当前i节点的左右子节点
		HT[q].parent=i;
		HT[i].lchild=p;
		HT[i].rchild=q;
		HT[i].weight=HT[p].weight+HT[q].weight;//两个节点的频度和作为i节点的频度
	}//所有中间节点成为父节点后，编码树生成
	for(i=0;i<n;i++){//从叶结点开始逆推到根结点，此路径即为霍夫曼编码
		p=i;
		q=HT[i].parent;//当前叶节点的父节点
		k=n-1;
		tmp[k]='\0';//暂存编码字符数组结束标志放在数组最后，确保字符串可靠结尾
		while(q){
			if(HT[q].lchild==p) tmp[--k]='0';//从后往前倒存编码，左子串为0右子串为1
			else if(HT[q].rchild==p) tmp[--k]='1';
			p=q;//往上再走一层，直到走到根结点(无父节点)结束循环
			q=HT[p].parent;
		}
		for(j=0;k<n;j++,k++)//将编码放到编码表中
			Code[i][j]=tmp[k];
	}
}

void EncodeHfm(void)//霍夫曼编码函数
{
	int i=0,k,j,l=0;
	while(C2b[i]){//为每一个字符进行编码
		k=0;
		for(j=0;j<n;j++){//查表
			if(C2b[i]==HT[j].c){
				while(Code[j][k])//将查到的编码放入编码流中
					c2B[l++]=Code[j][k++];
				break;
			}
		}
		++i;
	}
	c2B[l]='\0';
}


void DecodeHfm(void)//译码函数，从B2c中取得霍夫曼编码，译码字符串输出到b2C中
{
	int i=0,j=0,p,root=2*n-2;
	while(B2c[i]){
		p=root;//每次译码均从根节点出发
		while(HT[p].lchild || HT[p].rchild){//一路走下去，直至叶节点
			if(B2c[i]=='0') p=HT[p].lchild;
			else p=HT[p].rchild; 
			i++;
		}
	b2C[j++]=HT[p].c;
	}
	b2C[j]='\0';//字符串结束标志
	printf("\n");
}

			
int main(void)
{
	int i,j;
	printf("\n\n请输入编码对象的个数:");
	scanf("%d",&n);
	for(i=0;i<n;i++){//叶节点(待编码对象)赋初值
		printf("\n\n请输入代表编码对象的字符(%d):",i+1);
		scanf("%s",&HT[i].c);
		printf("\n\n请输入对应的权值:");
		scanf("%f",&HT[i].weight);
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	for(i=n;i<2*n-1;i++){//中间节点赋初值
		HT[i].c='\0';
		HT[i].weight=0;
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	HfmTreeCreat();//编码表生成
		printf("\n……………………………………………………………………\n");
	for(i=0;i<n;i++){//查表
		printf("\n");
		printf("符号:%c\t",HT[i].c);
		printf("权值:%3.2f\t",HT[i].weight);
		printf("编码:%s",Code[i]);
	}
		printf("\n……………………………………………………………………\n");
	printf("\n请输入代表消息的字符串:");
	scanf("%s",C2b);
	EncodeHfm();
	printf("\n===>编码后的二进制字符串为:%s",c2B);
	printf("\n\n请输入二进制代码串:");
	scanf("%s",B2c);
	DecodeHfm();
	printf("\n===>译码字符串为:%s\n",b2C);
	return 0;
}

