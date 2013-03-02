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
        <script language="javascript">
            function cancelselect(){
                var len = document.getElementsByName("stu1").length;
                var retstr = "";
                for (i = 0; i < len; i++)
                {
                    if (document.getElementsByName("stu1")[i].checked == true)
                    {
                        retstr = retstr + document.getElementsByName("stu1")[i].value +",";
                    }
                }
                return retstr;
            }
           function cancel(){
             if(cancelselect()==""){
                alert("请选择已确认学生");
                return false;
             }
             if(cancelselect()!=""){
                document.tabForm.student.value=cancelselect();
                document.tabForm.cmd.value="cancel";
                document.tabForm.submit();
             }
           }
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
            <LI ><A onclick="changeTab('/check/dailyclassstudentdetail.do?method=getPlannedCheck')" href="javascript:void(0)">本班学生<c:out value="${typename}" />考勤</A></LI>
            <LI class="selectTag"><A href="javascript:void(0)">非本班学生确认<c:out value="${typename}" />考勤</A> </LI>
            <LI><A onClick="changeTab('/check/dailyclassstudentdetail.do?method=getInvalidCheck')" href="javascript:void(0)">非本班学生未确认<c:out value="${typename}" />考勤</A> </LI>
        </UL>
         <div id="lineDiv" class="tagContent">
             <form action="/check/dailyclassstudentdetail.do?method=updateUnplanStudent"  name="tabForm" id="tabForm"  method="post">
                <input type="hidden" name="student">
                <input type="hidden" name="cmd">
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
            <ec:table items="activeList" var="activedetail" rowsDisplayed="50" action="dailyclassstudentdetail.do?method=getValidCheck">
                <ec:exportXls fileName="activeDetailList.xls" tooltip="导出 Excel" />
                <ec:row>
                    <ec:column property="id" title="选择" width="4%" >
                       <input type="checkbox" name="stu1" value="${activedetail.id}" style="border:0px" />
                     </ec:column>
                    <ec:column property="coursename" title="课程" width="16%" />
                    <ec:column property="classname" title="班级" width="37%" />
                    <ec:column property="stuempno" title="学工号" width="10%" />
                    <ec:column property="custname" title="姓名" width="8%" />
                    <ec:column property="checkdate" title="考勤日期" width="8%" />
                    <ec:column property="checktime" title="刷卡时间" width="10%" />
                    <ec:column property="isactivate" title="是否有效" width="7%" />
                </ec:row>
            </ec:table>
        </div>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td align="right">
                    &nbsp;&nbsp;
                    <input name="Submit22" type="button" class="submitButton"  value="取消确认" onclick="cancel();">
                </td>
            </tr>
        </table>
    </DIV>
	</body>
</html>