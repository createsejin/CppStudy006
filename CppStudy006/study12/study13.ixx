module;
#include <cstring>
#include <stdio.h>
#include <time.h>
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

    export void study005() { // p.691
        cout.exceptions(ios::failbit | ios::badbit | ios::eofbit);
        try {
            cout << "Hello World." << endl;
        } catch (const ios_base::failure& ex) {
            cerr << "Caught exception: " << ex.what() << ", error code = " << ex.code() << endl;
        }
        cout.clear();
	}

    export void study006() {
        // bool
        constexpr bool my_bool{ true };
        cout << "This is the default: " << my_bool << endl;
        cout << "This should be true: " << boolalpha << my_bool << endl;
        cout << "This should be 1: " << noboolalpha << my_bool << endl;

        constexpr int i{ 123 };
        printf_s("This should be |   123|: |%6d|\n", i);
        cout << "This should be |   123|: |" << setw(6) << i << "|" << endl;

        printf_s("This should be |000123|: |%06d|\n", i);
        cout << "This should be |000123|: |" << setfill('0') << setw(6) << i << "|" << endl;

        cout << "This should be |***123|: |" << setfill('*') << setw(6) << i << "|" << endl;
        cout << setfill(' '); // reset

        // float
        constexpr double db1{ 1.452 };
        constexpr double db2{ 5 };
        cout << "This should be | 5|: |" << setw(2) << noshowpoint << db2 << "|" << endl;
        cout << "This should be @@1.452: " << setw(7) << setfill('@') << db1 << endl;
        cout << showpoint << setfill(' ');

        cout.imbue(std::locale("en_US.utf8"));

        cout << "This is 1234567 formatted according to your location: " << 1234567 << endl;
        cout << put_money("120000") << "\n" << endl;

        const time_t t{ std::time(nullptr) };
        tm buf;
        localtime_s(&buf, &t);
        cout << put_time(&buf, "%c") << endl;

        cout << "This should be: \"Quoted string with \\\"embedded quotes\\\".\": " <<
            quoted("Quoted string with \"embedded quotes\".") << endl;

        cout.precision(5);
        cout << 1.23454623 << endl;
	}

    export void study007() {
		
	}
}