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

        <script type="text/javascript">
            function preview(){
                var syncForm = document.syncForm;
                syncForm.action = "syncCourseplan.do?method=previewData";
                syncForm.submit();
            }
            function importData(){
                var syncForm = document.syncForm;
                syncForm.action = "syncCourseplan.do?method=importData";
                syncForm.submit();
            }
            function check(){
                var syncForm = document.syncForm;
                syncForm.action = "syncCourseplan.do?method=checkPreviewData";
                syncForm.submit();
            }
            function view(){
                var syncForm = document.syncForm;
                syncForm.action = "syncCourseplan.do?method=findCourseplanTemp&status=1";
                syncForm.submit();
            }
            function error(){
                var syncForm = document.syncForm;
                syncForm.action = "syncCourseplan.do?method=findCourseplanTemp&status=0";
                syncForm.submit();
            }
        </script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> 课程计划同步 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="1400px" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>

        <html:form action="syncCourseplan.do?method=findCourseplanTemp" method="post">
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
            <td height="40" align="left" valign="middle" class="tdborder02">
                &nbsp;&nbsp;&nbsp;学期：
                <html:select property="termName">
                    <html:option value="">请选择</html:option>
                    <html:options collection="terms" property="termName" labelProperty="termName"/>
                </html:select>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;同步日期：
                <html:text property="beginDate" size="12" readonly="true"/>
                <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="开始日期" style="cursor:pointer">
                ------------
                <html:text property="endDate" size="12" readonly="true"/>
                <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="结束日期" style="cursor:pointer">
                <script type="text/javascript">
                    new calendar("beginDate", "calBegin", "%Y%m%d");
                    new calendar("endDate", "calEnd", "%Y%m%d");
                </script>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <input name="Submit" type="button" class="submitButton" value="查看异常课程计划" onclick="javascript:error();">
            </td>
        </tr>
		<tr>
            <td height="40" align="left" valign="middle" class="tdborder02">
                &nbsp;&nbsp;&nbsp;
                <input name="Submit" type="button" class="submitButton" value="预览下周课程计划" onclick="javascript:preview();">
                &nbsp;&nbsp;&nbsp;
                <input name="Submit" type="button" class="submitButton" value="校验下周课程计划" onclick="javascript:check();">
                &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;
                <span style="color:red"><%=request.getAttribute("previewInfo")==null?"":request.getAttribute("previewInfo")%></span>

            </td>
        </tr>
        <tr>
            <td height="40" align="left" valign="middle" class="tdborder02">
                &nbsp;&nbsp;&nbsp;
                <input name="Submit" type="button" class="submitButton" value="查看下周课程计划" onclick="javascript:view();">
                &nbsp;&nbsp;&nbsp;
                <input name="Submit" type="button" class="submitButton" value="导入下周课程计划" onclick="javascript:importData();">
                &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;
                <span style="color:red"><%=request.getAttribute("importInfo")==null?"":request.getAttribute("importInfo")%></span>
            </td>
        </tr>
		</table>
        </html:form>
		<div id="lineDiv" class="hrLine">
			<table width="1400px" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv" style="position:relative;width:1450px;overflow-x:scroll;padding:0px; margin:0px;">
			<ec:table items="result" var="temp" sortable="true"  rowsDisplayed="100" 
			    action="syncCourseplan.do?method=findCourseplanTemp" locale="zh_CN" filterable="false">
				<ec:exportXls fileName="errorCourseplan.xls"  tooltip="导出 Excel" />
				<ec:row>
                    <ec:column property="id"  title="ID" width="60px"/>
                    <ec:column property="term"  title="学期" width="70px"/>
                    <ec:column property="faculty"  title="院系" width="110px"/>
				    <ec:column property="area"  title="校区" width="100px"/>
					<ec:column property="building" title="楼宇" width="80px"/>
					<ec:column property="room" title="教室" width="80px"/>
                    <ec:column property="course" title="课程" width="140px"/>
					<ec:column property="stuempno" title="教师工号" width="60px" escapeAutoFormat="true"/>
					<ec:column property="custname" title="教师姓名" width="60px"/>
					<ec:column property="deptname" title="班级名称" width="140px"/>
                    <ec:column property="deptcode" title="班级代码" width="140px" escapeAutoFormat="true" style="word-break:break-all"/>
					<ec:column property="week" title="周几" width="50px"/>
					<ec:column property="beginWeek" title="开始周次" width="60px"/>
                    <ec:column property="endWeek" title="结束周次" width="60px"/>
					<ec:column property="beginClass" title="开始课次" width="60px"/>
					<ec:column property="endClass" title="结束课次" width="60px"/>
                    <ec:column property="ischeck" title="是否考勤" width="60px"/>
                    <ec:column property="isopen" title="是否开门" width="60px"/>
                    <ec:column property="checkInfo" title="校验信息" viewsDenied="html"/>
				</ec:row>
			</ec:table>
		</div>
	</body>
</html>

