<%@include file="/html/common/init.jsp" %>
<%@page import="com.liferay.portal.kernel.language.LanguageUtil"%>
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>
<%@ taglib uri="http://displaytag.sf.net" prefix="display" %>
<%@page import="com.liferay.util.servlet.SessionErrors"%>
<link href="/html/extcommon/styles/displaytag/alternative.css" rel="stylesheet" type="text/css" />

<%@page pageEncoding="GBK"%>
<%@page import="java.util.List"%>
<portlet:defineObjects />
<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.LOSECARD_DATAFORMATERROR)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.LOSECARD_DATAFORMATERROR, SessionErrors.get(
										request, EcardConstants.LOSECARD_DATAFORMATERROR))%> </font>
</c:if>
<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.LOSECARD_DATACOMERROR)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.LOSECARD_DATACOMERROR, SessionErrors.get(
										request, EcardConstants.LOSECARD_DATACOMERROR))%> </font>
</c:if>

<jsp:include page="stat.jsp"></jsp:include>
<c:if test='<%=request.getAttribute("result") != null%>'>
		<%
			List result = (List) request.getAttribute("result");
		%>
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
				<display:table name="result" pagesize="10" class="isis"
					style="width:100%" requestURI="/ext/losecardstatresult"
					export="false" >
					<display:column property="shopcode" 
						title="商户登录号">
					</display:column>
					<display:column property="totnum"
						title="总登记数">
					</display:column>
					<display:column property="getnum"
						title="已领取数">
					</display:column>
					<display:column property="notgetnum"
						title="未领取数">
					</display:column>
					<display:column property="destorynum"
						title="作废数">
					</display:column>
				</display:table>


			</td>
		</tr>
	</table>
</c:if>
