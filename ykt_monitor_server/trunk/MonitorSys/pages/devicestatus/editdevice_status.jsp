<%@ page language="java"  pageEncoding="UTF-8"%>
<%@ include file="../commons/init.jsp" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>运行维护</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
    <script type="text/javascript">
    function init(){
       document.getElementById("detail").style.display='none';
    }
    function sub(){
      document.devicestatusForm.submit();
    }
    </script>   
  </head>
  <body  onload="init()">
  <html:form action="/devicestatus.do?method=updateDeviceStatus">
       <table width=60% align="center">
        <tr>
            <td>是否接受<html:radio property="receive"   value="1"/> </td>
            <td>是否忽略<html:radio property="receive"   value="0"/></td>
         </tr>
       </table>
       <table width=60% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff      id=submenu1>
         <input  name="id" type="hidden" value="<bean:write name="result" property="id" />"/>
         <input  name="deviceid" type="hidden" value="<bean:write name="result" property="deviceid" />"/>
         
         <tr>
            <td align=center>设备id</td><td align="left"><bean:write name="result" property="devphyid" />&nbsp;</td> 
         </tr>
         <tr>
            <td align=center>设备名</td><td align="left"><bean:write name="result" property="devicename" />&nbsp;</td> 
         </tr>
         <tr>
            <td align=center>故障原因</td><td align="left"><bean:write name="result" property="statename" />&nbsp;</td> 
         </tr>
         <tr>
            <td align=center>起始时间</td><td align="left"><bean:write name="result" property="errstarttime" />&nbsp;</td> 
         </tr>
         <tr>
            <td align=center>持续时间</td><td align="left"><bean:write name="result" property="errlasttime" />&nbsp;</td> 
         </tr>
         
        <div id="detail"> 
         <tr >
            <td align=center>忽略到何时</td><td align="left"><html:text size="15" property="canceltime"></html:text>格式:2009-07-31&nbsp;</td> 
          
         </tr>
        
         <tr>
            <td align=center>忽略原因</td><td align="left"><html:textarea    property="cancelreason"></html:textarea>&nbsp;</td> 
         </tr>
         </div>
  
         <tr>
           <td COLSPAN="2" align="center">
             <input name="send" type="button" value="保存"  onclick="sub()"/>
             <input name="back" type="button" value="返回"  onclick="javascript:history.go(-1);"/> 
           
          </tr> 
        </table>
      <input  name="detailCount" type="hidden" value="0">
    </html:form>      
    
  </body>
</html>
