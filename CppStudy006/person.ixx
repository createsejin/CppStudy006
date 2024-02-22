export module person;
import std;

namespace person01
{
    export class Person
    {
        static inline unsigned call_counter{ 0 };
        std::string first_name;
        std::string last_name;
        std::string initial;
        void make_initial();
    public:
        Person();
        ~Person();
        Person(const Person& person) = default;
        Person& operator=(const Person& rhs) = default;
        Person(Person&& rhs) noexcept;
        Person& operator=(Person&& rhs) noexcept;
        Person(std::string_view first_name, std::string_view last_name);
        Person(std::string_view first_name, std::string_view last_name, std::string_view initial);
        [[nodiscard]] auto get_first_name() -> std::string&;
        void set_first_name(std::string_view first_name);
        [[nodiscard]] auto get_last_name() -> std::string&;
        void set_last_name(std::string_view last_name);
        [[nodiscard]] auto get_initial() -> std::string&;
        void set_initial(std::string_view initial);
        void print_info() const;
        void swap(Person& other) noexcept;
        [[nodiscard]] std::partial_ordering operator<=>(const Person& rhs) const = default;
    };
    void swap(Person& first, Person& second) noexcept;

    export void study001();
    export void study002();
}