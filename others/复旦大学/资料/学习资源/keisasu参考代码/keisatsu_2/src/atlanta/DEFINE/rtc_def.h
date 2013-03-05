#ifndef RTC_DEF
	#define RTC_DEF
/************************************************************************
 * RTC操作用デファイン													*
 ************************************************************************/

#define RTC_OFF				0
#define RTC_ON				1

#define YEAR_REGISTER		0x60
#define MONTH_REGISTER		0x50
#define DATE_REGISTER		0x40
#define WEEK_REGISTER		0x30
#define HOUR_REGISTER		0x20
#define MINUTE_REGISTER		0x10
#define SECOND_REGISTER		0x00
#define CONTROL1_REGISTER	0xE0
#define CONTROL2_REGISTER	0xF0
#define ADJUST_REGISTER		0x70

#define YEAR_MASK		0xFF
#define MONTH_MASK		0x1F
#define DATE_MASK		0x3F
#define WEEK_MASK		0x07
#define HOUR_MASK		0x3F
#define MINUTE_MASK		0x7F
#define SECOND_MASK		0xFF
#define CONTROL1_MASK	0xFF
#define CONTROL2_MASK	0xFF
#define ADJUST_MASK		0x7F

#define BYTE_WRITE_MODE		0x08
#define BURST_WRITE_MODE	0x00
#define BYTE_READ_MODE		0x0C
#define BURST_READ_MODE		0x04

#define RTC_RW_PERMIT		0x01
#define RTC_RW_FORBIT		0x00

#endif