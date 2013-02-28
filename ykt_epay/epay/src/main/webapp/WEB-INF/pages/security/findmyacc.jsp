<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<%@ taglib prefix="sys" tagdir="/WEB-INF/tags" %>
<html>
<head>
<%
String emflag = "";
if(request.getAttribute("emflag")!=null)
	emflag = (String)request.getAttribute("emflag");
 %>
    <title>支付平台</title>
    <meta http-equiv="Content-Type" content="text/html;">

     <link rel="stylesheet" type="text/css" href="<c:url value="/theme/style/epay/css.css"/>"/>
    <link href="<c:url value="/theme/style/default/info.css"/>" type="text/css" rel=stylesheet>
    <script src="<c:url value="/theme/scripts/jquery.js"/>"	type="text/javascript"></script>
	<script src="<c:url value="/theme/scripts/jquery.validate.js"/>"	type="text/javascript"></script>
    <script type="text/javascript">
        $().ready(function() {
	// validate signup form on keyup and submit
		$("#activateform").validate({
			rules: {
				xh: "required",
				checkcode: "required"
			},
			messages: {
				xh: "请输入您的学号!",
				checkcode: "请输入验证码!"
			}
		});
	});
    </script>
    <style type="text/css">
	#activateform label.error {
		margin-left: 10px;
		width: auto;
		display: inline;
		color: red;
	}
</style>
</head>
<body>
<div id="breadcrumbe"></div>
    <div class="content">
<form id="activateform" action="activateAction.do?method=findacc" method="post">
        <html:errors />
        <table class="ProfileTable" >
            <tr class="toptitle">
                <td colspan="4" style="text-align:center;"><p style="font-weight:bold;"><font size="4">找回账号</font></p></td>
            </tr>
            <tr>
                <td  class="list01">学号：</td>
                <td>
                    <font color="#ff0000">*</font><input type="text" name="xh" id="xh" value="${xh}" class="input_box" maxlength="15">
                </td>
                <%if(emflag!=null&&"1".equals(emflag)) {%>
                 <td class="list01">
                 	姓名:
                </td>
                <td align="left">
                 	<%=(String)request.getAttribute("accname") %>
                </td>
                <%} %>
            </tr>
            <tr>
                <td  class="list01">卡密码：</td>
                <td >
                    <font color="#ff0000">*</font><input type="password" name="pwd" id="pwd" class="input_box" maxlength="10">
                </td>
                <%if(emflag!=null&&"1".equals(emflag)) {%>
                 <td class="list01">
                 	电子账号：
                </td>
                <td align="left">
                	<%=(String)request.getAttribute("netaccno") %>
                </td>
                <%} %>
                
            </tr>

            <tr>
                <td  class="list01">验证码：</td>
                <td >
                    <font color="#ff0000">*</font><input type="text" name="checkcode" id="checkcode" class="input_box">
                	<html:img page="/CheckCodeImage" align="absmiddle" style="border: 1 dotted black"
										width="52" height="20" />
                </td>
                <%if(emflag!=null&&"1".equals(emflag)) {%>
                 <td class="list01">
                 	状态：
                </td>
                <td align="left">
                	<%=(String)request.getAttribute("stutes") %>
                </td>
                <%} %>
            </tr>
            <tr class="toptitle">
                <td colspan="4"   style="text-align:center;">
                    &nbsp;&nbsp;
                    <input type="submit" class="button_nor" value=" 查找 "/>
                    <input type="reset" class="button_nor" value=" 重 置 " />
                </td>
            </tr>
        </table>
</form>
</div>
</div>

</body>

</html>
