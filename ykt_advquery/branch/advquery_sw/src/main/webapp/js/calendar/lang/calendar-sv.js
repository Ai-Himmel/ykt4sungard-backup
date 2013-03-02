// ** I18N

// Calendar SV language (Swedish, svenska)
// Author: Mihai Bazon, <mihai_bazon@yahoo.com>
// Translation team: <sv@li.org>
// Translator: Leonard Norrg錼d <leonard.norrgard@refactor.fi>
// Last translator: Leonard Norrg錼d <leonard.norrgard@refactor.fi>
// Encoding: iso-latin-1
// Distributed under the same terms as the calendar itself.

// For translators: please use UTF-8 if possible.  We strongly believe that
// Unicode is the answer to a real internationalized world.  Also please
// include your contact information in the header, as can be seen above.

// full day names
Calendar._DN = new Array
("s鰊dag",
 "m铼dag",
 "tisdag",
 "onsdag",
 "torsdag",
 "fredag",
 "l鰎dag",
 "s鰊dag");

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
Calendar._SDN_len = 2;
Calendar._SMN_len = 3;

// full month names
Calendar._MN = new Array
("januari",
 "februari",
 "mars",
 "april",
 "maj",
 "juni",
 "juli",
 "augusti",
 "september",
 "oktober",
 "november",
 "december");

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "Om kalendern";

Calendar._TT["ABOUT"] =
"DHTML Datum/tid-v钕jare\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"F鰎 senaste version g?till: http://www.dynarch.com/projects/calendar/\n" +
"Distribueras under GNU LGPL.  Se http://gnu.org/licenses/lgpl.html f鰎 detaljer." +
"\n\n" +
"Val av datum:\n" +
"- Anv鋘d knapparna \xab, \xbb f鰎 att v钕ja 錼\n" +
"- Anv鋘d knapparna " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " f鰎 att v钕ja m铼ad\n" +
"- H表l musknappen nedtryckt p?n珍on av ovanst错nde knappar f鰎 snabbare val.";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"Val av tid:\n" +
"- Klicka p?en del av tiden f鰎 att 鰇a den delen\n" +
"- eller skift-klicka f鰎 att minska den\n" +
"- eller klicka och drag f鰎 snabbare val.";

Calendar._TT["PREV_YEAR"] = "F鰎eg错nde 錼 (h表l f鰎 menu)";
Calendar._TT["PREV_MONTH"] = "F鰎eg错nde m铼ad (h表l f鰎 menu)";
Calendar._TT["GO_TODAY"] = "G?till dagens datum";
Calendar._TT["NEXT_MONTH"] = "F鲽jande m铼ad (h表l f鰎 menu)";
Calendar._TT["NEXT_YEAR"] = "F鲽jande 錼 (h表l f鰎 menu)";
Calendar._TT["SEL_DATE"] = "V钕j datum";
Calendar._TT["DRAG_TO_MOVE"] = "Drag f鰎 att flytta";
Calendar._TT["PART_TODAY"] = " (idag)";
Calendar._TT["MON_FIRST"] = "Visa m铼dag f鰎st";
Calendar._TT["SUN_FIRST"] = "Visa s鰊dag f鰎st";
Calendar._TT["CLOSE"] = "St鋘g";
Calendar._TT["TODAY"] = "Idag";
Calendar._TT["TIME_PART"] = "(Skift-)klicka eller drag f鰎 att 鋘dra tid";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "%Y-%m-%d";
Calendar._TT["TT_DATE_FORMAT"] = "%A %d %b %Y";

Calendar._TT["WK"] = "vecka";
