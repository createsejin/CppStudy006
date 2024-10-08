export module person02;
import std;

export namespace hr
{   // p.587 ��������
    class Person
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
        virtual ~Person();
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
        virtual void print_info() const;
        virtual auto to_string() const->std::string;
        void swap(const Person& other) const noexcept;
        //[[nodiscard]] std::weak_ordering operator<=>(const Person& rhs) const = default;
        bool operator==(const Person& rhs) const;
        bool operator!=(const Person& rhs) const;
        bool operator<(const Person& rhs) const;
        bool operator>=(const Person& rhs) const;
        bool operator>(const Person& rhs) const;
        bool operator<=(const Person& rhs) const;
    };

    class Manager;
    class Director;

    class Employee : public Person
    {
        unsigned int employee_id_{ 0 };
    public:
        Employee() = default;
        ~Employee() override = default;
        Employee(const Employee& src);
        Employee& operator=(const Employee& rhs) = default;
        Employee(Employee&& src) noexcept = default;
        Employee& operator=(Employee&& rhs) noexcept = default;
        Employee(std::string_view first_name, std::string_view last_name, unsigned int id);
        Employee(std::string_view first_name, std::string_view last_name, std::string_view initial, unsigned int id);

        [[nodiscard]] auto get_id() const -> unsigned int { return employee_id_; }
        void set_id(const unsigned int value) { employee_id_ = value; }

        void print_info() const override;
        auto to_string() const->std::string override;
    };

    class Manager final : public Employee
    {
    public:
        using Employee::Employee;
        explicit Manager(const Employee& employee);
        explicit Manager(Employee&& employee);
        auto to_string() const->std::string override;
        
    };
    class Director final : public Employee
    {
    public:
        using Employee::Employee;
        explicit Director(const Employee& employee);
        auto to_string() const -> std::string override;
    };

    void swap(Person& first, Person& second) noexcept;
}
