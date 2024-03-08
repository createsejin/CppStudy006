export module grid03;
import std;

namespace game_board04
{
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
		template<typename E>
		explicit Grid(const Grid<E>& src);
		template<typename E>
		Grid& operator=(const Grid<E>& rhs);
		Grid(Grid&& src) noexcept = default;
		Grid& operator=(Grid&& rhs) noexcept = default;

		std::optional<T>& at(size_t x, size_t y);
		const std::optional<T>& at(size_t x, size_t y) const;

		[[nodiscard]] auto getHeight() const -> size_t { return height_; }
		[[nodiscard]] auto getWidth() const -> size_t { return width_; }

		void swap(Grid& other) noexcept;
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
	template<typename E>
	Grid<T>::Grid(const Grid<E>& src) // Grid<T>와 Grid<E>의 타입이 다르기 때문에 src는 반드시 public method로 접근해야한다.
		: Grid(src.getWidth(), src.getHeight())
	{
		for (size_t i{0}; i < width_; ++i) {
			for (size_t j{0}; j < height_; ++j) {
				cells_[i][j] = src.at(i, j);
			}
		}
	}

	template<typename T>
	template<typename E>
	Grid<T>& Grid<T>::operator=(const Grid<E>& rhs)	{
		Grid<T> temp{ rhs }; // 모든 작업을 임시 인스턴스에서 처리한다.
		swap(temp); // 예외가 발생하지 않는 연산에 대해서만 맞바꾼다.
		return *this;
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
	void swap(Grid<T>& first, Grid<T>& second) noexcept {
		first.swap(second);
	}

	template<typename T>
	void Grid<T>::swap(Grid& other) noexcept {
		std::swap(width_, other.width_);
		std::swap(height_, other.height_);
		std::swap(cells_, other.cells_);
	}
}
