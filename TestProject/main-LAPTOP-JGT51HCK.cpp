#include <map>
#include <mutex>
#include <vector>
#include <iostream>


template<class Container, class Lock>
class ContainerPlus
{
	Container container;
	Lock lock;

public:
	/*template<typename Func, typename... Args>
	auto call(Func func, Args&&... args)
	{
		std::lock_guard<Lock> guard(lock);
		return std::invoke(func, &container, std::forward<Args>(args)...);
	}*/

	template<typename F, typename... Args>
	auto call(F&& f, Args&&... args)
	{
		std::lock_guard<Lock> guard(lock);
		return std::invoke(std::forward<F>(f), container, std::forward<Args>(args)...);
	}


};


int main()
{
	ContainerPlus<std::vector<int>, std::mutex> cp;
	
	std::cout<< cp.call(&std::vector<int>::size);

	//cp.call(&std::vector<int>::push_back, 42);

	cp.call(static_cast<void (std::vector<int>::*)(int&&)>( & std::vector<int>::push_back), 42);

	std::cout<<cp.call(&std::vector<int>::size);
}