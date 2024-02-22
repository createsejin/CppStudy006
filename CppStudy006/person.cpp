module person;
using namespace std;
namespace person01
{
    void Person::make_initial() {
        std::string first_initial{ *first_name.begin() };
        std::string last_initial{ *last_name.begin() };
        initial = first_initial + last_initial;
    }
    Person::Person() {
        call_counter++;
        cout << std::format("Calling Default Constructor: {}", call_counter) << endl;
    }
    Person::~Person() {
        call_counter++;
        cout << std::format("Calling Destructor: {}", call_counter) << endl;
    }
    
    Person::Person(const std::string_view first_name, const std::string_view last_name)
        : Person(first_name, last_name, "")
    {
        call_counter++;
        cout << std::format("Calling parameters 2 Constructor: {}", call_counter) << endl;
        make_initial();
    }
    Person::Person(std::string_view first_name, std::string_view last_name, std::string_view initial)
        : first_name{first_name}, last_name{last_name}, initial{initial}
    {
        call_counter++;
        cout << std::format("Calling parameters 3 Constructor: {}", call_counter) << endl;
    }
    auto Person::get_first_name() -> std::string& { return first_name; }

    void Person::set_first_name(const std::string_view first_name) {
        this->first_name = first_name;
    }
    auto Person::get_last_name() -> std::string& { return last_name; }
    void Person::set_last_name(const std::string_view last_name) {
        this->last_name = last_name;
    }
    auto Person::get_initial() -> std::string& { return initial; }
    void Person::set_initial(std::string_view initial) { this->initial = initial; }

    void Person::print_info() const {
        cout << initial << ": " << first_name << " " << last_name << endl;
    }

    void Person::swap(Person& other) noexcept {
        std::swap(this->first_name, other.first_name);
        std::swap(this->last_name, other.last_name);
        std::swap(this->initial, other.initial);
    }

    bool Person::operator==(const Person& rhs)
    {
        return this->first_name == rhs.first_name &&
            this->last_name == rhs.last_name &&
            this->initial == rhs.initial;
    }

    bool Person::operator!=(const Person& rhs)
    {
        return !operator==(rhs);
    }

    bool Person::operator<(const Person& rhs)
    {        
        if (this->first_name != rhs.first_name) return this->first_name < rhs.first_name;
        if (this->last_name != rhs.last_name) return this->last_name < rhs.last_name;
        return this->initial < rhs.initial;
    }

    bool Person::operator>=(const Person& rhs)
    {
        return !(*this < rhs);
    }

    bool Person::operator>(const Person& rhs)
    {
        if (this->first_name != rhs.first_name) return this->first_name > rhs.first_name;
        if (this->last_name != rhs.last_name) return this->last_name > rhs.last_name;
        return this->initial > rhs.initial;
    }

    bool Person::operator<=(const Person& rhs)
    {
        return !(*this > rhs);
    }

    void swap(Person& first, Person& second) noexcept {
        first.swap(second);
    }

    Person& Person::operator=(Person&& rhs) noexcept
    {
        person01::swap(*this, rhs);
        return *this;
    }

    Person::Person(Person&& rhs) noexcept {
        person01::swap(*this, rhs);
    }

    static void compare_result(std::weak_ordering result) {
        if (is_lt(result)) cout << "less" << endl;
        if (is_gt(result)) cout << "great" << endl;
        if (is_eq(result)) cout << "equal" << endl;
    }

    void study001() { // p.503 연습문제
        auto* person1 = new Person("SeJin"sv, "Bae"sv);
        const auto person3 = std::make_unique<Person>("DeWo"sv, "Lee"sv);
        auto* person4 = new Person("SeAum"sv, "Bae"sv);
        constexpr size_t book_size{ 6 };
        auto** phoneBook = new Person * [book_size];
        phoneBook[0] = new Person("SeHee"sv, "Bae"sv);
        phoneBook[1] = person1;
        phoneBook[2] = person3.get();
        phoneBook[3] = new Person("SeAum"sv, "Kim"sv, "SV"sv);
        phoneBook[4] = person4;
        phoneBook[5] = new Person("SeJin"sv, "Bae"sv, "SV");
        for (size_t i{ 0 }; i < book_size; ++i) {
            phoneBook[i]->print_info();
        }
        /*auto result1 = *person1 <=> *phoneBook[0];
        compare_result(result1);
        auto result2 = *person1 <=> *phoneBook[3];
        compare_result(result2);
        auto result3 = *phoneBook[3] <=> *phoneBook[4];
        compare_result(result3);*/

        if (*person4 < *phoneBook[3]) cout << std::format("{0} {1} is less than {2} {3}", 
            person4->get_first_name(), person4->get_last_name(), 
            phoneBook[3]->get_first_name(), phoneBook[3]->get_last_name()) << endl;
        if (*person1 > *person4) cout << std::format("{0} {1} is greater than {2} {3}",
            person1->get_first_name(), person1->get_last_name(),
            person4->get_first_name(), person4->get_last_name()) << endl;
        if (*person1 < *phoneBook[5]) cout << std::format("{0} {1} is less than {2} {3}",
            person1->get_first_name(), person1->get_last_name(),
            phoneBook[5]->get_first_name(), phoneBook[5]->get_last_name()) << endl;

        for (size_t i{ 0 }; i < book_size; ++i) {
            if (i != 2) delete phoneBook[i];
        }
        delete[] phoneBook;
        phoneBook = nullptr;
    }

    void study002() {
        auto* person1 = new Person("SeJin"sv, "Bae"sv);
        person1->print_info();
        delete person1;
        auto person2 = std::make_unique<Person>("SeHee"sv, "Bae"sv, "UU"sv);
        person2->print_info();
    }
}