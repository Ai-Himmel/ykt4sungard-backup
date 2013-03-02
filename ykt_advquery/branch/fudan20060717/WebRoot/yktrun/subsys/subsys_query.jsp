<%@ page import="com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO" %>
<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.SubSysUtil" %>
<%@ page import="com.kingstargroup.advquery.dictionary.TPifDictionary" %>
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
<%String querytype54="0";
		if (null!=session.getAttribute("querytype54")){
		querytype54 = session.getAttribute("querytype54").toString();
	}
	String queryType = ParamUtil.getString(request, "querytype", querytype54);%>
<%String beginDate54d = session.getAttribute("begindate54d").toString();%>
<%String endDate54d = session.getAttribute("enddate54d").toString();%>
<%String beginDate54m = session.getAttribute("begindate54m").toString();%>
<%String endDate54m = session.getAttribute("enddate54m").toString();%>
<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/yktrun/subsys/subsys_queryresult.do" name=subsysform method=post>
	<td>
	<input type=hidden name="querytype"
	value="<%=queryType%>">
	<table width="94%" border="0" align="center" cellpadding="0" cellspacing="0">
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
        <td height="25" align="right" nowrap="nowrap"><bean:message key="query.subsysname" /></td>
        <td nowrap="nowrap"><select name="subsystype" style="width: 155">
		<%
			List subSysList = SubSysUtil.getSubSysName();
			String subSysType = "";
			if (null!=session.getAttribute("subsystype")){
				subSysType = session.getAttribute("subsystype").toString();
			}
			Iterator iter = subSysList.iterator();
			//for (int i = 0; i < typeList.size(); i++) {
			while (iter.hasNext()){
				TPifDictionary value= (TPifDictionary)iter.next();
				String selectedStr = "";
				if (subSysType.equals(value.getId().getDictValue()))
					selectedStr = "selected";
				else
					selectedStr = "";
		%>
		<option value="<%=value.getId().getDictValue()%>" <%=selectedStr%> ><%=value.getDictCaption()%></option>
			<%}%>
        </select></td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
      </tr>
      <tr>
        <td width="8%" align="right" nowrap="nowrap"><bean:message key="query.begindate" /></td>
        <td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate54d%>"/></td>
        <td width="20%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
        <td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
        <td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate54d%>"/></td>
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
        <td height="25" align="right" nowrap="nowrap"><bean:message key="query.subsysname" /></td>
        <td nowrap="nowrap"><select name="subsystype">
		<%
			List subSysList1 = SubSysUtil.getSubSysName();
			String subSysType1 = "";
			if (null!=session.getAttribute("subsystype")){
				subSysType1 = session.getAttribute("subsystype").toString();
			}
			Iterator iter1 = subSysList1.iterator();
			//for (int i = 0; i < typeList.size(); i++) {
			while (iter1.hasNext()){
				TPifDictionary value= (TPifDictionary)iter1.next();
				if (subSysType1.equals(value.getId().getDictValue())){
		%>
		<option value="<%=value.getId().getDictValue()%>" selected="selected"><%=value.getDictCaption()%></option>
		<%}else%>
		<option value="<%=value.getId().getDictValue()%>"><%=value.getDictCaption()%></option>
		<%}%>
        </select></td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
        <td nowrap="nowrap">&nbsp;</td>
      </tr>
      <tr>
        <td width="8%" align="right" nowrap="nowrap"><bean:message key="query.beginmonth" /></td>
        <td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate54m%>" /></td>
        <td width="20%" nowrap="nowrap"><a href="#"><img src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
        <td width="8%" nowrap="nowrap"><bean:message key="query.endmonth" /></td>
        <td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate54m%>" /></td>
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
        <td height="25" align="right" nowrap="nowrap"><bean:message key="query.subsysname" /></td>
        <td nowrap="nowrap"><select name="subsystype">
		<%
			List subSysList2 = SubSysUtil.getSubSysName();
			String subSysType2 = "";
			if (null!=session.getAttribute("subsystype")){
				subSysType2 = session.getAttribute("subsystype").toString();
			}
			Iterator iter2 = subSysList2.iterator();
			//for (int i = 0; i < typeList.size(); i++) {
			while (iter2.hasNext()){
				TPifDictionary value= (TPifDictionary)iter2.next();
				if (subSysType2.equals(value.getId().getDictValue())){
		%>
		<option value="<%=value.getId().getDictValue()%>" selected="selected"><%=value.getDictCaption()%></option>
		<%}else%>
		<option value="<%=value.getId().getDictValue()%>"><%=value.getDictCaption()%></option>
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
		document.subsysform.querytype.value = typevalue;
		self.location = '<%= ContextUtil.getCtxPath(request)%>/yktrun/subsys/subsys_query.jsp?querytype=' + typevalue;
	}
</script>