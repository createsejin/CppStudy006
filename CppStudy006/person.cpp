module person;

using namespace std;
namespace person01
{
    Person::Person() {
        call_counter++;
        cout << std::format("Calling Default Constructor: {}", call_counter) << endl;
    }
    Person::~Person() {
        call_counter++;
        cout << std::format("Calling Destructor: {}", call_counter) << endl;
    }
    Person::Person(const Person& person)
        : Person(person.first_name, person.last_name)
    {
    }
    Person& Person::operator=(const Person& rhs) {
        if (this == &rhs) return *this;
        first_name = rhs.first_name;
        last_name = rhs.last_name;
        return *this;
    }
    Person::Person(const std::string_view first_name, const std::string_view last_name)
        : first_name(first_name), last_name(last_name)
    {
        call_counter++;
        cout << std::format("Calling parameters Constructor: {}", call_counter) << endl;
    }
    auto Person::get_first_name() -> std::string& { return first_name; }

    void Person::set_first_name(const std::string_view first_name) {
        this->first_name = first_name;
    }
    auto Person::get_last_name() -> std::string& { return last_name; }
    void Person::set_last_name(const std::string_view last_name) {
        this->last_name = last_name;
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
}