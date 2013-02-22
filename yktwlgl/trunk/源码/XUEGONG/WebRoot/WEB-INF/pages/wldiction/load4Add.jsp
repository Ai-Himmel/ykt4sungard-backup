<%@page pageEncoding="GBK"%>
<%@ page import="java.util.*"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<%@ page import="org.king.business.domain.DeptInfo"%>
<html>
	<head>
		<title>上海复旦大学物料库存及仓储管理系统</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<script src="<c:url value="/pages/scripts/util.js"/>" type="text/javascript"></script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<%String curentDeptName = "";
			DeptInfo deptInfo = new DeptInfo();
			if (request.getSession().getAttribute("currentDept") != null) {
				deptInfo = (DeptInfo) request.getSession().getAttribute(
						"currentDept");
			}

			curentDeptName = deptInfo.getDeptName();

			%>

		<br>

		<form name=form1 action="" method="post">
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
												字典项新增
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
											<input type="hidden" name="isNew" value="<%=request.getAttribute("isNew")==null?"0":request.getAttribute("isNew")%>">
											<tr align="center" valign=center>
												<input type="hidden" name="dictValue" value="" />
												<td width="20%" height="26" align="right" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
													<font color="red" style="font-weight:normal">*</font>&nbsp;字典类别
												</td>
												<td align="left" valign="middle" class="tableHeader3" colspan="3">
													<select name="s_querylb" class="select01" onchange="changeLb(this)">
														<option value="" selected>
															请选择
														</option>
														<option value="1">
															物料来源
														</option>
														<option value="2">
															派发对象
														</option>
														<option value="5">
															设备派发原因
														</option>
														<option value="6">
															易耗品派发原因
														</option>
														<option value="7">
															校区
														</option>
													</select>
												</td>
												<input type="hidden" name="addquerylb" value="" title="字典类别" isMust='1'>
											</tr>
											<tr align="center" valign=center>
												<td align="left" valign="middle" style="background-color: #D1DAE9;font-weight:bold;font-family:宋体;font-size: 12px;text-align: right;">
													<font color="red" style="font-weight:normal">*</font>&nbsp;字典项值
												</td>
												<td colspan="3" align="left" valign="middle" class="tableHeader3">
													<input type="text" name="adddictCaption" style="input_box" maxlength="10" title="字典项值" isMust='1'>
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="right" valign="middle" class="tdborder02">
									<input name="Submit" type="button" class="button_nor" value="保 存" onclick="javascript:save();">
									&nbsp;
									<input name="button" type="button" class="button_nor" value="返 回" onclick="javascript:back();">
								</td>
							</tr>

						</table>
					</td>
				</tr>
			</table>
			<logic:present name="msg" scope="request">
				<input name="hmsg" type="hidden" value="<bean:write name="msg" />">
			</logic:present>
			<logic:notPresent name="msg" scope="request">
				<input name="hmsg" type="hidden" value="">
			</logic:notPresent>
			<input type="hidden" name="ec_p" value="1">
			<input type="hidden" name="ec_i" value="<%=request.getParameter("ec_i") %>">
			<input type="hidden" name="ec_crd" value="<%=request.getParameter("ec_crd") %>">
			<input type="hidden" name="querylb" value="">
			<input type="hidden" name="dictstate" value="">
		</form>

	</body>
</html>
<script>

setTimeout('init()',10);
function init(){
  
  if(document.all.hmsg.value=='1')
       alert("添加成功！");
  else if(document.all.hmsg.value=='2')
       alert("修改成功！");
  else if(document.all.hmsg.value=='0')
       alert("保存失败！");
  else if(document.all.hmsg.value=='9')
       alert("该字典项已存在！");
  
}  

function changeLb(sel){

    document.all.addquerylb.value=sel.value;

}
	  
  function save(){
 
 if(doCheckForm(form1)){
 	form1.action="dictionarys.do?method=saveDiction";
 	form1.submit();
 }
}
 
function back(){
    form1.action="dictionarys.do?method=getDictionarys";
    form1.submit();
}
 
</script>
