#ifndef __UTIL_H__
#define __UTIL_H__

#include <memory>
#include <functional>

namespace util {

	//---------------------------------------------------//
	template<typename T, typename... TArgs>
	static T* create(TArgs&&... mArgs)
	{
		T *obj = new T{std::forward<TArgs>(mArgs)...};
		if (obj && obj->init())
		{
			obj->autorelease();
			return obj;
		}
		delete obj;
		return nullptr;
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
		T* get()
		{
			return &std::get<get_element_count<T, 0, TArgs...>::value>(m_data);
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
