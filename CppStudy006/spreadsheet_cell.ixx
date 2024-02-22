export module spreadsheet_cell;
import std;

export namespace spreadsheet01
{
    class SpreadsheetCell {
    public:
        enum class Color { Red = 1, Green, Blue, Yellow }; // p.481
        void setColor(Color color);
        auto getColor() const->Color;
    private:
        double value{};
        mutable size_t numAccesses{ 0 };
        Color color{ Color::Red };
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
        // 만약 연산자 사용으로 인해 암묵적 변환 생성자를 사용하려면 explicit을 붙이지 말아야한다.
        // 암묵적 변환은 성능이 떨어질 수 있어서 되도록 피하게 하는것 같다.
        // ReSharper disable once CppNonExplicitConvertingConstructor
        SpreadsheetCell(double initial_value); // NOLINT(*-explicit-constructor)
        // ReSharper disable once CppNonExplicitConvertingConstructor
        SpreadsheetCell(std::string_view initial_value); // NOLINT(*-explicit-constructor)
        void setValue(double value); // p.465 메서드 오버로딩
        //void setValue(int value); // p.467 명시적 오버로딩 제거
        [[nodiscard]] double getValue() const;

        void setValue(std::string_view inString);
        [[nodiscard]] std::string getString() const;

        static void printCell(const SpreadsheetCell& cell);
        void printCell() const;

        SpreadsheetCell add(const SpreadsheetCell& cell) const;
        //SpreadsheetCell operator+(const SpreadsheetCell& cell) const;
        SpreadsheetCell operator+(double rhs) const;
        SpreadsheetCell operator/(const SpreadsheetCell& cell) const;
        SpreadsheetCell operator-(const SpreadsheetCell& cell) const;
        SpreadsheetCell operator*(const SpreadsheetCell& cell) const;

        SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
        SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
        SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
        SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);
        [[nodiscard]] bool operator==(const SpreadsheetCell& rhs) const = default; // p.491 참조
        // p.491 C++20부터 도입된 비교 연산자 자동 지원. 이거 하나만 만들면 나머지 6가지 비교 연산자를 자동으로 만들어준다.
        [[nodiscard]] std::partial_ordering operator<=>(const SpreadsheetCell& rhs) const = default;
    };
}