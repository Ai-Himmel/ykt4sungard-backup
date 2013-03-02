<%@ include file="/html/commons/init.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<head>
	<link
		href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css"
		rel="stylesheet" type="text/css" />
	<html:base />
</head>
<%List resultinfo = (List) request.getAttribute("resultinfo");%>
<%String pretip = request.getAttribute("pretip").toString() ;%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<form name="SignPreview" id="SignPreview"
		action="<%=ContextUtil.getCtxPath(request)%>/preview.do" method=post>
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td>
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="25" align="left" valign="middle"
					background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
					&nbsp;&nbsp;&nbsp;
					<span class="mediumwhite"><strong></strong> </span>&nbsp;
					<span class="mediumwhite"><strong><%=pretip%> </strong> </span>
				</td>
			</tr>
			<tr>
				<td align="left" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<ec:table var="pres" items="delegraylist" filterable="true"
						imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
						rowsDisplayed="16"
						action="${pageContext.request.contextPath}/preview.do"
						form="SignPreview">
						<ec:row highlightRow="true">
							<ec:column property="cutId" headerStyle="text-align:center"
								filterable="true"
								title='<%= GetProperty.getProperties("attendee.custid",getServletContext())%>'>
							</ec:column>
							<ec:column property="stuempNo" headerStyle="text-align:center"
								style="text-align:left" filterable="true" sortable="false"
								title='<%= GetProperty.getProperties("attendee.custno",getServletContext())%>'>
							</ec:column>
							<ec:column property="cutName" headerStyle="text-align:center"
								style="text-align:left" filterable="true" sortable="false"
								title='<%= GetProperty.getProperties("attendee.custname",getServletContext())%>' />
							<ec:column property="deptName" headerStyle="text-align:center"
								style="text-align:left" filterable="true" sortable="false"
								title='<%= GetProperty.getProperties("attendee.dept",getServletContext())%>' />
							<ec:column property="dutyName" headerStyle="text-align:center"
								style="text-align:left" filterable="true" sortable="false"
								title='<%= GetProperty.getProperties("attendee.duty",getServletContext())%>' />
							<ec:column property="attendSign" headerStyle="text-align:center"
								style="text-align:left" filterable="true" sortable="false"
								title='<%= GetProperty.getProperties("attendee.status",getServletContext())%>' />
							<ec:column property="attendTime" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="false"
								title='<%= GetProperty.getProperties("sign.signtime",getServletContext())%>' />
						</ec:row>
					</ec:table>
				</td>
			</tr>
		</table>
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td height="40" align="right" valign="middle" class="tdborder02">
					<input name="Submit2" type="button" class="button_nor"
						value="<bean:message key="button.return"/>"
						onClick="javascript:renderCancelPage();">
				</td>
			</tr>
		</table>

	</form>
	<script>
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/preview.do?confid=<%=ParamUtil.getString(request,"confid")%>&selecttype=delegray';
	}
</script>

</body>

