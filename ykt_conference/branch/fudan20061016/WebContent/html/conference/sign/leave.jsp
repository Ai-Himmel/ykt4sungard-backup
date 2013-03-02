<%@page pageEncoding="GBK"%>
<%@ page import="java.util.List"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TConference"%>
<%@ page import="java.util.HashMap"%>
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
<%
	List result = (List) request.getAttribute("result");
	String custno = ParamUtil.getString(request, "custno");
	String custname = ParamUtil.getString(request, "custname");
	String duty = ParamUtil.getString(request, "duty");
	String username = GetterUtil.get((String) request.getSession()
			.getAttribute("username"), "");
%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
	<form id="Leave" name="Leave"
		action="<%=ContextUtil.getCtxPath(request)%>/leave.do" method=post>
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">

			<tr>
				<td>
					&nbsp;
					<input type=hidden name=cmd value="query">
				</td>
			</tr>
			<tr>
				<td height="25" align="left" valign="middle"
					background="<%=ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">
					&nbsp;
					<span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<bean:message
								key="sign.leavemanage" /> </strong> </span>
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
							<td width="15%" height="25" align="right" valign="middle"
								bgcolor="#A9CFE2" class="medium">
								<bean:message key="conference.name" />
							</td>
							<td width="35%" align="left" valign="middle" bgcolor="#E6ECF2">
								<select name="confid" class="select01" style="width: 280">
									<%
										List confList = GetDictionary.getConfList(username);
										String confid = "";
										if (null == request.getAttribute("confid")) {
											confid = "0";
										} else {
											confid = request.getAttribute("confid").toString();
										}
										Iterator iter2 = confList.iterator();
										while (iter2.hasNext()) {
											TConference row = (TConference) iter2.next();
											if (row.getConId().toString().equals(confid)) {
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
								</select>
							</td>
							<td width="15%" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.custno" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input name=custno class="input_box" style="width: 150"
									value="<%=custno%>" maxlength=50>
							</td>
						</tr>
						<tr>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.custname" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input name=custname class="input_box" style="width: 150"
									value="<%=custname%>" maxlength=50>
							</td>
							<td align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.dept" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<select name=deptcode class="select01" style="width: 150">
									<OPTION>
										-
									</OPTION>
									<%
										List deptList = GetDictionary.getDeptList();
										String deptcode = "";
										if (null == request.getAttribute("deptcode")) {
											deptcode = "0";
										} else {
											deptcode = request.getAttribute("deptcode").toString();
										}
										Iterator iter1 = deptList.iterator();
										while (iter1.hasNext()) {
											HashMap row = (HashMap) iter1.next();
											if (row.get("deptCode").toString().equals(deptcode)) {
									%>
									<option value="<%=row.get("deptCode")%>" selected="selected">
										<%=row.get("deptName")%>
									</option>
									<%
									} else {
									%>
									<option value="<%=row.get("deptCode")%>">
										<%=row.get("deptName")%>
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
								<bean:message key="attendee.duty" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input name=duty class="input_box" value="<%=duty%>"
									style="width: 150" maxlength=50>
							</td>
							<td align="center" valign="middle" bgcolor="#E6ECF2">
								&nbsp;
							</td>
							<td align="right" valign="middle" bgcolor="#E6ECF2">
								<input name="Submit" type="submit" class="button_nor"
									value="<bean:message key="button.query"/>" onclick="javascript:doquery();">
							</td>
						</tr>
					</table>
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
						rowsDisplayed="5"
						action="${pageContext.request.contextPath}/leave.do" form="Leave">
						<ec:row highlightRow="true">
							<ec:column property="cutId" headerStyle="text-align:center"
								title='<%=GetProperty.getProperties("attendee.custid",
							getServletContext())%>'
								width="80">
								<input name="custid" type="checkbox" value="${pres.cutId}">
								<a>${pres.cutId}</a>
							</ec:column>
							<ec:column property="stuempNo" headerStyle="text-align:center"
								width="100" style="text-align:left" filterable="false"
								sortable="false"
								title='<%=GetProperty.getProperties("attendee.custno",
							getServletContext())%>'>
							</ec:column>
							<ec:column property="cutName" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="false"
								title='<%=GetProperty.getProperties("attendee.custname",
							getServletContext())%>' />
							<ec:column property="dutyName" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="false"
								title='<%=GetProperty.getProperties("attendee.duty",
							getServletContext())%>' />
							<ec:column property="deptName" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="false"
								title='<%=GetProperty.getProperties("attendee.dept",
							getServletContext())%>' />
							<ec:column property="attendSign" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="false"
								title='<%=GetProperty.getProperties("attendee.status",
							getServletContext())%>' />
						</ec:row>
					</ec:table>
				</td>
			</tr>

		</table>
	</form>
