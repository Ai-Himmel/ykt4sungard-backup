<%@ page import="java.util.List" %>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.common.ContextUtil" %>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConference" %>
<%@ page import="java.util.HashMap" %>
<%@ page import="com.kingstargroup.conference.common.DateUtilExtend" %>
<%@ include file="/html/commons/top_calendar.jsp"%>
<%@ include file="/html/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/util.js"></script>
<head>
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css">
<link href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css">
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
</head>
<% List result = (List)request.getAttribute("result"); 
	String custname = ParamUtil.getString(request,"custname");
	String custno = ParamUtil.getString(request,"custno");
	String duty = ParamUtil.getString(request,"duty");
	String deptcode = ParamUtil.getString(request,"deptcode");
	Integer confid = new Integer(ParamUtil.getInteger(request,"confid"));
	String datetime = DateUtilExtend.getNowTime2();
	
%>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

<form id="Replace" name="Replace" action="<%=ContextUtil.getCtxPath(request)%>/replace.do" method=post >
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	
    <tr> 
      <td>&nbsp;<input type=hidden name=cmd value="query"></td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;
      <span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<bean:message key="sign.replacesign"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top" >&nbsp;</td>
    </tr>
    <tr> 
      <td align="left" valign="top" ><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.name"/></td>
            <td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
            	<select name=confid class="select01" style="width: 150" >
				<%
					List confList = new GetDictionary().getConfList();
					Iterator iter2 = confList.iterator();
					while (iter2.hasNext()){
						TConference row = (TConference)iter2.next();
						if (confid.equals(row.getConId())){
				%>
				<option value="<%=row.getConId()%>" selected="selected"><%=row.getConName()%></option>
				<%}else{%>
				<option value="<%=row.getConId()%>" ><%=row.getConName()%></option>
				<%}}%>
              </select></td>
            <td width="15%" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.custno"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<input name=custno class="input_box" style="width: 150" value="<%=custno%>" maxlength=50>
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.custname"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<input name=custname class="input_box" style="width: 150" value="<%=custname%>" maxlength=50>
            </td>
            <td align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.dept"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<select name=deptcode class="select01" style="width: 150" >
            	<OPTION>-</OPTION>
				<%
					List deptList = new GetDictionary().getDeptList();
					Iterator iter1 = deptList.iterator();
					while (iter1.hasNext()){
						HashMap row = (HashMap)iter1.next();
						if (deptcode.equals(row.get("deptCode"))){
						
				%>
				<option value="<%=row.get("deptCode")%>" selected="selected"><%=row.get("deptName")%></option>
				<%}else{%>
				<option value="<%=row.get("deptCode")%>"><%=row.get("deptName")%></option>
				<%}}%>
              </select></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.duty"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<input name=duty class="input_box"  style="width: 150" value="<%=duty%>" maxlength=50>
            </td>
            <td align="center" valign="middle" bgcolor="#E6ECF2">&nbsp;</td>
            <td align="right" valign="middle" bgcolor="#E6ECF2"> 
              <input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.query"/>" >
            </td>
          </tr>
        </table></td>
    </tr>
	<tr> 
		<td align="center" valign="top">
		<ec:table 
				var="pres" 
				items="result" 
				filterable="false"
				imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif" 
				rowsDisplayed="5"
				action="${pageContext.request.contextPath}/replace.do"
				form="Replace">
			<ec:row highlightRow="true">		
				<ec:column property="cutId" headerStyle="text-align:center"
					title='<%= GetProperty.getProperties("attendee.custid",getServletContext())%>'width="80"  >
					<input name="custid" type="radio" value="${pres.cutId}" onclick="javascript:getRadioValue(custid);">
					<a>${pres.cutId}</a>
				</ec:column>
				<ec:column property="stuempNo" headerStyle="text-align:center"
					width="100" 
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.custno",getServletContext())%>' >
				</ec:column>	
				<ec:column property="cutName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.custname",getServletContext())%>' />
				<ec:column property="dutyName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.duty",getServletContext())%>' />
				<ec:column property="deptName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.dept",getServletContext())%>' />
				<ec:column property="attendSign" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.status",getServletContext())%>' />
			</ec:row>
		</ec:table>
		</td>
	</tr>
	</table>
</form>
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<form id="ReplaceForm" name="ReplaceForm" action="<%=ContextUtil.getCtxPath(request)%>/replace.do" method=post >
	<%String custid="";%>
	<input type=hidden name=cmd value="sign">
	<input type=hidden name=confid value="<%=ParamUtil.getString(request,"confid")%>">
	<input type=hidden name=custid value="<%=custid%>">
    <tr> 
      <td height="30" align="left" valign="middle" class="medium"><font color="#000099"><strong><bean:message key="sign.replacer.info"/></strong></font></td>
    </tr>
    <tr> 
      <td align="left" valign="top"><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.custname"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<input name=repname class="input_box" style="width: 150"  maxlength=15>
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.duty"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<input name=repduty class="input_box" style="width: 150"  maxlength=20>
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.signtime"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2"><table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr> 
                  <td width="155"> <input 
            				name=signtime readonly="readonly" class="input_box"  style="width=150"
            					value='<%=datetime%>'> 
                  </td>
                  <td width="25"><a href="#"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/clock.gif" width="21" height="21" border="0" id="f_trigger_signtime"></a></td>
                  <td><span class="medium"><a class="portlet-msg-error"><html:errors property="signtime" />&nbsp;</a></span></td>
                </tr>
              </table></td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.comments"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<input name=repcomments class="input_box" style="width: 400"  maxlength=30>
            </td>
          </tr>
        </table></td>
    </tr>
    <tr> 
      <td height="40" align="right" valign="middle" class="tdborder02">
        <input name="Submit2" type="submit" class="button_nor" value="<bean:message key="button.sign"/>"> 
      </td>
    </tr>
    </form>
</table>
<SCRIPT>
function getRadioValue(col){
	document.ReplaceForm.custid.value=getSelectedRadioValue(col);
}
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

</SCRIPT>
</body>
