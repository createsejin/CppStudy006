export module game_board06;
import grid05;
import std;

namespace game_board06
{
	export template<typename T>
	class GameBoard final : public Grid<T>
	{
	public:
		explicit GameBoard(size_t width = Grid<T>::DefaultWidth, size_t height = Grid<T>::DefaultHeight);
		void move(size_t xSrc, size_t ySrc, size_t xDest, size_t yDest);
	};

	template<typename T>
	GameBoard<T>::GameBoard(const size_t width, const size_t height)
		: Grid<T>(width, height)
	{
	}

	template<typename T>
	void GameBoard<T>::move(const size_t xSrc, const size_t ySrc, const size_t xDest, const size_t yDest)
	{
		Grid<T>::at(xDest, yDest) = std::move(Grid<T>::at(xSrc, ySrc));
		Grid<T>::at(xSrc, ySrc).reset();
		/*this->at(xDest, yDest) = std::move(this->at(xSrc, ySrc));
		this->at(xSrc, ySrc).reset(); �̷��� �ص� �ȴ�. ��, at �޼��带 �������̵� �� ���, �Ļ�Ŭ������ �������̵��� ������
		ȣ��ȴ�. */
	}

}
