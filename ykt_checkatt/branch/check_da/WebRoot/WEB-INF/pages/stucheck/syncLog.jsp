<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>

<html:html>
	<head>
		<title>�Ϻ����У԰һ��ͨ���ڹ���ϵͳ</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel="stylesheet">
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel="stylesheet">
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
        <script type="text/javascript">
            function searchLog(){
                document.forms[0].submit();
            }
        </script>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ͬ����־�鿴 </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
				<html:form action="syncCourseplan.do?method=findSyncLog" method="post">
                    <table width="100%">
                        <tr>
                            <td align="center">
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ѧ&nbsp;&nbsp;&nbsp;&nbsp;�ڣ�
                                <html:select property="termName">
                                    <html:option value="">��ѡ��</html:option>
                                    <html:options collection="terms" property="termName" labelProperty="termName"/>
                                </html:select>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;ʹ���ܴΣ�
                                <html:text property="useWeek" size="10"/>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                <input id="searchBtn"  width="50" type="button" class="button_nor" value="��  ѯ" onclick="searchLog();">
                            </td>
                        </tr>
                    </table>
				</html:form>
		</div>
        <div id="tableDiv">
            <logic:present name="result">
			<ec:table items="result" var="syncLog" sortable="true" rowsDisplayed="50" action="syncCourseplan.do?method=findSyncLog" locale="zh_CN" filterable="false">
				<ec:exportXls fileName="syncLog.xls"  tooltip="���� Excel" />
				<ec:row>
					<ec:column property="term" title="ѧ��" width="10%" filterable="false"  escapeAutoFormat="true"/>
					<ec:column property="useWeek" title="ʹ���ܴ�" width="10%" escapeAutoFormat="true"/>
					<ec:column property="recordCount" title="�ܼ�¼��" width="10%" escapeAutoFormat="true"/>
                    <ec:column property="syncTime" title="ͬ��ʱ��" width="10%"/>
                    <ec:column property="remark" title="��ע" width="60%"/>
				</ec:row>
			</ec:table>
            </logic:present>
		</div>
	</body>
</html:html>