<form id="LeaveForm" name="LeaveForm"
		action="<%=ContextUtil.getCtxPath(request)%>/leave.do" method="post">
		<input type="hidden" name="cmd" value="sign">
			<input type="hidden" name="confid"
				value="<%=ParamUtil.getString(request, "confid")%>">
			<input type="hidden" name="custids">
		<table width="800" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="200" align="left" valign="middle" class="tdborder02">
					<input name="selectall" type="button" class="button_nor"
						value="<bean:message key="button.selectAll"/>"
						onclick="javascript:DoSelectall();">
					<input name="notselectall" type="button" class="button_nor"
						value="<bean:message key="button.disselectAll"/>"
						onclick="javascript:DoNotselectall();">
					<input name="reverseselect" type="button" class="button_nor"
						value="<bean:message key="button.selectOthers"/>"
						onclick="javascript:DoReverseselect();">
				</td>
				<td width="60" align="right" valign="middle" class="tdborder02">
					<font color="#000099"><strong><bean:message
								key="sign.leavereason" /> </strong> </font>
				</td>
				<td width="200" class="tdborder02">
					<input name=reason class="input_box" style="width: 200"
						maxlength=30>
				</td>
				<td width="22" class="tdborder02">
					&nbsp;
				</td>
				<td  height="40" align="right" valign="middle"
					class="tdborder02">
					<input name="Submit2" type="button" class="button_nor"
						value="<bean:message key="button.leave"/>" onclick="javascript:dosign();">
					<input name="Submit2" type="button" class="button_nor"
						value="<bean:message key="button.cancle.leave"/>" onclick="javascript:undosign();">
				</td>
			</tr>
		</table>
	</form>


<SCRIPT language="javascript">
	function dogetselectedcustid(){
	var custids ="";
		 if(document.forms[0].custid!=null&&document.forms[0].custid.length>1){
		 	for(var i=0;i<document.forms[0].custid.length;i++){
				 if( document.forms[0].custid[i].checked==true){
				 	custids += document.forms[0].custid[i].value+",";
				 }
		      }	
		 }else if(document.forms[0].custid!=null){
		 	custids = document.forms[0].custid.value+",";
		 }else{
		 	alert("请选择需要请假的人员！");
			return false;
		 }		 
       document.LeaveForm.custids.value=custids;
	}
	function doquery(){
		document.forms[0].action='<%=ContextUtil.getCtxPath(request)%>/leave.do?cmd=query';
		document.forms[0].submit();
	}
	
	function dosign(){
		dogetselectedcustid();
		if(document.LeaveForm.custids.value==''){
			alert("请选择需要请假的人员！");
			return false;
		}
		document.LeaveForm.action='<%=ContextUtil.getCtxPath(request)%>/leave.do?cmd=sign';
		document.LeaveForm.submit();
	}
	
	function undosign(){
		dogetselectedcustid();
		if(document.LeaveForm.custids.value==''){
			alert("请选择需要消假的人员！");
			return false;
		}
		document.LeaveForm.action='<%=ContextUtil.getCtxPath(request)%>/leave.do?cmd=cleave';
		document.LeaveForm.submit();
	}


function DoSelectall(){

  if(document.forms[0].custid!=null&&document.forms[0].custid.length>1){   
       for(var i=0;i<document.forms[0].custid.length;i++){
              document.forms[0].custid[i].checked=true;
       }
       
  }else if(document.forms[0].custid!=null){
       document.forms[0].custid.checked=true;       
  }
  else{
       alert("当前无记录！");
  }
  

}

function DoNotselectall(){
  
  if(document.forms[0].custid!=null&&document.forms[0].custid.length>1){   
       for(var i=0;i<document.forms[0].custid.length;i++){
              document.forms[0].custid[i].checked=false;
       }
       
  }else if(document.forms[0].custid!=null){
       document.forms[0].custid.checked=false;       
  }
  else{
       alert("当前无记录！");
  }

}

function DoReverseselect(){
   
   if(document.forms[0].custid!=null&&document.forms[0].custid.length>1){   
       for(var i=0;i<document.forms[0].custid.length;i++){
           if(document.forms[0].custid[i].checked)
              document.forms[0].custid[i].checked=false;
           else if(!document.forms[0].custid[i].checked)
              document.forms[0].custid[i].checked=true;
       }
       
  }else if(document.forms[0].custid!=null){
      if(document.forms[0].custid.checked)
          document.forms[0].custid.checked=false; 
      else if(!document.forms[0].custid.checked)
          document.forms[0].custid.checked=true;    
  }
  else{
       alert("当前无记录！");
  }
  

}
</SCRIPT>
</body>
