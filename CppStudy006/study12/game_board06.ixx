export module game_board06;
import std;
import grid05;
import game_piece06;

namespace game_board06
{
	export template<std::derived_from<GamePiece> T> // p.677
	class GameBoard final : public Grid<T>
	{
	public:
		explicit GameBoard(size_t width = Grid<T>::DefaultWidth, size_t height = Grid<T>::DefaultHeight);
		void move(size_t xSrc, size_t ySrc, size_t xDest, size_t yDest) requires std::movable<T>;
	};

	template<std::derived_from<GamePiece> T>
	GameBoard<T>::GameBoard(const size_t width, const size_t height)
		: Grid<T>(width, height)
	{
	}

	template<std::derived_from<GamePiece> T>
	void GameBoard<T>::move(const size_t xSrc, const size_t ySrc, const size_t xDest, const size_t yDest)
		requires std::movable<T>
	{
		Grid<T>::at(xDest, yDest) = std::move(Grid<T>::at(xSrc, ySrc));
		Grid<T>::at(xSrc, ySrc).reset();
		/*this->at(xDest, yDest) = std::move(this->at(xSrc, ySrc));
		this->at(xSrc, ySrc).reset(); 이렇게 해도 된다. 단, at 메서드를 오버라이드 한 경우, 파생클래스의 오버라이드한 버전이
		호출된다. */
	}

}
