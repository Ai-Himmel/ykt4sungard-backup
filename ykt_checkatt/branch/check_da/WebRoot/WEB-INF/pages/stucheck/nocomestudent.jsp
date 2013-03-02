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

    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

        <div id="titleDiv" class="pageTitle">
            <strong> <font class="medium">缺勤学生名单 </font> </strong>
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
            <ec:table items="list" var="stucheckdetail" rowsDisplayed="50" action="todaystuchecksearch.do?method=allClassStudent">
                <ec:exportXls fileName="todayStuCheckDetailList.xls" tooltip="导出 Excel" />
                <ec:row>
                    <ec:column property="coursename" title="课程" width="100" />
                    <ec:column property="classname" title="班级" width="100" />
                    <ec:column property="stuempno" title="学工号" width="60" />
                    <ec:column property="custname" title="姓名" width="80" />
                    <ec:column property="usedate" title="考勤日期" width="150" />  
                    <ec:column property="punchtime" title="刷卡时间" width="150" />                 
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
