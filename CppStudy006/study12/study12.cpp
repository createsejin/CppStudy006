module study12;
import std;
import game_board01;
import game_piece01;
using namespace std;
using namespace game_board01;
namespace study12_001
{
	void study001() {
		cout << "study001 called." << endl;
		GameBoard chessBoard{ 8, 8 };
		auto pawn{ std::make_unique<ChessPiece>() };
		chessBoard.at(0, 0) = std::move(pawn);
		chessBoard.at(0, 1) = std::make_unique<ChessPiece>();
		chessBoard.at(0, 1) = nullptr;
	}
}