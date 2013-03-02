<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>


<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
	
	<body>
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> �Ͽ�ʱ������ </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
			<div id=lineDiv class="hrLine">
				<table width="80%" border="0" cellspacing="0" cellpadding="0">
				</table>
			</div>

			<div id="tableDiv">
				<ec:table items="timeList" var="time" rowsDisplayed="50" action="classTimes.do?method=search">
					<ec:exportXls fileName="ClassTimes.xls" tooltip="���� Excel" />
					<ec:row>
						<ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="5%" style="text-align: center">
							<input type="checkbox" name="itemlist" value="${time.classNum}" style="border:0px" />
						</ec:column>
						<ec:column property="classNum" title="�δ�" width="20%" />
						<ec:column property="beginTime" title="��ʼʱ��" width="20%" />
						<ec:column property="endTime" title="����ʱ��" width="20%" />
						<ec:column property="update" title="�޸�" width="10%" sortable="false">
							<a href="classTimes.do?method=update_step1&classNum=${time.classNum}">�޸�</a>
						</ec:column>
					</ec:row>
				</ec:table>

			</div>
            </table>
    </body>
</html>