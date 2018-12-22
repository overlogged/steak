#ifndef _STEAK_H_
#define _STEAK_H_
/**
 *  @brief  a functional library for cpp
 *  @author Nicekingwei(Long Jinwei)
 */ 
#include <iostream>
#include <exception>
#include <functional>
#include <memory>
#include <variant>
#include "runtime.h"

#define With(x) if(1){auto match_var=x.eval();if(0){;
#define Case(name,...) }else if(match_var.match(steak::attach_ghost<steak_constructors::name>(steak::forward_and_zip(__VA_ARGS__)))){;
#define Default }else{;
#define EndWith() }}
#define UnZip(name,...) steak::attach_ghost<steak_constructors::name>(steak::forward_and_zip(__VA_ARGS__))
#define Data(T,name,...) T struct name;T struct name:public steak::data_class_t<__VA_ARGS__>{name(){} template<typename...K>name(K...args):steak::data_class_t<__VA_ARGS__>(args...){}};
#define RegCons(name) namespace steak_constructors{struct name {static constexpr const char* consname=#name;};};
#define RealType(name,...) steak::cal_cons_type<steak_constructors::name>::R<__VA_ARGS__>
#define DerivingShow(T,name) \
T std::ostream& operator << (std::ostream& out,name& x)\
{\
	return x.show(out);\
}

namespace steak
{
	#define Cons0(T,name,ret)\
T inline steak::lazy_type_t<ret> name(){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name>());} ) );}\

	#define Cons1(T,name,ret,t1)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1>(v1.get()));} ) );}\

	#define Cons2(T,name,ret,t1,t2)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2>(v1.get(),v2.get()));} ) );}\

	#define Cons3(T,name,ret,t1,t2,t3)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1.get(),v2.get(),v3.get()));} ) );}\

	#define Cons4(T,name,ret,t1,t2,t3,t4)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.get(),v2.get(),v3.get(),v4.get()));} ) );}\

	#define Cons5(T,name,ret,t1,t2,t3,t4,t5)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get()));} ) );}\

	#define Cons6(T,name,ret,t1,t2,t3,t4,t5,t6)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get()));} ) );}\

	#define Cons7(T,name,ret,t1,t2,t3,t4,t5,t6,t7)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get()));} ) );}\

	#define Cons8(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get()));} ) );}\

	#define Cons9(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get()));} ) );}\

	#define Cons10(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get()));} ) );}\

	#define Cons11(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get(),v11.get()));} ) );}\

	#define Cons12(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get(),v11.get(),v12.get()));} ) );}\

	#define Cons13(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get(),v11.get(),v12.get(),v13.get()));} ) );}\

	#define Cons14(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get(),v11.get(),v12.get(),v13.get(),v14.get()));} ) );}\

	#define Cons15(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get(),v11.get(),v12.get(),v13.get(),v14.get(),v15.get()));} ) );}\

	#define Cons16(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get(),v11.get(),v12.get(),v13.get(),v14.get(),v15.get(),v16.get()));} ) );}\

	#define Cons17(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get(),v11.get(),v12.get(),v13.get(),v14.get(),v15.get(),v16.get(),v17.get()));} ) );}\

	#define Cons18(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17,steak::lazy_type_t<t18> v18){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get(),v11.get(),v12.get(),v13.get(),v14.get(),v15.get(),v16.get(),v17.get(),v18.get()));} ) );}\

	#define Cons19(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17,steak::lazy_type_t<t18> v18,steak::lazy_type_t<t19> v19){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get(),v11.get(),v12.get(),v13.get(),v14.get(),v15.get(),v16.get(),v17.get(),v18.get(),v19.get()));} ) );}\

	#define Cons20(T,name,ret,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20)\
T inline steak::lazy_type_t<ret> name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17,steak::lazy_type_t<t18> v18,steak::lazy_type_t<t19> v19,steak::lazy_type_t<t20> v20){return steak::lazy_call(std::function<ret()> ( [=](){return ret(steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20>(v1.get(),v2.get(),v3.get(),v4.get(),v5.get(),v6.get(),v7.get(),v8.get(),v9.get(),v10.get(),v11.get(),v12.get(),v13.get(),v14.get(),v15.get(),v16.get(),v17.get(),v18.get(),v19.get(),v20.get()));} ) );}\

		#define V
		#define Va template<typename a>
		#define Vab template<typename a,typename b>
		#define Vabc template<typename a,typename b,typename c>
		#define Vabcd template<typename a,typename b,typename c,typename d>
		#define Vabcde template<typename a,typename b,typename c,typename d,typename e>
		#define Vabcdef template<typename a,typename b,typename c,typename d,typename e,typename f>
		#define Vabcdefg template<typename a,typename b,typename c,typename d,typename e,typename f,typename g>
		#define Vabcdefgh template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h>
		#define Vabcdefghi template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i>
		#define Vabcdefghij template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j>
		#define Vabcdefghijk template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j,typename k>
		#define Vabcdefghijkl template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j,typename k,typename l>
		#define Vabcdefghijklm template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j,typename k,typename l,typename m>
		#define Vabcdefghijklmn template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j,typename k,typename l,typename m,typename n>
		#define Vabcdefghijklmno template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j,typename k,typename l,typename m,typename n,typename o>
		#define Vabcdefghijklmnop template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j,typename k,typename l,typename m,typename n,typename o,typename p>
		#define Vabcdefghijklmnopq template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j,typename k,typename l,typename m,typename n,typename o,typename p,typename q>
		#define Vabcdefghijklmnopqr template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j,typename k,typename l,typename m,typename n,typename o,typename p,typename q,typename r>
		#define Vabcdefghijklmnopqrs template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j,typename k,typename l,typename m,typename n,typename o,typename p,typename q,typename r,typename s>
		#define Vabcdefghijklmnopqrst template<typename a,typename b,typename c,typename d,typename e,typename f,typename g,typename h,typename i,typename j,typename k,typename l,typename m,typename n,typename o,typename p,typename q,typename r,typename s,typename t>
};
#endif