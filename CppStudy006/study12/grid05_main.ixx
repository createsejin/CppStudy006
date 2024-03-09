export module grid05:main;
import std;

namespace game_board06
{
	/*export template<typename T> class Grid;
	export template<typename T>
	Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs);*/

	export template <typename T>
	class Grid
	{
		size_t width_{ 0 }, height_{ 0 };
		std::vector<std::vector<std::optional<T>>> cells_;
		void verifyCoordinate(size_t x, size_t y) const;
	public:
		static constexpr size_t DefaultWidth{ 10 };
		static constexpr size_t DefaultHeight{ 10 };

		explicit Grid(size_t width = DefaultWidth, size_t height = DefaultHeight);

		virtual ~Grid() = default;
		Grid(const Grid& src) = default;
		Grid& operator=(const Grid& rhs) = default;
		Grid(Grid&& src) noexcept = default;
		Grid& operator=(Grid&& rhs) noexcept = default;

		std::optional<T>& at(size_t x, size_t y);
		const std::optional<T>& at(size_t x, size_t y) const;

		[[nodiscard]] auto getHeight() const -> size_t { return height_; }
		[[nodiscard]] auto getWidth() const -> size_t { return width_; }

		void print_at(std::string_view name, size_t x, size_t y) const;
		friend Grid<T> operator+<T>(const Grid<T>& lhs, const Grid<T>& rhs);
	};

	// p.631 참고: 템플릿 메서드의 정의는 그 템플릿을 사용하는 모든 클라이언트 코드에서 볼 수 있어야하므로 같은 파일에 적어야한다.
	template<typename T>
	void Grid<T>::verifyCoordinate(const size_t x, const size_t y) const {
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
	std::optional<T>& Grid<T>::at(size_t x, size_t y) {
		return const_cast<std::optional<T>&>(std::as_const(*this).at(x, y));
	}
	template<typename T>
	const std::optional<T>& Grid<T>::at(size_t x, size_t y) const {
		verifyCoordinate(x, y);
		return cells_[x][y];
	}

	template<typename T>
	void Grid<T>::print_at(const std::string_view name, size_t x, size_t y) const {
		verifyCoordinate(x, y);
		if (at(x, y).has_value())
			std::cout << std::format("{}.at({}, {}) = {}\n", name, x, y, at(x, y).value());
		else std::cout << std::format("{}.at({}, {}) = null\n", name, x, y);
	}

	export template<typename T>
	Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs) {
		size_t min_width{ std::min(lhs.width_, rhs.width_) };
		size_t min_height{ std::min(lhs.height_, rhs.height_) };

		Grid<T> result{ min_width, min_height };
		for (size_t y{0}; y < min_height; ++y) {
			for (size_t x{0}; x < min_width; ++x) {
				const auto& left_element{ lhs.cells_[x][y] };
				const auto& right_element{ rhs.cells_[x][y] };
				if (left_element.has_value() && right_element.has_value()) {
					result.at(x, y) = left_element.value() + right_element.value();
				}
			}
		}
		return result;
	}
}
