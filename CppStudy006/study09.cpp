module study09;

using namespace std;

namespace study09::study001 {
    // ----------------------------------SpreadsheetCell----------------------------------------- //
    std::string SpreadsheetCell::doubleToString(const double value) {
        return to_string(value);
    }
    double SpreadsheetCell::stringToDouble(const std::string_view inString) {
        double number{ 0 };
        from_chars(inString.data(), inString.data() + inString.size(), number);
        return number;
    }

    SpreadsheetCell::SpreadsheetCell(const double initial_value) : value{ initial_value } {}
    SpreadsheetCell::SpreadsheetCell(const std::string_view initial_value) { setValue(initial_value); }

    void SpreadsheetCell::setValue(const double value) {
        this->value = value;
        printCell(*this);
    }
    double SpreadsheetCell::getValue() const {
        numAccesses++; // mutable keyword p.464
        return value;
    }

    void SpreadsheetCell::setValue(const std::string_view inString) { value = stringToDouble(inString); }
    std::string SpreadsheetCell::getString() const {
        numAccesses++;
        return doubleToString(value);
    }

    void SpreadsheetCell::printCell(const SpreadsheetCell& cell) {
        cout << cell.getString() << endl;
    }
    void SpreadsheetCell::printCell() const { cout << this->getString() << endl; }

    // --------------------------------Spreadsheet--------------------------------------------- //
    void Spreadsheet::verifyCoordinate(const size_t x, const size_t y) const {
        if (x >= width) {
            throw out_of_range{ std::format("{} must be less than {}.", x, width) };
        }
        if (y >= height) {
            throw out_of_range{ std::format("{} must be less than {}.", y, height) };
        }
    }

    // void Spreadsheet::cleanup() noexcept {
    //     for (size_t i{0}; i < width; ++i) {
    //         delete[] cells[i];
    //     }
    //     delete[] cells;
    //     cells = nullptr;
    //     width = height = 0;
    // }

    // void Spreadsheet::moveFrom(Spreadsheet& src) noexcept {
    //     // 객체 데이터 멤버를 이동시킬때에는 std::move를 이용해야한다. p.453
    //     this->name = std::move(src.name);
    //     // 데이터에 대한 얕은 복제
    //     // src.width를 0으로 바꾸고 기존 src.width값을 반환
    //     this->width = std::exchange(src.width, 0);
    //     this->height = std::exchange(src.height, 0);
    //     this->cells = std::exchange(src.cells, nullptr);
    //
    //     // 소유권이 이전되었기 때문에 원본 객체를 리셋한다.
    //     // src.width = 0;
    //     // src.height = 0;
    //     // src.cells = nullptr; // 이동 의미론에서 이동은 원본객체의 소멸을 의미하지는 않는다.
    //     // 단순히 원본 객체에 할당된 cells 포인터를 nullptr로 만들고 이동 시키는것.
    // }

    // 이동 생성자
    Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept {
        if (debug1)
            cout << "move constructor: " << call_counter++ << endl;
        // moveFrom(rhs);
        swap(*this, src); // p.453
        // 이렇게 단순히 객체를 뒤바꾸기만 해도 move가 가능한 이유는 이 이동 생성자 또는 이동 대입 연산자를 부를때
        // 우측값 레퍼런스 즉, rvalue 형식으로 부르기 때문에 원본 객체는 임시 객체가 되어 이동 후에는 유효하지 않게 된다.
        // 또한 std::move를 부를때에도 마찬가지다. 그래서 원본 객체인 src는 유효한 객체가 아니게 된다.
    }
    // 이동 대입 연산자
    Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept {
        if (debug1)
            cout << "move assignment operator: " << call_counter++ << endl;
        // if (this == &rhs) return *this;
        // cleanup(); // 현재 객체의 이전 메모리를 해제한다. 이것은 덮어쓰기에 의한 메모리 누수를 방지하기 위함이다.
        // moveFrom(rhs); // 소유권을 이전하고 원본 객체의 동적 할당된 cells 포인터를 nullptr로 할당하여
        // // 원본 객체의 소멸자가 원본 데이터를 해제하는걸 방지한다.
        swap(*this, rhs);
        return *this;
    }

