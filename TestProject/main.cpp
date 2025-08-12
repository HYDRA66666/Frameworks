#include "StaffUnion/ThreadLake.h"
#include <iostream>
#include <Windows.h>

int foo(int a, int b)
{
	return a + b;
}


using namespace HYDRA15::Frameworks::StaffUnion;

int main()
{
	ThreadLake lake(4, 10);
	auto task1 = std::packaged_task<int()>(std::bind(foo, 1, 2));
	auto future1 = lake.submit(task1, [] { std::cout << "Task 1 completed.\n"; });
	auto task2 = std::packaged_task<int()>(std::bind(foo, 3, 4));
	auto future2 = lake.submit(task2, [] { std::cout << "Task 2 completed.\n"; });
	auto future3 = lake.submit(foo, 4, 5);

	Sleep(1000); // 等待一段时间以确保所有任务完成
	std::cout << "Result of Task 1: " << future1.get() << std::endl;
	std::cout << "Result of Task 2: " << future2.get() << std::endl;
	std::cout << "Result of Task 3: " << future3.get() << std::endl;
	
	return 0;
}