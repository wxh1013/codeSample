/*
注意：属于转载，非原创

一、问题描述问题描述：假设要在足够多的会场里安排一批活动，并希望使用尽可能少的会场。

★算法设计：
对于给定的k个待安排的活动，计算使用最少会场的时间表。

★数据输入：第一行有1个正整数k，表示有k个待安排的活动。接下来的k行中，每行有两个正
整数，分别表示k个待安排的活动开始时间和活动结束时间。时间以0点开始的分钟计。

★结果输出：将计算结果输出到文件output.txt。文件第1行中的数是计算出的最大值。

输入文件示例：input.txt

5        //表示有5个活动
1 23
12 28
25 35
27 80
36 50

输出文件示例：output.txt

3
*/

/*
二、问题分析

（1）.输入数据的储存和表示：
首先,需要定义一个结构体来表示活动，其中包括活动的开始时间和结束时间。
其次,需要定义一个整形变量来表示会场的空闲时间，或者说是该会场最后一个活动的结束时间。

（2）.解题思路这个问题是书本上4.1活动安排问题的变形。

1.书本例题4.1的思路。

4.1活动安排问题说的是如何在一个会场中安排下足够多的活动。它通过先将所有的活动按结束时
间从小到大进行排序，再将依次选择那些没有时间冲突的的活动。一开始先选择活动1，如何依次检
查活动i是否与当前所有活动相容（只要和最后一个相容即可）。若相容则将活动i加入到已选择的活
动中，否则不选择活动i，而继续检查下一活动与当前活动的相容性。通过比较待检查活动的开始时
间与当前所有活动的结束时间来判断兼容性。如果待检查的活动开始时间大于所有当期活动的结束
时间，则是相容的。直观上，这种方法选择相容活动为未安排活动留下尽可能多的时间。贪心选择的
意义是使剩余可安排时间段极大化。

数学证明该种贪心算法总是能取得最优解：设集合A为最优解集合，其中第一个集合为k。如果k=1，
则说明该集合是贪心选择得出的最优解。如果k>1，令集合B=(A-{k})U{1}。因为活动1的结束
时间比活动k少，并且集合A是相容的，所以集合B也是相容。两个集合的活动个数也是一样多的。
因此集合A也是该问题的最优解之一。

2.本题的思路本题要实现用最少的会场来安排完所有的活动。也就是每个会场的利用率要达到最大。

首先，先申请一个会场，用roomavail来记录该会场的空闲时间段，也就是最后一个活动的结束时间。
先遍历所有的活动，通过贪心算法来记录可以安排哪些活动，将已安排好的活动记为ok=1，未安排的为ok=0。
遍历结束后重新申请一个新会场，即将roomavail重新初始化为0，并使roomnum+1表明当前使用的会场数增加1。
当所有的活动都被安排好以后退出循环。

*/


#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
 
struct Job{
	int begin,end;
	bool ok;
};
 
int manage(int n,Job *b){
	int count=n,roomavail=0,roomnum=0;//count表示还剩余几个活动未安排
	while(count>0){//当count=0就退出while循环
		for(int i=1;i<=n;i++){
			if((b[i].begin>roomavail)&&(b[i].ok==0)){//如果当前活动未安排并且和会场中已   //有活动不冲突
				roomavail=b[i].end;//将当前活动加入该会场，并且更新会场的空闲时间
				b[i].ok=1;//标记该活动已被安排
				count--;//未安排的活动数减1
			}
		}
		roomavail=0;//把roomavail初始化，相当于重新再找一个房间 
		roomnum++;//遍历一次，使用的会场数加1
	}
	return roomnum;//返回使用的会场数
}
 
int main(){
	ifstream cinfile;
	cinfile.open("input.txt",ios::in);
	int n,roomnum;
	cinfile>>n;
	Job b[n+1];
	b[0].begin=0;b[0].end=0;b[0].ok=0;
	for(int i=1;i<=n;i++){
		cinfile>>b[i].begin>>b[i].end;
		b[i].ok=0;
	}
	cinfile.close();
	
    for(int i=1;i<=n;i++){//排序
		for(int j=i+1;j<=n;j++){
			if(b[i].end>b[j].end){
				Job Register=b[i];
				b[i]=b[j];
				b[j]=Register;
			}
		}
	}
	roomnum=manage(n,b);
	
	ofstream outfile;
	outfile.open("output.txt",ios::out);
	outfile<<roomnum<<endl;
	outfile.close();
	return 0;
}
/*
5
1 23
12 28
25 35
27 80
36 50
*/
