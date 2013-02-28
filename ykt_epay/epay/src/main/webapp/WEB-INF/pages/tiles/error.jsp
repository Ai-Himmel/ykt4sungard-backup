<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://struts.apache.org/tags-bean" prefix="bean" %>
<%@ taglib uri="http://struts.apache.org/tags-html" prefix="html" %>
<%@ taglib uri="http://struts.apache.org/tags-logic" prefix="logic" %>

<center>
<bean:define id="title">
<bean:message key="errorDef.title"/>
</bean:define>
  <table class="win" CELLPADDING="0" CELLSPACING="0" WIDTH="300">
    <tr><td><html:errors/>&nbsp;</td>
    </tr>
  </table>
</center>