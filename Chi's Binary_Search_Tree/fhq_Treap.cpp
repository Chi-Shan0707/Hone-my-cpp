#include<bits/stdc++.h>
using namespace std;
const int N=100010;
const int INF=1000000004;
int n,tot,root;
inline int input()
{
	int num;
	scanf("%d",&num);
	return num;
}
struct Treap
{
	int v,w;//v:权值 w:随机数索引值 
	int sz;//子树大小
//这里不合并权值相同的节点
	int l,r;//左子树右子树下标 
}tr[N];
inline void new_node(int num)
{
	++tot;
	tr[tot].v=num;tr[tot].w=rand()%123456789;
	tr[tot].sz=1;
	tr[tot].l=tr[tot].r=0;	
}
inline void update(int cur){tr[cur].sz=tr[tr[cur].l].sz+tr[tr[cur].r].sz+1;}
//基本节点信息向上传递
void split(int cur,int key,int &x,int &y)//按照节点权值key来分 
/*
cur是当前节点,key是分的标准，x是左边那棵分出来的树下
一个加入节点的位置编号
y则是右边那棵分出来的树的下一个能加的节点编号
*/ 
{
	if(!cur)x=y=0;//访问到叶子节点,返回0
	else
	{
//将cur树分成权值≤key的和权值>key的 
		if(tr[cur].v<=key)
	//cur被划去左边了,它的左子树也都被划去左边了 
		{
			x=cur;
			split(tr[cur].r,key,tr[cur].r,y); 
		}
		else
		{
	//cur被划去右边了,它的右子树也都被划去右边了
			y=cur;
			split(tr[cur].l,key,x,tr[cur].l);
		}
		update(cur);
		//这里更新，是指在cur划分到的子树中对于那个新划分的点进行更新 
	}
}
int merge(int x,int y)
//当前要合并的两棵子树，左边的节点编号是x右边的节点编号是y 
{
	if(!x||!y)return x+y;
/*
if(!x)return y;
if(!x)return x;
这是针对访问到叶子节点0没法再合并下去了的情况 
*/
	if(tr[x].w<tr[y].w)
//将x提到上面去，让x的右子树和y合并去,x的左子树已经ok了 
	{
		tr[x].r=merge(tr[x].r,y);
		update(x);
//这个是返回x，y到底谁成了这块的根，这会儿是x 
		return x;
	}
	else
	//将y提到上面去，让x和y的左子树合并去,y的右子树已经ok了 
	{
		tr[y].l=merge(x,tr[y].l);
		update(y);
//这个是返回x，y到底谁成了这块的根，这会儿是y 
		return y;
	}
}
inline void insert(int &root,int num)
{
	new_node(num);//新增一个节点的操作 
	int x,y;
	split(root,num,x,y);
//分裂成两个树再加上num一起合并 
	root=merge(merge(x,tot),y);
}
inline void del(int &root,int num)
{
	int x,y,cnt;
	//节点v值全是num的树的根为cnt
	split(root,num,x,y);
	split(x,num-1,x,cnt);
/*
注意这里的写法,x是指分裂开始的点;
x,cnt表示将来分出的两棵树的根
split(cur,key,&x,&y)
&x的更改不会影响cur 
*/
	cnt=merge(tr[cnt].l,tr[cnt].r);
/*
这里的合并抛弃了tr[cnt]，直接将其两个儿子并在一起
表明,已经del(num)了 
*/
	root=merge(merge(x,cnt),y);
}
inline int query_rank(int root,int num)
{
	int x,y,res;
	split(root,num-1,x,y);
	res=tr[x].sz+1;
	root=merge(x,y);
	return res;
}
inline int query_num(int cur,int q)
{
	/*
	if(tr[tr[cur].l].sz>=q)return query_num(tr[cur].l,q);
	else if(tr[tr[cur].l].sz+1<q)return query_num(tr[cur].r,q-tr[cur].l-1);
	return tr[cur].v;
	*/
	while(cur)
	{
	if(q<=tr[tr[cur].l].sz)cur=tr[cur].l;
	else if(tr[tr[cur].l].sz+1<q)
	{
		q-=(tr[tr[cur].l].sz+1);
		cur=tr[cur].r;
	}
	else return tr[cur].v;
	}
}
inline int pre(int root,int num)
{
	int x,y,res=-INF;
	split(root,num-1,x,y);
//x树里头的v都小于num，求num的前驱相当于在x中找最大的 
	int cur;cur=x;
	while(cur)
	{
		res=tr[cur].v;
		cur=tr[cur].r;
	}
	root=merge(x,y);
	return res;
}
inline int succ(int root,int num)
{
	int x,y,res=INF;
	split(root,num,x,y);
//y树里头的v都大于num，求num的后继相当于在y中找最小的
	int cur;cur=y;
	while(cur)
	{
		res=tr[cur].v;
		cur=tr[cur].l;
	}
	root=merge(x,y);
	return res;
}
int main()
{
	srand(time(0));
	n=input();
	for(int k=1;k<=n;++k)
	{
		int op,m;op=input();m=input();
        if(op==1)insert(root,m);
        else if(op==2)del(root,m);
        else if(op==3)printf("%d\n",query_rank(root,m));
        else if(op==4)printf("%d\n",query_num(root,m));
		else if(op==5)printf("%d\n",pre(root,m));
        else printf("%d\n",succ(root,m));
    }
	return 0;
}
