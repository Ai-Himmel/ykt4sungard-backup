<%@ include file="/html/commons/init.jsp" %>
<%@ include file="/html/commons/top_calendar.jsp"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ page import="com.kingstargroup.conference.util.ConferenceUtil" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TAssemblyRoom" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConferenceType" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConference" %>
<%@ page import="java.util.HashMap" %>
<head>
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
</head>
<%
	Integer confid= new Integer(ParamUtil.getInteger(request,"conid"));
	TConference conf = ConferenceUtil.getConfById(confid); 
	String confname = conf.getConName();
	String roomid = conf.getRoomId();
	String conftype = conf.getTypeName();
	String signtime = conf.getConSigntime();
	String begindate = conf.getConBegindate();
	String begintime = conf.getConBegintime();
	String endtime = conf.getConEndtime();
	String deptcode = conf.getOrganigerId();
	String ifs = (conf.getIfSerecy());
	String explain = conf.getConExplain();
	String comments = conf.getComments();
%>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
 <form action="<%=ContextUtil.getCtxPath(request)%>/editconference.do"
	name=EditConferenceForm method=post >
    <input type=hidden name=conid value="<%= confid%>">
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
  <form>
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
      <span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<span class="mediumwhite"><strong></strong></span><bean:message key="conference.edit"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top">&nbsp; </td>
    </tr>
    <tr> 
      <td align="center" valign="top"><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.name"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><input 
            	name=conname class="input_box" maxlength=35  style="width=200" value="<%=confname%>">
            	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
            	<a class="portlet-msg-error"><html:errors property="conname" /></a>
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.assembly"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><select name=assembly class="select01"  style="width=200">
			<%
				List roomList = new GetDictionary().getAssimblyRoom();
				Iterator iter = roomList.iterator();
				while (iter.hasNext()){
					TAssemblyRoom row = (TAssemblyRoom)iter.next();
					if (roomid.equals(row.getRoomId())){
			%>
			<option value="<%=row.getRoomId()%>" selected="selected"><%=row.getRoomName()%></option>
			<%}else%>
			<option value="<%=row.getRoomId()%>"><%=row.getRoomName()%></option>
			<%}%>
			</select></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.type"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><select name=type class="select01" style="width=200">
			<%
				List typeList = new GetDictionary().getConfType();
				Iterator iter2 = typeList.iterator();
				while (iter2.hasNext()){
					TConferenceType row = (TConferenceType)iter2.next();
					if (conftype.equals(row.getTypeName())){
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
                  <td width="205"> <input 
            				name=begindate readonly="readonly" class="input_box" maxlength=50  style="width=200" value="<%=begindate%>" > 
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
            				name=signtime class="input_box" readonly="readonly" style="width=200" value="<%=signtime%>" > 
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
            				name=begintime class="input_box" readonly="readonly" style="width=200" value="<%=begintime%>" > 
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
            				name=endtime class="input_box" readonly="readonly" style="width=200" value="<%=endtime%>"> 
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
				Iterator iter3 = deptList.iterator();
				while (iter3.hasNext()){
					HashMap row = (HashMap)iter3.next();
					if (deptcode.equals(row.get("deptCode"))){
			%>
			<option value="<%=row.get("deptCode")%>" selected="selected"><%=row.get("deptName")%></option>
			<%}else%>
			<option value="<%=row.get("deptCode")%>"><%=row.get("deptName")%></option>
			<%}%>
              </select></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.ifserecy"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><table border="0" cellpadding="0" cellspacing="0">
                <tr align="center"> 
                  <td width="25"> <input name="ifserecy" type="radio"  value="1" checked> 
                  </td>
                  <td width="50" align="left"><bean:message key="chk.yes"/></td>
                  <td width="25"> <input type="radio" name="ifserecy" value="0"> 
                  </td>
                  <td align="left"><bean:message key="chk.no"/></td>
                </tr>
              </table></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.explan"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><textarea name="explan" cols=50 rows=4 ><%=explain%></textarea>
            <a class="portlet-msg-error"><html:errors property="explan" /></a>
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.comments"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><textarea name="comments" cols=50 rows=4  ><%=comments%></textarea>
            <a class="portlet-msg-error"><html:errors property="explan" /></a>
            </td>
          </tr>
        </table></td>
    </tr>
    <tr> 
      <td height="50" align="right" valign="middle" class="tdborder02"><input name="Submit3" type="submit" class="button_nor" value="<bean:message key="button.ok"/>"> 
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
        singleClick    :    true
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
