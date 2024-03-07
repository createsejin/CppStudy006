module simulator;

namespace simulator01
{
	CarSimulator::CarSimulator() {
		cout << "CarSimulator Constructed." << endl;
	}
	void CarSimulator::set_odometer(const double miles) {
		cout << convert_miles_to_km(miles) << endl;
	}
}
