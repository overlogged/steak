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
	#define Apply1(f,v1) steak::lazy_apply1(std::function(f),v1)
	/**
	*  @brief nested lazy apply1
	*/
	template<typename T0,typename T1>
	steak::lazy_type_t<T0> lazy_apply1(std::function<T0(T1)> f,steak::lazy_type_t<T1> t1)
	{
		return std::function([=](){return f(t1.eval());});
	}

	/**
	*  @brief weak lazy apply1
	*/
	template<typename T0,typename T1>
	steak::lazy_type_t<T0> lazy_apply1(std::function<T0(T1)> f,const T1& v1)
	{
		return std::function([=](){return f(v1);});
	}

	#define Apply2(f,v1,v2) steak::lazy_apply2(std::function(f),v1,v2)
	/**
	*  @brief nested lazy apply2
	*/
	template<typename T0,typename T1,typename T2>
	steak::lazy_type_t<T0> lazy_apply2(std::function<T0(T1,T2)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2)
	{
		return std::function([=](){return f(t1.eval(),t2.eval());});
	}

	/**
	*  @brief weak lazy apply2
	*/
	template<typename T0,typename T1,typename T2>
	steak::lazy_type_t<T0> lazy_apply2(std::function<T0(T1,T2)> f,const T1& v1,const T2& v2)
	{
		return std::function([=](){return f(v1,v2);});
	}

	#define Apply3(f,v1,v2,v3) steak::lazy_apply3(std::function(f),v1,v2,v3)
	/**
	*  @brief nested lazy apply3
	*/
	template<typename T0,typename T1,typename T2,typename T3>
	steak::lazy_type_t<T0> lazy_apply3(std::function<T0(T1,T2,T3)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval());});
	}

	/**
	*  @brief weak lazy apply3
	*/
	template<typename T0,typename T1,typename T2,typename T3>
	steak::lazy_type_t<T0> lazy_apply3(std::function<T0(T1,T2,T3)> f,const T1& v1,const T2& v2,const T3& v3)
	{
		return std::function([=](){return f(v1,v2,v3);});
	}

	#define Apply4(f,v1,v2,v3,v4) steak::lazy_apply4(std::function(f),v1,v2,v3,v4)
	/**
	*  @brief nested lazy apply4
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4>
	steak::lazy_type_t<T0> lazy_apply4(std::function<T0(T1,T2,T3,T4)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval());});
	}

	/**
	*  @brief weak lazy apply4
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4>
	steak::lazy_type_t<T0> lazy_apply4(std::function<T0(T1,T2,T3,T4)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4)
	{
		return std::function([=](){return f(v1,v2,v3,v4);});
	}

	#define Apply5(f,v1,v2,v3,v4,v5) steak::lazy_apply5(std::function(f),v1,v2,v3,v4,v5)
	/**
	*  @brief nested lazy apply5
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
	steak::lazy_type_t<T0> lazy_apply5(std::function<T0(T1,T2,T3,T4,T5)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval());});
	}

	/**
	*  @brief weak lazy apply5
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5>
	steak::lazy_type_t<T0> lazy_apply5(std::function<T0(T1,T2,T3,T4,T5)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5);});
	}

	#define Apply6(f,v1,v2,v3,v4,v5,v6) steak::lazy_apply6(std::function(f),v1,v2,v3,v4,v5,v6)
	/**
	*  @brief nested lazy apply6
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	steak::lazy_type_t<T0> lazy_apply6(std::function<T0(T1,T2,T3,T4,T5,T6)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval());});
	}

	/**
	*  @brief weak lazy apply6
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6>
	steak::lazy_type_t<T0> lazy_apply6(std::function<T0(T1,T2,T3,T4,T5,T6)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6);});
	}

	#define Apply7(f,v1,v2,v3,v4,v5,v6,v7) steak::lazy_apply7(std::function(f),v1,v2,v3,v4,v5,v6,v7)
	/**
	*  @brief nested lazy apply7
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	steak::lazy_type_t<T0> lazy_apply7(std::function<T0(T1,T2,T3,T4,T5,T6,T7)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval());});
	}

	/**
	*  @brief weak lazy apply7
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7>
	steak::lazy_type_t<T0> lazy_apply7(std::function<T0(T1,T2,T3,T4,T5,T6,T7)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7);});
	}

	#define Apply8(f,v1,v2,v3,v4,v5,v6,v7,v8) steak::lazy_apply8(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8)
	/**
	*  @brief nested lazy apply8
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	steak::lazy_type_t<T0> lazy_apply8(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval());});
	}

	/**
	*  @brief weak lazy apply8
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8>
	steak::lazy_type_t<T0> lazy_apply8(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8);});
	}

	#define Apply9(f,v1,v2,v3,v4,v5,v6,v7,v8,v9) steak::lazy_apply9(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9)
	/**
	*  @brief nested lazy apply9
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
	steak::lazy_type_t<T0> lazy_apply9(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval());});
	}

	/**
	*  @brief weak lazy apply9
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9>
	steak::lazy_type_t<T0> lazy_apply9(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9);});
	}

	#define Apply10(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10) steak::lazy_apply10(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10)
	/**
	*  @brief nested lazy apply10
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
	steak::lazy_type_t<T0> lazy_apply10(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval());});
	}

	/**
	*  @brief weak lazy apply10
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10>
	steak::lazy_type_t<T0> lazy_apply10(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10);});
	}

	#define Apply11(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11) steak::lazy_apply11(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11)
	/**
	*  @brief nested lazy apply11
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
	steak::lazy_type_t<T0> lazy_apply11(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10,steak::lazy_type_t<T11> t11)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval(),t11.eval());});
	}

	/**
	*  @brief weak lazy apply11
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11>
	steak::lazy_type_t<T0> lazy_apply11(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10,const T11& v11)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11);});
	}

	#define Apply12(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12) steak::lazy_apply12(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12)
	/**
	*  @brief nested lazy apply12
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
	steak::lazy_type_t<T0> lazy_apply12(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10,steak::lazy_type_t<T11> t11,steak::lazy_type_t<T12> t12)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval(),t11.eval(),t12.eval());});
	}

	/**
	*  @brief weak lazy apply12
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12>
	steak::lazy_type_t<T0> lazy_apply12(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10,const T11& v11,const T12& v12)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12);});
	}

	#define Apply13(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13) steak::lazy_apply13(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13)
	/**
	*  @brief nested lazy apply13
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
	steak::lazy_type_t<T0> lazy_apply13(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10,steak::lazy_type_t<T11> t11,steak::lazy_type_t<T12> t12,steak::lazy_type_t<T13> t13)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval(),t11.eval(),t12.eval(),t13.eval());});
	}

	/**
	*  @brief weak lazy apply13
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13>
	steak::lazy_type_t<T0> lazy_apply13(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10,const T11& v11,const T12& v12,const T13& v13)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13);});
	}

	#define Apply14(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14) steak::lazy_apply14(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14)
	/**
	*  @brief nested lazy apply14
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
	steak::lazy_type_t<T0> lazy_apply14(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10,steak::lazy_type_t<T11> t11,steak::lazy_type_t<T12> t12,steak::lazy_type_t<T13> t13,steak::lazy_type_t<T14> t14)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval(),t11.eval(),t12.eval(),t13.eval(),t14.eval());});
	}

	/**
	*  @brief weak lazy apply14
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14>
	steak::lazy_type_t<T0> lazy_apply14(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10,const T11& v11,const T12& v12,const T13& v13,const T14& v14)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14);});
	}

	#define Apply15(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15) steak::lazy_apply15(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15)
	/**
	*  @brief nested lazy apply15
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
	steak::lazy_type_t<T0> lazy_apply15(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10,steak::lazy_type_t<T11> t11,steak::lazy_type_t<T12> t12,steak::lazy_type_t<T13> t13,steak::lazy_type_t<T14> t14,steak::lazy_type_t<T15> t15)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval(),t11.eval(),t12.eval(),t13.eval(),t14.eval(),t15.eval());});
	}

	/**
	*  @brief weak lazy apply15
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15>
	steak::lazy_type_t<T0> lazy_apply15(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10,const T11& v11,const T12& v12,const T13& v13,const T14& v14,const T15& v15)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15);});
	}

	#define Apply16(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16) steak::lazy_apply16(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16)
	/**
	*  @brief nested lazy apply16
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
	steak::lazy_type_t<T0> lazy_apply16(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10,steak::lazy_type_t<T11> t11,steak::lazy_type_t<T12> t12,steak::lazy_type_t<T13> t13,steak::lazy_type_t<T14> t14,steak::lazy_type_t<T15> t15,steak::lazy_type_t<T16> t16)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval(),t11.eval(),t12.eval(),t13.eval(),t14.eval(),t15.eval(),t16.eval());});
	}

	/**
	*  @brief weak lazy apply16
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16>
	steak::lazy_type_t<T0> lazy_apply16(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10,const T11& v11,const T12& v12,const T13& v13,const T14& v14,const T15& v15,const T16& v16)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16);});
	}

	#define Apply17(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17) steak::lazy_apply17(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17)
	/**
	*  @brief nested lazy apply17
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
	steak::lazy_type_t<T0> lazy_apply17(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10,steak::lazy_type_t<T11> t11,steak::lazy_type_t<T12> t12,steak::lazy_type_t<T13> t13,steak::lazy_type_t<T14> t14,steak::lazy_type_t<T15> t15,steak::lazy_type_t<T16> t16,steak::lazy_type_t<T17> t17)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval(),t11.eval(),t12.eval(),t13.eval(),t14.eval(),t15.eval(),t16.eval(),t17.eval());});
	}

	/**
	*  @brief weak lazy apply17
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17>
	steak::lazy_type_t<T0> lazy_apply17(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10,const T11& v11,const T12& v12,const T13& v13,const T14& v14,const T15& v15,const T16& v16,const T17& v17)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17);});
	}

	#define Apply18(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18) steak::lazy_apply18(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18)
	/**
	*  @brief nested lazy apply18
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
	steak::lazy_type_t<T0> lazy_apply18(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10,steak::lazy_type_t<T11> t11,steak::lazy_type_t<T12> t12,steak::lazy_type_t<T13> t13,steak::lazy_type_t<T14> t14,steak::lazy_type_t<T15> t15,steak::lazy_type_t<T16> t16,steak::lazy_type_t<T17> t17,steak::lazy_type_t<T18> t18)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval(),t11.eval(),t12.eval(),t13.eval(),t14.eval(),t15.eval(),t16.eval(),t17.eval(),t18.eval());});
	}

	/**
	*  @brief weak lazy apply18
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18>
	steak::lazy_type_t<T0> lazy_apply18(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10,const T11& v11,const T12& v12,const T13& v13,const T14& v14,const T15& v15,const T16& v16,const T17& v17,const T18& v18)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18);});
	}

	#define Apply19(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19) steak::lazy_apply19(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19)
	/**
	*  @brief nested lazy apply19
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
	steak::lazy_type_t<T0> lazy_apply19(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10,steak::lazy_type_t<T11> t11,steak::lazy_type_t<T12> t12,steak::lazy_type_t<T13> t13,steak::lazy_type_t<T14> t14,steak::lazy_type_t<T15> t15,steak::lazy_type_t<T16> t16,steak::lazy_type_t<T17> t17,steak::lazy_type_t<T18> t18,steak::lazy_type_t<T19> t19)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval(),t11.eval(),t12.eval(),t13.eval(),t14.eval(),t15.eval(),t16.eval(),t17.eval(),t18.eval(),t19.eval());});
	}

	/**
	*  @brief weak lazy apply19
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19>
	steak::lazy_type_t<T0> lazy_apply19(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10,const T11& v11,const T12& v12,const T13& v13,const T14& v14,const T15& v15,const T16& v16,const T17& v17,const T18& v18,const T19& v19)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19);});
	}

	#define Apply20(f,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20) steak::lazy_apply20(std::function(f),v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20)
	/**
	*  @brief nested lazy apply20
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
	steak::lazy_type_t<T0> lazy_apply20(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20)> f,steak::lazy_type_t<T1> t1,steak::lazy_type_t<T2> t2,steak::lazy_type_t<T3> t3,steak::lazy_type_t<T4> t4,steak::lazy_type_t<T5> t5,steak::lazy_type_t<T6> t6,steak::lazy_type_t<T7> t7,steak::lazy_type_t<T8> t8,steak::lazy_type_t<T9> t9,steak::lazy_type_t<T10> t10,steak::lazy_type_t<T11> t11,steak::lazy_type_t<T12> t12,steak::lazy_type_t<T13> t13,steak::lazy_type_t<T14> t14,steak::lazy_type_t<T15> t15,steak::lazy_type_t<T16> t16,steak::lazy_type_t<T17> t17,steak::lazy_type_t<T18> t18,steak::lazy_type_t<T19> t19,steak::lazy_type_t<T20> t20)
	{
		return std::function([=](){return f(t1.eval(),t2.eval(),t3.eval(),t4.eval(),t5.eval(),t6.eval(),t7.eval(),t8.eval(),t9.eval(),t10.eval(),t11.eval(),t12.eval(),t13.eval(),t14.eval(),t15.eval(),t16.eval(),t17.eval(),t18.eval(),t19.eval(),t20.eval());});
	}

	/**
	*  @brief weak lazy apply20
	*/
	template<typename T0,typename T1,typename T2,typename T3,typename T4,typename T5,typename T6,typename T7,typename T8,typename T9,typename T10,typename T11,typename T12,typename T13,typename T14,typename T15,typename T16,typename T17,typename T18,typename T19,typename T20>
	steak::lazy_type_t<T0> lazy_apply20(std::function<T0(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20)> f,const T1& v1,const T2& v2,const T3& v3,const T4& v4,const T5& v5,const T6& v6,const T7& v7,const T8& v8,const T9& v9,const T10& v10,const T11& v11,const T12& v12,const T13& v13,const T14& v14,const T15& v15,const T16& v16,const T17& v17,const T18& v18,const T19& v19,const T20& v20)
	{
		return std::function([=](){return f(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20);});
	}

	#define Cons0(T,name,ret)\
