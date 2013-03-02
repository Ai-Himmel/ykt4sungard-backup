<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TDevice" %>
<%@ include file="/html/commons/init.jsp" %>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/option.js"></script>
</head>
<%
String oneattend = (String)request.getAttribute("oneattend");
%>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<form name="AttendeeAllotForm" action="<%=ContextUtil.getCtxPath(request)%>/attendeeallot.do" method=post >
	<input type=hidden name=cmd value="create">
	<input type=hidden name=oneattend value='<%=oneattend%>'>
	<input type=hidden name=confid value='<%=ParamUtil.getString(request,"confid")%>'>
  <table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
      <span class="mediumwhite"><strong><bean:message key="attendee.allot.stage3"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="center" valign="top" ><table width="800" border="0" cellspacing="0" cellpadding="0">
          <tr align="center" valign="top"> 
            <td><font color="#FF0000"> 
              <select name="devsrclist" size="10" style="width: 350" ondblclick="transferOption(this.form.devsrclist, this.form.devdestlist,false)" >
				<%
					List devList = GetDictionary.getDeviceList();
					Iterator iter2 = devList.iterator();
					while (iter2.hasNext()){
						TDevice row = (TDevice)iter2.next();
				%>
				<option value="<%=row.getDeviceid()%>"><%=row.getDevicename()%></option>
				<%}%>
              </select>
              </font></td>
            <td width="10%" valign="middle">
              <p> 
                <input name="Submit22" type="button" class="button_nor" value="<bean:message key="button.add"/>"
                onclick="transferOption(this.form.devsrclist, this.form.devdestlist,false)">
              </p>
              <p> 
                <input name="Submit23" type="button" class="button_nor" value="<bean:message key="button.move"/>"
                onclick="returnOption(this.form.devdestlist, this.form.devsrclist,false)">
              </p>
            </td>
            <td><font color="#FF0000"> 
              <select name="devdestlist" size="10" style="width: 350" ondblclick="returnOption(this.form.devdestlist, this.form.devsrclist,false)">
              </select>
              </font></td>
          </tr>
        </table></td>
    </tr>
    <tr> 
      <td height="30" align="left" valign="middle" class="medium" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="right" valign="middle" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="right" valign="middle" class="tdborder02" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="right" valign="middle" >
      	<input name="Submit242" type="button" class="button_nor" value="<bean:message key="button.back"/>" 
      		onClick="javascript:history.go(-1)" > &nbsp;&nbsp; 
        <input name="Submit24" type="button" class="button_nor" value="<bean:message key="button.allot"/>"
        	onClick="javascript:setCmdValue('allot')"> &nbsp;&nbsp; 
        <input name="Submit26" type="button" class="button_nor" value="<bean:message key="button.cancle"/>" 
        	onClick="javascript:renderCancelPage();"></td>
    </tr>
  </table>
</form>
<script>
  	function setCmdValue(cmd) {      		
		var devlist="";
  		document.AttendeeAllotForm.cmd.value = cmd;
  		document.AttendeeAllotForm.submit();
  	}   
  	   	
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/conf/attendeeconflist.do';
	}
</script>
</body>
