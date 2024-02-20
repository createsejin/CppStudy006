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
    //     // ��ü ������ ����� �̵���ų������ std::move�� �̿��ؾ��Ѵ�. p.453
    //     this->name = std::move(src.name);
    //     // �����Ϳ� ���� ���� ����
    //     // src.width�� 0���� �ٲٰ� ���� src.width���� ��ȯ
    //     this->width = std::exchange(src.width, 0);
    //     this->height = std::exchange(src.height, 0);
    //     this->cells = std::exchange(src.cells, nullptr);
    //
    //     // �������� �����Ǿ��� ������ ���� ��ü�� �����Ѵ�.
    //     // src.width = 0;
    //     // src.height = 0;
    //     // src.cells = nullptr; // �̵� �ǹ̷п��� �̵��� ������ü�� �Ҹ��� �ǹ������� �ʴ´�.
    //     // �ܼ��� ���� ��ü�� �Ҵ�� cells �����͸� nullptr�� ����� �̵� ��Ű�°�.
    // }

    // �̵� ������
    Spreadsheet::Spreadsheet(Spreadsheet&& src) noexcept {
        if (debug1)
            cout << "move constructor: " << call_counter++ << endl;
        // moveFrom(rhs);
        swap(*this, src); // p.453
        // �̷��� �ܼ��� ��ü�� �ڹٲٱ⸸ �ص� move�� ������ ������ �� �̵� ������ �Ǵ� �̵� ���� �����ڸ� �θ���
        // ������ ���۷��� ��, rvalue �������� �θ��� ������ ���� ��ü�� �ӽ� ��ü�� �Ǿ� �̵� �Ŀ��� ��ȿ���� �ʰ� �ȴ�.
        // ���� std::move�� �θ������� ����������. �׷��� ���� ��ü�� src�� ��ȿ�� ��ü�� �ƴϰ� �ȴ�.
    }
    // �̵� ���� ������
    Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept {
        if (debug1)
            cout << "move assignment operator: " << call_counter++ << endl;
        // if (this == &rhs) return *this;
        // cleanup(); // ���� ��ü�� ���� �޸𸮸� �����Ѵ�. �̰��� ����⿡ ���� �޸� ������ �����ϱ� �����̴�.
        // moveFrom(rhs); // �������� �����ϰ� ���� ��ü�� ���� �Ҵ�� cells �����͸� nullptr�� �Ҵ��Ͽ�
        // // ���� ��ü�� �Ҹ��ڰ� ���� �����͸� �����ϴ°� �����Ѵ�.
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
        /*// �ڽ��� �����ϴ��� Ȯ��
        if (this == &rhs) {
            return *this;
        }

        // ���� �޸𸮸� ����
        for (size_t i{0}; i < this->width; ++i) {
            delete[] this->cells[i];
        }
        delete[] this->cells;
        this->cells = nullptr;

        //�޸𸮸� ���� �Ҵ�
        this->width = rhs.width;
        this->height = rhs.height;
        this->cells = new SpreadsheetCell*[this->width];
        for (size_t i{0}; i < this->width; ++i) {
            this->cells[i] = new SpreadsheetCell[this->height];
        }

        // ������ ����
        for (size_t i{0}; i < this->width; ++i) {
            for (size_t j{0}; j < this->height; ++j) {
                this->cells[i][j] = rhs.cells[i][j];
            }
        }
        return *this;*/

        // swap�� �̿�
        if (this == &rhs) { return *this; }
        Spreadsheet temp{ rhs };
        swap(temp); // �̶� swap�� �Ǹ� �ӽ� ��ü�� ���ŵȴ�.
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
        // second�� first�� swap�Ѵ�.
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
        // ���� *this(���� ��ü)�� const ��ü�� ĳ�����Ѵ�. �״����� const ������ getCellAt()�� ȣ���Ѵ�.
        // �׷��� ���ϰ����� const SpreadsheetCell&�� ���ϵǴµ�, �� ���� �ٽ� const_cast�� �̿��ؼ�
        // non-const SpreadsheetCell&���� ĳ�����ؼ� �����Ѵ�. p.466
    }
    // p.465 const ��� �����ε�
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
        //helper(message); // �̷��� �ϸ� �Լ��� �Ű������� string&& message�� �Ű������϶����� �������� lvalue�̱� ������
        // rvalue�� �޴� helper �Լ��� message�� �����ϸ� ������ ������ �߻��Ѵ�.
        // ���� ������ ���� std::move�� �̿��ؼ� lvalue�� rvalue�� ĳ���� �ؾ��Ѵ�.
        helper(std::move(message));
    }
    // p.446 ������ ���۷���
    void study001() {
        const string a{ "Hello " };
        handleMessage(a); // lvalue handleMessage call
        string b{ "World!" };
        handleMessage(a + b); // rvalue handleMessage call
        handleMessage("Hello world!!"); // rvalue handleMessage call
        handleMessage(std::move(b)); // rvalue handleMessage call
        // �� �̰��� b�� lvalue�ε� std::move�� �̿��ؼ� lvalue�� rvalue�� ĳ���� �߱� ������
        // rvalue �Լ��� ȣ��ȴ�.
        //handleMessage(std::move(a)); // �̰Ŵ� const�� move�� �ᵵ �׳� �����ǹ�����. ��, move�� ȿ���� �ƿ� ���»��� �ȴ�.
        // ��, �� ������ �׳� handleMessage(a)�� �ؼ� ������(lvalue) ���۷����� �޴� �Լ��� ����Ѵ�.
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
        // a�� b�� �ٲٰ� ���� ���� a���� ��ȯ�Ѵ�.
        int returnedValue = { std::exchange(a, b) };
        cout << std::format("After exchange(): a = {}, b = {}", a, b) << endl;
        cout << std::format("exchange() returned = {}", returnedValue) << endl;
    }

    //p.454 Spreadsheet�� �̵� ������ �׽�Ʈ�ϱ�
    Spreadsheet createObject() {
        return Spreadsheet{ 3, 2 };
    }
    void study004() {
        std::vector<Spreadsheet> vec;
        for (size_t i{ 0 }; i < 2; ++i) {
            cout << "Iteration: " << i << endl;
            vec.push_back(Spreadsheet{ 100, 100 }); // NOLINT(*-use-emplace)
            // �� ó�� Spreadsheet ��ü�� �����ϸ� normal constructor(0)�� ȣ��ǰ� �̰��� vector�� �ű�� ����
            // move constructor(1)�� ȣ��ǰ�, move�� ���� ���� ��ü�� �����ȴ�(2).
            // �� ��, �ι�° iteration������ �Ǵٽ� normal constructor(3)�� ȣ��Ǿ�
            // ���ο� ��ü�� �����ǰ�, vector�� ũ�Ⱑ ����Ǿ��� ������ ���ο� vector�� ���� ���Ҹ� �ű�� ����
            // move constructor(4)�� ȣ��ǰ�, ����, ���ο� ��ü�� �� ���ͷ� �̵���Ű�� ���� move constructor(5)�� ȣ��ȴ�.
            // �̵��� move�̱� ������ ���� ��ü�� �����ȴ�. (5), (6)
        }

        Spreadsheet s{ 2, 3 }; // normal constructor(8)
        s = createObject(); // ���� create..�� ���� �ӽ� ��ü�� �����ǰ�(9), �̰��� �ӽ� ��ü�̸� rvalue�̱� ������
        // move assignment operator(10)�� ȣ��ȴ�. �׸��� �ӽ� ��ü�� �����ȴ�(11).

        // ReSharper disable once CppEntityAssignedButNoRead
        Spreadsheet s2{ 5, 6 }; // normal constructor(12)
        // ReSharper disable once CppDFAUnusedValue
        s2 = s; // ���⿡���� s2�� �̸��ִ� lvalue�̱� ������ copy assignment operator(13)�� ȣ��ȴ�.
        // copy assignment operator(13)�� ȣ��Ǹ鼭 ���������� �ӽ� ��ü�� ����(14)�ǰ�,
        // swap�� ���� copy constructor(15)�� ȣ��ȴ�. �׸��� �ӽ� ��ü�� �����ȴ�(16).

        // �׸��� �������� ����� vector�� ��� ��ü �� ����, �������� ���� s�� s2�� �����ȴ�. (17), (18), (19), (20)
    }

    // p.457 �̵� �ǹ̷����� swap �Լ� �����ϱ�
    template <typename T> // �̵� �ǹ̷� ������
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
    } // ǥ�� ���̺귯���� std::swap�� �̷� ������ �����Ǿ���.

    // p.459 �Լ��� �μ��� �����ϴ� ������ ���
    class DataHolder {
        std::vector<int> data;
    public:
        // void setData(const std::vector<int>& data) {
        //     cout << "lvalue type" << endl;
        //     this->data = data; // ������ ����
        // } // lvalue type argment
        // void setData(std::vector<int>&& data) {
        //     cout << "rvalue type" << endl;
        //     this->data = std::move(data); // ������ �̵�
        // } // rvalue type argment
        void setData(std::vector<int> data) { this->data = std::move(data); }
    };

    void study005() {
        DataHolder wrapper;
        const std::vector myData{ 11, 22, 33 };
        wrapper.setData(myData); // lvalue type
        wrapper.setData({ 22, 33, 44 }); // rvalue type
    }

    // p.463 const �޼���
    void study006() {
        SpreadsheetCell myCell{ 5 };
        cout << myCell.getValue() << endl;
        myCell.setValue("6");

        const SpreadsheetCell myCellConstRef{ myCell };
        cout << myCellConstRef.getValue() << endl;
        //myCellConstRef.setString("6");
        // �� Cannot convert this argument from type const SpreadsheetCell to type SpreadsheetCell:
        // function is missing const qualifier
        // �̸��� ���� const Ÿ���� SpreadsheetCell ��ü�� ���ؼ� non-const �޼����� setString() �޼��带 �ҷ��ٴ� ���̴�.
        // ��, const ��ü�� ���ؼ��� �ݵ�� const �޼��常�� ȣ���� �� �ִٴ� ���̴�.
    }

    // p.466 const ��� �޼��� �����ε�
    void study007() {
        auto* sheet1_ptr{ new Spreadsheet(5, 6) };
        [[maybe_unused]] auto& cell1{ sheet1_ptr->getCellAt(1, 1) };
        // �� non-const getCellAt �޼��� ȣ��
        delete sheet1_ptr;
        // ReSharper disable once CppDFAUnusedValue
        sheet1_ptr = nullptr;

        const Spreadsheet sheet2{ 5, 6 };
        [[maybe_unused]] const auto& cell2{ sheet2.getCellAt(1, 1) };
        // �� const getCellAt �޼��� ȣ��
    }

    // p.468 ���� ���� �޼���(ref_qualified method)
    class TextHolder {
        std::string text;
    public:
        explicit TextHolder(std::string text) : text(std::move(text)) {}
        [[nodiscard]] auto getText() const& -> const string& { // ���� �ν��Ͻ�(lvalue)�� ���ؼ��� ȣ���ϵ��� �ϴ� & ������
            cout << "lvalue reference qualified method call" << endl;
            return text;
        }
        [[nodiscard]] auto getText() && -> string&& { // �ӽ� �ν��Ͻ�(rvalue)�� ���ؼ��� ȣ���ϵ��� �ϴ� && ������
            cout << "rvalue reference qualified method call" << endl;
            return std::move(text);
        }
    };
    void study008() {
        TextHolder text_holder{ "Hello World!" };
        // ���� �ν��Ͻ��� ���� getText() ȣ��
        cout << text_holder.getText() << endl; // lvalue reference qualified method call
        // �ӽ� �ν��Ͻ��� ���� getText() ȣ��
        cout << TextHolder{ "Hello World!" }.getText() << endl; // rvalue reference qualified method call
        cout << std::move(text_holder).getText() << endl; // rvalue reference qualified method call
    } // p.469 ���� ����
}