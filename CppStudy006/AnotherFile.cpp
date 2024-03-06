import std;

static void f(); // 이렇게 하면 내부링크로 처리되어서 외부 파일(FirstFile.cpp)에서 사용할 수 없게 된다.

void f() {
	std::cout << "f\n";
}