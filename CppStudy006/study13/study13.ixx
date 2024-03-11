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

    auto get_args_from_input_v2(const size_t argc) -> std::vector<std::string> {
        std::vector args{ argc, ""s };
        for (size_t i{0}; i < argc; ++i) {
            cin >> args[i];
        }
        return args;
	}

    auto get_args_from_wchar(const size_t argc) -> std::vector<std::wstring> {
        std::vector<std::wstring> args{ argc, L"" };
        for (size_t i{0}; i < argc; ++i) {
            wcin >> args[i];
        }
        return args;
	}

	export void study002() { // my custom command args input getter 
		const std::string prompt{ "cmd> " };
		std::cout << prompt;
        const auto args{ std::move(get_args_from_input_v2(4)) };
        for (const auto& arg : args) {
            cout << arg << "\n";
        }
	}
    export void study002_02() {
        wcout << L"안녕하세요.";
        wcout << L"cmd> ";
        std::wstring input;        
        wcin >> input;
        wcout << input;
	}
    export void study002_03() { // 한글의 wstring, wcin, wcout의 입출력을 해결해줬다. (main 함수 참고)
        cout << "cmd> ";
        const auto args{ std::move(get_args_from_wchar(3)) };
        for (const auto& arg : args) {
            wcout << arg << "\n";
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

        cout << R"(This should be: "Quoted string with \"embedded quotes\".": )" <<
            quoted("Quoted string with \"embedded quotes\".") << endl;

        cout.precision(5);
        cout << 1.23454623 << endl;
	}

    export void study007() {
        cout << "cmd> ";
        string user_input1;
        string user_input2;
        cin >> user_input1 >> user_input2;
        cout << "User input was: " << user_input1 << ", " << user_input2 << endl;
	}

    export void study008() { // p.695
        int user_input;
        cin >> user_input;
        cout << "user input = " << user_input << endl;
	}

    void get_reservation_data() {
        wstring guest_name;
        int party_size;
        cout << "Name and number of guests> ";
        wcin >> guest_name >> party_size;
        wcout << "Thank you, " << guest_name << "." << endl;
        if (party_size > 10) {
            cout << "An extra gratuity will apply." << endl;
        }
	}
    export void study009() {
        get_reservation_data();
	}

    export int study010() { // p.697
        cout << "Enter number on separate lines to add.\n"
            << "Use Ctrl+Z followed by Enter to finish\n";
        int sum{ 0 };

        if (!cin.good()) {
            cerr << "Standard input is in a bad state!" << endl;
            return 1;
        }

        while (!cin.bad()) {
            int number;
            cin >> number;
            if (cin.good()) {
                sum += number;
            } else if (cin.eof()) { break; }
            else if (cin.fail()) {
                cin.clear();
                string badToken;
                cin >> badToken;
                cerr << "WARNING: Bad input encountered: " << badToken << endl;
            }            
        }
        cout << "The sum is " << sum << endl;
        return 0;
	}
    // p.698
    string read_name(istream& stream) {
        string name;
        while (stream) {
            const int next{ stream.get() };
            if (!stream || next == std::char_traits<char>::eof()) break;
            name += static_cast<char>(next);
        }
        return name;
	}
    string read_name_v2(istream& stream) {
        string name;
        char next;
        while (stream.get(next)) {
            if (next == ';') break;
            name += next;
        }
        return name;
	}

    // multi lines user input implement function
    auto read_user_input(std::wistream& stream) {
        std::wstring input;
        wchar_t next;
        while (stream.get(next)) {
	        if (next == L';') break;
            if (next == L'\n') wcout << L"> ";
            input += next;
        }
        input += L';';
        return input;
	}
    export void study011() {
        cout << "input names> ";
        const auto name{ read_name_v2(std::cin) };
        cout << "name = " << name << endl;
	}
    export void study012() {
        cout << "cmd> ";
        const wstring input{ read_user_input(std::wcin) };
        wcout << "user input =\n" << input << endl;
	}
    // p.700
    auto remove_last_ws(std::string& str) -> std::string;

    void get_reservation_data2() {
        string guestName;
        int partySize{ 0 };
        cout << "Name and number of guests> ";
        char ch;
        cin >> noskipws; // 스트림이 공백(ws)을 건너뛰지 말고 일반 문자처럼 취급하게 한다.
        while (cin >> ch) {
            // 만약 숫자라면
	        if (isdigit(ch)) {
                // 스트림을 하나 되돌린 후
                cin.unget();
                if (cin.fail())
                    cout << "unget() failed" << endl;
                break; // 루프를 벗어나서
	        }
            guestName += ch;
        }
        // partySize에 정수를 입력한다.
        if (cin) cin >> partySize;
        if (!cin) {
            cerr << "Error getting party size." << endl;
            return;
        }
        cout << std::format("Thank you '{}', party of {}" , remove_last_ws(guestName), partySize) << endl;
        if (partySize > 10) cout << "An extra gratuity will apply." << endl;
        cin >> skipws; // 공백 무시 설정을 다시 reset한다.
	}
    auto remove_last_ws(std::string& str) -> std::string {
        const auto pos = str.find_last_of(' ');
        const auto last_pos = str.size() - 1;
        cout << std::format("pos = {}, last_pos = {}" , pos , last_pos) << endl;
        if (pos == last_pos) str.erase(last_pos);
        return str;
	}

    export void study013() {
        //get_reservation_data2();
        auto str1{ "test str1 "s };
        auto result{ remove_last_ws(str1) };
        cout << std::format("result1 = |{}|" , result) << endl;
        auto str2{ "test str2"s };
        result = remove_last_ws(str2);
        cout << std::format("result2 = |{}|" , result) << endl;
	}
    export void study014() {
        get_reservation_data2();
    }
    // p.701 putback()
    export void study015() {
        cout << "input> ";
        string input;
    	char c;
        cin >> noskipws;
        while (cin >> c) {
            if (c == 'y') {
                cin.putback('e');
                continue;
            }
            if (c == ';') break;
            input += c;
        }
        cout << "result: \n" << input << endl;
    }
}