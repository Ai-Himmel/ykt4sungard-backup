<%@ include file="/html/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
<html:base/>
</head>
<%List result = (List) request.getAttribute("result");%>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<form name="AttendeeInform" id="AttendeeInform" action="<%=ContextUtil.getCtxPath(request)%>/attendeeinform.do" method=post >
	<input type=hidden name=cmd value="stage1">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr> 
		<td>&nbsp;</td>
	</tr>
	<tr> 
		<td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
		<span class="mediumwhite"><strong></strong></span>&nbsp;<span class="mediumwhite"><strong><bean:message key="attendee.inform.stage1"/></strong></span></td>
	</tr>
	<tr> 
		<td align="left" valign="top" >&nbsp;</td>
	</tr>
	<tr> 
		<td align="center" valign="top">
		<ec:table 
				var="pres" 
				items="result" 
				filterable="false"
				imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif" 
				rowsDisplayed="15"
				action="${pageContext.request.contextPath}/attendeeinform.do"
				form="AttendeeInform">
			<ec:row highlightRow="true">		
				<ec:column property="cutId" headerStyle="text-align:center"
					title='<%= GetProperty.getProperties("attendee.custid",getServletContext())%>' >
				</ec:column>
				<ec:column property="stuempNo" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.custno",getServletContext())%>' >
				</ec:column>	
				<ec:column property="cutName" headerStyle="text-align:center"
					style="text-align:center"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.custname",getServletContext())%>' />
				<ec:column property="deptName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.dept",getServletContext())%>' />
				<ec:column property="dutyName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.duty",getServletContext())%>' />
			</ec:row>
		</ec:table>
		</td>
	</tr>
	</table>
</form>
<form name="AttendeeInformForm" id="AttendeeInformForm" action="<%=ContextUtil.getCtxPath(request)%>/attendeeinform.do" method=post >
	<input type=hidden name=cmd value="create">
	<input type=hidden name=confid value='<%=ParamUtil.getString(request,"confid")%>'>
	<input type=hidden name=queryliststring value='<%=ParamUtil.getString(request,"queryliststring")%>'>
	<input type=hidden name=groupliststring value='<%=ParamUtil.getString(request,"groupliststring")%>'>
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr> 
		<td align="center" valign="top">&nbsp;</td>
	</tr>
    <tr> 
      <td height="30" align="left" valign="middle"> 
        <input type="checkbox" name="gselect" value="checkbox" 
		        <c:if test='<%= !ParamUtil.getString(request, "gselect").equals("")%>'>
		        checked
		        </c:if>
        >
        <bean:message key="attendee.inform.continue"/></td>
    </tr>
	<tr> 
		<td height="40" align="right" valign="middle" class="tdborder02"> 
			<input name="Submit" type="button" class="button_nor" value="<bean:message key="button.next"/>" 
				onClick="javascript:setCmdValue('next');">&nbsp;&nbsp;&nbsp; 
			<input name="Submit2" type="button" class="button_nor" value="<bean:message key="button.cancle"/>" 
				onClick="javascript:renderCancelPage();">
		</td>
	</tr>
	</table>
</form>
<script>
	function setCmdValue(cmd) {
		var conid=0;
		if (cmd == 'next') {
      			if (document.AttendeeInformForm.gselect.checked) {
      				cmd = 'stage2';
      			} else {
      				cmd = 'stage4';
      			}
		}
		document.AttendeeInformForm.cmd.value = cmd;
		document.AttendeeInformForm.submit();
	}
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/conf/informconflist.do';
	}
</script>

</body>
