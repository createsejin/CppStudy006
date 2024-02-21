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
        static constexpr size_t MaxHeight{ 100 };
        static constexpr size_t MaxWidth{ 100 };
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
        void setValue(int value) = delete; // p.467 명시적 오버로딩 제거
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
        [[nodiscard]] bool operator==(const SpreadsheetCell& rhs) const; // p.491 참조
        // p.491 C++20부터 도입된 비교 연산자 자동 지원. 이거 하나만 만들면 나머지 6가지 비교 연산자를 자동으로 만들어준다.
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
        // p.479 중첩 클래스
        class Cell;
    private:
        Cell** cells{ nullptr };
        const SpreadsheetApplication& theApp;
    public:
        //Spreadsheet() = default; // 디폴트 값이 정해진 생성자와 겹칠 수 있음.
        Spreadsheet(const Spreadsheet& src); // 복제 생성자
        Spreadsheet& operator=(const Spreadsheet& rhs); // 복제 대입 연산자
        //Spreadsheet(Spreadsheet&& src) noexcept; // 이동 생성자
        Spreadsheet& operator=(Spreadsheet&& rhs) noexcept; // 이동 대입 연산자
        void swap(Spreadsheet& other) noexcept;
        static void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
        explicit Spreadsheet(size_t width, size_t height,
            const SpreadsheetApplication& theApp);
        // ㄴ 여기에서 explicit을 붙이는 이유는 아마도 Spreadsheet s1 = 5나 Spreadsheet s2 = {5, 6}
        // 이런 암묵적 변환 때문에 그런것 같다. 이렇게 하면 Spreadsheed s3 {5}; 이런식으로만 써야한다.
        ~Spreadsheet();
        void setCellAt(size_t x, size_t y, const Cell& cell) const;
        //[[nodiscard]] auto getCellAt(size_t x, size_t y) -> SpreadsheetCell&;
        [[nodiscard]] auto getCellAt(size_t x, size_t y) -> Cell&;
        [[nodiscard]] auto getCellAt(size_t x, size_t y) const -> const Cell&;
        static void set_debug1(bool value);
        [[nodiscard]] static auto get_debug1() -> bool;
        [[nodiscard]] auto getId() const->size_t;
    };

    class Spreadsheet::Cell { // 중첩 클래스
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
        // 복제 생성자
        Cell(const Cell& src) = default;
        // 복사 대입 연산자 p.421
        Cell& operator=(const Cell& rhs) = default;

        // 단항 생성자 -> explicit 사용으로 명시적 호출
        explicit Cell(double initial_value);
        explicit Cell(std::string_view initial_value);
        void setValue(double value); // p.465 메서드 오버로딩
        void setValue(int value) = delete; // p.467 명시적 오버로딩 제거
        [[nodiscard]] inline double getValue() const;

        void setValue(std::string_view inString);
        [[nodiscard]] inline std::string getString() const;

        static void printCell(const Cell& cell);
        void printCell() const;
    };

    void study013();
}