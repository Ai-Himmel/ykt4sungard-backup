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
        <script type="text/javascript">
            function changeTab(action){
                var tabForm = document.forms["tabForm"];
                tabForm.action = action;
                tabForm.submit();
            }
        </script>
    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
    <DIV id=con>

        <UL id=tags>
            <LI class="selectTag"><A href="javascript:void(0)">本班学生<c:out value="${typename}" />考勤</A></LI>
            <LI><A onClick="changeTab('/check/dailyclassstudentdetail.do?method=getValidCheck')" href="javascript:void(0)">非本班学生确认<c:out value="${typename}" />考勤</A> </LI>
            <LI><A onClick="changeTab('/check/dailyclassstudentdetail.do?method=getInvalidCheck')" href="javascript:void(0)">非本班学生未确认<c:out value="${typename}" />考勤</A> </LI>
        </UL>
         <div id="lineDiv" class="tagContent">
             <form name="tabForm" action="" method="post">
                 <input id="courseid" name="courseid" type="hidden" value="<c:out value="${courseid}" />" />
                 <input id="classid" name="classid" type="hidden" value="<c:out value="${classid}" />" />
                 <input id="begindate" name="begindate" type="hidden" value="<c:out value="${begindate}" />" />
                 <input id="enddate" name="enddate" type="hidden" value="<c:out value="${enddate}" />" />
                 <input id="type" name="type" type="hidden" value="<c:out value="${type}" />" />
             </form>
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
            <ec:table items="list" var="classcheckdetail" rowsDisplayed="50" action="dailyclassstudentdetail.do?method=getPlannedCheck">
                <ec:exportXls fileName="classCheckDetailList.xls" tooltip="导出 Excel" />
                <ec:row>
                    <ec:column property="coursename" title="课程" width="20%" />
                    <ec:column property="classname" title="班级" width="37%" />
                    <ec:column property="stuempno" title="学工号" width="12%" />
                    <ec:column property="custname" title="姓名" width="10%" />
                    <ec:column property="usedate" title="考勤日期" width="10%" />
                    <ec:column property="checktime" title="刷卡时间" width="11%" />
                </ec:row>
            </ec:table>
        </div>
  </DIV>
	</body>
</html>