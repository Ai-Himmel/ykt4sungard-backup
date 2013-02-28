<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<%@ taglib prefix="sys" tagdir="/WEB-INF/tags" %>
<html>
<head>
    <title>支付平台</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/theme/style/epay/css.css"/>" type="text/css" rel=stylesheet>
</head>
<body>
<div id="breadcrumbe"><span>当前位置：商户账户信息</span> </div>
<div class="content">	
        <table class="ProfileTable" >
            <tr>
                <td width="20%" class="list01">账号：</td>
                <td >
                    <bean:write name="tShopacc" property="accno"/>
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">商户号：</td>
                <td >
                    <bean:write name="tShopacc" property="shopid"/>
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">账户名：</td>
                <td >
                    <bean:write name="tShopacc" property="accname"/>
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">科目名：</td>
                <td >
                    <bean:write name="tShopacc" property="subjno"/>
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">状态：</td>
                <td >
                    <sys:status type="3" defaultValue=""><bean:write name="tShopacc" property="status"/></sys:status>
                </td>
            </tr>
            <tr>
                <td width="20%" class="list01">账户余额：</td>
                <td >
                    <bean:write name="tShopacc" property="balance" format="0.00"/> 元
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">上次交易日期：</td>
                <td >
                    <sys:format><bean:write name="tShopacc" property="lasttransdate"/></sys:format>
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">上次清算日期：</td>
                <td >
                    <sys:format><bean:write name="tShopacc" property="lastaccdate"/></sys:format>
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">开户日期：</td>
                <td >
                    <sys:format><bean:write name="tShopacc" property="opendate"/></sys:format>
                </td>
            </tr>
        </table>
    </div>
</div>
</body>

</html>
