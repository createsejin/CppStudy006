module study12;
import std;
import game_board01;
import game_piece01;
import grid01;
import spreadsheet_cell;

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
	
}