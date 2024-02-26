module;
#include <memory>
export module spreadsheet;

export import spreadsheet_cell;


namespace spreadsheet01
{
    export class SpreadsheetApplication {};

    export class Spreadsheet { // �������̽� Ŭ����
        inline static bool debug1{ false };
        inline static unsigned int call_counter{ 0 };
        inline static size_t sheet_counter{ 0 };
        //const size_t id;
        static constexpr size_t MaxHeight{ 100 };
        static constexpr size_t MaxWidth{ 100 };
        //SpreadsheetCell** cells{ nullptr };
        //const SpreadsheetApplication& theApp;
        class Impl; // ���漱��
        std::unique_ptr<Impl> impl;
    public:
        explicit Spreadsheet(const SpreadsheetApplication& theApp, size_t width, size_t height);
        // �� ���⿡�� explicit�� ���̴� ������ �Ƹ��� Spreadsheet s1 = 5�� Spreadsheet s2 = {5, 6}
        // �̷� �Ϲ��� ��ȯ ������ �׷��� ����. �̷��� �ϸ� Spreadsheed s3 {5}; �̷������θ� ����Ѵ�.
        ~Spreadsheet();
        //Spreadsheet() = default; // ����Ʈ ���� ������ �����ڿ� ��ĥ �� ����.
        Spreadsheet(const Spreadsheet& src); // ���� ������
        Spreadsheet& operator=(const Spreadsheet& rhs); // ���� ���� ������
        //Spreadsheet(Spreadsheet&& src) noexcept; // �̵� ������
        Spreadsheet& operator=(Spreadsheet&& rhs) noexcept; // �̵� ���� ������
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

