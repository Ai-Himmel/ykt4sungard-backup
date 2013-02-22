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
		<script src="<c:url value="/pages/scripts/selectbox.js"/>" type="text/javascript"></script>

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

		<form name=form1 action="" method=post>

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
												部门物料小类新增
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="40" align="center" valign="top">
									<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
										<tbody>
											<tr align="center" valign=center>
												<td width="20%" height="26" align="right" valign="middle" style="background-color: #D1DAE9;font-family:宋体;font-size: 12px;text-align: right;">
													<b>请选择大类</b>
												</td>
												<td align="left" valign="middle" class="tableHeader3">
													<select name=deptDlCode class="select01" onChange="dochange();">
														<option name=aa value="null">
															请选择
														</option>
														<c:forEach var="dl" items="${deptDl}">
															<option name=aa value="<c:out value="${dl.dlbh}"/>" <c:if test="${dl.dlbh==curentdeptDl}" >selected</c:if>>
																<c:out value="${dl.dlmc}" />
															</option>
														</c:forEach>
													</select>
												</td>
											</tr>
										</tbody>
									</table>
								</td>
							</tr>
							<tr>
								<td height="35" align="center" valign="middle" class="mediumblack">
									&nbsp;
								</td>
							</tr>
							<tr>
								<td align="center" valign="top">
									<table width="90%" border="0" cellspacing="0" cellpadding="0">

										<tr>
											<td align="center" valign="top" bgcolor="#C4E8F9" width="40%">
												<font color="#FF0000"> ----请选择小类----<br> <select name='xlbh' size="18" multiple style="width:270" onDblClick="moveSelectedOptions(this,document.getElementById('rxlbh'),true)">

														<c:forEach var="xl" items="${notIndeptXl}">
															<option name=pp value="<c:out value="${xl.lbbh}"/>">
																<c:out value="${xl.lbbh}" />
																<c:out value="${xl.lbmc}" />
															</option>
														</c:forEach>
													</select> </font>
												<p>
											</td>
											<td align="center" width="20%">

												<input name="moveAllRight" type="button" style="width:56px;height:20px;background-color:#C4E8F9;" onclick="moveSelectedOptions(document.getElementById('xlbh'),document.getElementById('rxlbh'),true)" value="&gt;&gt;">
												<p>
													<input name="moveLeft" type="button" style="width:56px;height:20px;background-color:#C4E8F9;" onclick="moveSelectedOptions(document.getElementById('rxlbh'),document.getElementById('xlbh'),true)" value="&lt;&lt;">
												<p>
											</td>
											<td align="center" valign="top" bgcolor="#C4E8F9">
												<font color="#FF0000">----当前已选择的小类----<br> <select name="rxlbh" size="18" multiple style="width:270" onDblClick="moveSelectedOptions(this,document.getElementById('xlbh'),true)">
													</select> </font>
												<p>
											</td>
										</tr>
										<tr align="right" valign="middle">
											<td height="50" colspan="4">
												<input name="Submit222" type="button" class="button_nor" value="确 定" onClick="javascript:doSave();">
												<input name="bback" type="button" class="button_nor" value="返 回" onclick="DoBack();">
											</td>
										</tr>
									</table>
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
			<input type="hidden" name="ec_p" value="<%=request.getParameter("ec_p") %>">
			<input type="hidden" name="ec_i" value="<%=request.getParameter("ec_i") %>">
			<input type="hidden" name="ec_crd" value="<%=request.getParameter("ec_crd") %>">
			<input type="hidden" name="search_wldl" value="<%=request.getParameter("search_wldl") %>">
			<input type="hidden" name="search_wlxl" value="<%=request.getParameter("search_wlxl") %>">
			<input type="hidden" name="search_xlstate" value="<%=request.getParameter("search_xlstate") %>">
			<input type="hidden" name="newidstring" value="<%=request.getAttribute("newidstring")==null?"":request.getAttribute("newidstring") %>">
		</form>

	</body>
</html>
<script>
setTimeout('init()',10);
function init(){
    
  if(document.form1.hmsg.value=='1')
       alert("添加成功！");
  else if(document.form1.hmsg.value=='0')
       alert("添加失败！");
         
}
function dochange(){

	form1.action="deptXl.do?method=load4Add";
	form1.submit();
}
function doSave(){

    if(form1.rxlbh.length==0){
        alert("您没有选择任何小类！");
        return;

    }
	selectMatchingOptions(form1.rxlbh,"");
	form1.action="deptXl.do?method=saveDeptXl";
	form1.submit();
}
function DoBack(){   
   form1.action="deptXl.do?method=search4List&listNum='all'";
   form1.submit();
}
</script>
