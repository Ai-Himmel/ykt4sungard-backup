<%@ page import="com.kingstargroup.conference.common.ParamUtil" %>
<%@ include file="/html/commons/init.jsp" %>
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/option.js"></script>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
</head>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<form name="AttendeeInformForm" action="<%=ContextUtil.getCtxPath(request)%>/attendeeinform.do" method=post >
	<%String queryliststring=ParamUtil.getString(request,"queryliststring");%>
	<input type=hidden name=cmd value="query">
	<input type=hidden name=confid value='<%=ParamUtil.getString(request,"confid")%>'>
	<input type=hidden name=ifquery value='<%= ParamUtil.getString(request, "ifquery")%>'>
	<input type=hidden name=gselect value='<%= ParamUtil.getString(request, "gselect")%>'>
	<input type=hidden name=groupliststring value='<%=ParamUtil.getString(request,"groupliststring")%>'>
	<input type=hidden name=queryliststring value='<%=queryliststring%>'>
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
      	<span class="mediumwhite"><strong><bean:message key="attendee.inform.stage4"/></strong></span>
      </td>
    </tr>
    <tr> 
      <td align="center" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td height="30" align="left" valign="middle" class="medium" >
        <table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.inform.informcont"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><textarea name="informcontent" cols=85 rows=15></textarea>
            
            </td>
          </tr>
        </table>
      </td>
    </tr>
    <tr> 
      <td align="right" valign="middle" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="right" valign="middle" class="tdborder02" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="right" valign="middle" >
      	<input name="Submit24" type="button" class="button_nor" value="<bean:message key="button.back"/>" onClick="javascript:setCmdValue('back');"> &nbsp;&nbsp; 
      	<input name="Submit24" type="button" class="button_nor" value="<bean:message key="button.inform"/>" onClick="javascript:setCmdValue('inform');"> &nbsp;&nbsp; 
      	<input name="Submit26" type="button" class="button_nor" value="<bean:message key="button.cancle"/>" onClick="javascript:renderCancelPage();" >
      </td>
    </tr>
	</table>
</form>
<script>
  	function setCmdValue(cmd) {   
		if (cmd=='back'){
			if ((document.AttendeeInformForm.gselect.value == 'checkbox')
				&&(document.AttendeeInformForm.ifquery.value == 'checkbox')){
				cmd = 'stage3'
			}else if (document.AttendeeInformForm.gselect.value == 'checkbox'){
				cmd = 'stage2'
			}else {
				cmd = 'stage1'
			}
		}
  		document.AttendeeInformForm.cmd.value = cmd;
  		document.AttendeeInformForm.submit();
  	}   
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/conf/informconflist.do';
	}
</script>
</body>
