module;
#include <cstring>
#include "grid_test01.h"
module study12;
import std;
import game_board01;
import game_piece01;
import grid01;
import grid02;
import grid03;
import grid04;
import grid05;
import spreadsheet_cell;
import game_board06;
import game_piece06;
import key_value_pair01;
import key_value_pair02;

using namespace std;
namespace study12_001
{
	void study001() {
		using namespace game_board01;
		cout << "study001 called." << endl;
		GameBoard chessBoard{ 8, 8 };
		auto pawn{ std::make_unique<ChessPiece>() };
		chessBoard.at(0, 0) = std::move(pawn);
		chessBoard.at(0, 1) = std::make_unique<ChessPiece>();
		chessBoard.at(0, 1) = nullptr;
	}

	using namespace game_board02;
	using namespace spreadsheet01;

	using IntGrid = Grid<int>;
	void processIntGrid(IntGrid& grid) {}

	void study002() { // p.634
		Grid<int> myIntGrid;
		Grid<double> myDoubleGrid{ 11, 11 };
		myIntGrid.at(0, 0) = 10;
		const int x { myIntGrid.at(0, 0).value_or(0) };
		if (x == 3) cout << "3";

		Grid<int> grid2{ myIntGrid }; // copy constructor
		Grid<int> anotherGrid;
		anotherGrid = grid2; // copy assignment
		anotherGrid.at(0, 0) = 3;

		Grid<SpreadsheetCell> my_spreadsheet_grid;
		SpreadsheetCell myCell{ 1.234 };
		my_spreadsheet_grid.at(3, 4) = myCell;

		Grid<const char*> my_string_grid;
		my_string_grid.at(2, 2) = "hello";

		Grid<vector<int>> gridOfVector;
		vector<int> my_vector{ 1, 2, 3, 4 };
		gridOfVector.at(5, 6) = my_vector;

		const auto myGridOnHeap{ make_unique<Grid<int>>(2, 2) };
		myGridOnHeap->at(0, 0) = 10;
		const int x2 { myGridOnHeap->at(0, 0).value_or(0) };
		if (x2 == 0) cout << "at(0, 0) is empty." << endl;
	}
}
namespace study12_002
{
	using namespace game_board03;

	// template 매개변수에 인수를 전달할 목적의 함수라면, trailing return type을 사용하면 안되는것 같다.
	constexpr size_t get_height() { return 10; }

	void study003() {
		constexpr size_t height{ 10 };
		Grid<int, 10, height> my_grid;
		// ReSharper disable once CppJoinDeclarationAndAssignment
		Grid<int, 10, get_height()> another_grid;
		my_grid.at(2, 3) = 42;
		cout << std::format("my_grid = {}\n", my_grid.at(2, 3).value_or(0));
		//another_grid = my_grid;
		another_grid = std::move(my_grid);
		//cout << std::format("my_grid = {}\n", my_grid.at(2, 3).value_or(0)); //move된 객체는 사용하지 않아야한다.
		cout << std::format("another_grid = {}\n", another_grid.at(2, 3).value_or(0));
	}
	void study004() { // p.641
		Grid<> my_int_grid;
		Grid<int> my_grid;
		Grid<int, 5> another_grid;
		Grid<int, 5, 5> a_fourth_grid;
	}
	void study005() {
		auto pair2{ std::make_pair(1, 2.3) };
		std::pair pair3{ 1, 2.3 };
		// CTAD가 작동하기 위한 조건 :
		// 1. 클래스 템플릿 매개변수의 디폴트값이 모두 지정되어있다.
		// 2. 생성자에서 모든 매개변수를 사용하도록 작성되어 있다.
	}
	// p.643 사용자 정의 템플릿 매개변수 추론
	template<typename  T>
	class SpreadsheedCell
	{
		T content_;
	public:
		explicit SpreadsheedCell(T t) : content_(std::move(t)) {}
		const T& get_content() const { return content_; }
	};
	
