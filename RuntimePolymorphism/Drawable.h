#pragma once
#include "TypeTraits.h"
#
#include <memory>

class Drawable {
public:
    template <typename T>
    Drawable(T& t)
        : _data(std::make_unique<Concept<T>>(t)) {};

    void Draw()
    {
        _data->Draw();
    }

    void Draw2()
    {
        _data->Draw2();
    }

private:
    struct conceptBase {
        virtual void Draw() = 0;
        virtual void Draw2() = 0;
        virtual ~conceptBase() = default;
    };

    template <typename internalType>
    struct Concept final : conceptBase {
        Concept(internalType& ref)
            : _ref(ref)
        {
        }

        void Draw() override
        {
            _ref.Draw();
        }

        void Draw2() override
        {
            invoke_Draw2_if_possible(_ref, []() {
                std::cout << typeid(decltype(_ref)).name() << " do not implement Draw2" << std::endl;
            });
        }
        internalType& _ref;
    };

    std::unique_ptr<conceptBase> _data;
};
