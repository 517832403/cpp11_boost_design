#include <string>
#include <unordered_map>
#include <memory>

template<typename ManufacturedType,typename ClassIDKey=std::string>
class GenericFactory
{
	private:
		typedef std::shared_ptr<ManufacturedType> (*BaseCreateFn)() ;
		typedef std::unordered_map<ClassIDKey,BaseCreateFn> FnRegistry ;
	
	public :
		static GenericFactory& GetInstance()
		{
			static GenericFactory s_singleton ;
			return s_singleton ;
		}

		void RegCreateFn(const ClassIDKey& class_name,BaseCreateFn fn)
		{
			if(registry_.count(class_name))
			{
				return ;
			}

			registry_.emplace(class_name,fn) ;
		}

		std::shared_ptr<ManufacturedType> Create(const ClassIDKey& class_name) const 
		{
			std::shared_ptr<ManufacturedType> the_object ;

			if(!registry_.count(class_name))
			{
				return the_object ;
			}

			the_object = registry_.at(class_name)() ;
			return the_object ;
		}

	private:
		GenericFactory(){}
		GenericFactory(const GenericFactory&) = delete ;
		GenericFactory& operator=(const GenericFactory&) = delete ;
	private:
		FnRegistry registry_;
};

template<typename AncestorType,
	typename ManufacturedType,
	typename ClassIDKey=std::string>
class RegisterInFactory
{
	public:
		static std::shared_ptr<AncestorType> CreateInstance()
		{
			return std::shared_ptr<AncestorType>(new ManufacturedType) ;
		}

		RegisterInFactory(const ClassIDKey &id)
		{
			GenericFactory<AncestorType,ClassIDKey>::GetInstance().RegCreateFn(id,CreateInstance) ;
		}
};




