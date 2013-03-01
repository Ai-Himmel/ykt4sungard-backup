<%@ page import="com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO" %>
<%@ page import="com.kingstargroup.advquery.dept.TCifDept" %>
<%@ page import="com.kingstargroup.advquery.speciality.TCifSpeciality" %>
<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>
<%@ include file="permission.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<%String querytype44="0";
		if (null!=session.getAttribute("querytype44")){
		querytype44 = session.getAttribute("querytype44").toString();
	}
	String queryType = ParamUtil.getString(request, "querytype", querytype44);%>
<%String beginDate44d = session.getAttribute("begindate44d").toString();%>
<%String endDate44d = session.getAttribute("enddate44d").toString();%>
<%String beginDate44m = session.getAttribute("begindate44m").toString();%>
<%String endDate44m = session.getAttribute("enddate44m").toString();%>
<%String beginDate44w = session.getAttribute("begindate44w").toString();%>
<%String endDate44w = session.getAttribute("enddate44w").toString();%>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/financestat/deptconsume/deptconsumestat_queryresult.do"
	name=deptconsumeform method=post >
	<td>
	<input type=hidden name="querytype" value="<%=queryType%>">
<table width="94%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td nowrap="nowrap" width="53%"><bean:message key="query.type"/><input
			name="statType" type="radio" value="bydate" 
			<c:if test='<%= queryType.equals("0")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('0')" /><bean:message key="query.bydate" />
		<input type="radio"
			name="statType" value="byweek"
			<c:if test='<%= queryType.equals("2")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('2')" /><bean:message key="query.byweek" />
		<input type="radio"
			name="statType" value="bymonth"
			<c:if test='<%= queryType.equals("1")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('1')" /><bean:message key="query.bymonth" />
		</td>
		<TD nowrap="nowrap" align="left" width="47%"><bean:message key="showtitle.type"/>
			<INPUT name="showType" type="radio" checked="checked" value = "line"/><bean:message key="showpic.line"/>
			<INPUT name="showType" type="radio" value = "bar"/><bean:message key="showpic.bar"/>
			<INPUT name="showType" type="radio" value = "stack"/><bean:message key="showpic.stack"/>
			
		</TD>
	</tr>
</table>
<c:if test='<%= queryType.equals("0")%>'>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td height="40"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td width="8%" height="25" align="right" nowrap><bean:message key="query.depno" /></td>
        	<td width="92%">
        	
				<%
					if (null!=session.getAttribute("deptcode")){
				%>
				<input type="text" name="depno" value="<%=session.getAttribute("deptcode")%>" />
				<%}else{%>
				<input type="text" name="depno" value="" />
				<%}%>
        		<!-- 
        		<select name="depno" style="width=155">
					<%
						List deptList = new GetQueryConListDAO().getDeptList();
						String deptCode = "";
						if (null!=session.getAttribute("deptcode")){
							deptCode = session.getAttribute("deptcode").toString();
						}
						Iterator iter = deptList.iterator();
						while (iter.hasNext()){
							Object[] row = (Object[])iter.next();
							if (deptCode.equals(row[0])){
					%>
					<option value="<%=row[0]%>" selected="selected"><%=row[1]%></option>
					<%}else{%>
					<option value="<%=row[0]%>"><%=row[1]%></option>
					<%}}%>
				</select>
				-->
			</td>
      </tr>
    </table>
    <table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td width="8%" align="right" nowrap="nowrap"><bean:message key="query.begindate" /></td>
        <td width="21%" nowrap="nowrap"><input type="text" name="begindate" value="<%=beginDate44d%>" /></td>
        <td width="24%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate"  /></a></td>
        <td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
        <td width="21%" nowrap="nowrap"><input type="text" name="enddate" value="<%=endDate44d%>" /></td>
        <td width="18%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate"  /></a></td>
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
    </table></td>
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
				<button onclick="document.forms[0].submit();"><bean:message
					key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</c:if>
