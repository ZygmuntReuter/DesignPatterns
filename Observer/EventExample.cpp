#include "Event.h"
#include <iostream>
#include <functional>

#pragma region SimpleFunction
	void SimpleFunction(int i)
	{
		std::cout << "SimpleFunction, Parameter i = " << i << std::endl;
	}
#pragma endregion 

#pragma region SimpleObjects
	struct AnyObj
	{
		void operator() ()
		{
			std::cout << "AnyObj::operator()" << std::endl;
		}

		void memberFunction(int i)
		{
			std::cout << "AnyObj::memberFunction(), Parameter i = " << i << std::endl;
		}
		AnyObj() {}
		AnyObj(const AnyObj&) = delete;
		AnyObj& operator=(const AnyObj&) = delete;
	};
#pragma endregion

#pragma region Interfaces 
	class IRun
	{
	public:
		virtual void Run(float f) = 0;
	};

	class DerivativeClass : public IRun
	{
		void Run(float f) override
		{
			std::cout << "concreteClass::Run(), f = " << f << std::endl;
		};
	};

	template<typename T>
	class RunnerAdapter
	{
		T* const _t;
	public:
		RunnerAdapter(T* t) : _t(t) {}

		template<typename... Params>
		void operator() (Params... args)
		{
			_t->Run(args...);
		}

		operator bool() const
		{
			return _t != nullptr;
		}
	};
#pragma endregion

#pragma region RealLife
namespace 
{
	class Subject 
	{
		using FunctionT = std::function<void(const Subject&)>;
	public:
		FunctionT& RegisterOnLandingObserver(FunctionT f)
		{
			return OnLanding.Attach(f);
		}

		void UnregisterOnLandingObserver(FunctionT& f)
		{
			OnLanding.Dettach(f);
		}

		void SomeBusinessLogic() 
		{
			if (landingOnMars) 
			{
				OnLanding(*this);
			}
		}

		std::string GetLandingDate() const
		{
			return "20 lipca 1969";
		}

		private:
			Event<FunctionT> OnLanding;

			bool landingOnMars = true;
	};

	class Observer 
	{
		public:
		Observer(Subject& subject)
		{
			subject.RegisterOnLandingObserver(std::bind(&Observer::OpenChampagneBottle, this, std::placeholders::_1));
		}
		private:
		void OpenChampagneBottle(const Subject& s)
		{
			std::cout << "hura" << std::endl;
			std::cout << s.GetLandingDate() << std::endl;
		}
	};
}

#pragma endregion


void EventExample()
{
	{	//Simple function example
		functional::Event<void(*)(int)> Event;

		auto& p = Event.Attach(&SimpleFunction); // same as void(*p)(int) = e1.Attach(&SimpleFunction);
		Event.Dettach(p);
		Event(5);
	}

	{	// Simple objects example 
		AnyObj obj;
		Event<std::function<void(int)>> Event1;
		auto& f1 = Event1.Attach(std::bind(&SimpleFunction, std::placeholders::_1));
		auto& f2 = Event1.Attach(std::bind(&AnyObj::memberFunction, std::ref(obj), std::placeholders::_1));
		Event1(45);


		Event<AnyObj*> Event2;
		Event2.Attach(&obj);
		Event2();
	}

	{	// Interface example
		Event<RunnerAdapter<IRun>> Event;

		DerivativeClass cc;
		auto& cr = Event.Attach(&cc);
		//e4.Dettach(cr);
		Event(45.5f);
	}

	{	//RealLife example
		Subject globalSubject;
		Observer observer(globalSubject);

		globalSubject.SomeBusinessLogic();
	}

}
