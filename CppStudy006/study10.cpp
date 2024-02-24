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