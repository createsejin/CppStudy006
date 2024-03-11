#include <Windows.h>
import std;
import study13;

using namespace std;
int main() { // .\x64\Debug\CppStudy006.exe
	// set locale to UTF-8, and set wcout to use it
	std::locale::global(std::locale("ko_KR.utf8"));
	std::wcout.imbue(std::locale());
	std::wcin.imbue(std::locale());
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	cout << "Program start\n";
	study13_001::study016();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
