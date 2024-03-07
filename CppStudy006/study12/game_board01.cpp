module game_board01;

namespace game_board01
{
	void GameBoard::verifyCoordinate(const size_t x, const size_t y) const {
		if (x >= width_) {
			throw std::out_of_range{
				std::format("{} must be less than {}.", x, width_)
			};
		}
		if (y >= height_) {
			throw std::out_of_range{
				std::format("{} must be less than {}.", y, height_)
			};
		}
	}
	GameBoard::GameBoard(const size_t width, const size_t height)
		: width_(width), height_(height)
	{
		cells_.resize(width);
		for (auto& column : cells_) {
			column.resize(height);
		}
	}
	GameBoard::GameBoard(const GameBoard& src)
		: GameBoard(src.width_, src.height_)
	{
		for (size_t i{0}; i < width_; ++i) {
			for (size_t j{0}; i < height_; ++j) {
				if (src.cells_[i][j])
					cells_[i][j] = src.cells_[i][j]->clone();
			} // data copy
		}
	}
	void GameBoard::swap(GameBoard& other) noexcept
	{
		std::swap(width_, other.width_);
		std::swap(height_, other.height_);
		std::swap(cells_, other.cells_);
	}
	GameBoard& GameBoard::operator=(const GameBoard& rhs) {
		GameBoard temp{ rhs };
		swap(temp);
		return *this;
	}
	std::unique_ptr<GamePiece>& GameBoard::at(const size_t x, const size_t y)
	{
		return const_cast<std::unique_ptr<GamePiece>&>(std::as_const(*this).at(x, y));
		// std::as_const: *this를 const 타입으로 캐스팅 후 const 버전 at() 호출 후,
		// const_cast: 반환된 객체를 비 const 타입(std::unique_ptr<GamePiece>&)으로 캐스팅 후 return
	}
	const std::unique_ptr<GamePiece>& GameBoard::at(const size_t x, const size_t y) const
	{
		verifyCoordinate(x, y);
		return cells_[x][y];
	}
	void game_board01::swap(GameBoard& first, GameBoard& second) noexcept {
		first.swap(second);
	}
}
