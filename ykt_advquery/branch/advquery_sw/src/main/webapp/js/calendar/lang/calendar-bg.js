// ** I18N

// Calendar BG language
// Author: Mihai Bazon, <mihai_bazon@yahoo.com>
// Translator: Valentin Sheiretsky, <valio@valio.eu.org>
// Encoding: Windows-1251
// Distributed under the same terms as the calendar itself.

// For translators: please use UTF-8 if possible.  We strongly believe that
// Unicode is the answer to a real internationalized world.  Also please
// include your contact information in the header, as can be seen above.

// full day names
Calendar._DN = new Array
("湾溴?",
 "项礤溴腠桕",
 "买铕龛?,
 "佯溧",
 "族蜮蝥?,
 "襄蝥?,
 "漾犷蜞",
 "湾溴?");

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
("湾?,
 "项?,
 "买?,
 "佯",
 "族?,
 "襄?,
 "漾?,
 "湾?);

// full month names
Calendar._MN = new Array
("唔筻痂",
 "藻怵筻痂",
 "锑痱",
 "里痂?,
 "锑?,
 "揄?,
 "揠?,
 "棱泱耱",
 "彦矧屐怵?,
 "侮蝾焘痂",
 "皖屐怵?,
 "腻赍焘痂");

// short month names
Calendar._SMN = new Array
("唔?,
 "藻?,
 "锑?,
 "里?,
 "锑?,
 "揄?,
 "揠?,
 "棱?,
 "彦?,
 "侮?,
 "皖?,
 "腻?);

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "软纛痨圉? 玎 赅脲礓囵?;

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"For latest version visit: http://www.dynarch.com/projects/calendar/\n" +
"Distributed under GNU LGPL.  See http://gnu.org/licenses/lgpl.html for details." +
"\n\n" +
"Date selection:\n" +
"- Use the \xab, \xbb buttons to select year\n" +
"- Use the " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " buttons to select month\n" +
"- Hold mouse button on any of the above buttons for faster selection.";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"Time selection:\n" +
"- Click on any of the time parts to increase it\n" +
"- or Shift-click to decrease it\n" +
"- or click and drag for faster selection.";

Calendar._TT["PREV_YEAR"] = "橡邃磬 泐滂磬 (玎漯蝈 玎 戾睨)";
Calendar._TT["PREV_MONTH"] = "橡邃屙 戾皴?(玎漯蝈 玎 戾睨)";
Calendar._TT["GO_TODAY"] = "如徨疱蝈 漤羼";
Calendar._TT["NEXT_MONTH"] = "央邃忄?戾皴?(玎漯蝈 玎 戾睨)";
Calendar._TT["NEXT_YEAR"] = "央邃忄 泐滂磬 (玎漯蝈 玎 戾睨)";
Calendar._TT["SEL_DATE"] = "如徨疱蝈 溧蜞";
Calendar._TT["DRAG_TO_MOVE"] = "橡屐羼蜮囗?;
Calendar._TT["PART_TODAY"] = " (漤羼)";

// the following is to inform that "%s" is to be the first day of week
// %s will be replaced with the day name.
Calendar._TT["DAY_FIRST"] = "%s 赅蝾 嵇疴?溴?;

// This may be locale-dependent.  It specifies the week-end days, as an array
// of comma-separated numbers.  The numbers are from 0 to 6: 0 means Sunday, 1
// means Monday, etc.
Calendar._TT["WEEKEND"] = "0,6";

Calendar._TT["CLOSE"] = "青蜮铕弪?;
Calendar._TT["TODAY"] = "捻羼";
Calendar._TT["TIME_PART"] = "(Shift-)Click 桦?drag 玎 溧 镳铎屙栩?耱铋眍耱蜞";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "%Y-%m-%d";
Calendar._TT["TT_DATE_FORMAT"] = "%A - %e %B %Y";

Calendar._TT["WK"] = "彦潇";
Calendar._TT["TIME"] = "奏?";
