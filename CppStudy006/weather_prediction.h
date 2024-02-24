#pragma once
import std;

namespace weather_prediction01
{
	class WeatherPrediction
	{
		double current_temp_fahrenheit_{ 0 };
		double distance_from_mars_{ 0 };
	public:
		// virtual 소멸자
		WeatherPrediction() = default;
		virtual ~WeatherPrediction() = default;
		WeatherPrediction(const WeatherPrediction& src) = default;
		WeatherPrediction& operator=(const WeatherPrediction& rhs) = default;
		WeatherPrediction(WeatherPrediction&& src) = default;
		WeatherPrediction& operator=(WeatherPrediction&& rhs) = default;
		// 현재 온도를 화씨 단위로 설정한다.
		virtual void set_current_temp_fahrenheit(double temp);
		// 목성과 화성 사이의 현재 거리를 설정한다.
		virtual void set_position_of_jupiter(double distance_from_mars);
		// 내일 온도에 대한 예측값을 가져온다.
		[[nodiscard]] virtual auto get_tomorrow_temp_fahrenheit() const -> bool;
		// 내일 비가 올 확률을 가져온다. 1-> 확실히 비가옴 0-> 비가 안옴
		[[nodiscard]] virtual auto get_chance_of_rain() const -> double;
		// 결과 출력
		virtual void show_result() const;
		// 현재 온도를 스트링값으로 리턴한다.
		[[nodiscard]] virtual auto get_temperature() const -> std::string;
	};
}
