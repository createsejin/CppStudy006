module study10;
import std;
import person02;
using namespace std;
namespace study10::study01
{
    class Base
    {
    public:
        virtual void someMethod();
    protected:
        int protected_int_{ 0 };
    private:
        int private_int_{ 0 };
    protected:
        void test_private() const {
            cout << "the base class's protectedInt = " << protected_int_ << endl;
        }
    };

    //class Derived : public Base
    class Derived final : public Base
    { // 여기서 final 키워드는 이 클래스는 더이상 하위클래스로 상속할 수 없다는걸 명시한다.
    public:
        void someMethod() override;
        void someOtherMethod() const {
            cout << "the base class's protectedInt = " << protected_int_ << endl;
            //cout << "the base class's privateInt = " << privateInt << endl; // compile error!
        }
    };

    void Base::someMethod() {
        cout << "This is Base's version of someMethod()." << endl;
    }
    void Derived::someMethod() {
	    // ReSharper disable once StringLiteralTypo
	    cout << "This is Derived's version of someMethod()." << endl;
    }

    void study001() {
        Derived derived;
        derived.someMethod();
        derived.someOtherMethod();
        // p.509
        const Base* base1{ new Derived{} };
        //base1->someOtherMethod(); // 컴파일 오류
        delete base1;
        base1 = nullptr;
    }

    void study002()
    {
        Base myBase;
        myBase.someMethod();
        Derived myDerived;
        myDerived.someMethod();

        cout << endl; cout << "파생 클래스의 객체를 가리키는 Base클래스 레퍼런스" << endl;
        Base& ref{ myDerived }; // 이렇게 하면 파생 클래스의 정보가 유지되고 접근 방식만 달라진다.
        cout << "Base& ref {myDerived} myDerived.someOtherMethod() 호출" << endl;
        myDerived.someOtherMethod(); // 파생 클래스의 메서드를 호출함.
        cout << "Base& ref {myDerived} ref.someMethod() 호출" << endl;
        ref.someMethod(); // 파생 클래스의 메서드를 호출함
        //ref.someOtherMethod(); // 컴파일 에러

        cout << endl; cout << "Derived를 Base로 캐스트하기" << endl;
        Base assignedObject{ myDerived }; // 이렇게 하면 파생 클래스의 정보가 사라진다. 이것을 슬라이싱(slicing)이라고 부른다.
        cout << "Base assignedObject{myDerived} assignedObject.someMethod() 호출" << endl;
        assignedObject.someMethod(); // Base 클래스의 메서드를 호출함
    }
}

namespace study10::study02
{
    class Base
    {
    public:
        virtual void someMethod(double d);
    protected:
        int protected_int_{ 0 };
    private:
        int private_int_{ 0 };
    protected:
        void test_private() const {
            cout << "the base class's protectedInt = " << protected_int_ << endl;
        }
    };

    //class Derived : public Base
    class Derived final : public Base
    { // 여기서 final 키워드는 이 클래스는 더이상 하위클래스로 상속할 수 없다는걸 명시한다.
    public:
        void someMethod(double d) override;
        void someOtherMethod() const {
            cout << "the base class's protectedInt = " << protected_int_ << endl;
            //cout << "the base class's privateInt = " << privateInt << endl; // compile error!
        }
    };
    void Base::someMethod(double d) {
        cout << "This is Base's version of someMethod()." << endl;
    }
    void Derived::someMethod(double d) {
        // ReSharper disable once StringLiteralTypo
        cout << "This is Derived's version of someMethod()." << endl;
    }

    void study003()
    {
        Derived myDerived;
        Base& ref{ myDerived };
        ref.someMethod(1.1); // Base 버전의 someMethod가 호출된다. p.517
        // override 키워드를 붙이면 이런일을 사전에 알려서 방지해준다.
        // 이제 다시 Derived 버전의 someMethod가 호출된다.
    }
	namespace case01
	{
        class Base
        {
        public:
            void go() { cout << "go() called on Base" << endl; }
        };
        class Derived : public Base
        {
        public:
            void go() { cout << "go() called on Derived" << endl; }
        };
        void study004()
        {
            Derived my_derived;
            cout << "단순히 Derived class에 go()가 생성된 것." << endl;
            my_derived.go(); cout << endl;
            Base& ref{ my_derived };
            cout << "Base 타입 레퍼런스로 호출하면 실제로 Derived에서\n"
                "오버라이드 되지 않은 Base 클래스의 go()가 호출된다." << endl;
            ref.go(); cout << endl;
        }
	}

