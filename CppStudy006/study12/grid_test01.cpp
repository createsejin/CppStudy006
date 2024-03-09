#include "grid_test01.h"

namespace grid_test01
{
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
		std::cout << std::format("{}.at({}, {}) = {}\n", name, x, y, at(x, y).value_or(""));
	}

	template<typename T>
		Grid<T> operator+(const Grid<T>& lhs, const Grid<T>& rhs) {
		size_t min_width{ std::min(lhs.width_, rhs.width_) };
		size_t min_height{ std::min(lhs.height_, rhs.height_) };

		Grid<T> result{ min_width, min_height };
		for (size_t y{ 0 }; y < min_height; ++y) {
			for (size_t x{ 0 }; x < min_width; ++x) {
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
