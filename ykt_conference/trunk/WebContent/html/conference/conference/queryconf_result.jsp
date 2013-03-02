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
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<form id="QueryConferenceForm" action="<%=ContextUtil.getCtxPath(request)%>/queryconference.do" method=post >
	<tr> 
		<td>&nbsp;</td>
	</tr>
	<tr> 
		<td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
		<span class="mediumwhite"><strong></strong></span>&nbsp;<span class="mediumwhite"><strong><bean:message key="conference.view"/></strong></span></td>
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
				action="${pageContext.request.contextPath}/queryconference.do"
				form="QueryConferenceForm">
			<ec:row highlightRow="true">		
				<ec:column property="conId" headerStyle="text-align:center"
					title='<%= GetProperty.getProperties("conference.id",getServletContext())%>' >
					<a >${pres.conId}</a>
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
					style="text-align:center"
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
					title='<%= GetProperty.getProperties("conference.status",getServletContext())%>' >
					
				</ec:column>
			</ec:row>
		</ec:table>
		</td>
	</tr>
	<tr> 
		<td align="center" valign="top">&nbsp;</td>
	</tr>
	<tr> 
		<td height="40" align="right" valign="middle" class="tdborder02"> 
			<input name="Submit" type="button" class="button_nor" value='<bean:message key="button.return"/>' onClick="javascript:createPage();">
		</td>
	</tr>
	</form>
	</table>
<script>
      	function createPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/conf/queryconference.do';
		}
</script>

</body>
