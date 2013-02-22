<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
	<head>
		<title>上海复旦大学物料库存及仓储管理系统</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/deptUsageCategoryAction.do?method=saveUsageCategory" method="post">

			<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td align="left" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td height="25" align="left" valign="top">
									<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">
												部门用途大类维护
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<input type="hidden" name="listNum" value="all">
										<tbody>
											<input type="hidden" name="formName" value="<%=request.getAttribute("formName")==null?"":request.getAttribute("formName")%>">
											<input type="hidden" name="addNum" value="<%=request.getAttribute("addNum")==null?"":request.getAttribute("addNum")%>">
											<input type="hidden" name="isNew" value="<%=request.getAttribute("isNew")==null?"0":request.getAttribute("isNew")%>">
											<input type="hidden" name="noNew" value="<%=request.getAttribute("noNew")==null?"0":request.getAttribute("noNew")%>">
											<tr align="center" valign=center>
												<html:hidden property="deptusagecategory.id" />
												<td width="20%" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
													<font color="red" style="font-weight:normal">*</font>&nbsp;用途大类名称
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<html:text property="deptusagecategory.usageCategoryName" styleClass="input_boxlong" maxlength="20" />
											    </td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">

									<input name="Submit" type="button" class="button_nor" value="保 存" onclick="DoSave()">
									&nbsp;
									<input name="Submit2" type="button" class="button_nor" value="返 回" onclick="DoBack()">
								</td>

							</tr>							
						</table>
						<logic:present name="msg" scope="request">
							<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
						</logic:present>
						<logic:notPresent name="msg" scope="request">
							<input name="hmsg" type="hidden" value="">
						</logic:notPresent>
						<input type="hidden" name="ec_p" value="<%=request.getAttribute("isNew")!=null&&request.getAttribute("isNew").equals("1")?"1":request.getParameter("ec_p") %>">
						<input type="hidden" name="ec_i" value="<%=request.getParameter("ec_i") %>">
						<input type="hidden" name="ec_crd" value="<%=request.getParameter("ec_crd") %>">

						<input type="hidden" name="search_usageCategoryname" value="<%=request.getParameter("search_usageCategoryname") %>">
						<input type="hidden" name="search_ucstate" value="<%=request.getParameter("search_ucstate") %>">
						</html:form>
	</body>
</html>

<SCRIPT language=javascript>

setTimeout('init()',50);
function init(){
  
  if(document.all.hmsg.value=='1')
       alert("添加成功！");
  else if(document.all.hmsg.value=='2')
       alert("修改成功！");
  else if(document.all.hmsg.value=='0')
       alert("保存失败！");
  else if(document.all.hmsg.value=='9')
       alert("该用途大类已存在！");
}  

function DoSave(){

   if(document.deptUsageCategoryForm.elements["deptusagecategory.usageCategoryName"].value==''){
       alert("请填写用途大类！");
       return;
   
   }
      
   deptUsageCategoryForm.action="deptUsageCategoryAction.do?method=saveUsageCategory";
   deptUsageCategoryForm.submit();
  
}

function DoBack(){
   if(document.all.addNum.value!='') {       
       self.close();       
       opener.deptUsageCategoryForm.action="deptUsageCategoryAction.do?method=search4List&formName="+document.all.formName.value+"&addNum="+document.all.addNum.value+"&isNew="+document.all.isNew.value+"&listNum="+document.all.listNum.value+"&ec_p="+document.all.ec_p.value+"&deptusagecategory.id="+document.deptUsageCategoryForm.elements["deptusagecategory.id"].value;
       opener.deptUsageCategoryForm.submit();
   }
   else{
       deptUsageCategoryForm.action="deptUsageCategoryAction.do?method=search4List";
       deptUsageCategoryForm.submit();
   
   }
}
</SCRIPT>
