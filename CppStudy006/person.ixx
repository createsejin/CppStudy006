export module person;
import std;

namespace person01
{
    export class Person
    {
        static inline unsigned call_counter{ 0 };
        std::string first_name;
        std::string last_name;
    public:
        Person();
        ~Person();
        Person(const Person& person);
        Person& operator=(const Person& rhs);
        Person(std::string_view first_name, std::string_view last_name);
        [[nodiscard]] auto get_first_name() -> std::string&;
        void set_first_name(std::string_view first_name);
        [[nodiscard]] auto get_last_name() -> std::string&;
        void set_last_name(std::string_view last_name);
    };

    export void study001();
}