<c:if test='<%= queryType.equals("1")%>'>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td height="40"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td width="8%" height="25" align="right" nowrap><bean:message key="query.depno" /></td>
        	<td width="92%">
        	
				<%if (null!=session.getAttribute("deptcode")){%>
					<input type="text" name="depno" value="<%=session.getAttribute("deptcode")%>" />
				<%}else{%>
					<input type="text" name="depno" value="" />
				<%}%>
        		<!-- 
        		<select name="depno" style="width=155">
					<%
						List deptList = new GetQueryConListDAO().getDeptList();
						String deptCode = "";
						if (null!=session.getAttribute("deptcode")){
							deptCode = session.getAttribute("deptcode").toString();
						}
						Iterator iter = deptList.iterator();
						while (iter.hasNext()){
							Object[] row = (Object[])iter.next();
							if (deptCode.equals(row[0])){
					%>
					<option value="<%=row[0]%>" selected="selected"><%=row[1]%></option>
					<%}else{%>
					<option value="<%=row[0]%>"><%=row[1]%></option>
					<%}}%>
				</select>
				-->
			</td>
      </tr>
    </table>
    <table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td width="8%" align="right" nowrap="nowrap"><bean:message key="query.beginmonth" /></td>
        <td width="21%" nowrap="nowrap"><input type="text" name="begindate" value="<%=beginDate44m%>" /></td>
        <td width="24%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate"  /></a></td>
        <td width="8%" nowrap="nowrap"><bean:message key="query.endmonth" /></td>
        <td width="21%" nowrap="nowrap"><input type="text" name="enddate" value="<%=endDate44m%>" /></td>
        <td width="18%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate"  /></a></td>
					<script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.month",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					    
						Calendar.setup({
					        inputField     :    "enddate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.month",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					</script>

      </tr>
    </table></td>
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
				<button onclick="document.forms[0].submit();"><bean:message
					key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</c:if>
<c:if test='<%= queryType.equals("2")%>'>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td height="40"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td width="8%" height="25" align="right" nowrap><bean:message key="query.depno" /></td>
        	<td width="92%">
        	
				<%
					if (null!=session.getAttribute("deptcode")){
				%>
				<input type="text" name="depno" value="<%=session.getAttribute("deptcode")%>" />
				<%}else{%>
				<input type="text" name="depno" value="" />
				<%}%>
        		<!-- 
        		<select name="depno" style="width=155">
					<%
						List deptList = new GetQueryConListDAO().getDeptList();
						String deptCode = "";
						if (null!=session.getAttribute("deptcode")){
							deptCode = session.getAttribute("deptcode").toString();
						}
						Iterator iter = deptList.iterator();
						while (iter.hasNext()){
							Object[] row = (Object[])iter.next();
							if (deptCode.equals(row[0])){
					%>
					<option value="<%=row[0]%>" selected="selected"><%=row[1]%></option>
					<%}else{%>
					<option value="<%=row[0]%>"><%=row[1]%></option>
					<%}}%>
				</select>
				-->
			</td>
      </tr>
    </table>
    <table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td width="8%" align="right" nowrap="nowrap"><bean:message key="query.begindate" /></td>
        <td width="21%" nowrap="nowrap"><input type="text" name="begindate" value="<%=beginDate44w%>" /></td>
        <td width="24%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate"  /></a></td>
        <td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
        <td width="21%" nowrap="nowrap"><input type="text" name="enddate" value="<%=endDate44w%>" /></td>
        <td width="18%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate"  /></a></td>
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
    </table></td>
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
				<button onclick="document.forms[0].submit();"><bean:message
					key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</c:if>
</td>
</form>
</tr></table>
<script>
	function setQueryType(typevalue) {
		document.deptconsumeform.querytype.value = typevalue;
		self.location = '<%= ContextUtil.getCtxPath(request)%>/financestat/deptconsume/deptconsume_query.jsp?querytype=' + typevalue;
	}
</script>
