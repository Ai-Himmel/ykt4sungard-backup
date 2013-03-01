// ** I18N

// Calendar LT language
// Author: Martynas Majeris, <martynas@solmetra.lt>
// Encoding: UTF-8
// Distributed under the same terms as the calendar itself.

// For translators: please use UTF-8 if possible.  We strongly believe that
// Unicode is the answer to a real internationalized world.  Also please
// include your contact information in the header, as can be seen above.

// full day names
Calendar._DN = new Array
("Sekmadienis",
 "Pirmadienis",
 "Antradienis",
 "Tre膷iadienis",
 "Ketvirtadienis",
 "Pentadienis",
 "艩e拧tadienis",
 "Sekmadienis");

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
("Sek",
 "Pir",
 "Ant",
 "Tre",
 "Ket",
 "Pen",
 "艩e拧",
 "Sek");

// full month names
Calendar._MN = new Array
("Sausis",
 "Vasaris",
 "Kovas",
 "Balandis",
 "Gegu啪腊",
 "Bir啪elis",
 "Liepa",
 "Rugpj奴tis",
 "Rugs腊jis",
 "Spalis",
 "Lapkritis",
 "Gruodis");

// short month names
Calendar._SMN = new Array
("Sau",
 "Vas",
 "Kov",
 "Bal",
 "Geg",
 "Bir",
 "Lie",
 "Rgp",
 "Rgs",
 "Spa",
 "Lap",
 "Gru");

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "Apie kalendori懦";

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"Naujausi膮 versij膮 rasite: http://www.dynarch.com/projects/calendar/\n" +
"Platinamas pagal GNU LGPL licencij膮. Aplankykite http://gnu.org/licenses/lgpl.html" +
"\n\n" +
"Datos pasirinkimas:\n" +
"- Met懦 pasirinkimas: \xab, \xbb\n" +
"- M腊nesio pasirinkimas: " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + "\n" +
"- Nuspauskite ir laikykite pel腊s klavi拧膮 greitesniam pasirinkimui.";
Calendar._TT["ABOUT_TIME"] = "\n\n" +
"Laiko pasirinkimas:\n" +
"- Spustelkite ant valand懦 arba minu膷i懦 - skai膷ius padid腊s vienetu.\n" +
"- Jei spausite kartu su Shift, skai膷ius suma啪腊s.\n" +
"- Greitam pasirinkimui spustelkite ir pajudinkite pel臀.";

Calendar._TT["PREV_YEAR"] = "Ankstesni metai (laikykite, jei norite meniu)";
Calendar._TT["PREV_MONTH"] = "Ankstesnis m腊nuo (laikykite, jei norite meniu)";
Calendar._TT["GO_TODAY"] = "Pasirinkti 拧iandien膮";
Calendar._TT["NEXT_MONTH"] = "Kitas m腊nuo (laikykite, jei norite meniu)";
Calendar._TT["NEXT_YEAR"] = "Kiti metai (laikykite, jei norite meniu)";
Calendar._TT["SEL_DATE"] = "Pasirinkite dat膮";
Calendar._TT["DRAG_TO_MOVE"] = "Tempkite";
Calendar._TT["PART_TODAY"] = " (拧iandien)";
Calendar._TT["MON_FIRST"] = "Pirma savait腊s diena - pirmadienis";
Calendar._TT["SUN_FIRST"] = "Pirma savait腊s diena - sekmadienis";
Calendar._TT["CLOSE"] = "U啪daryti";
Calendar._TT["TODAY"] = "艩iandien";
Calendar._TT["TIME_PART"] = "Spustelkite arba tempkite jei norite pakeisti";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "%Y-%m-%d";
Calendar._TT["TT_DATE_FORMAT"] = "%A, %Y-%m-%d";

Calendar._TT["WK"] = "sav";
