#include <iostream>

class Scanner
{
	public:
		void Scan(){std::cout<<"scan"<<std::endl;}
} ;
class Parser
{
	public:
		void Parse(){std::cout<<"parse"<<std::endl;}
};

class GenMidCode
{
	public:
		void GenCode(){std::cout<<"gencode"<<std::endl;}
};

class Compiler
{
	public:
		void run()
		{
			Scanner scanner ;
			Parser parser ;
			GenMidCode genmidcode ;
			scanner.Scan() ;
			parser.Parse() ;
			genmidcode.GenCode() ;
		}
};

int main()
{
	Compiler compiler ;
	compiler.run() ;
	return 0 ;
}
