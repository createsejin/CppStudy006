module study10;
import std;

using namespace std;
namespace study10::study01
{
    class Base
    {
    public:
        virtual void someMethod() {}
    protected:
        int protectedInt{ 0 };
    private:
        int privateInt{ 0 };
    protected:
        void test_private() const {
            cout << "the base class's protectedInt = " << protectedInt << endl;
        }
    };

    //class Derived : public Base
    class Derived final : public Base
    { // 여기서 final 키워드는 이 클래스는 더이상 하위클래스로 상속할 수 없다는걸 명시한다.
    public:
        void someMethod() override;
        void someOtherMethod() {
            cout << "the base class's protectedInt = " << protectedInt << endl;
            //cout << "the base class's privateInt = " << privateInt << endl; // compile error!
        }
    };

    void Derived::someMethod() {
        Base::someMethod();
    }

    void study001() {
        Derived derived;
        derived.someMethod();
        derived.someOtherMethod();
        // p.509
        Base* base1{ new Derived{} };
        //base1->someOtherMethod(); // 컴파일 오류
        delete base1;
        base1 = nullptr;
    }
}