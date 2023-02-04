#ifndef element_hpp
#define element_hpp

#include <yaml-cpp/yaml.h>
#include <string>

// template<typename T>
class element {
	public:
		// T data;
		virtual ~element(){ }
		virtual void parse(std::string) = 0;
		virtual void parse(YAML::Node &) = 0;
		virtual YAML::Emitter& operator << (YAML::Emitter&) = 0;
	};


#endif // element_hpp