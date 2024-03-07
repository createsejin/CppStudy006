export module grid02;
import std;

namespace game_board03
{
	export template<typename T, size_t Width, size_t Height>
	class Grid
	{
		size_t width_{ 0 }, height_{ 0 };
		std::optional<T> cells_[Width][Height];
		void verify_coordinate(size_t x, size_t y) const;
	public:
		Grid() = default;
		~Grid() = default;
		Grid(const Grid& src) = default;
		Grid& operator=(const Grid& rhs) = default;
		Grid(Grid&& src) noexcept;
		Grid& operator=(Grid&& rhs) noexcept;

		std::optional<T>& at(size_t x, size_t y);
		const std::optional<T>& at(size_t x, size_t y) const;

		[[nodiscard]] static auto get_height() { return Height; }
		[[nodiscard]] static auto get_width() { return Width; }
	};

	template<typename T, size_t Width, size_t Height>
	void Grid<T, Width, Height>::verify_coordinate(const size_t x, const size_t y) const {
		if (x >= Width) {
			throw std::out_of_range{
				std::format("{} must be less than {}.", x, width_)
			};
		}
		if (y >= Height) {
			throw std::out_of_range{
				std::format("{} must be less than {}.", y, height_)
			};
		}
	}
	//p.639
	template<typename T, size_t Width, size_t Height>
	Grid<T, Width, Height>::Grid(Grid&& src) noexcept {
		const size_t max_width{ src.width_ < Width ? src.width_ : Width };
		const size_t max_height{ src.height_ < Height ? src.height_ : Height };
		for (size_t i{0}; i < max_width; ++i) {
			for (size_t j{0}; j < max_height; ++j) {
				cells_[i][j] = std::move(src.cells_[i][j]);
			}
		}
	}

	template<typename T, size_t Width, size_t Height>
	Grid<T, Width, Height>& Grid<T, Width, Height>::operator=(Grid&& rhs) noexcept {
		const size_t max_width{ rhs.width_ < Width ? rhs.width_ : Width };
		const size_t max_height{ rhs.height_ < Height ? rhs.height_ : Height };
		for (size_t i{ 0 }; i < max_width; ++i) {
			for (size_t j{ 0 }; j < max_height; ++j) {
				cells_[i][j] = std::move(rhs.cells_[i][j]);
			}
		}
		return *this;
	}

	template<typename T, size_t Width, size_t Height>
	std::optional<T>& Grid<T, Width, Height>::at(size_t x, size_t y) {
		return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
	}

	template<typename T, size_t Width, size_t Height>
	const std::optional<T>& Grid<T, Width, Height>::at(const size_t x, const size_t y) const {
		verify_coordinate(x, y);
		return cells_[x][y];
	}
}
