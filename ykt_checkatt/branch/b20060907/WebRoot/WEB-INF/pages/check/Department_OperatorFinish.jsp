<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<html>
<head>
<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
</head>

<body>
<div class="pageTitle">
<c:out value="${msg}" />
</div>
<form name="clerkForm"  action="department.do?method=addConf" method="post" >
<jodd:form bean="request">
       <%@ include file="/pages/common/messages.jsp" %>
        <table class="border" width=100% cellSpacing=0 cellPadding=2 align="center">
           <tr>
                <td class="left" width="20%">�Űಿ��:</td>
                <td class="right" align="left">
                    <c:out value="${dptName}" />
                </td>
            </tr>
            <tr>
                <td class="left">�����ƶ�:</td>
                <td class="right">
					<c:out value="${workconfDetail}" />
					<input type="hidden" name="new_workconfDetail" value="<c:out value='${workconfDetail}' />"/>
                </td>
            </tr>
            <tr>
                <td class="left">���ڹ���ʱ��:</td>
                <td class="right"> 
				<c:out value="${timeDetail}" />
				<input type="hidden" name="new_timeDetail" value="<c:out value='${timeDetail}' />"/>
			    </td>
            </tr>
			<tr>
               <td class="left" width="20%">
			   ����ʱ��:
			   </td>
               <td class="right">
				<span class="medium">
				��ʼ����
				</span> &nbsp;
                <c:out value="${startDate}" />
				&nbsp;	
				��������
				&nbsp;
				 <c:out value="${endDate}" />
               </td>
            </tr>
			<tr>
                <td class="left" width="20%">����:</td>
                <td class="right">
                   <c:out value="${isSeat}" />
                </td>
            </tr>
            <tr>
                <td colspan="2" class="bottom">
                    <input type="button" class="submitButton" name="submitButton" value="<c:out value='${btnInfo}' />"  style="margin-right:60px" onclick="<c:out value='${actionUrl}' />"/>
					 <input type="button" class="submitButton" name="submitButton" value="�˳�"  style="margin-right:60px" onclick="window.location.href='department.do?method=goDeptConf';"/>
					<BUTTON onclick="history.back();">��һ��</BUTTON>
                   
                </td>
            </tr>
        </table>
		</jodd:form>
</form>

<div id="titleDiv" class="pageTitle" style="display:<c:out value='${display}'/>">
<strong>
<font class="medium">
<c:out value="${dptName}" />�ص����Ű���Ϣ
</font>
</strong>
</div>

<div id="tableDiv" style="display:<c:out value='${display}'/>">
			<ec:table items="existList" var="dptConf" rowsDisplayed="5" action="department.do?method=addConf">
				<ec:exportXls fileName="existList.xls" tooltip="���� Excel" />
				<ec:row>
					<ec:column property="dptname" title="����" width="60" />
                    <ec:column property="startdate" title="��ʼʱ��" width="60" />
					<ec:column property="enddate" title="����ʱ��" width="60" />
					<ec:column property="wconfname" title="�����ƶ�" width="120" />
					<ec:column property="tconfname" title="����ʱ��" width="120" />
					
				</ec:row>
			</ec:table>

		</div>
</body>
</html>
