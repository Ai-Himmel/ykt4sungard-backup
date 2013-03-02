<%@page pageEncoding="GBK"%>
<%@ page import="java.util.List"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page import="com.kingstargroup.conference.common.ContextUtil"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TConference"%>
<%@ page import="java.util.HashMap"%>
<%@ page import="com.kingstargroup.conference.common.DateUtilExtend"%>
<%@ include file="/html/commons/top_calendar.jsp"%>
<%@ include file="/html/commons/init.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<script language="JavaScript"
	src="<%=ContextUtil.getCtxPath(request)%>/html/commons/js/util.js"></script>
<head>
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css">
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css">
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css">
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css"
		rel="stylesheet" type="text/css" />
</head>

<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
  <%  String username = GetterUtil.get((String) request.getSession()
			.getAttribute("username"), "");
	 Integer confid = new Integer(ParamUtil
			.getInteger(request, "confid"));
	 String tipinfo =  request.getAttribute("tipinfo")==null?"":request.getAttribute("tipinfo").toString();	
			
 %>

	<form    action="<%=ContextUtil.getCtxPath(request)%>/addNoCardNoInfo.do"  method=post>
	<table width="400" border="0" align="center" cellpadding="0"
		cellspacing="0">
             
			<tr>
				<td height="30" align="left" valign="middle" class="medium">
					<font color="#000099"><strong><bean:message
								key="sign.signnocard" /> </strong> </font>
				   <%if(!"".equals(tipinfo)){%>
				       <font color="red"><%=tipinfo%></font>
				   <%}%>
				</td>
			</tr>
			
			<tr>
				<td align="left" valign="top">
					<table width="100%" border="1" cellspacing="0" cellpadding="2"
						bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
						 <tr>
							<td width="15%" height="25" align="right" valign="middle"
								bgcolor="#A9CFE2" class="medium">
								<bean:message key="conference.name" />
							</td>
							<td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
								<select name=confid class="select01" style="width: 150">
									<%
										List confList = GetDictionary.getConfList(username);
										Iterator iter2 = confList.iterator();
										while (iter2.hasNext()) {
											TConference row = (TConference) iter2.next();
											if (confid.equals(row.getConId())) {
									%>
									<option value="<%=row.getConId()%>" selected="selected">
										<%=row.getConName()%>
									</option>
									<%
										} else {
									%>
									<option value="<%=row.getConId()%>">
										<%=row.getConName()%>
									</option>
									<%
										}
										}
									%>
								</select><font color="red"><html:errors property="confid"/></font>
							</td>   
			</tr>				
						<tr>
							<td width="15%" height="25" align="right" valign="middle"
								bgcolor="#A9CFE2" class="medium">
								<bean:message key="attendee.custname" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input name="name" class="input_box" style="width: 150"
									maxlength=15><font color="red"><html:errors property="name"/></font>
							</td>
						</tr>
						
						<tr>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.sex" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<select name="sex">
								   <option value="1">ÄÐ</option>
								   <option value="2">Å®</option>
								</select>
							</td>
						</tr>
						<tr>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.duty" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input name="duty" class="input_box" style="width: 150"
									maxlength=20>
							</td>
						</tr>
						<tr>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.dept" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input name="dept" class="input_box" style="width: 150"
									maxlength=20>
							</td>
						</tr>
					
					</table>
				</td>
			</tr>
			<tr>
				<td height="40" align="right" valign="middle" class="tdborder02">
					<input name="Submit" type="submit" class="button_nor"
									value="<bean:message key="button.save"/>"
									>
				</td>
			</tr>
		</table>
	</form>

</body>
