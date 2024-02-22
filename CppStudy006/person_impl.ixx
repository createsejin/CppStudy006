export module person_impl;
import std;

namespace person01 {
	export class Impl {
		static inline unsigned call_counter{ 0 };
		std::string first_name;
		std::string last_name;
		std::string initial;
		void make_initial();
	public:
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
		bool operator==(const Impl& rhs);
		bool operator!=(const Impl& rhs);
		bool operator<(const Impl& rhs);
		bool operator>=(const Impl& rhs);
		bool operator>(const Impl& rhs);
		bool operator<=(const Impl& rhs);
	};
	void swap(Impl& first, Impl& second) noexcept;
}