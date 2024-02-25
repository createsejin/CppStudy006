module study10;
import std;

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
        public:
            Derived() { cout << "3"; }
        };
	}
}