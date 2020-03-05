// 6.正确性与测试.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std.h"
//6.1
//#define BOOST_DISABLE_ASSERTS			//6.1.2
//#include <cassert>

//6.1.3
#include <boost/format.hpp>
namespace boost {
	void assertion_failed(char const* expr, char const* function, char const* file, long line){}
	void assertion_failed_msg(char const* expr, char const* msg, char const* function, char const* file, long line)
	{
		boost::format fmt("Assertion failed!\nExpression: %s\n"
						  "Function: %s\nFile: %s\nLine: %ld\n"
						  "Msg: %s\n\n");
		fmt% expr% function% file% line% msg;
		cout << fmt;
	}
}
#define BOOST_ENABLE_ASSERT_HANDLER
#include <boost/assert.hpp>

//6.2
#include <boost/static_assert.hpp>

namespace static_assert_6_2 
{
	template<typename T>
	T my_min(T a, T b)
	{
		BOOST_STATIC_ASSERT(sizeof(T) < sizeof(int));
		return a < b ? a : b;
	}

	class empty_class
	{
		//在类域中静态断言，要求 int 至少 4 字节
		BOOST_STATIC_ASSERT_MSG(sizeof(int) >= 4, "for 32 bit");
	};
}

//6.3
#include <boost/smart_ptr.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/core/lightweight_test_trait.hpp>

int main()
{
	//6.1 assert
	{
		using namespace boost;
		//6.1.1基本用法
		{
			auto func = [](int x) -> double
			{
				BOOST_ASSERT_MSG(x != 0, "divided by zero");
				return 1.0 / x;
			};
			//func(0);
		}

		//6.1.2禁用断言
		{
			auto func = [](int x) -> double
			{
				BOOST_ASSERT(x != 0 && "divided by zero");//失效
				cout << "after BOOST_ASSERT" << endl;

				assert(x != 0 && "divided by zero");	  //有效
				cout << "after assert" << endl;

				return 1.0 / x;
			};
			//func(0);
		}

		//6.1.3 扩展用法
		{
			auto func = [](int x) -> double
			{
				BOOST_ASSERT_MSG(x != 0 , "divided by zero");//失效

				return 1.0 / x;
			};
			double r = func(0);
			cout << r;
		}
	}

	//6.2 static_assert
	{
		using namespace static_assert_6_2;
		//6.2.2 用法
		{
			cout << my_min((short)1, (short)3);	//编译OK
			//cout << my_min(1L, 3L);				//编译期错误

			//名字空间域静态断言，是一个“空类”
			BOOST_STATIC_ASSERT(sizeof(empty_class) == 1);
		}
	}

	//6.3 lightweight_test
	{
		//6.3.2 用法
		{
			auto p = make_shared<int>(10);				//智能指针

			BOOST_TEST(*p == 10);						//测试解引用
			BOOST_TEST(p.unique());						//测试唯一性

			BOOST_TEST_EQ(p.use_count(), 1);			//相等测试
			BOOST_TEST_NE(*p, 20);						//不等测试

			p.reset();
			BOOST_TEST(!p);

			BOOST_TEST_THROWS(*p, std::runtime_error);	//测试抛出异常，失败
			BOOST_ERROR("error accured!!");				//输出错误消息

			boost::report_errors();						//输出测试报告
		}
		
		//6.3.3 测试元编程
		{
			BOOST_TEST_TRAIT_TRUE((is_integral<int>));	//int 是整数，注意圆括号
			BOOST_TEST_TRAIT_FALSE((is_function<int>));	//int 不是函数

			boost::report_errors();		//输出测试报告
		}
	}
    std::cout << "Hello World!\n";
}

