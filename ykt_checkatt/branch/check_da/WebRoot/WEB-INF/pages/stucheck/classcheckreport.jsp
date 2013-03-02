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
            }else{
                alert('��ѡ������');
            }
        }
        function validate(){
            var startDate=noSeat.startDate.value;
            var endDate=noSeat.endDate.value;
            if(startDate==''||endDate==''){
                alert("�뽫������������");
                return false;
            }
            if(startDate>endDate){
                alert("��ʼ���ڲ��ܴ��ڽ���ʱ��");
                return false;
            }
        }
        function docheck(){
           document.forms[0].submit();
        }
        function shoud(para){
             window.open('/check/dailyclassstudentdetail.do?method=getClassShoud'+para,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=600");
        }
        function real(para){
             window.open('/check/dailyclassstudentdetail.do?method=getPlannedCheck'+para, "a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=1000,height=600");
        }
        function late(para){
             window.open('/check/dailyclassstudentdetail.do?method=getPlannedCheck'+para,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=1000,height=600");
        }
        function leave(para){
             window.open('/check/dailyclassstudentdetail.do?method=getPlannedCheck'+para,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=1000,height=600");
        }
        function nocome(para){
             window.open('/check/dailyclassstudentdetail.do?method=getClassOther'+para,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=1000,height=600");
        }
       <%
        String beginDate="";
        if(request.getAttribute("beginDate")!=null){
            beginDate = request.getAttribute("beginDate").toString();
        }else if(session.getAttribute("beginDate")!=null){
            beginDate = session.getAttribute("beginDate").toString();
        }
        String endDate="";
        if(request.getAttribute("endDate")!=null){
            endDate = request.getAttribute("endDate").toString();
        }else if(session.getAttribute("endDate")!=null){
           endDate = session.getAttribute("endDate").toString();
        }
        %>
        <%
          if(request.getAttribute("msg")!=null){
        %>
            alert('<%=request.getAttribute("msg").toString()%>')
        <%
        }
        %>
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
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> �༶���忼�ڱ��� </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>                    
		</div>
		<div id="filterDiv" style="text-align: left;">
				<html:form action="classcheckreport.do?method=dailyreport" method="post" >
                    <table width="100%">
                        <tr>
                            <td>
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
                            <td>
                                &nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;����
                                <html:select property="classno" onchange="changeDepartment();">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="deptList" property="DEPTID" labelProperty="DEPTNAME"/>
                                </html:select>
                            </td>
                        </tr>
                        <tr>              
                            <td width="25%">
                                &nbsp;��ʼ���ڣ�
					            <html:text property="beginDate" size="10"readonly="readonly" value="<%=beginDate%>"/>
					            <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
                            </td>
                            <td width="25%">
                                &nbsp;�������ڣ�
					            <html:text property="endDate" size="10" readonly="readonly" value="<%=endDate%>" />
					            <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                                <script type="text/javascript">
                                    new calendar("beginDate", "calBegin", "%Y%m%d");
                                    new calendar("endDate", "calEnd", "%Y%m%d");
                                </script>
                            </td>
                            <td width="50%">
                                &nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�̣�
                                <html:select property="courseId">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="courseList" property="COURSEID" labelProperty="COURSENAME"/>
                                </html:select>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="Submit" width="50" type="button" class="button_nor" value="��  ѯ" onclick="docheck()">
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
			<ec:table items="classcheckList" var="cla"  rowsDisplayed="50" action="classcheckreport.do?method=dailyreport">
				<ec:exportXls fileName="classchecklist.xls"  tooltip="���� Excel" />
				<ec:row>			   
					<ec:column property="classname" title="�༶" width="21%" />
					<ec:column property="coursename" title="�γ�" width="15%" />
					<ec:column property="coursenum" title="Ӧ���˴�" width="8%" >
						<a href="javascript:void(0);" onclick="shoud('&courseid=${cla.courseid}&classid=${cla.classno}&begindate=<%=beginDate%>&enddate=<%=endDate%>')">${cla.coursenum}</a>
					</ec:column>
					<ec:column property="checknum" title="ʵ���˴�" width="8%" >
						<a href="javascript:void(0);" onclick="real('&courseid=${cla.courseid}&classid=${cla.classno}&begindate=<%=beginDate%>&enddate=<%=endDate%>&type=real')">${cla.checknum}</a>
					</ec:column>
					<ec:column property="checkrate" title="������" width="8%" />
                    <ec:column property="absenceNum" title="ȱ���˴�" width="8%" >
                        <a href="javascript:void(0);" onclick="nocome('&courseid=${cla.courseid}&classid=${cla.classno}&begindate=<%=beginDate%>&enddate=<%=endDate%>&type=nocome');">${cla.absenceNum}</a>
					</ec:column>
					<%if(issysadmin==true){ %>
					<ec:column property="comelatenum" title="�ٵ��˴�" width="8%" >
						<a href="javascript:void(0);" onclick="late('&courseid=${cla.courseid}&classid=${cla.classno}&begindate=<%=beginDate%>&enddate=<%=endDate%>&type=late');">${cla.comelatenum}</a>
					</ec:column>
					<ec:column property="comelaterate" title="�ٵ���" width="8%" />
					<ec:column property="leaveearlynum" title="�����˴�" width="8%" >
                        <a href="javascript:void(0);" onclick="leave('&courseid=${cla.courseid}&classid=${cla.classno}&begindate=<%=beginDate%>&enddate=<%=endDate%>&type=leave');">${cla.leaveearlynum}</a>
					</ec:column>
					<ec:column property="leaveearlyrate" title="������" width="8%" />
					<%}%>
				</ec:row>
			</ec:table>

		</div>
		
	</body>
</html>

