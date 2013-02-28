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
				password:"required"
			},
			messages: {
				password:"<font color=red>密码不能为空!</font>"
			}
		});
	 });
</script>
</head>
<div id="wrap">
  <div id="top">
    <div class="logo flt"><img src="<c:url value="/theme/style/epay/images/cashier.gif"/>" /></div>
    <div class="frt">您好，<bean:write name="accname"/>。您的帐号是：<span><bean:write name="payForm" property="name"/></span></div>
  </div>
  <div id="container">
    <p><span class="yelText">您正使用即时到账交易:</span>付款后资金直接进入对账户</p>
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
    	<html:form action="payManager.do?method=epayend" target="_top" focus="name">
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
      <div class="blue_tb bulebg">
        <div class="content">
        <p>您的一卡通帐户:<bean:write name="payForm" property="name"/><input type="hidden" name="name" value="<bean:write name="payForm" property="name"/>"/></p>
        <p>可支付金额:<span class="greenText"><bean:write name="availbal"/></span>元</p>
        <div class="underline "></div>
        <div class="topPadd"></div>
         <p class="fieldBlock">
            <label class="bbg"></label>
           		使用一卡通余额支付:<span class="lightText"><bean:write name="payForm" property="v_amount"/></span>元
          </p>
         <p class="fieldBlock">
            <div>
            <label class="bbg">一卡通支付密码</label>
            <html:password property="password" maxlength="18" redisplay="false" styleClass="loginInput" onkeydown="if(event.keyCode==13) {dosubmit.click();}"/><!--<span> <a href="">忘记密码？</a> </span>-->
          	</div>
          	<div class="loginError">
      			<html:errors />
      		</div>
          </p>
          <!-- 
          <p class="fieldBlock">
            <label class="bbg">验证码</label>
            <input name="chkCode" maxlength=50 onkeydown="if(event.keyCode==13) {if(validateLoginForm(loginForm)) {loginForm.submit();}}">
            <html:img page="/CheckCodeImage" align="absmiddle" style="border: 1 dotted black" width="52" height="20" />
          </p>
           -->
          <p class="fieldBlock">
            <label class="bbg">&nbsp;</label>
            <input type="submit" class="lgbigBtn" id="dosubmit" value="确认支付 " name="dosubmit"> 
        </div>
      </div>
      </html:form>
    </div>
  </div>
  <div id="footer">版权所有&copy;一卡通支付平台</div>
</div>

