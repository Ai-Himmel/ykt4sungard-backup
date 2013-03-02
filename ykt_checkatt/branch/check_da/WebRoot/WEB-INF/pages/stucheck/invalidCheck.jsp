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
         function confirmselect(){
                var len = document.getElementsByName("stu2").length;
                var retstr = "";
                for (i = 0; i < len; i++)
                {
                    if (document.getElementsByName("stu2")[i].checked == true)
                    {
                        retstr = retstr + document.getElementsByName("stu2")[i].value +",";
                    }
                }
                return retstr;
         }
         function confirm(){
             if(confirmselect()==""){
                alert("��ѡ��δȷ��ѧ��");
                return false;
             }
             if(confirmselect()!=""){
                document.tabForm.student.value=confirmselect();
                document.tabForm.cmd.value="confirm";
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
            <LI><A onclick="changeTab('/check/dailyclassstudentdetail.do?method=getPlannedCheck')" href="javascript:void(0)">����ѧ��<c:out value="${typename}" />����</A></LI>
            <LI><A onClick="changeTab('/check/dailyclassstudentdetail.do?method=getValidCheck')" href="javascript:void(0)">�Ǳ���ѧ��ȷ��<c:out value="${typename}" />����</A> </LI>
            <LI class="selectTag"><A href="javascript:void(0)">�Ǳ���ѧ��δȷ��<c:out value="${typename}" />����</A> </LI>
        </UL>
         <div id="lineDiv" class="tagContent">
             <form action="/check/dailyclassstudentdetail.do?method=updateUnplanStudent"  name="tabForm" id="tabForm" method="post">
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
        <div id="tableDiv" >
            <ec:table items="noactiveList" var="noactivedetail" rowsDisplayed="50" action="dailyclassstudentdetail.do?method=getInvalidCheck">
                <ec:exportXls fileName="noactiveDetailList.xls" tooltip="���� Excel" />
                <ec:row>
                     <ec:column property="id" title="ѡ��" width="4%" >
                       <input type="checkbox" name="stu2" value="${noactivedetail.id}" style="border:0px" />
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
		<div id="lineDiv1" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td align="right">
						&nbsp;&nbsp;
						<input name="Submit22" type="button" class="submitButton"  value="ȷ   ��" onclick="confirm();">
					</td>
				</tr>

			</table>
		</div>
  </DIV>
</body>
</html>
