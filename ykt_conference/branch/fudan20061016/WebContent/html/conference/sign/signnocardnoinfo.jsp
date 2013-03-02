<%@page pageEncoding="GBK"%>
<%@ page import="java.util.List"%>
<%@ page import="com.kingstargroup.conference.util.GetDictionary"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page import="com.kingstargroup.conference.common.ParamUtil"%>
<%@ page import="com.kingstargroup.conference.hibernate.form.TConference"%>
<%@ page import="java.util.HashMap"%>
<%@ page import="com.kingstargroup.conference.hibernate.form.TDelegate"%>
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
<%
	String custname = ParamUtil.getString(request, "custname");
	String custno = ParamUtil.getString(request, "custno");
	String duty = ParamUtil.getString(request, "duty");
	String deptcode = ParamUtil.getString(request, "deptcode");
	Integer confid = new Integer(ParamUtil
			.getInteger(request, "confid"));
	String dlgtcode = ParamUtil.getString(request, "dlgtcode");
	String username = GetterUtil.get((String) request.getSession()
			.getAttribute("username"), "");
%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">

	<form   name="SignNoCardNoInfo"
		action="<%=ContextUtil.getCtxPath(request)%>/noCardNoInfo.do?cmd=query"
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
								<select name=confid class="select01" style="width: 280">
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
								</select>
							</td>
							<td height="25" align="right" valign="middle" bgcolor="#A9CFE2"
								class="medium">
								<bean:message key="attendee.custname" />
							</td>
							<td align="left" valign="middle" bgcolor="#E6ECF2">
								<input name=custname class="input_box" style="width: 150"
									maxlength=50 value="<%=custname%>">
							</td>
							
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
									value="<bean:message key="button.query"/>"
									onclick="javascript:doquery();">
						
								<input name="Submit" type="button" class="button_nor"
									value="<bean:message key="button.add"/>"
									onclick="javascript:add();">
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<ec:table var="pres" items="result" filterable="false"
						imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif"
						rowsDisplayed="12"
						action="${pageContext.request.contextPath}/noCardNoInfo.do"
						form="SignNoCardNoInfo">
						<ec:row highlightRow="true">
							<ec:column property="custId" headerStyle="text-align:center"
								title='<%=GetProperty.getProperties("conference.id",
										getServletContext())%>'
								width="80">
								<input name="custid" type="checkbox" value="${pres.custId}">
								<%="${pres.custId}"%>
							</ec:column>
							
							<ec:column property="cutName" headerStyle="text-align:center"
								width="80" style="text-align:center" filterable="false"
								sortable="false"
								title='<%=GetProperty.getProperties("attendee.custname",
									getServletContext())%>' />
						   <ec:column property="sex" headerStyle="text-align:center"
					            style="text-align:center"
					            filterable="false" 
					            sortable="false"
					           title='<%= GetProperty.getProperties("attendee.sex",getServletContext())%>' />
					           
							<ec:column property="replacerDuty" headerStyle="text-align:center"
								width="250" style="text-align:center" filterable="false"
								sortable="false"
								title='<%=GetProperty.getProperties("attendee.duty",
									getServletContext())%>' />
									
							<ec:column property="deptName" headerStyle="text-align:center"
								style="text-align:left" filterable="false" sortable="false"
								title='<%=GetProperty.getProperties("attendee.dept",
									getServletContext())%>' />
									
							<ec:column property="attendSign" headerStyle="text-align:center"
								width="60" style="text-align:center" filterable="false"
								sortable="false"
								title='<%=GetProperty.getProperties("attendee.status",
									getServletContext())%>' />
									
						</ec:row>
					</ec:table>
				</td>
			</tr>
		</table>
	</form>
	<form name="SignNoCardNoInfoForms"
		action="<%=ContextUtil.getCtxPath(request)%>/noCardNoInfo.do"
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
						onClick="javascript:DoSelectall();">
					<input name="notselectall" type="button" class="button_nor"
						value="<bean:message key="button.disselectAll"/>"
						onClick="javascript:DoNotselectall();">
					<input name="reverseselect" type="button" class="button_nor"
						value="<bean:message key="button.selectOthers"/>"
						onClick="javascript:DoReverseselect();">
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
				<td height="40" align="right" valign="middle"
					class="tdborder02">
					<input name="Submit2" type="button" class="button_nor"
						value="<bean:message key="button.sign"/>"
						onclick="javascript:dosign();">
					<input name="Submit2" type="button" class="button_nor"
						value="<bean:message key="button.unsign"/>"
						onclick="javascript:undosign();">
				</td>
			</tr>
		</table>
	</form>
	<SCRIPT language="javascript">
	function  add(){
	 window.open('<%=ContextUtil.getCtxPath(request)%>/html/conference/sign/addnocardnoinfo.jsp','�޿�����������','top=450,left=600,height=400,width=600,scrollbars=no,resizable=no,status=no,toolbar=no,menubar=no,location=no'); 	
	}
	
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
		 	alert("��ѡ����Ҫ�޿�ǩ������Ա��");
			return false;
		 }		 
       document.SignNoCardNoInfoForms.custids.value=custids;
	}
	function doquery(){
		document.forms[0].action='<%=ContextUtil.getCtxPath(request)%>/noCardNoInfo.do?cmd=query';
		document.forms[0].submit();
	}
	
	function dosign(){
		dogetselectedcustid();
		if(document.SignNoCardNoInfoForms.custids.value==''){
			alert("��ѡ����Ҫ�޿�ǩ������Ա��");
			return false;
		}
		document.SignNoCardNoInfoForms.action='<%=ContextUtil.getCtxPath(request)%>/noCardNoInfo.do?cmd=sign';
		document.SignNoCardNoInfoForms.submit();
	}
	
	function undosign(){
		dogetselectedcustid();
		if(document.SignNoCardNoInfoForms.custids.value==''){
			alert("��ѡ����Ҫȡ���޿�ǩ������Ա��");
			return false;
		}
		document.SignNoCardNoInfoForms.action='<%=ContextUtil.getCtxPath(request)%>/noCardNoInfo.do?cmd=unsign';
		document.SignNoCardNoInfoForms.submit();
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
       alert("��ǰ�޼�¼��");
  }
  

}

function DoNotselectall(){
  if(document.forms[0].custid!=null&&document.forms[0].custid.length>1){   
       for(var i=0;i<document.forms[0].custid.length;i++){
              document.forms[0].custid[i].checked=false;
       }
       
  }
  else if(document.forms[0].custid!=null){
       document.forms[0].custid.checked=false;       
  }
  else{
       alert("��ǰ�޼�¼��");
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
       alert("��ǰ�޼�¼��");
  }
  

}
</SCRIPT>

</body>
