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
		<script type='text/javascript' src='<c:url value="/dwr/engine.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/util.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/interface/OPT.js"/>'></script>
        <script src="<c:url value="/pages/scripts/department.js"/>" type="text/javascript"></script>
        <script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
        <SCRIPT language=javascript>
            function back() {
                window.open('login.htm', '_self');
            }
            function on_FD() {
                document.all("sd").click();
            }
            function on_validate(para) {
                if (document.all(para).value != '') {
                    document.forms[0].submit();
                }
                else {
                    alert('请选择日期');
                }
            }
            function validate() {
                var startDate = noSeat.startDate.value;
                var endDate = noSeat.endDate.value;
                if (startDate == '' || endDate == '') {
                    alert("请将日期输入完整");
                    return false;
                }
                if (startDate > endDate) {
                    alert("开始日期不能大于结束时间");
                    return false;
                }
            }
            function docheck() {
                document.forms[0].submit();
            }
            function upcheck() {
                window.location.href = 'coursePlan.do?method=updateCourseplan_step1';
            }
            function changeArea() {
                var pid = document.forms[0].pid.value;
                var areaCode = document.forms[0].schoolArea.value;
                OPT.getBuildList(areaCode, changeAreaBuildCallback);
                OPT.findDepartment(areaCode,pid,'0',changeAreaFacultyCallback);
                OPT.findCourse(areaCode,pid,'','0',refreshCourse);
            }
            function changeAreaBuildCallback(result) {
                DWRUtil.removeAllOptions("build");
                DWRUtil.removeAllOptions("roomname");
                DWRUtil.addOptions("build", { '':'请选择'});
                DWRUtil.addOptions("roomname", { '':'请选择'});
                DWRUtil.addOptions("build", result);
            }
            function changeAreaFacultyCallback(result){
                DWRUtil.removeAllOptions("classno");
                DWRUtil.addOptions("classno", { '':'请选择'});
                DWRUtil.addOptions("classno", result,"DEPTID","DEPTNAME");
            }
            function refreshCourse(result){
                DWRUtil.removeAllOptions("courseId");
                DWRUtil.addOptions("courseId", { '':'请选择'});
                DWRUtil.addOptions("courseId", result,"COURSEID","COURSENAME");
            }
            function changeBuild() {
                var build = document.forms[0].build.value;
                OPT.getRoomnameList(build, changeBuildCallback);
            }
            function changeBuildCallback(result) {
                DWRUtil.removeAllOptions("roomname");
                DWRUtil.addOptions("roomname",{ '':'请选择'});
                DWRUtil.addOptions("roomname", result);
            }
            function changeFaculty(){
                var pid = document.forms[0].pid.value;
                OPT.findAreaFromDepartment(pid,changeFacultyCallback);
                OPT.findCourse('',pid,'','0',refreshCourse);
            }
            function changeFacultyCallback(result){
                DWRUtil.removeAllOptions("schoolarea");
                DWRUtil.addOptions("schoolarea", { '':'请选择'});
                DWRUtil.removeAllOptions("classno");
                DWRUtil.addOptions("classno", { '':'请选择'});
                DWRUtil.addOptions("schoolarea", result,"AREACODE","AREANAME");
                DWRUtil.removeAllOptions("build");
                DWRUtil.removeAllOptions("roomname");
                DWRUtil.addOptions("build", { '':'请选择'});
                DWRUtil.addOptions("roomname", { '':'请选择'});
            }
            function changeDepartment(){
                var areaCode = document.forms[0].schoolArea.value;
                var pid = document.forms[0].pid.value;
                var deptId = document.forms[0].classno.value;
                OPT.findCourse(areaCode,pid,deptId,'0',refreshCourse);
            }
            function setValue(id,name) {
                var inputObj = document.getElementById("departmentName");
                inputObj.value = name;
            }
            function updateCourseplan(action){
                window.open (action, "", "height=600, width=800, scrollbars=no, resizable=no,top=300,left=400");
            }
            function clean(){
                var form = document.forms[0];
                form.schoolArea.value="";
                form.build.value="";
                form.roomname.value="";
                form.stuempNo.value="";
                form.custName.value="";
                form.courseId.value="";
                form.classno.value="";
                form.departmentName.value="";
                form.useWeek.value="";
                form.beginWeek.value="";
                form.endWeek.value="";
                form.week.value="";
                form.beginClassNum.value="";
                form.endClassNum.value="";
                form.beginDate.value="";
                form.endDate.value="";
            }
        </SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 考勤计划查询 </font> </strong>
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
				<html:form action="coursePlan.do?method=courseplanQuery" method="post">
                    <table width="100%">
                        <tr>
                            <td width="25%">
                                &nbsp;院&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;系
                                <html:select property="pid" onchange="changeFaculty();">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="facultyList" property="ID" labelProperty="NAME"/>
                                </html:select>
                            </td>
                            <td width="25%">
                                &nbsp;校&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;区
                                <html:select property="schoolArea" onchange="changeArea();">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="areaList" property="AREACODE" labelProperty="AREANAME"/>
                                </html:select>
                            </td>
                            <td colspan="2">
                                &nbsp;班&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;级
                                <html:select property="classno" onchange="changeDepartment();">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="deptList" property="DEPTID" labelProperty="DEPTNAME"/>
                                </html:select>
                            </td>
                        </tr>
                        <tr>
                            <td width="25%">
                                &nbsp;楼&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;宇
                                <aa:zone name="buildzone">
                                <html:select property="build" onchange="changeBuild();">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="buildList" property="build" labelProperty="build"/>
                                </html:select>
                                </aa:zone>
                            </td>
                            <td width="25%">
                                &nbsp;教&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;室
                                <aa:zone name="roomnamezone">
                                <html:select property="roomname">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="roomnameList" property="roomname" labelProperty="roomname"/>
                                </html:select>
                                </aa:zone>
                            </td>
                            <td colspan="2">
                                &nbsp;班级名称
                                <html:text property="departmentName" onclick="getDepartments('departmentName','deptSelect');"  onkeyup="search('departmentName','deptSelect');" size="40" />
                                <UL class=droplist id="deptSelect" style="position:absolute;z-index:1;width:250px;height:200px;display:none" onmouseover="drop_mouseover('deptSelect');" onmouseout="drop_mouseout('deptSelect');">
                                </UL>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="2">
                                &nbsp;课&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;程
                                <html:select property="courseId">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="courseList" property="COURSEID" labelProperty="COURSENAME"/>
                                </html:select>
                            </td>
                            <td colspan="2"></td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;教师工号
                                <html:text property="stuempNo"  size="16" maxlength="50"/>
                            </td>
                            <td>
                                &nbsp;教师姓名
                                <html:text property="custName" size="16" maxlength="50"/>
                            </td>
                            <td colspan="2">
                                &nbsp;星&nbsp;&nbsp;期&nbsp;&nbsp;几
                                <html:text property="week" size="16" maxlength="10"/>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;使用周次
                                <html:text property="useWeek" size="16" maxlength="10"/>
                            </td>
                            <td>
                                &nbsp;开始周次
                                <html:text property="beginWeek" size="16" maxlength="10"/>
                            </td>
                            <td>
                                &nbsp;结束周次
                                <html:text property="endWeek" size="16" maxlength="10"/>
                            </td>
                            <td></td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;开始课次
                                <html:text property="beginClassNum" size="16" maxlength="10"/>
                            </td>
                            <td>
                                &nbsp;结束课次
                                <html:text property="endClassNum" size="16" maxlength="10"/>
                            </td>
                            <td colspan="2">
                                &nbsp;开始日期
                                <html:text property="beginDate" size="12" readonly="true"/>
					            <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
                                &nbsp;结束日期
                                <html:text property="endDate" size="12" readonly="true"/>
                                <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                                <script type="text/javascript">
                                    new calendar("beginDate", "calBegin", "%Y%m%d");
                                    new calendar("endDate", "calEnd", "%Y%m%d");
                                </script>
                                &nbsp;
                                <input name="Submit" width="50" type="button" class="button_nor" value="查  询" onclick="docheck()"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                <input type="button" class="button_nor" value="重  置" onclick="clean();">
                            </td>
                        </tr>
                    </table>
				</html:form>
			</jodd:form>
		</div>

		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<ec:table items="courseplanList" var="plan" sortable="false"  rowsDisplayed="50" retrieveRowsCallback="org.extremecomponents.table.callback.LimitCallback" filterRowsCallback="org.extremecomponents.table.callback.LimitCallback" sortRowsCallback="org.extremecomponents.table.callback.LimitCallback"
			    action="coursePlan.do?method=courseplanQuery" locale="zh_CN" filterable="false">
				<ec:exportXls fileName="courseplanSearch.xls"  tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="areaName"  title="校区" width="8%"/>
					<ec:column property="build" title="楼宇" width="8%"/>
					<ec:column property="roomName" title="教室" width="8%"/>
					<ec:column property="stuempNo" title="教师工号" width="8%" filterable="false" sortable="false"  escapeAutoFormat="true"/>
					<ec:column property="custName" title="教师姓名" width="8%"/>
					<ec:column property="courseName" title="课程名" width="8%"/>
                    <ec:column property="className" title="班级" width="21%"/>
					<ec:column property="useWeek" title="第几周" width="5%"/>
					<ec:column property="week" title="星期几" width="5%"/>
					<ec:column property="useDate" title="上课日期" width="7%"/>
					<ec:column property="beginClassNum" title="开始课次" width="7%"/>
					<ec:column property="endClassNum" title="结束课次" width="7%"/>
				</ec:row>
			</ec:table>
		</div>

	</body>
</html>

