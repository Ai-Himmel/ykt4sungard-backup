<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>

<html:html>
	<head>
		<title>上海电大校园一卡通考勤管理系统</title>
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
			<strong> <font class="medium"> 同步日志查看 </font> </strong>
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
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;学&nbsp;&nbsp;&nbsp;&nbsp;期：
                                <html:select property="termName">
                                    <html:option value="">请选择</html:option>
                                    <html:options collection="terms" property="termName" labelProperty="termName"/>
                                </html:select>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;使用周次：
                                <html:text property="useWeek" size="10"/>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                                <input id="searchBtn"  width="50" type="button" class="button_nor" value="查  询" onclick="searchLog();">
                            </td>
                        </tr>
                    </table>
				</html:form>
		</div>
        <div id="tableDiv">
            <logic:present name="result">
			<ec:table items="result" var="syncLog" sortable="true" rowsDisplayed="50" action="syncCourseplan.do?method=findSyncLog" locale="zh_CN" filterable="false">
				<ec:exportXls fileName="syncLog.xls"  tooltip="导出 Excel" />
				<ec:row>
					<ec:column property="term" title="学期" width="10%" filterable="false"  escapeAutoFormat="true"/>
					<ec:column property="useWeek" title="使用周次" width="10%" escapeAutoFormat="true"/>
					<ec:column property="recordCount" title="总记录数" width="10%" escapeAutoFormat="true"/>
                    <ec:column property="syncTime" title="同步时间" width="10%"/>
                    <ec:column property="remark" title="备注" width="60%"/>
				</ec:row>
			</ec:table>
            </logic:present>
		</div>
	</body>
</html:html>
