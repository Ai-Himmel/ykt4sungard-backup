<%@ page import="com.kingstargroup.conference.common.ContextUtil" %>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ include file="/html/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ include file="/html/commons/permission.jsp" %>
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/util.js"></script>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<form id="DeleteOper" name="DeleteOper" action="<%=ContextUtil.getCtxPath(request)%>/operator/delete.do" method=post >
	<input type=hidden name=cmd value="query">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr> 
		<td>&nbsp;</td>
	</tr>
	<tr> 
		<td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
		<span class="mediumwhite"><strong><bean:message key="operator.list"/></strong></span></td>
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
				action="${pageContext.request.contextPath}/operator/delete.do"
				form="DeleteOper">
			<ec:row highlightRow="true">		
				<ec:column property="operCode" headerStyle="text-align:center"
					width="100"
					title='<%= GetProperty.getProperties("operator.opercode",getServletContext())%>' >
					<input name="operCode" type="radio" value="${pres.operCode}" onclick="javascript:getRadioValue(operCode);">
					<a href="<%= ContextUtil.getCtxPath(request)%>/usermanage/edit.do?opercode=${pres.operCode}">${pres.operCode}</a>
				</ec:column>
				<ec:column property="operName" headerStyle="text-align:center"
					width="120"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("operator.opername",getServletContext())%>' >
				</ec:column>	
				<ec:column property="deptName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("operator.deptid",getServletContext())%>' />
			</ec:row>
		</ec:table>
		</td>
	</tr>
	</table>
</form>
	<form id="DeleteOperForm" name="DeleteOperForm" action="<%=ContextUtil.getCtxPath(request)%>/operator/delete.do" method=post >
	<input type=hidden name=cmd value="delete">
	<input type=hidden name=operCode value="">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr> 
		<td height="40" align="right" valign="middle" class="tdborder02"> 
			<input name="Submit" type="button" class="button_nor" value="<bean:message key="button.create"/>" 
				onClick="javascript:renderCancelPage();">&nbsp;&nbsp;&nbsp; 
			<input name="Submit2" type="button" class="button_nor" value="<bean:message key="button.delete"/>" 
				onclick="javascript:setCmdValue('<bean:message key='window.delete.tip'/>');">
		</td>
	</tr>
	</table>
</form>
<script>
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/usermanage/add.do';
	}
	function setCmdValue(str) {
		if (window.confirm(str)){
			document.DeleteOperForm.submit();
		}else{
			
		}
		
	}
	function getRadioValue(col){
		document.DeleteOperForm.operCode.value=getSelectedRadioValue(col);
		
	}
	
</script>

</body>
