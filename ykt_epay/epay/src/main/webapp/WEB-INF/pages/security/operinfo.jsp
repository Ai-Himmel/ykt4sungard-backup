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
<div id="breadcrumbe"><span>当前位置：个人信息查看</span> </div>
<div class="content">	
        <table class="ProfileTable" >
            <tr>
                <td width="20%" class="list01">代码：</td>
                <td >
                    <bean:write name="operator" property="opercode"/>
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">姓名：</td>
                <td >
                    <bean:write name="operator" property="opername"/>
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">电话：</td>
                <td >
                    <bean:write name="operator" property="tel"/>
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">手机：</td>
                <td >
                    <bean:write name="operator" property="mobile"/>
                </td>
            </tr>
             <tr>
                <td width="20%" class="list01">电子邮箱：</td>
                <td >
                   <bean:write name="operator" property="email"/>
                </td>
            </tr>
           
        </table>
    </div>
</div>
</body>

</html>
