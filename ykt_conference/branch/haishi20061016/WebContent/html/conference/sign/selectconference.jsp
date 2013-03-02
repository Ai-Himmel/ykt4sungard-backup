<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConference" %>
<%@ include file="/html/commons/init.jsp" %>
<head>
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<form id="SignPreview" name="SignPreview" action="<%=ContextUtil.getCtxPath(request)%>/preview.do" method=post >
		<input type=hidden name=attendeesign value="prev">
	
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;
      <span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<bean:message key="sign.preview.select"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td height="22" align="left" valign="middle"><table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
          <td width="24">&nbsp;</td>
          <td width="25" align="center" valign="middle"><input type="radio" name="selecttype" value="totle" checked="checked"></td>
          <td width="150"><bean:message key="sign.preview.totle"/></td>
          <td width="25" align="center" valign="middle"><input type="radio" name="selecttype" value="delegray"></td>
          <td width="150"><bean:message key="sign.preview.delegray"/></td>
          <td>&nbsp;</td>
        </tr>
      </table></td>
    </tr>

    <tr> 
      <td align="left" valign="top" ><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="10%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.name"/></td>
            <td width="90%" align="left" valign="middle" bgcolor="#E6ECF2"><select name=confid class="select01" style="width: 200" >
				<%
					String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
					List confList = new GetDictionary().getConfList(username);
					String confid = "";
					if (null==session.getAttribute("confid")){
						confid = "0";
					}else{
						confid = session.getAttribute("confid").toString();
					}
					Iterator iter2 = confList.iterator();
					while (iter2.hasNext()){
						TConference row = (TConference)iter2.next();
						if (row.getConId().toString().equals(confid)){
				%>
				<option value="<%=row.getConId()%>" selected="selected"><%=row.getConName()%></option>
				<%}else{%>
				<option value="<%=row.getConId()%>"><%=row.getConName()%></option>
				<%}}%>
              </select>
              <input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.query"/>" ></td>           
          </tr>
        </table></td>
    </tr>
    <tr>
      <td align="left" valign="top" >&nbsp;</td>
    </tr>
  </form>
</table>
</body>
