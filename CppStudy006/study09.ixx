export module study09;
import std;

export namespace study09::study001 {
    class SpreadsheetCell {
        double value{};
        mutable size_t numAccesses{ 0 };
        [[nodiscard]] static std::string doubleToString(double value);
        [[nodiscard]] static double stringToDouble(std::string_view inString);
    public:
        SpreadsheetCell() = default;
        ~SpreadsheetCell() = default;
        // 복제 생성자
        SpreadsheetCell(const SpreadsheetCell& src) = default;
        // 복사 대입 연산자 p.421
        SpreadsheetCell& operator=(const SpreadsheetCell& rhs) = default;

        // 단항 생성자 -> explicit 사용으로 명시적 호출
        explicit SpreadsheetCell(double initial_value);
        explicit SpreadsheetCell(std::string_view initial_value);
        void setValue(double value); // p.465 메서드 오버로딩
        void setValue(int value) = delete; // p.467 명시적 오버로딩 제거
        [[nodiscard]] double getValue() const;

        void setValue(std::string_view inString);
        [[nodiscard]] inline std::string getString() const;

        static void printCell(const SpreadsheetCell& cell);
        void printCell() const;
    };


    class Spreadsheet {
        inline static bool debug1{ false };
        inline static unsigned int call_counter{ 0 };
        void verifyCoordinate(size_t x, size_t y) const;
        std::string name;
        size_t width{ 0 };
        size_t height{ 0 };
        SpreadsheetCell** cells{ nullptr };
        // void cleanup() noexcept;
        // void moveFrom(Spreadsheet& src) noexcept;
    public:
        Spreadsheet() = default;
        Spreadsheet(const Spreadsheet& src); // 복제 생성자
        Spreadsheet& operator=(const Spreadsheet& rhs); // 복제 대입 연산자
        Spreadsheet(Spreadsheet&& src) noexcept; // 이동 생성자
        Spreadsheet& operator=(Spreadsheet&& rhs) noexcept; // 이동 대입 연산자
        void swap(Spreadsheet& other) noexcept;
        static void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
        Spreadsheet(size_t width, size_t height);
        ~Spreadsheet();
        void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell) const;
        [[nodiscard]] auto getCellAt(size_t x, size_t y) -> SpreadsheetCell&;
        [[nodiscard]] auto getCellAt(size_t x, size_t y) const -> const SpreadsheetCell&;
        static void set_debug1(bool value);
        [[nodiscard]] static auto get_debug1() -> bool;
    };

    void study001();
    void study003();
    void study004();
    void study005();
    void study008();
}