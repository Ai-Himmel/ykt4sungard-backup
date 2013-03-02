#ifndef _FUNCTOR_H_
#define _FUNCTOR_H_

#include <xutils/xtype_trait.h>
#include <xutils/xtypelist.h>

XUTIL_NAMESPACE_BEGIN
template<class Return, class Func,class Param>
class bind1param_t
{
public:
	bind1param_t(const Func& f,const Param& p)
		:_func(f),_param(p)
	{
	}
	Return operator()() const
	{
		return _func(_param);
	}
private:
	Func _func;        
	Param _param;
};

template<class R, class F,class P>
bind1param_t< R, F,P > bind1param(F f,P p)
{
	return bind1param_t< R, F, P >(f,p);
}


XUTIL_NAMESPACE_END

#endif // _FUNCTOR_H_

