#include <string>
#include <boost/system/error_code.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/filesystem.hpp>
#include <boost/exception/diagnostic_information.hpp>


class FileLock
{
public:
	FileLock(const std::string& file_path):
		m_file_path_(file_path),
		m_is_locked_(false),
		m_file_lock_(NULL)
	{}

	~FileLock()
	{
		if(m_file_lock_ != NULL && m_is_locked_)
		{
			m_file_lock_.unlock();
		}
		delete m_file_lock_ ;
	}

	uint32_t Lock()
	{
		try
		{
			boost::filesystem::path file_path = m_file_path_ ;
			boost::filesystem::path dir_path = file_path.parent_path();
			if(m_file_lock_ != NULL)
			{
				return -2 ;
			}
			boost::system::error_code ec ;
			if( !boost::filesystem::exists(dir_path))
			{
				if(!boost::filesystem::create_directory(dir_path))
				{
					return -3 ;
				}
			}
				
			if(!boost::filesystem::exists(file_path))
			{
				return -1 ;
			}

			m_file_lock_ = new boost::interprocess::file_lock(file_path.c_str());
			if(!(m_file_lock_->try_lock()))
			{
				return -4 ;
			}

			m_file_stream_.open(file_path_.c_str());
			m_file_stream_ << boost::interprocess::ipcdetail::get_current_process_id()<<std::endl;
			m_file_stream_.flush();
			m_is_locked_ = true;

			return 0 ;
		}
		catch(...)
		{
			std::cout<<boost::current_exception_diagnostic_information()<<std::endl;
			return -1 ;
		}
	}

private:
	std::string m_file_path_ ;
	bool	    m_is_locked_ ;
	boost::interprocess::file_lock* m_file_lock_ ;
	std::ofstream			m_file_stream_ ;
};
