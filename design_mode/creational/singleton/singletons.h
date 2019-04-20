#include <type_traits>
#include <map>
#include <mutex>
#include <tuple>

template<typename T>
class Singleton
{

	public:
		static inline T* GetInstance();
		template<typename... Types>
		static T* GetInstance(Types&&.. types);
};

template<typename T>
T* GetInstance()
{
	static T t ;
	return &t ;
}

template<typename T>
template<typename... Types>
T* GetInstance(Types&&... types)
{
	typedef std::tuple<typename std::remove_reference<Types>::type...> TupleType;

	static std::map<TupleType,T*> ins_map;
	static std::mutex mtx ;

	const auto& key = std::make_tuple(std::forward<Types>(types)...);
	std::unique_lock<std::mutex> lock(mtx);
	auto it = ins_map.find(key);
	if(it != ins_map.end())
	{
		return it->second;
	}

	try
	{
		T* new_t = new T(std::forward<Types>(types)...);
		if(new_t == NULL)
			return NULL;
		ins_map[key] = new_t ;
		return new_t ;
	}
	catch(...)
	{
		return NULL;
	}
}
