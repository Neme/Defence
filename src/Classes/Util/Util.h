#ifndef __UTIL_H__
#define __UTIL_H__

#include <memory>
#include <functional>

namespace util {

	//---------------------------------------------------//
	template<typename T>
	static T* create()
	{
		T *pRet = new T{};
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}
	//---------------------------------------------------//
	template<class... TArgs>
	class DependencyContainer
	{
	public:
		DependencyContainer(TArgs&&... mArgs) {
			m_data = std::make_tuple(std::forward<TArgs>(mArgs)...);
		}

		template <class T>
		T& get()
		{
			return std::get<get_element_count<T, 0, TArgs...>::value>(m_data);
		}


	private:

		std::tuple<TArgs...> m_data;


		template <class T, std::size_t N, class... Args>
		struct get_element_count
		{
			static const auto value = N;
		};

		template <class T, std::size_t N, class... Args>
		struct get_element_count<T, N, T, Args...>
		{
			static const auto value = N;
		};

		template <class T, std::size_t N, class U, class... Args>
		struct get_element_count<T, N, U, Args...>
		{
			static const auto value = get_element_count<T, N + 1, Args...>::value;
		};

	};

}

#endif // __UTIL_H__
