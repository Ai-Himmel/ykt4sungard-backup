#ifndef _XTYPELIST_H_
#define _XTYPELIST_H_

#include <xutils/_xutil_types.h>

XUTIL_NAMESPACE_BEGIN


template<bool,class is_true,class is_false>
struct Selector
{
	typedef is_true Result;
};
template<class is_true,class is_false>
struct Selector<false,is_true,is_false>
{
	typedef is_false Result;
};

struct EmptyType {};
class NullType;

namespace TL
{

	template<class T,class U>
	struct TypeList
	{
		typedef T Head;
		typedef U Tail;
	};

#define TYPELIST_1(T1) xutil::TL::TypeList<T1,xutil::NullType >
#define TYPELIST_2(T1,T2) xutil::TL::TypeList<T1,TYPELIST_1(T2) >
#define TYPELIST_3(T1,T2,T3) xutil::TL::TypeList<T1,TYPELIST_2(T2,T3) >
#define TYPELIST_4(T1,T2,T3,T4) xutil::TL::TypeList<T1,TYPELIST_3(T2,T3,T4) >
#define TYPELIST_5(T1,T2,T3,T4,T5) xutil::TL::TypeList<T1,TYPELIST_4(T2,T3,T4,T5) >
#define TYPELIST_6(T1,T2,T3,T4,T5,T6) xutil::TL::TypeList<T1,TYPELIST_5(T2,T3,T4,T5,T6) >
#define TYPELIST_7(T1,T2,T3,T4,T5,T6,T7) xutil::TL::TypeList<T1,TYPELIST_6(T2,T3,T4,T5,T6,T7) >
#define TYPELIST_8(T1,T2,T3,T4,T5,T6,T7,T8) xutil::TL::TypeList<T1,TYPELIST_7(T2,T3,T4,T5,T6,T7,T8) >
#define TYPELIST_9(T1,T2,T3,T4,T5,T6,T7,T8,T9) xutil::TL::TypeList<T1,TYPELIST_8(T2,T3,T4,T5,T6,T7,T8,T9) >
#define TYPELIST_10(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10) xutil::TL::TypeList<T1,TYPELIST_9(T2,T3,T4,T5,T6,T7,T8,T9,T10) >
#define TYPELIST_11(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11) xutil::TL::TypeList<T1,TYPELIST_10(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11) >
#define TYPELIST_12(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12) xutil::TL::TypeList<T1,TYPELIST_11(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12) >
#define TYPELIST_13(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13) xutil::TL::TypeList<T1,TYPELIST_12(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13) >
#define TYPELIST_14(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14) xutil::TL::TypeList<T1,TYPELIST_13(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14) >
#define TYPELIST_15(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15) xutil::TL::TypeList<T1,TYPELIST_14(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15) >
#define TYPELIST_16(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16) xutil::TL::TypeList<T1,TYPELIST_15(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16) >
#define TYPELIST_17(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17) xutil::TL::TypeList<T1,TYPELIST_16(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17) >
#define TYPELIST_18(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18) xutil::TL::TypeList<T1,TYPELIST_17(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18) >
#define TYPELIST_19(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19) xutil::TL::TypeList<T1,TYPELIST_18(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19) >
#define TYPELIST_20(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20) xutil::TL::TypeList<T1,TYPELIST_19(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20) >
#define TYPELIST_21(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21) xutil::TL::TypeList<T1,TYPELIST_20(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21) >
#define TYPELIST_22(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22) xutil::TL::TypeList<T1,TYPELIST_21(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22) >
#define TYPELIST_23(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23) xutil::TL::TypeList<T1,TYPELIST_22(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23) >
#define TYPELIST_24(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24) xutil::TL::TypeList<T1,TYPELIST_23(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24) >
#define TYPELIST_25(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25) xutil::TL::TypeList<T1,TYPELIST_24(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25) >
#define TYPELIST_26(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26) xutil::TL::TypeList<T1,TYPELIST_25(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26) >
#define TYPELIST_27(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27) xutil::TL::TypeList<T1,TYPELIST_26(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27) >
#define TYPELIST_28(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28) xutil::TL::TypeList<T1,TYPELIST_27(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28) >
#define TYPELIST_29(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29) xutil::TL::TypeList<T1,TYPELIST_28(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29) >
#define TYPELIST_30(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30) xutil::TL::TypeList<T1,TYPELIST_29(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30) >
#define TYPELIST_31(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31) xutil::TL::TypeList<T1,TYPELIST_30(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31) >
#define TYPELIST_32(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32) xutil::TL::TypeList<T1,TYPELIST_31(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32) >
#define TYPELIST_33(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33) xutil::TL::TypeList<T1,TYPELIST_32(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33) >
#define TYPELIST_34(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34) xutil::TL::TypeList<T1,TYPELIST_33(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34) >
#define TYPELIST_35(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35) xutil::TL::TypeList<T1,TYPELIST_34(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35) >
#define TYPELIST_36(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36) xutil::TL::TypeList<T1,TYPELIST_35(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36) >
#define TYPELIST_37(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37) xutil::TL::TypeList<T1,TYPELIST_36(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37) >
#define TYPELIST_38(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38) xutil::TL::TypeList<T1,TYPELIST_37(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38) >
#define TYPELIST_39(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39) xutil::TL::TypeList<T1,TYPELIST_38(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39) >
#define TYPELIST_40(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40) xutil::TL::TypeList<T1,TYPELIST_39(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40) >
#define TYPELIST_41(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41) xutil::TL::TypeList<T1,TYPELIST_40(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41) >
#define TYPELIST_42(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42) xutil::TL::TypeList<T1,TYPELIST_41(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42) >
#define TYPELIST_43(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43) xutil::TL::TypeList<T1,TYPELIST_42(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43) >
#define TYPELIST_44(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44) xutil::TL::TypeList<T1,TYPELIST_43(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44) >
#define TYPELIST_45(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45) xutil::TL::TypeList<T1,TYPELIST_44(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45) >
#define TYPELIST_46(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46) xutil::TL::TypeList<T1,TYPELIST_45(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46) >
#define TYPELIST_47(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46,T47) xutil::TL::TypeList<T1,TYPELIST_46(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46,T47) >
#define TYPELIST_48(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46,T47,T48) xutil::TL::TypeList<T1,TYPELIST_47(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46,T47,T48) >
#define TYPELIST_49(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46,T47,T48,T49) xutil::TL::TypeList<T1,TYPELIST_48(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46,T47,T48,T49) >
#define TYPELIST_50(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46,T47,T48,T49,T50) xutil::TL::TypeList<T1,TYPELIST_49(T2,T3,T4,T5,T6,T7,T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,T38,T39,T40,T41,T42,T43,T44,T45,T46,T47,T48,T49,T50) >


