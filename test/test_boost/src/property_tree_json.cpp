/*

	{
		Result:
		{
			ORSID:101,
			ReportIndexList:
			{
				[
					{
						ID:111,
						ConfirmReportNum:101,
						TradeReportNum:100
					},
					{
						ID:112,
						ConfirmReportNum:102,
						TradeReportNum:102
					},
				]
			}	
		
		}
	}

  */
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;

int main()
{
	boost::property_tree::ptree pt ;
	
	boost::property_tree::json_parser::read_json("test.json",pt) ;
	
	boost::property_tree::ptree child_result = pt.get_child("Result") ;
	try{
		int ors_id = child_result.get<int>("ORSID") ;
		std::cout<<"orsid:"<<ors_id<<std::endl;
	
	
		//boost::property_tree::ptree list = child_result.get_child("ReportIndex");
		{
			BOOST_FOREACH(boost::property_tree::ptree::value_type &v1,child_result.get_child("ReportIndex"))
			{
			std::cout<< v1.second.get<int>("ID")<<" :"<<v1.second.get<int>("ConfirmReportNum")<<":"<<v1.second.get<int>("TradeReportNum")<<std::endl;
			}
		}
	}
	catch(boost::property_tree::ptree_error &e)
	{
		std::cout<<e.what()<<std::endl;
		return 2 ;
	}
		return 0 ;
}