T inline ret name(){return steak::case_class_t<steak_constructors::name>();}\
T inline steak::lazy_type_t<ret> name##_(){return std::function([=](){return steak::case_class_t<steak_constructors::name>();});}\

	#define Cons1(T,name,t1,ret)\
T inline ret name(const t1& v1){return steak::case_class_t<steak_constructors::name,t1>(v1);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1>(v1);});}\
T inline ret name(steak::lazy_type_t<t1> v1){return steak::case_class_t<steak_constructors::name,t1>(v1.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1>(v1.eval());});}\

	#define Cons2(T,name,t1,t2,ret)\
T inline ret name(const t1& v1,const t2& v2){return steak::case_class_t<steak_constructors::name,t1,t2>(v1,v2);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2>(v1,v2);});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2){return steak::case_class_t<steak_constructors::name,t1,t2>(v1.eval(),v2);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2>(v1.eval(),v2);});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2){return steak::case_class_t<steak_constructors::name,t1,t2>(v1,v2.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2>(v1,v2.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2){return steak::case_class_t<steak_constructors::name,t1,t2>(v1.eval(),v2.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2>(v1.eval(),v2.eval());});}\

	#define Cons3(T,name,t1,t2,t3,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1,v2,v3);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1,v2,v3);});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1.eval(),v2,v3);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1.eval(),v2,v3);});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1,v2.eval(),v3);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1,v2.eval(),v3);});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1.eval(),v2.eval(),v3);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1.eval(),v2.eval(),v3);});}\
T inline ret name(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1,v2,v3.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1,v2,v3.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1.eval(),v2,v3.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1.eval(),v2,v3.eval());});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1,v2.eval(),v3.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1,v2.eval(),v3.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1.eval(),v2.eval(),v3.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3>(v1.eval(),v2.eval(),v3.eval());});}\

	#define Cons4(T,name,t1,t2,t3,t4,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2,v3,v4);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2,v3,v4);});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,const t4& v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2,v3,v4);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,const t4& v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2,v3,v4);});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2.eval(),v3,v4);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2.eval(),v3,v4);});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2.eval(),v3,v4);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2.eval(),v3,v4);});}\
