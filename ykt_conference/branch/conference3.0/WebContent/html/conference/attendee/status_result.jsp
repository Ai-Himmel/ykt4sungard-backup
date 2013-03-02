<%@ include file="/html/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ page import="com.kingstargroup.conference.util.SignUtil" %>
<%@ page import="com.kingstargroup.conference.util.GetDictionary" %>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConference" %>
<%@ page import="com.kingstargroup.conference.common.StringUtil" %>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
<html:base/>
</head>
<%List result = (List) request.getAttribute("result");
	TConference conf = (TConference)SignUtil.getConfInfoById(ParamUtil.getInteger(request,"confid"));
  String tip = request.getAttribute("tip").toString();
%>
<body   bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
<form id="AllotInformForm" name="AllotInform" action="<%=ContextUtil.getCtxPath(request)%>/attendeeinform/list.do" method=post >
<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr> 
    <td>&nbsp;</td>
  </tr>
  <tr> 
    <td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;<span class="mediumwhite">
    	<strong>&nbsp;&nbsp;&nbsp;<bean:message key="attendee.statusquery.result"/></strong></span></td>
  </tr>
  <tr>
    <td align="left" valign="top" >&nbsp;</td>
  </tr>
  <tr> 
    <td align="left" valign="top" ><table width="100%" border="1" cellspacing="0" cellpadding="2" bordercolor="#FFFFFF"  bordercolordark="#F2F2F2">
        <tr> 
          <td width="15%" height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key ="conference.name"/></td>
          <td align="left" valign="middle" bgcolor="#E6ECF2"><%=conf.getConName()%></td>
        </tr>
        <tr> 
          <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key ="conference.assembly"/></td>
          <td align="left" valign="middle" bgcolor="#E6ECF2"><%=new GetDictionary().getAssemblyNameById(conf.getRoomId())%></td>
        </tr>
        <tr> 
          <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key ="conference.type"/></td>
          <td align="left" valign="middle" bgcolor="#E6ECF2"><%=conf.getTypeName()%></td>
        </tr>
        <tr> 
          <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key ="conference.org"/></td>
          <td align="left" valign="middle" bgcolor="#E6ECF2"><%=new GetDictionary().getDeptNameByDeptCode(conf.getOrganigerId())%></td>
        </tr>

        <tr> 
          <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key ="attendee.inform.informcont"/></td>
          <td align="left" valign="middle" bgcolor="#E6ECF2">
          <textarea name="informcontent" cols=85 rows=4 readonly="readonly"><%=StringUtil.nullConvertToString(conf.getContent()) %></textarea>
          </td>
        </tr>
        <tr> 
          <td height="25" align="right" valign="middle" bgcolor="#A9CFE2" class="medium"><bean:message key ="conference.tip"/></td>
          <td align="left" valign="middle" bgcolor="#E6ECF2"><%=tip%></td>
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
				action="${pageContext.request.contextPath}/attendeeinform/list.do"
				form="AllotInformForm">
			<ec:row highlightRow="true">		
				<ec:column property="cutId" headerStyle="text-align:center"
					title='<%= GetProperty.getProperties("attendee.custid",getServletContext())%>' width="80">
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
				<ec:column property="deptName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.dept",getServletContext())%>' />
				<ec:column property="dutyName" headerStyle="text-align:center"
					style="text-align:left"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.duty",getServletContext())%>' />
			</ec:row>
		</ec:table>
    </td>
  </tr>
  <tr> 
    <td align="center" valign="top">&nbsp;</td>
  </tr>
  <tr> 
    <td height="40" align="right" valign="middle" class="tdborder02"> 
    	<input name="Submit" type="button" class="button_nor" value="<bean:message key ="button.return"/>" onClick="javascript:renderCancelPage();"> 
    </td>
  </tr>
</table>
</form>
<SCRIPT>
	function renderCancelPage() {
		self.location = '<%= ContextUtil.getCtxPath(request)%>/query/allotinform.do';
	}
</SCRIPT>

</body>
