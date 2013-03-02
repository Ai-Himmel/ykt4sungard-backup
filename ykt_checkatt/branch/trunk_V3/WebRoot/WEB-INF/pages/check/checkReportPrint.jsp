<%@page pageEncoding="GBK"%>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Iterator" %>
<%@ include file="../tiles/include.jsp"%>
<%List checkReportList = (List)request.getAttribute("checkReportList");%>
<html>
  <head>
    <base >
    	<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
    <title>教师考勤报表</title>
 
  <!--media=print 这个属性可以在打印时有效--> 
<style type="text/css">
	@media  print{.noPrint{visibility:hidden !important}}
    .PageNext{page-break-after: always;} 
</style>
  </head>
  
  <body>
  <table width="800" align="center" border=1 cellpadding=1 cellspacing=0 bordercolor=#3462AD bordercolordark=#ffffff  >
		    <div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 教师考勤报表<%=request.getAttribute("syear")%>年<%=request.getAttribute("smonth")%>月 </font> </strong>
		    </div>
		            <tr align="center" > 
		              <td rowspan="3" width="350" valign="middle" ><strong>部门</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>工号</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>姓名</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>考勤类别</strong></td>
		              <td rowspan="3" width="100" valign="middle" ><strong>当月总考勤天数</strong></td>
		              <td></td>
		            </tr>
		            
		            <tr align="center" > 		            
		           
		            </tr>
		             <tr align="center" > 		            
		           
		            </tr>
		            <%
						if (null==checkReportList){%>
		            <tr align="center" > 
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
					  <td align="center" valign="middle" bgcolor="#FFFFFF" >&nbsp;</td>
		            </tr>
					<%	}else{
						String sdate = "";
						String checkInfo="";
						String deptName = "";
						String stuempNo = "";
						String custName = "";
						String custType = "";
						String totNum = "";
						String halfNum = "";
						String linkNum = "";
						String patchMoney = "";
						String holidayNum = "";
						Iterator checkIter = checkReportList.iterator();
						int i=0;
						while (checkIter.hasNext()){
						    ++i;
							Map checkMap = (Map)checkIter.next();
							deptName = checkMap.get("deptName").toString();
							stuempNo = checkMap.get("stuempNo").toString();
							custName = checkMap.get("custName").toString();
							custType = checkMap.get("custType").toString();
							totNum = checkMap.get("totNum").toString();
							 
						 %>
							
		              <tr align="center" > 
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=deptName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=stuempNo%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custName%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=custType%></td>
		              <td align="center" valign="middle" bgcolor="#FFFFFF" ><%=totNum%></td>
		              </tr>
		              
		                <% if(i%34==0){
						%>
							  <tr><td></td><td></td><td></td><td></td><td></td>
							  </tr>
		              </table>
		                    
					<!-- <div class="PageNext"></div> -->
					
				<table width="800" align="center" border=1 cellpadding=1 cellspacing=0 bordercolor=#3462AD bordercolordark=#ffffff  >
		           <div id="titleDiv" class="pageTitle">
			      <strong> <font class="medium"> 教师考勤报表<%=request.getAttribute("syear")%>年<%=request.getAttribute("smonth")%>月 </font> </strong>
		          </div>
		          <tr align="center" > 
		              <td rowspan="3" width="350" valign="middle" ><strong>部门</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>工号</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>姓名</strong></td>
		              <td rowspan="3" width="150" height="24" valign="middle" ><strong>考勤类别</strong></td>
		              <td rowspan="3" width="100" valign="middle" ><strong>当月总考勤天数</strong></td>
		              <td></td>
		            </tr>
		            
		            <tr align="center" > 		            
		           
		            </tr>
		             <tr align="center" > 		            
		           
		            </tr>
		           
		             <%}%>
		            <%}}%>
		                <tr><td></td><td></td><td></td><td></td><td></td></tr>
		         </table>
		        
		      <DIV class="noPrint" > 
		         <table width="80%" algin="center">
		             <tr align="center"><td  align="center"> 
		 
		              <object id="WebBrowser" width=0 height=0 classid="CLSID:8856F961-340A-11D0-A96B-00C04FD705A2"></object>
		              <input  type="button"  class="submitButton" value="页面设置" onclick="javascript:document.all.WebBrowser.ExecWB(8,1)"/>&nbsp;&nbsp;
		              <!--  <input type="button" class="submitButton" value="打印预览" onclick="document.all.WebBrowser.ExecWB(7,1)"/>&nbsp;&nbsp;-->
		              <input  type="button"  class="submitButton" value="  打 印 " onclick="javascript:selfprint()" />&nbsp;&nbsp;
		              <input  type="button"  class="submitButton" value="关闭窗口" onclick="javascript:window.close()" />
		             </td></tr> 
		          </table>
		      </DIV>	
		
  </body>
</html>
<script language="javascript">
	var HKEY_Root,HKEY_Path,HKEY_Key; 
	HKEY_Root="HKEY_CURRENT_USER"; 
	HKEY_Path="\\Software\\Microsoft\\Internet Explorer\\PageSetup\\"; 
	//设置网页打印的页眉页脚为空 
	function PageSetup_Null() 
	{ 
		try 
		{ 
			
			var Wsh=new ActiveXObject("WScript.Shell"); 
			HKEY_Key="header"; 
			Wsh.RegWrite(HKEY_Root+HKEY_Path+HKEY_Key,""); 
			HKEY_Key="footer"; 
			Wsh.RegWrite(HKEY_Root+HKEY_Path+HKEY_Key,""); 
		} 
		catch(e)
		{
			alert("错误是 "+e);
		} 
	}

	function selfprint(){
		PageSetup_Null();
		window.print();
	}
</script>
