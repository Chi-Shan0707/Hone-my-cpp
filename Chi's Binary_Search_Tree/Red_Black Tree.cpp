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
void Insert(Binary_Search_Tree &BST,int val,bool *col)
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
/*
红黑树的删除操作与普通的 BST 相比要多一些步骤。具体而言：

1. 若待删除的节点 𝑛 有两个子节点，则交换 𝑛和左子树中最大节点 𝑠
    s 的数据，并将 𝑛 设为 𝑠。此时  n 不可能有两个子节点。
2. 若待删除的节点 𝑛有一个子节点 𝑠。由性质 4 可知 𝑠必为红色，再由性质 3 可知 𝑛必为黑色。所以只需将 𝑛
 在父节点 𝑝 中对应的指针替换为 𝑠 的地址，以及将 𝑠 的父节点指针替换为 p 的地址，之后再将 𝑠 染黑即可。
若待删除的节点n 没有子节点。若 n 是根节点或 𝑛
n 是红色节点，则直接删除即可，否则直接删除会违反性质 4，需要维护平衡性。
*/
void transplant(Binary_Search_Tree &BST,int u,int v)//将u子树整体替换为v子树
{
    if(u==BST.root)BST.root=v;
    else BST.tr[BST.tr[u].pa].child[BST.which_one(u)]=v;
    BST.tr[v].pa=BST.tr[u].pa;
//更改父与子关系
}
void Delete_fixup(Binary_Search_Tree &BST,int id,bool *col)
{
/*
x是左儿
子



Case 1:
双黑x兄弟bro是红色的
两边应该等黑高，bro下面必定还有黑色的
给x父亲和bro都改一些颜色
再在x父亲那边左旋一下，所以此时x的父亲还是原本的父亲，但他兄弟爬到他老子头上了，他兄弟bro的儿子变成了x的儿子，是黑色的

Case 2:
x兄弟bro是黑色的，bro的孩子都是黑色的
x是双黑,x兄弟bro是黑色的
两人各扣1个黑色，他们的大爹多一个
如果大爹双黑就继续更新

Case 3:
x兄弟bro是黑色的, bro左儿子红

bro左儿子 bro取反颜色
在bro子树内右旋
变成case4

Case 4:
x兄弟bro是黑色的, bro右儿子红

X是双黑，bro是黑色的，bro右儿子红色的

先在x父亲子树里头左旋一下

这棵子树 老大爷现在是黑色的bro，右儿子是红色的，左儿子是x的老爹，颜色unknown；x的兄弟是原先bro的左耳子

如果原先x的父亲是黑色的，那么左旋后，由于bro右儿子是红色的，为了稳定，右儿子要变成黑色；对于有双黑的情况下，竟然这时候理解为单黑就稳定了！
如果原先x的父亲是红色的，那么左旋后，仍然是稳定的；我们把黑色下放，根节点（bro）变为红色，bro右儿子该是黑色的

就让黑色“下放“，bro的右儿子是红色，所以下方没问题；



*/
    int bro;
    while(id!=BST.root&&col[id]==BLACK)
    {
        int parent=BST.tr[id].pa;
        bro=BST.tr[parent].child[1^BST.which_one(id)];
        if(col[bro]==RED)
        //case 1
        {
            col[bro]=BLACK;
            col[parent]=RED;
            BST.rotate(bro);
            bro=BST.tr[parent].child[1^BST.which_one(id)];
        }
        //到这里，老兄一定是黑色的了
        if(col[BST.tr[bro].child[LEFT]]==BLACK&&col[BST.tr[bro].child[RIGHT]]==BLACK)
        {
//case 2
            col[bro]=RED;
            id=parent;
            //就看了，如果大爹是黑色的，那么大爹就是双黑，循环就会继续
            //反之则会，让循环跳出，让红色+黑色的大爹变黑（稳定的）
        }
        else
        {
            int dir=BST.which_one(id);
            if(col[BST.tr[bro].child[dir]]==RED)
            {
                col[BST.tr[bro].child[dir]]=BLACK;
                col[bro]=RED;
                BST.rotate(BST.tr[bro].child[dir]);
                bro=BST.tr[parent].child[1^BST.which_one(id)];//记得更新bro
            }
//到这里，bro一定是黑色的，且bro的远端儿子是红色的
            col[bro]=col[parent];
            col[parent]=BLACK;
            col[BST.tr[bro].child[1^dir]]=BLACK;
            BST.rotate(bro);
            id=BST.root;//这里跳出循环，就会让根节点保持黑色
        }
    }
    col[id]=BLACK;
}
void Delete_Node(Binary_Search_Tree &BST,int id,bool *col)
{
    Tree_Node cur=BST.tr[id];
    int temp_id;
    int id_original_color=col[id];
    if(cur.child[0]==nil)
    {
        temp_id=cur.child[RIGHT];
        transplant(BST,id,temp_id);
        BST.update(temp_id);
    }
    else if(cur.child[1]==nil)
    {
        temp_id=cur.child[LEFT];
        transplant(BST,id,temp_id);
        BST.update(temp_id);
    }
    else
    {
        temp_id=cur.child[RIGHT];
        while(BST.tr[temp_id].child[LEFT]!=nil)temp_id=BST.tr[temp_id].child[LEFT];
        if(temp_id==cur.child[RIGHT])
        {
            transplant(BST,id,temp_id);
            BST.tr[temp_id].child[LEFT]=cur.child[LEFT];
            BST.tr[cur.child[LEFT]].pa=temp_id;
            BST.update(temp_id);
        }
        else
        {
            transplant(BST,temp_id,BST.tr[temp_id].child[RIGHT]);
//会更改一对父子关系
            BST.update(BST.tr[temp_id].pa);


            BST.tr[temp_id].child[LEFT]=cur.child[LEFT];
            BST.tr[cur.child[LEFT]].pa=temp_id;
//更改另外左 的一对父子关系

            BST.tr[temp_id].child[RIGHT]=cur.child[RIGHT];
            BST.tr[cur.child[RIGHT]].pa=temp_id;

            transplant(BST,id,temp_id);
            BST.update(temp_id);
//最后利用封装函数更新最上面的父子关系
        }
    }
    if(id_original_color==BLACK)
    {
        Delete_fixup(BST,temp_id,col);
    }
}
void Delete_val(Binary_Search_Tree &BST,int val,bool *col)
{
    int id=BST.root;
    while(id!=nil)
    {
        if(val<BST.tr[id].val)id=BST.tr[id].child[LEFT];
        else if(BST.tr[id].val<val)id=BST.tr[id].child[RIGHT];
        else
        {
            if(BST.tr[id].cnt>1)
            {
                --BST.tr[id].cnt;
                BST.update(id);
                return;
            }
            else
            {
                Delete_Node(BST,id,col);
                return;
            }
        }
    }
}
int Rank(Binary_Search_Tree &BST,int val)
{
    int id=BST.root;
    int res=0;
    while(id!=nil)
    {
        if(val<BST.tr[id].val)id=BST.tr[id].child[LEFT];
        else if(BST.tr[id].val<val)
        {
            res+=BST.tr[BST.tr[id].child[LEFT]].sz+BST.tr[id].cnt;
            id=BST.tr[id].child[RIGHT];
        }
        else
        {
            res+=BST.tr[BST.tr[id].child[LEFT]].sz;
            return res+1;
        }
    }
    return res+1;
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
        int mode,val;
        cin>>mode>>val;
        switch(mode)
        {
            case 1:
                Insert(BST,val,col);
                
                break;
            case 2:
                Delete_val(BST,val,col);
                break;
            case 3:
                cout<<Rank(BST,val)<<endl;
                break;
        }
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