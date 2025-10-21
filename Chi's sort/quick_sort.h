
#ifndef QUICK_SORT_H
#define QUICK_SORT_H
using namespace std;
template<typename T>
void swap(T &x,T &y){T z=y;y=x;x=z;}
//template<typename T>只能被用一次，有东东用掉了就得再写一遍

template<typename T>
class Sort
{
//    template<typename T>;
    public:
        void quick_sort(T a[],int l,int r)
        {
            if(l>=r)return;
            int pivot=partition(a,l,r);
            quick_sort(a,l,pivot-1);
            quick_sort(a,pivot+1,r);
            /*
            for(int i=1;i<=n;++i)
            {
                cout<<a[i]<<" ";
            }
            cout<<endl<<"-------------------"<<endl;
            */
        }
    private:
        int partition(T a[],int l,int r)
        {
            int left=l,right=r;
            while(left<right)
            {
                while(right>left&&a[right]>=a[l])--right;
                while(left<right&&a[left]<=a[l])++left;
/*
注意点：
两个while顺序不能换&&至少有一个得有取等
和left不能设置成l+1

当l=r+1的时候，如果left=l+1,大的while就不执行了
当l=r+1的时候，如果++left在前，那么就会直接left=right=r
指针需要再细细品
*/
                swap(a[left],a[right]);
            }
            swap(a[l],a[right]);
            return right;
        }
};

#endif
