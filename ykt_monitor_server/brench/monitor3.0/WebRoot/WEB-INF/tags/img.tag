<%@ tag import="java.text.DecimalFormat" %>
<%@ tag pageEncoding="UTF-8" %>
<%@ taglib uri="http://java.sun.com/jstl/core" prefix="c" %>
<%--
 author: Allen

 用法：
 1、在jsp页面中引入taglib
    <%@ taglib prefix="sys" tagdir="/WEB-INF/tags" %>
 2、在需要系统代码的地方使用如下代码：
    <sys:img total="5" normal="1" >1</sys:img>
--%>

<%@ attribute name="total" type="java.lang.String" required="true" description="总数" %>
<%@ attribute name="unusual" type="java.lang.String" required="true" description="异常个数" %>
<%
    double totalNum = Double.parseDouble(total);
    double unusualNum = Double.parseDouble(unusual);
    double persent = (totalNum-unusualNum)/totalNum;
    double normalNum = totalNum-unusualNum;
    int width = new Double((normalNum/totalNum)*100).intValue();
    request.setAttribute("persent",persent);
    DecimalFormat decimalFormat = new DecimalFormat("##.00%");
    String title = decimalFormat.format(normalNum/totalNum)+" Health";
%>
<td valign="bottom" width="100" class="healthBar" style="padding:0;">
<c:choose>
    <c:when test="${totalNum!=0 and persent>=0.8}">
        <img height="20" border="0" width="<%=width%>" title="<%=title%>" alt="<%=title%>" src="<c:url value="/pages/style/default/images/thermok.png"/>"></td>
    </c:when>
    <c:when test="${totalNum!=0 and persent>=0.6 and persent<0.8}">
        <img height="20" border="0" width="<%=width%>" title="<%=title%>" alt="<%=title%>" src="<c:url value="/pages/style/default/images/thermwarn.png"/>"></td>
    </c:when>
    <c:when test="${totalNum!=0 and persent<0.6}">
        <img height="20" border="0" width="<%=width%>" title="<%=title%>" alt="<%=title%>" src="<c:url value="/pages/style/default/images/thermcrit.png"/>"></td>
    </c:when>
    <c:otherwise>
        <img height="20" border="0" width="0" src=""></td>        
    </c:otherwise>
</c:choose>