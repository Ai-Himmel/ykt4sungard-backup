<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
<head>
<title>详细信息</title>
<meta http-equiv="Content-Type" content="text/html;">

<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>


</head>

<body   bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<div id="tableDiv">
	<table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#445386 bordercolordark=#ffffff      id=submenu1>
          <tbody>
        	<tr valign=center>
              <td colspan="2" align="left" valign="middle" bgcolor="#FFFFFF" class="tableHeader1">
			  	姓名：<%=request.getAttribute("clerkName")==null?"":request.getAttribute("clerkName")%><br>
                  卡号：<%=request.getAttribute("cardId")==null?"":request.getAttribute("cardId")%><br>
				部门：<%=request.getAttribute("deptName")==null?"":request.getAttribute("deptName")%>
			 </td>              
           </tr>
       </tbody>
        </table>
         <ec:table items="staticInfoList" var="staticInfo" rowsDisplayed="10" action="workStatic.do?method=viewDetail">
			
				<ec:exportXls fileName="clerkstaticList.xls" tooltip="导出 Excel" />
				<ec:row>					
					<ec:column property="CHECKDATE" width="20%" title="考勤时间"/>
					<ec:column property="DESCRIPTION" width="60%" title="考勤结果"/>
					<ec:column property="EXCEPTIONMINS" title="时间（分钟）"/>					
				</ec:row>
			</ec:table>
	</div>
</body>
</html>