T inline ret name(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2,v3.eval(),v4);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2,v3.eval(),v4);});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2,v3.eval(),v4);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2,v3.eval(),v4);});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2.eval(),v3.eval(),v4);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2.eval(),v3.eval(),v4);});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2.eval(),v3.eval(),v4);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2.eval(),v3.eval(),v4);});}\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2,v3,v4.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2,v3,v4.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2,v3,v4.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2,v3,v4.eval());});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2.eval(),v3,v4.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2.eval(),v3,v4.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2.eval(),v3,v4.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2.eval(),v3,v4.eval());});}\
T inline ret name(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2,v3.eval(),v4.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2,v3.eval(),v4.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2,v3.eval(),v4.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2,v3.eval(),v4.eval());});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2.eval(),v3.eval(),v4.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1,v2.eval(),v3.eval(),v4.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2.eval(),v3.eval(),v4.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4>(v1.eval(),v2.eval(),v3.eval(),v4.eval());});}\

	#define Cons5(T,name,t1,t2,t3,t4,t5,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3,v4,v5);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3,v4,v5);});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3,v4,v5);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3,v4,v5);});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3,v4,v5);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3,v4,v5);});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3,v4,v5);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3,v4,v5);});}\
T inline ret name(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3.eval(),v4,v5);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3.eval(),v4,v5);});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3.eval(),v4,v5);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3.eval(),v4,v5);});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3.eval(),v4,v5);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3.eval(),v4,v5);});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3.eval(),v4,v5);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3.eval(),v4,v5);});}\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3,v4.eval(),v5);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3,v4.eval(),v5);});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3,v4.eval(),v5);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3,v4.eval(),v5);});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3,v4.eval(),v5);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3,v4.eval(),v5);});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3,v4.eval(),v5);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3,v4.eval(),v5);});}\
T inline ret name(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3.eval(),v4.eval(),v5);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3.eval(),v4.eval(),v5);});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3.eval(),v4.eval(),v5);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3.eval(),v4.eval(),v5);});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3.eval(),v4.eval(),v5);}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3.eval(),v4.eval(),v5);});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,const t5& v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5);}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,const t5& v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5);});}\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3,v4,v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3,v4,v5.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,const t4& v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3,v4,v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,const t4& v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3,v4,v5.eval());});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3,v4,v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3,v4,v5.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3,v4,v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,const t4& v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3,v4,v5.eval());});}\
T inline ret name(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3.eval(),v4,v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3.eval(),v4,v5.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3.eval(),v4,v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,const t4& v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3.eval(),v4,v5.eval());});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3.eval(),v4,v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3.eval(),v4,v5.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3.eval(),v4,v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,const t4& v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3.eval(),v4,v5.eval());});}\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3,v4.eval(),v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3,v4.eval(),v5.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3,v4.eval(),v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,const t3& v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3,v4.eval(),v5.eval());});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3,v4.eval(),v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3,v4.eval(),v5.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3,v4.eval(),v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,const t3& v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3,v4.eval(),v5.eval());});}\
T inline ret name(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3.eval(),v4.eval(),v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2,v3.eval(),v4.eval(),v5.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3.eval(),v4.eval(),v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,const t2& v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2,v3.eval(),v4.eval(),v5.eval());});}\
T inline ret name(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3.eval(),v4.eval(),v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1,v2.eval(),v3.eval(),v4.eval(),v5.eval());});}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval());}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval());});}\

	#define Cons6(T,name,t1,t2,t3,t4,t5,t6,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6>(v1,v2,v3,v4,v5,v6);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6>(v1,v2,v3,v4,v5,v6);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval());});}\

	#define Cons7(T,name,t1,t2,t3,t4,t5,t6,t7,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7>(v1,v2,v3,v4,v5,v6,v7);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7>(v1,v2,v3,v4,v5,v6,v7);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval());});}\

	#define Cons8(T,name,t1,t2,t3,t4,t5,t6,t7,t8,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8>(v1,v2,v3,v4,v5,v6,v7,v8);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8>(v1,v2,v3,v4,v5,v6,v7,v8);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval());});}\

	#define Cons9(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9>(v1,v2,v3,v4,v5,v6,v7,v8,v9);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9>(v1,v2,v3,v4,v5,v6,v7,v8,v9);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval());});}\

	#define Cons10(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval());});}\

	#define Cons11(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval());});}\

	#define Cons12(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval());});}\

	#define Cons13(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval());});}\

	#define Cons14(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval());});}\

	#define Cons15(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval());});}\

	#define Cons16(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15,const t16& v16){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval(),v16.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15,const t16& v16){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval(),v16.eval());});}\

	#define Cons17(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15,const t16& v16,const t17& v17){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval(),v16.eval(),v17.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15,const t16& v16,const t17& v17){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval(),v16.eval(),v17.eval());});}\

	#define Cons18(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15,const t16& v16,const t17& v17,const t18& v18){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17,steak::lazy_type_t<t18> v18){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval(),v16.eval(),v17.eval(),v18.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15,const t16& v16,const t17& v17,const t18& v18){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17,steak::lazy_type_t<t18> v18){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval(),v16.eval(),v17.eval(),v18.eval());});}\

	#define Cons19(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15,const t16& v16,const t17& v17,const t18& v18,const t19& v19){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17,steak::lazy_type_t<t18> v18,steak::lazy_type_t<t19> v19){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval(),v16.eval(),v17.eval(),v18.eval(),v19.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15,const t16& v16,const t17& v17,const t18& v18,const t19& v19){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17,steak::lazy_type_t<t18> v18,steak::lazy_type_t<t19> v19){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval(),v16.eval(),v17.eval(),v18.eval(),v19.eval());});}\

	#define Cons20(T,name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20,ret)\
