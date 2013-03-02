
<%@ include file="/html/common/init.jsp" %>

<%@ page isErrorPage="true" %>

<%
String message = exception.getMessage();

if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_MESSAGE_LOG))) {
	_log.error(message);
}

if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_MESSAGE_PRINT))) {
	System.out.println(message);
}

String stackTrace = StringUtil.stackTrace(exception);

if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_STACK_TRACE_LOG))) {
	_log.error(stackTrace);
}

if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_STACK_TRACE_PRINT))) {
	System.out.println(stackTrace);
}
%>

<center>

<br>

<table border="0" cellpadding="0" cellspacing="0" width="95%">
<tr>
	<td>
		<font color="#FF0000" face="Verdana, Tahoma, Arial" size="2">
		<%= LanguageUtil.get(pageContext, "an-unexpected-system-error-occurred") %><br>
		</font>

		<%
		if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_MESSAGE_SHOW))) {
		%>

			<br>

			<font face="Verdana, Tahoma, Arial" size="2">
			<%= message %><br>
			</font>

		<%
		}

		if (GetterUtil.getBoolean(PropsUtil.get(PropsUtil.ERROR_STACK_TRACE_SHOW))) {
		%>

<pre>
<%= stackTrace %>
</pre>

		<%
		}
		%>

	</td>
</tr>
</table>

<br>

</center>

<%!
private static final Log _log = LogFactory.getLog("portal-web.docroot.html.common.error.jsp");
%>