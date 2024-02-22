module;
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

    void study001() {
        const auto* person1 = new Person("SeJin"sv, "Bae"sv);
        const auto person3 = std::make_unique<Person>("DeWo"sv, "Lee"sv);
        constexpr size_t book_size{ 3 };
        auto* phoneBook = new Person[book_size];
        phoneBook[0] = Person("SeHee"sv, "Bae"sv);
        phoneBook[1] = *person1;
        phoneBook[2] = *person3;
        for (size_t i{ 0 }; i < book_size; ++i) {
            cout << phoneBook[i].get_first_name() << " " << phoneBook[i].get_last_name() << endl;
        }
        delete[] phoneBook;
        phoneBook = nullptr;
    }

    void study002() {
        auto* person1 = new Person("SeJin"sv, "Bae"sv);
        person1->print_info();
        delete person1;
        auto person2 = std::make_unique<Person>("SeHee"sv, "Bae"sv, "UU");
        person2->print_info();
    }
}