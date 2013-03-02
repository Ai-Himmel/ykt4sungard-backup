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
			<strong> <font class="medium"> �γ̼ƻ�ͬ�� </font> </strong>
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
                &nbsp;&nbsp;&nbsp;ѧ�ڣ�
                <html:select property="termName">
                    <html:option value="">��ѡ��</html:option>
                    <html:options collection="terms" property="termName" labelProperty="termName"/>
                </html:select>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ͬ�����ڣ�
                <html:text property="beginDate" size="12" readonly="true"/>
                <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��ʼ����" style="cursor:pointer">
                ------------
                <html:text property="endDate" size="12" readonly="true"/>
                <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��������" style="cursor:pointer">
                <script type="text/javascript">
                    new calendar("beginDate", "calBegin", "%Y%m%d");
                    new calendar("endDate", "calEnd", "%Y%m%d");
                </script>
                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                <input name="Submit" type="button" class="submitButton" value="�鿴�쳣�γ̼ƻ�" onclick="javascript:error();">
            </td>
        </tr>
		<tr>
            <td height="40" align="left" valign="middle" class="tdborder02">
                &nbsp;&nbsp;&nbsp;
                <input name="Submit" type="button" class="submitButton" value="Ԥ�����ܿγ̼ƻ�" onclick="javascript:preview();">
                &nbsp;&nbsp;&nbsp;
                <input name="Submit" type="button" class="submitButton" value="У�����ܿγ̼ƻ�" onclick="javascript:check();">
                &nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;
                <span style="color:red"><%=request.getAttribute("previewInfo")==null?"":request.getAttribute("previewInfo")%></span>

            </td>
        </tr>
        <tr>
            <td height="40" align="left" valign="middle" class="tdborder02">
                &nbsp;&nbsp;&nbsp;
                <input name="Submit" type="button" class="submitButton" value="�鿴���ܿγ̼ƻ�" onclick="javascript:view();">
                &nbsp;&nbsp;&nbsp;
                <input name="Submit" type="button" class="submitButton" value="�������ܿγ̼ƻ�" onclick="javascript:importData();">
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
				<ec:exportXls fileName="errorCourseplan.xls"  tooltip="���� Excel" />
				<ec:row>
                    <ec:column property="id"  title="ID" width="60px"/>
                    <ec:column property="term"  title="ѧ��" width="70px"/>
                    <ec:column property="faculty"  title="Ժϵ" width="110px"/>
				    <ec:column property="area"  title="У��" width="100px"/>
					<ec:column property="building" title="¥��" width="80px"/>
					<ec:column property="room" title="����" width="80px"/>
                    <ec:column property="course" title="�γ�" width="140px"/>
					<ec:column property="stuempno" title="��ʦ����" width="60px" escapeAutoFormat="true"/>
					<ec:column property="custname" title="��ʦ����" width="60px"/>
					<ec:column property="deptname" title="�༶����" width="140px"/>
                    <ec:column property="deptcode" title="�༶����" width="140px" escapeAutoFormat="true" style="word-break:break-all"/>
					<ec:column property="week" title="�ܼ�" width="50px"/>
					<ec:column property="beginWeek" title="��ʼ�ܴ�" width="60px"/>
                    <ec:column property="endWeek" title="�����ܴ�" width="60px"/>
					<ec:column property="beginClass" title="��ʼ�δ�" width="60px"/>
					<ec:column property="endClass" title="�����δ�" width="60px"/>
                    <ec:column property="ischeck" title="�Ƿ���" width="60px"/>
                    <ec:column property="isopen" title="�Ƿ���" width="60px"/>
                    <ec:column property="checkInfo" title="У����Ϣ" viewsDenied="html"/>
				</ec:row>
			</ec:table>
		</div>
	</body>
</html>

