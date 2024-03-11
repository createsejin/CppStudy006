export module key_value_pair01:string;
import :main;
import std;

namespace key_value_pair01
{	// p.680
	export template<>
	class KeyValuePair<const char*, const char*>
	{
		std::string key_;
		std::string value_;
	public:
		KeyValuePair(const char* key, const char* value) {
			key_ = std::move(key);
			value_ = std::move(value);
		}
		[[nodiscard]] std::string& get_key() { return key_; }
		[[nodiscard]] const std::string& get_key() const { return key_; }
		void set_key(const char* key) { key_ = key; }
		[[nodiscard]] std::string& get_value() { return value_; }
		[[nodiscard]] const std::string& get_value() const { return value_; }
		void set_value(const char* value) { value_ = value; }
	};
}
