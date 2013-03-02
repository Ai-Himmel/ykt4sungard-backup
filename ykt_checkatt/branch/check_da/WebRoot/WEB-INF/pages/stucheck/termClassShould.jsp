<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
    <head>
        <title>校园一卡通考勤管理系统</title>
        <meta http-equiv="Content-Type" content="text/html;">

        <%@ include file="/pages/common/meta.jsp"%>
        <%@ include file="/pages/components/calendar/calendar.jsp"%>
        <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
        <link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
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
        <div id="filterDiv" style="text-align: left;">
				<html:form action="classtermcheckreport.do?method=getClassShould" method="post" >
                    <table width="100%">
                        <tr>
                            <td width="30%">
                                &nbsp;学&nbsp;&nbsp;工&nbsp;&nbsp;号：
                                <html:text property="stuempNo" maxlength="50"/>               
                            </td>
                            <td width="30%" align="left">
                                &nbsp;开始日期：
					            <html:text property="beginDate" size="10"readonly="true"/>
					            <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
                            </td>
                            <td width="40%" align="left">
                                &nbsp;结束日期：
					            <html:text property="endDate" size="10" readonly="true"/>
					            <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                                <script type="text/javascript">
                                    new calendar("beginDate", "calBegin", "%Y%m%d");
                                    new calendar("endDate", "calEnd", "%Y%m%d");
                                </script>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="Submit" width="50" type="submit" class="button_nor" value="查  询">
                            </td>
                        </tr>
                    </table>
                    <html:hidden property="classno" />
                    <html:hidden property="courseId" />
                    <html:hidden property="termId" />
                    <html:hidden property="type" />
				</html:form>
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
            <ec:table items="list" var="classdetail" rowsDisplayed="50" action="classtermcheckreport.do?method=getClassShould">
                <ec:exportXls fileName="class.xls" tooltip="导出 Excel" />
                <ec:row>
                    <ec:column property="courseName" title="课程" width="25%" />
                    <ec:column property="deptName" title="班级" width="40%" />
                    <ec:column property="stuempNo" title="学工号" width="14%" />
                    <ec:column property="custName" title="姓名" width="10%" />
                    <ec:column property="useDate" title="应考勤日期" width="11%" />
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
