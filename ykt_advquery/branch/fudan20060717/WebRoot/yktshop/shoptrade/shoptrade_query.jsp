<%@ page import="com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO" %>
<%@ page import="com.kingstargroup.advquery.device.TPifDevice" %>
<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>

<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>

<html>
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>

<%String operCode = session.getAttribute("username").toString();
  String  begindate ="";
  if (null!=session.getAttribute("begindate")){
     begindate = session.getAttribute("begindate").toString();
     }
  String  enddate  = "";
  if (null!=session.getAttribute("enddate")){
     enddate = session.getAttribute("enddate").toString();
     }
     
  String  stuempNo = "";
  if (null!=session.getAttribute("stuempNo")){
    stuempNo =  session.getAttribute("stuempNo").toString();
    }
  String  name = "";
  if (null!=session.getAttribute("name")){
    name =session.getAttribute("name").toString();
    }
%>
<body>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/shoptraderesult.do"
	 method=post >
	<td>
<br>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td nowrap="nowrap" ><bean:message key="special.custid"/></td>
				<td nowrap="nowrap"><input type="text"  name="stuempNo" size="20" value="<%=stuempNo%>"></td>
				<td nowrap="nowrap"></td>
				
				<td nowrap="nowrap"  ><bean:message key="special.name"/></td>
				<td nowrap="nowrap"><input type="text"  name="name" size="20" value="<%=name%>"></td>
			</tr>
			<tr>
				<td width="10%" align="right" nowrap="nowrap"><bean:message
					key="query.begindate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" value="<%=begindate%>" size="20"/></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
				<td width="10%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" value="<%=enddate%>"  size="20"/></td>
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
			<tr>
			  <td height="25" align="right" nowrap="nowrap"><bean:message
					key="query.posid" /></td>
				<td nowrap="nowrap"><select name="posid" style="width = 140">
				 <option value="">--</option>
				<%  
					String posId = "";
					String posids="";
					if (null!=session.getAttribute("posid")){
						posId = session.getAttribute("posid").toString();
					}
					List list = new GetQueryConListDAO().getPosDeviceListByLimit(operCode);
					Iterator iter = list.iterator();
					
					while (iter.hasNext()){
						Object[] row = (Object[])iter.next();
						posids =posids +"'"+ row[0]+"',";
						
						if (posId.equals((row[0]).toString())){
						
				%>  
				   
					<option value="<%=row[0]%>" selected="selected"><%= row[1]%></option>
				<%}else%>
					<option value="<%=row[0]%>"><%= row[1]%></option>
				
				<%}%>
				</select></td>
			</tr>
		</table>
		</td>
	</tr>
</table>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0" bgcolor="#f8f8f8">
	<input type="hidden" name="posids" value="<%=posids%>">
	<tr>
		<td height="30">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="66%" class="red_text"><bean:message key="system.note" /></td>
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
</form>
</tr></table>
</body>
</html>

