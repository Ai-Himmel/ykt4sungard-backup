<%@page import="com.liferay.portal.util.PortalUtil"%>
<%@page import="com.liferay.util.servlet.SessionErrors"%>
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>

<%if(null==PortalUtil.getUserId(request)||"".equals(PortalUtil.getUserId(request))) {%>
<font class="portlet-msg-error" style="font-size: 13;">
	<bean:message key="ecard.error.shouldlogin" />
	</font>
<%return;}%>