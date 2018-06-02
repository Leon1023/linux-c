创建两个共享内存的顺序存储栈！top1，top2分别指向两个栈顶，数组头尾两端分别是两个栈的栈底。


ADT 栈(double stack)
Data
    同线性表。元素具有相同的类型,相邻元素具有前驱和后继关系。
Operation:
InitStack(*s):初始化操作,建立一个空栈。
DestroyStack(*s):若栈存在,则销毁它。
ClearStack(*S):将栈清空。
StackEmpty(S):若栈为空,返回TRUE,否则返回FALSE.
GetTop(S,stacknum,*e):若栈存在且非空,用e返回S的栈顶元素。
Push(*S,stacknum,e):若栈S存在,插入新元素e到栈S中并成为栈顶元素。
Pop(*S,stacknum,*e):弹出栈S中栈顶元素,并用e返回其值。
StackLength(*S):返回栈S的元素个数。

EndADT
