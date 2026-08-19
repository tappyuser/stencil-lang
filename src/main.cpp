#include <iostream>
#include <print>
#include <string>

int main(int argc, char** argv){
	
	std::format_string<std::string> s = "Hello";
	std::println(s);

	return 0;
}
