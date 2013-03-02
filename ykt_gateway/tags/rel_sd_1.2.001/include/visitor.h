#ifndef _KSG_VISITOR_H_
#define _KSG_VISITOR_H_

#ifdef _MSC_VER
#pragma once
#endif

class BaseVisitor
{
public:
	virtual ~BaseVisitor(){}
};

template<class T,class R=void>
class Visitor
{
public:
	Visitor(){}
	virtual ~Visitor(){}
	virtual R Visit(T&) = 0;
};

template<class R,class T>
struct DefaultCatchAll
{
	static R OnUnknownVisitor(T& visited,BaseVisitor& guest)
	{
		return R();
	}
};

template<class R,template<class,class> class CatchAllPolicy = DefaultCatchAll >
class Visitable
{
public:
	typedef R ReturnType;
	Visitable(){}
	virtual ~Visitable(){}
	virtual ReturnType Accept(BaseVisitor& guest) = 0;
protected:
	template<class T>
	static ReturnType AcceptImpl(T& visited,BaseVisitor& guest)
	{
		if(Visitor<T>* p = dynamic_cast<Visitor<T>*>(&guest))
		{
			return p->Visit(visited);
		}
		return CatchAllPolicy<R,T>::OnUnknownVisitor(visited,guest);
	}
};

#define DEFINE_VISITABLE() \
	virtual ReturnType Accept(BaseVisitor& guest) \
	{ return AcceptImpl(*this,guest); }

#endif // _KSG_VISITOR_H_
