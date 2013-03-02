// ** I18N

// Calendar EN language
// Author: Idan Sofer, <idan@idanso.dyndns.org>
// Encoding: UTF-8
// Distributed under the same terms as the calendar itself.

// For translators: please use UTF-8 if possible.  We strongly believe that
// Unicode is the answer to a real internationalized world.  Also please
// include your contact information in the header, as can be seen above.

// full day names
Calendar._DN = new Array
("专讗砖谠谉",
 "砖谞托",
 "砖诇托砖托",
 "专讘托注托",
 "谳诪托砖托",
 "砖托砖托",
 "砖讘转",
 "专讗砖谠谉");

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
("讗",
 "讘",
 "讙",
 "赞",
 "呓",
 "谠",
 "砖",
 "讗");

// full month names
Calendar._MN = new Array
("托谞谠讗专",
 "驻讘专谠讗专",
 "诪专抓",
 "讗驻专托诇",
 "诪讗托",
 "托谠谞托",
 "托谠诇托",
 "讗谠讙谠住讟",
 "住驻讟诪讘专",
 "讗谠拽讟谠讘专",
 "谞谠讘诪讘专",
 "赞爪诪讘专");

// short month names
Calendar._SMN = new Array
("托谞讗",
 "驻讘专",
 "诪专抓",
 "讗驻专",
 "诪讗托",
 "托谠谞",
 "托谠诇",
 "讗谠讙",
 "住驻讟",
 "讗谠拽",
 "谞谠讘",
 "赞爪诪");

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "讗谠赞谠转 呓砖谞转谠谉";

Calendar._TT["ABOUT"] =
"讘谳专谉 转讗专托讱/砖注呓 DHTML\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"呓讙托专住讗 呓讗谳专谠谞呓 讝诪托谞呓 讘: http://www.dynarch.com/projects/calendar/\n" +
"诪谠驻抓 转谳转 讝托讻托谠谉 呓 GNU LGPL.  注托托谉 讘 http://gnu.org/licenses/lgpl.html 诇驻专讟托诐 谞谠住驻托诐." +
"\n\n" +
讘谳托专转 转讗专托讱:\n" +
"- 呓砖转诪砖 讘讻驻转谠专托诐 \xab, \xbb 诇讘谳托专转 砖谞呓\n" +
"- 呓砖转诪砖 讘讻驻转谠专托诐 " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " 诇讘谳托专转 谳谠赞砖\n" +
"- 呓谳讝拽 呓注讻讘专 诇谳谠抓 诪注诇 呓讻驻转谠专托诐 呓诪谠讝讻专托诐 诇注托诇 诇讘谳托专呓 诪呓托专呓 托谠转专.";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"讘谳托专转 讝诪谉:\n" +
"- 诇谳抓 注诇 讻诇 讗谳赞 诪谳诇拽托 呓讝诪谉 讻赞托 诇呓谠住托祝\n" +
"- 讗谠 shift 讘砖托诇谠讘 注诐 诇谳托爪呓 讻赞托 诇呓谳住托专\n" +
"- 讗谠 诇谳抓 谠讙专谠专 诇驻注谠诇呓 诪呓托专呓 托谠转专.";

Calendar._TT["PREV_YEAR"] = "砖谞呓 拽谠赞诪转 - 呓谳讝拽 诇拽讘诇转 转驻专托讟";
Calendar._TT["PREV_MONTH"] = "谳谠赞砖 拽谠赞诐 - 呓谳讝拽 诇拽讘诇转 转驻专托讟";
Calendar._TT["GO_TODAY"] = "注讘谠专 诇呓托谠诐";
Calendar._TT["NEXT_MONTH"] = "谳谠赞砖 呓讘讗 - 呓谳讝拽 诇转驻专托讟";
Calendar._TT["NEXT_YEAR"] = "砖谞呓 呓讘讗呓 - 呓谳讝拽 诇转驻专托讟";
Calendar._TT["SEL_DATE"] = "讘谳专 转讗专托讱";
Calendar._TT["DRAG_TO_MOVE"] = "讙专谠专 诇呓讝讝呓";
Calendar._TT["PART_TODAY"] = " )呓托谠诐(";

// the following is to inform that "%s" is to be the first day of week
// %s will be replaced with the day name.
Calendar._TT["DAY_FIRST"] = "呓爪讙 %s 拽谠赞诐";

// This may be locale-dependent.  It specifies the week-end days, as an array
// of comma-separated numbers.  The numbers are from 0 to 6: 0 means Sunday, 1
// means Monday, etc.
Calendar._TT["WEEKEND"] = "6";

Calendar._TT["CLOSE"] = "住讙谠专";
Calendar._TT["TODAY"] = "呓托谠诐";
Calendar._TT["TIME_PART"] = "(砖托驻讟-)诇谳抓 谠讙专谠专 讻赞托 诇砖谞谠转 注专讱";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "%Y-%m-%d";
Calendar._TT["TT_DATE_FORMAT"] = "%a, %b %e";

Calendar._TT["WK"] = "wk";
Calendar._TT["TIME"] = "砖注呓::";
