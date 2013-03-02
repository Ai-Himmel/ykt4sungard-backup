<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<%@ page import="java.util.*" %>
<html>
    <head>
        <title>校园一卡通考勤管理系统</title>
        <meta http-equiv="Content-Type" content="text/html;">

        <%@ include file="/pages/common/meta.jsp"%>
        <%@ include file="/pages/components/calendar/calendar.jsp"%>
        <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
        <link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
        <script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
        <script src="<c:url value="/pages/scripts/department.js"/>" type="text/javascript"></script>
		<script type='text/javascript' src='<c:url value="/dwr/engine.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/util.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/interface/OPT.js"/>'></script>
        <script src="<c:url value="/pages/scripts/department.js"/>" type="text/javascript"></script>
        <script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
        <script type="text/javascript">
            function changeFaculty(){
                var pid = document.forms[0].pid.value;
                OPT.findAreaFromDepartment(pid,changeFacultyCallback);
            }
            function changeFacultyCallback(result){
                DWRUtil.removeAllOptions("schoolarea");
                DWRUtil.addOptions("schoolarea", { '':'请选择'});
                DWRUtil.addOptions("schoolarea", result,"AREACODE","AREANAME");
                DWRUtil.removeAllOptions("classno");
                DWRUtil.addOptions("classno", { '':'请选择'});
            }
            function changeArea() {
                var pid = document.forms[0].pid.value;
                var areaCode = document.forms[0].schoolarea.value;
                OPT.findDepartment(areaCode,pid,'0',changeAreaCallback);
            }
            function changeAreaCallback(result){
                DWRUtil.removeAllOptions("classno");
                DWRUtil.addOptions("classno", { '':'请选择'});
                DWRUtil.addOptions("classno", result,"DEPTID","DEPTNAME");
            }
            function setValue(id,name) {
                var inputObj = document.getElementById("departmentName");
                inputObj.value = name;
            }
            function docheck() {
                document.forms[0].submit();
            }
        </script>
	</head>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
    <div id="titleDiv" class="pageTitle">
        <strong> <font class="medium"> 班级列表</font> </strong>
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
            <html:form action="departmentManager.do?method=load4list" method="post" >
                    <table width="100%">
                        <tr>
                            <td width="50%">
                                &nbsp;院&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;系：
                                <html:select property="pid" onchange="changeFaculty();">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="facultyList" property="ID" labelProperty="NAME"/>
                                </html:select>
                            </td>
                            <td width="50%">
                                &nbsp;校&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;区：
                                <html:select property="schoolarea" onchange="changeArea();">
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
                                <html:select property="classno">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="deptList" property="DEPTID" labelProperty="DEPTNAME"/>
                                </html:select>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;创建年份：
                                <html:select property="createYear">
                                    <html:option value="">请选择</html:option>
                                    <html:options name="yearList"/>
                                </html:select>
                                &nbsp;&nbsp;&nbsp;&nbsp;<input name="Submit" width="50" type="button" class="button_nor" value="查  询" onclick="docheck()">
                            </td>
                            <td>
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
        <ec:table items="departments" var="department" sortable="false" rowsDisplayed="50" action="departmentManager.do?method=load4list" retrieveRowsCallback="org.extremecomponents.table.callback.LimitCallback" filterRowsCallback="org.extremecomponents.table.callback.LimitCallback" sortRowsCallback="org.extremecomponents.table.callback.LimitCallback">
            <ec:exportXls fileName="departments.xls" tooltip="导出 Excel" />
            <ec:row>
                <ec:column property="id" title="班级代码" width="12%" escapeAutoFormat="true"/>
                <ec:column property="name" title="班级名称" width="40%" />
                <ec:column property="faculty" title="院系代码" width="10%" />
                <ec:column property="facultyName" title="院系名称" width="15%" />
                <ec:column property="areaCode" title="校区代码" width="7%" />
                <ec:column property="areaName" title="校区名称" width="10%" />
                <ec:column property="createYear" title="创建年份" width="7%" />
            </ec:row>
        </ec:table>
    </div>
</body>
</html>