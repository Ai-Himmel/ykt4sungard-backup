
<%@page import="com.liferay.util.servlet.SessionErrors"%>
<%@page import="com.kingstargroup.ecard.util.EcardConstants"%>

<%if(null==request.getAttribute("stuempno")||"".equals(request.getAttribute("stuempno").toString())) {%>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.INFO_NOT_ENOUGH_CUSTOMER) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="ecard.info.not.enough.customer"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.INFO_NOT_ENOUGH_STUEMPNO) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="ecard.info.not.enough.stuempno"  />
 </font>
</c:if>
<c:if test="<%= SessionErrors.contains(request,EcardConstants.INFO_NOT_ENOUGH_IDCARD) %>">
<font class="portlet-msg-error">
    <liferay-ui:message key="ecard.info.not.enough.idcard"  />
 </font>
</c:if>

<%return;}%>