	namespace case02
	{
		class Base
		{
		public:
            // 5의 법칙
            Base() = default;
			virtual ~Base() = default;
            Base(const Base& src) = default;
            Base& operator=(const Base& rhs) = default;
            Base(Base&& src) noexcept = default;
            Base& operator=(Base&& rhs) noexcept = default;
			virtual void func1();
            virtual void func2();
            void nonVirtualFunc();
		};

        class Derived final : public Base
        {
        public:
            void func2() override;
            void nonVirtualFunc();
        };
	}
    namespace case03
    {
        class Base
        {
            char* base_string_;
        public:
            Base()
            {
                base_string_ = new char[30];
                cout << "base_string_ allocated." << endl;
            	cout << "Base class constructor called" << endl;
            }
            virtual ~Base()
            {
                delete[] base_string_;
				cout << "base_string_ deallocated." << endl;
	            cout << "Base class destructor called" << endl;
            }
            virtual void someMethod() const { cout << "Base someMethod" << endl; }
            Base(const Base& src) = default;
            Base& operator=(const Base& rhs) = default;
            Base(Base&& src) noexcept = default;
            Base& operator=(Base&& rhs) noexcept = default;
        };

        class Derived : public Base
        {
            char* string_;
        public:
            Derived()
            {
	            string_ = new char[30];
                cout << "string_ allocated." << endl;
            }
            ~Derived() override
            {
	            delete[] string_;
				cout << "string_ deallocated." << endl;
            }
            //void someMethod() override final;
            void someMethod() const final { cout << "Derived someMethod" << endl; }
            Derived(const Derived& src) = default;
            Derived& operator=(const Derived& rhs) = default;
            Derived(Derived&& src) noexcept = default;
            Derived& operator=(Derived&& rhs) noexcept = default;
        };
        /*class DerivedDerived : public Derived
        {
        public:
            void someMethod() override; // 컴파일 에러
        };*/
        void study005()
        {
            const Base* ptr{ new Derived() };
            ptr->someMethod();
            delete ptr;
            ptr = nullptr;
        }
    }
}

namespace study10::study03
{
	namespace case01
	{
		class Something
		{
        public:
            Something() { cout << "2"; }
		};

        class Base
        {
        public:
            Base() { cout << "1"; }
        };

        class Derived : public Base
        {
            Something data_member_;
        public:
            Derived() { cout << "3"; }
        };
        void study006() {
            Derived my_derived;
        }
	}
    namespace case02
    {
        class Base
        {
        public:
            Base(int i) {};
        };

        class Derived final : public Base
        {
        public:
            Derived() : Base{7} {}
            Derived(const int i) : Base{i} {}
        };
    }
    namespace case03
    {
        class Something
        {
        public:
            Something() { cout << "+2"; }
            virtual ~Something() { cout << "-2"; }
        };

        class Base
        {
        public:
            Base() { cout << "+1"; }
            virtual ~Base() { cout << "-1"; }
        };

        class Derived final : public Base
        {
            Something data_member_;
        public:
            Derived() { cout << "+3"; }
            virtual ~Derived() { cout << "-3"; }
        };

        void study007() {
            Derived my_derived;
        }
    }
    namespace case04
    {
        class Book
        {
        public:
            virtual ~Book() = default;
            virtual auto getDescription() const -> std::string { return "Book"; }
            virtual auto getHeight() const -> int { return 120; }
        };

        class Paperback : public Book
        {
        public:
            auto getDescription() const -> std::string override {
                return "Paperback " + Book::getDescription();
            }
        };

        class Romance final : public Paperback
        {
        public:
            auto getDescription() const -> std::string override {
                return "Romance " + Book::getDescription();
            }
            auto getHeight() const -> int override { return Paperback::getHeight() / 2; }
        };

        class Technical final : public Book
        {
        public:
            auto getDescription() const -> std::string override {
                return "Technical " + Book::getDescription();
            }
        };

