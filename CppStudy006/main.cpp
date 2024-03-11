import std;
import study13;

using namespace std;
int main() {
	// set locale to UTF-8, and set wcout to use it
	std::locale::global(std::locale("en_US.utf8"));
	std::wcout.imbue(std::locale());

	cout << "Program start\n";
	study13_001::study006();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