	void study006() {
		const string my_string{ "Hello world!" };
		SpreadsheedCell cell{ my_string };
	}
}
namespace study12_003
{
	using namespace game_board04;
	void study007() { // p.645
		Grid<int> myIntGrid;
		Grid<double> myDoubleGrid;
		myDoubleGrid = myIntGrid;
		Grid<double> newDoubleGrid{ myIntGrid };
	}
}
namespace study12_004
{
	using namespace game_board05;
	void study008() { // p.648
		constexpr size_t height{ 10 };
		Grid<int, 10, height> my_grid;
		// ReSharper disable once CppJoinDeclarationAndAssignment
		Grid<int, 10, height> another_grid;
		my_grid.at(2, 3) = 42;
		cout << std::format("my_grid = {}\n", my_grid.at(2, 3).value_or(0));
		//another_grid = my_grid;
		another_grid = std::move(my_grid);
		cout << std::format("another_grid = {}\n", another_grid.at(2, 3).value_or(0));
		Grid<int, 11, 11> my_grid2;
		my_grid2.at(10, 10) = 22;
		my_grid2.at(2, 3) = 34;
		Grid<int> another_grid2 = my_grid2;
		cout << std::format("another_grid2.at(2, 3) = {}\n", another_grid2.at(2, 3).value_or(0));
		Grid<int, 11, 11> my_grid3;
		my_grid3.at(3, 3) = 69;
		another_grid2 = std::move(my_grid3);
		cout << std::format("another_grid2.at(2, 3) = {}\n", another_grid2.at(2, 3).value_or(0));
		cout << std::format("another_grid2.at(3, 3) = {}\n", another_grid2.at(3, 3).value_or(0));
	}
}
namespace study12_005
{
	using namespace game_board06;
	
	void study009() {
		Grid<int> myIntGrid;
		Grid<const char*> stringGrid1{ 2, 2 };
		const char* dummy{ "dummy" };
		stringGrid1.at(0, 0) = "hello";
		stringGrid1.at(0, 1) = dummy;
		stringGrid1.at(1, 0) = dummy;
		stringGrid1.at(1, 1) = "there";
		const Grid<const char*> stringGrid2{ stringGrid1 };
		stringGrid1.print_at("stringGrid1", 0, 0);
		stringGrid1.print_at("stringGrid1", 0, 1);
		stringGrid1.print_at("stringGrid1", 1, 0);
		stringGrid1.print_at("stringGrid1", 1, 1);
		stringGrid2.print_at("stringGrid2", 0, 0);
		stringGrid2.print_at("stringGrid2", 0, 1);
		stringGrid2.print_at("stringGrid2", 1, 0);
		stringGrid2.print_at("stringGrid2", 1, 1);
		const Grid stringGrid3{ std::move(stringGrid1) };
		stringGrid3.print_at("stringGrid3", 0, 0);
		stringGrid3.print_at("stringGrid3", 0, 1);
		stringGrid3.print_at("stringGrid3", 1, 0);
		stringGrid3.print_at("stringGrid3", 1, 1);
	}
	void study010() { // p.655
		GameBoard<ChessPiece> chess_board{ 8, 8 };
		ChessPiece pawn;
		chess_board.at(0, 0) = pawn;
		chess_board.move(0, 0, 0, 1);
	}
	// p.656
	template<typename T1, typename T2>
	class MyClassTemplate {};
	using other_name1 = MyClassTemplate<int, double>;
	template<typename T1>
	using other_name2 = MyClassTemplate<T1, double>;
	void study011() {
		/*other_name1 my_class1;
		other_name2<int> my_class2;*/
	}
	// p.657 함수 템플릿
	template<typename T>
	std::optional<size_t> Find(const T& value, const T* arr, const size_t size) {
		for (size_t i{0}; i < size; ++i) {
			if (arr[i] == value) {
				return i;
			}
		}
		return std::nullopt;
	}

	template<typename T, size_t N> // 배열 참조 'T(&arr)[N]'를 이용하면 컴파일 시점에 배열 크기를 알 수 있다.
	std::optional<size_t> Find(const T& value, const T(&arr)[N]) {
		return Find(value, arr, N);
	}
	// p.659 함수 템플릿 오버로딩
	std::optional<size_t> Find(const char* value, const char** arr, const size_t size) {
		for (size_t i{ 0 }; i < size; ++i) {
			if (strcmp(arr[i], value) == 0) {
				return i;
			}
		}
		return std::nullopt;
	}

