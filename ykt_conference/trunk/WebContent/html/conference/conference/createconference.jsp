<%@ include file="/html/commons/init.jsp" %>
<%@ include file="/html/commons/top_calendar.jsp"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TAssemblyRoom" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConferenceType" %>
<%@ page import="java.util.HashMap" %>
<head>
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
 <form action="<%=ContextUtil.getCtxPath(request)%>/createconference.do"
	name=CreateConferenceForm method=post >
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
      <span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<span class="mediumwhite"><strong></strong></span><bean:message key="conference.create"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top">&nbsp; </td>
    </tr>
    <tr> 
      <td align="center" valign="top"><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.name"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<input name=conname class="input_box" maxlength=35  style="width=200"
            		value='<%=ParamUtil.getString(request,"conname")%>'>
            	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            	<a class="portlet-msg-error"><html:errors property="conname" /></a>
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.assembly"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><select name=assembly class="select01"  style="width=200">
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
			<%}else{%>
			<option value="<%=row.getRoomId()%>"><%=row.getRoomName()%></option>
			<%}}%>
			</select></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.type"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><select name=type class="select01" style="width=200">
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
			<%}else{%>
			<option ><%=row.getTypeName()%></option>
			<%}}%>
            </select></td>
          </tr>
          <tr> 
			<td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.begindate"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td width="205"> <input 
            				name=begindate readonly="readonly" class="input_box" maxlength=50  style="width=200" 
            					value='<%=ParamUtil.getString(request,"begindate")%>'> 
                  </td>
                  <td width="25"><a href="#"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/date.gif" width="21" height="21" border="0" id="f_trigger_begindate"></a></td>
                  <td><span class="medium"><a class="portlet-msg-error"><html:errors property="begindate" />&nbsp;</a></span></td>
                </tr>
              </table></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.signtime"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td width="205"> <input 
            				name=signtime readonly="readonly" class="input_box"  style="width=200"
            					value='<%=ParamUtil.getString(request,"signtime")%>'> 
                  </td>
                  <td width="25"><a href="#"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/clock.gif" width="21" height="21" border="0" id="f_trigger_signtime"></a></td>
                  <td><span class="medium"><a class="portlet-msg-error"><html:errors property="signtime" />&nbsp;</a></span></td>
                </tr>
              </table></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.begintime"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td width="205"> <input 
            				name=begintime readonly="readonly" class="input_box"  style="width=200"
            					value='<%=ParamUtil.getString(request,"begintime")%>'> 
                  </td>
                  <td width="25"><a href="#"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/clock.gif" width="21" height="21" border="0" id="f_trigger_begintime"></a></td>
                  <td><span class="medium"><a class="portlet-msg-error"><html:errors property="begintime" />&nbsp;</a></span></td>
                </tr>
              </table></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.endtime"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td width="205"> <input 
            				name=endtime readonly="readonly" class="input_box" style="width=200"
            					value='<%=ParamUtil.getString(request,"endtime")%>'> 
                  </td>
                  <td width="25"><a href="#"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/clock.gif" width="21" height="21" border="0" id="f_trigger_endtime"></a></td>
                  <td><span class="medium"><a class="portlet-msg-error"><html:errors property="enddate" />&nbsp;</a></span></td>
                </tr>
              </table></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.org"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><select name=org class="select01" style="width=200"  >
			<%
				List deptList = new GetDictionary().getDeptList();
				String deptCode = WebKeys.USER_DEPT.toString();
				Iterator iter3 = deptList.iterator();
				while (iter3.hasNext()){
					HashMap row = (HashMap)iter3.next();
					if (deptCode.equals(row.get("deptCode").toString())){
			%>
			<option value="<%=row.get("deptCode")%>" selected="selected"><%=row.get("deptName")%></option>
			<%}else{%>
			<option value="<%=row.get("deptCode")%>"><%=row.get("deptName")%></option>
			<%}}%>
              </select></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.explan"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><textarea name="explan" cols=50 rows=4 ></textarea>
            <a class="portlet-msg-error"><html:errors property="explan" /></a>
            
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.comments"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><textarea name="comments" cols=50 rows=4 maxlength="40"></textarea>
            <a class="portlet-msg-error"><html:errors property="comments" /></a>
            </td>
          </tr>
        </table></td>
    </tr>
    <tr> 
      <td height="50" align="right" valign="middle" class="tdborder02"><input name="Submit3" type="button" class="button_nor" value="<bean:message key="button.ok"/>" onClick="document.forms[0].submit();"> 
        &nbsp;&nbsp;&nbsp; <input name="Submit2" type="reset" class="button_nor" value="<bean:message key="button.cancle"/>"  onClick="javascript:cancelPage();"></td>
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
        singleClick    :    true,
        showsTime	   :	false,
        timeFormat	   :	"24"
    });
    
</script>                  
<script language="JavaScript">
	
	Calendar.setup({
        inputField     :    "signtime",     // id of the input field
        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
    	ifFormat	   :	"<%=GetProperty.getProperties("format.time",getServletContext())%>",
        button         :    "f_trigger_signtime",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true,
        showsTime	   :	true,
        timeFormat	   :	"24"
    });
	Calendar.setup({
        inputField     :    "begintime",     // id of the input field
        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
    	ifFormat	   :	"<%=GetProperty.getProperties("format.time",getServletContext())%>",
        button         :    "f_trigger_begintime",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true,
        showsTime	   :	true,
        timeFormat	   :	"24"
    });
    
	Calendar.setup({
        inputField     :    "endtime",     // id of the input field
        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
        button         :    "f_trigger_endtime",  // trigger for the calendar (button ID)
    	ifFormat	   :	"<%=GetProperty.getProperties("format.time",getServletContext())%>",
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true,
        showsTime	   :	true,
        timeFormat	   :	"24"
    });
</script>                  
</body>
