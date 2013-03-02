// ** I18N
// Calendar PL language
// Author: Artur Filipiak, <imagen@poczta.fm>
// January, 2004
// Encoding: UTF-8
Calendar._DN = new Array
("Niedziela", "Poniedzia艂ek", "Wtorek", "樯roda", "Czwartek", "Pi膮tek", "Sobota", "Niedziela");

Calendar._SDN = new Array
("N", "Pn", "Wt", "樯r", "Cz", "Pt", "So", "N");

Calendar._MN = new Array
("Stycze艅", "Luty", "Marzec", "Kwiecie艅", "Maj", "Czerwiec", "Lipiec", "Sierpie艅", "Wrzesie艅", "Pa藕dziernik", "Listopad", "Grudzie艅");

Calendar._SMN = new Array
("Sty", "Lut", "Mar", "Kwi", "Maj", "Cze", "Lip", "Sie", "Wrz", "Pa藕", "Lis", "Gru");

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "O kalendarzu";

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"For latest version visit: http://www.dynarch.com/projects/calendar/\n" +
"Distributed under GNU LGPL.  See http://gnu.org/licenses/lgpl.html for details." +
"\n\n" +
"Wyb贸r daty:\n" +
"- aby wybra膰 rok u偶yj przycisk贸w \xab, \xbb\n" +
"- aby wybra膰 miesi膮c u偶yj przycisk贸w " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + "\n" +
"- aby przyspieszy膰 wyb贸r przytrzymaj wci橹ni臀ty przycisk myszy nad ww. przyciskami.";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"Wyb贸r czasu:\n" +
"- aby zwi臀kszy膰 warto橹膰 kliknij na dowolnym elemencie selekcji czasu\n" +
"- aby zmniejszy膰 warto橹膰 u偶yj dodatkowo klawisza Shift\n" +
"- mo偶esz r贸wnie偶 porusza膰 myszk臀 w lewo i prawo wraz z wci橹ni臀tym lewym klawiszem.";

Calendar._TT["PREV_YEAR"] = "Poprz. rok (przytrzymaj dla menu)";
Calendar._TT["PREV_MONTH"] = "Poprz. miesi膮c (przytrzymaj dla menu)";
Calendar._TT["GO_TODAY"] = "Poka偶 dzi橹";
Calendar._TT["NEXT_MONTH"] = "Nast. miesi膮c (przytrzymaj dla menu)";
Calendar._TT["NEXT_YEAR"] = "Nast. rok (przytrzymaj dla menu)";
Calendar._TT["SEL_DATE"] = "Wybierz dat臀";
Calendar._TT["DRAG_TO_MOVE"] = "Przesu艅 okienko";
Calendar._TT["PART_TODAY"] = " (dzi橹)";
Calendar._TT["MON_FIRST"] = "Poka偶 Poniedzia艂ek jako pierwszy";
Calendar._TT["SUN_FIRST"] = "Poka偶 Niedziel臀 jako pierwsz膮";
Calendar._TT["CLOSE"] = "Zamknij";
Calendar._TT["TODAY"] = "Dzi橹";
Calendar._TT["TIME_PART"] = "(Shift-)klik | drag, aby zmieni膰 warto橹膰";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "%Y.%m.%d";
Calendar._TT["TT_DATE_FORMAT"] = "%a, %b %e";

Calendar._TT["WK"] = "wk";