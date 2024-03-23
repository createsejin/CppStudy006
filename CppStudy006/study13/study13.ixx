module;
#include <cstring>
#include <stdio.h>
#include <time.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <format>
#include <ranges>
#include <filesystem>

export module study13;

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
    auto read_user_input(std::wistream& stream, const bool semicolon = false) -> std::wstring {
        std::wstring input;
        wchar_t next;
        while (stream.get(next)) {
	        if (next == L';') break;
            if (next == L'\n') wcout << L"> ";
            input += next;
        }
        if (semicolon) input += L';';
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
                // y가 나오면 그 자리에 e로 putback 해놓는다.
                cin.putback('e');
                continue;
            }
            if (c == ';') break;
            input += c;
        }
        cout << "result: \n" << input << endl;
    }
    // peek()
    void get_reservation_data3() {
        string guest_name;
        int party_size{ 0 };
        cout << "input Name and party size> ";
        cin >> noskipws;
        while (true) {
            char ch{ static_cast<char>(cin.peek()) };
            if (!cin) break;
            if (std::isdigit(ch)) break;
            cin >> ch;
            if (!cin) break;
            guest_name += ch;
        }
        if (cin) cin >> party_size;
        if (!cin) {
            cerr << "Error getting party size." << endl;
            return;
        }
        cout << std::format("Thank you '{}', party of {}" , 
            remove_last_ws(guest_name) , party_size) << endl;
        if (party_size > 10) cout << "An extra gratuity will apply." << endl;
        cin >> skipws;
    }
    export void study016() {
        get_reservation_data3();
    }
    // test to convert from multi lines user input to args vector
    export void study017() {
        cout << "cmd> ";
        const wstring user_input{ read_user_input(std::wcin) };
        wcout << "user input =\n" << user_input << endl;
    }
    // p.702 getline() 부터
    export void study018() {
        constexpr unsigned kBufferSize { 50 };
        char buffer[kBufferSize] { 0 };
        cin.getline(buffer, kBufferSize);

        string myString;
        std::getline(cin, myString);
    }
    export void study019() {
        cout << "Enter multiple lines of text.\n"
            << "Use an ; character to signal the end of the text.\n> ";
        string myString;
        std::getline(cin, myString, ';');
        cout << std::format("Read text: \"{}\"", myString) << endl;
    }
    export void study020() {
        cin.imbue(locale { "en_US.utf8" });
        int i;
        cin >> i;
        cout << i << endl;
    }
}
namespace study13_002
{
    class Muffin
    {
    public:
        virtual ~Muffin() = default;

        auto getDesription() const -> const string& { return description_; }
        void setDescription(const string_view description) {
            description_ = description;
        }
        auto getSize() const -> int { return size_; }
        void setSize(const int size) { size_ = size; }

        auto hasChocolateChips() const -> bool { return hasChocolateChips_; }
        void setHasChocolateChips(const bool hasChips) { hasChocolateChips_ = hasChips; }
    private:
        string description_;
        int size_ { 0 };
        bool hasChocolateChips_ { false };
    };
    
    export void study021() {
        cout << "Enter tokens.\n";
        ostringstream outStream;
        while (cin) {
            string nextToken;
            cout << "Next token: ";
            cin >> nextToken;
            if (!cin || nextToken == "done") break;
            outStream << nextToken << "\t";
        }
        cout << "The end result is: " << outStream.str();
    }
    std::optional<Muffin> createMuffin(istringstream& stream) {
        Muffin muffin;
        // Description size chips

        string description;
        int size;
        bool hasChips;

        stream >> description >> size >> boolalpha >> hasChips;
        if (stream) {
            muffin.setSize(size);
            muffin.setDescription(description);
            muffin.setHasChocolateChips(hasChips);
            return muffin;
        }
        else return std::nullopt;
    }
}
namespace study13_003 // p.708 파일 스트림
{
    export int study022(const int argc, char* argv[]) {
        ofstream outFile ("test.txt", ios_base::trunc );
        if (!outFile.good()) {
            cerr << "Error while opening file!" << endl;
            return -1;
        }
        outFile << "There were" << argc << " arguments to this program." << endl;
        outFile << "They are: ";
        for (int i { 1 }; i < argc; ++i) {
            outFile << std::format("{} ", argv[i]);
        }
        return 0;
    }
    export void study023() {
        ofstream fout { "test.out", ios_base::trunc };
        if (!fout) {
            cerr << "Error opening test.out for writing" << endl;
        }

        // 1. "54321" 스트링을 파일에 출력한다.
        fout << "54321";

        // 2. 현재 위치가 5인지 확인한다.
        streampos curPos { fout.tellp() };
        if (5 == curPos) {
            cout << "Test passed: Currently at position 5" << endl;
        }
        else {
            cout << "Test failed: Not at position 5" << endl;
        }

        // 3. 스트림의 현재 위치를 2로 옮긴다.
        fout.seekp(2, ios_base::beg);

        // 4. 위치 2에 0을 쓰고 스트림을 닫는다.
        fout << 0;
        fout.close();

        // 5. test.out에 대한 입력 스트림을 연다.
        ifstream fin { "test.out" };
        if (!fin) {
            cerr << "Error opening test.out for reading" << endl;
        }

        // 6. 첫번째 토큰을 정수 타입의 값으로 읽는다.
        int testVal;
        fin >> testVal;
        if (!fin) {
            cerr << "Error reading from file" << endl;
        }

        // 7. 읽은 값이 54021인지 확인한다.
        const int expected { 54021 };
        if (testVal == expected) {
            cout << format("Test passed: Value is {}", expected) << endl;
        }
        else {
            cout << format("Test failed: Value is not {} (it was {})", expected, testVal) << endl;
        }
    }
    export void study024() {
        ifstream inFile { "input.txt" };
        ofstream outFile { "output.txt" };
        // inFile과 outFile을 연결한다.
        inFile.tie(&outFile);
        // outFile에 텍스트를 쓴다. std::endl이 입력되기 전까지는 내보내지 않는다.
        outFile << "Hello there!";
        // outFile을 아직 내보내지 않은 상태다.
        // inFile에서 텍스트를 읽는다. 그러면 outFile에 대해 flush()가 호출된다.
        string nextToken;
        inFile >> nextToken;
        // 이제 outFile이 내보내졌다.
        cout << nextToken << endl;
    }

    bool changeNumberForID(const string_view filename, const int id, const string_view newNumber) {
        fstream ioData { filename.data() };
        if (!ioData) {
            cerr << "Error while opening file " << filename << endl;
            return false;
        }
        // 파일을 끝까지 반복한다.
        while (ioData) {
            // 다음 ID를 읽는다. 이 위치는 나중에 tellg의 위치가 된다.
            int idRead;
            ioData >> idRead;
            if (!ioData) break;

            // 현재 레코드가 수정할 대상인지 확인한다.
            if (idRead == id) {
                // 쓰기 위치를 현재 읽기 위치로 이동한다.
                ioData.seekp(ioData.tellg());
                // 한 칸 띄운 뒤 새 번호를 쓴다.
                ioData << " " << newNumber;
                break;
            }

            // 현재 위치에서 숫자를 읽어서 스트림의 위치를 다음 레코드로 이동한다.
            string number;
            ioData >> number;
        }
        return true;
    }
    export void study025() {
        string filename { "phone.txt" };
        changeNumberForID(filename, 253, "010-0232-0434");
    }
}
