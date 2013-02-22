<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="/tags/struts-bean" prefix="bean" %>
<%@ taglib uri="/tags/struts-html" prefix="html" %>
<%@ taglib uri="/tags/struts-logic" prefix="logic" %>
<%@ page import="com.pow2.util.Util" %>
<%@ taglib uri="/tags/pow2webgui" prefix="gui" %> 


<center>
<bean:define id="title">
<bean:message key="errorDef.title"/>
</bean:define>

<gui:window title="<%=title%>" prototype="boWindow" color="100%">
  <table class="win" CELLPADDING="0" CELLSPACING="0" WIDTH="300">
    <tr><td><html:errors/>&nbsp;</td>
    </tr>
  </table>
</gui:window>
</center>