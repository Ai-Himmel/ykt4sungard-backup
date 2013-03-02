<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<%@ page import="java.util.*" %>
<%@ page import="org.king.check.domain.Department"%>
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
		<%boolean issysadmin = Boolean.parseBoolean(session.getAttribute("issysadmin").toString());%>
		<SCRIPT language="javascript">
        function back(){
        window.open('login.htm','_self');
        }
        function on_FD(){
            document.all("sd").click();
        }
        function on_validate(para){
            if(document.all(para).value!=''){
                document.forms[0].submit();
            }
            else{
                alert('请选择日期');
            }
        }
        function checkDate(){
            var termId = document.forms[0].termId.value;
            if(termId==null || termId==""){
                alert('请选择学期！');
                return false;
            }
            var endDate = document.forms[0].endDate.value;
            var year = endDate.substring(0,4);
            var month = endDate.substring(4,6);
            var day = endDate.substring(6,8);

            var date = new Date(year,month-1,day);
            var nowDate = new Date();
            nowDate.setHours(0,0,0);
            if(nowDate.getTime()-date.getTime()<0){
                alert('您选择的学期还没有结束，请在学期结束后再查询！');
                return false;
            }
            return true;
        }
        function docheck(){
            if(!checkDate()){
                return;
            }
           document.forms[0].submit();
        }
  
       var termArray = new Array();
       <%
            List term = (List)request.getAttribute("term");
            if(term!=null){
            for(int i=0;i<term.size();i++){
                Map map = (Map)term.get(i);
        %>
            termArray[<%=i%>] = new Array('<%=map.get("termId")%>','<%=map.get("beginDate")%>','<%=map.get("endDate")%>');
        <%
            }
            }
       %>
       function changeDate(termId){
           var hasFind;
           for (var i = 0; i < termArray.length; i++) {
               if (termArray[i][0] == termId) {
                   document.forms[0].beginDate.value = termArray[i][1];
                   document.forms[0].endDate.value = termArray[i][2];
                   hasFind = true;
                   break;
               }
           }
           if(!hasFind){
                document.forms[0].beginDate.value = "";
                document.forms[0].endDate.value = "";
           }
       }
   
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
        var termId = '<%=request.getAttribute("termId")%>';
        function should(para) {
            var beginDate = document.getElementById("beginDate").value;
            var endDate = document.getElementById("endDate").value;
            var url = "/check/classtermcheckreport.do?method=getClassShould&termId="+termId+para+"&beginDate="+beginDate+"&endDate="+endDate;
             window.open(url, "a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
        }
        function other(para){
            var beginDate = document.getElementById("beginDate").value;
            var endDate = document.getElementById("endDate").value;
            var url = "/check/classtermcheckreport.do?method=getPlannedCheck&termId="+termId+para+"&beginDate="+beginDate+"&endDate="+endDate+"&termBeginDate="+beginDate+"&termEndDate="+endDate;
             window.open(url,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=1000,height=500");
        }
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 班级考勤报表(学期) </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
				<html:form action="classtermcheckreport.do?method=classTermReport" method="post" >
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
                            &nbsp;开始日期：
                            <html:text property="beginDate" size="10" readonly="true"/>
                        </td>
                        <td width="25%">
                            &nbsp;结束日期：
                            <html:text property="endDate" size="10" readonly="true"/>

                        </td>
                        <td colspan="2">
                            &nbsp;课&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;程：
                            <html:select property="courseId">
                                <html:option value="">请选择</html:option>
                                <html:options collection="courseList" property="COURSEID" labelProperty="COURSENAME"/>
                            </html:select>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            &nbsp;学&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;期：
                            <html:select property="termId" onchange="changeDate(this.value);">
                                <html:option value="">请选择</html:option>
                                <html:options collection="term" property="termId" labelProperty="termName"/>
                            </html:select>
                        </td>
                        <td>
                            <input name="Submit" width="50" type="button" class="button_nor" value="查  询" onclick="docheck()">
                        </td>
                        <td></td>
                        <td></td>
                    </tr>

                </table>
            </html:form>
		</div>
	
		
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<ec:table items="classTermCheckList" var="classcheck"  rowsDisplayed="50" action="classtermcheckreport.do?method=classTermReport">
				<ec:exportXls fileName="classTermCheckList.xls"  tooltip="导出 Excel" />
				<ec:row>			   
					<ec:column property="classname" title="班级" width="30%" />
					<ec:column property="coursename" title="课程" width="14%" />
					<ec:column property="coursenum" title="应到人次" width="7%" >
                        <a href="javascript:void(0);" onclick="should('&type=should&courseId=${classcheck.courseid}&classno=${classcheck.classid}')">${classcheck.coursenum}</a>
                    </ec:column>
					<ec:column property="checknum" title="实到人次" width="7%" >
                        <a href="javascript:void(0);" onclick="other('&type=real&courseId=${classcheck.courseid}&classno=${classcheck.classid}')">${classcheck.checknum}</a>
					</ec:column>
					<ec:column property="checkrate" title="出勤率" width="7%" />
                    <ec:column property="absenceNum" title="缺勤人次" width="7%" >
                        <a href="javascript:void(0);" onclick="should('&type=nocome&courseId=${classcheck.courseid}&classno=${classcheck.classid}')">${classcheck.absenceNum}</a>
					</ec:column>
					<%if(issysadmin==true){ %>
					<ec:column property="comelatenum" title="迟到人次" width="7%" >
                        <a href="javascript:void(0);" onclick="other('&type=late&courseId=${classcheck.courseid}&classno=${classcheck.classid}')">${classcheck.comelatenum}</a>
					</ec:column>
					<ec:column property="comelaterate" title="迟到率" width="7%" />
					<ec:column property="leaveearlynum" title="早退人次" width="7%" >
                        <a href="javascript:void(0);" onclick="other('&type=leave&courseId=${classcheck.courseid}&classno=${classcheck.classid}')">${classcheck.leaveearlynum}</a>
					</ec:column>
					<ec:column property="leaveearlyrate" title="早退率" width="7%" />
					<%}%>
				</ec:row>
			</ec:table>

		</div>
		
	</body>
</html>

