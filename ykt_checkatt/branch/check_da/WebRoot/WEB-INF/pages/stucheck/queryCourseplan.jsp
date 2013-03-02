<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ page import="java.util.*" %>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
	<head>
		<title>�Ϻ����У԰һ��ͨ���ڹ���ϵͳ</title>
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
                    alert('��ѡ������');
                }
            }
            function validate() {
                var startDate = noSeat.startDate.value;
                var endDate = noSeat.endDate.value;
                if (startDate == '' || endDate == '') {
                    alert("�뽫������������");
                    return false;
                }
                if (startDate > endDate) {
                    alert("��ʼ���ڲ��ܴ��ڽ���ʱ��");
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
                DWRUtil.addOptions("build", { '':'��ѡ��'});
                DWRUtil.addOptions("roomname", { '':'��ѡ��'});
                DWRUtil.addOptions("build", result);
            }
            function changeAreaFacultyCallback(result){
                DWRUtil.removeAllOptions("classno");
                DWRUtil.addOptions("classno", { '':'��ѡ��'});
                DWRUtil.addOptions("classno", result,"DEPTID","DEPTNAME");
            }
            function refreshCourse(result){
                DWRUtil.removeAllOptions("courseId");
                DWRUtil.addOptions("courseId", { '':'��ѡ��'});
                DWRUtil.addOptions("courseId", result,"COURSEID","COURSENAME");
            }
            function changeBuild() {
                var build = document.forms[0].build.value;
                OPT.getRoomnameList(build, changeBuildCallback);
            }
            function changeBuildCallback(result) {
                DWRUtil.removeAllOptions("roomname");
                DWRUtil.addOptions("roomname",{ '':'��ѡ��'});
                DWRUtil.addOptions("roomname", result);
            }
            function changeFaculty(){
                var pid = document.forms[0].pid.value;
                OPT.findAreaFromDepartment(pid,changeFacultyCallback);
                OPT.findCourse('',pid,'','0',refreshCourse);
            }
            function changeFacultyCallback(result){
                DWRUtil.removeAllOptions("schoolarea");
                DWRUtil.addOptions("schoolarea", { '':'��ѡ��'});
                DWRUtil.removeAllOptions("classno");
                DWRUtil.addOptions("classno", { '':'��ѡ��'});
                DWRUtil.addOptions("schoolarea", result,"AREACODE","AREANAME");
                DWRUtil.removeAllOptions("build");
                DWRUtil.removeAllOptions("roomname");
                DWRUtil.addOptions("build", { '':'��ѡ��'});
                DWRUtil.addOptions("roomname", { '':'��ѡ��'});
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
			<strong> <font class="medium"> ���ڼƻ���ѯ </font> </strong>
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
                                &nbsp;Ժ&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ϵ
                                <html:select property="pid" onchange="changeFaculty();">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="facultyList" property="ID" labelProperty="NAME"/>
                                </html:select>
                            </td>
                            <td width="25%">
                                &nbsp;У&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��
                                <html:select property="schoolArea" onchange="changeArea();">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="areaList" property="AREACODE" labelProperty="AREANAME"/>
                                </html:select>
                            </td>
                            <td colspan="2">
                                &nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��
                                <html:select property="classno" onchange="changeDepartment();">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="deptList" property="DEPTID" labelProperty="DEPTNAME"/>
                                </html:select>
                            </td>
                        </tr>
                        <tr>
                            <td width="25%">
                                &nbsp;¥&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��
                                <aa:zone name="buildzone">
                                <html:select property="build" onchange="changeBuild();">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="buildList" property="build" labelProperty="build"/>
                                </html:select>
                                </aa:zone>
                            </td>
                            <td width="25%">
                                &nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��
                                <aa:zone name="roomnamezone">
                                <html:select property="roomname">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="roomnameList" property="roomname" labelProperty="roomname"/>
                                </html:select>
                                </aa:zone>
                            </td>
                            <td colspan="2">
                                &nbsp;�༶����
                                <html:text property="departmentName" onclick="getDepartments('departmentName','deptSelect');"  onkeyup="search('departmentName','deptSelect');" size="40" />
                                <UL class=droplist id="deptSelect" style="position:absolute;z-index:1;width:250px;height:200px;display:none" onmouseover="drop_mouseover('deptSelect');" onmouseout="drop_mouseout('deptSelect');">
                                </UL>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="2">
                                &nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��
                                <html:select property="courseId">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="courseList" property="COURSEID" labelProperty="COURSENAME"/>
                                </html:select>
                            </td>
                            <td colspan="2"></td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;��ʦ����
                                <html:text property="stuempNo"  size="16" maxlength="50"/>
                            </td>
                            <td>
                                &nbsp;��ʦ����
                                <html:text property="custName" size="16" maxlength="50"/>
                            </td>
                            <td colspan="2">
                                &nbsp;��&nbsp;&nbsp;��&nbsp;&nbsp;��
                                <html:text property="week" size="16" maxlength="10"/>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;ʹ���ܴ�
                                <html:text property="useWeek" size="16" maxlength="10"/>
                            </td>
                            <td>
                                &nbsp;��ʼ�ܴ�
                                <html:text property="beginWeek" size="16" maxlength="10"/>
                            </td>
                            <td>
                                &nbsp;�����ܴ�
                                <html:text property="endWeek" size="16" maxlength="10"/>
                            </td>
                            <td></td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;��ʼ�δ�
                                <html:text property="beginClassNum" size="16" maxlength="10"/>
                            </td>
                            <td>
                                &nbsp;�����δ�
                                <html:text property="endClassNum" size="16" maxlength="10"/>
                            </td>
                            <td colspan="2">
                                &nbsp;��ʼ����
                                <html:text property="beginDate" size="12" readonly="true"/>
					            <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
                                &nbsp;��������
                                <html:text property="endDate" size="12" readonly="true"/>
                                <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                                <script type="text/javascript">
                                    new calendar("beginDate", "calBegin", "%Y%m%d");
                                    new calendar("endDate", "calEnd", "%Y%m%d");
                                </script>
                                &nbsp;
                                <input name="Submit" width="50" type="button" class="button_nor" value="��  ѯ" onclick="docheck()"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                <input type="button" class="button_nor" value="��  ��" onclick="clean();">
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
				<ec:exportXls fileName="courseplanSearch.xls"  tooltip="���� Excel" />
				<ec:row>
					<ec:column property="areaName"  title="У��" width="8%"/>
					<ec:column property="build" title="¥��" width="8%"/>
					<ec:column property="roomName" title="����" width="8%"/>
					<ec:column property="stuempNo" title="��ʦ����" width="8%" filterable="false" sortable="false"  escapeAutoFormat="true"/>
					<ec:column property="custName" title="��ʦ����" width="8%"/>
					<ec:column property="courseName" title="�γ���" width="8%"/>
                    <ec:column property="className" title="�༶" width="21%"/>
					<ec:column property="useWeek" title="�ڼ���" width="5%"/>
					<ec:column property="week" title="���ڼ�" width="5%"/>
					<ec:column property="useDate" title="�Ͽ�����" width="7%"/>
					<ec:column property="beginClassNum" title="��ʼ�δ�" width="7%"/>
					<ec:column property="endClassNum" title="�����δ�" width="7%"/>
				</ec:row>
			</ec:table>
		</div>

	</body>
</html>

