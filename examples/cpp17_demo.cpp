/**
 *  @brief  a functional library for cpp
 *  @author Nicekingwei(Long Jinwei)
 */ 
#include <iostream>
#include "../include/steak.h"

using namespace std;

RegCons(Nil) RegCons(Cons)
Data(Va,List,RealType(Nil),RealType(Cons,a,List<a>))
    Cons0(Va,Nil,List<a>)
    Cons2(Va,Cons,List<a>,a,List<a>)
DerivingShow(Va,List<a>)

RegCons(Nothing) RegCons(Just)
Data(Va,Maybe,RealType(Nothing),RealType(Just,a))
    Cons0(Va,Nothing,Maybe<a>)
    Cons1(Va,Just,Maybe<a>,a)
DerivingShow(Va,Maybe<a>)

RegCons(Z) RegCons(S)
Data(V,Peano,RealType(Z),RealType(S,Peano))
    Cons0(V,Z,Peano)
    Cons1(V,S,Peano,Peano)
DerivingShow(V,Peano)


// Va std::ostream& operator << (std::ostream& out,List<a> l)
// {
//     out<<'[';
//     bool first=true;
//     while(true)
//     {
//         a x;
//         With(l)
//             Case(Cons,x,l)
//                 if(first) first=false;
//                 else out<<',';
//                 out<<x;
//             Case(Nil)
//                 break;
//         EndWith()
//     }
//     return out<<']';
// }

// int maybe_sum(List<Maybe<int>> l)
// {
//     int x=0,y=0;
//     while(1)
//     {
//         With(l)
//             Case(Cons,UnZip(Just,y),l)
//                 x+=y;
//             Case(Nil)
//                 break;
//             Case(Cons,UnZip(Nothing),l)
//                 ;            
//         EndWith()
//     }
//     return x;
// }

int main()
{
    auto l1=Nil<Maybe<int>>();
    l1=Cons(Just<int>(4),l1);
    l1=Cons(Nothing<int>(),l1);
    l1=Cons(Just<int>(6),l1);
    // cout<<l1<<endl;
    // cout<<"maybe sum : "<<maybe_sum(l1)<<endl;

    auto x=Cons<int>(1,Nil<int>());
    auto y=Cons<int>(steak::lazy_type_t(1),Nil<int>());

    return 0;
}