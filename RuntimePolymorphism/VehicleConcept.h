#pragma once
#include <iostream>
#include <memory>

class VehicleConcept {
public:
    template <typename T>
    VehicleConcept(T& t)
        : _vehicleAdapter(
            std::make_unique<ConceptAdapter<T&>>(t))
    {
        std::cout << "constructor" << std::endl;
    };

    template <typename T>
    VehicleConcept(T&& t)
        : _vehicleAdapter(
            std::make_unique<ConceptAdapter<T>>(t))
    {
        std::cout << "rvalue constructor t = " << t.anyNumber << std::endl;
    };

    VehicleConcept(const VehicleConcept& c)
        : _vehicleAdapter(c._copy())
    {
        std::cout << "copy constructor" << std::endl;
    }

    VehicleConcept(VehicleConcept&& c) noexcept = default;
    //{
    //	std::swap(_vehicleAdapter, c._vehicleAdapter);
    //	std::cout << "move constructor " << std::endl;
    //}

    VehicleConcept& operator=(const VehicleConcept& c)
    {
        std::cout << "assignment operator" << std::endl;
        _vehicleAdapter = c._copy();

        return *this;
    }

    VehicleConcept& operator=(VehicleConcept&& c) noexcept
    {
        std::cout << "move assignment operator " << std::endl;
        std::swap(_vehicleAdapter, c._vehicleAdapter);
        return *this;
    }

    ~VehicleConcept()
    {
        std::cout << "destructor" << std::endl;
    }

    void Accelerate()
    {
        _vehicleAdapter->_Accelerate();
    }

private:
    struct Iconcept {
        virtual void _Accelerate() = 0;
        virtual ~Iconcept() = default;
        virtual std::unique_ptr<Iconcept> _copy() const = 0;
    };

    template <typename InternalType>
    struct ConceptAdapter final : public Iconcept {

        ConceptAdapter(InternalType obj)
            : _internal(obj)
        {
        }

        void _Accelerate() override
        {
            _internal.Accelerate();
        };

        std::unique_ptr<Iconcept> _copy() const override
        {
            return std::make_unique<ConceptAdapter<InternalType>>(*this);
        }

    private:
        InternalType _internal;
    };

    std::unique_ptr<Iconcept> _copy() const
    {
        return _vehicleAdapter->_copy();
    }

    std::unique_ptr<Iconcept> _vehicleAdapter;
};
