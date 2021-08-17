#pragma once
#include <vector>
#include <algorithm>


inline namespace functional
{
	template<typename T >
	T& dereference(T& t) { return t; }

	template<typename T>
	T& dereference(T* t) { return *t; }

	template<
		typename CallableT,
		typename ContainerT = std::vector<CallableT>>
	class Event 
	{
	public:
		template<typename AnyCallableT>
		CallableT& Attach(AnyCallableT t)
		{
			static_assert(
				std::is_convertible<AnyCallableT, CallableT>::value,
				"Unconvertible type used with function Event::Attach");
			
			container.push_back(t);
			return *(container.end() - 1); //container.back() with c++ 20
		}

		void Dettach(const CallableT& toRemove)
		{
			container.erase(
				std::remove_if(
						container.begin(),
						container.end(),
						[&toRemove](const CallableT& containerItem) {
							return &containerItem == &toRemove;
						}
					),
				container.end()
			);
		}

		template<typename... Params>
		void operator() (Params... args)
		{
			for (auto& collable : container)
				if (collable)
					dereference(collable)(args...);
		}
	private:
		ContainerT container;
	};
}