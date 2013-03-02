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

<form id="DelDelegatesForm" name="DelDelegatesForm" action="<%=ContextUtil.getCtxPath(request)%>/querydelegate.do" method="post">
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td>&nbsp;</td>
  </tr>
  <tr> 
    <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
    	<span class="mediumwhite"><strong>
			&nbsp;&nbsp;&nbsp;&nbsp;
			<bean:message key="delegate.list"/>
		</strong></span>
		<c:if test='<%=SessionErrors.contains(request, "delegate.failed.delete")%>'>	
				<font class="portlet-msg-error" style="font-size: 11;">
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<bean:message key="delegate.failed.delete" />
				</font>
		</c:if>	
	</td>
  </tr>
   <tr> 
    <td>&nbsp;</td>
  </tr>
  <tr>
		<td align="center" valign="top">
			<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
				<tr>
					<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
						<bean:message key="delegate.name" />
					</td>
					<td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
						<input name="dlgtName" class="input_box" maxlength="50" >
					</td>
					<td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
						&nbsp;
					</td>
					<td align="left" valign="middle" bgcolor="#E6ECF2">
						&nbsp;
					</td>
				</tr>
			</table>
		</td>
	</tr>
	<tr>
		<td height="40" align="right" valign="middle">
			<input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.query"/>" >
				&nbsp;&nbsp;&nbsp; 
			<input name="Submit2" type="reset" class="button_nor" value="<bean:message key="button.reset"/>">
		</td>
	</tr>
  <tr> 
    <td align="left" valign="top"  class="tdborder02">&nbsp;</td>
  </tr>
  <tr> 
    <td align="center" valign="top">
    	<ec:table items="result"
		    	var="pres"
    			filterable="false"
    			imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
    			rowsDisplayed="10"
    			action=""
    			form="DelDelegatesForm">
			<ec:row highlightRow="true">
				<ec:column property="dlgtId"
						headerStyle="text-align:center"
						title='<%=GetProperty.getProperties("delegate.id",getServletContext())%>' >
					<input name="ids_allbox" type="checkbox" value="${pres.dlgtId}">
					<a href="<%=ContextUtil.getCtxPath(request)%>/para/modifydelegate.do?id=${pres.dlgtId}">${pres.dlgtId}</a>
				</ec:column>
				<ec:column property="dlgtName" headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="true"
						title='<%=GetProperty.getProperties("delegate.name",getServletContext())%>' />
				<ec:column property="operId" headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="true"
						title='<%=GetProperty.getProperties("delegate.operid",getServletContext())%>'>
				</ec:column>
				<ec:column property="comment" headerStyle="text-align:center"
						style="text-align:center"
						filterable="false" 
						sortable="true"
						title='<%=GetProperty.getProperties("delegate.comment",getServletContext())%>' />
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
    	self.location = '<%= ContextUtil.getCtxPath(request)%>/para/createdelegate.do';
	}
	
	function setCmdValue(str) {
		if (window.confirm(str)){
			document.DelDelegatesForm.action='<%=ContextUtil.getCtxPath(request)%>/deletedelegate.do';
			document.DelDelegatesForm.submit();
		}		
	}
	

</script>

</body>