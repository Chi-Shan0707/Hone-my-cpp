#include "next_permutation.h"
#include<iostream>
using namespace std;
int b[1002];
int main() {
    // 测试整数数组
    int m;
    cin>>m;
    
    for(int i=1;i<=m;++i)cin>>b[i];
    Array array_under_operation(m,b);
    do
    {
        for(int i=1;i<=m;++i)cout<<array_under_operation.p[i]<<" ";
        cout<<endl<<"-------------------------"<<endl;
    } while (array_under_operation.next_permutation());
    
    return 0;
}