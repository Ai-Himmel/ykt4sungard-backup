<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
    <head>
        <title>У԰һ��ͨ���ڹ���ϵͳ</title>
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
                                &nbsp;ѧ&nbsp;&nbsp;��&nbsp;&nbsp;�ţ�
                                <html:text property="stuempNo" maxlength="50"/>               
                            </td>
                            <td width="30%" align="left">
                                &nbsp;��ʼ���ڣ�
					            <html:text property="beginDate" size="10"readonly="true"/>
					            <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
                            </td>
                            <td width="40%" align="left">
                                &nbsp;�������ڣ�
					            <html:text property="endDate" size="10" readonly="true"/>
					            <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                                <script type="text/javascript">
                                    new calendar("beginDate", "calBegin", "%Y%m%d");
                                    new calendar("endDate", "calEnd", "%Y%m%d");
                                </script>
                                &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="Submit" width="50" type="submit" class="button_nor" value="��  ѯ">
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
							value="��   ��" onclick="window.close();">
					</td>
				</tr>

			</table>
		</div>

        <div id="tableDiv">
            <ec:table items="list" var="classdetail" rowsDisplayed="50" action="classtermcheckreport.do?method=getClassShould">
                <ec:exportXls fileName="class.xls" tooltip="���� Excel" />
                <ec:row>
                    <ec:column property="courseName" title="�γ�" width="25%" />
                    <ec:column property="deptName" title="�༶" width="40%" />
                    <ec:column property="stuempNo" title="ѧ����" width="14%" />
                    <ec:column property="custName" title="����" width="10%" />
                    <ec:column property="useDate" title="Ӧ��������" width="11%" />
                </ec:row>
            </ec:table>

        </div>
        <div id="lineDiv" class="hrLine">
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

	</body>
</html>
