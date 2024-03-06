export module datamodel;
export import datamodel.person;
export import datamodel.address;
import std;
export namespace datamodel
{
	using persons = std::vector<Person>;
}
