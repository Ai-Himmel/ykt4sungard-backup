<%@ page contentType="text/html;charset=UTF-8"%>
<%@ include file="/pages/common/taglibs.jsp"%>


<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>

	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<html:form action="coursePlanImp.do?method=impCoursePlan" method="post" enctype="multipart/form-data">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 考勤计划导入 </font> </strong>
		</div>
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			
				选择学期:
				<logic:present name="termList">
				  <select  style="width: 150" name="termId">
				     <logic:iterate name="termList" id="tl" type="java.util.Map">
				       <option value="<bean:write name="tl" property="termId"/>"><bean:write name="tl" property="termName"/></option>
				     </logic:iterate>
				  </select>
				</logic:present>
				&nbsp;&nbsp;&nbsp;&nbsp;
				选择校区:
				<logic:present name="areaList">
				   <select  style="width: 150" name="areaCode">
				     <logic:iterate name="areaList" id="al" type="java.util.Map">
				       <option value="<bean:write name="al" property="AREACODE"/>"><bean:write name="al" property="AREANAME"/></option>
				     </logic:iterate>
				  </select>
				</logic:present>
				
			    &nbsp;&nbsp;&nbsp;&nbsp;
			          导入文件:
			     <html:file property="theFile"></html:file>
			    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
				<input name="createButton" type="button" class="submitButton" value=" 确  定 " onclick="DoCheck()"/>
				
				<a href="javascript:getModel()">模板下载</a>
		</div>
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
	
	</html:form>
	
	<div id="filterDiv" style="text-align: left;">
			
<%
	String  resultstring = request.getAttribute("resultstring")==null?"":request.getAttribute("resultstring").toString();
	out.println(resultstring);	
%>

	</div>

	</body>
</html>
<form action="/check/getPlanModel.do?method=getModel" method="post" >
	
</form>

<script language="JavaScript">
  function 	getModel(){
  //	document.forms[1].action="/check/getPlanModel.do?method=getModel";
  	document.forms[1].submit();
  }

  function DoCheck(){
  if(document.forms[0].elements["theFile"].value!=''){
	    var fileName = document.forms[0].elements["theFile"].value;
         if(fileName.indexOf('.xls')==-1){
        	 alert("文件类型,必须为.xls ！");			
     			return;
         }
         if(fileName.indexOf('.xlsx')!=-1){
        	 alert("系统不支持2007版Excel ！");			
     			return;
         }
       
    }else{
        alert("请选择要导入的Excel文件！");
        return;    
    }
   document.forms[0].submit();
  }
</script>


