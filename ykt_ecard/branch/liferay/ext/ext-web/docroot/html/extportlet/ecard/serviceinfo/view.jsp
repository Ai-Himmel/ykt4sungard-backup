<%@ include file="/html/extportlet/ecard/serviceinfo/init.jsp"%>
<%
	ResultPage result = EcardInformationServiceUtil
			.list(EcardConstants.INFORMATION_SERVICEINFO_TYPE);
	EcardInformation info = (EcardInformation) result.getList().get(0);
%>
<table width="80%" align="center" border="0" cellspacing="0"
	cellpadding="0">
	<tr>
		<td valign="top" align="center">
			<!-- content table -->
			<table width="100%" align="center" border="0" cellspacing="0"
				cellpadding="0">

				<tr>
					<td align="center" valign="baseline">
						<%=info.getInfoTitle() == null ? "" : info
					.getInfoTitle()%>
					</td>

				</tr>
			</table>

			<table width="100%" align="center" height="5" border="0"
				cellpadding="0" cellspacing="0">
				<tr>
					<td></td>
				</tr>
			</table>
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td valign="top" align="center">
						<%=info.getInfoContent() == null ? "" : info
					.getInfoContent()%>
					</td>
				</tr>
			</table>
			<!-- content table -->
		</td>
	</tr>
</table>