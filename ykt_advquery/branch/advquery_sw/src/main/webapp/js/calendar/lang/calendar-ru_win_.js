// ** I18N

// Calendar RU language
// Translation: Sly Golovanov, http://golovanov.net, <sly@golovanov.net>
// Encoding: any
// Distributed under the same terms as the calendar itself.

// For translators: please use UTF-8 if possible.  We strongly believe that
// Unicode is the answer to a real internationalized world.  Also please
// include your contact information in the header, as can be seen above.

// full day names
Calendar._DN = new Array
("忸耜疱皴睃?,
 "镱礤溴朦龛?,
 "怛铕龛?,
 "耩邃?,
 "麇蜮屦?,
 "?蝽桷?,
 "耋后铗?,
 "忸耜疱皴睃?);

// Please note that the following array of short day names (and the same goes
// for short month names, _SMN) isn't absolutely necessary.  We give it here
// for exemplification on how one can customize the short day names, but if
// they are simply the first N letters of the full name you can simply say:
//
//   Calendar._SDN_len = N; // short day name length
//   Calendar._SMN_len = N; // short month name length
//
// If N = 3 then this is not needed either since we assume a value of 3 if not
// present, to be compatible with translation files that were written before
// this feature.

// short day names
Calendar._SDN = new Array
("怦?,
 "镱?,
 "怛?,
 "耩?,
 "麇?,
 "??,
 "耋?,
 "怦?);

// full month names
Calendar._MN = new Array
("礅囵?,
 "翦怵嚯?,
 "爨痱",
 "囡疱朦",
 "爨?,
 "桌睃",
 "桌朦",
 "噔泱耱",
 "皴眚狃?,
 "铌?狃?,
 "眍狃?,
 "溴赅狃?);

// short month names
Calendar._SMN = new Array
("礅",
 "翦?,
 "爨?,
 "囡?,
 "爨?,
 "桌?,
 "桌?,
 "噔?,
 "皴?,
 "铌?,
 "眍",
 "溴?);

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "?赅脲礓囵?..";

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"For latest version visit: http://www.dynarch.com/projects/calendar/\n" +
"Distributed under GNU LGPL.  See http://gnu.org/licenses/lgpl.html for details." +
"\n\n" +
"枢?恹狃囹?溧蝮:\n" +
"- 橡?镱祛 觏铒铌 \xab, \xbb 祛骓?恹狃囹?泐锌n" +
"- 橡?镱祛 觏铒铌 " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " 祛骓?恹狃囹?戾?鯸n" +
"- 项溴疰栩??觏铒觇 磬驵螓扈, 黩钺?镱忤腩顸 戾睨 猁耱痤泐 恹犷疣.";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"枢?恹狃囹?怵屐:\n" +
"- 橡?觌桕?磬 鬣襦?桦?扈眢蜞?铐?筲咫梓桠帼蝰\n" +
"- 镳?觌桕??磬驵蝾?觌噔桫彘 Shift 铐?箪屙帼蝰\n" +
"- 羼腓 磬驵螯 ?溻桡囹?禧铋 怆邂?怙疣忸, 铐?狍潴?戾?螯? 猁耱疱?";

Calendar._TT["PREV_YEAR"] = "袜 泐?磬玎?(箐屦骅忄螯 潆 戾睨)";
Calendar._TT["PREV_MONTH"] = "袜 戾??磬玎?(箐屦骅忄螯 潆 戾睨)";
Calendar._TT["GO_TODAY"] = "彦泐漤";
Calendar._TT["NEXT_MONTH"] = "袜 戾??怙屦邃 (箐屦骅忄螯 潆 戾睨)";
Calendar._TT["NEXT_YEAR"] = "袜 泐?怙屦邃 (箐屦骅忄螯 潆 戾睨)";
Calendar._TT["SEL_DATE"] = "蔓徨痂蝈 溧蝮";
Calendar._TT["DRAG_TO_MOVE"] = "襄疱蜞耜桠嚅蝈 禧铋";
Calendar._TT["PART_TODAY"] = " (皴泐漤)";

// the following is to inform that "%s" is to be the first day of week
// %s will be replaced with the day name.
Calendar._TT["DAY_FIRST"] = "襄疴 溴睃 礤溴腓 狍溴?%s";

// This may be locale-dependent.  It specifies the week-end days, as an array
// of comma-separated numbers.  The numbers are from 0 to 6: 0 means Sunday, 1
// means Monday, etc.
Calendar._TT["WEEKEND"] = "0,6";

Calendar._TT["CLOSE"] = "青牮?;
Calendar._TT["TODAY"] = "彦泐漤";
Calendar._TT["TIME_PART"] = "(Shift-)觌桕 桦?磬驵螯 ?溻桡囹?;

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "%Y-%m-%d";
Calendar._TT["TT_DATE_FORMAT"] = "%e %b, %a";

Calendar._TT["WK"] = "礤?;
Calendar._TT["TIME"] = "吗屐:";
