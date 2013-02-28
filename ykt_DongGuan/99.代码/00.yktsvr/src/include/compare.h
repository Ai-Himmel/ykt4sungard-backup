#ifndef _COMPARE_H_
#define _COMPARE_H_

#include <string>

namespace KSYKT {


template<class T>
class LessThan 
{
	T factor_;
public:
	LessThan(T& t):factor_(t)
	{
	}
	template<class U>
	int Compare(U& v)
	{
		return (v < factor_) ? 0 : 1;
	}
};

template<>
class LessThan<const char *> 
{
	std::string factor_;
public:
	LessThan(const char *t)
	{
		factor_ = std::string(t);
	}
	template<class U>
	int Compare(U& v)
	{
		return 1;
	}
	int Compare(const char* v)
	{
		return (strcmp(v,factor_.c_str()) < 0) ? 0 : 1;
	}
	int Compare(char *v)
	{
		return Compare((const char*)v);
	}

};

template<>
class LessThan<double> 
{
	double factor_;
public:
	LessThan(double t):factor_(t)
	{
	}
	template<class U>
	int Compare(U& v)
	{
		return 1;
	}
	int Compare(double v)
	{
		return (amtcmp(v,factor_)<0) ? 0 : 1;
	}
};

template<class T>
class LessEqual
{
	T factor_;
public:
	LessEqual(T& t):factor_(t)
	{
	}
	int Compare(T& v)
	{
		return (v <= factor_) ? 0 : 1;
	}
};

template<>
class LessEqual<char *>
{
	std::string factor_;
public:
	LessEqual(const char* t):factor_(t)
	{
	}
	template<class U>
	int Compare(U& v)
	{
		return 1;
	}
	int Compare(const char* v)
	{
		return (strcmp(v,factor_.c_str()) <= 0) ? 0 : 1;
	}
	int Compare(char *v)
	{
		return Compare((const char*)v);
	}

};

template<>
class LessEqual<double>
{
	double factor_;
public:
	LessEqual(double t):factor_(t)
	{
	}
	int Compare(double v)
	{
		return (amtcmp(v,factor_)<=0) ? 0 : 1;
	}
};

template<class T>
class EqualThan
{
	T factor_;
public:
	EqualThan(T& t):factor_(t)
	{
	}
	int Compare(T& v)
	{
		return (v == factor_) ? 0 : 1;
	}

};

template<>
class EqualThan<const char*>
{
	std::string factor_;
public:
	EqualThan(const char *t):factor_(t)
	{
	}
	template<class U>
	int Compare(U& v)
	{
		return 1;
	}
	int Compare(const char* v)
	{
		return (strcmp(v,factor_.c_str())==0) ? 0 : 1;
	}
	int Compare(char* v)
	{
		return Compare((const char *)v);
	}
};

template<>
class EqualThan<char*>
{
	std::string factor_;
public:
	EqualThan(char *t):factor_(t)
	{
	}
	template<class U>
	int Compare(U& v)
	{
		return 1;
	}
	int Compare(const char* v)
	{
		return (strcmp(v,factor_.c_str())==0) ? 0 : 1;
	}
	int Compare(char* v)
	{
		return Compare((const char *)v);
	}

};


template<>
class EqualThan<double>
{
	double factor_;
public:
	EqualThan(double t):factor_(t)
	{
	}
	int Compare(double v)
	{
		return (amtcmp(v,factor_)==0) ? 0 : 1;
	}
};
////////////////////////////////////////////////
// Great class
template<class T>
class GreatThan 
{
	T factor_;
public:
	GreatThan(T& t):factor_(t)
	{
	}
	template<class U>
	int Compare(U& v)
	{
		return (v > factor_) ? 0 : 1;
	}
};

template<>
class GreatThan<const char *> 
{
	std::string factor_;
public:
	GreatThan(const char *t)
	{
		factor_ = std::string(t);
	}
	template <class U>
	int Compare(U& v)
	{
		return 1;
	}
	int Compare (const char* v)
	{
		return (strcmp(v,factor_.c_str()) > 0) ? 0 : 1;
	}
	int Compare(char *v)
	{
		return Compare((const char*)v);
	}

};


template<>
class GreatThan<double>
{
	double factor_;
public:
	GreatThan(double t):factor_(t)
	{
	}
	template <class U>
	int Compare(U& v)
	{
		return 1;
	}
	int Compare(double v)
	{
		return (amtcmp(v,factor_)>0) ? 0 : 1;
	}
};

template<class T>
class GreatEqual
{
	T factor_;
public:
	GreatEqual(T& t):factor_(t)
	{
	}
	int Compare(T& v)
	{
		return (v >= factor_) ? 0 : 1;
	}
};

template<>
class GreatEqual<const char *>
{
	std::string factor_;
public:
	GreatEqual(const char* t):factor_(t)
	{
	}
	template<class U>
	int Compare(U& v)
	{
		//writelog(LOG_ERR,"error invoke");
		return 1;
	}
	int Compare(const char* v)
	{
		//writelog(LOG_ERR,"1[%s]2[%s]",v,factor_.c_str());
		return (strcmp(v,factor_.c_str()) >= 0) ? 0 : 1;
	}
	int Compare(char *v)
	{
		return Compare((const char*)v);
	}
};

template<>
class GreatEqual<double>
{
	double factor_;
public:
	GreatEqual(double t):factor_(t)
	{
	}
	int Compare(double v)
	{
		return (amtcmp(v,factor_)>=0) ? 0 : 1;
	}
};



}
#endif // _COMPARE_H_

