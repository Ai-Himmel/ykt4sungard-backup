<%@page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<head>
<bean:define id="loginTitle">
	<bean:message bundle="security" key="login.title" />
</bean:define>
<script src="<c:url value="/theme/scripts/jquery.js"/>"	type="text/javascript"></script>
<script src="<c:url value="/theme/scripts/jquery.validate.js"/>"	type="text/javascript"></script>
<script type="text/javascript">
	 $().ready(function() {
		$("form[name='payForm']").validate({
			rules: {
				name:"required",
				password:"required",
				chkCode:"required"
			},
			messages: {
				name:"<font color=red>不能为空!</font>",
				password:"<font color=red>不能为空!</font>",
				chkCode:"<font color=red>不能为空!</font>"
			}
		});
	 });
</script>
</head>
<div id="wrap">
  <div id="top">
    <div class="logo flt"><img src="<c:url value="/theme/style/epay/images/logo.gif"/>" /></div>
    <div class="frt">您好，欢迎使用一卡通支付平台</div>
  </div>
  <div id="container">
    <p><span class="yelText">您正使用即时到账交易:</span>1、确认订单--2、付款给买家---3、交易完成</p>
    <div>
      <table id="pay_tb">
        <tr>
          <th class="pay">订单名称</th>
          <th class="pay">收款方</th>
          <th class="pay">订单金额</th>
        </tr>
        <tr>
          <td width="40%"><bean:write name="payForm" property="v_oid"/><span class="strong leftPadd"><!-- <a href="">详情</a> --></span></td>
          <td><bean:write name="shopname"/></td>
          <td><span class="lightText"><bean:write name="payForm" property="v_amount"/></span>元</td>
        </tr>
      </table>
    </div>
    <div class="topPadd">
      <div  id="login_tb">
        <div class="loginTopbg">
          <div class="lgtopPadd"> <img src="<c:url value="/theme/style/epay/images/lg.gif"/>" /></div>
          <div class="content">
          	<div class="loginError">
      			<html:errors />
      		</div>
        	<html:form action="payManager.do?method=login" target="_top" focus="name">
          		<html:text property="v_shopid"  style="display:none"/>
		      	<html:text property="v_account"  style="display:none"/>
		      	<html:text property="v_oid" style="display:none"/>
		      	<html:text property="v_amount"  style="display:none"/>
		      	<html:text property="v_currency"  style="display:none"/>
		      	<html:text property="v_url"  style="display:none"/>
		      	<html:text property="v_code"  style="display:none"/>
		      	<html:text property="v_date"  style="display:none"/>
		      	<html:text property="v_time"  style="display:none"/>
		      	<html:text property="v_name"  style="display:none"/>
		      	<html:text property="v_remark"  style="display:none"/>
	          	<div class="lgLeft flt"> <p class="fieldBlock">
	            <label>用户名</label>
	            <html:text property="name" maxlength="18" styleClass="loginInput"  onkeydown="if(event.keyCode==13) {event.keyCode=9}" />
	          </p>
	          <p class="fieldBlock">
	            <label>密码</label>
	            <html:password property="password" maxlength="20" redisplay="false"  styleClass="loginInput" onkeydown="if(event.keyCode==13) {event.keyCode=9}"/>
	          </p>
	          <p class="fieldBlock">
	            <label>验证码</label>
	            <input type="text" title="验证码" name="chkCode" class="loginYzm" maxlength="4" onkeydown="if(event.keyCode==13) {loginBtn.click();}"/>
	            <html:img page="/CheckCodeImage" align="absmiddle" style="border: 1 dotted black" width="52" height="20" />
	            <span>
	            	<button class="primary" type="button" onclick=""></button>
            	</span>
            </p>
          	<p class="fieldBlock">
            <label>&nbsp;</label>
            <input class="loginBtn" id="loginBtn" type="submit" value="登录"/>
            <span><!-- <a href="">找回登录密码</a> --></span> </p></div>
         	 <div class="rightline flt"></div>
	          <div class="lgRight frt">
				<p></p>
				  <br />
			</div>
			</html:form>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div id="footer">版权所有&copy;一卡通支付平台</div>
</div>

