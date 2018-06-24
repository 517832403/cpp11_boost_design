#include <pwd.h>
#include <string>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <string.h>
int main()
{
	std::string login_user ;
	struct passwd* pw = getpwuid(geteuid()) ;
	if (pw == nullptr)
	{
		std::cout<<"get pwduid is failed,errno:"<<errno<<" err_msg:"<<strerror(errno)<<std::endl;
		return 0 ;
	}

	login_user = pw->pw_name ;
	std::cout<<"pwuid:"<<login_user<<std::endl;
	return 0 ;
}
