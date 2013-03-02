<%@ include file="/html/commons/init.jsp" %>
<%@ include file="/html/commons/top_calendar.jsp"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TAssemblyRoom" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConferenceType" %>
<head>
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
 <form action="<%=ContextUtil.getCtxPath(request)%>/queryconference.do"
	name=QueryConferenceForm method=post >
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
  <form>
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg"><span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;
      	<span class="mediumwhite"><strong></strong></span><bean:message key="conference.query"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top">&nbsp; </td>
    </tr>
    <tr> 
      <td align="center" valign="top"><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.name"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=conname class="input_box" style="width: 150" maxlength=15>
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.assembly"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><select name=confroom style="width: 150" class="select01" onChange="changeCounty()"  >
			<OPTION>-</OPTION>
			<%
				List roomList = new GetDictionary().getAssimblyRoom();
				String roomCode = "";
				if (null!=session.getAttribute("roomcode")){
					roomCode = session.getAttribute("roomcode").toString();
				}
				Iterator iter = roomList.iterator();
				while (iter.hasNext()){
					TAssemblyRoom row = (TAssemblyRoom)iter.next();
					if (roomCode.equals(row.getRoomName())){
			%>
			<option value="<%=row.getRoomId()%>" selected="selected"><%=row.getRoomName()%></option>
			<%}else%>
			<option value="<%=row.getRoomId()%>"><%=row.getRoomName()%></option>
			<%}%>
			</select></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.type"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><select name=type class="select01" style="width: 150" onChange="changeCounty()"  >
			<OPTION>-</OPTION>
			<%
				List typeList = new GetDictionary().getConfType();
				String typeCode = "";
				if (null!=session.getAttribute("deptcode")){
					typeCode = session.getAttribute("deptcode").toString();
				}
				Iterator iter2 = typeList.iterator();
				while (iter2.hasNext()){
					TConferenceType row = (TConferenceType)iter2.next();
					if (typeCode.equals(row.getTypeName())){
			%>
			<option selected="selected"><%=row.getTypeName()%></option>
			<%}else%>
			<option ><%=row.getTypeName()%></option>
			<%}%>
      		</select></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.begindate"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td width="130"> <input 
            				name=begindate class="input_box" style="width: 150" maxlength=8 readonly="true"> 
                  </td>
                  <td><a href="#"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/date.gif" width="21" height="21" border="0" id="f_trigger_begindate"></a></td>
                </tr>
              </table></td>
          </tr>
        </table></td>
    </tr>
    <tr> 
      <td align="center" valign="top">&nbsp;</td>
    </tr>
    <tr> 
      <td height="50" align="right" valign="middle" class="tdborder02"><input name="Submit3" type="button" class="button_nor" value="<bean:message key="button.query"/>" onClick="document.forms[0].submit();">
        &nbsp;&nbsp;&nbsp; 
        <input name="Submit2" type="reset" class="button_nor" value="<bean:message key="button.reset"/>" onClick="reset"></td>
    </tr>
  </form>
</table>
<script>
		function cancelPage() {
      		self.location = '<%= ContextUtil.getCtxPath(request)%>/viewconference.do';
		}
</script>
<script language="JavaScript">
	
	Calendar.setup({
        inputField     :    "begindate",     // id of the input field
        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    
</script>
                  
</body>
