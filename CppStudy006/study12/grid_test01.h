#pragma once
import std;

namespace grid_test01
{
	template <typename T>
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
}
