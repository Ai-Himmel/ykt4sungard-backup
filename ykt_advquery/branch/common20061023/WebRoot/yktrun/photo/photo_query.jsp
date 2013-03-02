<%@ page import="com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO" %>
<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link
	href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css"
	rel="stylesheet" type="text/css" />
<link
	href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css"
	rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
</head>
<%String querytype51="0";
		if (null!=session.getAttribute("querytype51")){
		querytype51 = session.getAttribute("querytype51").toString();
	}
	String queryType = ParamUtil.getString(request, "querytype", querytype51);%>
<%String beginDate51d = session.getAttribute("begindate51d").toString();%>
<%String endDate51d = session.getAttribute("enddate51d").toString();%>
<%String beginDate51m = session.getAttribute("begindate51m").toString();%>
<%String endDate51m = session.getAttribute("enddate51m").toString();%>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form
	action="<%= ContextUtil.getCtxPath(request)%>/yktrun/photo/photo_queryresult.do"
	name=photoform method=post>
	<td>
	<input type=hidden name="querytype"
	value="<%=queryType%>">
<table width="94%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td nowrap="nowrap"><bean:message key="query.type"/><input
			name="statType" type="radio" value="bydate"
			<c:if test='<%= queryType.equals("0")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('0')" /> <bean:message key="query.bydate" />
			<input type="radio" name="statType"
			value="bymonth"
			<c:if test='<%= queryType.equals("1")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('1')" /><bean:message key="query.bymonth" />
		</td>
	</tr>
</table>
<c:if test='<%= queryType.equals("0")%>'>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td height="40"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td height="25" align="right" nowrap="nowrap"><bean:message key="query.emptype" /></td>
        <td nowrap="nowrap"><select name="emptype">
        <option value="all"><bean:message key="photo.all"/></option>
		<%
			List typeList = new GetQueryConListDAO().getEmpType();
			String cutType = "";
			if (null!=session.getAttribute("cuttype")){
				cutType = session.getAttribute("cuttype").toString();
			}
			Iterator iter = typeList.iterator();
			//for (int i = 0; i < typeList.size(); i++) {
			while (iter.hasNext()){
				String value= (String)iter.next();
				if (cutType.equals(value)){
		%>
		<option value="<%=value%>" selected="selected"><%=value%></option>
		<%}else%>
		<option value="<%=value%>"><%=value%></option>
		<%}%>
<>				
        </select></td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
      </tr>
      <tr>
        <td width="8%" align="right" nowrap="nowrap"><bean:message key="query.begindate" /></td>
        <td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate51d%>"/></td>
        <td width="20%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
        <td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
        <td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate51d%>"/></td>
        <td width="20%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate" /></a></td>
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
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#f8f8f8">
  <tr>
    <td height="30"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
				<td width="66%" class="red_text"><bean:message key="system.note" /></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
				<button onclick="document.forms[0].reset();" ><bean:message key="btn.clear" /></button>
				</td>
        </tr>
    </table></td>
  </tr>
</table>
</c:if> 
<c:if test='<%= queryType.equals("1")%>'>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td height="40"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td height="25" align="right" nowrap="nowrap"><bean:message key="query.emptype" /></td>
        <td nowrap="nowrap"><select name="emptype">
        <option value="all"><bean:message key="photo.all"/></option>
		<%
			List typeList = new GetQueryConListDAO().getEmpType();
			String cutType = "";
			if (null!=session.getAttribute("cuttype")){
				cutType = session.getAttribute("cuttype").toString();
			}
			Iterator iter = typeList.iterator();
			//for (int i = 0; i < typeList.size(); i++) {
			while (iter.hasNext()){
				String value= (String)iter.next();
				if (cutType.equals(value)){
		%>
		<option value="<%=value%>" selected="selected"><%=value%></option>
		<%}else%>
		<option value="<%=value%>"><%=value%></option>
		<%}%>		
        </select></td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
      </tr>
      <tr>
        <td width="8%" align="right" nowrap="nowrap"><bean:message key="query.beginmonth" /></td>
        <td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate51m%>" /></td>
        <td width="20%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
        <td width="8%" nowrap="nowrap"><bean:message key="query.endmonth" /></td>
        <td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate51m%>" /></td>
        <td width="20%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate" /></a></td>
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
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.month",getServletContext())%>",
					        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					</script>
      </tr>
    </table></td>
  </tr>
</table>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#f8f8f8">
  <tr>
    <td height="30"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
				<td width="66%" class="red_text"><bean:message key="system.note" /></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
				<button onclick="document.forms[0].reset();" ><bean:message key="btn.clear" /></button>
				</td>
        </tr>
    </table></td>
  </tr>
</table>
</c:if>
<c:if test='<%= queryType.equals("2")%>'>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td height="40"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
      <tr>
        <td height="25" align="right" nowrap="nowrap"><bean:message key="query.emptype" /></td>
        <td nowrap="nowrap"><select name="emptype">
		<%
			List typeList = new GetQueryConListDAO().getEmpType();
			Iterator iter = typeList.iterator();
			//for (int i = 0; i < typeList.size(); i++) {
			while (iter.hasNext()){
				String value= (String)iter.next();
		%>
		<option value="<%=value%>"><%=value%></option>
		<%}%>
        </select></td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
      </tr>
      <tr>
        <td width="8%" align="right" nowrap="nowrap"><bean:message key="query.begindate" /></td>
        <td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly"/></td>
        <td width="20%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
        <td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
        <td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly"/></td>
        <td width="20%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate" /></a></td>
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
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#f8f8f8">
  <tr>
    <td height="30"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
				<td width="66%" class="red_text"><bean:message key="system.note" /></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
				<button onclick="document.forms[0].reset();" ><bean:message key="btn.clear" /></button>
				</td>
        </tr>
    </table></td>
  </tr>
</table>
</c:if>
</td>
</form>
</tr></table>
<script>
	function setQueryType(typevalue) {
		document.photoform.querytype.value = typevalue;
		self.location = '<%= ContextUtil.getCtxPath(request)%>/yktrun/photo/photo_query.jsp?querytype=' + typevalue;
	}
</script>