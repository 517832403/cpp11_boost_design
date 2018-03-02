#include <iostream>
#include <list>
class ElementA ;
class ElementB ;
class Visitor
{
	public:
		virtual void VisitElementA(ElementA* element)=0 ;
		virtual void VisitElementB(ElementB* element)=0 ;
};
class Element
{
	public:
		virtual void Accept(Visitor *visitor)=0 ;
};

class ElementA:public Element
{
	public:
		void Accept(Visitor *visitor) override
		{
			visitor->VisitElementA(this) ;
		}
		void OperationA()
		{
			std::cout<<"do operationA in elementA"<<std::endl;
		}
};

class ElementB:public Element
{
	public:
		void Accept(Visitor *visitor) override
		{
			visitor->VisitElementB(this) ;
		}
		void OperationB()
		{
			std::cout<<"do operationB in elementB"<<std::endl;
		}
};


class VisitorA:public Visitor
{
	public:
		void VisitElementA(ElementA *element) override
		{
			std::cout<<"A visit A"<<std::endl;
			element->OperationA() ;
		}
		void VisitElementB(ElementB *element) override
		{
			std::cout<<"A visit B"<<std::endl;
			element->OperationB() ;
		}
};

class VisitorB:public Visitor
{
	public:
		void VisitElementA(ElementA *element) override
		{
			std::cout<<"B visit A"<<std::endl;
			element->OperationA() ;
		}

		void VisitElementB(ElementB *element) override
		{
			std::cout<<"B visit B"<<std::endl;
			element->OperationB() ;
		}

};


class ObjectStruct
{
	public:
		void Accept(Visitor *visitor)
		{
			for(auto iter = ll.begin();iter!=ll.end();iter++)
			{
				(*iter)->Accept(visitor);
			}
		}
		void Add(Element* element)
		{
			ll.emplace_back(element) ;
		}
	private:
		std::list<Element*> ll ;
};

int main()

{
	Element *elementA = new ElementA() ;
	Element *elementB = new ElementB() ;
	Visitor *visitorA = new VisitorA() ;
	Visitor *visitorB = new VisitorB() ;
	ObjectStruct ost ;
	ost.Add(elementA) ;
	ost.Add(elementB) ;
	std::cout<<"---------------------"<<std::endl;
	ost.Accept(visitorA);
	std::cout<<"---------------------"<<std::endl;
	ost.Accept(visitorB);
	delete elementA ;
	delete elementB ;
	delete visitorA ;
	delete visitorB ;
	return 0 ;
}

