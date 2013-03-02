
<%if(null==request.getAttribute("stuempno")||"".equals(request.getAttribute("stuempno").toString())) {%>
<font class="portlet-msg-error">
    <liferay-ui:message key="ecard.info.not.enough.stuempno"  />
 </font>

<%return;}%>