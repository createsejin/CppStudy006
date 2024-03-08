export module game_piece06;
import std;

namespace game_board06
{
	export class GamePiece
	{
	public:
		virtual ~GamePiece() = default;
		virtual auto clone() const -> std::unique_ptr<GamePiece> = 0;
	};

	export class ChessPiece final : public GamePiece
	{
	public:
		auto clone() const -> std::unique_ptr<GamePiece> override {
			return std::make_unique<ChessPiece>(*this);
		}
	};
}
