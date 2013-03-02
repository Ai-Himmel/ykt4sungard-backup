<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<%String  isdevice = session.getAttribute("isdevice")==null?"0":session.getAttribute("isdevice").toString(); 
  String  ismeal = session.getAttribute("ismeal")==null?"0":session.getAttribute("ismeal").toString();
  String  check_device="";
  String  check_meal="";
  if("1".equals(isdevice)){
     check_device ="checked";
  }else{ 
     check_device ="";
  }
  if("1".equals(ismeal)){
  	 check_meal = "checked";
  }else{
     check_meal = "";
  }
   
%>

<%String beginDate34d = session.getAttribute("begindate34d").toString();
  if(session.getAttribute("beginDate")!=null){
    beginDate34d = session.getAttribute("beginDate").toString();
  }
%>
<%String endDate34d = session.getAttribute("enddate34d").toString();
  if(session.getAttribute("endDate")!=null){
    endDate34d = session.getAttribute("endDate").toString();
  }


%>

<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/yktshop/oneshopaccount/shopaccount_queryresult.do"
	name=oneshopaccountform method=post >
	<td>
	
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			
			<tr>
				<td width="8%" align="right" nowrap="nowrap"><bean:message
					key="query.begindate" /></td>
				<td width="10%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate34d%>" /></td>
				<td width="10%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
				<td width="10%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate34d%>" /></td>
				<td width="10%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_enddate" /></a></td>
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
				<td><input type="checkbox" name="isdevice" value="1" <%=check_device%> ><bean:message key="shopaccount.showdivice"/></td>
				<td><input type="checkbox" name="ismeal" value="1" <%=check_meal%> ><bean:message key="shopaccount.showmeal"/></td>	
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
<script>
	function setQueryType(typevalue) {
		document.oneshopaccountform.querytype.value = typevalue;
		self.location = '<%= ContextUtil.getCtxPath(request)%>/yktshop/oneshopaccount/oneshopaccount_query.jsp?querytype=' + typevalue;
	}
</script>
