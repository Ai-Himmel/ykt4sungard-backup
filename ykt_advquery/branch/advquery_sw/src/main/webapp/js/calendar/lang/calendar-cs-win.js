/* 
	calendar-cs-win.js
	language: Czech
	encoding: windows-1250
	author: Lubos Jerabek (xnet@seznam.cz)
	        Jan Uhlir (espinosa@centrum.cz)
*/

// ** I18N
Calendar._DN  = new Array('Ned靗e','Pond靗?,'趖er?,'St雁da','萾vrtek','P医ek','Sobota','Ned靗e');
Calendar._SDN = new Array('Ne','Po','趖','St','萾','P?,'So','Ne');
Calendar._MN  = new Array('Leden','趎or','B雁zen','Duben','Kv腼en','萫rven','萫rvenec','Srpen','Z狲?,'仨jen','Listopad','Prosinec');
Calendar._SMN = new Array('Led','趎o','B雁','Dub','Kv?,'萺v','葀c','Srp','Z狲','仨j','Lis','Pro');

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "O komponent?kalend狲";
Calendar._TT["TOGGLE"] = "Zm靓a prvn韍o dne v t齞nu";
Calendar._TT["PREV_YEAR"] = "P雁dchoz?rok (p凤dr?pro menu)";
Calendar._TT["PREV_MONTH"] = "P雁dchoz?m疱袜 (p凤dr?pro menu)";
Calendar._TT["GO_TODAY"] = "Dne齿?datum";
Calendar._TT["NEXT_MONTH"] = "Dal氻 m疱袜 (p凤dr?pro menu)";
Calendar._TT["NEXT_YEAR"] = "Dal氻 rok (p凤dr?pro menu)";
Calendar._TT["SEL_DATE"] = "Vyber datum";
Calendar._TT["DRAG_TO_MOVE"] = "Chy?a t丑ni, pro p雁sun";
Calendar._TT["PART_TODAY"] = " (dnes)";
Calendar._TT["MON_FIRST"] = "Uka?jako prvn?Pond靗?;
//Calendar._TT["SUN_FIRST"] = "Uka?jako prvn?Ned靗i";

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"For latest version visit: http://www.dynarch.com/projects/calendar/\n" +
"Distributed under GNU LGPL.  See http://gnu.org/licenses/lgpl.html for details." +
"\n\n" +
"V龇面 datumu:\n" +
"- Use the \xab, \xbb buttons to select year\n" +
"- Pou涩jte tla桧tka " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " k v龇面u m疱袜e\n" +
"- Podr潇e tla桧tko my步 na jak闹koliv z t靋h tla桧tek pro rychlej氻 v龇面.";

Calendar._TT["ABOUT_TIME"] = "\n\n" +
"V龇面 鉴su:\n" +
"- Klikn腼e na jakoukoliv z 栳st?v龇面u 鉴su pro zv龤en?\n" +
"- nebo Shift-click pro sn颂en缰n" +
"- nebo klikn腼e a t丑n腼e pro rychlej氻 v龇面.";

// the following is to inform that "%s" is to be the first day of week
// %s will be replaced with the day name.
Calendar._TT["DAY_FIRST"] = "Zobraz %s prvn?;

// This may be locale-dependent.  It specifies the week-end days, as an array
// of comma-separated numbers.  The numbers are from 0 to 6: 0 means Sunday, 1
// means Monday, etc.
Calendar._TT["WEEKEND"] = "0,6";

Calendar._TT["CLOSE"] = "Zavt";
Calendar._TT["TODAY"] = "Dnes";
Calendar._TT["TIME_PART"] = "(Shift-)Klikni nebo t丑ni pro zm靓u hodnoty";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "d.m.yy";
Calendar._TT["TT_DATE_FORMAT"] = "%a, %b %e";

Calendar._TT["WK"] = "wk";
Calendar._TT["TIME"] = "萢s:";
