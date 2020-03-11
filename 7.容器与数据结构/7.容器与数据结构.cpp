// 7.容器与数据结构.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std.h"
//7.1
#include <boost/array.hpp>
#include <boost/assign.hpp>
//7.2
#include <boost/dynamic_bitset.hpp>
//7.3
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/functional/hash.hpp>
namespace unordered_7_3 {
	struct demo_class
	{
		int a;
		//实现unordered需要的自定义类的相等比较谓词
		friend bool operator==(const demo_class& l, const demo_class& r) {
			return l.a == r.a;
		}
	};
	//实现unordered需要的自定义类的散列函数
	size_t hash_value(demo_class& s) {
		return boost::hash<int>()(s.a);
	}
}

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
				db.append(BOOST_BINARY(101));				//把整数转换为一个Block再追加，使得dynamic_bitset 的大小增加一个Block的长度
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

		//7.2.6 类型转换
		{
			dynamic_bitset<> db(10, BOOST_BINARY(1010101));
			cout << db << endl;
			cout << hex << db.to_ulong() << endl;	//16进制
			cout << oct << db.to_ulong() << endl;	//8进制
			cout << dec << db.to_ulong() << endl;	//10进制

			db.append(10);							//追加一个整数
			cout << db << endl;
			cout << dec << db.to_ulong() << endl;	//10进制

			db.push_back(1);
			//cout << db.to_ulong() << endl;			//抛出异常
			string str;
			to_string(db, str);
			cout << str << endl;
		}

		//7.2.7 集合操作
		{
			dynamic_bitset<> db1(5, BOOST_BINARY(10101));
			dynamic_bitset<> db2(5, BOOST_BINARY(10010));

			cout << (db1 | db2) << endl;	//并集 10111
			cout << (db1 & db2) << endl;	//交集 10000
			cout << (db1 - db2) << endl;	//差集 00101

			dynamic_bitset<> db3(5, BOOST_BINARY(101));
			assert(db3.is_proper_subset_of(db1));	//检测一个对象是否另一个对象的真子集

			dynamic_bitset<> db4(db2);
			assert(db4.is_subset_of(db2));			//检测一个对象是否另一个对象的子集
			assert(!db4.is_proper_subset_of(db2));	//不是真子集
		}

		//7.2.8 综合运用
		{
			int n;
			//cin >> n;
			dynamic_bitset<> db(100);

			db.set();	//置所有位为 1
			for (dynamic_bitset<>::size_type i = db.find_next(1); i != dynamic_bitset<>::npos; i = db.find_next(i)) 
			{
				for (dynamic_bitset<>::size_type j = db.find_next(i); j != dynamic_bitset<>::npos; j = db.find_next(j)) //db.find_next(i) 从 i 位置开始找下一个二进制位 1
				{
					if (j % i == 0)
					{
						db[j] = 0;		//被整除，非质数
					}
				}
			}

			for (dynamic_bitset<>::size_type i = db.find_next(2); i != dynamic_bitset<>::npos; i = db.find_next(i))
			{
				cout << i << ", ";
			}
			cout << db << endl;

		}
	}

	//7.3 unordered
	{}
	{
		using namespace boost;
		//7.3.2 散列集合的用法
		{
			{
				unordered_set<int> s = { 1,2,3,4,5 };	//初始化数据

				for (auto x : s) {						//使用 for 遍历集合
					cout << x << " ";
				}
				cout << endl;
				cout << s.size() << endl;				//获取容器大小

				s.clear();								//清空集合
				cout << s.empty() << endl;				//判断集合是否空

				s.insert(8);
				s.insert(45);							//使用 insert() 函数
				cout << s.size() << endl;
				cout << *s.find(8) << endl;				//查找元素

				s.erase(45);							//删除元素
			}

			//C++11标准
			{
				typedef complex<double> complex_t;	//使用标准库的复数类型
				unordered_set<complex_t> s;			//散列容器容纳复数

				s.emplace(1.0, 2.0);				//直接使用多个参数构造袁术并插入
				s.emplace(3.0, 4.0);

				for (auto & x : s) {
					cout << x << ", ";
				}
				cout << endl;

				s.emplace_hint(s.begin(), 5.0, 6.0);//在容器前端插入，不能保证位置
				for (auto& x : s) {
					cout << x << ",";
				}
			}
		}
		
		//7.3.4 散列映射的用法
		{
			//基本用法
			{
				using namespace boost::assign;

				unordered_map<int, string> um = map_list_of(1, "one")(2, "two")(3, "three");//使用 assign 初始化

				um.insert(make_pair(10, "ten"));		//可以使用 insert() 函数
				cout << um[10] << endl;
				um[11] = "eleven";						//关联数组用法
				um[15] = "fifteen";
				um[15] = "fifteen2";

				auto p = um.begin();
				for (; p != um.end(); ++p) {
					cout << p->first << "-" << p->second << ",";
				}
				cout << endl;

				um.erase(11);							//删除键值为 11 的元素
				cout << um.size() << endl;
			}

			//C++11标准
			{
				typedef complex<double> complex_t;			//使用标准库的复数类型
				typedef unordered_map<int, complex_t> um_t;	//散列映射类型
				um_t s;

				s.emplace(boost::unordered::piecewise_construct,	//分段构造 pair
					make_tuple(1), make_tuple(1.0, 2.0));			//使用 make_tuple
				s.emplace(boost::unordered::piecewise_construct,	//分段构造 pair
					make_tuple(3), make_tuple(3.0, 4.0));			//使用 make_tuple

				for (auto& x : s) {
					cout << x.first << "<->" << x.second << ",";
				}
				cout << endl;

				s.emplace_hint(s.begin(),							//在前端放置元素
					boost::unordered::piecewise_construct,
					make_tuple(5), make_tuple(5.0, 6.0));
				for (auto& x : s) {
					cout << x.first << "<->" << x.second << ",";
				}
			}
		}

		//7.3.5 高级议题
		{
			using namespace unordered_7_3;
			using namespace boost::assign;

			unordered_set<int> us = (list_of(1), 2, 3, 4);
			cout << us.bucket_count() << endl;

			for (size_t i = 0; i < us.bucket_count(); ++i) {//访问每个桶
				cout << us.bucket_size(i) << ",";
			}

			unordered_set<int> us1(100);	//要求使用 100 个桶存储数据
			us1.rehash(200);				//改为使用 200 个桶

			unordered_set<demo_class> us3;
		}
	}
	{

	}
    std::cout << "Hello World!\n";
}
