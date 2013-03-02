<%@page pageEncoding="GBK"%>
<%@ include file="/html/commons/init.jsp" %>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ page import="com.kingstargroup.conference.util.ConferenceUtil" %>
<%@ include file="/html/commons/permission.jsp" %>
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/util.js"></script>
<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
<html:base/>
</head>
   
  <body>
  <form  name="NoCardNextForm"   action="<%=ContextUtil.getCtxPath(request)%>/qryimpattend.do" method=post >
   <table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr> 
		<td>&nbsp;</td>
	</tr>
	<tr> 
		<td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
		<span class="mediumwhite"><strong></strong></span>&nbsp;<span class="mediumwhite"><strong><bean:message key="conflist.nocard"/></strong></span></td>
	</tr>
	<tr> 
		<td align="left" valign="top" >&nbsp;</td>
	</tr>
	<tr> 
		<td align="center" valign="top">
		<ec:table 
				var="pres" 
				items="result" 
				filterable="false"
				imagePath="${pageContext.request.contextPath}/html/commons/ximages/*.gif" 
				rowsDisplayed="15"
				action="${pageContext.request.contextPath}/qryimpattend.do"
				form="NoCardNextForm">
			<ec:row highlightRow="true">		
			   <ec:column property="custId" headerStyle="text-align:center"
					title='<%= GetProperty.getProperties("attendee.custid",getServletContext())%>' >
					 <input name="custid" type="checkbox" value="${pres.custId}"/>
					 <%="${pres.custId}"%>
				</ec:column>
				
				<ec:column property="cutName" headerStyle="text-align:center"
					style="text-align:center"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("analyse.custname",getServletContext())%>' >
				</ec:column>	
				
				<ec:column property="sex" headerStyle="text-align:center"
					style="text-align:center"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("attendee.sex",getServletContext())%>' />
				
				<ec:column property="deptName" headerStyle="text-align:center"
					style="text-align:center"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("analyse.custdept",getServletContext())%>' />
					
				<ec:column property="replacerDuty" headerStyle="text-align:center"
					style="text-align:center"
					filterable="false" 
					sortable="false"
					title='<%= GetProperty.getProperties("analyse.custduty",getServletContext())%>' />

			</ec:row>
		</ec:table>
		</td>
	</tr>
	</table>
	</form>
	<form name="deleteInfoForm" action="<%=ContextUtil.getCtxPath(request)%>/nocarddelete.do" method=post >
	<input type=hidden name=confid value="<%=request.getAttribute("confid")%>">
	
		<input type="hidden" name="custids">
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
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
		<td height="40" align="right" valign="middle" class="tdborder02"> 
			<input name="button" type=button class="button_nor" onclick="javascript:deleteInfo()"    value="<bean:message key="button.delete"/>"  >
		</td>
	</tr>
	</table>
</form>
  </body>
</html>
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
		 	alert("请选择需要删除的人员！");
			return false;
		 }		 
       document.deleteInfoForm.custids.value=custids;
	}
	function deleteInfo(){
	  dogetselectedcustid();
		if(document.deleteInfoForm.custids.value==''){
			alert("请选择需要删除的人员！");
			return false;
		}
		document.deleteInfoForm.action='<%=ContextUtil.getCtxPath(request)%>/nocarddelete.do';
		document.deleteInfoForm.submit();
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
</script>