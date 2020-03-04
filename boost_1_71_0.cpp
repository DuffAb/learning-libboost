// boost_1_71_0.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "std.h"

#include "boost/version.hpp"
#include "boost/config.hpp"

int main()
{
    cout << BOOST_VERSION << endl;      //Boost 版本号
    cout << BOOST_LIB_VERSION << endl;  //Boost 版本号
    cout << BOOST_PLATFORM << endl;     //操作系统
    cout << BOOST_COMPILER << endl;     //编译器
    cout << BOOST_STDLIB << endl;       //标准库
    
    return 0;
}