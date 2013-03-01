<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>
<%@ include file="permission.jsp" %>

<html>
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<% 
   String webip = configs.getString("webip");
   String remark = configs.getString("moretradedetail");
%>
<%String beginDate42d = "";
  if(request.getAttribute("begindate")!=null){
	  beginDate42d = request.getAttribute("begindate").toString();
  }else{
 	  beginDate42d = session.getAttribute("begindate42d").toString();
  }
%>
<%String endDate42d = "";
	if(request.getAttribute("enddate")!=null){
		endDate42d = request.getAttribute("enddate").toString();
	}else{
		endDate42d = session.getAttribute("enddate42d").toString();
	}
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
</script>
<body>
<form action="<%= ContextUtil.getCtxPath(request)%>/moretradedetailresult.do"
	name=moreaccountdetailform method=post >
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>

	<td>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			
			<tr>
				 <td height="25" align="right" nowrap="nowrap"><bean:message key="cutName" /></td>
				
				<td >
				 <input id="Text1" type="text"  /><input id="Hidden1" type="hidden" name="ticketIdOfUser" />
				</td>
				<td> 
				 <a href="#" onclick="selectuser()"> <bean:message key="selectuser"/></a>
				 </td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			
			<tr>
				<td width="8%" align="right" nowrap="nowrap"><bean:message
					key="query.begindate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate42d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate42d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate" /></a></td>
					<script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					    
						Calendar.setup({
					        inputField     :    "enddate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
						    ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					</script>
					
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
				<td width="66%" ><bean:message key="system.note" /><%=remark%></td>
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