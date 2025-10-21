/*
1. 每个节点红色或黑色
2. 根节点为黑色
3. 叶子节点为nihil，且为黑色
4. 不存在两个相邻的红色节点
5. 从任意节点往下走到叶子节点（为nihil）的路径上，有同样数目的黑色节点
*/
#include<iostream>
#include "Tree.h"
using namespace std;
#define nil 1
#define RED 1
#define BLACK 0
void fixup(Binary_Search_Tree &BST,int id,bool *col)
{
    int uncle,parent,grandpa;
    while(id!=BST.root&&col[BST.tr[id].pa]==RED)
    {
        parent=BST.tr[id].pa;
        grandpa=BST.tr[parent].pa;
        if(grandpa==nil)
        {
            col[parent]=BLACK;
            return;
        }
//如果父亲是整棵树根节点，其就是黑色了
        uncle=BST.tr[grandpa].child[1^BST.which_one(parent)];
        if(col[uncle]==RED)
        {
            col[parent]=BLACK;
            col[uncle]=BLACK;
            col[grandpa]=RED;
            id=grandpa;//继续向上更新
        }
        else if(BST.which_one(parent)^BST.which_one(id))
        {
//这种情况是三点不共线
            if(grandpa==BST.root)BST.root=id;
//记得更新根节点
            BST.rotate(id);
            BST.rotate(id);

/*
id-pa-grandpa不共线，故id连转两次(id往上转，转到原先grandpa的位置)
*/
            col[id]=BLACK;
            col[grandpa]=RED;
            break;
        }
        else
        {
/*
id-pa-grandpa三点共线，故直接转pa比较合适
*/            
            if(grandpa==BST.root)BST.root=parent;
//记得更新根节点
            BST.rotate(parent);
            col[parent]=BLACK;//相当于颜色取反
            col[grandpa]=RED;
            break;
        }
/*
1. 重点一：理解旋转的原因和逻辑：也要和splay一样，同侧情况转1次，已测情况转2次
2. 重点二：splay中最后统一更改root，这里需要我们手动判断root是否需要更新
*/
    }
    //勿忘
    col[BST.root]=BLACK;
}
void insert(Binary_Search_Tree &BST,int val,bool *col)
{
    int id=BST.root;
    int parent=nil;
    while(id!=nil)
    {
        parent=id;
        if(val<BST.tr[id].val)id=BST.tr[id].child[LEFT];
        else if(BST.tr[id].val<val)id=BST.tr[id].child[RIGHT];
        else
        {
            ++BST.tr[id].cnt;
            BST.update(id);
            return;
        }
    }
    BST.tr[id=++BST.node_tot]=(Tree_Node){val
                                ,parent,
                                {1,1},
                                1,1};
    col[id]=RED;
    if(parent==nil){
        BST.root=id;
        col[id]=BLACK;
        return;
    }
    BST.tr[parent].child[BST.tr[parent].val<val]=id;
    BST.update(id);
    fixup(BST,id,col);
}

int main()
{
    int n;
    bool *col;
    cin>>n;
    col=new bool[n+5];
    for(int id=0;id<n;++id)col[id]=0;
    Binary_Search_Tree BST(n+4);
    BST.tr[BST.root=BST.node_tot=1]=(Tree_Node)
    {
                                0
                                ,1,
                                {1,1},
                                0,0
    };
    col[1]=BLACK;
    for(int i=0;i<n;++i)
    {
        int val;
        cin>>val;
        insert(BST,val,col);
//        cout<<"当前插入完毕"<<i<<endl;
    }
/*
    cout<<"****"<<endl<<BST.root<<endl;
    for(int id=1;id<=BST.node_tot;++id)
    {
        cout<<"id:"<<id<<" val:"<<BST.tr[id].val<<" pa:"<<BST.tr[id].pa<<" child:"<<BST.tr[id].child[LEFT]<<" "<<BST.tr[id].child[RIGHT]<<" cnt:"<<BST.tr[id].cnt<<" sz:"<<BST.tr[id].sz<<"col"<<col[id]<<endl;
    }
 //   for(int id=1;id<=BST.node_tot;++id)cout<<id<<" "<<col[id]<<endl;
 for(int i=n-1;i<=n-1;++i)
    {
        int val;
        cin>>val;
        insert(BST,val,col);
//        cout<<"当前插入完毕"<<i<<endl;
    }
    for(int id=1;id<=BST.node_tot;++id)
    {
        cout<<"id:"<<id<<" val:"<<BST.tr[id].val<<" pa:"<<BST.tr[id].pa<<" child:"<<BST.tr[id].child[LEFT]<<" "<<BST.tr[id].child[RIGHT]<<" cnt:"<<BST.tr[id].cnt<<" sz:"<<BST.tr[id].sz<<"col"<<col[id]<<endl;
    }
*/
    return 0;
}