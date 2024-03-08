export module grid02;
import std;

using namespace std;
namespace game_board03
{
	export template<typename T, size_t Width, size_t Height>
	class Grid
	{
		size_t width_{ 0 }, height_{ 0 };
		std::optional<T> cells_[Width][Height];
		static void verify_coordinate(size_t x, size_t y);
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

		void swap(Grid& other) noexcept;
	};

	template<typename T, size_t Width, size_t Height>
	void Grid<T, Width, Height>::verify_coordinate(const size_t x, const size_t y) {
		if (x >= Width) {
			throw std::out_of_range{
				std::format("{} must be less than {}.", x, Width)
			};
		}
		if (y >= Height) {
			throw std::out_of_range{
				std::format("{} must be less than {}.", y, Height)
			};
		}
	}
	export template<typename T, size_t Width, size_t Height>
		void swap(Grid<T, Width, Height>& first, Grid<T, Width, Height>& second) noexcept {
		first.swap(second);
	}

	template<typename T, size_t Width, size_t Height> // reference p.454
	Grid<T, Width, Height>::Grid(Grid&& src) noexcept { // move constructor
		game_board03::swap(*this, src);
	}

	template<typename T, size_t Width, size_t Height> // move assignment operator
	Grid<T, Width, Height>& Grid<T, Width, Height>::operator=(Grid&& rhs) noexcept {
		game_board03::swap(*this, rhs);
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
	} // p.639 บฮลอ

	template<typename T, size_t Width, size_t Height>
	void Grid<T, Width, Height>::swap(Grid& other) noexcept	{
		std::swap(width_, other.width_);
		std::swap(height_, other.height_);
		std::swap(cells_, other.cells_);
	}
}
