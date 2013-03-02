<!--

////////////////ÑùÊ½//////////////

document.writeln('<STYLE>');

document.writeln('#menuOut, #menuIn');

document.writeln('{position:absolute;');

document.writeln('top:450px;');

document.writeln('left:-195px;');

document.writeln('width:60px;');

document.writeln('border:1.5px solid red;');

document.writeln('background-color:#FFCC00;');

document.writeln('layer-background-color:#FFCC00;');

document.writeln('font:bold 12px Verdana;');

document.writeln('line-height:20px;}');

document.writeln('</STYLE>');

////////////////////////////////////

if (document.all)

	document.write('<div id="menuIn" style="left:-190" onMouseover="pull()" onMouseout="draw()">')



document.writeln('<layer id="menuOut" onMouseover="pull()" onMouseout="draw()">');

//////////////»­¼ÆËãÆ÷£­begin//////////////////////

document.writeln('<table border="0" cellspacing="0" cellpadding="0" width="100%">');

document.writeln('<tr><td width="100%" valign="top"><table border="2" width="200" cellspacing="0" cellpadding="0" bgcolor="#36C9BE" style="border-color:black" onClick="previouskey=event.srcElement.innerText"><tr>');

document.writeln('<td width="100%" bgcolor="#FFCC00" id="result" style="font:bold 20px Verdana;color:black;text-align=\'right\'">0</td>');

document.writeln('</tr>');

document.writeln('<tr><td width="100%" valign="middle" align="center"><table border="0" width="100%" cellspacing="0" cellpadding="0" style="font:bold 20px Verdana;color:white"><tr>');

document.writeln('<td width="80%" align="center">');

document.writeln('<table border="1" width="100%" cellspacing="0" cellpadding="0" style="cursor:hand;font:bold 20px Verdana;color:white" onMouseover="if (event.srcElement.tagName==\'TD\')event.srcElement.style.color=\'yellow\'" onMouseout="event.srcElement.style.color=\'white\'" onselectStart="return false" onClick="calculate()" height="82">');

document.writeln('<tr>');

document.writeln('<td width="25%" align="center" height="17">7</td>');

document.writeln('<td width="25%" align="center" height="17">8</td>');

document.writeln('<td width="25%" align="center" height="17">9</td>');

document.writeln('<td width="25%" align="center" height="17">/</td>');

document.writeln('</tr><tr><td width="25%" align="center" height="19">4</td>');

document.writeln('<td width="25%" align="center" height="19">5</td>');

document.writeln('<td width="25%" align="center" height="19">6</td>');

document.writeln('<td width="25%" align="center" height="19">*</td>');

document.writeln('</tr><tr><td width="25%" align="center" height="19">1</td>');

document.writeln('<td width="25%" align="center" height="19">2</td>');

document.writeln('<td width="25%" align="center" height="19">3</td>');

document.writeln('<td width="25%" align="center" height="19">-</td>');

document.writeln('</tr><tr><td width="25%" align="center" height="19">0</td>');

document.writeln('<td width="25%" align="center" height="19" onClick="pn();previouskey=1;event.cancelBubble=true">+/-</td>');

document.writeln('<td width="25%" align="center" height="19">.</td>');

document.writeln('<td width="25%" align="center" height="19">+</td>');

document.writeln('</tr></table></td><td width="20%">');

document.writeln('<div align="left">');

document.writeln('<table border="1" width="100%" cellspacing="0" cellpadding="0">');

document.writeln('<tr><td width="100%" style="cursor:hand;font:bold 20px Verdana;color:white;text-align:center" onClick="result.innerText=0;results=\'\'">Çå³ý</td></tr>');

document.writeln('</table>');

document.writeln('</div>');

document.writeln('<div align="left">');

document.writeln('<table border="1" width="100%" cellspacing="0" cellpadding="0" height="81">');

document.writeln('<tr><td width="100%" style="cursor:hand;font:bold 32px Verdana;color:white;text-align:center" onMouseover="event.srcElement.style.color=\'yellow\'" onMouseout="event.srcElement.style.color=\'white\'" onClick="calculateresult()">=</td></tr>');

document.writeln('</table>');

document.writeln('</div>');

//////////////»­¼ÆËãÆ÷£­end//////////////////////

document.writeln('</layer>');



/////////////×ó²àÒÆ³ö/////////////////

function regenerate() {

window.location.reload();

}

function regenerate2() {

if (document.layers)

setTimeout("window.onresize=regenerate", 100);

}

window.onload = regenerate2;

if (document.all) {

document.write('</div>');

slideMenu = document.all.menuIn.style;

boundryR = 0;

boundryL = -190;

}

else {

slideMenu = document.layers.menuOut;

boundryR = 150;

boundryL = 10;

}

function pull() {

if (window.drawMenu)

clearInterval(drawMenu);

pullMenu = setInterval("pullEngine()", 3);

}

function draw() {

clearInterval(pullMenu);

drawMenu = setInterval("drawEngine()", 3);

}

function pullEngine() {

if (document.all && slideMenu.pixelLeft < boundryR)

slideMenu.pixelLeft += 5;

else if(document.layers && slideMenu.left < boundryR)

slideMenu.left += 5;

else if (window.pullMenu)

clearInterval(pullMenu);

}

function drawEngine() {

if (document.all && slideMenu.pixelLeft > boundryL)

slideMenu.pixelLeft -= 5;

else if(document.layers && slideMenu.left > boundryL)

slideMenu.left -= 5;

else if (window.drawMenu)

clearInterval(drawMenu);

}

//////////////¼ÆËãÆ÷//////////////////////

var results=''

var previouskey=''

var re=/(\/|\*|\+|-)/

var re2=/(\/|\*|\+|-){2}$/

var re3=/.+(\/|\*|\+|-).+/

var re4=/\d|\./

var re5=/^[^\/\*\+].+\d$/

var re6=/\./

function calculate(){

if (event.srcElement.tagName=="TD"){

if (event.srcElement.innerText.match(re4)&&previouskey=="=")

results=''

if (result.innerText.match(re3)&&event.srcElement.innerText.match(re)){

if (!results.match(re5)){

result.innerText="Error!"

return

}

results=eval(results)

if (results.toString().length>=12&&results.toString().match(re6))

results=results.toString().substring(0,12)

result.innerText=results

}

results+=event.srcElement.innerText

if (results.match(re2))

results=results.substring(0,results.length-2)+results.charAt(results.length-1)

result.innerText=results

}

}

function calculateresult(){

if (!results.match(re5)){

result.innerText="Error!"

return

}

results=eval(results)

if (results.toString().length>=12&&results.toString().match(re6))

results=results.toString().substring(0,12)

result.innerText=results

}

function pn(){

if (result.innerText.charAt(0)!='-')

result.innerText=results='-'+result.innerText

else if (result.innerText.charAt(0)=='-')

result.innerText=results=result.innerText*(-1)

}

-->