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
                if(!checkDate()){
                    return;
                }
                var reportForm = document.forms["reportForm"];
                reportForm.action = action;
                reportForm.submit();
            }
            function checkDate(){
                var reportForm = document.forms["reportForm"];
                var termBeginDate = reportForm.termBeginDate.value;
                var termEndDate = reportForm.termEndDate.value;
                var beginDate = reportForm.beginDate.value;
                var endDate = reportForm.endDate.value;
                if(beginDate>=endDate){
                    alert("结束时间必须大于等于开始时间！");
                    return false;
                }
                if(beginDate<termBeginDate){
                    alert("当前学期范围为"+termBeginDate+"----"+termEndDate+"，所选时间段必须在学期内！");
                    return false;
                }
                if(endDate>termEndDate){
                    alert("当前学期范围为"+termBeginDate+"----"+termEndDate+"，所选时间段必须在学期内！");
                    return false;
                }
                return true;
            }
        </script>
    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
    <DIV id=con>

        <UL id=tags>
            <LI class="selectTag"><A href="javascript:void(0)">本班学生<c:out value="${typename}" />考勤</A></LI>
            <LI><A onClick="changeTab('/check/classtermcheckreport.do?method=getValidCheck')" href="javascript:void(0)">非本班学生确认<c:out value="${typename}" />考勤</A> </LI>
            <LI><A onClick="changeTab('/check/classtermcheckreport.do?method=getInvalidCheck')" href="javascript:void(0)">非本班学生未确认<c:out value="${typename}" />考勤</A> </LI>
        </UL>
         <div id="lineDiv" class="tagContent">
             <html:form action="classtermcheckreport.do?method=getPlannedCheck" method="post" onsubmit="return checkDate();">
                    <table width="100%">
                        <tr>
                            <td width="30%">
                                &nbsp;学&nbsp;&nbsp;工&nbsp;&nbsp;号：
                                <html:text property="stuempNo" maxlength="50"/>
                            </td>
                            <td width="25%" align="left">
                                &nbsp;开始日期：
					            <html:text property="beginDate" size="10"readonly="true"/>
					            <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
                            </td>
                            <td width="45%" align="left">
                                &nbsp;结束日期：
					            <html:text property="endDate" size="10" readonly="true"/>
					            <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                                <script type="text/javascript">
                                    new calendar("beginDate", "calBegin", "%Y%m%d");
                                    new calendar("endDate", "calEnd", "%Y%m%d");
                                </script>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="Submit" width="50" type="submit" class="button_nor" value="查  询">
                                &nbsp;&nbsp;&nbsp;&nbsp;<input name="Submit22" type="button" class="button_nor" value="关  闭" onclick="window.close();">
                            </td>
                        </tr>                                              
                    </table>
                    <html:hidden property="classno" />
                    <html:hidden property="courseId" />
                    <html:hidden property="termId" />
                    <html:hidden property="type" />
                    <html:hidden property="termBeginDate" />
                    <html:hidden property="termEndDate" />
				</html:form>
		</div>                       

        <div id="tableDiv">
            <ec:table items="list" var="classcheckdetail" rowsDisplayed="50" action="classtermcheckreport.do?method=getPlannedCheck">
                <ec:exportXls fileName="classCheckDetailList.xls" tooltip="导出 Excel" />
                <ec:row>
                    <ec:column property="courseName" title="课程" width="20%" />
                    <ec:column property="deptName" title="班级" width="37%" />
                    <ec:column property="stuempNo" title="学工号" width="12%" />
                    <ec:column property="custName" title="姓名" width="10%" />
                    <ec:column property="useDate" title="考勤日期" width="10%" />
                    <ec:column property="checkTime" title="刷卡时间" width="11%" />
                </ec:row>
            </ec:table>
        </div>
  </DIV>
	</body>
</html>