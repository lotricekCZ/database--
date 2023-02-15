#ifndef element_hpp
#define element_hpp

#include <yaml-cpp/yaml.h>
#include <string>
#include <tuple>
#include <array>
#include <vector>
#include <any>
#include <iostream>
#include <utility>
#include <type_traits>
#include <stdexcept>



template<
	typename Tuple, 
	typename Indices = std::make_index_sequence<std::tuple_size<Tuple>::value>>
struct runtime_get_func_table;

template<typename Tuple, size_t ... Indices>
struct runtime_get_func_table<Tuple, std::index_sequence<Indices...>>{
	using return_type = typename std::tuple_element<0, Tuple>::type&;
	using get_func_ptr = return_type (*)(Tuple&) noexcept;
	static constexpr get_func_ptr table[std::tuple_size<Tuple>::value] = {
		&std::get<Indices>...
	};
};

template<typename Tuple, size_t ... Indices>
constexpr typename
runtime_get_func_table<Tuple, std::index_sequence<Indices...>>::get_func_ptr
runtime_get_func_table<Tuple, std::index_sequence<Indices...>>::table[std::tuple_size<Tuple>::value];

template<typename Tuple>
constexpr
typename std::tuple_element<0, typename std::remove_reference<Tuple>::type>::type&
runtime_get(Tuple&& t, size_t index){
	using tuple_type = typename std::remove_reference<Tuple>::type;
	if(index >= std::tuple_size<tuple_type>::value)
		throw std::runtime_error("Out of range");
	return runtime_get_func_table<tuple_type>::table[index](t);
	};

// using return_type=typename
// 	std::tuple_element<0,Tuple>::type&;
// using get_func_ptr=return_type(*)(Tuple&)
// 	noexcept;

template<typename... T>
class element {
	public:
		std::tuple<T...> values;
		std::array<std::string, sizeof...(T)> keys;

		std::tuple<T...> &getRefValues() {return values;}
		
		// access values just as when using std::get<I>()
		template <std::size_t I, typename... Ts>
		static auto get(element<Ts...>& e) 
			-> decltype(std::get<I>(e.getRefValues())) {
	    	return std::get<I>(e.getRefValues());
			}
		
		// accesses values by string key
		// template <typename... T>
		auto operator[] (int i){
			return runtime_get<std::tuple<T...>>(this -> values, i);
			}
		
		virtual ~element(){}
		virtual void parse(std::string) = 0;
		virtual void parse(YAML::Node &) = 0;
		virtual YAML::Emitter& operator << (YAML::Emitter&) = 0;
		// inheriting std::map functions
		// std::size_t get_size(){return ;};
		// using std::map<std::string, std::any>::operator[];
		// using std::map<std::string, std::any>::at;
	};


#endif // element_hpp