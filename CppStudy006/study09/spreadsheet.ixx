module;
#include <memory>
export module spreadsheet;

export import spreadsheet_cell;


namespace spreadsheet01
{
    export class SpreadsheetApplication {};

    export class Spreadsheet { // 인터페이스 클래스
        inline static bool debug1{ false };
        inline static unsigned int call_counter{ 0 };
        inline static size_t sheet_counter{ 0 };
        //const size_t id;
        static constexpr size_t MaxHeight{ 100 };
        static constexpr size_t MaxWidth{ 100 };
        //SpreadsheetCell** cells{ nullptr };
        //const SpreadsheetApplication& theApp;
        class Impl; // 전방선언
        std::unique_ptr<Impl> impl;
    public:
        explicit Spreadsheet(const SpreadsheetApplication& theApp, size_t width, size_t height);
        // ㄴ 여기에서 explicit을 붙이는 이유는 아마도 Spreadsheet s1 = 5나 Spreadsheet s2 = {5, 6}
        // 이런 암묵적 변환 때문에 그런것 같다. 이렇게 하면 Spreadsheed s3 {5}; 이런식으로만 써야한다.
        ~Spreadsheet();
        //Spreadsheet() = default; // 디폴트 값이 정해진 생성자와 겹칠 수 있음.
        Spreadsheet(const Spreadsheet& src); // 복제 생성자
        Spreadsheet& operator=(const Spreadsheet& rhs); // 복제 대입 연산자
        //Spreadsheet(Spreadsheet&& src) noexcept; // 이동 생성자
        Spreadsheet& operator=(Spreadsheet&& rhs) noexcept; // 이동 대입 연산자
        void swap(const Spreadsheet& other) const noexcept;
        void swap(const Spreadsheet& first, const Spreadsheet& second) const noexcept;


        void setCellAt(size_t x, size_t y, const SpreadsheetCell& cell) const;
        //[[nodiscard]] auto getCellAt(size_t x, size_t y) -> SpreadsheetCell&;
        [[nodiscard]] auto getCellAt(size_t x, size_t y) -> SpreadsheetCell&;
        [[nodiscard]] const SpreadsheetCell& getCellAt(size_t x, size_t y) const;
        static void set_debug1(bool value);
        [[nodiscard]] static auto get_debug1() -> bool;
        [[nodiscard]] auto getId() const->size_t;
    };

    export void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
}

