<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ page import="java.util.*" %>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>上海电大校园一卡通考勤管理系统</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
        <script src="<c:url value="/pages/scripts/department.js"/>" type="text/javascript"></script>
        <script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
        <script type='text/javascript' src='<c:url value="/dwr/engine.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/util.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/interface/OPT.js"/>'></script>
        <script type="text/javascript">
            function docheck() {
                document.forms[0].submit();
            }
            function changeFaculty(){
                var pid = document.forms[0].pid.value;
                OPT.findAreaFromDepartment(pid,changeFacultyCallback);
            }
            function changeFacultyCallback(result){
                DWRUtil.removeAllOptions("areaCode");
                DWRUtil.addOptions("areaCode", { '':'请选择'});
                DWRUtil.addOptions("areaCode", result,"AREACODE","AREANAME");
                DWRUtil.removeAllOptions("deptId");
                DWRUtil.addOptions("deptId", { '':'请选择'});
            }
            function changeArea() {
                var pid = document.forms[0].pid.value;
                var areaCode = document.forms[0].areaCode.value;
                OPT.findDepartment(areaCode,pid,'0',changeAreaCallback);
            }
            function changeAreaCallback(result){
                DWRUtil.removeAllOptions("deptId");
                DWRUtil.addOptions("deptId", { '':'请选择'});
                DWRUtil.addOptions("deptId", result,"DEPTID","DEPTNAME");
            }
            function setValue(id,name) {
                var inputObj = document.getElementById("departmentName");
                inputObj.value = name;
            }
        </script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 辅导员班级关系维护 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
			<jodd:form bean="request">
				<html:form action="teacherClassSearch.do?method=teacherClassSearch" method="post">
                    <table width="100%">
                        <tr>
                            <td width="60%">
                                &nbsp;院&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;系：
                                <html:select property="pid" onchange="changeFaculty();">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="facultyList" property="ID" labelProperty="NAME"/>
                                </html:select>
                            </td>
                            <td width="40%">
                                &nbsp;校&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;区：
                                <html:select property="areaCode" onchange="changeArea();">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="areaList" property="AREACODE" labelProperty="AREANAME"/>
                                </html:select>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;班级名称：
                                <html:text property="departmentName" onclick="getDepartments('departmentName','deptSelect');"  onkeyup="search('departmentName','deptSelect');" size="40" />
                                <UL class=droplist id="deptSelect" style="position:absolute;z-index:1;width:250px;height:200px;display:none" onmouseover="drop_mouseover('deptSelect');" onmouseout="drop_mouseout('deptSelect');">
                                </UL>
                            </td>
                            <td>
                                &nbsp;班&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;级：
                                <html:select property="deptId">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="deptList" property="deptId" labelProperty="deptName"/>
                                </html:select>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;教师工号：
                                <html:text property="stuempNo" maxlength="50"/>
                            </td>
                            <td>
                                &nbsp;姓&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;名：
                                <html:text property="custName" maxlength="50"/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="Submit" width="50" type="button" class="button_nor" value="查  询" onclick="docheck()">
                            </td>
                        </tr>
                    </table>
				</html:form>
			</jodd:form>
		</div>

		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
				<td height="40" align="left" valign="middle" class="tdborder02">
                    <input name="Submit" type="button" class="submitButton" value=" 添 加 " onclick="window.location.href='teacherClassSearch.do?method=addTeacherClass';">
					&nbsp;&nbsp;&nbsp;
					<input name="Submit" type="button" class="submitButton" value=" 删 除 " onclick="javascript:batch_del(document.forms.ec,'辅导员班级关系','<c:url value="/teacherClassSearch.do?method=deleteTeacherClass" />');">
				</td>
			</tr>
		</table>
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<ec:table items="teacherClassList" var="teacherClass" sortable="false"  rowsDisplayed="50" retrieveRowsCallback="org.extremecomponents.table.callback.LimitCallback" filterRowsCallback="org.extremecomponents.table.callback.LimitCallback" sortRowsCallback="org.extremecomponents.table.callback.LimitCallback"
			    action="teacherClassSearch.do?method=teacherClassSearch" locale="zh_CN" filterable="false">
				<ec:exportXls fileName="teacherClass.xls"  tooltip="导出 Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="选择" sortable="false" viewsAllowed="html" width="4%">
					    <input type="checkbox" name="itemlist" value="${teacherClass.id}" style="border:0px" />
					</ec:column>
					<ec:column property="stuempno" title="教师工号" width="10%" filterable="false" sortable="false"  escapeAutoFormat="true"/>
					<ec:column property="custname" title="教师姓名" width="10%"/>
					<ec:column property="deptid" title="班级代码" width="12%" escapeAutoFormat="true"/>
                    <ec:column property="deptname" title="班级名称" width="35%"/>
                    <ec:column property="faculty" title="院系" width="17%"/>
					<ec:column property="areaName" title="校区" width="12%"/>
                    <ec:parameter name="itemlist" value=""/>
				</ec:row>
			</ec:table>
		</div>
	</body>
</html>

