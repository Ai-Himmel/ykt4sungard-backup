<%@ page import="java.util.List" %>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ page import="com.kingstargroup.conference.common.ParamUtil" %>
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
<% 	List result = (List)request.getAttribute("result"); 
	String custname = ParamUtil.getString(request,"custname");
	String custno = ParamUtil.getString(request,"custno");
	String duty = ParamUtil.getString(request,"duty");
	String deptcode = ParamUtil.getString(request,"deptcode");
	Integer confid = new Integer(ParamUtil.getInteger(request,"confid"));
	String datetime = DateUtilExtend.getNowTime2();
	String username = GetterUtil.get((String) request.getSession().getAttribute("username"), "");
%>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<form id="SignNoCard" name="SignNoCard" action="<%=ContextUtil.getCtxPath(request)%>/nocardsign.do" method=post >
	<input type=hidden name=cmd value="query">
    <tr> 
      <td>&nbsp;</td>
    </tr>
    <tr> 
      <td height="25" align="left" valign="middle" background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;
      <span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<bean:message key="sign.signnocard"/></strong></span></td>
    </tr>
    <tr> 
      <td align="left" valign="top" ><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
          <tr> 
            <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="conference.name"/></td>
            <td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
            	<select name=confid class="select01" style="width: 150" >
				<%
					List confList = new GetDictionary().getConfList(username);
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
            	<input name=custno class="input_box" style="width: 150"  maxlength=50 value="<%=custno%>">
            </td>
          </tr>
          <tr> 
            <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key="attendee.custname"/></td>
            <td align="left" valign="middle" bgcolor="#E6ECF2">
            	<input name=custname class="input_box" style="width: 150"  maxlength=50 value="<%=custname%>">
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
            	<input name=duty class="input_box"  style="width: 150" maxlength=50 value="<%=duty%>">
            </td>
            <td align="center" valign="middle" bgcolor="#E6ECF2">&nbsp;</td>
            <td align="right" valign="middle" bgcolor="#E6ECF2"> 
              <input name="Submit" type="submit" class="button_nor" value="<bean:message key="button.query"/>" ></td>
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
				rowsDisplayed="8"
				action="${pageContext.request.contextPath}/nocardsign.do"
				form="SignNoCard">
			<ec:row highlightRow="true">		
				<ec:column property="cutId" headerStyle="text-align:center"
					title='<%= GetProperty.getProperties("attendee.custid",getServletContext())%>' width="80" >
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
    </form>
</table>
<form id="SignNoCardForm" name="SignNoCardForm" action="<%=ContextUtil.getCtxPath(request)%>/nocardsign.do" method=post >
	<%String custid="";%>
	<input type=hidden name=cmd value="sign">
	<input type=hidden name=confid value="<%=ParamUtil.getString(request,"confid")%>">
	<input type=hidden name=custid value="<%=custid%>">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
      <td width="60" align="right" valign="middle" class="medium"><bean:message key="conference.signtime"/></td>
      <td width="122"> <input 
				name=signtime readonly="readonly" class="input_box" style="width=120"
					value='<%=datetime%>'> 
      </td>
      <td width="22"><a href="#"><img src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/clock.gif" width="21" height="21" border="0" id="f_trigger_signtime"></a></td>
      <td width="600" height="40" align="right" valign="middle" class="tdborder02">
        <input name="Submit2" type="submit" class="button_nor" value="<bean:message key="button.sign"/>"> </td>
    </tr>
    </table>
</form>
<SCRIPT>
function getRadioValue(col){
	document.SignNoCardForm.custid.value=getSelectedRadioValue(col);
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
