<%@ page pageEncoding="GBK"%>
<%@page import="java.util.HashMap"%>
<%@page import="com.kingstargroup.conference.hibernate.form.TConference"%>
<%@ include file="/html/commons/init.jsp"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page import="com.kingstargroup.conference.hibernate.form.TGroup"%>
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
<%
	List result = (List) request.getAttribute("result");
	String physicalno = request.getAttribute("physicalno")==null?"":request.getAttribute("physicalno").toString();
	HashMap timemap = (HashMap)request.getAttribute("timemap");
	
	String username = GetterUtil.get((String) request.getSession()
			.getAttribute("username"), "");
	Integer confid = new Integer(ParamUtil
			.getInteger(request, "confid"));
%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<form name="fileAttendeeListForm"
		action="<%=ContextUtil.getCtxPath(request)%>/uploadlist.do?cmd=query"
		enctype="multipart/form-data" method="post">
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
					&nbsp;
					<span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<bean:message
								key="attendee.list" /> </strong> </span>
				</td>
			</tr>
			<tr>
				<td align="left" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="left" valign="top">
					<table width="100%" border="1" cellspacing="0" cellpadding="2"
						bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
						<tr>
							<td width="15%" height="25" align="right" valign="top"
								bgcolor="#A9CFE2" class="medium">&nbsp;
								<bean:message key="sign.file" />
							</td>
							<!-- 
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<textarea rows="5" cols="20" name="physicalno"
									title="批量物理卡号输入,回车标识分割" ><%=physicalno %></textarea>
								&nbsp;&nbsp;&nbsp;&nbsp;
								<input name="Submit" type="submit" class="button_nor"
									value="<bean:message key="button.query"/>">
							</td-->
							<td>
								<input type="file" name="theFile">								
								<input name="Submit" type="submit" class="button_nor"
									value="<bean:message key="button.query"/>">
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width="100%" border="1" cellspacing="0" cellpadding="2"
						bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
						<tr align="center" valign="middle">
							<td align="center" valign="top">
								<ec:table var="pres" items="result" filterable="false" 
									imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
									action="${pageContext.request.contextPath}/attendeelist.do"		
									showPagination="false"							
									form="AttendeeListForm">
									
									<ec:row highlightRow="true">
										<ec:column property="stuempNo" headerStyle="text-align:center"
											width="150" style="text-align:left" filterable="false"
											sortable="true"
											title='<%=GetProperty.getProperties("attendee.custno",
							getServletContext())%>' >
							                    
												
												<a>${pres.stuempNo}</a>
										</ec:column>
										<ec:column property="cutName" headerStyle="text-align:center"
											width="150" style="text-align:left" filterable="false"
											sortable="true"
											title='<%=GetProperty.getProperties("attendee.custname",
							getServletContext())%>'>
										</ec:column>
										<ec:column property="typeName" headerStyle="text-align:center"
											width="120" style="text-align:left" filterable="false"
											sortable="true"
											title='<%=GetProperty.getProperties("attendee.type",
							getServletContext())%>'>
										</ec:column>

										<ec:column property="dictCaption"
											headerStyle="text-align:center" width="40"
											style="text-align:left" filterable="false" sortable="true"
											title='<%=GetProperty.getProperties("attendee.sex",
							getServletContext())%>'>
										</ec:column>
										<ec:column property="deptName" headerStyle="text-align:center"
											width="150" style="text-align:left" filterable="false"
											sortable="true"
											title='<%=GetProperty.getProperties("attendee.dept",
							getServletContext())%>' />

										<ec:column property="asignTime"
											headerStyle="text-align:center" style="text-align:center"
											filterable="false" sortable="false"
											title='<%=GetProperty.getProperties("sign.signtime",
							getServletContext())%>' />
									</ec:row>
									
								</ec:table>
							</td>
					</table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
		</table>
	</form>
	
	
	<form name="fileAttendeeSignOn"
		action="<%=ContextUtil.getCtxPath(request)%>/uploadlist.do"
		method="post">
		<%
		String custIdString = "";
		if(request.getAttribute("custIdString")!=null)
		    custIdString=request.getAttribute("custIdString").toString();
		%>
		<input name="custIdString" type="hidden" value="<%=custIdString%>">
		<input type="hidden" name="cmd" value="upload">
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td align="right" valign="middle" class="tdborder02" colspan="2">
				<bean:message key="conference.name" />:
					<select name=confid class="select01">
					<%  Object obj = request.getAttribute("conference");
							TConference conf =null;
					 		if(obj != null){
					 		       conf =  (TConference)obj;
					 		  }
							List confList = GetDictionary.getConfList(username);
							Iterator iter2 = confList.iterator();
							while (iter2.hasNext()) {
								TConference row = (TConference) iter2.next();
								 if(conf != null && conf.getConId().equals(row.getConId())){
						%>
							<option value="<%=row.getConId()%>" selected="selected">
								<%=row.getConName()%>
							</option>
						<%
						         break;
						        } 
						    }
						%>
					</select>
				</td>
				<td width="22" class="tdborder02">
					&nbsp;
				</td>
				<td width="300" height="40" align="right" valign="middle"
					class="tdborder02">
					<input name="Submit" type="Submit" class="button_nor"
						value="<bean:message key="sign.upload"/>" >
				</td>
			</tr>
		</table>
	</form>
</body>