        void study008() {
            auto novel{ std::make_unique<Romance>() };
            auto* book{ new Book() };
            cout << novel->getDescription() << endl; // "Romance Paperback Book"
            cout << book->getDescription() << endl; // "Book"
            cout << novel->getHeight() << endl; // "60"
            cout << book->getHeight() << endl; // "120"
            delete book; book = nullptr;
        }
    }
    namespace case05
    {
        class Something
        {
        public:
            Something() { cout << "+2"; }
            virtual ~Something() { cout << "-2"; }
        };

        class Base
        {
        public:
            Base() { cout << "+1"; }
            virtual ~Base() { cout << "-1"; }
        };

        class Derived final : public Base
        {
            Something data_member_;
        public:
            Derived() { cout << "+3"; }
            virtual ~Derived() { cout << "-3"; }
        };
        static void presumptuous(Base* base) { // p.536
            // base가 Derived* 타입이라고 보장할 수 없다.
            Derived* myDerived{ static_cast<Derived*>(base) };
        }
        static void lessPresumptuous(Base* base) {
            Derived* myDerived{ dynamic_cast<Derived*>(base) };
            if (myDerived != nullptr) {
                // doing something
            }
        }
    }
}
namespace study10::study04
{
    namespace case17
    {
        class Secret
        {
        public:
            virtual ~Secret() = default;
        protected:
            virtual void dontTell() { cout << "I'll never tell." << endl; }
        };
        class Blabber final : public Secret
        {
        public:
            using Secret::dontTell;
        };
        void study022() {
            Blabber my_blabber;
            my_blabber.dontTell();
            Secret& ref{ my_blabber };
            //ref.donTell(); // compile error. Secret::dontTell() is protected method.
            Secret* ptr{ &my_blabber };
            //ptr->donTell(); // comile error. Secret::dontTell() is protected method.
            // ptr point to stack object. so It's not have to call delete deallocator.
        }
        class Base
        {
        public:
            virtual ~Base() = default;
            Base() = default;
            Base(const Base& src) {}
            Base& operator=(const Base& rhs) = default;
        };
        class Derived final : public Base
        {
        public:
            Derived() = default;
            Derived(const Derived& src) : Base{src} {}
            Derived& operator=(const Derived& rhs) {
                if (&rhs == this) return *this;
                Base::operator=(rhs);
                return *this;
            }
        };
        // p.576 실행 시간 타입 정보
        class Animal { public: virtual ~Animal() = default; };
        class Dog final : public Animal {};
        class Bird final : public Animal {};
        void speak(const Animal& animal) {
            if (typeid(animal) == typeid(Dog)) {
                cout << "Woof!" << endl;
            }
            else if (typeid(animal) == typeid(Bird)) {
                cout << "Chirp!" << endl;
            }
        }
        // typeid 연산자를 로깅 및 디버깅 용도로 활용하기
        class Loggable
        {
        public:
            virtual ~Loggable() = default;
            virtual auto getLogMessage() const -> std::string = 0;
        };
        class Foo final : public Loggable
        {
        public:
            auto getLogMessage() const -> std::string override {
                return "Hello logger.";
            }
        };
        void logObject(const Loggable& loggableObject) {
            cout << typeid(loggableObject).name() << ": "
                << loggableObject.getLogMessage() << endl;
        }
        void study023() {
            Foo foo;
            logObject(foo);
        }
    }
    // p.578 비 public 클래스 상속
    
