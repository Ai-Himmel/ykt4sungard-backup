// ** I18N

// Calendar big5 language
// Author: Gary Fu, <gary@garyfu.idv.tw>
// Encoding: big5
// Distributed under the same terms as the calendar itself.

// For translators: please use UTF-8 if possible.  We strongly believe that
// Unicode is the answer to a real internationalized world.  Also please
// include your contact information in the header, as can be seen above.
	
// full day names
Calendar._DN = new Array
("璃戳ら",
 "璃戳",
 "璃戳",
 "璃戳",
 "璃戳",
 "璃戳き",
 "璃戳せ",
 "璃戳ら");

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
("ら",
 "",
 "",
 "",
 "",
 "き",
 "せ",
 "ら");

// full month names
Calendar._MN = new Array
("る",
 "る",
 "る",
 "る",
 "きる",
 "せる",
 "る",
 "る",
 "る",
 "る",
 "る",
 "る");

// short month names
Calendar._SMN = new Array
("る",
 "る",
 "る",
 "る",
 "きる",
 "せる",
 "る",
 "る",
 "る",
 "る",
 "る",
 "る");

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "闽";

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"For latest version visit: http://www.dynarch.com/projects/calendar/\n" +
"Distributed under GNU LGPL.  See http://gnu.org/licenses/lgpl.html for details." +
"\n\n" +
"ら戳匡拒よ猭:\n" +
"- ㄏノ \xab, \xbb 秙匡拒\n" +
"- ㄏノ " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " 秙匡拒る\n" +
"- 俫秙е匡";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"丁匡拒よ猭:\n" +
"- 翴阑ヴ俫丁场糤ㄤ\n" +
"- Shift龄翴阑搭ぶㄤ\n" +
"- 翴阑╈∑еэ跑俫";

Calendar._TT["PREV_YEAR"] = " (匡虫)";
Calendar._TT["PREV_MONTH"] = " (匡虫)";
Calendar._TT["GO_TODAY"] = "さら";
Calendar._TT["NEXT_MONTH"] = "る (匡虫)";
Calendar._TT["NEXT_YEAR"] = "る (匡虫)";
Calendar._TT["SEL_DATE"] = "匡拒ら戳";
Calendar._TT["DRAG_TO_MOVE"] = "╈∑";
Calendar._TT["PART_TODAY"] = " (さら)";

// the following is to inform that "%s" is to be the first day of week
// %s will be replaced with the day name.
Calendar._TT["DAY_FIRST"] = "盢 %s 陪ボ玡";

// This may be locale-dependent.  It specifies the week-end days, as an array
// of comma-separated numbers.  The numbers are from 0 to 6: 0 means Sunday, 1
// means Monday, etc.
Calendar._TT["WEEKEND"] = "0,6";

Calendar._TT["CLOSE"] = "闽超";
Calendar._TT["TODAY"] = "さら";
Calendar._TT["TIME_PART"] = "翴阑or╈∑э跑丁(Shift搭)";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "%Y-%m-%d";
Calendar._TT["TT_DATE_FORMAT"] = "%a, %b %e";

Calendar._TT["WK"] = "秅";
Calendar._TT["TIME"] = "Time:";
