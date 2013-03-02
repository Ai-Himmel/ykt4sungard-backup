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
        <script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
        <script type='text/javascript' src='<c:url value="/dwr/engine.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/util.js"/>'></script>
        <script type='text/javascript' src='<c:url value="/dwr/interface/OPT.js"/>'></script>
        <%boolean issysadmin = Boolean.parseBoolean(session.getAttribute("issysadmin").toString());%>

        <SCRIPT type="text/javascript">
        function sharr(planId,classno){
             window.open('/check/allclassstudent.do?method=getAllClassStudent&planId='+planId+"&classno="+classno,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
        }

        function real(planId,classno){
             window.open('/check/todaystuchecksearch.do?method=realStudent&planId='+planId+"&classno="+classno,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
        }
        function nocome(planId,classno){
             window.open('/check/todaystuchecksearch.do?method=nocomeStudent&planId='+planId+"&classno="+classno,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
        }

        <% String msg=(String)request.getAttribute("msg");
        if(msg!=null)
        {
        %>
            alert('<%=msg%>');
        <%}%>
        function changeFaculty(){
            var pid = document.forms[0].pid.value;
            OPT.findAreaFromDepartment(pid,changeFacultyCallback);
            OPT.findCourse('',pid,'','1',refreshCourse);
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
            OPT.findDepartment(areaCode,pid,'1',changeAreaCallback);
            OPT.findCourse(areaCode,pid,'','1',refreshCourse);
        }
        function changeAreaCallback(result){
            DWRUtil.removeAllOptions("classno");
            DWRUtil.addOptions("classno", { '':'请选择'});
            DWRUtil.addOptions("classno", result,"DEPTID","DEPTNAME");
        }
        function refreshCourse(result){
            DWRUtil.removeAllOptions("courseId");
            DWRUtil.addOptions("courseId", { '':'请选择'});
            DWRUtil.addOptions("courseId", result,"COURSEID","COURSENAME");
        }
        function changeDepartment(){
            var areaCode = document.forms[0].schoolarea.value;
            var pid = document.forms[0].pid.value;
            var deptId = document.forms[0].classno.value;
            OPT.findCourse(areaCode,pid,deptId,'1',refreshCourse);
        }
        function setValue(id,name) {
            var inputObj = document.getElementById("departmentName");
            inputObj.value = name;
        }
    </SCRIPT>

    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
        <div id="titleDiv" class="pageTitle">
            <strong> <font class="medium">今日考勤记录查询 </font> </strong>
        </div>
        <div id=lineDiv class="hrLine">
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                    <td class="tdborderLine">
                    
                    </td>                                                   
                </tr>
            </table>                                                                   
        </div>
       <html:form action="todaystuchecksearch.do?method=list" >
            <table width="100%">
                <tr>
                    <td colspan="2">
                        &nbsp;院&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;系：
                        <html:select property="pid" onchange="changeFaculty();">
                            <html:option value="">请选择</html:option>
                            <html:options collection="facultyList" property="ID" labelProperty="NAME"/>
                        </html:select>
                    </td>
                    <td colspan="2">
                        &nbsp;校&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;区：
                        <html:select property="schoolarea" onchange="changeArea();">
                            <html:option value="">请选择</html:option>
                            <html:options collection="areaList" property="AREACODE" labelProperty="AREANAME"/>
                        </html:select>
                    </td>
                </tr>
                <tr>
                    <td colspan="2">
                        &nbsp;班级名称：
                        <html:text property="departmentName" onclick="getDepartments('departmentName','deptSelect');"  onkeyup="search('departmentName','deptSelect');" size="40" />
                        <UL class=droplist id="deptSelect" style="position:absolute;z-index:1;width:250px;height:200px;display:none" onmouseover="drop_mouseover('deptSelect');" onmouseout="drop_mouseout('deptSelect');">
                        </UL>
                    </td>
                    <td colspan="2">
                        &nbsp;班&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;级：
                        <html:select property="classno" onchange="changeDepartment();">
                            <html:option value="">请选择</html:option>
                            <html:options collection="deptList" property="DEPTID" labelProperty="DEPTNAME"/>
                        </html:select>
                    </td>
                </tr>
                <tr>
                    <td width="25%">
                        &nbsp;教师工号：
                        <html:text property="stuempNo" maxlength="50"/>
                    </td>
                    <td width="25%">
                        &nbsp;教师姓名：
                        <html:text property="custName" maxlength="50"/>
                    </td>
                    <td colspan="2">
                        &nbsp;课&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;程：
                        <html:select property="courseId">
                            <html:option value="">请选择</html:option>
                            <html:options collection="courseList" property="COURSEID" labelProperty="COURSENAME"/>
                        </html:select>
                        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                        <html:submit property="csb">查 询</html:submit>
                    </td>
                </tr>
            </table>
         </html:form>
        <div id="lineDiv" class="hrLine">
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                    <td class="tdborderLine"></td>
                </tr>                                                   
            </table>
        </div>
        <div id="tableDiv">
            <ec:table items="todayStuCheckList" var="stucheck" rowsDisplayed="50" action="todaystuchecksearch.do?method=list">
                <ec:exportXls fileName="todayStuCheckList.xls" tooltip="导出 Excel" />
                <ec:row>
                    <ec:column property="areaname" title="校区" width="10%" />
                    <ec:column property="deptname" title="班级" width="20%" />                  
                    <ec:column property="stuempno" title="工号" width="10%" escapeAutoFormat="true"/>
                    <ec:column property="custname" title="任课教师" width="10%" />
                    <ec:column property="coursename" title="课程" width="15%" />
                    <ec:column property="begintime" title="开始时间" width="10%" />
                    <ec:column property="endtime" title="结束时间" width="10%" />
                    <ec:column property="sharr" title="应到" width="5%" >
                        <a href="javascript:void(0);" onclick="sharr('${stucheck.id}','${stucheck.deptcode}');">${stucheck.sharr}</a>
                     </ec:column>   
                    <ec:column property="realarr" title="实到" width="5%" >
                        <a href="javascript:void(0);" onclick="real('${stucheck.id}','${stucheck.deptcode}');">${stucheck.realarr}</a>
                    </ec:column>
                    <ec:column property="reallate" title="缺勤" width="5%" >
                         <a href="javascript:void(0);" onclick="nocome('${stucheck.id}','${stucheck.deptcode}');">${stucheck.reallate}</a>
                    </ec:column>
                </ec:row>
            </ec:table>
        </div>
    </body>
</html>