	void print_res(const std::optional<size_t> res, const unsigned int num) {
		if (res.has_value()) cout << std::format("result{} = {}\n", num, res.value());
		else cout << std::format("result{} = not found.\n", num);
	}

	void study012() {
		constexpr int myInt{ 3 }, intArray[]{ 1, 2, 3, 4 };
		constexpr size_t sizeIntArray{ size(intArray) };

		size_t result{ Find<int>(myInt, intArray, sizeIntArray).value_or(-1) };
		cout << std::format("result1 = {}\n", result);

		constexpr double myDouble{ 5.6 }, doubleArray[]{ 1.2, 3.4, 5.7, 7.5 };
		constexpr size_t sizeDoubleArray{ size(intArray) };
		// 타입을 명시적으로 호출
		auto result2{ Find<double>(myDouble, doubleArray, sizeDoubleArray) };
		print_res(result2, 2);

		result2 = Find<double>(myInt, doubleArray, sizeDoubleArray);
		print_res(result2, 3);

		using namespace spreadsheet01;
		const SpreadsheetCell cell1{ 10.0 };
		const SpreadsheetCell cellArray[] {
			SpreadsheetCell{3.0},
			SpreadsheetCell{4.0},
			SpreadsheetCell{10.0},
		};
		constexpr size_t sizeCellArray{ size(cellArray) };
		result2 = Find<SpreadsheetCell>(cell1, cellArray, sizeCellArray);
		print_res(result2, 4);
	}
	void study013() { // p.658
		constexpr int myInt{ 3 }, intArray[]{ 1, 2, 3, 4 };
		const auto res{ Find(myInt, intArray) };
		print_res(res, 1);
	}
	void study014() {
		const char* word{ "two" };
		const char* words[]{ "one", "two", "three", "four" };
		constexpr size_t sizeWords{ std::size(words) };
		auto res{ Find(word, words, sizeWords) };
		print_res(res, 1);
		res = Find(word, words); // 이것도 가능하다.
		print_res(res, 2);
		res = Find<const char*>(word, words, sizeWords); // 이렇게 하면 오버로드된 버전(<const char*>)이 아닌
		//	T=const char* 원본 버전이 호출된다.
		print_res(res, 3);
	}
	// p.662
	template<typename ReturnType = long long, typename T1, typename T2>
	ReturnType add(const T1& t1, const T2& t2) { return t1 + t2; }

	void study015() {
		auto result1{ add<long long, int, int>(1, 2) };
		cout << std::format("result{} = {}", 1, result1);
		auto result2{ add<long long>(1, 2) };
		cout << std::format("result{} = {}", 2, result2);
	}
	template<typename T1, typename ReturnType, typename T2> // parameter의 마지막에 있는 매개변수만 추론 가능하다.
	// 따라서 이 경우에는 T1과 ReturnType을 명시적으로 지정해야한다.
	ReturnType add(const T1& t1, const T2& t2) { return t1 + t2; }

	void study016() {
		auto result1{ add<int, long long>(1, 2) };
		cout << std::format("result{} = {}", 1, result1);
		auto result2{ add(1, 2) }; // default 값을 지정한 add
		cout << std::format("result{} = {}", 2, result2);
	}
	
	
}
namespace study12_006
{
	// p.663
	template<typename T1, typename T2> // p.664
	decltype(auto) add(const T1& t1, const T2& t2) { return t1 + t2; }

	const std::string message{ "Test" };
	const std::string& get_string() { return message; }

