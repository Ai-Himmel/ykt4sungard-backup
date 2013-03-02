// ** I18N

// Calendar HU language
// Author: ???
// Modifier: KARASZI Istvan, <jscalendar@spam.raszi.hu>
// Encoding: any
// Distributed under the same terms as the calendar itself.

// For translators: please use UTF-8 if possible.  We strongly believe that
// Unicode is the answer to a real internationalized world.  Also please
// include your contact information in the header, as can be seen above.

// full day names
Calendar._DN = new Array
("Vas醨nap",
 "H闰f?,
 "Kedd",
 "Szerda",
 "Cs黩鰎t鰇",
 "P閚tek",
 "Szombat",
 "Vas醨nap");

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
("v",
 "h",
 "k",
 "sze",
 "cs",
 "p",
 "szo",
 "v");

// full month names
Calendar._MN = new Array
("janu醨",
 "febru醨",
 "m醨cius",
 "醦rilis",
 "m酝us",
 "j鷑ius",
 "j鷏ius",
 "augusztus",
 "szeptember",
 "okt骲er",
 "november",
 "december");

// short month names
Calendar._SMN = new Array
("jan",
 "feb",
 "m醨",
 "醦r",
 "m酝",
 "j鷑",
 "j鷏",
 "aug",
 "sze",
 "okt",
 "nov",
 "dec");

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "A kalend醨iumr髓";

Calendar._TT["ABOUT"] =
"DHTML d医um/id?kiv醠aszt骪n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"a legfrissebb verzi?megtal醠hat? http://www.dynarch.com/projects/calendar/\n" +
"GNU LGPL alatt terjesztve.  L醩d a http://gnu.org/licenses/lgpl.html oldalt a r閟zletekhez." +
"\n\n" +
"D医um v醠aszt醩:\n" +
"- haszn醠ja a \xab, \xbb gombokat az 关 kiv醠aszt醩丑oz\n" +
"- haszn醠ja a " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " gombokat a h髇ap kiv醠aszt醩丑oz\n" +
"- tartsa lenyomva az eg閞gombot a gyors v醠aszt醩hoz.";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"Id?v醠aszt醩:\n" +
"- kattintva n鳆elheti az id鮰\n" +
"- shift-tel kattintva cs鰇kentheti\n" +
"- lenyomva tartva 閟 h鷝va gyorsabban kiv醠aszthatja.";

Calendar._TT["PREV_YEAR"] = "El鲪?关 (tartsa nyomva a men党鰖)";
Calendar._TT["PREV_MONTH"] = "El鲪?h髇ap (tartsa nyomva a men党鰖)";
Calendar._TT["GO_TODAY"] = "Mai napra ugr醩";
Calendar._TT["NEXT_MONTH"] = "K鳆. h髇ap (tartsa nyomva a men党鰖)";
Calendar._TT["NEXT_YEAR"] = "K鳆. 关 (tartsa nyomva a men党鰖)";
Calendar._TT["SEL_DATE"] = "V醠asszon d医umot";
Calendar._TT["DRAG_TO_MOVE"] = "H鷝za a mozgat醩hoz";
Calendar._TT["PART_TODAY"] = " (ma)";

// the following is to inform that "%s" is to be the first day of week
// %s will be replaced with the day name.
Calendar._TT["DAY_FIRST"] = "%s legyen a h闰 els?napja";

// This may be locale-dependent.  It specifies the week-end days, as an array
// of comma-separated numbers.  The numbers are from 0 to 6: 0 means Sunday, 1
// means Monday, etc.
Calendar._TT["WEEKEND"] = "0,6";

Calendar._TT["CLOSE"] = "Bez醨";
Calendar._TT["TODAY"] = "Ma";
Calendar._TT["TIME_PART"] = "(Shift-)Klikk vagy h鷝醩 az 閞t斗 v醠toztat醩丑oz";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "%Y-%m-%d";
Calendar._TT["TT_DATE_FORMAT"] = "%b %e, %a";

Calendar._TT["WK"] = "h闰";
Calendar._TT["TIME"] = "id?";
