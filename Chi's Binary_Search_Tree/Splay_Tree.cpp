
// void splay(int &root,int id)
// {
//     if(id==root)return;
//     for(;Pa(id)!=0;)
//     //id会自己递变，通过id的父亲?0来判断是否到达根节点
//     //不能以id!=root 来当作判断语句
//     {
//         int parent=Pa(id);
//         if(parent==root)rotate(id);
//         else{
//             if(which_one(id)==which_one(parent))
//             {
//                 rotate(parent);
//                 rotate(id);
//             }
//             else
//             {
//                 rotate(id);
//                 rotate(id);
//             }
//         }
//     }
//     root=id;
// }
// void insert(int &root,int val)
// {
//     int id=root;
//     int parent=0;
//     for(;id&&val!=tr[id].val;id=tr[parent=id].child[tr[id].val<val]);
// //跨越到下一步的时候记录父亲
// //tr[id].val<val为真：RIGHT
//     if(id)
//     {
//         ++tr[id].cnt;
//         ++tr[id].sz;
//     }
//     else
//     {
        
//         tr[id=++tot]=(Tree_Node){val
//                                 ,parent,
//                                 {0,0},
//                                 1,1};
        
//         if(tot==1)
//         {
//             root=1;
//             return;
//         }
//         tr[parent].child[tr[parent].val<val]=id;
//     }
//     splay(root,id);
// }

// int Rank(int &root,int val)
// {
//     int id=root;
//     for(;tr[id].val!=val;id=tr[id].child[tr[id].val<val]);
//     splay(root,id);
//     return sz(tr[root].child[LEFT])+1;
// }

#include<iostream>
#include "Tree.h"
using namespace std;

extern Binary_Search_Tree BST;

void splay(int &root,int id)
{
    if(id==root)return;
    for(;BST.tr[id].pa!=0;)
    //id会自己递变，通过id的父亲?0来判断是否到达根节点
    //不能以id!=root 来当作判断语句
    {
        int parent=BST.tr[id].pa;
        if(parent==root)BST.rotate(id);
        else{
            if(BST.which_one(id)==BST.which_one(parent))
            {
                BST.rotate(parent);
                BST.rotate(id);
            }
            else
            {
                BST.rotate(id);
                BST.rotate(id);
            }
        }
    }
    root=id;
}
void insert(int &root,int val)
{
    int id=root;
    int parent=0;
    for(;id&&val!=BST.tr[id].val;id=BST.tr[parent=id].child[BST.tr[id].val<val]);
//跨越到下一步的时候记录父亲
//tr[id].val<val为真：RIGHT
    if(id)
    {
        ++BST.tr[id].cnt;
        ++BST.tr[id].sz;
    }
    else
    {
        
        BST.tr[id=++BST.node_tot]=(Tree_Node){val
                                ,parent,
                                {0,0},
                                1,1};
        
        if(BST.node_tot==1)
        {
            root=1;
            return;
        }
        BST.tr[parent].child[BST.tr[parent].val<val]=id;
    }
    splay(root,id);
}

int Rank(int &root,int val)
{
    int id=root;
    for(;BST.tr[id].val!=val;id=BST.tr[id].child[BST.tr[id].val<val]);
    splay(root,id);
    return BST.tr[BST.tr[root].child[LEFT]].sz+1;
}
int main()
{
    int n;
    cin>>n;
    Binary_Search_Tree BST(n);

    return 0;
}