	// Typelist length
	template<class T> struct TypeListLength;
	template<> struct TypeListLength<NullType>
	{
		enum { length = 0 };
	};
	template<class T,class U> 
	struct TypeListLength< TypeList<T,U> >
	{
		enum { length = TypeListLength<U>::length + 1 };
	};
	// typelist type at
	template <class TList, unsigned int index> struct TypeAt;
	template<class Head,class Tail>
	struct TypeAt< TypeList<Head,Tail>,0 >
	{
		typedef Head Result;
	};

	template<class Head,class Tail,unsigned int i >
	struct TypeAt< TypeList<Head,Tail>,i >
	{
		typedef typename TypeAt<Tail,i - 1>::Result Result;
	};

	// typelist Indexof
	template<class TList,class T> struct IndexOf;
	template<class T> struct IndexOf< NullType , T> 
	{
		enum { value = -1};
	};
	template<class Tail,class T>
	struct IndexOf< TypeList<T,Tail> , T>
	{
		enum { value = 0 };
	};
	template<class Head,class Tail,class T>
	struct IndexOf< TypeList<Head,Tail> , T >
	{
	private:
		enum { temp = IndexOf<Tail,T>::value };
	public:
		enum { value = temp == -1 ? -1 : temp + 1};
	};

	// append to typelist
	template<class TList,class T> struct Append;
	template<> struct Append<NullType,NullType>
	{
		typedef NullType Result;
	};
	template<class T> 
	struct Append<NullType,T>
	{
		typedef TYPELIST_1(T) Result;
	};
	template<class Head,class Tail>
	struct Append< NullType,TypeList<Head,Tail> >
	{
		typedef TypeList<Head,Tail> Result;
	};
	template<class Head,class Tail,class T>
	struct Append< TypeList<Head,Tail> , T>
	{
		typedef TypeList< Head , typename Append<Tail,T>::Result > Result;
	};
	// Erase All
	template<class TList,class T> struct EraseAll;
	template<class T>
	struct EraseAll<NullType,T>
	{
		typedef NullType Result;
	};
	template<class Tail,class T>
	struct EraseAll<TypeList<T,Tail>,T>
	{
		typedef typename EraseAll<Tail,T>::Result Result;
	};
	template<class Head,class Tail,class T>
	struct EraseAll<TypeList<Head,Tail>,T>
	{
		typedef TypeList<Head,
			typename EraseAll<Tail,T>::Result> Result;
	};
	// Erase 
	template<class TList,class T> struct Erase;
	template<class T>
	struct Erase<NullType,T>
	{
		typedef NullType Result;
	};
	template<class T,class Tail>
	struct Erase< TypeList<T,Tail> , T>
	{
		typedef Tail Result;
	};
	template<class Head,class Tail,class T>
	struct Erase< TypeList<Head,Tail> , T >
	{
		typedef TypeList< Head,
			typename Erase<TypeList<Tail,T>,T>::Result > Result;
	};
	
