<%@page pageEncoding="GBK"%>
<%@ page import="java.util.List"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page import="com.kingstargroup.conference.common.ParamUtil"%>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConference"%>
<%@ page import="java.util.HashMap"%>
<%@ page import="com.kingstargroup.conference.common.DateUtilExtend"%>
<%@ page import="com.kingstargroup.conference.hibernate.form.TDelegate"%>
<%@ include file="/html/commons/top_calendar.jsp"%>
<%@ include file="/html/commons/init.jsp"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<script language="JavaScript"
	src="<%=ContextUtil.getCtxPath(request)%>/html/commons/js/util.js">
</script>
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
	String custname = ParamUtil.getString(request, "custname");
	String custno = ParamUtil.getString(request, "custno");
	String duty = ParamUtil.getString(request, "duty");
	String deptcode = ParamUtil.getString(request, "deptcode");
	int confid =ParamUtil.getInteger(request, "confid");
	String dlgtcode = ParamUtil.getString(request, "dlgtcode");
	String datetime = DateUtilExtend.getNowTime2();
	String username = GetterUtil.get((String) request.getSession()
			.getAttribute("username"), "");
%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

	<form id="SignNoCard" name="SignNoCard"
		action="<%=ContextUtil.getCtxPath(request)%>/nocardsign.do"
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
					&nbsp;
					<span class="mediumwhite"><strong>&nbsp;&nbsp;&nbsp;<bean:message
								key="sign.signnocard" /> </strong> </span>
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
								<select name=confid class="select01" style="width: 280" id="confidSelect">
									<%
										List confList = GetDictionary.getConfList(username);
										Iterator iter2 = confList.iterator();
										while (iter2.hasNext()) {
											TConference row = (TConference) iter2.next();
											if (confid==row.getConId()) {
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
									maxlength=50 value="<%=custno%>" id="custnoInput">
							</td>
						</tr>
						<tr>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.custname" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input name=custname class="input_box" style="width: 150"
									maxlength=50 value="<%=custname%>">
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
										Iterator iter1 = deptList.iterator();
										while (iter1.hasNext()) {
											HashMap row = (HashMap) iter1.next();
											if (deptcode.equals(row.get("deptCode"))) {
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
								<input name=duty class="input_box" style="width: 150"
									maxlength=50 value="<%=duty%>">
							</td>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.delegate" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<select name="dlgtcode" class="select01" style="width: 150">
									<OPTION>
										-
									</OPTION>
									<%
										List dlgtList = GetDictionary.getDlgtList(username);
										Iterator iter = dlgtList.iterator();
										while (iter.hasNext()) {
											TDelegate dlgt = (TDelegate) iter.next();
											if (dlgtcode.equals(String.valueOf(dlgt.getDlgtId()))) {
									%>
									<option value="<%=dlgt.getDlgtId()%>" selected="selected">
										<%=dlgt.getDlgtName()%>
									</option>
									<%
									} else {
									%>
									<option value="<%=dlgt.getDlgtId()%>">
										<%=dlgt.getDlgtName()%>
									</option>
									<%
										}
										}
									%>
								</select>
						</tr>
						<tr>
							<td height="25" align="right" valign="middle" bgcolor="#E6ECF2"
								class="medium">
								&nbsp;
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								&nbsp;
							</td>
							<td align="center" valign="middle" bgcolor="#E6ECF2">
								&nbsp;
							</td>
							<td align="right" valign="middle" bgcolor="#E6ECF2">
								<input name="Submit" type="button" class="button_nor"
									value="<bean:message key="button.query"/>" onclick="javascript:doquery();">
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<ec:table var="pres" items="result" filterable="false"
						imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
						rowsDisplayed="8"
						action="${pageContext.request.contextPath}/nocardsign.do?cmd=query"
						form="SignNoCard">
						<ec:row highlightRow="true">
							<ec:column property="cutId" headerStyle="text-align:center"
								title='<%=GetProperty.getProperties("attendee.custid",
							getServletContext())%>'
								width="80">
								<input name="custid" type="checkbox" value="${pres.cutId}">
								<a>${pres.cutId}</a>
							</ec:column>
							<ec:column property="stuempNo" headerStyle="text-align:center"
								width="80" style="text-align:left" filterable="false"
								sortable="false"
								title='<%=GetProperty.getProperties("attendee.custno",
							getServletContext())%>'>
							</ec:column>
							<ec:column property="cutName" headerStyle="text-align:center"
								width="80" style="text-align:left" filterable="false" sortable="false"
								title='<%=GetProperty.getProperties("attendee.custname",
							getServletContext())%>' />
							<ec:column property="dutyName" headerStyle="text-align:center"
								width="250" style="text-align:left" filterable="false" sortable="false"
								title='<%=GetProperty.getProperties("attendee.duty",
							getServletContext())%>' />
							<ec:column property="deptName" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="false"
								title='<%=GetProperty.getProperties("attendee.dept",
							getServletContext())%>' />
							<ec:column property="attendSign" headerStyle="text-align:center"
								width="60" style="text-align:left" filterable="false" sortable="false"
								title='<%=GetProperty.getProperties("attendee.status",
							getServletContext())%>' />
						</ec:row>
					</ec:table>
				</td>
			</tr>
		</table>
		</form>
		<form name="SignNoCardForm"
		action="<%=ContextUtil.getCtxPath(request)%>/nocardsign.do"
		method="post">
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
						onClick="DoSelectall()">
					<input name="notselectall" type="button" class="button_nor"
						value="<bean:message key="button.disselectAll"/>"
						onClick="DoNotselectall()">
					<input name="reverseselect" type="button" class="button_nor"
						value="<bean:message key="button.selectOthers"/>"
						onClick="DoReverseselect()">
				</td>
				<td width="60" align="right" valign="middle" class="tdborder02">
					&nbsp;
				</td>
				<td width="100" class="tdborder02">
					&nbsp;
				</td>
				<td width="22" class="tdborder02">
					&nbsp;
				</td>
				<td width="300" height="40" align="right" valign="middle"
					class="tdborder02">
					<input name="Submit2" type="button" class="button_nor"
						value="<bean:message key="button.sign"/>" onclick="javascript:dosign();">
					<input name="Submit2" type="button" class="button_nor"
						value="<bean:message key="button.unsign"/>" onclick="javascript:undosign();">
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
		 	alert("请选择需要无卡签到的人员！");
			return false;
		 }		 
       document.SignNoCardForm.custids.value=custids;
	}
	//保存会议类型
	var preplan1Array = new Array();
	<%
		if(confList!=null && confList.size()>0){
			for(int i=0;i<confList.size();i++){
				TConference conference = (TConference) confList.get(i);
	%>
				preplan1Array.push('<%=conference.getPreplan1()%>');
	<%
			}
		}
	%>
	function checkPreplan1(){
		var confSelect = document.getElementById("confidSelect");
		var index = confSelect.options.selectedIndex;
		if(index==-1){
			alert("没有对应的会议");
			return false;
		}
		var preplan1 = preplan1Array[index];
		if("2"==preplan1){
			//如果是无名单会议，那么需要输入学工号进行查询
			var custno = document.getElementById("custnoInput");
			if(custno.value==""){
				alert("该会议为无名单会议，请输入学工号进行查询！");
				custno.focus();
				return false;
			}
		}
		return true;	
	}
	function doquery(){
		if(!checkPreplan1()){
			return;
		}
		document.forms[0].action='<%=ContextUtil.getCtxPath(request)%>/nocardsign.do?cmd=query';
		document.forms[0].submit();
	}
	
	function dosign(){
		dogetselectedcustid();
		if(document.SignNoCardForm.custids.value==''){
			alert("请选择需要无卡签到的人员！");
			return false;
		}
		document.SignNoCardForm.action='<%=ContextUtil.getCtxPath(request)%>/nocardsign.do?cmd=sign';
		document.SignNoCardForm.submit();
	}
	
	function undosign(){
		dogetselectedcustid();
		if(document.SignNoCardForm.custids.value==''){
			alert("请选择需要取消无卡签到的人员！");
			return false;
		}
		document.SignNoCardForm.action='<%=ContextUtil.getCtxPath(request)%>/nocardsign.do?cmd=unsign';
		document.SignNoCardForm.submit();
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

function DoNotselectAll(){
  
  if(document.forms[0].custid!=null&&document.forms[0].custid.length>1){   
       for(var i=0;i<document.forms[0].custid.length;i++){
              document.forms[0].custid[i].checked=false;
       }
       
  }
  else if(document.forms[0].custid!=null){
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
