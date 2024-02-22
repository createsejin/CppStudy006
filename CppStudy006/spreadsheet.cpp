module spreadsheet;
import std;
using namespace std;
namespace spreadsheet01
{
    // p.496 안정된 인터페이스 만들기
    class Spreadsheet::Impl // 구현 클래스
    {
        std::string name;
        const size_t id{};
        size_t width{};
        size_t height{};
        inline static size_t sheet_counter{ 0 };
        SpreadsheetCell** cells{ nullptr };
        const SpreadsheetApplication& theApp;
        void verifyCoordinate(size_t x, size_t y) const;
    public:
        Impl(const SpreadsheetApplication& theApp, size_t width, size_t height);
        ~Impl();
        Impl(const Impl& src);
        Impl& operator=(const Impl& rhs);
        Impl& operator=(Impl&& rhs) noexcept;

        void swap(Impl& other) noexcept;
        static void swap(Impl& first, Impl& second) noexcept;
        [[nodiscard]] auto get_cells() -> SpreadsheetCell**&;
        void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell) const;
        [[nodiscard]] auto getCellAt(size_t x, size_t y) const->SpreadsheetCell&;
        [[nodiscard]] auto getId() const->size_t;
    };

    auto Spreadsheet::Impl::getId() const -> size_t { return id; }

    auto Spreadsheet::Impl::getCellAt(const size_t x, const size_t y) const -> SpreadsheetCell& {
        verifyCoordinate(x, y);
        return cells[x][y];
    }

    void Spreadsheet::Impl::setCellAt(const size_t x, const size_t y, const SpreadsheetCell& cell) const {
        verifyCoordinate(x, y);
        cells[x][y] = cell;
    }

    auto Spreadsheet::Impl::get_cells() -> SpreadsheetCell**& {
        return cells;
    }

    Spreadsheet::Impl::~Impl() {
        for (size_t i{ 0 }; i < width; ++i) {
            delete[] cells[i];
        }
        delete[] cells;
        cells = nullptr;
        width = height = 0;
    }

    void Spreadsheet::Impl::swap(Impl& other) noexcept {
        std::swap(this->name, other.name);
        std::swap(this->width, other.width);
        std::swap(this->height, other.height);
        std::swap(this->cells, other.cells);
    }

    void Spreadsheet::Impl::swap(Impl& first, Impl& second) noexcept {
        first.swap(second);
    }

    Spreadsheet::Impl& Spreadsheet::Impl::operator=(const Impl& rhs) {
        if (this == &rhs) { return *this; }
        Impl temp{ rhs };
        swap(temp);
        return *this;
    }

    Spreadsheet::Impl& Spreadsheet::Impl::operator=(Impl&& rhs) noexcept {
        swap(*this, rhs);
        return *this;
    }

    Spreadsheet::Impl::Impl(const Impl& src)
        : Impl(src.theApp, src.width, src.height)
    {
        for (size_t i{ 0 }; i < this->width; ++i) {
            for (size_t j{ 0 }; j < this->height; ++j) {
                this->cells[i][j] = src.cells[i][j];
            }
        }
    }

    void Spreadsheet::Impl::verifyCoordinate(const size_t x, const size_t y) const {
        if (x >= width) {
            throw std::out_of_range{ std::format("{} must be less than {}.", x, width) };
        }
        if (y >= height) {
            throw std::out_of_range{ std::format("{} must be less than {}.", y, height) };
        }
    }

    Spreadsheet::Impl::Impl(const SpreadsheetApplication& theApp, const size_t width, const size_t height)
        : id(sheet_counter++), width(std::min(width, MaxWidth)), height(std::min(height, MaxHeight)),
        theApp(theApp)
    {
        cells = new SpreadsheetCell * [this->width];
        for (size_t i{ 0 }; i < this->width; ++i) {
            cells[i] = new SpreadsheetCell[this->height];
        }
    }
    // 이동 대입 연산자
    Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept {
        if (debug1)
            cout << "move assignment operator: " << call_counter++ << endl;
        // if (this == &rhs) return *this;
        // cleanup(); // 현재 객체의 이전 메모리를 해제한다. 이것은 덮어쓰기에 의한 메모리 누수를 방지하기 위함이다.
        // moveFrom(rhs); // 소유권을 이전하고 원본 객체의 동적 할당된 cells 포인터를 nullptr로 할당하여
        // // 원본 객체의 소멸자가 원본 데이터를 해제하는걸 방지한다.
        *this->impl = std::move(*rhs.impl);
        return *this;
    }

    // Spreadsheet::Cell::Cell(const double initial_value)
    //    : value(initial_value) {}

    Spreadsheet::Spreadsheet(const Spreadsheet& src) {
        if (debug1)
            cout << "copy constructor: " << call_counter++ << endl;
        impl = std::make_unique<Impl>(*src.impl);
    }

    Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs) { // p.440
        if (debug1)
            cout << "copy assignment operator: " << call_counter++ << endl;
        *impl = *rhs.impl;
        return *this;
    }

    void Spreadsheet::swap(const Spreadsheet& other) const noexcept {
        // other
        impl->swap(*other.impl);
    }
    void Spreadsheet::swap(const Spreadsheet& first, const Spreadsheet& second) const noexcept {
        // second를 first로 swap한다.
        impl->swap(*first.impl, *second.impl);
    }

    Spreadsheet::Spreadsheet(const SpreadsheetApplication& theApp,
        const size_t width, const size_t height) {
        impl = make_unique<Impl>(theApp, width, height);
    }

    Spreadsheet::~Spreadsheet() {
        if (debug1)
            cout << "destructor: " << call_counter++ << endl;
        impl->~Impl();
    }

    void Spreadsheet::setCellAt(const size_t x, const size_t y, const SpreadsheetCell& cell) const {
        impl->setCellAt(x, y, cell);
    }
    auto Spreadsheet::getCellAt(const size_t x, const size_t y) -> SpreadsheetCell& {
        return const_cast<SpreadsheetCell&>(as_const(*this).getCellAt(x, y));
        // 먼저 *this(현재 객체)를 const 객체로 캐스팅한다. 그다음에 const 버전의 getCellAt()을 호출한다.
        // 그러면 리턴값으로 const SpreadsheetCell&가 리턴되는데, 이 값을 다시 const_cast를 이용해서
        // non-const SpreadsheetCell&으로 캐스팅해서 리턴한다. p.466
        // 이 방법은 스콧 마이어스가 제안한 방법이다.
    }

    // p.465 const 기반 오버로딩
    const SpreadsheetCell& Spreadsheet::getCellAt(const size_t x, const size_t y) const {
        return impl->getCellAt(x, y);
    }

    void Spreadsheet::set_debug1(const bool value) { debug1 = value; }
    auto Spreadsheet::get_debug1() -> bool { return debug1; }

    auto Spreadsheet::getId() const -> size_t { return impl->getId(); }

    // global function
    static SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs) {
        //return SpreadsheetCell{lhs.getValue() + rhs.getValue()};
        auto result{ lhs }; // p.489
        result += rhs;
        return result;
    }
    void swap(Spreadsheet& first, Spreadsheet& second) noexcept {
        first.swap(second);
    }
}