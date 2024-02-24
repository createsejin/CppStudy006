#pragma once
import std;

namespace weather_prediction01
{
	class WeatherPrediction
	{
		double current_temp_fahrenheit_{ 0 };
		double distance_from_mars_{ 0 };
	public:
		// virtual �Ҹ���
		WeatherPrediction() = default;
		virtual ~WeatherPrediction() = default;
		WeatherPrediction(const WeatherPrediction& src) = default;
		WeatherPrediction& operator=(const WeatherPrediction& rhs) = default;
		WeatherPrediction(WeatherPrediction&& src) = default;
		WeatherPrediction& operator=(WeatherPrediction&& rhs) = default;
		// ���� �µ��� ȭ�� ������ �����Ѵ�.
		virtual void set_current_temp_fahrenheit(double temp);
		// �񼺰� ȭ�� ������ ���� �Ÿ��� �����Ѵ�.
		virtual void set_position_of_jupiter(double distance_from_mars);
		// ���� �µ��� ���� �������� �����´�.
		[[nodiscard]] virtual auto get_tomorrow_temp_fahrenheit() const -> bool;
		// ���� �� �� Ȯ���� �����´�. 1-> Ȯ���� �񰡿� 0-> �� �ȿ�
		[[nodiscard]] virtual auto get_chance_of_rain() const -> double;
		// ��� ���
		virtual void show_result() const;
		// ���� �µ��� ��Ʈ�������� �����Ѵ�.
		[[nodiscard]] virtual auto get_temperature() const -> std::string;
	};
}
