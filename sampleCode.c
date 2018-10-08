1，地址对齐
#define bufAlign(ptr, align)    ((ptr + (align - 1)) & ~(align - 1))  

2，统计二进制1的个数

while(x)
{
	count++;
	X=X&(X-1);
}


