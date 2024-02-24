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
        void someMethod(double d);
        void someOtherMethod() const {
            cout << "the base class's protectedInt = " << protected_int_ << endl;
            //cout << "the base class's privateInt = " << privateInt << endl; // compile error!
        }
    };

    void study003()
    {
	    
    }
}