// 7.容器与数据结构.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std.h"
//7.1
#include <boost/array.hpp>

int main()
{
    //7.1 array
    {
        //7.1.3 用法
        {
			boost::array<int, 10> ar;           //一个大小为 10 的 int 数组

			ar[0] = 1;                          //使用 operator[]
			ar.back() = 10;                     //back()访问最后一个元素
			assert(ar[ar.max_size() - 1] == 10);

			ar.assign(777);                     //数组所有元素赋值为 777
			for (auto x : ar)                    //for + auto 遍历元素
			{
				cout << x << ",";
			}

			int* p = ar.c_array();              //获得原始数组指针
			*(p + 5) = 253;                     //指针算术运算
			cout << ar[5] << endl;

			ar.at(8) = 666;                     //使用 at 函数访问元素
			sort(ar.begin(), ar.end());         //可以使用标准算法排序
        }
        //using namespace boost;
        
    }
    std::cout << "Hello World!\n";
}