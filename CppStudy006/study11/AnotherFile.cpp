#include "AnotherFile.h"
import std;

namespace // 익명 네임스페이스를 사용하면 내부 링크로 처리된다.
{
	void f(); 

	void f() {
		std::cout << "f\n";
	}
}

namespace study11_003
{
	
	void study002() {
		
	}
}