    Spreadsheet::Spreadsheet(const Spreadsheet& src) : Spreadsheet(src.width, src.height) {
        if (debug1)
            cout << "copy constructor: " << call_counter++ << endl;
        for (size_t i{ 0 }; i < this->width; ++i) {
            for (size_t j{ 0 }; j < this->height; ++j) {
                this->cells[i][j] = src.cells[i][j];
            }
        }
    }

    Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs) { // p.440
        if (debug1)
            cout << "copy assignment operator: " << call_counter++ << endl;
        /*// 자신을 대입하는지 확인
        if (this == &rhs) {
            return *this;
        }

        // 기존 메모리를 해제
        for (size_t i{0}; i < this->width; ++i) {
            delete[] this->cells[i];
        }
        delete[] this->cells;
        this->cells = nullptr;

        //메모리를 새로 할당
        this->width = rhs.width;
        this->height = rhs.height;
        this->cells = new SpreadsheetCell*[this->width];
        for (size_t i{0}; i < this->width; ++i) {
            this->cells[i] = new SpreadsheetCell[this->height];
        }

        // 데이터 복제
        for (size_t i{0}; i < this->width; ++i) {
            for (size_t j{0}; j < this->height; ++j) {
                this->cells[i][j] = rhs.cells[i][j];
            }
        }
        return *this;*/

        // swap을 이용
        if (this == &rhs) { return *this; }
        Spreadsheet temp{ rhs };
        swap(temp); // 이때 swap이 되면 임시 객체가 제거된다.
        return *this;
    }

    void Spreadsheet::swap(Spreadsheet& other) noexcept {
        // other
        std::swap(this->name, other.name);
        std::swap(this->width, other.width);
        std::swap(this->height, other.height);
        std::swap(this->cells, other.cells);
    }
    void Spreadsheet::swap(Spreadsheet& first, Spreadsheet& second) noexcept {
        // second를 first로 swap한다.
        first.swap(second);
    }

    Spreadsheet::Spreadsheet(const size_t width, const size_t height)
        : width(width), height(height) {
        if (debug1)
            cout << "normal constructor: " << call_counter++ << endl;
        this->cells = new SpreadsheetCell * [this->width];
        for (size_t i{ 0 }; i < this->width; ++i) {
            this->cells[i] = new SpreadsheetCell[this->height];
        }
    }

    Spreadsheet::~Spreadsheet() {
        if (debug1)
            cout << "destructor: " << call_counter++ << endl;
        for (size_t i{ 0 }; i < width; ++i) {
            delete[] cells[i];
        }
        delete[] cells;
        cells = nullptr;
        width = height = 0;
    }

    void Spreadsheet::setCellAt(const size_t x, const size_t y, const SpreadsheetCell& cell) const {
        verifyCoordinate(x, y);
        this->cells[x][y] = cell;
    }
    auto Spreadsheet::getCellAt(const size_t x, const size_t y) -> SpreadsheetCell& {
        return const_cast<SpreadsheetCell&>(as_const(*this).getCellAt(x, y));
        // 먼저 *this(현재 객체)를 const 객체로 캐스팅한다. 그다음에 const 버전의 getCellAt()을 호출한다.
        // 그러면 리턴값으로 const SpreadsheetCell&가 리턴되는데, 이 값을 다시 const_cast를 이용해서
        // non-const SpreadsheetCell&으로 캐스팅해서 리턴한다. p.466
    }
    // p.465 const 기반 오버로딩
    auto Spreadsheet::getCellAt(const size_t x, const size_t y) const -> const SpreadsheetCell& {
        verifyCoordinate(x, y);
        return cells[x][y];
    }

    void Spreadsheet::set_debug1(const bool value) { debug1 = value; }
    auto Spreadsheet::get_debug1() -> bool { return debug1; }

    // ----------------------------------------------------------------------------------------- //

    void helper(std::string&& message) {
        cout << std::format("handleMessage with rvalue reference: {}", message) << endl;
    }
    void handleMessage(const string& message) {
        cout << std::format("handleMessage with lvalue reference: {}", message) << endl;
    }
    void handleMessage(string&& message) {
        //helper(message); // 이렇게 하면 함수의 매개변수인 string&& message는 매개변수일때에는 엄밀히는 lvalue이기 때문에
        // rvalue를 받는 helper 함수에 message를 전달하면 컴파일 오류가 발생한다.
        // 따라서 다음과 같이 std::move를 이용해서 lvalue를 rvalue로 캐스팅 해야한다.
        helper(std::move(message));
    }
    // p.446 우측값 레퍼런스
    void study001() {
        const string a{ "Hello " };
        handleMessage(a); // lvalue handleMessage call
        string b{ "World!" };
        handleMessage(a + b); // rvalue handleMessage call
        handleMessage("Hello world!!"); // rvalue handleMessage call
        handleMessage(std::move(b)); // rvalue handleMessage call
        // ㄴ 이것은 b가 lvalue인데 std::move를 이용해서 lvalue를 rvalue로 캐스팅 했기 때문에
        // rvalue 함수가 호출된다.
        //handleMessage(std::move(a)); // 이거는 const라서 move를 써도 그냥 복제되버린다. 즉, move의 효과가 아예 없는샘이 된다.
        // 즉, 이 때에는 그냥 handleMessage(a)를 해서 좌측값(lvalue) 레퍼런스를 받는 함수를 써야한다.
    }
    void study002() {
        // p.449
        //int& i {2}; // Non-const lvalue reference 'i' to type int cannot bind to rvalue of type int
        int&& i{ 2 };
        cout << i << endl;
        constexpr int a{ 2 }, b{ 3 };
        //int& j {a + b}; // Non-const lvalue reference 'j' to type int cannot bind to rvalue of type int
        int&& j{ a + b };
        cout << j << endl;
    }

    // p.452 std::exchange()
    void study003() {
        int a{ 11 };
        int b{ 22 };
        cout << std::format("Before exchange(): a = {}, b = {}", a, b) << endl;
        // a를 b로 바꾸고 기존 값인 a값을 반환한다.
        int returnedValue = { std::exchange(a, b) };
        cout << std::format("After exchange(): a = {}, b = {}", a, b) << endl;
        cout << std::format("exchange() returned = {}", returnedValue) << endl;
    }

    //p.454 Spreadsheet의 이동 연산자 테스트하기
    Spreadsheet createObject() {
        return Spreadsheet{ 3, 2 };
    }
    void study004() {
        std::vector<Spreadsheet> vec;
        for (size_t i{ 0 }; i < 2; ++i) {
            cout << "Iteration: " << i << endl;
            vec.push_back(Spreadsheet{ 100, 100 }); // NOLINT(*-use-emplace)
            // ㄴ 처음 Spreadsheet 객체를 생성하면 normal constructor(0)가 호출되고 이것을 vector로 옮기기 위해
            // move constructor(1)가 호출되고, move에 의해 기존 객체는 삭제된다(2).
            // 그 후, 두번째 iteration에서는 또다시 normal constructor(3)가 호출되어
            // 새로운 객체가 생성되고, vector의 크기가 변경되었기 때문에 새로운 vector로 기존 원소를 옮기기 위해
            // move constructor(4)가 호출되고, 또한, 새로운 객체를 그 벡터로 이동시키기 위해 move constructor(5)가 호출된다.
            // 이들은 move이기 때문에 기존 객체는 삭제된다. (5), (6)
        }

        Spreadsheet s{ 2, 3 }; // normal constructor(8)
        s = createObject(); // 먼저 create..에 의해 임시 객체가 생성되고(9), 이것은 임시 객체이며 rvalue이기 때문에
        // move assignment operator(10)가 호출된다. 그리고 임시 객체는 삭제된다(11).

        // ReSharper disable once CppEntityAssignedButNoRead
        Spreadsheet s2{ 5, 6 }; // normal constructor(12)
        // ReSharper disable once CppDFAUnusedValue
        s2 = s; // 여기에서는 s2는 이름있는 lvalue이기 때문에 copy assignment operator(13)가 호출된다.
        // copy assignment operator(13)가 호출되면서 내부적으로 임시 객체가 생성(14)되고,
        // swap에 의해 copy constructor(15)가 호출된다. 그리고 임시 객체는 삭제된다(16).

        // 그리고 스코프를 벗어나면 vector에 담긴 객체 두 개와, 마지막에 생긴 s와 s2가 삭제된다. (17), (18), (19), (20)
    }

    // p.457 이동 의미론으로 swap 함수 구현하기
    template <typename T> // 이동 의미론 미적용
    void swapCopy(T& a, T& b) {
        T temp{ a };
        a = b;
        b = temp;
    }
    template <typename T>
    void swapMove(T& a, T& b) {
        T temp{ std::move(a) };
        a = std::move(b);
        b = std::move(temp);
    } // 표준 라이브러리의 std::swap이 이런 식으로 구현되었다.

    // p.459 함수에 인수를 전달하는 최적의 방법
    class DataHolder {
        std::vector<int> data;
    public:
        // void setData(const std::vector<int>& data) {
        //     cout << "lvalue type" << endl;
        //     this->data = data; // 데이터 복제
        // } // lvalue type argment
        // void setData(std::vector<int>&& data) {
        //     cout << "rvalue type" << endl;
        //     this->data = std::move(data); // 데이터 이동
        // } // rvalue type argment
        void setData(std::vector<int> data) { this->data = std::move(data); }
    };

    void study005() {
        DataHolder wrapper;
        const std::vector myData{ 11, 22, 33 };
        wrapper.setData(myData); // lvalue type
        wrapper.setData({ 22, 33, 44 }); // rvalue type
    }

    // p.463 const 메서드
    void study006() {
        SpreadsheetCell myCell{ 5 };
        cout << myCell.getValue() << endl;
        myCell.setValue("6");

        const SpreadsheetCell myCellConstRef{ myCell };
        cout << myCellConstRef.getValue() << endl;
        //myCellConstRef.setString("6");
        // ㄴ Cannot convert this argument from type const SpreadsheetCell to type SpreadsheetCell:
        // function is missing const qualifier
        // 이말은 현재 const 타입인 SpreadsheetCell 객체에 대해서 non-const 메서드인 setString() 메서드를 불렀다는 것이다.
        // 즉, const 객체에 대해서는 반드시 const 메서드만을 호출할 수 있다는 것이다.
    }

    // p.466 const 기반 메서드 오버로딩
    void study007() {
        auto* sheet1_ptr{ new Spreadsheet(5, 6) };
        [[maybe_unused]] auto& cell1{ sheet1_ptr->getCellAt(1, 1) };
        // ㄴ non-const getCellAt 메서드 호출
        delete sheet1_ptr;
        // ReSharper disable once CppDFAUnusedValue
        sheet1_ptr = nullptr;

        const Spreadsheet sheet2{ 5, 6 };
        [[maybe_unused]] const auto& cell2{ sheet2.getCellAt(1, 1) };
        // ㄴ const getCellAt 메서드 호출
    }

    // p.468 참조 한정 메서드(ref_qualified method)
    class TextHolder {
        std::string text;
    public:
        explicit TextHolder(std::string text) : text(std::move(text)) {}
        [[nodiscard]] auto getText() const& -> const string& { // 정식 인스턴스(lvalue)에 대해서만 호출하도록 하는 & 한정자
            cout << "lvalue reference qualified method call" << endl;
            return text;
        }
        [[nodiscard]] auto getText() && -> string&& { // 임시 인스턴스(rvalue)에 대해서만 호출하도록 하는 && 한정자
            cout << "rvalue reference qualified method call" << endl;
            return std::move(text);
        }
    };
    void study008() {
        TextHolder text_holder{ "Hello World!" };
        // 정식 인스턴스에 대한 getText() 호출
        cout << text_holder.getText() << endl; // lvalue reference qualified method call
        // 임시 인스턴스에 대한 getText() 호출
        cout << TextHolder{ "Hello World!" }.getText() << endl; // rvalue reference qualified method call
        cout << std::move(text_holder).getText() << endl; // rvalue reference qualified method call
    } // p.469 부터 시작
}