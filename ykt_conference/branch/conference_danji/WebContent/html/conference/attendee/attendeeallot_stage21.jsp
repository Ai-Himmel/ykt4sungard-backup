<%@ include file="/html/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<%List attendeelist = (List) request.getAttribute("attendeelist");
String oneattend = (String)request.getAttribute("oneattend");
%>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<form id="AttendeeAllot" name="AttendeeAllot" action="<%=ContextUtil.getCtxPath(request)%>/attendeeallot.do" method=post >
  <table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr> 
		<td>&nbsp;</td>
	</tr>
	<tr> 
		<td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
		<span class="mediumwhite"><strong></strong></span>&nbsp;<span class="mediumwhite"><strong><bean:message key="attendee.allot.custlist"/></strong></span></td>
	</tr>
	<tr> 
		<td align="left" valign="top" >&nbsp;</td>
	</tr>
	<tr> 
		<td align="center" valign="top">
		<ec:table 
				var="pres" 
				items="attendedList" 
				filterable="false"
				imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif" 
				rowsDisplayed="15"
				action="${pageContext.request.contextPath}/attendeeallot.do"
				form="AttendeeAllot">
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
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.custname",getServletContext())%>' />
				<ec:column property="deptName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.dept",getServletContext())%>' />
				<ec:column property="duty" headerStyle="text-align:center"
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
<form name="AttendeeAllotForm" action="<%=ContextUtil.getCtxPath(request)%>/attendeeallot.do" method=post >
	<input type=hidden name=cmd value="stage4">
	<input type=hidden name=oneattend value='<%=oneattend%>'>
	<input type=hidden name=confid value='<%=ParamUtil.getString(request,"confid")%>'>
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr> 
		<td height="40" align="right" valign="middle" class="tdborder02"> 
      		<input name="Submit3" type="button" class="button_nor" value="<bean:message key="button.back"/>"
      		onClick="javascript:history.go(-1);">&nbsp;&nbsp; 
			<input name="Submit" type="button" class="button_nor" value="<bean:message key="button.next"/>"
			onClick="javascript:setCmdValue();">&nbsp;&nbsp;&nbsp; 
			<input name="Submit2" type="button" class="button_nor" value="<bean:message key="button.cancle"/>" 
				onClick="javascript:renderCancelPage();">
		</td>
	</tr>
	</table>
</form>
<script>
	function setCmdValue() {
  		document.AttendeeAllotForm.cmd.value = 'stage4';
		document.AttendeeAllotForm.submit();
	}
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/conf/attendeeconflist.do';
	}
</script>

</body>
