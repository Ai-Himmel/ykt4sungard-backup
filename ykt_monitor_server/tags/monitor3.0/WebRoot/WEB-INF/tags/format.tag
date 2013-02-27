<%@ tag import="org.apache.commons.lang.StringUtils" %>
<%@ tag import="org.king.utils.Contants" %>
<%@ tag import="java.text.Format" %>
<%@ tag import="java.text.MessageFormat" %>
<%@ tag pageEncoding="UTF-8" %>
<%--
 author: Allen

 用法：
 1、在jsp页面中引入taglib
    <%@ taglib prefix="sys" tagdir="/WEB-INF/tags" %>
 2、在需要系统代码的地方使用如下代码：
    <sys:format>20100729140623</sys:format>
--%>

<%@ attribute name="defaultValue" type="java.lang.String" required="false" description="默认值" %>
<%@ attribute name="pattern" type="java.lang.String" required="false" description="转换规则，默认为{0}-{1}-{2} {3}:{4}:{5}" %>
<jsp:doBody scope="request" var="_value"/>
<%
    String result;
    Format dateFormat = Contants.DATE_FORMAT;
    String value = (String) request.getAttribute("_value");
    if (StringUtils.isNotBlank(pattern)) {
        dateFormat = new MessageFormat(pattern);
    }
    if (StringUtils.isNotBlank(value)) {
        Object[] array = {value.substring(0, 4), value.substring(4, 6), value.substring(6, 8), value.substring(8, 10), value.substring(10, 12), value.substring(12, 14)};
        result = dateFormat.format(array);
    } else {
        if (defaultValue != null) {
            result = defaultValue;
        } else {
            result = "";
        }
    }
%>
<%=result%>
