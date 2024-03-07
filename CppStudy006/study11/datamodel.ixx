export module datamodel;
export import :person;
export import :address;
import std;
export namespace datamodel
{
	using persons = std::vector<Person>;
}
