<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
    <head>
        <title>У԰һ��ͨ���ڹ���ϵͳ</title>
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
                alert("��ѡ����ȷ��ѧ��");
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
            <LI ><A onclick="changeTab('/check/dailyclassstudentdetail.do?method=getPlannedCheck')" href="javascript:void(0)">����ѧ��<c:out value="${typename}" />����</A></LI>
            <LI class="selectTag"><A href="javascript:void(0)">�Ǳ���ѧ��ȷ��<c:out value="${typename}" />����</A> </LI>
            <LI><A onClick="changeTab('/check/dailyclassstudentdetail.do?method=getInvalidCheck')" href="javascript:void(0)">�Ǳ���ѧ��δȷ��<c:out value="${typename}" />����</A> </LI>
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
							value="��   ��" onclick="window.close();">
					</td>
				</tr>
			</table>
		</div>
        <div id="tableDiv">
            <ec:table items="activeList" var="activedetail" rowsDisplayed="50" action="dailyclassstudentdetail.do?method=getValidCheck">
                <ec:exportXls fileName="activeDetailList.xls" tooltip="���� Excel" />
                <ec:row>
                    <ec:column property="id" title="ѡ��" width="4%" >
                       <input type="checkbox" name="stu1" value="${activedetail.id}" style="border:0px" />
                     </ec:column>
                    <ec:column property="coursename" title="�γ�" width="16%" />
                    <ec:column property="classname" title="�༶" width="37%" />
                    <ec:column property="stuempno" title="ѧ����" width="10%" />
                    <ec:column property="custname" title="����" width="8%" />
                    <ec:column property="checkdate" title="��������" width="8%" />
                    <ec:column property="checktime" title="ˢ��ʱ��" width="10%" />
                    <ec:column property="isactivate" title="�Ƿ���Ч" width="7%" />
                </ec:row>
            </ec:table>
        </div>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr>
                <td align="right">
                    &nbsp;&nbsp;
                    <input name="Submit22" type="button" class="submitButton"  value="ȡ��ȷ��" onclick="cancel();">
                </td>
            </tr>
        </table>
    </DIV>
	</body>
</html>