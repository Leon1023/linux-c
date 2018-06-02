/*
 *所谓魔方矩阵就是nxn的方阵，n为大于1的奇数。
 *将自然数1至n²分别填入矩阵的各个元素使其纵向
 *横向元素相加和相等。起始位置为第0行中间，取值
 *为1，下一个位置一般在上一行前一个位置，若此
 *位置已经赋过值了，那下一个位置就是正下方。
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 15	 /* maximum size of square */
int main(void)
{ 			/* construct a magic square, iterativety */
int square[MAX_SIZE][MAX_SIZE];
int i, j, row, col;	 /* indexes */
int count; 		/* counter */
int size; 		/* square size */
printf("Enter the size of the square: ");
scanf("%d",&size);

/* check for input errors */
if(size < 1 || size > MAX_SIZE) {
	fprintf(stderr,"Error! size out of range"); 
	exit(EXIT_FAILURE);
}

if(!(size%2)) {
	fprintf(stderr,"Error! Size is even\n");
	exit(EXIT_FAILURE);
}
//initial the square
for(i=0; i<size; i++)
   for (j=0; j<size; j++)
	 square[i][j] = 0 ;

i = 0; j = (size-1)/2; 		// (0,(size-1)/2) are first position of number
square[i][j] = 1;	 	// first number is 1
				//(row,col) are next position of num++
for (count=2; count<=size*size; count++) {	//rest numbers which be filled
   row = (i-1<0) ? (size-1) : (i-1); // next position(up) of row
   col = (j-1<0) ? (size-1) : (j-1); // next position(left) of col
   if (square[row][col]) ++i;		//if filled,then go to down
   else { i = row; j = col; }		//square r,s unoccupied
   square[i][j] = count;
}

/* output the magic square */
printf("Magic square of size %d :\n\n",size);
for (i=0; i<size; i++) {
   for (j=0; j<size; j++)
	 printf ("%5d", square[i][j]);
	 printf("\n");
}
printf("\n\n");
return 0;
}
