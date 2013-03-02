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
                    alert("����ʱ�������ڵ��ڿ�ʼʱ�䣡");
                    return false;
                }
                if(beginDate<termBeginDate){
                    alert("��ǰѧ�ڷ�ΧΪ"+termBeginDate+"----"+termEndDate+"����ѡʱ��α�����ѧ���ڣ�");
                    return false;
                }
                if(endDate>termEndDate){
                    alert("��ǰѧ�ڷ�ΧΪ"+termBeginDate+"----"+termEndDate+"����ѡʱ��α�����ѧ���ڣ�");
                    return false;
                }
                return true;
            }
        </script>
    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
    <DIV id=con>

        <UL id=tags>
            <LI class="selectTag"><A href="javascript:void(0)">����ѧ��<c:out value="${typename}" />����</A></LI>
            <LI><A onClick="changeTab('/check/classtermcheckreport.do?method=getValidCheck')" href="javascript:void(0)">�Ǳ���ѧ��ȷ��<c:out value="${typename}" />����</A> </LI>
            <LI><A onClick="changeTab('/check/classtermcheckreport.do?method=getInvalidCheck')" href="javascript:void(0)">�Ǳ���ѧ��δȷ��<c:out value="${typename}" />����</A> </LI>
        </UL>
         <div id="lineDiv" class="tagContent">
             <html:form action="classtermcheckreport.do?method=getPlannedCheck" method="post" onsubmit="return checkDate();">
                    <table width="100%">
                        <tr>
                            <td width="30%">
                                &nbsp;ѧ&nbsp;&nbsp;��&nbsp;&nbsp;�ţ�
                                <html:text property="stuempNo" maxlength="50"/>
                            </td>
                            <td width="25%" align="left">
                                &nbsp;��ʼ���ڣ�
					            <html:text property="beginDate" size="10"readonly="true"/>
					            <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
                            </td>
                            <td width="45%" align="left">
                                &nbsp;�������ڣ�
					            <html:text property="endDate" size="10" readonly="true"/>
					            <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                                <script type="text/javascript">
                                    new calendar("beginDate", "calBegin", "%Y%m%d");
                                    new calendar("endDate", "calEnd", "%Y%m%d");
                                </script>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="Submit" width="50" type="submit" class="button_nor" value="��  ѯ">
                                &nbsp;&nbsp;&nbsp;&nbsp;<input name="Submit22" type="button" class="button_nor" value="��  ��" onclick="window.close();">
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
                <ec:exportXls fileName="classCheckDetailList.xls" tooltip="���� Excel" />
                <ec:row>
                    <ec:column property="courseName" title="�γ�" width="20%" />
                    <ec:column property="deptName" title="�༶" width="37%" />
                    <ec:column property="stuempNo" title="ѧ����" width="12%" />
                    <ec:column property="custName" title="����" width="10%" />
                    <ec:column property="useDate" title="��������" width="10%" />
                    <ec:column property="checkTime" title="ˢ��ʱ��" width="11%" />
                </ec:row>
            </ec:table>
        </div>
  </DIV>
	</body>
</html>