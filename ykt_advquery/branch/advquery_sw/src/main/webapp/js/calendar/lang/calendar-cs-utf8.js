/* 
	calendar-cs-win.js
	language: Czech
	encoding: windows-1250
	author: Lubos Jerabek (xnet@seznam.cz)
	        Jan Uhlir (espinosa@centrum.cz)
*/

// ** I18N
Calendar._DN  = new Array('Ned臎le','Pond臎l铆','脷ter媒','St艡eda','膶tvrtek','P谩tek','Sobota','Ned臎le');
Calendar._SDN = new Array('Ne','Po','脷t','St','膶t','P谩','So','Ne');
Calendar._MN  = new Array('Leden','脷nor','B艡ezen','Duben','Kv臎ten','膶erven','膶ervenec','Srpen','Z谩艡铆','艠铆jen','Listopad','Prosinec');
Calendar._SMN = new Array('Led','脷no','B艡e','Dub','Kv臎','膶rv','膶vc','Srp','Z谩艡','艠铆j','Lis','Pro');

// tooltips
Calendar._TT = {};
Calendar._TT["INFO"] = "O komponent臎 kalend谩艡";
Calendar._TT["TOGGLE"] = "Zm臎na prvn铆ho dne v t媒dnu";
Calendar._TT["PREV_YEAR"] = "P艡edchoz铆 rok (p艡idr啪 pro menu)";
Calendar._TT["PREV_MONTH"] = "P艡edchoz铆 m臎s铆c (p艡idr啪 pro menu)";
Calendar._TT["GO_TODAY"] = "Dne拧n铆 datum";
Calendar._TT["NEXT_MONTH"] = "Dal拧铆 m臎s铆c (p艡idr啪 pro menu)";
Calendar._TT["NEXT_YEAR"] = "Dal拧铆 rok (p艡idr啪 pro menu)";
Calendar._TT["SEL_DATE"] = "Vyber datum";
Calendar._TT["DRAG_TO_MOVE"] = "Chy钮 a t谩hni, pro p艡esun";
Calendar._TT["PART_TODAY"] = " (dnes)";
Calendar._TT["MON_FIRST"] = "Uka啪 jako prvn铆 Pond臎l铆";
//Calendar._TT["SUN_FIRST"] = "Uka啪 jako prvn铆 Ned臎li";

Calendar._TT["ABOUT"] =
"DHTML Date/Time Selector\n" +
"(c) dynarch.com 2002-2005 / Author: Mihai Bazon\n" + // don't translate this this ;-)
"For latest version visit: http://www.dynarch.com/projects/calendar/\n" +
"Distributed under GNU LGPL.  See http://gnu.org/licenses/lgpl.html for details." +
"\n\n" +
"V媒b臎r datumu:\n" +
"- Use the \xab, \xbb buttons to select year\n" +
"- Pou啪ijte tla膷铆tka " + String.fromCharCode(0x2039) + ", " + String.fromCharCode(0x203a) + " k v媒b臎ru m臎s铆ce\n" +
"- Podr啪te tla膷铆tko my拧i na jak茅mkoliv z t臎ch tla膷铆tek pro rychlej拧铆 v媒b臎r.";

Calendar._TT["ABOUT_TIME"] = "\n\n" +
"V媒b臎r 膷asu:\n" +
"- Klikn臎te na jakoukoliv z 膷谩st铆 v媒b臎ru 膷asu pro zv媒拧en铆.\n" +
"- nebo Shift-click pro sn铆啪en铆\n" +
"- nebo klikn臎te a t谩hn臎te pro rychlej拧铆 v媒b臎r.";

// the following is to inform that "%s" is to be the first day of week
// %s will be replaced with the day name.
Calendar._TT["DAY_FIRST"] = "Zobraz %s prvn铆";

// This may be locale-dependent.  It specifies the week-end days, as an array
// of comma-separated numbers.  The numbers are from 0 to 6: 0 means Sunday, 1
// means Monday, etc.
Calendar._TT["WEEKEND"] = "0,6";

Calendar._TT["CLOSE"] = "Zav艡铆t";
Calendar._TT["TODAY"] = "Dnes";
Calendar._TT["TIME_PART"] = "(Shift-)Klikni nebo t谩hni pro zm臎nu hodnoty";

// date formats
Calendar._TT["DEF_DATE_FORMAT"] = "d.m.yy";
Calendar._TT["TT_DATE_FORMAT"] = "%a, %b %e";

Calendar._TT["WK"] = "wk";
Calendar._TT["TIME"] = "膶as:";
