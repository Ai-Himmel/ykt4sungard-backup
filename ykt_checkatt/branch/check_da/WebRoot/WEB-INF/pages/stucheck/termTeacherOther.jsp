<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
    <head>
        <title>校园一卡通考勤管理系统</title>
        <meta http-equiv="Content-Type" content="text/html;">

        <%@ include file="/pages/common/meta.jsp"%>
        <%@ include file="/pages/components/calendar/calendar.jsp"%>
        <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel="stylesheet">
        <link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel="stylesheet">
        <script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
        <%String typename = request.getAttribute("typename").toString(); %>
    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

        <div id="titleDiv" class="pageTitle">
            <strong> <font class="medium"><%=typename%> </font> </strong>
        </div>
        <div id="lineDiv" class="hrLine">
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                    <td class="tdborderLine">

                    </td>
                </tr>
            </table>
        </div>

        <div id="lineDiv" class="hrLine">
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                    <td class="tdborderLine"></td>
                </tr>
            </table>
        </div>

         <div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td align="right">
						&nbsp;&nbsp;
						<input name="Submit22" type="button" class="submitButton"
							value="关   闭" onclick="window.close();">
					</td>
				</tr>

			</table>
		</div>

        <div id="tableDiv">
            <ec:table items="list" var="teacher" rowsDisplayed="50" action="teachertermcheckreport.do?method=getTeacherOther">
                <ec:exportXls fileName="teacher.xls" tooltip="导出 Excel" />
                <ec:row>
                    <ec:column property="courseName" title="课程" width="30%" />
                    <ec:column property="stuempNo" title="学工号" width="20%" />
                    <ec:column property="custName" title="姓名" width="20%" />
                    <ec:column property="useDate" title="考勤日期" width="15%" />
                    <ec:column property="checkTime" title="刷卡时间" width="15%" />
                </ec:row>
            </ec:table>

        </div>

		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td align="right">
						&nbsp;&nbsp;
						<input name="Submit22" type="button" class="submitButton"
							value="关   闭" onclick="window.close();">
					</td>
				</tr>

			</table>
		</div>

	</body>
</html>
