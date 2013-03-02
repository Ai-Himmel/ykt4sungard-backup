<%@ page contentType="text/html; charset=UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jstl/core" %>
<%@ taglib prefix="fmt" uri="http://java.sun.com/jstl/fmt" %>
<%@ page import="java.util.Date" %>
<%@ page import="java.text.SimpleDateFormat" %>
<%
  Date now = new Date();

  SimpleDateFormat formatter1 = new SimpleDateFormat ("HH':'mm':'ss");
  String dateStr = formatter1.format(now);
  String hour = dateStr.substring(0,2);
  String minute = dateStr.substring(3,5);
  String second = dateStr.substring(6,8);
%>


<html>
<head>

<style>
INPUT{
        font-size: 10pt;
        font-family: Arial;
        border: solid 0 black;
        background: transparent;
        width:18;
        height:18;
	}
</style>

<script language="javascript">



  /*以下是控件对外提供的方法*/

  function public_getHour() {
    if(form1.hour.value == "") {
      return 0;
    }
    return parseFloat(form1.hour.value);
  }

  function public_setHour(hourStr) {
    var value;
    try {
      var value = parseFloat(hourStr);
      if(value > 23 || value < 0) {
        value = "00";
      }
      else if(value < 9||value==9) {
        value = "0" + value;
      }
      else if(value > 9 && value < 24){
      }
      else {
        value = "00";
      }
    }
    catch(e) {
      value = "00";
    }
    form1.hour.value = value;
  }

  function public_getMinute() {
    if(form1.minute.value == "") {
      return 0;
    }
    return parseFloat(form1.minute.value);
  }

  function public_setMinute(minuteStr) {
    var value;
    try {
      var value = parseFloat(minuteStr);
      if(value > 59 || value < 0) {
        value = "00";
      }
      else if(value < 9||value==9) {
        value = "0" + value;
      }
      else if(value > 9 && value < 59){
      }
      else {
        value = "00";
      }
    }
    catch(e) {
      value = "00";
    }
    form1.minute.value = value;
  }



  function public_getSecond() {
    if(form1.second.value == "") {
      return 0;
    }
    return parseFloat(form1.second.value);
  }

  function public_setSecond(secondStr) {
    var value;
    try {
      var value = parseFloat(secondStr);
      if(value > 59 || value < 0) {
        value = "00";
      }
      else if(value < 9 || value==9) {
        value = "0" + value;
      }
      else if(value > 9 && value < 59){
      }
      else {
        value = "00";
      }
    }
    catch(e) {
      value = "00";
    }
    form1.second.value = value;
  }


  function public_getTime() {
    var hourStr = form1.hour.value;
    var minuteStr = form1.minute.value;
    var secondStr = form1.second.value;
    if(hourStr == "") {
      hourStr = "00";
    }
    if(minuteStr == "") {
      minuteStr = "00";
    }
    if(secondStr == "") {
      secondStr = "00";
    }
    return hourStr + ":" + minuteStr + ":" + secondStr;
  }


  function public_setTime(timeStr) {
    try {
      public_setHour(timeStr.substring(0,2));
      public_setMinute(timeStr.substring(3,5));
      public_setSecond(timeStr.substring(6,8));
    }
    catch(e) {
      form1.hour.value = "00";
      form1.minute.value = "00";
      form1.second.value = "00";
    }
  }


  /*以下是控件内部使用的函数*/
  var currInput = -1;

  function init() {
  	<c:choose>
  		<c:when test="${not empty param.timeStr}">
  			var timeStr = "<c:out value="${param.timeStr}"/>";
  			form1.hour.value = timeStr.substring(0,2);
    		form1.minute.value = timeStr.substring(2,4);
    		form1.second.value = "00";
  		</c:when>
  		<c:otherwise>
  			form1.hour.value = "<%=hour%>";
    		form1.minute.value = "<%=minute%>";
    		form1.second.value = "<%=second%>";
  		</c:otherwise>  	
  	</c:choose>
    
  }

  function fnHandleUp() {
    switch(currInput) {
      case -1:
        return;
      case 0:
        form1.elements[currInput].select();
        var value = form1.elements[currInput].value;
        if(value.charAt(0) == '0') {
          value = parseInt(value.charAt(1));
        }
        else {
          value = parseInt(value);
        }
        if(value == 23 ) {
          form1.elements[currInput].value = "00";
          return;
        }
        value = value + 1;
        if(value <= 9) {
          value = "0" + value;
        }
        form1.elements[currInput].value = value;
        return;
      case 1:
      case 2:
        form1.elements[currInput].select();
        var value = form1.elements[currInput].value;
        if(value.charAt(0) == '0') {
          value = parseInt(value.charAt(1));
        }
        else {
          value = parseInt(value);
        }
        if(value == 55 ) {
          form1.elements[currInput].value = "00";
          return;
        }
        value = value + 5;
        if(value <= 9) {
          value = "0" + value;
        }
        form1.elements[currInput].value = value;
        return;
    }
  }

  function fnHandleDown() {
    switch(currInput) {
      case -1:
        return;
      case 0:
        form1.elements[currInput].select();
        var value = form1.elements[currInput].value;
        if(value.charAt(0) == '0') {
          value = parseInt(value.charAt(1));
        }
        else {
          value = parseInt(value);
        }
        if(value == 0 ) {
          form1.elements[currInput].value = "23";
          return;
        }
        value = value - 1;
        if(value <= 9) {
          value = "0" + value;
        }
        form1.elements[currInput].value = value;
        return;
      case 1:
      case 2:
        form1.elements[currInput].select();
        var value = form1.elements[currInput].value;
        if(value.charAt(0) == '0') {
          value = parseInt(value.charAt(1));
        }
        else {
          value = parseInt(value);
        }
        if(value == 0 ) {
          form1.elements[currInput].value = "55";
          return;
        }
        value = value - 5;
        if(value <= 9) {
          value = "0" + value;
        }
        form1.elements[currInput].value = value;
        return;
    }
  }

  function fnHandleFoucs(index) {
    form1.elements[index].select();
    currInput = index;
  }

  function fnHandleBlur(index) {
    form1.elements[index].value = form1.elements[index].value;
    if(form1.elements[index].value == "") {
      form1.elements[index].value = "00";
    }
    switch(index) {
      case 0:
        var value = form1.elements[index].value;
        if (parseFloat(value) < 0 || parseFloat(value) > 23) {
                form1.elements[index].value = "00";
                form1.elements[index].select();
                return false;
        }
        if (value.length < 2 && form1.elements[index].value != "")
                form1.elements[index].value = "0" + form1.elements[index].value;
        return;
      case 1:
      case 2:
        var value = form1.elements[index].value;
        if (parseFloat(value) < 0 || parseFloat(value) > 59) {
                form1.elements[index].value = "00";
                form1.elements[index].select();
                return false;
        }
        if (value.length < 2 && form1.elements[index].value != "")
                form1.elements[index].value = "0" + form1.elements[index].value;
        return;
    }

    //currInput = -1;
  }

  function fnHandleOnKeyPress() {
    if(event.keyCode >= 48 && event.keyCode <= 57)
      return true;
    else
      return false;
  }

