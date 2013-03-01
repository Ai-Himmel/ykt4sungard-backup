<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>
<%@ include file="permission.jsp" %>
<html>
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<% 
   String webip = configs.getString("webip");
   String remark = configs.getString("cardbalance");
%>
<script>
function selectuser() {
        vReturnValue = null;
        var param = 'showUserSelector=True&showOriganizationUnitSelector=False&showRoleSelector=False&showOriganizationUnitRoleSelector=False&showPrIsSingleSelect=False';
        
        selectObjectsURL = 'http://<%=webip%>/advquery/Redirect.jsp?'+param;
        if (document.all["Hidden1"].value != ""){
            selectObjectsURL = selectObjectsURL + "&TicketID=" + document.all["Hidden1"].value;
        }

        vReturnValue = window.showModalDialog(selectObjectsURL, "", "resizable=none;dialogWidth=800px;dialogHeight=600px");
        
        if (vReturnValue != null) {
            if (vReturnValue.indexOf("|") >= 0) {
                document.all["Hidden1"].value = vReturnValue.split("|")[0];
                document.all["Text1"].value = vReturnValue.split("|")[1];
                
             }
            else {
                document.all["Hidden1"].value = vReturnValue;
            }
        }
    }

function selectdept() {
	 vReturnValue = null;
        var param = 'showUserSelector=False&showOriganizationUnitSelector=True&showRoleSelector=False&showOriganizationUnitRoleSelector=False&showPrIsSingleSelect=False';
        
        selectObjectsURL = 'http://<%=webip%>/advquery/Redirect.jsp?'+param;
        if (document.all["Hidden2"].value != ""){
            selectObjectsURL = selectObjectsURL + "&TicketID=" + document.all["Hidden2"].value;
        }

        vReturnValue = window.showModalDialog(selectObjectsURL, "", "resizable=none;dialogWidth=800px;dialogHeight=600px");
        
        if (vReturnValue != null) {
            if (vReturnValue.indexOf("|") >= 0) {
                document.all["Hidden2"].value = vReturnValue.split("|")[0];
                document.all["Text2"].value = vReturnValue.split("|")[1];
              
             }
            else {
                document.all["Hidden2"].value = vReturnValue;
            }
        }
        
}

</script>
</head>
<body>
<form action="<%= ContextUtil.getCtxPath(request)%>/cardbalanceresult.do"	name="cardbalanceform" method="post" >
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>

	<td>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<br/>
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="cutName" /></td>
				<td >
				 <input id="Text1" type="text"  /><input id="Hidden1" type="hidden" name="ticketIdOfUser" />
				 <a href="#" onclick="selectuser()"> <bean:message key="selectuser"/></a>
				 </td>
				
				
				<td height="25" align="right" nowrap="nowrap"><bean:message key="deptName" /></td>
				<td align="left">
				 <input id="Text2" type="text"  /><input id="Hidden2" type="hidden" name="ticketIdOfDept" />
				  <a href="#" onclick="selectdept()"> <bean:message key="selectdept"/></a>
				 </td>
				
			</tr>
			
		</table>
		</td>
	</tr>
</table>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0" bgcolor="#f8f8f8">
	<tr>
		<td height="30">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="66%" ><bean:message key="system.note" /><%=remark %></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>

</tr></table>
</form>
</body>
</html>