export module study09;
import std;

export namespace study09::study01 {
    class SpreadsheetCell {
        double value{};
        mutable size_t numAccesses{ 0 };
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
        explicit SpreadsheetCell(double initial_value);
        explicit SpreadsheetCell(std::string_view initial_value);
        void setValue(double value); // p.465 �޼��� �����ε�
        void setValue(int value) = delete; // p.467 ����� �����ε� ����
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
        static constexpr size_t MaxHeight{ 100 };
        static constexpr size_t MaxWidth{ 100 };
        SpreadsheetCell** cells{ nullptr };
        // void cleanup() noexcept;
        // void moveFrom(Spreadsheet& src) noexcept;
    public:
        Spreadsheet() = default;
        Spreadsheet(const Spreadsheet& src); // ���� ������
        Spreadsheet& operator=(const Spreadsheet& rhs); // ���� ���� ������
        Spreadsheet(Spreadsheet&& src) noexcept; // �̵� ������
        Spreadsheet& operator=(Spreadsheet&& rhs) noexcept; // �̵� ���� ������
        void swap(Spreadsheet& other) noexcept;
        static void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
        Spreadsheet(size_t width = 100, size_t height = 100);
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
    void study009();
}

export namespace study09::study02
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
        void setValue(int value) = delete; // p.467 ����� �����ε� ����
        [[nodiscard]] inline double getValue() const;

        void setValue(std::string_view inString);
        [[nodiscard]] inline std::string getString() const;

        static void printCell(const SpreadsheetCell& cell);
        void printCell() const;

        auto add(const SpreadsheetCell& cell) const->SpreadsheetCell;
        //SpreadsheetCell operator+(const SpreadsheetCell& cell) const;
        SpreadsheetCell operator+(double rhs) const;
        SpreadsheetCell operator/(const SpreadsheetCell& cell) const;
        SpreadsheetCell operator-(const SpreadsheetCell& cell) const;
        SpreadsheetCell operator*(const SpreadsheetCell& cell) const;

        SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
        SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
        SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
        SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);
        [[nodiscard]] bool operator==(const SpreadsheetCell& rhs) const; // p.491 ����
        // p.491 C++20���� ���Ե� �� ������ �ڵ� ����. �̰� �ϳ��� ����� ������ 6���� �� �����ڸ� �ڵ����� ������ش�.
        [[nodiscard]] std::partial_ordering operator<=>(const SpreadsheetCell& rhs) const;
    };

    class SpreadsheetApplication {};

    class Spreadsheet {
        inline static bool debug1{ false };
        inline static unsigned int call_counter{ 0 };
        inline static size_t sheet_counter{ 0 };
        void verifyCoordinate(size_t x, size_t y) const;
        const size_t id;
        std::string name;
        size_t width{ 0 };
        size_t height{ 0 };
        static constexpr size_t MaxHeight{ 100 };
        static constexpr size_t MaxWidth{ 100 };
    public:
        // p.479 ��ø Ŭ����
        class Cell;
    private:
        Cell** cells{ nullptr };
        const SpreadsheetApplication& theApp;
    public:
        //Spreadsheet() = default; // ����Ʈ ���� ������ �����ڿ� ��ĥ �� ����.
        Spreadsheet(const Spreadsheet& src); // ���� ������
        Spreadsheet& operator=(const Spreadsheet& rhs); // ���� ���� ������
        //Spreadsheet(Spreadsheet&& src) noexcept; // �̵� ������
        Spreadsheet& operator=(Spreadsheet&& rhs) noexcept; // �̵� ���� ������
        void swap(Spreadsheet& other) noexcept;
        static void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
        explicit Spreadsheet(size_t width, size_t height,
            const SpreadsheetApplication& theApp);
        // �� ���⿡�� explicit�� ���̴� ������ �Ƹ��� Spreadsheet s1 = 5�� Spreadsheet s2 = {5, 6}
        // �̷� �Ϲ��� ��ȯ ������ �׷��� ����. �̷��� �ϸ� Spreadsheed s3 {5}; �̷������θ� ����Ѵ�.
        ~Spreadsheet();
        void setCellAt(size_t x, size_t y, const Cell& cell) const;
        //[[nodiscard]] auto getCellAt(size_t x, size_t y) -> SpreadsheetCell&;
        [[nodiscard]] auto getCellAt(size_t x, size_t y) -> Cell&;
        [[nodiscard]] auto getCellAt(size_t x, size_t y) const -> const Cell&;
        static void set_debug1(bool value);
        [[nodiscard]] static auto get_debug1() -> bool;
        [[nodiscard]] auto getId() const->size_t;
    };

    class Spreadsheet::Cell { // ��ø Ŭ����
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
        Cell() = default;
        ~Cell() = default;
        // ���� ������
        Cell(const Cell& src) = default;
        // ���� ���� ������ p.421
        Cell& operator=(const Cell& rhs) = default;

        // ���� ������ -> explicit ������� ����� ȣ��
        explicit Cell(double initial_value);
        explicit Cell(std::string_view initial_value);
        void setValue(double value); // p.465 �޼��� �����ε�
        void setValue(int value) = delete; // p.467 ����� �����ε� ����
        [[nodiscard]] inline double getValue() const;

        void setValue(std::string_view inString);
        [[nodiscard]] inline std::string getString() const;

        static void printCell(const Cell& cell);
        void printCell() const;
    };

    void study013();
}