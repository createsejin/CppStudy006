export module person;
import std;

namespace person01
{
    inline unsigned call_counter{ 0 };

    export class Person
    {
        std::string first_name_;
        std::string last_name_;
        std::string initial_;
        [[nodiscard]] std::string make_initial(std::string_view first_name, std::string_view last_name) const;
        class Impl;
        std::unique_ptr<Impl> impl_;
        friend void swap(Impl& first, Impl& second) noexcept;
    public:
        Person();
        ~Person();
        Person(const Person& src);
        Person& operator=(const Person& rhs);
        Person(Person&& rhs) noexcept;
        Person& operator=(Person&& rhs) noexcept;
        Person(std::string_view first_name, std::string_view last_name);
        Person(std::string_view first_name, std::string_view last_name, std::string_view initial);
        [[nodiscard]] auto get_first_name() const->std::string&;
        void set_first_name(std::string_view first_name) const;
        [[nodiscard]] auto get_last_name() const->std::string&;
        void set_last_name(std::string_view last_name) const;
        [[nodiscard]] auto get_initial() const->std::string&;
        void set_initial(std::string_view initial) const;
        void print_info() const;
        void swap(const Person& other) const noexcept;
        //[[nodiscard]] std::weak_ordering operator<=>(const Person& rhs) const = default;
        bool operator==(const Person& rhs) const;
        bool operator!=(const Person& rhs) const;
        bool operator<(const Person& rhs) const;
        bool operator>=(const Person& rhs) const;
        bool operator>(const Person& rhs) const;
        bool operator<=(const Person& rhs) const;
    };

    void swap(Person& first, Person& second) noexcept;

    export void study001();
    export void study002();
}