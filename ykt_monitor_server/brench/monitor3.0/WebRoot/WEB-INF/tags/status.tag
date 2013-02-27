<%@ tag import="org.apache.commons.lang.StringUtils" %>
<%@ tag import="org.king.utils.Contants" %>
<%@ tag pageEncoding="UTF-8" %>
<%--
 author: Allen

 用法：
 1、在jsp页面中引入taglib
    <%@ taglib prefix="sys" tagdir="/WEB-INF/tags" %>
 2、在需要系统代码的地方使用如下代码：
    <sys:status type="5" >1</sys:status>
--%>

<%@ attribute name="defaultValue" type="java.lang.String" required="false" description="状态默认值" %>
<%@ attribute name="type" type="java.lang.String" required="true" description="状态类型，目前支持1,2,3,4,5,6" %>
<jsp:doBody scope="request" var="_value"/>
<%
    String value = (String) request.getAttribute("_value");
    String status = null;
    int t = Integer.parseInt(type);
    if (StringUtils.isNotBlank(type)) {
        switch (t) {
            case 1:
                status = (String) Contants.HOST_STATUS.get(value);
                System.out.println("value = " + value);
                break;
            case 2:
                status = (String) Contants.SERVICE_STATUS.get(value);
                break;
            case 3:
                status = (String) Contants.TERMDEVICE_STATUS.get(value);
                break;
            case 4:
                status = (String) Contants.TERMDEVSERVICE_STATUS.get(value);
                break;
            case 5:
                status = (String) Contants.YES_NO_STATUS.get(value);
                break;
            case 6:
                status = (String)Contants.HOST_TYPE.get(value);
                break;
            default:
                status = value;
        }
    }
    if (status == null) {
        if (StringUtils.isNotEmpty(defaultValue)) {
            status = defaultValue;
        } else {
            status = "";
        }
    }
%>
<%=status%>
