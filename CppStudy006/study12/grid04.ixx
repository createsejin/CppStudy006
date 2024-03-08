export module grid04;
import std;

using namespace std;
namespace game_board05
{
	export template<typename T, size_t Width = 10, size_t Height = 10>
		class Grid
	{
		size_t width_{ 0 }, height_{ 0 };
		std::optional<T> cells_[Width][Height];
		static void verify_coordinate(size_t x, size_t y);
	public:
		Grid() = default;
		~Grid() = default; // virtual method와 destructor는 메서드 템플릿으로 만들 수 없다.
		Grid(const Grid& src) = default;
		Grid& operator=(const Grid& rhs) = default;

		template<typename E, size_t Width2, size_t Height2>
		Grid(const Grid<E, Width2, Height2>& src);
		template<typename E, size_t Width2, size_t Height2>
		Grid& operator=(const Grid<E, Width2, Height2>& rhs);

		Grid(Grid&& src) noexcept;
		Grid& operator=(Grid&& rhs) noexcept;

		std::optional<T>& at(size_t x, size_t y);
		const std::optional<T>& at(size_t x, size_t y) const;

		[[nodiscard]] static auto get_height() -> size_t { return Height; }
		[[nodiscard]] static auto get_width() -> size_t { return Width; }

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

	template<typename T, size_t Width, size_t Height>
	template<typename E, size_t Width2, size_t Height2>
	Grid<T, Width, Height>::Grid(const Grid<E, Width2, Height2>& src) {
		for (size_t i{0}; i < Width; ++i) {
			for (size_t j{0}; j < Height; ++j) {
				if (i < Width2 && j < Height2) {
					cells_[i][j] = src.at(i, j);
				} else {
					cells_[i][j].reset();
				}
			}
		}
	}

	template<typename T, size_t Width, size_t Height>
	template<typename E, size_t Width2, size_t Height2>
	Grid<T, Width, Height>& Grid<T, Width, Height>::operator=(const Grid<E, Width2, Height2>& rhs) {
		Grid temp{ rhs };
		swap(temp);
		return *this;
	}

	template<typename T, size_t Width, size_t Height> // reference p.454
	Grid<T, Width, Height>::Grid(Grid&& src) noexcept { // move constructor
		game_board05::swap(*this, src);
	}

	template<typename T, size_t Width, size_t Height> // move assignment operator
	Grid<T, Width, Height>& Grid<T, Width, Height>::operator=(Grid&& rhs) noexcept {
		game_board05::swap(*this, rhs);
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
	} // p.639 부터

	template<typename T, size_t Width, size_t Height>
	void Grid<T, Width, Height>::swap(Grid& other) noexcept {
		std::swap(width_, other.width_);
		std::swap(height_, other.height_);
		std::swap(cells_, other.cells_);
	}
}