	// No duplicate
	template<class TList> struct NoDuplicates;
	template<> struct NoDuplicates<NullType>
	{
		typedef NullType Result;
	};
	template<class Head,class Tail>
	struct NoDuplicates<TypeList<Head,Tail> >
	{
	private:
		typedef typename NoDuplicates<Tail>::Result L1;
		typedef typename Erase<L1,Head>::Result L2;
	public:
		typedef TypeList<Head,L2> Result;
	};
	// Replace all
	template<class TList,class T,class U>struct Replace;
	template<class T,class U>
	struct Replace<NullType,T,U>
	{
		typedef NullType Result;
	};
	template<class T,class Tail,class U>
	struct Replace<TypeList<T,Tail>,T,U>
	{
		typedef TypeList<U,Tail> Result;
	};
	template<class Head,class Tail,class T,class U>
	struct Replace<TypeList<Head,Tail>,T,U>
	{
		typedef TypeList<Head,
			typename Replace<Tail,T,U>::Result> Result;
	};
	// Reverse
	template <class TList> struct Reverse;

	template <>
	struct Reverse<NullType>
	{
		typedef NullType Result;
	};

	template <class Head, class Tail>
	struct Reverse<TypeList<Head, Tail> >
	{
		typedef typename Append<
			typename Reverse<Tail>::Result, Head>::Result Result;
	};
	// see xtype_trait.h

} // end of TL namespace

template
<
	class TList,
	template <class AtomicType,class Base>class AUnit,
	class Root = EmptyType
>
class GenLinearHierarchy;

template
<
	class T1,
	class T2,
	template<class,class> class AUnit,
	class Root
>
class GenLinearHierarchy<TL::TypeList<T1,T2>,AUnit,Root> : public
	AUnit<T1,GenLinearHierarchy<T2,AUnit,Root> >
{
};

template
<
	class T,
	template<class,class> class AUnit,
	class Root
>
class GenLinearHierarchy<TYPELIST_1(T),AUnit,Root>
	: public AUnit<T,Root>
{
};

template<class TList,template<class> class Unit >
class GenScatterHierarchy;

template<class T1,class T2,template<class> class Unit >
class GenScatterHierarchy<TL::TypeList<T1,T2>,Unit>
:public GenScatterHierarchy<T1,Unit>
,public GenScatterHierarchy<T2,Unit>
{
public:
	typedef TL::TypeList<T1,T2> Tlist;
	typedef GenScatterHierarchy<T1,Unit> LeftBase;
	typedef GenScatterHierarchy<T2,Unit> RightBase;
};

template<class T1,template<class> class Unit >
class GenScatterHierarchy :public Unit<T1>
{
public:
	typedef Unit<T1> LeftBase;
};

template<template<class> class Unit>
class GenScatterHierarchy<NullType,Unit>
{

};
XUTIL_NAMESPACE_END

#endif // _XTYPELIST_H_
