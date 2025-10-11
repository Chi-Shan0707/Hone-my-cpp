#ifndef TREE_H_
#define TREE_H

struct Tree_Node
{
    int val;
    int pa;
    int child[2];//left,right
    int cnt,sz;
};
#define LEFT 0
#define RIGHT 1
#define sz(id) tr[id].sz
#define Pa(id) tr[id].pa
class Binary_Search_Tree
{
    private:
        
        
        
    public:
        Tree_Node *tr;  // 将tr声明为类成员变量
        int root,node_tot;
        void push_up(int id){sz(id)=sz(tr[id].child[LEFT])+sz(tr[id].child[RIGHT])+tr[id].cnt;}
        int which_one(int id){return tr[Pa(id)].child[RIGHT]==id;}
        Binary_Search_Tree(int n)
        {
            tr=new Tree_Node[n];
            root=node_tot=0;
        }
        ~Binary_Search_Tree()
        {
            delete [] tr;
        }
        void rotate(int id)
        {
            int parent=Pa(id);
            int dir=which_one(id);
            
        //每一步操作都要注意，双向关系的维护   

        //先搞定原爷爷(左旋右旋都如此)
            tr[Pa(parent)].child[which_one(parent)]=id;
            Pa(id)=Pa(parent);

        //再搞定自己的儿子(让原儿子去跟原父亲建立bilateral relationship)

            //要利用好dir
            //dir=0:id是左儿子，需要顺时针右旋
            //dir=1:id是右儿子。需要逆时针左旋
            tr[parent].child[dir]=tr[id].child[dir^1];
            Pa(tr[id].child[dir^1])=parent;
            
        //最后搞定自己的父亲（让原父亲和自己建立bilateral relationship)
            Pa(parent)=id;
            tr[id].child[dir^1]=parent;

            push_up(parent);
            push_up(id);
        }
        
    
};

#endif