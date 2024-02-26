module;
#include <iostream>
module person;
using namespace std;
namespace person01
{
    unsigned call_counter {0};
    //------------------------------------Person::Impl--------------------------------------//
    class Person::Impl {
        std::string first_name_;
        std::string last_name_;
        std::string initial_;
    public:
        [[nodiscard]] static auto make_initial(std::string_view first_name,
            std::string_view last_name) -> std::string;
        Impl();
        ~Impl();
        Impl(const Impl& impl) = default;
        Impl& operator=(const Impl& rhs) = default;
        Impl(Impl&& rhs) noexcept;
        Impl& operator=(Impl&& rhs) noexcept;
        Impl(std::string_view first_name, std::string_view last_name);
        Impl(std::string_view first_name, std::string_view last_name, std::string_view initial);
        [[nodiscard]] auto get_first_name() -> std::string&;
        void set_first_name(std::string_view first_name);
        [[nodiscard]] auto get_last_name() -> std::string&;
        void set_last_name(std::string_view last_name);
        [[nodiscard]] auto get_initial() -> std::string&;
        void set_initial(std::string_view initial);
        void print_info() const;
        void swap(Impl& other) noexcept;
        bool operator==(const Impl& rhs) const;
        bool operator!=(const Impl& rhs) const;
        bool operator<(const Impl& rhs) const;
        bool operator>=(const Impl& rhs) const;
        bool operator>(const Impl& rhs) const;
        bool operator<=(const Impl& rhs) const;
    };
    //------------------------------------Person::Impl--------------------------------------//

    auto Person::Impl::make_initial(const std::string_view first_name,
        const std::string_view last_name) -> std::string {
        const std::string first_initial{ *first_name.begin() };
        const std::string last_initial{ *last_name.begin() };
        return first_initial + last_initial;
    }
    Person::Impl::Impl() {
        cout << "Calling Impl Default Constructor: " << call_counter++ << " ";
        print_info();
    }
    Person::Impl::~Impl() {
        cout << "Calling Impl Destructor: " << call_counter++ << " ";
        print_info();
    }

    Person::Impl::Impl(const std::string_view first_name, const std::string_view last_name)
        : Impl(first_name, last_name, make_initial(first_name, last_name))
    {
        cout << "Calling Impl parameters 2 Constructor: " << call_counter++ << " ";
        print_info();
    }
    Person::Impl::Impl(const std::string_view first_name, const std::string_view last_name,
        const std::string_view initial)
        : first_name_{ first_name }, last_name_{ last_name }, initial_{ initial }
    {
        cout << "Calling Impl parameters 3 Constructor: " << call_counter++ << " ";
        print_info();
    }
    auto Person::Impl::get_first_name() -> std::string& { return first_name_; }

    void Person::Impl::set_first_name(const std::string_view first_name) {
        this->first_name_ = first_name;
    }
    auto Person::Impl::get_last_name() -> std::string& { return last_name_; }
    void Person::Impl::set_last_name(const std::string_view last_name) {
        this->last_name_ = last_name;
    }
    auto Person::Impl::get_initial() -> std::string& { return initial_; }
    void Person::Impl::set_initial(const std::string_view initial) { this->initial_ = initial; }

    void Person::Impl::print_info() const {
        cout << initial_ << ": " << first_name_ << " " << last_name_ << endl;
    }

    void Person::Impl::swap(Impl& other) noexcept {
        std::swap(this->first_name_, other.first_name_);
        std::swap(this->last_name_, other.last_name_);
        std::swap(this->initial_, other.initial_);
    }

    bool Person::Impl::operator==(const Impl& rhs) const {
        return this->first_name_ == rhs.first_name_ &&
            this->last_name_ == rhs.last_name_ &&
            this->initial_ == rhs.initial_;
    }

    bool Person::Impl::operator!=(const Impl& rhs) const
    {
        return !operator==(rhs);
    }

    bool Person::Impl::operator<(const Impl& rhs) const
    {
        if (this->first_name_ != rhs.first_name_) return this->first_name_ < rhs.first_name_;
        if (this->last_name_ != rhs.last_name_) return this->last_name_ < rhs.last_name_;
        return this->initial_ < rhs.initial_;
    }

    bool Person::Impl::operator>=(const Impl& rhs) const
    {
        return !(*this < rhs);
    }

    bool Person::Impl::operator>(const Impl& rhs) const {
        if (this->first_name_ != rhs.first_name_) return this->first_name_ > rhs.first_name_;
        if (this->last_name_ != rhs.last_name_) return this->last_name_ > rhs.last_name_;
        return this->initial_ > rhs.initial_;
    }

    bool Person::Impl::operator<=(const Impl& rhs) const {
        return !(*this > rhs);
    }

    void swap(Person::Impl& first, Person::Impl& second) noexcept {
        first.swap(second);
    }

    Person::Impl& Person::Impl::operator=(Impl&& rhs) noexcept
    {
        person01::swap(*this, rhs);
        return *this;
    }

    Person::Impl::Impl(Impl&& rhs) noexcept {
        person01::swap(*this, rhs);
    }
    //------------------------------------Person-------------------------------------------//
    auto Person::make_initial(const std::string_view first_name,
        const std::string_view last_name) const -> std::string {
        return impl_->make_initial(first_name, last_name);
    }
    Person::Person() {
        impl_ = std::make_unique<Impl>();
        cout << "Calling Person Default Constructor: " << call_counter++ << " ";
        print_info();
    }
    Person::~Person() {
        cout << "Calling Person Destructor: " << call_counter++ << " ";
        print_info();
    }
    Person::Person(const Person& src) { // 복제 생성자
        *impl_ = *src.impl_;
    }

