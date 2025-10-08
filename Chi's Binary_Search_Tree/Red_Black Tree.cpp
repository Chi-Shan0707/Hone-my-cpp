/*
1. 每个节点红色或黑色
2. 根节点为黑色
3. 叶子节点为null，且为黑色
4. 不存在两个相邻的红色节点
5. 从任意节点往下走到叶子节点（为null）的路径上，有同样数目的黑色节点
*/
#include<iostream>
using namespace std;
// typedef  leftson ls;
// typedef rightson rs;
#define RED 0
#define BLACK 1
#define LEFT 0
#define RIGHT 1
const int N=100005;
struct Tree_Node
{
    int val,col;
    int pa;
    int child[2]//left,right
    int sz;
}tr[N];

void clockwise_rotate(int id)
{
//closewise顺时针
    int parent=tr[id].pa;
    tr[id].pa=tr[parent].pa;
    tr[parent].pa=id;
    tr[parent].child[LEFT]=tr[id].child[RIGHT];
    tr[id].child[RIGHT]=parent;

}
void anticlockwise_rotate(int id)
{
//anticlosewise逆时针
    int parent=tr[id].pa;
    tr[id].pa=tr[parent].pa;
    tr[parent].pa=id;
    tr[parent].child[RIGHT]=tr[id].child[LEFT];
    tr[id].child[LEFT]=parent;
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;++i)
    {
        int num;cin>>num;
        Tree_Node new_node;
        new_node={num,RED,
                    0,
                    0,0,
                    1};
    }
    return 0;
}