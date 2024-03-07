export module simulator:car;
import :internal;
import std;

using namespace std;
export namespace simulator01
{
	class CarSimulator
	{
	public:
		CarSimulator();
		static void set_odometer(double miles);
	};
}
