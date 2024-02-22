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
        // ���� ������
        SpreadsheetCell(const SpreadsheetCell& src) = default;
        // ���� ���� ������ p.421
        SpreadsheetCell& operator=(const SpreadsheetCell& rhs) = default;

        // ���� ������ -> explicit ������� ����� ȣ��
        // ���� ������ ������� ���� �Ϲ��� ��ȯ �����ڸ� ����Ϸ��� explicit�� ������ ���ƾ��Ѵ�.
        // �Ϲ��� ��ȯ�� ������ ������ �� �־ �ǵ��� ���ϰ� �ϴ°� ����.
        // ReSharper disable once CppNonExplicitConvertingConstructor
        SpreadsheetCell(double initial_value); // NOLINT(*-explicit-constructor)
        // ReSharper disable once CppNonExplicitConvertingConstructor
        SpreadsheetCell(std::string_view initial_value); // NOLINT(*-explicit-constructor)
        void setValue(double value); // p.465 �޼��� �����ε�
        //void setValue(int value); // p.467 ����� �����ε� ����
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
        [[nodiscard]] bool operator==(const SpreadsheetCell& rhs) const = default; // p.491 ����
        // p.491 C++20���� ���Ե� �� ������ �ڵ� ����. �̰� �ϳ��� ����� ������ 6���� �� �����ڸ� �ڵ����� ������ش�.
        [[nodiscard]] std::partial_ordering operator<=>(const SpreadsheetCell& rhs) const = default;
    };
}