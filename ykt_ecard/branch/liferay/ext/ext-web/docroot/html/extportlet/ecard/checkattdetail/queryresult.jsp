<%@include file="/html/extcommon/init.jsp" %>
<%@page import="com.liferay.portal.kernel.language.LanguageUtil"%>
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>
<%@ taglib uri="http://displaytag.sf.net" prefix="display" %>
<%@page import="com.liferay.util.servlet.SessionErrors"%>
<link href="/html/extcommon/styles/displaytag/alternative.css" rel="stylesheet" type="text/css" />

<%@page pageEncoding="GBK"%>
<%@page import="java.util.List"%>
<portlet:defineObjects />
<c:if test='<%=request.getAttribute("result") != null%>'>
		<%
			List result = (List) request.getAttribute("result");
		%>
	<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr>
			<td>
				<display:table name="result" pagesize="100" class="isis"
					style="width:100%" requestURI="/ext/ecardtransactionquerydetail_result"
					export="false" >
					<display:column property="devid" 
						title="�豸���">
					</display:column>
					<display:column property="devname"
						title="�豸����">
					</display:column>
					<display:column property="attdate"
						title="��������">
					</display:column>
					<display:column property="atttime"
						title="����ʱ��">
					</display:column>
				</display:table>


			</td>
		</tr>
	</table>
</c:if>
