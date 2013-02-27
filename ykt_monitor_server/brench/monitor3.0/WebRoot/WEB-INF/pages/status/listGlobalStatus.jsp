<%@page pageEncoding="UTF-8" %>
<jsp:useBean id="now" class="java.util.Date" />
<%@ include file="../tiles/include.jsp" %>
<%@ taglib prefix="sys" tagdir="/WEB-INF/tags" %>
<html>
<head>
    <title>监控系统</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/pages/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
    <script type="text/javascript">
        function flushCallback(pe){
            window.location.reload();
            pe.stop();
        }
        function initTimer(){
            new PeriodicalExecuter(flushCallback,60);
        }
        window.onload = function(){
            initTimer();
        }
    </script>
</head>
<body>
<div style="width:100%;margin:8px 8px 0 10">
    <table width="100%" cellpadding="0" cellspacing="0" style="border:0" >
        <tr align="left">
            <td width="30%" align="left">
                <table class="search" style="border:0">
                    <tr class="toptitle">
                        <td width="100%">
                           一卡通运行情况
                        </td>
                    </tr>
                    <tr class="toptitle1">
                        <td width="100%" height="86" style="text-align:left;">
                            最新更新：<fmt:setLocale value="en"/><fmt:formatDate value="${now}" type="both" dateStyle="long" pattern="EEE yyyy-MM-dd HH:mm:ss" /> <br/>
                            更新间隔：60 秒 <br/>
                            &nbsp;
                        </td>
                    </tr>
                </table>
            </td>
            <td width="20%" align="left">
                <table class="search" style="border:0;width:90%">
                    <tr class="toptitle">
                        <td width="100%">
                           整体健康状况
                        </td>
                    </tr>
                    <tr class="toptitle1">
                        <td width="100%" height="60" style="text-align:left;">
                            <table cellspacing="0" border="0" cellspadding="0" >
                                <tbody>
                                <tr>
                                    <td class="healthBox">
                                        <table cellspacing="4" border="0" cellspadding="0">
                                            <tbody>
                                            <tr >
                                                <td valign="center" align="left" class="healthItem" style="padding:0;">主机 &nbsp;&nbsp;</td>
                                                <sys:img total='<%=((String[][])request.getAttribute("totalStatusResult"))[0][0]%>' unusual='<%=((String[][])request.getAttribute("totalStatusResult"))[0][1]%>' />
                                            </tr>
                                            <tr >
                                                <td valign="center" align="left" class="healthItem" style="padding:0;">服务&nbsp;&nbsp;</td>
                                                <sys:img total='<%=((String[][])request.getAttribute("totalStatusResult"))[1][0]%>' unusual='<%=((String[][])request.getAttribute("totalStatusResult"))[1][1]%>' />
                                            </tr>
                                            <tr >
                                                <td valign="center" align="left" class="healthItem" style="padding:0;">设备&nbsp;&nbsp;</td>
                                                <sys:img total='<%=((String[][])request.getAttribute("totalStatusResult"))[2][0]%>' unusual='<%=((String[][])request.getAttribute("totalStatusResult"))[2][1]%>' />
                                            </tr>
                                            </tbody>
                                        </table>
                                    </td>
                                </tr>
                                </tbody>
                            </table>
                        </td>
                    </tr>
                </table>
            </td>
            <td width="50%"></td>
        </tr>
    </table>
    <br/>
    <table width="100%" cellpadding="0" cellspacing="0" style="border:0" >
        <tr align="left">
            <td width="30%" align="left">
                <table class="search" style="border:0">
                    <tr class="toptitle">
                        <td width="100%" colspan="3">
                          	<a href="calcuVML.do?method=test"> 监控执行情况总体概览</a>
                        </td>
                    </tr>
                    <tr class="toptitle1">
                        <td width="60%" style="text-align:left;">监控主机（异常）</td>
                        <td style="text-align:left;">
                            <c:out value="${totalStatusResult[0][0]}" />
                            <c:choose>
                                <c:when test="${totalStatusResult[0][1]=='0'}">(&nbsp;<c:out value="${totalStatusResult[0][1]}" />&nbsp;)</c:when>
                                <c:otherwise>(&nbsp;<font color="red"><c:out value="${totalStatusResult[0][1]}" /></font>&nbsp;)</c:otherwise>
                            </c:choose>
                        </td>
                    </tr>
                    <tr class="toptitle1">
                        <td width="60%" style="text-align:left;">监控服务（异常）</td>
                        <td style="text-align:left;">
                            <c:out value="${totalStatusResult[1][0]}" />
                            <c:choose>
                                <c:when test="${totalStatusResult[1][1]=='0'}">(&nbsp;<c:out value="${totalStatusResult[1][1]}" />&nbsp;)</c:when>
                                <c:otherwise>(&nbsp;<font color="red"><c:out value="${totalStatusResult[1][1]}" /></font>&nbsp;)</c:otherwise>
                            </c:choose>
                        </td>
                    </tr>
                    <tr class="toptitle1">
                        <td width="60%" style="text-align:left;">监控设备（异常）</td>
                        <td style="text-align:left;">
                            <c:out value="${totalStatusResult[2][0]}" />
                            <c:choose>
                                <c:when test="${totalStatusResult[2][1]=='0'}">(&nbsp;<c:out value="${totalStatusResult[2][1]}" />&nbsp;)</c:when>
                                <c:otherwise>(&nbsp;<font color="red"><c:out value="${totalStatusResult[2][1]}" /></font>&nbsp;)</c:otherwise>
                            </c:choose>
                        </td>
                    </tr>
                </table>
            </td>
            <td width="20%" align="center">
                <table class="search" style="border:0;width:90%">
                    <tr class="toptitle">
                        <td width="100%" colspan="3">
                           整体业务情况
                        </td>
                    </tr>
                    <tr class="toptitle1">
                        <td width="60%" style="text-align:left;">系统流水总比数</td>
                        <td style="text-align:left;">34000</td>
                    </tr>
                    <tr class="toptitle1">
                        <td width="60%" style="text-align:left;">前台业务比数</td>
                        <td style="text-align:left;">1300</td>
                    </tr>
                    <tr class="toptitle1">
                        <td width="60%" style="text-align:left;">系统最高并发</td>
                        <td style="text-align:left;">450</td>
                    </tr>
                </table>
            </td>
            <td width="50%"></td>
        </tr>
    </table>
    <br/>
    <table class="search" align="left" style="width:40%">
        <tr class="toptitle"><td colspan="4" style="text-align:left"><a href="hostStatus.do?method=listMonitorHostStatus">主机</a></td></tr>
        <tr class="toptitle0">
            <c:forEach var="count" items="${hostStatusResult}">
                <td width="25%"><c:out value="${count[0]}"></c:out></td>
            </c:forEach>
        </tr>
        <tr class="toptitle1">
            <c:forEach var="count" items="${hostStatusResult}" varStatus="status">
                <c:choose>
                    <c:when test="${count[1]=='0'}">
                        <td>
                            <c:out value="${count[1]}"></c:out>
                        </td>
                    </c:when>
                    <c:when test="${count[0]=='down'}">
                        <td bgcolor="#FE3E00">
                            <a href="hostStatus.do?method=listMonitorHostStatus&currentState=<c:out value="${status.index}"/>">
                                <c:out value="${count[1]}"></c:out>
                            </a>
                        </td>
                    </c:when>
                    <c:when test="${count[0]=='unreachable'}">
                        <td bgcolor="#F9A810">
                            <a href="hostStatus.do?method=listMonitorHostStatus&currentState=<c:out value="${status.index}"/>">
                                <c:out value="${count[1]}"></c:out>
                            </a>
                        </td>
                    </c:when>
                    <c:otherwise>
                        <td>
                            <a href="hostStatus.do?method=listMonitorHostStatus&currentState=<c:out value="${status.index}"/>">
                                <c:out value="${count[1]}"></c:out>
                            </a>
                        </td>
                    </c:otherwise>
                </c:choose>
            </c:forEach>
        </tr>
    </table>
    <br/>
    <br/>
    <br/>
    <br/>
    <br/>
    <br/>
    <table class="search" align="left" style="width:50%">
        <tr class="toptitle"><td colspan="4" style="text-align:left"><a href="serviceStatus.do?method=listMonitorServiceStatus">服务</a></td></tr>
        <tr class="toptitle0">
            <c:forEach var="count" items="${serviceStatusResult}">
                <td width="20%"><c:out value="${count[0]}"></c:out></td>
            </c:forEach>
        </tr>
        <tr class="toptitle1">
            <c:forEach var="count" items="${serviceStatusResult}" varStatus="status">
                <c:choose>
                    <c:when test="${count[1]=='0'}">
                        <td>
                            <c:out value="${count[1]}"></c:out>
                        </td>
                    </c:when>
                    <c:when test="${count[0]=='critical'}">
                        <td bgcolor="#FE3E00">
                            <a href="serviceStatus.do?method=listMonitorServiceStatus&currentState=<c:out value="${status.index}"/>">
                                <c:out value="${count[1]}"></c:out>
                            </a>
                        </td>
                    </c:when>
                    <c:when test="${count[0]=='warning'}">
                        <td bgcolor="#F9A810">
                            <a href="serviceStatus.do?method=listMonitorServiceStatus&currentState=<c:out value="${status.index}"/>">
                                <c:out value="${count[1]}"></c:out>
                            </a>
                        </td>
                    </c:when>
                    <c:when test="${count[0]=='unknow'}">
                        <td bgcolor="#B1C9D3">
                            <a href="serviceStatus.do?method=listMonitorServiceStatus&currentState=<c:out value="${status.index}"/>">
                                <c:out value="${count[1]}"></c:out>
                            </a>
                        </td>
                    </c:when>
                    <c:otherwise>
                        <td>
                            <a href="serviceStatus.do?method=listMonitorServiceStatus&currentState=<c:out value="${status.index}"/>">
                                <c:out value="${count[1]}"></c:out>
                            </a>
                        </td>
                    </c:otherwise>
                </c:choose>
            </c:forEach>
        </tr>
    </table>
     <br/>
    <br/>
    <br/>
     <br/>
    <br/>
    <br/>
    <table class="search"  align="left" style="width:30%">
        <tr class="toptitle"><td colspan="4" style="text-align:left"><a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus">设备</a></td></tr>
        <tr class="toptitle0">
            <c:forEach var="count" items="${termdeviceStatusResult}">
                <td width="33.3%"><c:out value="${count[0]}"></c:out></td>
            </c:forEach>
        </tr>
        <tr class="toptitle1">
            <c:forEach var="count" items="${termdeviceStatusResult}" varStatus="status">
                <c:choose>
                    <c:when test="${count[1]=='0'}">
                        <td>
                            <c:out value="${count[1]}"></c:out>
                        </td>
                    </c:when>
                    <c:when test="${count[0]=='down'}">
                        <td bgcolor="#FE3E00">
                            <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&currentState=<c:out value="${status.index}"/>">
                                <c:out value="${count[1]}"></c:out>
                            </a>
                        </td>
                    </c:when>
                    <c:when test="${count[0]=='unreachable'}">
                        <td bgcolor="#F9A810">
                            <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&currentState=<c:out value="${status.index}"/>">
                                <c:out value="${count[1]}"></c:out>
                            </a>
                        </td>
                    </c:when>
                    <c:otherwise>
                        <td>
                            <a href="termdeviceStatus.do?method=listMonitorTermdeviceStatus&currentState=<c:out value="${status.index}"/>">
                                <c:out value="${count[1]}"></c:out>
                            </a>
                        </td>
                    </c:otherwise>
                </c:choose>
            </c:forEach>
        </tr>
    </table>
</div>    
</body>
</html>
