export module simulator:bike;
import :internal;
import std;

using namespace std;
export namespace simulator01
{
	class BikeSimulator
	{
	public:
		BikeSimulator() {
			cout << "BikeSimulator constructed." << endl;
		}
		static void set_odometer(const double miles) {
			cout << convert_miles_to_km(miles) << endl;
		}
	};
}
