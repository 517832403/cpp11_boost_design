#include <string>
#include <iostream>
#include "property.h"



const std::string test_string("test_string");
const std::string test_value("test_value");
const std::string test_int("test_int");
const std::string test_bool("test_bool");
const std::string test_char("test_char");
const char* ptr = "test test_char";
int main()
{

	tools::Property property;
	property.SetValue(test_string,test_value) ;
	property.SetValue(test_int,12) ;
	property.SetValue(test_char,ptr) ;
	property.SetValue(test_bool,true);
	std::cout<<property.GetValue(test_string,std::string(""))<<std::endl;
	std::cout<<property.GetValue(test_char,"")<<std::endl;
	std::cout<<property.GetValue(test_int,0)<<std::endl;
	std::cout<<property.GetValue(test_bool,false)<<std::endl;



	return 0 ;
}