export module game_piece01;
import std;

namespace game_board01
{
	export class GamePiece
	{ // abstract base class
	public:
		virtual ~GamePiece() = default;
		virtual auto clone() const -> std::unique_ptr<GamePiece> = 0;
	};

	class ChessPiece final : public GamePiece
	{
	public:
		auto clone() const -> std::unique_ptr<GamePiece> override {
			return std::make_unique<ChessPiece>(*this);
		}
	};
}
