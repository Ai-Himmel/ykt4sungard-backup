<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="/tags/pager" prefix="pg" %>
<%@ taglib uri="/tags/struts-bean" prefix="bean" %>
<jsp:useBean id="currentPageNumber" type="java.lang.Integer" scope="request"/>
<pg:index export="total=itemCount">
<pg:first>
  <a href="<%= pageUrl %>"><nobr>[<bean:message key="page.first"/>]</nobr></a>
</pg:first>
<pg:skip pages="<%= -10 %>">
  <a href="<%= pageUrl %>"><nobr>[<bean:message key="page.uper"/>]</nobr></a>
</pg:skip>
<pg:prev>
  <a href="<%= pageUrl %>"><nobr>[<bean:message key="page.prev"/>]</nobr></a>
</pg:prev>
<pg:pages>
<% if (pageNumber == currentPageNumber) { %> 
[<%= pageNumber %>]
<% } else { %>
   <a href="<%= pageUrl %>"><%= pageNumber %></a> 
<% } %>
</pg:pages>
<pg:next>
  <a href="<%= pageUrl %>"><nobr>[<bean:message key="page.next"/>]</nobr></a>
</pg:next>
<pg:skip pages="<%= 10 %>">
  <a href="<%= pageUrl %>"><nobr>[<bean:message key="page.skip"/>]</nobr></a>
</pg:skip>
<pg:last>
  <a href="<%= pageUrl %>"><nobr>[<bean:message key="page.last"/>]</nobr></a>
</pg:last>
<pg:page export="first,last">
    <%= first %> - <%= last %> / <%= total %>
</pg:page>
</pg:index>