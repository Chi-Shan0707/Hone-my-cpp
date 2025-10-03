
#include<iostream>
#include "quick_sort.h"
using namespace std;
int main()
{
    int n;
    cin>>n;
    int a[1002];
    for(int i=1;i<=n;i++)cin>>a[i];
    Sort my_quick_sort;
    my_quick_sort.quick_sort(a,1,n);
    for (int  i = 1; i <=n;++i)cout<<a[i]<<" ";
    return 0;
    
}