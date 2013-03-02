#ifndef _XTYPE_TRAIT_H_
#define _XTYPE_TRAIT_H_

#include <xutils/xtypelist.h>

XUTIL_NAMESPACE_BEGIN


template<int T>
struct Int2Type
{
	enum { value = T };
};

template<class T>
struct Type2Type
{
	typedef T OriginType;
};

template<class T>
struct ConstantTrait
{
	enum { result = false };
	typedef NullType Result;
};
template<class T>
struct ConstantTrait<const T>
{
	enum { result = true };
	typedef T Result;
};

template<class T>
struct PointerTrait
{
	enum { result = false };
	typedef NullType Pointer;
};

template<class T>
struct PointerTrait<T *>
{
	enum { result = true };
	typedef T Pointer;
};

template<class T,class U>
struct Conversion
{
	typedef char Small;
	class Big { char dummy[2]; };
	static Small Test(U);
	static Big Test(...);
	static T MakeT();
public:
	enum { exists = sizeof(Test(MakeT())) == sizeof(Small) };
	enum { exists2way = exists && Conversion<U,T>::exists };
	enum { sameType = false };
};

template<class T>
class Conversion<T,T>
{
public:
	enum { exists = 1, exists2way = 1, sameType = 1};
};

#define SUPERSUBCLASS(SUPER,SUB) \
	(xutil::Conversion<const SUB*,const SUPER*>::exists && \
	!xutil::Conversion<const SUPER*,const void*>::sameType)

#define SUPERSUBCLASS_STRICT(SUPER,SUB) \
	(SUPERSUBCLASS(SUPER,SUB) && \
	!xutil::Conversion<const SUPER,const SUB>::sameType)
	
template< class T >
class TypeTraits
{
public:
	typedef TYPELIST_4(
		unsigned char,unsigned short int,
		unsigned int,unsigned long) SignedInts;
	
	typedef TYPELIST_4(
		char,short int,int,long) UnsignedInts;
	typedef TYPELIST_3(bool,char,wchar_t) OtherInts;
	typedef TYPELIST_3(float,double,long double) Floats;
	
	enum { isStdUnsignedInt = TL::IndexOf<T,UnsignedInts>::value >= 0};
	enum { isStdSignedInt = TL::IndexOf<T,SignedInts>::value >= 0 };
	enum { isStdIntegral = isStdUnsignedInt || isStdSignedInt ||
		TL::IndexOf<T,OtherInts>::value >= 0 };
	enum { isStdFloat = TL::IndexOf<T,Floats>::value >= 0 };
	enum { isStdArith = isStdIntegral || isStdFloat };
	enum { isStdFundamental = isStdArith || isStdFloat ||
		Conversion<T,void>::sameType };
		
};

template<class T>
struct ConstnessTrait
{
	typedef const typename xutil::Selector<xutil::ConstantTrait<T>::result
		,typename xutil::ConstantTrait<T>::Result,T>::Result Result;
};

namespace TL {

// Most Derived

template<class TList,class T> struct MostDerived;
template<class T>
struct MostDerived<NullType,T>
{
	typedef T Result;
};
template<class Head,class Tail,class T>
struct MostDerived< TypeList<Head,Tail>,T >
{
private:
	typedef typename MostDerived<Tail,T>::Result Candidate;
public:
	typedef typename Selector<SUPERSUBCLASS(Candidate, Head),
			Head,Candidate >::Result Result;
};

// Derived To Front

template<class T> struct DerivedToFront;
template<>
struct DerivedToFront<NullType>
{
	typedef NullType Result;
};
template<class Head,class Tail>
struct DerivedToFront< TypeList<Head,Tail> >
{
private:
	typedef typename MostDerived<Tail,Head>::Result TheMostDerived;
	typedef typename Replace<Tail,TheMostDerived,Head>::Result L1;
public:
	typedef TypeList<TheMostDerived,L1> Result;
};
}
XUTIL_NAMESPACE_END

#endif // _XTYPE_TRAIT_H_
