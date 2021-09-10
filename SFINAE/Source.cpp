#include <functional>
#include <iostream>

#pragma region has_foo sfinae implemntation
template <typename T>
class has_foo {
    typedef char yes[1];
    typedef char no[2];
    template <typename U, U u>
    struct fooTypeHelper; //<-decltype bypass

    template <typename C>
    static yes& test(fooTypeHelper<void (C::*)(), &C::foo>*);

    template <typename C>
    static yes& test(fooTypeHelper<void (C::*)() const, &C::foo>*);

    template <typename C>
    static no& test(...);

public:
    constexpr static bool value = (sizeof(test<T>(nullptr)) == sizeof(yes));
};
#pragma endregion


#pragma region feature_function implementation
template <typename T, bool>
struct feature_function;

class FeatureBase {
protected:
    FeatureBase(void (*ptr)())
        : _ptr(ptr)
    {
    }

    void (*_ptr)();
};

template <typename T>
struct feature_function<T, false> : protected FeatureBase {

    feature_function(T& t, void (*ptr)() = nullptr)
        : FeatureBase(ptr)
    {
    }

    template <typename... Args>
    void foo(Args&&... params)
    {
        if (FeatureBase::_ptr)
            (*FeatureBase::_ptr)(params...);
    }
};

template <typename T>
struct feature_function<T, true> {
    feature_function(T& t, ...)
        : _t(t)
    {
    }

    template <typename... Args>
    void foo(Args&&... params)
    {
        _t.foo(params...);
    }

private:
    T& _t;
};

#pragma endregion 

template <typename T, typename Function>
void invoke_foo_if_possible(T t, Function optional = OptFunction())
{
    feature_function<T, has_foo<T>::value>(t, optional).foo();
}

#pragma region additional code for test 
struct FooTest {
    void foo() { std::cout << "foo" << std::endl; }
};

struct FooTest2 {

    //void foo2() { std::cout << "foo2" << std::endl; }
};

#pragma endregion

int main()
{
    std::cout << has_foo<FooTest>::value << std::endl;
    std::cout << has_foo<FooTest2>::value << std::endl;
   
    FooTest foo_owner;
    invoke_foo_if_possible(foo_owner, []() { std::cout << "nie ma " << std::endl; });

    FooTest2 foo_owner2;
    invoke_foo_if_possible(foo_owner2, []() { std::cout << "nie ma " << std::endl; });

    //feature_function<FooTest, has_foo<FooTest>::value>(d, []() { std::cout << "nie ma" << std::endl; }).foo();

    std::cin.get();
    return 0;
}
