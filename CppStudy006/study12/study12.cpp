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
		other_name1 my_class1;
		other_name2<int> my_class2;
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
	void study012() {
		constexpr int myInt{ 3 }, intArray[]{ 1, 2, 3, 4 };
		constexpr size_t sizeIntArray{ size(intArray) };

		size_t result{ Find<int>(myInt, intArray, sizeIntArray).value_or(-1) };
		cout << std::format("result1 = {}\n", result);

		constexpr double myDouble{ 5.6 }, doubleArray[]{ 1.2, 3.4, 5.7, 7.5 };
		constexpr size_t sizeDoubleArray{ size(intArray) };
		// 타입을 명시적으로 호출
		auto result2{ Find<double>(myDouble, doubleArray, sizeDoubleArray) };
		if (result2.has_value()) cout << std::format("result2 = {}\n", result2.value());
		else cout << "result2 = not found.\n";

		result2 = Find<double>(myInt, doubleArray, sizeDoubleArray);
		if (result2.has_value()) cout << std::format("result3 = {}\n", result2.value());
		else cout << "result3 = not found.\n";

		using namespace spreadsheet01;
		const SpreadsheetCell cell1{ 10.0 };
		const SpreadsheetCell cellArray[] {
			SpreadsheetCell{3.0},
			SpreadsheetCell{4.0},
			SpreadsheetCell{10.0},
		};
		constexpr size_t sizeCellArray{ size(cellArray) };
		result2 = Find<SpreadsheetCell>(cell1, cellArray, sizeCellArray);
		if (result2.has_value()) cout << std::format("result4 = {}\n", result2.value());
		else cout << "result4 = not found.\n";
	}
}