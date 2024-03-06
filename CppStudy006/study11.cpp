module;
#include <cstdio>
#include <cstdarg>
module study11;

using namespace std;
namespace study11_005
{
	extern bool debug{ false };
	void debug_out(const char* str, ...) {
		va_list ap;
		if (debug) {
			va_start(ap, str);
			auto result{ vfprintf_s(stderr, str, ap) };
			cout << std::format("vfprintf_s result = {}", result) << endl;
			va_end(ap);
		}
	}
	void study001()
	{
		debug = true;
		debug_out("int %d\n", 5);
		debug_out("String %s and int %d\n", "hello", 5);
		debug_out("Many ints: %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5);
	}
	void print_ints(size_t num, ...) {
		va_list ap;
		va_start(ap, num);
		for (size_t i{0}; i < num; ++i) {
			const int temp{ va_arg(ap, int) };
			if (i == num - 1)
				cout << temp;
			else
				cout << temp << ", ";
		}
		va_end(ap);
		cout << endl;
	}
	void study002() {
		print_ints(5, 5, 3, 4, 2, 1);
	}
}