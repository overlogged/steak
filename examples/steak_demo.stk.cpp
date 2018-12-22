#include <iostream>
#include "../include/runtime.h"

using namespace std;

int f()
{
    char c;
    switch(c)
    {
    case 0:
        cout<<1;
    default:
        cout<<3;
    }
    return 0;
}

dataclass Peano
{
    Peano Z();             /* zero */
    Peano S(Peano);        /* succ */
};


template<typename a>
dataclass Maybe
{
    Maybe<a> Nothing();
    Maybe<a> Just(a);
};

template<typename a>
dataclass List
{
    List<a> Nil();
    List<a> Cons(a,List<a>);
};

int maybe_sum(List<Maybe<int>> l)
{
    int x=0,y=0;
    bool flag=true;
    while(flag)
    {
        match(l)
        {
            case Cons(Just(y),l):
                x+=y;
                break;
            case Cons(Nothing(),l):
                break;
            case Nil():
                flag=false;
                break;
        }
    }
    return x;
}

int main()
{
    auto l = Cons(Just<int>(1),Nil<Maybe<int>>());
    l = Cons(Nothing<int>(),l);
    l = Cons(Just<int>(3),l);
    cout<<maybe_sum(l)<<endl;
    return 0;
}