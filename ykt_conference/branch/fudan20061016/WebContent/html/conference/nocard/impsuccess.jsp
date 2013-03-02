<%@ include file="/html/commons/init.jsp" %>
<head>
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<% String tipinfo = request.getAttribute("tipinfo").toString(); %>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
      	<span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<span class="mediumwhite">
      	<strong><bean:message key="conference.tip"/></strong></span></strong></span></td>
    </tr>
    <tr> 
      <td height="50" align="left" valign="top">&nbsp; </td>
    </tr>
    <tr> 
      <td align="center" valign="top"><table width="400" border="0" cellspacing="0" cellpadding="0">
          <tr> 
            <td width="20%" align="center" valign="top"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/right.gif" width="60" height="60"></td>
            <td align="center" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td height="25" align="center" valign="middle"><font class="medium"><strong></strong></font></td>
                </tr>
                <tr> 
                  <td height="25" align="left" valign="top" class="medium">&nbsp;&nbsp;&nbsp;&nbsp;<%=tipinfo%></td>
                </tr>
                <tr> 
                  <td height="40" align="center" valign="middle">&nbsp;</td>
                </tr>
              </table></td>
          </tr>
        </table></td>
    </tr>
    <tr> 
      <td align="center" valign="top">&nbsp;</td>
    </tr>
    <tr> 
      <td height="50" align="right" valign="middle" class="tdborder02">
       	<input name="Submit3" type="button" class="button_nor" value="<bean:message key="button.return"/>" 
      	onClick="togo();">
      </td>
    </tr>
	</table>
</body>
<script>
   function togo(){
     self.location="<%= ContextUtil.getCtxPath(request)%>/conf/noCardConfList.do";
   }

</script>