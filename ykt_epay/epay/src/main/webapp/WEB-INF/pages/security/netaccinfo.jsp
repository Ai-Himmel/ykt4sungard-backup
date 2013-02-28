<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<%@ taglib prefix="sys" tagdir="/WEB-INF/tags" %>
<html>
<head>
    <title>支付平台</title>
    <meta http-equiv="Content-Type" content="text/html;">
    <link rel="stylesheet" type="text/css" href="<c:url value="/theme/style/epay/css.css"/>"/>
    <script type="text/javascript" src="<c:url value='/theme/scripts/jquery-1.4.2.min.js'/>" ></script>
    <script language="JavaScript">
    	function setstoppay(flag,accno){
    		if(confirm("确定此操作?")){
		      $.ajax({
				   type: "POST",
				   url: 'accountManager.do?method=setstoppay',
				   //data: "class_id="+id+"&gspydybzt="+gspydybzt,
				   data:{'flag':flag,'accno':accno},
				   //dataType:'json',
				   //error:function(ajax,e){alert(e);},
				   success: function(msg){
				   	if(msg=='1'){
				   		alert('操作成功!');
				   		location.href='getLoginNetAcc.do?method=getLoginNetAcc';
				   	}else{
				   		alert('操作失败!');
				   	}
				   }
				});
		    }
    	}
    </script>
</head>
<body>
	<div id="breadcrumbe"><span>当前位置：网络账户信息</span> </div>
    <div class="content">
        <table  class="ProfileTable" >
            <tr>
                <td width="20%" class="list01">账号：</td>
                <td >
                    <bean:write name="tNetacc" property="accno"/>
                </td>
            </tr>
             <tr>
                <td class="list01">账户名：</td>
                <td >
                    <bean:write name="tNetacc" property="accname"/>
                </td>
            </tr>
            <tr>
                <td class="list01">客户号：</td>
                <td >
                    <bean:write name="tNetacc" property="custid"/>
                </td>
            </tr>
             <tr>
                <td class="list01">止付标志：</td>
                <td >
                    <sys:status type="1" defaultValue=""><bean:write name="tNetacc" property="stoppayflag"/></sys:status>
                	<c:if test="${tNetacc.stoppayflag=='1'}">
                		<input name="setpayflag" type="button" value="解 付" onclick="setstoppay('0','<bean:write name="tNetacc" property="accno"/>')"/>
                	</c:if>
                	<c:if test="${tNetacc.stoppayflag=='0'}">
                		<input name="setpayflag" type="button" value="止 付" onclick="setstoppay('1','<bean:write name="tNetacc" property="accno"/>')"/>
                	</c:if>
                </td>
            </tr>
             <tr>
                <td class="list01">状态：</td>
                <td >
                    <sys:status type="2" defaultValue=""><bean:write name="tNetacc" property="status"/></sys:status>
                </td>
            </tr>
            <tr>
                <td class="list01">账户余额：</td>
                <td >
                    <bean:write name="tNetacc" property="balance" format="0.00"/> 元
                </td>
            </tr>
            <tr>
                <td class="list01">上次交易日期：</td>
                <td >
                    <sys:format><bean:write name="tNetacc" property="lasttransdate"/></sys:format>
                </td>
            </tr>
             <tr>
                <td class="list01">开户日期：</td>
                <td >
                    <sys:format><bean:write name="tNetacc" property="opendate"/></sys:format>
                </td>
            </tr>
             <tr>
                <td class="list01">最后登陆时间：</td>
                <td >
                    <sys:format><bean:write name="tNetacc" property="lastlogintime"/></sys:format>
                </td>
            </tr>
        </table>
    </div>
</body>

</html>
