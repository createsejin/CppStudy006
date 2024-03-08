export module grid05:string;
import :main;

namespace game_board06
{
	export template<>
	class Grid<const char*>
	{
		size_t width_{ 0 }, height_{ 0 };
		std::vector<std::vector<std::optional<std::string>>> cells_;
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

		std::optional<std::string>& at(size_t x, size_t y);
		const std::optional<std::string>& at(size_t x, size_t y) const;

		[[nodiscard]] auto getHeight() const -> size_t { return height_; }
		[[nodiscard]] auto getWidth() const -> size_t { return width_; }

		void print_at(std::string_view name, size_t x, size_t y) const;
	};

	void Grid<const char*>::verifyCoordinate(size_t x, size_t y) const {
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
	Grid<const char*>::Grid(const size_t width, const size_t height)
		: width_(width), height_(height)
	{
		cells_.resize(width_);
		for (auto& column : cells_) {
			column.resize(height_);
		}
	}

	std::optional<std::string>& Grid<const char*>::at(const size_t x, const size_t y) {
		return const_cast<std::optional<std::string>&>(std::as_const(*this).at(x, y));
	}

	const std::optional<std::string>& Grid<const char*>::at(const size_t x, const size_t y) const {
		verifyCoordinate(x, y);
		return cells_[x][y];
	}
	void Grid<const char*>::print_at(const std::string_view name, const size_t x, const size_t y) const {
		verifyCoordinate(x, y);
		std::cout << std::format("{}.at({}, {}) = {}\n", name, x, y, at(x, y).value_or(""));
	}
}
