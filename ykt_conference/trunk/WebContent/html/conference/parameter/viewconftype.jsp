<%@ include file="/html/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>

<head>
	<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
	<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
	<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
	<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css" rel="stylesheet" type="text/css" />
<html:base/>
</head>
<% 
	List result = (List) request.getAttribute("result");
%>

<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

<form id="DeleteConfTypeForm" name="DeleteConfTypeForm" action="<%=ContextUtil.getCtxPath(request)%>/deleteconftype.do" method="post">
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td>&nbsp;</td>
  </tr>
  <tr> 
    <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
    	<span class="mediumwhite"><strong>
			&nbsp;&nbsp;&nbsp;&nbsp;
			<bean:message key="conftype.list"/>
		</strong></span>
		<c:if test='<%=SessionErrors.contains(request, "conftype.failed.delete") %>'>	
			<font class="portlet-msg-error" style="font-size: 11;">
				&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<bean:message key="conftype.failed.delete" />
			</font>
		</c:if>	
	</td>
  </tr>
  <tr> 
    <td align="left" valign="top">&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top">
    	<ec:table items="result"
		    	var="pres"
    			filterable="false"
    			imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
    			rowsDisplayed="10"
    			action=""
    			form="DeleteConfTypeForm">
			<ec:row highlightRow="true">
				<ec:column property="typeId"
						headerStyle="text-align:center"
						title='<%=GetProperty.getProperties("conftype.id",getServletContext())%>' >
					<input name="ids_allbox" type="checkbox" value="${pres.typeId}">
					<a href="<%=ContextUtil.getCtxPath(request)%>/para/modifyconftype.do?id=${pres.typeId}">${pres.typeId}</a>
				</ec:column>
				<ec:column property="typeName" headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("conftype.name",getServletContext())%>' />
				<ec:column property="comments" headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="false"
						title='<%=GetProperty.getProperties("conftype.comments",getServletContext())%>' />
			</ec:row>
		</ec:table>
	</td>
  </tr>
  <tr> 
    <td align="center" valign="top">&nbsp;</td>
  </tr>
  <tr> 
    <td height="40" align="right" valign="middle" class="tdborder02"> 
      <input name="Submit" type="button" class="button_nor" value="<bean:message key="button.create"/>" onClick="javascript:createPage();" >
      &nbsp;&nbsp;&nbsp; 
      <input name="Submit2" type="button" class="button_nor" value="<bean:message key="button.delete"/>" 
      onClick="javascript:setCmdValue('<bean:message key='window.delete.tip'/>');" >
    </td>
  </tr>
</table>
</form>

<script type="text/javascript">

	function createPage() {		
    	self.location = '<%= ContextUtil.getCtxPath(request)%>/para/createconftype.do';
	}
	
	function setCmdValue(str) {
		if (window.confirm(str)){
			document.DeleteConfTypeForm.submit();
		}		
	}

</script>

</body>

