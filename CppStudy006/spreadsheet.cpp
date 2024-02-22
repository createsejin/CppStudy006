module spreadsheet;
import std;
using namespace std;
namespace spreadsheet01
{
    // p.496 ������ �������̽� �����
    class Spreadsheet::Impl // ���� Ŭ����
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
    // �̵� ���� ������
    Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept {
        if (debug1)
            cout << "move assignment operator: " << call_counter++ << endl;
        // if (this == &rhs) return *this;
        // cleanup(); // ���� ��ü�� ���� �޸𸮸� �����Ѵ�. �̰��� ����⿡ ���� �޸� ������ �����ϱ� �����̴�.
        // moveFrom(rhs); // �������� �����ϰ� ���� ��ü�� ���� �Ҵ�� cells �����͸� nullptr�� �Ҵ��Ͽ�
        // // ���� ��ü�� �Ҹ��ڰ� ���� �����͸� �����ϴ°� �����Ѵ�.
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
        // second�� first�� swap�Ѵ�.
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
        // ���� *this(���� ��ü)�� const ��ü�� ĳ�����Ѵ�. �״����� const ������ getCellAt()�� ȣ���Ѵ�.
        // �׷��� ���ϰ����� const SpreadsheetCell&�� ���ϵǴµ�, �� ���� �ٽ� const_cast�� �̿��ؼ�
        // non-const SpreadsheetCell&���� ĳ�����ؼ� �����Ѵ�. p.466
        // �� ����� ���� ���̾�� ������ ����̴�.
    }

    // p.465 const ��� �����ε�
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