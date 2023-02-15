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

class a: public element<std::string, int, float>{
	public:
		a(YAML::Node&);
		a(std::string, std::array<std::string, 3>);
		using element::get;
		using element::operator[];
		std::string name; 
		void parse(std::string);
		void parse(YAML::Node&);
		void print(){printf("name: %s\n", name.c_str());}
		YAML::Emitter& operator << (YAML::Emitter&);
	};



a::a(YAML::Node& b){
	this -> parse(b);
	}



a::a(std::string b, std::array<std::string, 3> c){
	this -> keys = c;
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


class b: public element<char, int>{
	public:
		b(std::string c){}
		std::string name; 
		void parse(std::string){}
		void parse(YAML::Node&){}
		void print(){printf("name: %s\n", name.c_str());}
		YAML::Emitter& operator << (YAML::Emitter&){}
	};

int main(int argc, char *argv[]){
	a test(argv[1], {"sth", "num", "flt"});
	// test.keys = {"sth", "num", "flt"};
	// a::get<0>(test) = "lol";
	// a::get<1>(test) = 42;
	// a::get<2>(test) = 69.420;
	(std::string)test[0] = "lol";
	// test[1] = 42;
	// test[2] = 69.420;
	// test["skill issue"];
	b rest(argv[1]);
	test.print();
	printf("%d\n", test.keys.size());
	printf("%s\n", a::get<0>(test).c_str());
	printf("%d\n", rest.keys.size());
	}