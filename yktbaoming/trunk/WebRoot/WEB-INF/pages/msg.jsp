<%@ include file="tiles/include.jsp"%>

<bean:define id="title">
<bean:message bundle="security" key="msg.title"/>
</bean:define>
<center>
<gui:window title="<%=title%>" prototype="boWindow" color="80%">
<html:errors/>
</gui:window>
</center>
