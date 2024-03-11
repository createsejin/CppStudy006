export module key_value_pair02;
#include <concepts>

namespace key_value_pair02
{
	export template<typename T1, typename T2>
	requires std::integral<T1> && std::floating_point<T2>
		class KeyValuePair
	{
		T1 key_;
		T2 value_;
	public:
		KeyValuePair(const T1& key, const T2& value)
			: key_(key), value_(value) {}
		[[nodiscard]] T1 get_key() const { return key_; }
		void set_key(const T1& key) { key_ = key; }
		[[nodiscard]] T2 get_value() const { return value_; }
		void set_value(const T2& value) { value_ = value; }
	};
}