T inline ret name(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15,const t16& v16,const t17& v17,const t18& v18,const t19& v19,const t20& v20){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20);}\
T inline ret name(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17,steak::lazy_type_t<t18> v18,steak::lazy_type_t<t19> v19,steak::lazy_type_t<t20> v20){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval(),v16.eval(),v17.eval(),v18.eval(),v19.eval(),v20.eval());}\
T inline steak::lazy_type_t<ret> name##_(const t1& v1,const t2& v2,const t3& v3,const t4& v4,const t5& v5,const t6& v6,const t7& v7,const t8& v8,const t9& v9,const t10& v10,const t11& v11,const t12& v12,const t13& v13,const t14& v14,const t15& v15,const t16& v16,const t17& v17,const t18& v18,const t19& v19,const t20& v20){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20>(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15,v16,v17,v18,v19,v20);});}\
T inline steak::lazy_type_t<ret> name##_(steak::lazy_type_t<t1> v1,steak::lazy_type_t<t2> v2,steak::lazy_type_t<t3> v3,steak::lazy_type_t<t4> v4,steak::lazy_type_t<t5> v5,steak::lazy_type_t<t6> v6,steak::lazy_type_t<t7> v7,steak::lazy_type_t<t8> v8,steak::lazy_type_t<t9> v9,steak::lazy_type_t<t10> v10,steak::lazy_type_t<t11> v11,steak::lazy_type_t<t12> v12,steak::lazy_type_t<t13> v13,steak::lazy_type_t<t14> v14,steak::lazy_type_t<t15> v15,steak::lazy_type_t<t16> v16,steak::lazy_type_t<t17> v17,steak::lazy_type_t<t18> v18,steak::lazy_type_t<t19> v19,steak::lazy_type_t<t20> v20){return std::function([=](){return steak::case_class_t<steak_constructors::name,t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20>(v1.eval(),v2.eval(),v3.eval(),v4.eval(),v5.eval(),v6.eval(),v7.eval(),v8.eval(),v9.eval(),v10.eval(),v11.eval(),v12.eval(),v13.eval(),v14.eval(),v15.eval(),v16.eval(),v17.eval(),v18.eval(),v19.eval(),v20.eval());});}\

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