	void study017() {
		auto s1{ get_string() }; // const와 reference 지시자가 사라짐. 즉, 복제 연산이 발생함.
		const auto& s2{ get_string() }; // 이렇게 명시적으로 지정해야한다.
		cout << s2 << "\n";
		decltype(auto) s3{ get_string() }; // 이렇게 하면 const나 ref가 제거되지 않는다.
		cout << s3 << "\n";
		decltype(auto) result1{ add(1, 2) };
		cout << std::format("result{} = {}", 1, result1);
	}
	void test001() {
		using namespace grid_test01;
		Grid<int> my_grid{ 2, 2 };
		my_grid.at(0, 0) = 23;
		my_grid.print_at("my_grid"sv, 0, 0);
	}
}
namespace study12_007
{
	// p.665 축약 함수 템플릿 구문
	decltype(auto) add(const auto& t1, const auto& t2) { return t1 + t2; }
	// p.666 변수 템플릿
	template<typename T>
	constexpr T pi{ T{3.141592653897} };void study018() {
		constexpr float pi_float{ pi<float> };
		cout << std::format("{:.8L}", pi_float) << endl;
		constexpr auto pi_long_double{ pi<long double> };
		cout << std::format("{:.12L}", pi_long_double) << endl;
		constexpr auto pi_std{ std::numbers::pi };
		cout << std::format("{:.15}", pi_std) << endl;
	}

	// p.667 concept
	template<typename T> // constraints expression
	concept c01 = sizeof(T) == 4;
	// simple requirement
	template<typename T> // p.669
	concept incrementable = requires(T x) { x++; ++x; };
	// type requirement
	template<typename T>
	concept c02 = requires { typename T::value_type; };
	// compound requirement
	template<typename T>
	concept c03 = requires (T x, T y) {
		{ x.swap(y) } noexcept;
	};
	// p.670
	template<typename T>
	concept c04 = requires (const T x)
	{
		{ x.size() } -> convertible_to<size_t>;
	};
	
	template<typename T>
	concept comparable = requires(const T a, const T b)
	{
		{ a == b } -> convertible_to<bool>;
		{ a < b } -> convertible_to<bool>;
	};

	// nested requirement
	template<typename T>
	concept c05 = requires (T t)
	{
		requires sizeof(t) == 4;
		++t; --t; t++; t--;
	};
	// combine concept
	template<typename T>
	concept decrementable = requires(T x) { x--; --x; };
	template<typename T>
	concept increment_and_decrementable = incrementable<T> && decrementable<T>;
	// p.672 standard concept
	class Foo {};
	template<typename T>
	concept isDerivedFromFoo = derived_from<T, Foo>;

	template<typename T>
	concept IsConvertibleToBool = convertible_to<T, bool>;
	// combination concept
	template<typename T>
	concept DefaultAndCopyConstructible = default_initializable<T> && copy_constructible<T>;

	void study019() {
		incrementable auto value1{ 1 };
		//incrementable auto value2{ "abc"s }; // error
	}
	// p.673
	template<convertible_to<bool> T>
	void handle(const T& t) {}

	template<incrementable T>
	void process01(const T& t) {}

	template<typename T> requires incrementable<T>
	void process02(const T& t) {}

	template<typename T> requires std::convertible_to<T, bool>
	void process03(const T& t) {}

	template<typename T> requires requires(T x) { x++; ++x; }
	void process04(const T& t) {}

	template<typename T> requires(sizeof(T) == 4)
	void process05(const T& t) {}

	template<typename T> requires incrementable<T> && decrementable<T>
	void process06(const T& t) {}

	template<typename T> requires std::is_arithmetic_v<T> // type trait
	void process07(const T& t) {}

	template<typename T> // trailing requires syntax
	void process08(const T& t) requires incrementable<T> {}

	// 축약 함수 템플릿 구문
	void process09(const incrementable auto& t) {}

	void study020() {
		process02(2);
		//process("str"s);
	}
}
namespace study12_008
{	// p.676 제약 조건 포함 관계
	template<typename T> requires std::integral<T>
	void process(const T& t) { cout << "integral<T>" << endl; }

	template<typename T> requires (std::integral<T> && sizeof(T) == 4)
	void process(const T& t) { cout << "integral<T> && sizeof(T) == 4" << endl; }

	void study021() {
		process(int{ 1 });
		process(short{ 2 });
	}

	template<typename T>
	std::optional<size_t> Find(const T& value, const T* arr, const size_t size) {
		for (size_t i{ 0 }; i < size; ++i) {
			if (arr[i] == value) {
				return i;
			}
		}
		return std::nullopt;
	}

	template<std::floating_point T>
	bool AreEqual(T x, T y, int precision = 2) {
		return fabs(x - y) <= numeric_limits<T>::epsilon() * fabs(x + y) * precision ||
			fabs(x - y) < numeric_limits<T>::min();
	}

