<%@ include file="/html/commons/init.jsp" %>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TGroup" %>
<%@ page import="com.kingstargroup.conference.common.ParamUtil" %>
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/util.js"></script>
<head>
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<%List result = (List) request.getAttribute("result");	
%>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<form id="ManagerGroup" name="ManagerGroup" action="<%=ContextUtil.getCtxPath(request)%>/attendeemanager.do" method=post >
	<input type=hidden name=cmd value="query">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;
      <span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<bean:message key="attendee.manager"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="left" valign="top" ><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="12%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.groupname"/></td>
            <td width="88%" align="left" valign="middle" bgcolor="#E6ECF2"><select name=groupname class="select01" style="width:200" >
				<%
					List groupList = new GetDictionary().getGroupNameList();
					String groupid="";
					if (null==request.getAttribute("groupid")){
						groupid = "0";
					}else{
						groupid = request.getAttribute("groupid").toString();
					}
					Iterator iter4 = groupList.iterator();
					while (iter4.hasNext()){
						TGroup row = (TGroup)iter4.next();
						if (row.getGroupId().toString().equals(groupid)){
				%>
				<option value="<%=row.getGroupId()%>" selected="selected"><%=row.getGroupName()%></option>
				<%}else{%>
				<option value="<%=row.getGroupId()%>" ><%=row.getGroupName()%></option>
				<%}}%>
              </select>
              <input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.query"/>"  >
              </td>
              
          </tr>
        </table>
      </td>
    </tr>
    <tr> 
      <td align="center" valign="top"><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr align="center" valign="middle"> 
		<td align="center" valign="top">
		<ec:table 
				var="pres" 
				items="result" 
				filterable="false"
				imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif" 
				rowsDisplayed="10"
				action="${pageContext.request.contextPath}/attendeemanager.do"
				form="ManagerGroup">
			<ec:row highlightRow="true">		
				<ec:column property="cutId" headerStyle="text-align:center"
					width="100"
					title='<%= GetProperty.getProperties("attendee.custid",getServletContext())%>' 
					style="text-align:center">
					<input name="custgroups" type="checkbox" value="${pres.cutId}"  onclick="javascript:getSelectValue(ManagerGroup);">${pres.cutId}
				</ec:column>
				<ec:column property="stuempNo" headerStyle="text-align:center"
					width="100"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.custno",getServletContext())%>' />
				<ec:column property="cutName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.custname",getServletContext())%>' >
				</ec:column>	
				<ec:column property="deptName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.dept",getServletContext())%>' />
				<ec:column property="dutyName" headerStyle="text-align:center"
					style="text-align:center"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.duty",getServletContext())%>' />
			</ec:row>
		</ec:table>
		</td>
        </table></td>
    </tr>
    <tr> 
      <td align="center" valign="top">&nbsp;</td>
    </tr>
  </form>
</table>
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<form id="ManagerGroupForm" name="ManagerGroupForm" action="<%=ContextUtil.getCtxPath(request)%>/attendeemanager.do" method=post >
	<input type=hidden name=cmd value="delete">
	<input type=hidden name=groupname value="<%=ParamUtil.getString(request,"groupname")%>">
	<INPUT type=hidden name=selectvalue >
    <tr> 
      <td height="40" align="right" valign="middle" class="tdborder02"> &nbsp;&nbsp;&nbsp; 
        <input name="Submit2" type="submit" class="button_nor" value="<bean:message key="button.delete"/>"> </td>
    </tr>
  </form>
</table>
<script>
  	function getSelectValue(form) {      		
  		document.ManagerGroupForm.selectvalue.value = listChecked(form);
  	}      	
</script>

</body>
