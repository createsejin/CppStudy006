module;
#include <cstring>
export module study13;

import std;
using namespace std;

namespace study13_001
{
	export void study001() { // p.689
		const char* test{ "hello there\n" };
		cout.write(test, std::strlen(test));
		cout.put('d');
	}

    auto get_args_from_input(const std::string_view prompt) -> std::vector<std::string> {
        std::string input;
        std::getline(std::cin, input);
        const auto pos = input.find(prompt);
        if (pos != std::string::npos) {
            input.erase(pos, prompt.size());
        }
        ranges::transform(input.begin(), input.end(), input.begin(),
            [](const unsigned char c) {
                return std::tolower(c, std::cout.getloc());
            });
        std::istringstream iss(input);
        std::vector<std::string> args;
        std::string arg;
        while (std::getline(iss, arg, ' ')) {
            args.push_back(arg);
        }
        return args;
    }

	export void study002() { // my custom command args input getter
		const std::string prompt{ "cmd> " };
		std::cout << prompt;
        const auto args{ get_args_from_input(prompt) };
        for (const auto& arg : args) {
            cout << arg << "\n";
        }
	}

    export void study003() { // p.690
        cout << "abc";
        cout.flush();
        cout << "def" << endl;
	}

    export void study004() { // p.690
        if (cout.good()) { cout << "All good.\n"; }
        cout.flush();
        if (cout.fail()) { cerr << "Unable to flush to stdout." << endl; }
        if (!cout) { cerr << "Unable to flush to stdout." << endl; }
	}

    export void study005() {
        cout.exceptions(ios::failbit | ios::badbit | ios::eofbit);
        try {
            cout << "Hello World." << endl;
        } catch (const ios_base::failure& ex) {
            cerr << "Caught exception: " << ex.what() << ", error code = " << ex.code() << endl;
        }
        cout.clear();
	}
}