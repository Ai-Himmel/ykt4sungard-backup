<%@ page import="com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO" %>
<%@ page import="com.kingstargroup.advquery.dept.TCifDept" %>
<%@ page import="com.kingstargroup.advquery.speciality.TCifSpeciality" %>
<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.TicketUtil" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="com.kingstargroup.advquery.dictionary.TPifDictionary" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.CutTypeUtil" %>
<%@ page import="com.kingstargroup.advquery.cuttype.TCifCuttypefee" %>
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
<%String beginDate ="" ;
  if(session.getAttribute("beginDate")!=null){
    beginDate=(String)session.getAttribute("beginDate");
  }
  String endDate ="";
  if(session.getAttribute("endDate")!=null){
   endDate=(String)session.getAttribute("endDate");
  }
  
%>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/ticketquery/result.do"
	name=ticketform method=post >
	<td>
<table width="94%" border="0" align="center" cellpadding="0"
	cellspacing="0">
</table>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td height="40"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr>
	  <td align="right" nowrap="nowrap"><bean:message key="query.begindate" /></td>
		<td nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate%>" >
		  <a href="#"><img
			src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
			border="0"  id="f_trigger_begindate" /></a>		  <a href="#"></a></td>
		<td align="right" nowrap="nowrap"><bean:message key="query.enddate" /></td>
		<td colspan="6" nowrap="nowrap"><a href="#">
		  <input type="text" name="enddate" readonly="readonly" value="<%=endDate%>"/>
		</a><a href="#"></a><a href="#"><img
			src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
			border="0"  id="f_trigger_enddate" /></a></td>
		<script language="JavaScript">
				
				Calendar.setup({
			        inputField     :    "begindate",     // id of the input field
			        weekNumbers		:	false,
			        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
			    	ifFormat	   :	"%Y-%m-%d",
			        align          :    "Tr",           // alignment (defaults to "Bl")
			        singleClick    :    true
			    });
			    
				Calendar.setup({
			        inputField     :    "enddate",     // id of the input field
			        weekNumbers		:	false,
			        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
			    	ifFormat	   :	"%Y-%m-%d",
			        align          :    "Tr",           // alignment (defaults to "Bl")
			        singleClick    :    true
			    });
			</script>
	</tr>
      <TR>
        <td align="right" nowrap="nowrap"><bean:message key="query.emptype" /></td>
        <td align="left" nowrap="nowrap"><select name="custtype" style="width=155">
        <OPTION></OPTION>
        <%
        	List cuttype = CutTypeUtil.getCutType();
        	String typeid = "";
        	if (null!=session.getAttribute("cuttype")){ 
        		typeid = session.getAttribute("cuttype").toString();
        	}
        	Iterator cutiter = cuttype.iterator();
        	while (cutiter.hasNext()){
        		TCifCuttypefee cut = (TCifCuttypefee)cutiter.next();
        		if (typeid.equals(cut.getCutType().toString())){
        %>
			<option value="<%=cut.getCutType()%>" selected="selected"><%=cut.getTypeName()%></option>
			<%}else{%>
			<option value="<%=cut.getCutType()%>"><%=cut.getTypeName()%></option>
			<%}}%>
        </select>
        </td>
        <td nowrap="nowrap" align="right"><bean:message key="query.empno" /></td>
        <td nowrap="nowrap" align="left"><input type="text" name="stuempno" style="width=155"/></td>      
      </TR>
      <tr>
        <td width="12%" align="right" nowrap><bean:message key="query.depno" /></td>
        <td width="25%" height="25" align="left" nowrap>
        
			<%
				if (null!=session.getAttribute("deptcode")){
			%>
			<input type="text" name="depno" value="<%=session.getAttribute("deptcode")%>" />
			<%}else{%>
			<input type="text" name="depno" value="" />
			<%}%>
        	<!-- 
        	<select name="depno" style="width=155">
        			<OPTION>-</OPTION>
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
        <td width="12%" align="right" nowrap="nowrap"><bean:message key="query.savingtype" /></td>
        <td width="20%" align="left" nowrap="nowrap"><select name="tickettype" style="width=155">
        <%	List fillList = TicketUtil.getFillType();
        	String filltype = "";
        	if (null!=session.getAttribute("filltype")){
        		filltype= session.getAttribute("filltype").toString();
        	}
        	Iterator iter2 = fillList.iterator();
        	while (iter2.hasNext()){
        		TPifDictionary dict = (TPifDictionary)iter2.next();
        		if (filltype.equals(dict.getId().getDictValue())){
        %>
        <OPTION value="<%=dict.getId().getDictValue()%>" selected="selected"><%=dict.getDictCaption()%></OPTION>
        <%}else{%>
        <OPTION value="<%=dict.getId().getDictValue()%>"><%=dict.getDictCaption()%></OPTION>
        <%}}%>
        </select></td>
        <td width="12%" align="right" nowrap="nowrap"><bean:message key="ticket.ticketno" /></td>
        <td nowrap="nowrap" align="left"><input type="text" name="billno" style="width=150"/></td>
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
</td>
</form>
</tr></table>
