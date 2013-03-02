<%@page import="com.kingstargroup.advquery.util.GetPropertiesUtil"%>
<%@page import="org.apache.commons.configuration.PropertiesConfiguration"%>
<%
PropertiesConfiguration configs = GetPropertiesUtil.getInstance();
String ip = configs.getString("directpath");
//222.66.165.27:8097,10.14.158.96
String param = request.getQueryString();
response.sendRedirect("http://"+ip+"/SAFF.Organization.Web/Utils/ObjectsSelector.aspx?"+param);
%>
