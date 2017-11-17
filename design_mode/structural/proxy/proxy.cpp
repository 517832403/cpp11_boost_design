#include <iostream>


class Image
{
	public:
		Image(std::string name):m_image_name_(name){}
		virtual ~Image(){}
		virtual void show(){}

	protected:
		std::string m_image_name_ ;

};

class BigImage:public Image
{
	public:
		BigImage(std::string name):Image(name){}
		~BigImage(){}
		void show()
		{
			std::cout<<"show big image"<<std::endl;
		}
};

class BigImageProxy:public Image
{
	private:
		BigImage *m_image_ = nullptr;
	public:
		BigImageProxy(std::string name):Image(name){}
		~BigImageProxy()
		{ 
			if(m_image_!=nullptr)
				delete m_image_ ;
		}

		void show()
		{
			if(m_image_ == nullptr) 
				m_image_ = new BigImage(m_image_name_) ;
			m_image_->show() ;
		}
};

int main()
{
	Image *image = new BigImageProxy("proxy") ;
	image->show() ;
	delete image ;
	return 0 ;
}
