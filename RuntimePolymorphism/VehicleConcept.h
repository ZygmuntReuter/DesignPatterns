#pragma once

#include <memory>

class VehicleConcept
{
public:
	template <typename T>
	VehicleConcept(T& t) :
		_vehicleAdapter(
			std::make_unique<Concept<T>>(t)
		)
	{};
	
	void Accelerate()
	{
		_vehicleAdapter->_Accelerate();
	}
private:
	struct Iconcept
	{
		virtual void _Accelerate() = 0;
		virtual ~Iconcept() = default;
	};

	template<typename InternalType> 
	struct Concept final : public Iconcept
	{
		Concept(InternalType& obj) :
			_internal(obj) 
		{}

		void _Accelerate() override
		{
			_internal.Accelerate();
		};

	private:
		InternalType& _internal;
	};

	std::unique_ptr<Iconcept> _vehicleAdapter;
};
