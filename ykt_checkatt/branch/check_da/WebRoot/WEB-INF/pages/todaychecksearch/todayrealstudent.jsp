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
    
    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

        <div id="titleDiv" class="pageTitle">
            <strong> <font class="medium">ʵ��ѧ������ </font> </strong>
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
							value="��   ��" onclick="window.close();">
					</td>
				</tr>

			</table>
		</div>
        
        <div id="tableDiv">
            <ec:table items="list" var="stucheckdetail" rowsDisplayed="50" action="todaystuchecksearch.do?method=allClassStudent">
                <ec:exportXls fileName="StuCheckDetailList.xls" tooltip="���� Excel" />
                <ec:row>
                    <ec:column property="coursename" title="�γ�" width="18%" />
                    <ec:column property="classname" title="�༶" width="42%" />
                    <ec:column property="stuempno" title="ѧ����" width="12%" />
                    <ec:column property="custname" title="����" width="9%" />
                    <ec:column property="usedate" title="��������" width="10%" />
                    <ec:column property="punchtime" title="ˢ��ʱ��" width="9%"/>                 
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