    Person& Person::operator=(const Person& rhs) { // 복제 대입 연산자
        *impl_ = *rhs.impl_;
        return *this;
    }

    Person::Person(const std::string_view first_name, const std::string_view last_name)
        : Person(first_name, last_name, make_initial(first_name, last_name))
    {
        cout << "Calling Person parameters 2 Constructor: " << call_counter++ << " ";
        print_info();
    }
    Person::Person(std::string_view first_name, std::string_view last_name, std::string_view initial)
    {
        impl_ = std::make_unique<Impl>(first_name, last_name, initial);
        cout << "Calling Person parameters 3 Constructor: " << call_counter++ << " ";
        print_info();
    }
    auto Person::get_first_name() const -> std::string& { return impl_->get_first_name(); }

    void Person::set_first_name(const std::string_view first_name) const {
        impl_->set_first_name(first_name);
    }
    auto Person::get_last_name() const -> std::string& { return impl_->get_last_name(); }
    void Person::set_last_name(const std::string_view last_name) const {
        impl_->set_last_name(last_name);
    }
    auto Person::get_initial() const -> std::string& { return impl_->get_initial(); }
    auto Person::set_initial(const std::string_view initial) const -> void { impl_->set_initial(initial); }

    void Person::print_info() const {
        impl_->print_info();
    }

    void Person::swap(const Person& other) const noexcept {        
        impl_->swap(*other.impl_);
    }

    bool Person::operator==(const Person& rhs) const {
        return *impl_ == *rhs.impl_;
    }

    bool Person::operator!=(const Person& rhs) const {
        return *impl_ != *rhs.impl_;
    }

    bool Person::operator<(const Person& rhs) const {
        return *impl_ < *rhs.impl_;
    }

    bool Person::operator>=(const Person& rhs) const {
        return *impl_ >= *rhs.impl_;
    }

    bool Person::operator>(const Person& rhs) const {
        return *impl_ > *rhs.impl_;
    }

    bool Person::operator<=(const Person& rhs) const {
        return *impl_ <= *rhs.impl_;
    }

    // 이걸 어떻게 할까..
    void swap(const Person& first, const Person& second) noexcept {
        first.swap(second);
    }

    Person& Person::operator=(Person&& rhs) noexcept
    {
        *this->impl_ = std::move(*rhs.impl_);
        return *this;
    }

    Person::Person(Person&& rhs) noexcept {
        *this->impl_ = std::move(*rhs.impl_);
    }

    [[maybe_unused]]
    void compare_result(const std::weak_ordering result)
    {
	    if (is_lt(result)) cout << "less" << endl;
	    if (is_gt(result)) cout << "great" << endl;
	    if (is_eq(result)) cout << "equal" << endl;
    }

    void study001() { // p.503
        auto* person1 = new Person("SeJin"sv, "Bae"sv);
        const auto person3 = std::make_unique<Person>("DeWo"sv, "Lee"sv);
        auto* person4 = new Person("SeAum"sv, "Bae"sv);
        constexpr size_t book_size{ 6 };
        auto** phoneBook{ new Person * [book_size] };
        // ReSharper disable once CppDFAMemoryLeak
        phoneBook[0] = new Person("SeHee"sv, "Bae"sv);
        phoneBook[1] = person1;
        phoneBook[2] = person3.get();
        // ReSharper disable once CppDFAMemoryLeak
        phoneBook[3] = new Person("SeAum"sv, "Kim"sv, "SV"sv);
        phoneBook[4] = person4;
        // ReSharper disable once CppDFAMemoryLeak
        phoneBook[5] = new Person("SeJin"sv, "Bae"sv, "SV");
        constexpr int dynamic_array_index[]{ 0, 3, 5 };
        constexpr size_t dynamic_array_size{ 3 };
        for (size_t i{ 0 }; i < book_size; ++i) {
            phoneBook[i]->print_info();
        }
        /*auto result1 = *person1 <=> *phoneBook[0];
        compare_result(result1);
        auto result2 = *person1 <=> *phoneBook[3];
        compare_result(result2);
        auto result3 = *phoneBook[3] <=> *phoneBook[4];
        compare_result(result3);*/        
        if (*person4 < *phoneBook[3]) { // format을 쓰면 여기 VS에서는 인텔리센스가 먹통이 되버린다..
            // VS에서는 그냥 cout을 쓰는게 속 편하다. 
            //cout << person4->get_first_name() << " " << person4->get_last_name()
            //    << " is less than "
            //    << phoneBook[3]->get_first_name() << " " << phoneBook[3]->get_last_name() << endl;
            cout << format("{0} {1} is less than {2} {3}",
                person4->get_first_name(), person4->get_last_name(),
                phoneBook[3]->get_first_name(), phoneBook[3]->get_last_name()) << endl;
        }
        if (*person1 > *person4) {
            cout << person1->get_first_name() << " " << person1->get_last_name()
                << " is greater than "
                << person4->get_first_name() << " " << person4->get_last_name() << endl;
        }
        if (*person1 < *phoneBook[5]) {
            cout << person1->get_first_name() << " " << person1->get_last_name()
                << " is less than "
                << phoneBook[5]->get_first_name() << " " << phoneBook[5]->get_last_name() << endl;
        }

        for (size_t i{ 0 }; i < dynamic_array_size; ++i) {
            delete phoneBook[dynamic_array_index[i]];
        }

        delete person1;
        person1 = nullptr;
        delete person4;
        person4 = nullptr;

        delete[] phoneBook;
        phoneBook = nullptr;
    }

    void study002() {
        const auto* person1 = new Person("SeJin"sv, "Bae"sv);
        person1->print_info();
        delete person1;
        const auto person2 = std::make_unique<Person>("SeHee"sv, "Bae"sv, "UU"sv);
        person2->print_info();
    }
}