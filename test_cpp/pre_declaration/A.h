#ifndef A_H_
#define A_H_
class B ; //pre_declaration
class A{
	public:
		A(B* b):b_(b){}

		void printB();

	private:
		B *b_{nullptr} ;
};

#endif