	template<std::floating_point T>
	std::optional<size_t> Find(const T& value, const T* arr, const size_t size) {
		for (size_t i{0}; i < size; ++i) {
			if (AreEqual(arr[i], value)) {
				return i;
			}
		}
		return nullopt;
	}
	void print_res(const std::optional<size_t> res, const unsigned int num) {
		if (res.has_value()) cout << std::format("result{} = {}\n", num, res.value());
		else cout << std::format("result{} = not found.\n", num);
	}

	void study022() {
		constexpr double d_arr[] { 1.2, 2.3, 3.4, 5.5, 6.2 };
		constexpr double find_d{ 3.4 };
		const auto res{ Find<double>(find_d, d_arr, std::size(d_arr)) };
		print_res(res, 1);
	}
}
// p.680 연습문제
namespace study12_009
{
	// 12-1
	void study023() {
		using namespace key_value_pair01;
		vector<KeyValuePair<int, std::string>> my_vec;
		my_vec.emplace_back(1, "아나나나"s);
		my_vec.emplace_back(2, "배세희는 바보다."s);
		my_vec.emplace_back(3, "대우형도 바보다."s);
		my_vec.emplace_back(4, "그런데 나는 훠어어얼씬 바보다."s);
		for (const auto& pair : my_vec) {
			auto key{ pair.get_key() };
			auto value{ pair.get_value() };
			cout << std::format("{}: {}\n", key, value);
		}		
	}
	// 12-2
	void study024() {
		using namespace key_value_pair01;
		const KeyValuePair<const char*, const char*> kv{ "ddd", "나는 누구일까" };
		cout << std::format("{}: {}\n", kv.get_key(), kv.get_value());
	}
	// 12-3
	void study025() {
		using namespace key_value_pair02;
		const KeyValuePair kv{ 2, 3.4 };
		cout << std::format("{}: {}\n", kv.get_key(), kv.get_value());
	}
	// 12-4
	template<typename T>
	concept is_string_convertible = requires(T t) { std::to_string(t); };

	template<typename T1, typename T2> requires is_string_convertible<T1> && is_string_convertible<T2>
	auto concat(const T1& t1, const T2& t2) -> std::string {
		return std::to_string(t1) + std::to_string(t2);
	}
	// 12-5
	auto concat(const std::string& t1, const std::string& t2) -> std::string
	{
		return t1 + t2;
	}
	template<typename T> requires is_string_convertible<T>
	auto concat(const T& t1, const std::string& t2) -> std::string {
		return std::to_string(t1) + t2;
	}

	void study026() {
		std::string result1{ concat<int, double>(1, 2.3) };
		cout << std::format("result{} = {}\n", 1, result1);
		auto result2{ concat(2.0, 3) };
		cout << std::format("result{} = {}\n", 2, result2);
		auto result3{ concat("ddd"s, "fff"s) };
		cout << std::format("result{} = {}\n", 3, result3);
		auto result4{ concat(2.0, "fff"s) };
		cout << std::format("result{} = {}\n", 4, result4);
	}
	// 12-6
	template<typename T> requires std::integral<T> || std::floating_point<T>
	std::optional<size_t> Find(const T& value, const T* arr, const size_t size) {
		for (size_t i{0}; i < size; ++i) {
			if (arr[i] == value) {
				return i;
			}
		}
		return nullopt;
	}
	void study027() {
		constexpr int arr[]{ 1, 2, 3, 4, 5, 6 };
		constexpr size_t size { std::size(arr) };
		constexpr int find_value{ 4 };
		auto result1{ Find(find_value, arr, size) };
		if (result1.has_value()) cout << std::format("result{} index = {}\n", 1, result1.value());

		constexpr char arr2[]{ 'a', 'b', 'c', 'd', 'e' };
		constexpr size_t size2{ std::size(arr2) };
		constexpr char find_value2{ 'd' };
		auto result2{ Find(find_value2, arr2, size2) };
		if (result1.has_value()) cout << std::format("result{} index = {}\n", 2, result2.value());
	}
}