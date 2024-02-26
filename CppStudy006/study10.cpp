module;
#include <iostream>
module study10;

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
    { // ���⼭ final Ű����� �� Ŭ������ ���̻� ����Ŭ������ ����� �� ���ٴ°� ����Ѵ�.
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
        //base1->someOtherMethod(); // ������ ����
        delete base1;
        base1 = nullptr;
    }

    void study002()
    {
        Base myBase;
        myBase.someMethod();
        Derived myDerived;
        myDerived.someMethod();

        cout << endl; cout << "�Ļ� Ŭ������ ��ü�� ����Ű�� BaseŬ���� ���۷���" << endl;
        Base& ref{ myDerived }; // �̷��� �ϸ� �Ļ� Ŭ������ ������ �����ǰ� ���� ��ĸ� �޶�����.
        cout << "Base& ref {myDerived} myDerived.someOtherMethod() ȣ��" << endl;
        myDerived.someOtherMethod(); // �Ļ� Ŭ������ �޼��带 ȣ����.
        cout << "Base& ref {myDerived} ref.someMethod() ȣ��" << endl;
        ref.someMethod(); // �Ļ� Ŭ������ �޼��带 ȣ����
        //ref.someOtherMethod(); // ������ ����

        cout << endl; cout << "Derived�� Base�� ĳ��Ʈ�ϱ�" << endl;
        Base assignedObject{ myDerived }; // �̷��� �ϸ� �Ļ� Ŭ������ ������ �������. �̰��� �����̽�(slicing)�̶�� �θ���.
        cout << "Base assignedObject{myDerived} assignedObject.someMethod() ȣ��" << endl;
        assignedObject.someMethod(); // Base Ŭ������ �޼��带 ȣ����
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
    { // ���⼭ final Ű����� �� Ŭ������ ���̻� ����Ŭ������ ����� �� ���ٴ°� ����Ѵ�.
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
        ref.someMethod(1.1); // Base ������ someMethod�� ȣ��ȴ�. p.517
        // override Ű���带 ���̸� �̷����� ������ �˷��� �������ش�.
        // ���� �ٽ� Derived ������ someMethod�� ȣ��ȴ�.
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
            cout << "�ܼ��� Derived class�� go()�� ������ ��." << endl;
            my_derived.go(); cout << endl;
            Base& ref{ my_derived };
            cout << "Base Ÿ�� ���۷����� ȣ���ϸ� ������ Derived����\n"
                "�������̵� ���� ���� Base Ŭ������ go()�� ȣ��ȴ�." << endl;
            ref.go(); cout << endl;
        }
	}

	namespace case02
	{
		class Base
		{
		public:
            // 5�� ��Ģ
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
            void someMethod() override; // ������ ����
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
            // base�� Derived* Ÿ���̶�� ������ �� ����.
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