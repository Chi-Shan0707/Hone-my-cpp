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
#define nil 0
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
        uncle=BST.tr[parent].child[1^BST.which_one(parent)];
        if(col[uncle]==RED)
        {
            col[parent]=BLACK;
            col[uncle]=BLACK;
            col[grandpa]=RED;
            id=grandpa;
        }
        else if(BST.which_one(parent)&BST.which_one(id))
        {
            BST.rotate(parent);
            col[parent]=BLACK;
            col[grandpa]=RED;
            break;
        }
        else
        {
            BST.rotate(id);
            BST.rotate(id);
            col[id]=BLACK;
            col[grandpa]=RED;
            break;
        }
        
    }
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
                                {0,0},
                                1,1};
    col[id]=RED;
    if(parent==nil){
        BST.root=id;
        col[id]=BLACK;
        return;
    }
    BST.tr[parent].child[BST.tr[parent].val<val]=id;
    //建立双向父子关系
//    cout<<"插入完毕"<<endl;
    BST.update(id);
    fixup(BST,id,col);
}
void print_tree(Binary_Search_Tree BST,int *tr,int *col)
{
    
}
int main()
{
    int n;
    bool *col;
    cin>>n;
    col=new bool[n+4];
    for(int id=0;id<n;++id)col[id]=0;
    Binary_Search_Tree BST(n+4);
    for(int i=0;i<n;++i)
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
 //   for(int id=1;id<=BST.node_tot;++id)cout<<id<<" "<<col[id]<<endl;
    return 0;
}