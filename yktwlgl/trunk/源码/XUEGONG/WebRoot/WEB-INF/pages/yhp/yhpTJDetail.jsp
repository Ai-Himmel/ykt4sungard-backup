<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
	<head>
		<title>�Ϻ�������ѧ���Ͽ�漰�ִ�����ϵͳ</title>

		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<br>
		<html:form action="/gyf/yhpAction.do?method=load4Detail" method="post">

			<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
				<tr>
					<td align="left" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td height="25" align="left" valign="top">
									<table width="170" height="20" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="10" bgcolor="#0066CA">
												&nbsp;
											</td>
											<td bgcolor="#0066CA" class="mediumwhite">
												�׺�Ʒͳ����ϸ
											</td>
											<td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg" />" width="27" height="20"></td>
										</tr>
									</table>
								</td>
							</tr>
							</html:form>
							<logic:present name="yhplist" scope="request">

								<tr>
									<td height="35" align="center" valign="middle" class="mediumblack">
										�׺�Ʒͳ����ϸ
									</td>
								</tr>
								<tr>
									<td height="20" align="center" valign="middle">

										<ec:table items="yhplist" var="tl" rowsDisplayed="10" autoIncludeParameters="false" action="yhpAction.do?method=load4Detail">
											<ec:parameter name="wlid"></ec:parameter>
											<ec:parameter name="room"></ec:parameter>
											<ec:parameter name="building"></ec:parameter>
											<ec:parameter name="area"></ec:parameter>
											<ec:parameter name="pfdx"></ec:parameter>

											<ec:parameter name="search_wlmc"></ec:parameter>
											<ec:parameter name="search_xq"></ec:parameter>
											<ec:parameter name="search_louyu"></ec:parameter>
											<ec:parameter name="search_jfkf"></ec:parameter>
											<ec:parameter name="search_sccj"></ec:parameter>


											<ec:row>
												<ec:column property="id" title="�׺�Ʒ����" headerClass="tableHeader">
													<a href="javascript:DoView('<c:out value="${tl.id}"/>')"><c:out value="${tl.id}" /></a>&nbsp;
				</ec:column>
												<ec:column property="wlmc" title="�׺�Ʒ����" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="usageCategoryName" title="��;" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="beginNo" title="��ʼ���" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="endNo" title="�������" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="yhpNum" title="��������" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="lymc" title="¥��" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="roommc" title="����" headerStyle="text-align:center" style="text-align: center" />
												<ec:column property="curNum" title="��ǰ����" headerStyle="text-align:center" style="text-align: center" />

												<ec:column property="sccjName" title="������" headerStyle="text-align:center" style="text-align: center" />

												<%if (request.getAttribute("ifLimit").equals("0")) {%>
												<ec:column property="procurePrice" title="�ɹ���" headerStyle="text-align:center" style="text-align: center" />
												<%}%>
											</ec:row>
										</ec:table>
									</td>
								</tr>
							</logic:present>
						</table>
					</td>
				</tr>
				<tr>
					<td height="40" align="right" valign="middle">

						<input name="Submit3" type="button" class="button_nor" value="�� ��" onClick="DoBack()">
					</td>
				</tr>
			</table>
	</body>
</html>

<SCRIPT language=javascript>

function DoView(eno){

    window.open("yhpAction.do?method=load4view&yhpNo="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function DoBack(){
	ec.action = "<c:url value="/gyf/yhpAction.do"/>?method=tongji4YhpKucun";
	ec.submit();
}

</SCRIPT>