    // p.579 가상 베이스 클래스
    namespace case018
    {
        class Animal
        {
        public:
            virtual void eat() = 0;
            virtual void sleep() { cout << "zzzzzz..." << endl; }
        };
        class Dog : public virtual Animal
        {
        public:
            virtual void bark() { cout << "Woof!" << endl; }
            void eat() override { cout << "The dog ate." << endl; }
        };
        class Bird : public virtual Animal
        {
        public:
            virtual void chirp() { cout << "Chirp!" << endl; }
            void eat() override { cout << "The bird ate." << endl; }
        };
        class DogBird final : public Dog, public Bird
        {
        public:
            virtual void eat() override { Dog::eat(); }
        };
        void study024() {
            DogBird myConfusedAnimal;
            myConfusedAnimal.sleep();
            cout << std::format("dddddd foramt test") << endl; // 웬일? 패치했나??
        }
    }
    // p.581 캐스트
    namespace case019
    {
        void study025() {
            int i{ 3 };
            int j{ 4 };
            double result{ static_cast<double>(i) / j };
        }
        class Base
        {
        public:
            virtual ~Base() = default;
        };
        class Derived final : public Base
        {
        public:
            ~Derived() = default;
        };
        void study026() {
            Base* base{ nullptr };
            Derived* derived{ new Derived{} };
            base = derived;
            derived = static_cast<Derived*>(base); // 다운캐스트
            delete derived;

            Base base2;
            Derived derived2;
            Base& base_ref{ derived2 };
            Derived& derived_ref{ static_cast<Derived&>(base_ref) };

            const Base* base3{ new Base() };
            //Derived* derived3{ static_cast<Derived*>(base3) }; // 예상치 못한 결과가 생길 수 있다.
            delete base3;
        }
        // p.583
        class X {};
        class Y {};
        void study027() { // 서로 관련이 없는 타입 끼리 변환할때 
            X x; Y y;
            X* xp{ &x }; Y* yp{ &y };
            xp = reinterpret_cast<X*>(yp);
            void* p{ xp }; // 보통의 방법
            xp = static_cast<X*>(p); // 다시 되돌릴때에는 반드시 static_cast를 사용해야한다.
            X& xr{ x };
            Y& yr{ reinterpret_cast<Y&>(x) };
            // p.584 std::bit_cast
            constexpr float as_float{ 1.23f };            
            if (const auto as_uint{ bit_cast<unsigned int>(as_float) };
                bit_cast<float>(as_uint) == as_float) cout << "Roundtrip success. \u25A0" << endl;
            // bit_cast를 쉽게 복제할 수 있는 타입에 대한 바이너리 I/O에 사용된다. p.584 참고
        }
    }
    namespace case020
    {
        class Base
        {
        public:
            Base() = default;
            virtual ~Base() = default;
            Base(const Base& src) = default;
            Base& operator=(const Base& rhs) = default;
            Base(Base&& src) noexcept = default;
            Base& operator=(Base&& rhs) noexcept = default;
        };
        class Derived final : public Base
        {
        public:
            Derived() = default;
            ~Derived() override = default;
            Derived(const Derived& src) = default;
            Derived& operator=(const Derived& rhs) = default;
            Derived(Derived&& src) noexcept = default;
            Derived& operator=(Derived&& rhs) noexcept = default;
        };
        void study028() {
            Base* b;
            Derived* d{ new Derived() };
            b = d; // 업캐스트
            d = dynamic_cast<Derived*>(b); // 다운 캐스트
            Base base;
            Derived derived;
            Base& base_ref{ base };
            try {
                Derived& derived_ref{ dynamic_cast<Derived&>(base_ref) };
            } catch (const std::bad_cast&) {
                cerr << "Bad Cast!" << endl;
                return;
            }
        }
        void study029() {
            Base base;
            Base& base_ref{ base };
            Derived derived;
            Derived& derived_ref{ derived };
            try {
                derived_ref = dynamic_cast<Derived&>(base_ref);
            } catch (const std::bad_cast&) {
                cerr << "Bad cast! \u25A1" << endl;
                return;
            }
            cout << "success dynamic_cast. \u25A0" << endl;
        }
    }
        
    using namespace hr;
    void study030() {
        std::vector<std::unique_ptr<Person>> vec;
        auto person1{ std::make_unique<Person>("SeJin"sv, "Bae"sv) };
        vec.push_back(std::move(person1));
        auto person2{ std::make_unique<Employee>("SeHee"sv, "Bae"sv, "SBB"sv, 21) };
        vec.push_back(std::move(person2));
        auto person3{ std::make_unique<Manager>("I"sv, "U"sv, 45) };
        vec.push_back(std::move(person3));
        auto person4{ std::make_unique<Director>("DeWoo"sv, "Lee"sv, "DV"sv, 67) };
        vec.push_back(std::move(person4));

        for (const auto& person : vec) {
            cout << person->to_string() << endl;
        }
    }
}
