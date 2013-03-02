<%@ include file="/html/commons/init.jsp" %>
<%@ page import="com.kingstargroup.conference.util.ParameterUtil" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TGroup" %>

<head>
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
	<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<% 
	String groupId = request.getParameter("id");
	boolean back = false;
	if(null == groupId) {
		back = true;
		groupId = ParamUtil.getString(request,"groupid");
	}

	TGroup group = new TGroup();
	if (!"".equals(groupId) && (null != groupId)) {
		group = ParameterUtil.getAttGroupName(Long.valueOf(groupId));
	}	
%>

<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

<html:form action="modifyattgroupname.do">
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
			<span class="mediumwhite"><strong>
				&nbsp;&nbsp;&nbsp;
				<bean:message key="attgroupname.modify" />
			</strong></span>
			<c:if test='<%=SessionErrors.contains(request, "attgroupname.failed.groupname") %>'>	
				<font class="portlet-msg-error" style="font-size: 11;">
					&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
					<bean:message key="attgroupname.failed.groupname" />
				</font>
			</c:if>	
		</td>
    </tr>
    <tr> 
      <td align="left" valign="top">&nbsp; </td>
    </tr>
    <tr> 
      <td align="center" valign="top">
      	<table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
            	<bean:message key="attgroupname.name" />
            </td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<input name="groupName" class="input_box" maxlength="40" value="<%=back?ParamUtil.getString(request,"groupName"):group.getGroupName()%>">
            	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            	<a class="portlet-msg-error"><html:errors property="groupName" /></a>
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium">
            	<bean:message key="attgroupname.comments" />
            </td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<textarea name="comments" cols=50 rows=5 maxlength="40"><%=back?ParamUtil.getString(request,"comments"):group.getComments()%></textarea>
            	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            	<a class="portlet-msg-error"><html:errors property="comments" /></a>
            </td>
            <input type="hidden" name="groupid" value="<%=groupId%>" >
          </tr>
        </table>
      </td>
    </tr>
    <tr> 
      <td align="center" valign="top">&nbsp;</td>
    </tr>
    <tr> 
      <td height="50" align="right" valign="middle" class="tdborder02">
      	<input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.ok"/>" >
				&nbsp;&nbsp;&nbsp; 
		<input name="Submit2" type="reset" class="button_nor" value="<bean:message key="button.cancle"/>" onclick="javascript:renderCancelPage()">
      </td>
    </tr>
</table>
</html:form>
<script>
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/viewattgroupname.do';
	}
</script>
</body>

