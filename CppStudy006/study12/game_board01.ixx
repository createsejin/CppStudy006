export module game_board01;
import std;
import game_piece01;
namespace game_board01
{
	export class GameBoard
	{
		size_t width_{ 0 }, height_{ 0 };
		void verifyCoordinate(size_t x, size_t y) const;
		std::vector<std::vector<std::unique_ptr<GamePiece>>> cells_;
	public:
		static constexpr size_t DefaultWidth{ 10 };
		static constexpr size_t DefaultHeight{ 10 };
		explicit GameBoard(size_t width = DefaultWidth, size_t height = DefaultHeight);
		virtual ~GameBoard() = default;
		GameBoard(const GameBoard& src);
		GameBoard& operator=(const GameBoard& rhs);
		GameBoard(GameBoard&& src) noexcept = default;
		GameBoard& operator=(GameBoard&& rhs) noexcept = default;

		auto at(size_t x, size_t y) -> std::unique_ptr<GamePiece>&;
		auto at(size_t x, size_t y) const -> const std::unique_ptr<GamePiece>&;

		[[nodiscard]] auto getHeight() const -> size_t { return height_; }
		[[nodiscard]] auto getWidth() const -> size_t { return width_; }

		void swap(GameBoard& other) noexcept;
	};

	export void swap(GameBoard& first, GameBoard& second) noexcept;
}
