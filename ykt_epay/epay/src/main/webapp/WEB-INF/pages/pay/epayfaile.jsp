<%@page pageEncoding="UTF-8"%>
<%@ include file="../tiles/include.jsp"%>
<div id="wrap">
  <div id="top">
  	<div class="logo flt"><img src="<c:url value="/theme/style/epay/images/cashier.gif"/>" /></div>
    <div class="frt">您好，<c:if test="${accname!=null&&accname!=''}"><bean:write name="accname"/></c:if>。您的帐号是：<span><bean:write name="payForm" property="name"/></span></div>
  </div>
  <div id="container">
    <p><span class="yelText">您正使用即时到账交易:</span>付款后资金直接进入对账户</p>
      <div class="error_tb">
        <div class="content">
        <div class=" lgLeft flt topPadd">
        <div class="flt rgtPadd imgtopPadd"><img src="<c:url value="/theme/style/epay/images/error.gif"/>"/></div><div class=" flt F14"><p class="Font14">付款失败!<bean:write name="payForm" property="v_amount"/>元</p>
        <p style="color: red"><c:if test="${msg!=null&&msg!=''}"><bean:write name="msg"/></c:if></p>
         <form id="returnform" action="<bean:write name="payForm" property="v_url"/>" method="post">
         	<input type="hidden" name="v_oid" value="<bean:write name="payForm" property="v_oid"/>"/>
         	<input type="hidden" name="v_status" value="-1"/>
         	<input type="hidden" name="v_code" value="<bean:write name="v_returncode"/>"/>
         	<input type="hidden" name="v_amount" value="<bean:write name="payForm" property="v_amount"/>"/>
         	<input type="hidden" name="v_currency" value="<bean:write name="payForm" property="v_currency"/>"/>
         	<input type="hidden" name="v_errcode" value="<bean:write name="v_errcode"/>"/>
         	<input type="hidden" name="v_errmsg" value="<bean:write name="v_errmsg"/>"/>
         	<input type="hidden" name="v_name" value="<bean:write name="payForm" property="v_name"/>"/>
         	<input type="hidden" name="v_remark" value="<bean:write name="payForm" property="v_remark"/>"/>
         </form>
         <p>如果您有款付款信息<a href="###" onclick="returnform.submit();">查看并继续付款</a></p>
         <!-- <p>您可能要：<a href="">查看余额</a>  | <a href=""> 消费记录</a> </p> -->
        </div>
        </div>
        <div class="frt"><img src="<c:url value="/theme/style/epay/images/errorpic.gif"/>" /></div>
        </div>
      </div>
    </div>
  <div id="footer">版权所有&copy;一卡通支付平台</div>
</div>	