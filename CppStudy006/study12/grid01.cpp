module grid01;

namespace game_board02
{
	template<typename T>
	void Grid<T>::verifyCoordinate(const size_t x, const size_t y) const {
		if (x >= width_) {
			throw std::out_of_range {
				std::format("{} must be less than {}.", x, width_)
			};
		}
		if (y >= height_) {
			throw std::out_of_range {
				std::format("{} must be less than {}.", y, height_)
			};
		}
	}
	template<typename T>
	Grid<T>::Grid(const size_t width, const size_t height)
		: width_(width), height_(height)
	{
		cells_.resize(width_);
		for (auto& column : cells_) {
			column.resize(height_);
		}
	}
	template<typename T>
	std::optional<T>& Grid<T>::at(size_t x, size_t y)	{
		return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
	}
	template<typename T>
	const std::optional<T>& Grid<T>::at(size_t x, size_t y) const {
		verifyCoordinate(x, y);
		return cells_[x][y];
	}
}
