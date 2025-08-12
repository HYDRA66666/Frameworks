#include <iostream>

#include "Foundation/iExceptionBase.h"
#include "Foundation/Infomation.h"

using namespace std;
using namespace HYDRA15::Frameworks::Foundation;

int foo()
{
	Infomation iInfo = { 1,12,0,0,nullptr,nullptr };
	std::string iDescription = "An error occurred in foo.";
		throw iExceptionBase({ 1,12,0,0,nullptr,nullptr }, "An error occurred in foo.");
	return 1;
}

int main() {
	try {
		foo();
	} catch (const exception& e) {
		cout << e.what() << std::endl;
	}
	return 0;
}