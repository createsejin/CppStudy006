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
            input.erase(pos, 5);
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

	export void study002() {
		const std::string prompt{ "cmd> " };
		std::cout << prompt;
        const auto args{ get_args_from_input(prompt) };
        for (const auto& arg : args) {
            cout << arg << "\n";
        }
	}
}