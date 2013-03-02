<%@ include file="/html/commons/init.jsp"%>
<%@ include file="/html/commons/top_calendar.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TConferenceType"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TAssemblyRoom"%>
<head>
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css"
		rel="stylesheet" type="text/css" />
	<html:base />
</head>
<%
	String conname = ParamUtil.getString(request,"conname");
	String confroom = ParamUtil.getString(request,"confroom");
	String type = ParamUtil.getString(request,"type");
	String begindate = ParamUtil.getString(request,"begindate");
%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<form id="DeleteConferenceForm" name="DeleteConferenceForm"
		action="<%=ContextUtil.getCtxPath(request)%>/anal/totalquery.do"
		method="post">
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td>
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="25" align="left" valign="middle"
					background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
					&nbsp;&nbsp;&nbsp;
					<span class="mediumwhite"><strong></strong> </span>&nbsp;
					<span class="mediumwhite"><strong><bean:message
								key="analyse.totle.list" /> </strong> </span>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width="100%" border="1" cellspacing="0" cellpadding="2"
						bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
						<tr>
							<td width="15%" height="25" align="right" valign="middle"
								bgcolor="#A9CFE2" class="medium">
								<bean:message key="conference.name" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input id="aname" name="conname" class="input_box" style="width: 150"
									maxlength="15" value="<%=conname%>">
							</td>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="conference.assembly" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<select name="confroom" style="width: 150" class="select01"
									onChange="changeCounty()">
									<OPTION>
										-
									</OPTION>
									<%
										List roomList = GetDictionary.getAssimblyRoom();
										Iterator iter = roomList.iterator();
										while (iter.hasNext()) {
											TAssemblyRoom row = (TAssemblyRoom) iter.next();
											if (confroom.equals(row.getRoomId())) {
									%>
									<option value="<%=row.getRoomId()%>" selected="selected">
										<%=row.getRoomName()%>
									</option>
									<%
									} else {
									%>
									<option value="<%=row.getRoomId()%>">
										<%=row.getRoomName()%>
									</option>
									<%
										}
										}
									%>
								</select>
							</td>
						</tr>
						<tr>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="conference.type" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<select name="type" class="select01" style="width: 150"
									onChange="changeCounty()">
									<OPTION>
										-
									</OPTION>
									<%
										List typeList = GetDictionary.getConfType();
										Iterator iter2 = typeList.iterator();
										while (iter2.hasNext()) {
											TConferenceType row = (TConferenceType) iter2.next();
											if (type.equals(row.getTypeName())) {
									%>
									<option value="<%=row.getTypeName()%>" selected="selected">
										<%=row.getTypeName()%>
									</option>
									<%
									} else {
									%>
									<option value="<%=row.getTypeName()%>">
										<%=row.getTypeName()%>
									</option>
									<%
										}
										}
									%>
								</select>
							</td>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="conference.begindate" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<table width="100%" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td width="130">
											<input name="begindate" class="input_box" style="width: 150"
												maxlength="8" readonly="true" value="<%=begindate%>">
										</td>
										<td>
											&nbsp;&nbsp;
											<a href="#"><img
													src="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/date.gif"
													width="16" height="16" border="0" id="f_trigger_begindate">
											</a>
										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td height="40" align="right" valign="middle">
					<input name="Submit3" type="button" class="button_nor"
						value="<bean:message key="button.query"/>"
						onClick="document.forms[0].submit();">
					&nbsp;&nbsp;&nbsp;
					<input name="Submit2" type="reset" class="button_nor"
						value="<bean:message key="button.reset"/>">
				</td>
			</tr>
			<tr>
				<td align="left" valign="top" class="tdborder02">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<ec:table var="pres" items="result" filterable="false"
						imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
						rowsDisplayed="10" action="" form="DeleteConferenceForm">						
						<ec:row highlightRow="true" onclick="javascript:avigate(${pres.conId})">
						<ec:column property="conId" headerStyle="text-align:center"
								title='<%= GetProperty.getProperties("conference.id",getServletContext())%>'>
								<a href="<%=ContextUtil.getCtxPath(request)%>/totalreport.do?conId=${pres.conId}">${pres.conId}</a>
							</ec:column>
							<ec:column property="conName" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="true"
								title='<%=GetProperty.getProperties("conference.name",
							getServletContext())%>'>						
							</ec:column>
							<ec:column property="typeName" headerStyle="text-align:center"
								style="text-align:center" filterable="false" sortable="true"
								title='<%=GetProperty.getProperties("conference.type",
							getServletContext())%>' />
							<ec:column property="beginDate" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="true"
								title='<%=GetProperty.getProperties("conference.begindate",
							getServletContext())%>' />
							<ec:column property="beginTime" headerStyle="text-align:center"
								style="text-align:center" filterable="false" sortable="false"
								title='<%=GetProperty.getProperties("conference.begintime",
							getServletContext())%>' />
							<ec:column property="deptName" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="true"
								title='<%=GetProperty.getProperties("conference.org",
							getServletContext())%>' />
							<ec:column property="roomName" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="true"
								title='<%=GetProperty.getProperties("conference.assembly",
							getServletContext())%>' />
							<ec:column property="status" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="true"
								title='<%=GetProperty.getProperties("conference.status",
							getServletContext())%>'>
							</ec:column>
						</ec:row>
						
					</ec:table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="40" align="right" valign="middle" class="tdborder02">
					&nbsp;
				</td>
			</tr>

		</table>
	</form>
	<script language="JavaScript">
	
	Calendar.setup({
        inputField     :    "begindate",     // id of the input field
        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",
							getServletContext())%>,
    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",
							getServletContext())%>",
        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
        align          :    "Tr",           // alignment (defaults to "Bl")
        singleClick    :    true
    });
    
    function avigate(id){
    	window.location='<%=ContextUtil.getCtxPath(request)%>/totalreport.do?conId='+id;
    }
</script>
</body>
