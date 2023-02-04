#include "../src/element/element.hpp"
#include "../src/element_container/element_container.hpp"
#include <yaml-cpp/yaml.h>
// #include <yaml.h>
#include <any>
#include <string>
#include <vector>

// class c {

// 	std::vector<std::string> get_keys();
// 	};

class a: public element{
	public:
		a(YAML::Node&);
		a(std::string);

		std::string name; 
		void parse(std::string);
		void parse(YAML::Node&);
		void print(){printf("name: %s\n", name.c_str());}
		YAML::Emitter& operator << (YAML::Emitter&);
	};



a::a(YAML::Node& b){
	this -> parse(b);
	}



a::a(std::string b){
	this -> parse(b);
	}




void a::parse(std::string b){
	YAML::Node n = YAML::Load(b);
	this -> parse(n); // TODO: Exception
	}



void a::parse(YAML::Node& b){
	this -> name = b["name"].as<std::string>();
	}



YAML::Emitter& a::operator << (YAML::Emitter& b){
	// YAML::Node e;
	// e["name"] = name;
	//  << name;
	using namespace YAML;
	b << YAML::Key << "name";
	b << YAML::Value << name;
	return b;
	}





int main(int argc, char *argv[]){
	a test(argv[1]);
	test.print();
	}