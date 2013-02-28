<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>支付平台</title>
    <meta http-equiv="Content-Type" content="text/html;">

     <link rel="stylesheet" type="text/css" href="<c:url value="/theme/style/epay/css.css"/>"/>
    <link href="<c:url value="/theme/style/default/info.css"/>" type="text/css" rel=stylesheet>
    <script src="<c:url value="/theme/scripts/jquery.js"/>"	type="text/javascript"></script>
	<script src="<c:url value="/theme/scripts/jquery.validate.js"/>"	type="text/javascript"></script>
    <script type="text/javascript">
        $().ready(function() {
	// validate signup form on keyup and submit
			jQuery.validator.addMethod("password", function( value, element ) {
				var flag=0;
				if(this.optional(element) || /\d/.test(value)){
					flag=flag+1;
				}
				if(this.optional(element) || /[a-z]/.test(value)){
					flag=flag+1;
				}
				if(this.optional(element) || /[A-Z]/.test(value)){
					flag=flag+1;
				}
				return flag>2&&/^[A-Za-z0-9]+$/.test(value)&&value!=$("#account").val();
			}, "必须含有数字、大写字母、小写字母,不能包含特殊字符和汉字,不能与账号相同!");
			jQuery.validator.addMethod("equesacc", function( value, element ) {
				return value!=$("#account").val();
			}, "不能与账号相同!");
		$("#activateform").validate({
			rules: {
				account: "required",
				activatecode: "required",
				accpwd1: {
					required:true,
					minlength:6,
					maxlength:8,
					password:true,
					equesacc:true
				},
				accpwd2: {
					required:"true",
					equalTo: "#accpwd1"
				},
				paypwd1: {
					required:true,
					minlength:6,
					maxlength:8,
					password:true
				},
				paypwd2: {
					required:"true",
					equalTo: "#paypwd1"
				},
				checkcode: "required"
			},
			messages: {
				account: "请输入您的账号!",
				activatecode: "请输入您激活码!",
				accpwd1: {
					required:"请设置您的登录密码!",
					maxlength:"密码长度不能大于8个字符",
					minlength:"密码长度不能小于6个字符"
				},
				accpwd2: {
					required:"请再次输入您登录密码!",
					equalTo: "两次输入登录密码不一致!"
				},
				paypwd1: {
					required:"请设置您的登录密码!",
					maxlength:"密码长度不能大于8个字符",
					minlength:"密码长度不能小于6个字符"
				},
				paypwd2: {
					required:"请再次输入您的支付密码!",
					equalTo: "两次输入支付密码不一致!"
				},
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
<form id="activateform" action="activateAction.do?method=activate" method="post">
        <html:errors />
        <table class="ProfileTable" >
            <tr class="toptitle">
                <td colspan="3" style="text-align:center;"><p style="font-weight:bold;"><font size="4">激活账号</font></p></td>
            </tr>
            <tr>
                <td  class="list01">电子钱包账号：</td>
                <td>
                    <font color="#ff0000">*</font><input type="text" name="account" id="account" class="input_box" maxlength="15">
                </td>
                 <td >
                </td>
            </tr>
            <tr>
                <td  class="list01">激活码：</td>
                <td >
                    <font color="#ff0000">*</font><input type="text" name="activatecode" id="activatecode" class="input_box" maxlength="10">
                    
                </td>
                 <td >
                 	
                </td>
            </tr>
            <tr>
                <td  class="list01">请输入登录密码：</td>
                <td >
                    <font color="#ff0000">*</font><input type="password" name="accpwd1" id="accpwd1"  class="input_box" maxlength="9">
                    
                </td>
                 <td >
                 	
                 	
                </td>
            </tr>
            <tr>
                <td  class="list01">再次输入登录密码：</td>
                <td >
                    <font color="#ff0000">*</font><input type="password" name="accpwd2" id="accpwd2" class="input_box" maxlength="9">
                    
                </td>
                 <td >
                </td>
            </tr>
            <tr>
                <td  class="list01">请输入支付密码：</td>
                <td >
                    <font color="#ff0000">*</font><input type="password" name="paypwd1" id="paypwd1" class="input_box" maxlength="9">
                    
                </td>
                 <td >
                 	
                 	
                </td>
            </tr>
            <tr>
                <td  class="list01">再次输入支付密码：</td>
                <td >
                    <font color="#ff0000">*</font><input type="password" name="paypwd2" id="paypwd2" class="input_box" maxlength="9">
                </td>
                 <td >
                </td>
            </tr>
            <tr>
                <td  class="list01">验证码：</td>
                <td >
                    <font color="#ff0000">*</font><input type="text" name="checkcode" id="checkcode" class="input_box">
                	<html:img page="/CheckCodeImage" align="absmiddle" style="border: 1 dotted black"
										width="52" height="20" />
                </td>
                 <td >
                 	
                 	
                </td>
            </tr>
            <tr class="toptitle">
                <td colspan="3"   style="text-align:center;">
                    &nbsp;&nbsp;
                    <input type="submit" class="button_nor" value=" 保 存 "/>
                    <input type="reset" class="button_nor" value=" 重 置 " />
                    <a href="activateAction.do?method=findacc" target="_blank">找回账号</a>
                </td>
            </tr>
        </table>
</form>
</div>
</div>

</body>

</html>
