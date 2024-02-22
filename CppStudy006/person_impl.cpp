module person_impl;
import std;
using namespace std;

namespace person01 {
    void Impl::make_initial() {
        std::string first_initial{ *first_name.begin() };
        std::string last_initial{ *last_name.begin() };
        initial = first_initial + last_initial;
    }
    Impl::Impl() {
        call_counter++;
        cout << "Calling Default Constructor: " << call_counter << endl;
    }
    Impl::~Impl() {
        call_counter++;
        cout << "Calling Destructor: " << call_counter << endl;
    }

    Impl::Impl(const std::string_view first_name, const std::string_view last_name)
        : Impl(first_name, last_name, "")
    {
        call_counter++;
        cout << "Calling parameters 2 Constructor: " << call_counter << endl;
        make_initial();
    }
    Impl::Impl(std::string_view first_name, std::string_view last_name, std::string_view initial)
        : first_name{ first_name }, last_name{ last_name }, initial{ initial }
    {
        call_counter++;
        cout << "Calling parameters 3 Constructor: " << call_counter << endl;
    }
    auto Impl::get_first_name() -> std::string& { return first_name; }

    void Impl::set_first_name(const std::string_view first_name) {
        this->first_name = first_name;
    }
    auto Impl::get_last_name() -> std::string& { return last_name; }
    void Impl::set_last_name(const std::string_view last_name) {
        this->last_name = last_name;
    }
    auto Impl::get_initial() -> std::string& { return initial; }
    void Impl::set_initial(std::string_view initial) { this->initial = initial; }

    void Impl::print_info() const {
        cout << initial << ": " << first_name << " " << last_name << endl;
    }

    void Impl::swap(Impl& other) noexcept {
        std::swap(this->first_name, other.first_name);
        std::swap(this->last_name, other.last_name);
        std::swap(this->initial, other.initial);
    }

    bool Impl::operator==(const Impl& rhs)
    {
        return this->first_name == rhs.first_name &&
            this->last_name == rhs.last_name &&
            this->initial == rhs.initial;
    }

    bool Impl::operator!=(const Impl& rhs)
    {
        return !operator==(rhs);
    }

    bool Impl::operator<(const Impl& rhs)
    {
        if (this->first_name != rhs.first_name) return this->first_name < rhs.first_name;
        if (this->last_name != rhs.last_name) return this->last_name < rhs.last_name;
        return this->initial < rhs.initial;
    }

    bool Impl::operator>=(const Impl& rhs)
    {
        return !(*this < rhs);
    }

    bool Impl::operator>(const Impl& rhs)
    {
        if (this->first_name != rhs.first_name) return this->first_name > rhs.first_name;
        if (this->last_name != rhs.last_name) return this->last_name > rhs.last_name;
        return this->initial > rhs.initial;
    }

    bool Impl::operator<=(const Impl& rhs)
    {
        return !(*this > rhs);
    }

    void swap(Impl& first, Impl& second) noexcept {
        first.swap(second);
    }

    Impl& Impl::operator=(Impl&& rhs) noexcept
    {
        person01::swap(*this, rhs);
        return *this;
    }

    Impl::Impl(Impl&& rhs) noexcept {
        person01::swap(*this, rhs);
    }
}