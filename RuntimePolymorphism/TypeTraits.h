#pragma once

template <typename T>
class has_Draw2 {
    typedef char yes[1];
    typedef char no[2];

    template <typename U, U u>
    struct fooTypeHelper;

    template <typename C>
    static yes& test(fooTypeHelper<void (C::*)(), &C::Draw2>*);

    template <typename C>
    static yes& test(fooTypeHelper<void (C::*)() const, &C::Draw2>*);

    template <typename C>
    static no& test(...);

public:
    enum {
        value = (sizeof(test<T>(nullptr)) == sizeof(yes))
    };
};

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
    void Draw2(Args&&... params)
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
    void Draw2(Args&&... params)
    {
        _t.Draw2(params...);
    }

private:
    T& _t;
};

template <typename T>
void invoke_Draw2_if_possible(T t, void (*optional_function)() = nullptr)
{
    feature_function<T, has_Draw2<T>::value>(t, optional_function).Draw2();
}
