// 7.容器与数据结构.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std.h"
//7.1
#include <boost/array.hpp>
#include <boost/assign.hpp>
//7.2
#include <boost/dynamic_bitset.hpp>

int main()
{
    //7.1 array
    {
		//using namespace boost;
        //7.1.3 用法
        {
			boost::array<int, 10> ar;           //一个大小为 10 的 int 数组

			ar[0] = 1;                          //使用 operator[]
			ar.back() = 10;                     //back()访问最后一个元素
			assert(ar[ar.max_size() - 1] == 10);

			ar.assign(777);                     //数组所有元素赋值为 777
			for (auto x : ar)                   //for + auto 遍历元素
			{
				cout << x << " ,";
			}

			int* p = ar.c_array();              //获得原始数组指针
			*(p + 5) = 253;                     //指针算术运算
			cout << ar[5] << endl;

			ar.at(8) = 666;                     //使用 at 函数访问元素
			sort(ar.begin(), ar.end());         //可以使用标准算法排序
        }
        
        //7.1.5 初始化
		{
			boost::array<string, 3> ar = { "allice","bob","carl" };

			int a[10] = { 0 };								//普通数组初始化
			boost::array<int, 10> ar1 = { 0 };				//array 初始化
			assert(std::equal(ar1.begin(), ar1.end(), a));	//两者的值同为全 0

			boost::array<string, 3> ar2 = { "racer" };		//初始化第一个元素
			assert(ar2.at(1).empty());

			using namespace boost::assign;
			boost::array<int, 3> arr(list_of(2)(4)(6));		//只能用 list_of
			
			for (int i = 0; i < arr.size(); ++i) {
				cout << arr[i] << ",";
			}
		}
    }

	//7.2 dynamic_bitset
	{
		using namespace boost;
		//7.2.2 创建与赋值
		{
			dynamic_bitset<> db1;							//空的 dynamic_bitset
			dynamic_bitset<> db2(10);						//大小为 10 的 dynamic_bitset
			dynamic_bitset<> db3(0x16, BOOST_BINARY(10101));//大小为 22 的 dynamic_bitset
			dynamic_bitset<> db4(string("0100"));			//字符串构造
			dynamic_bitset<> db5(db3);						//拷贝构造

			dynamic_bitset<> db6;
			db6 = db4;										//赋值操作符

			cout << hex << db5.to_ulong() << endl;			//转换为整数
			cout << db4[0] << db4[1] << db4[2] << endl;		//使用 operator[]
		}

		//7.2.3 容器操作
		{
			{
				dynamic_bitset<> db;	//空的 dynamic_bitset

				db.resize(10, true);	//扩展为 10 个二进制位，值全为 1
				cout << db << endl;		//输出 1111111111

				db.resize(5);			//缩小容量为 5
				cout << db << endl;		//输出 11111

			}

			{
				dynamic_bitset<> db(5, BOOST_BINARY(01110));
				cout << db << endl;						//输出 01110
				assert(db.size());						//目前有 5 个二进制位

				db.clear();								//清空 dynamic_bitset
				assert(db.empty() && db.size() == 0);	//判断 dynamic_bitset 是否为空

#ifdef  _WIN32
				assert(dynamic_bitset<>(64).num_blocks() == 2);//num_blocks() 的计算公式: size()/sizeof(Block)*8 + 1
				assert(dynamic_bitset<>(65).num_blocks() == 3);
#endif
#ifdef  _WIN64
				assert(dynamic_bitset<>(64).num_blocks() == 1);//num_blocks() 的计算公式: size()/sizeof(Block)*8 + 1
				assert(dynamic_bitset<>(65).num_blocks() == 2);
#endif
				
			}

			{
				dynamic_bitset<> db(5, BOOST_BINARY(01001));
				db.push_back(true);
				assert(db.to_ulong() == BOOST_BINARY_UL(101001));
			}

			{
				dynamic_bitset<> db(5, BOOST_BINARY(01001));
				db.append(BOOST_BINARY(101));
				assert(db.size() == sizeof(unsigned long) * 8 + 5);
				cout << db << endl;
			}
		}

		//7.2.4 位运算与比较运算
		{
			dynamic_bitset<> db1(4, BOOST_BINARY(1010));
			db1[0] &= 1;		//按位与运算
			db1[1] ^= 1;		//按位异或运算
			cout << db1 << endl;

			dynamic_bitset<> db2(4, BOOST_BINARY(0101));
			assert(db1 > db2);

			cout << (db1 ^ db2) << endl;
			cout << (db1 | db2) << endl;
		}

		//7.2.5 访问元素
		{
			{
				dynamic_bitset<> db(4, BOOST_BINARY(0101));

				assert(db.test(0) && !db.test(1));
				assert(db.any() && !db.none());
				assert(db.count() == 2);
			}

			{
				dynamic_bitset<> db(4, BOOST_BINARY(0101));

				db.flip();	//翻转所有二进制位
				assert(db.to_ulong() == BOOST_BINARY(1010));

				db.set();				//置所有位为 1
				assert(!db.none());		//容器不存在二进制位 1，返回true

				db.reset();				//置全部或特定位置的值为 0
				assert(!db.any());		//容器存在二进制位 1，返回true

				db.set(1, 1);
				assert(db.count() == 1);//统计容器中所有值为 1 的元素的数量
			}

			{
				dynamic_bitset<> db(5, BOOST_BINARY(00101));

				auto pos = db.find_first();	//从最低位找二进制位 1
				assert(pos == 0);

				pos = db.find_next(pos);	//从 pos 位置开始找下一个二进制位 1
				assert(pos == 2);
			}
		}

		//7.2.5 类型转换
		{
			dynamic_bitset<> db(10, BOOST_BINARY(1010101));
			cout << hex << db.to_ulong() << endl;	//16进制
			cout << oct << db.to_ulong() << endl;	//8进制
			cout << dec << db.to_ulong() << endl;	//10进制
		}
	}
    std::cout << "Hello World!\n";
}
