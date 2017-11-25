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
    Cons2(Va,Cons,a,List<a>,List<a>)
DerivingShow(Va,List<a>)

RegCons(Nothing) RegCons(Just)
Data(Va,Maybe,RealType(Nothing),RealType(Just,a))
    Cons0(Va,Nothing,Maybe<a>)
    Cons1(Va,Just,a,Maybe<a>)
DerivingShow(Va,Maybe<a>)

RegCons(Z) RegCons(S)
Data(V,Peano,RealType(Z),RealType(S,Peano))
    Cons0(V,Z,Peano)
    Cons1(V,S,Peano,Peano)
DerivingShow(V,Peano)


Va std::ostream& operator << (std::ostream& out,steak::lazy_type_t<List<a>> l)
{
    out<<'[';
    bool first=true;
    while(1)
    {
        a x;
        With(l)
            Case(Cons,x,l)
                if(first) first=false;
                else out<<',';
                out<<x;
            Case(Nil)
                break;
        EndWith()
    }
    return out<<']';
}

Vab steak::lazy_type_t<List<b>> map(std::function<b(a)> f,steak::lazy_type_t<List<a>> l)
{
    steak::lazy_type_t<a> x;
    steak::lazy_type_t<List<a>> xs;
    With(l)
        Case(Nil)
            return Nil<b>();
        Case(Cons,x,xs)
            return Cons(Apply1(f,x),map(f,xs));
    EndWith()
}

int maybe_sum(steak::lazy_type_t<List<Maybe<int>>> l)
{
    int x=0,y=0;
    while(1)
    {
        With(l)
            Case(Cons,UnZip(Just,y),l)
                x+=y;
            Case(Nil)
                break;
            Case(Cons,UnZip(Nothing),l)
                ;            
        EndWith()
    }
    return x;
}

int main()
{
    auto l1=Nil_<Maybe<int>>();
    l1=Cons_(Just(4),l1);
    l1=Cons_(Nothing<int>(),l1);
    l1=Cons_(Just(6),l1);
    cout<<l1<<endl;
    cout<<"maybe sum : "<<maybe_sum(l1)<<endl;

    auto l2=Nil_<int>();
    l2=Cons_(1,l2);
    auto h=Apply2((map<int,char>),std::function([](int x)->char{return 'a'+x;}),l2);
    cout<<h<<endl;

    auto x=Cons(1,Nil<int>());
    auto y=Cons(steak::lazy_type_t(1),Nil<int>());

    return 0;
}