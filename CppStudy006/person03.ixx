export module person03;
import std;

using namespace std;
namespace person03
{
	class Person
	{
		std::string first_name_;
		std::string last_name_;
	public:
		Person(std::string_view first_name, std::string_view last_name);
		[[nodiscard]] auto get_first_name() const -> const std::string& { return first_name_; }
		[[nodiscard]] auto get_last_name() const -> const std::string& { return last_name_; }
	};
}