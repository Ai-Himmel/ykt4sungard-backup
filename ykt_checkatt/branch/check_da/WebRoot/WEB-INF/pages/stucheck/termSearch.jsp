<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>


<html>
	<head>
		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
	</head>
	<%String msg = (String) request.getAttribute("msg");
			if (msg != null) {

	%>
	<script language="javascript">
	alert('<%=msg%>');
</script>
	<%}%>
	<body>
		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ѧ�ڶ��� </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="40" align="left" valign="middle" class="tdborder02">
					<input name="Submit" type="button" class="submitButton" value=" �� �� " onclick="window.location.href='term.do?method=addTerm_init';">
					&nbsp;&nbsp;&nbsp;
					
					<input name="Submit" type="button" class="submitButton" value=" ɾ �� " onclick="javascript:batch_del(document.forms.ec,'ѧ��','<c:url value="term.do?method=deleteTerm" />');">
				</td>
			</tr>
			<div id=lineDiv class="hrLine">
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td class="tdborderLine"></td>
					</tr>
				</table>
			</div>
			
			<div id="tableDiv"> 
				<ec:table items="termList" var="terms" rowsDisplayed="50" action="term.do?method=search">
					<ec:exportXls fileName="termList.xls" tooltip="���� Excel" />
					<ec:row>
						<ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="30" style="text-align: left">
							<input type="checkbox" name="itemlist" value="${terms.termId}" style="border:0px" />
						</ec:column>
						<ec:column property="termName" title="ѧ������" width="100" />
						<ec:column property="beginDate" title="������ʼ��" width="80" />
						<ec:column property="endDate" title="���ν�����" width="80" />
						<!--<ec:column property="update" title="�޸�" width="40" sortable="false">
							<a href="term.do?method=update_step1&termId=${terms.termId}">�޸�</a>
						</ec:column>
						-->
					</ec:row>
				</ec:table>

			</div>