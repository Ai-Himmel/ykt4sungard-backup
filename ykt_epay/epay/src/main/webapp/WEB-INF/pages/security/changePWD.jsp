<%@page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<head>
 <script src="<c:url value="/theme/scripts/jquery.js"/>"	type="text/javascript"></script>
	<script src="<c:url value="/theme/scripts/jquery.validate.js"/>"	type="text/javascript"></script>
    <script type="text/javascript">
        $().ready(function() {
	// validate signup form on keyup and submit
			jQuery.validator.addMethod("passwordcheck", function( value, element ) {
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
				return flag>2&&/^[A-Za-z0-9]+$/.test(value)&&value!=$("#accno").val();
			}, "必须含有数字、大写字母、小写字母,不能包含特殊字符和汉字,不能与账号相同!");
		jQuery.validator.addMethod("equesacc", function( value, element ) {
				return value!=$("#account").val();
		}, "不能与账号相同!");
		jQuery.validator.addMethod("equesoldpas", function( value, element ) {
				return value!=$("#oldpwd").val();
		}, "不能原密码相同!");
		$("#changepwdform").validate({
			rules: {
				pwdtype: "required",
				oldpwd: "required",
				newpwd: {
					required:true,
					minlength:6,
					equesacc:true,
					equesoldpas:true,
					passwordcheck:true
				},
				newpwd2: {
					required:"true",
					equalTo: "#newpwd"
				}
			},
			messages: {
				pwdtype: "请选择修改密码类型!",
				oldpwd: "请输入您原密码!",
				newpwd: {
					required:"请设置您的新密码!",
					minlength:"密码长度不能小于6个字符"
				},
				newpwd2: {
					required:"请再次输入您的设置的密码!",
					equalTo: "两次输入密码不一致!"
				}
			}
		});
	});
    </script>
    <style type="text/css">
	#changepwdform label.error {
		margin-left: 10px;
		width: auto;
		display: inline;
		color: red;
	}
</style>
</head>
<center>
				<form id="changepwdform" name="changepwdform" action="accountManager.do?method=changePwd" method="post">
					<html:errors/>
					<div id="breadcrumbe"><span>当前位置：修改密码</span> </div>
    					<div class="content">
       					 <table  class="ProfileTable" >
						<c:if test="${acctype!=null&&acctype=='1'}">
							<tr>
								<td width="20%" class="list01">
									修改密码类型:<input id="accno" name="accno" type="hidden" value="<bean:write name="accno" scope="session"/>">
								</td>
							
								<td>
									 <select id="pwdtype" name="pwdtype">
	            						<option value="">------请选择------</option>
	            						<option value="1">登录密码</option>
	            						<option value="2">支付密码</option>
	         						 </select>
								</td>
							</tr>
						</c:if>
						<c:if test="${acctype!=null&&acctype=='2'}">
							<input type="hidden" name="pwdtype" value="1"/>
						</c:if>
						<tr>
							<td width="20%" class="list01">
								请输入原密码:
							</td>

							<td align="left">
								<input name="oldpwd" id="oldpwd" type="password" maxlength="8">
							</td>
						</tr>
						<tr>
							<td width="20%" class="list01">
								请输入新密码:
							</td>

							<td align="left">
								<input name="newpwd" id="newpwd" type="password"  maxlength="8">
							</td>
						</tr>

						<tr>
							<td  width="20%" class="list01">
								请再次输入新密码:
							</td>

							<td align="left">
								<input name="newpwd2" id="newpwd2" type="password" maxlength="8">
							</td>
						</tr>
						<tr>
							<td width="20%" class="list01"></td>
							<td >
								<html:submit styleClass="button">
									<bean:message key="button.submit" />
								</html:submit>
								<html:reset styleClass="button">
									<bean:message key="button.reset" />
								</html:reset>
							</td>
						</tr>
					</table>
				</div>
			</div>
			</form>
</center>