</script>


</head>

<body onload="init();">
<div style="top:0;left:0;position:absolute;height:100%;width:100%" id="mytree">
<form name="form1">

<table border=0 cellspacing="0" cellpadding="0">
  <tr>
    <td rowspan="2" height="20"><input type="text" name="hour" maxlength="2"  onfocus="fnHandleFoucs(0);" onblur="fnHandleBlur(0);"  onkeypress="return fnHandleOnKeyPress();"></td>
    <td rowspan="2" width="1" style="font-size:10pt"  height="20">:</td>
    <td rowspan="2" height="20"><input type="text" name="minute" maxlength="2" onfocus="fnHandleFoucs(1);" onblur="fnHandleBlur(1);"  onkeypress="return fnHandleOnKeyPress();"></td>
    <%--
    <td rowspan="2" width="1" style="font-size:10pt" height="20">:</td>
    <td rowspan="2" height="20"><input type="text" name="second" maxlength="2" onfocus="fnHandleFoucs(2);" onblur="fnHandleBlur(2);"  onkeypress="return fnHandleOnKeyPress();"></td>
     --%>
   
    <td rowspan="2" width="1" style="font-size:10pt" height="20"></td>
    <td rowspan="2" height="20"><input type="hidden" name="second"/></td>
    
    <td height="10" width="10" onclick="fnHandleUp();" style="color:black;font-size:5pt;cursor:hand">▲</td>
  </tr>
  <tr>
    <td height="10" width="10" onclick="fnHandleDown();" style="color:black;font-size:5pt;cursor:hand">▼</td>
  </tr>
</table>
</form>
</div>
</body>
</html>
