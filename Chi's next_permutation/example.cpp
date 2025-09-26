#include "next_permutation.h"
#include<iostream>
using namespace std;
int m,b[100];
int main() {
    // 测试整数数组
    cin>>m;
    for(int i=1;i<=m;++i)cin>>b[i];
    do
    {
        for(int i=1;i<=m;++i)cout<<b[i]<<" ";
        cout<<endl<<"-------------------------"<<endl;
    } while (next_permutation(m,b));
    
    return 0;
}