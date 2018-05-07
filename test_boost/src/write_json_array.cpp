#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace bpt = boost::property_tree ;
int main()
{
	bpt::ptree p1,p2;
	std::string value("test") ;
	for(int i=0;i<5;i++)
	{
		bpt::ptree p3 ;
		p3.put_value(value) ;
		p2.push_back(std::make_pair("",p3));
	}	
	p1.push_back(std::make_pair("next",p2)) ;

	boost::property_tree::write_json("test.json",p1) ;

	return 0 ;
}
