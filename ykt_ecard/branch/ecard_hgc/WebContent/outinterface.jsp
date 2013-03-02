<%@ page language="java" import="com.sungard.cas.client.CasFilterValidStatus" %>
<%@ page pageEncoding="UTF-8" %>

<table border="0" cellpadding="0" cellspacing="0" width="95%">
    <tr>
        <td valign="top">
            <%
                //String websiteRealURL = "http://192.168.146.128:8080" + "/c/portal/layout"; //ykt website real http path
                String websiteRealURL = "http://10.253.42.116:8082" + "/entry.jsp"; //ykt website real http path
                String websiteInitURL = "http://10.253.42.116:8082" + "/index.html";
                //String stuempNo = request.getParameter("stuempno");
                if (CasFilterValidStatus.isValid()) {
                    String url = "http://10.253.42.187:8899/cas/login?isLoginService=11&username=admin&password=kingstar&service=" + websiteRealURL;
                    response.sendRedirect(url);
                } else {
                    //displayString = "Server is crash";
                    response.sendRedirect(websiteInitURL);
                }
            %>
        </td>
    </tr>
</table>
