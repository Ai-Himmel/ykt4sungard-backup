<%@ include file="init.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<TITLE><bean:message key="system.name" /></TITLE>
<tiles:useAttribute id="tilesHead" name="head"
	classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesSubnav" name="subnav"
	classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesContent" name="content"
	classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesBottom" name="bottom"
	classname="java.lang.String" ignore="true" />
<jsp:include page="<%= tilesHead %>" flush="true" />
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td width="138"> 
      	<iframe name="subnavframe" src="<%= ContextUtil.getCtxPath(request)%><%= tilesSubnav%>" width="138"  height="495" frameborder="0"></iframe>
    </td>
    <td>
    	<iframe name="dataframe" src="<%= ContextUtil.getCtxPath(request)%><%= tilesContent%>" width="100%"  height="495" frameborder="0"></iframe>
    </td>
  </tr>
</table>

<jsp:include page="<%= tilesBottom%>" flush="true" />