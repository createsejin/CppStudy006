module;
#include "weather_prediction.h"
export module my_weather_prediction;

using namespace std;
namespace weather_prediction01
{
	export class MyWeatherPrediction : public WeatherPrediction
	{
		static auto convert_celsius_to_fahrenheit(double celsius) -> double;
		static auto convert_fahrenheit_to_celsius(double fahrenheit) -> double;
	public:
		virtual void set_current_temp_celsius(double temp);
		[[nodiscard]] virtual auto get_tomorrow_temp_celsius() const -> double;
	};

	auto MyWeatherPrediction::convert_celsius_to_fahrenheit(const double celsius) -> double
	{
		return celsius * (9.0 / 5.0) + 32;
	}
	auto MyWeatherPrediction::convert_fahrenheit_to_celsius(const double fahrenheit) -> double
	{
		return (5 / 9) * (fahrenheit - 32);
	}

	void MyWeatherPrediction::set_current_temp_celsius(const double temp)
	{
		const auto fahrenheit_temp{ convert_celsius_to_fahrenheit(temp) };
		set_current_temp_fahrenheit(fahrenheit_temp);
	}

	auto MyWeatherPrediction::get_tomorrow_temp_celsius() const -> double
	{
		const auto fahrenheit_temp{ get_tomorrow_temp_fahrenheit() };
		return convert_fahrenheit_to_celsius(fahrenheit_temp);
	}

}
