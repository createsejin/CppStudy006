export module simulator:internal;

export namespace simulator01
{
	auto convert_miles_to_km(const double miles) -> double {
		return miles * 1.6;
	}
}
