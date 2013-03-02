<%@ include file="/html/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ page import="com.kingstargroup.conference.util.ConferenceUtil" %>
<%@ include file="/html/commons/permission.jsp" %>
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/util.js"></script>
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
	<form name="AttendeeAllot" id="AttendeeAllot" action="<%=ContextUtil.getCtxPath(request)%>/attendeeallot.do" method=post >
	<input type=hidden name=cmd value="next">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr> 
		<td>&nbsp;</td>
	</tr>
	<tr> 
		<td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
		<span class="mediumwhite"><strong></strong></span>&nbsp;<span class="mediumwhite"><strong><bean:message key="attendee.allot.conflist"/></strong></span></td>
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
				rowsDisplayed="10"
				action=""
				form="AttendeeAllot">
			<ec:row highlightRow="true">		
				<ec:column property="conId" headerStyle="text-align:center"
					title='<%= GetProperty.getProperties("conference.id",getServletContext())%>' >
					<input name="confid" type="radio" value="${pres.conId}" onclick="getRadioValue(confid);">
					<a>${pres.conId}</a>
				</ec:column>
				<ec:column property="conName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("conference.name",getServletContext())%>' >
				</ec:column>	
				<ec:column property="typeName" headerStyle="text-align:center"
					style="text-align:center"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("conference.type",getServletContext())%>' />
				<ec:column property="beginDate" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("conference.begindate",getServletContext())%>' />
				<ec:column property="beginTime" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("conference.begintime",getServletContext())%>' />
				<ec:column property="deptName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("conference.org",getServletContext())%>' />
				<ec:column property="roomName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("conference.assembly",getServletContext())%>' />
				<ec:column property="status" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("conference.status",getServletContext())%>' />
			</ec:row>
		</ec:table>
		</td>
	</tr>
	</table>
</form>
	<form name="AttendeeAllotForm" action="<%=ContextUtil.getCtxPath(request)%>/attendeeallot.do" method=post >
	<input type=hidden name=cmd value="">
	<input type=hidden name=confid value="">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr> 
		<td height="40" align="right" valign="middle" class="tdborder02"> 
			<input name="Submit" type="button" class="button_nor" value="<bean:message key="button.allot"/>" onClick="javascript:setCmdValue('next');">
			&nbsp;&nbsp;&nbsp; 
			<input name="Submit2" type="button" class="button_nor" value="<bean:message key="button.send"/>" onClick="javascript:setCmdValue('send');">
		</td>
	</tr>
	</table>
	</form>
<script>
	function setCmdValue(cmd) {
		var conid=0;
		if (cmd == 'next') {
      		cmd = 'stage1';
		}
		document.AttendeeAllotForm.cmd.value = cmd;
		document.AttendeeAllotForm.submit();
	}
	function getRadioValue(col){
		document.AttendeeAllotForm.confid.value=getSelectedRadioValue(col);
	}
</script>

</body>
