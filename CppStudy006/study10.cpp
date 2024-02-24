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
    { // ���⼭ final Ű����� �� Ŭ������ ���̻� ����Ŭ������ ����� �� ���ٴ°� ����Ѵ�.
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
        //base1->someOtherMethod(); // ������ ����
        delete base1;
        base1 = nullptr;
    }
}