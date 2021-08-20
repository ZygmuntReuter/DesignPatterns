#pragma once
#include <memory>


class Drawable 
{
public:
	template<typename T>
	Drawable(T& t): 
		_data(std::make_unique<Concept<T>>(t)) {};

	void Draw() 
	{
		_data->_draw();
	}

private:
	struct conceptBase
	{
		virtual void _draw() = 0;
		virtual ~conceptBase() = default;
	};

	template<typename internalType>
	struct Concept final : conceptBase 
	{
		Concept(internalType& ref) : _ref(ref) {}
		void _draw() override
		{
			_ref.Draw();
		}
		internalType& _ref;
	};

	std::unique_ptr<conceptBase> _data;

};
