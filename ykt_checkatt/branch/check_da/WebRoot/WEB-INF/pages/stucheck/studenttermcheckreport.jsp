<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<%@ page import="java.util.*" %>
<%@ page import="org.king.check.domain.Department"%>
<html>
	<head>
		<title>�Ϻ����У԰һ��ͨ���ڹ���ϵͳ</title>
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
                alert('��ѡ������');
            }
        }
        function checkDate(){
            var termId = document.forms[0].termId.value;
            if(termId==null || termId==""){
                alert('��ѡ��ѧ�ڣ�');
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
                alert('��ѡ���ѧ�ڻ�û�н���������ѧ�ڽ������ٲ�ѯ��');
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
            DWRUtil.addOptions("schoolarea", { '':'��ѡ��'});
            DWRUtil.addOptions("schoolarea", result,"AREACODE","AREANAME");
            DWRUtil.removeAllOptions("classno");
            DWRUtil.addOptions("classno", { '':'��ѡ��'});
        }
        function changeArea() {
            var pid = document.forms[0].pid.value;
            var areaCode = document.forms[0].schoolarea.value;
            OPT.findDepartment(areaCode,pid,'1',changeAreaCallback);
            OPT.findCourse(areaCode,pid,'','1',refreshCourse);
        }
        function changeAreaCallback(result){
            DWRUtil.removeAllOptions("classno");
            DWRUtil.addOptions("classno", { '':'��ѡ��'});
            DWRUtil.addOptions("classno", result,"DEPTID","DEPTNAME");
        }
        function refreshCourse(result){
            DWRUtil.removeAllOptions("courseId");
            DWRUtil.addOptions("courseId", { '':'��ѡ��'});
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
            var url = "/check/studenttermcheckreport.do?method=getStudentShould&termId="+termId+para;
             window.open(url, "a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
        }
        function other(para){
            var url = "/check/studenttermcheckreport.do?method=getStudentOther&termId="+termId+para;
             window.open(url,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
        }
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ѧ�����ڱ���(ѧ��) </font> </strong>
		</div>
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>                                                    
			</table>                   
		</div>
		<div id="filterDiv" style="text-align: left;">
				<html:form action="studenttermcheckreport.do?method=studentTermReport" method="post" >
                    <table width="100%">         
                        <tr>
                            <td colspan="2">
                                &nbsp;Ժ&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ϵ��
                                <html:select property="pid" onchange="changeFaculty();">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="facultyList" property="ID" labelProperty="NAME"/>
                                </html:select>
                            </td>
                            <td colspan="2">
                                &nbsp;У&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;����
                                <html:select property="schoolarea" onchange="changeArea();">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="areaList" property="AREACODE" labelProperty="AREANAME"/>
                                </html:select>
                            </td>
                        </tr>
                        <tr>
                            <td colspan="2">
                                &nbsp;�༶���ƣ�
                                <html:text property="departmentName" onclick="getDepartments('departmentName','deptSelect');"  onkeyup="search('departmentName','deptSelect');" size="40" />
                                <UL class=droplist id="deptSelect" style="position:absolute;z-index:1;width:250px;height:200px;display:none" onmouseover="drop_mouseover('deptSelect');" onmouseout="drop_mouseout('deptSelect');">
                                </UL>
                            </td>
                            <td colspan="2">
                                &nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;����
                                <html:select property="classno" onchange="changeDepartment();">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="deptList" property="DEPTID" labelProperty="DEPTNAME"/>
                                </html:select>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                &nbsp;ѧ&nbsp;&nbsp;��&nbsp;&nbsp;�ţ�
                                <html:text property="stuempNo" maxlength="50"/>
                            </td>
                            <td>
                                &nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;����
                                <html:text property="custName" maxlength="50"/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            </td>
                            <td colspan="2">
                                &nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�̣�
                                <html:select property="courseId">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="courseList" property="COURSEID" labelProperty="COURSENAME"/>
                                </html:select>
                            </td>
                        </tr>
                        <tr>
                            <td width="25%">
                                &nbsp;��ʼ���ڣ�
					            <html:text property="beginDate" size="10" readonly="true"/>
                            </td>
                            <td width="25%">
                                &nbsp;�������ڣ�
					            <html:text property="endDate" size="10" readonly="true"/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            </td>
                            <td width="25%">
                                &nbsp;ѧ&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�ڣ�
                                <html:select property="termId" onchange="changeDate(this.value);">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="term" property="termId" labelProperty="termName"/>
                                </html:select>
                            </td>
                            <td>
                                <input name="Submit" width="50" type="button" class="button_nor" value="��  ѯ" onclick="docheck()">
                            </td>
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
			<ec:table items="studentTermCheckList" var="stucheck"  rowsDisplayed="50" action="studenttermcheckreport.do?method=studentTermReport" retrieveRowsCallback="org.extremecomponents.table.callback.LimitCallback" filterRowsCallback="org.extremecomponents.table.callback.LimitCallback" sortRowsCallback="org.extremecomponents.table.callback.LimitCallback" filterable="false" sortable="false">
				<ec:exportXls fileName="studentTermCheckList.xls"  tooltip="���� Excel" />
				<ec:row>			   
					<ec:column property="classname" title="�༶" width="20%"/>                           
					<ec:column property="coursename" title="�γ�" width="14%" />
					<ec:column property="stuempno" title="ѧ����" width="10%" escapeAutoFormat="true"/>
					<ec:column property="custname" title="����" width="8%" />
					<ec:column property="coursenum" title="Ӧ������" width="6%">
                        <a href="javascript:void(0);" onclick="should('&type=should&courseId=${stucheck.courseid}&stuempNo=${stucheck.stuempno}&classId=${stucheck.classid}')">${stucheck.coursenum}</a>
					</ec:column>
					<ec:column property="checknum" title="ʵ������" width="6%" >
                        <a href="javascript:void(0);" onclick="other('&type=real&courseId=${stucheck.courseid}&stuempNo=${stucheck.stuempno}&classId=${stucheck.classid}')">${stucheck.checknum}</a>
					</ec:column>
					<ec:column property="checkrate" title="������" width="6%" />
					<%if(issysadmin==true){ %>
                    <ec:column property="absenceNum" title="ȱ�ڴ���" width="6%" >
                        <a href="javascript:void(0);" onclick="should('&type=nocome&courseId=${stucheck.courseid}&stuempNo=${stucheck.stuempno}&classId=${stucheck.classid}')">${stucheck.absenceNum}</a>
					</ec:column>
					<ec:column property="comelatenum" title="�ٵ�����" width="6%" >
                        <a href="javascript:void(0);" onclick="other('&type=late&courseId=${stucheck.courseid}&stuempNo=${stucheck.stuempno}&classId=${stucheck.classid}')">${stucheck.comelatenum}</a>
					</ec:column>
					<ec:column property="comelaterate" title="�ٵ���" width="6%" />
					<ec:column property="leaveearlynum" title="���˴���" width="6%" >
                        <a href="javascript:void(0);" onclick="other('&type=leave&courseId=${stucheck.courseid}&stuempNo=${stucheck.stuempno}&classId=${stucheck.classid}')">${stucheck.leaveearlynum}</a>
					</ec:column>
					<ec:column property="leaveearlyrate" title="������" width="6%" />
					<%}%>
				</ec:row>
			</ec:table>

		</div>
		
	</body>
</html>

