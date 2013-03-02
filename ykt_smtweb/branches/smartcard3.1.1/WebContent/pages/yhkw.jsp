<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.ConfigMenu" %>
<html>
	<head>
		<title>银行卡务</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<style type="text/css">

		</style>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
	</head>
	
	
	<body scroll="no">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layer2">
				<div id="mid_center1">
					<ul>
						 <li onmouseout="this.style.background='url(/smartcardweb/pages/images/yhzz.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/yhzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/yhzza.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/yhzz.gif); <% if (!ConfigMenu.getMenuStatus("bankBiz_nctrade")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/nctranslogin.do';"></li>

                           <li onmouseout="this.style.background='url(/smartcardweb/pages/images/ye.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/ye.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/yea.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/ye.gif); <% if (!ConfigMenu.getMenuStatus("bankBiz_ncbalance")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/ncreadbankcard.do';"></li>
                            
                            <li onmouseout="this.style.background='url(/smartcardweb/pages/images/yhzz.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/yhzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/yhzza.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/yhzz.gif); <% if (!ConfigMenu.getMenuStatus("bankBiz_trade")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/translogin.do';"></li>

                           <li onmouseout="this.style.background='url(/smartcardweb/pages/images/ye.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/ye.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/yea.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/ye.gif); <% if (!ConfigMenu.getMenuStatus("bankBiz_balance")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/bankquerylogin.do';"></li> 
							
						<li onmouseout="this.style.background='url(/smartcardweb/pages/images/yhqc.gif)'"
                           onmouseup="this.style.background='url(/smartcardweb/pages/images/yhqc.gif)'"
                           onmousedown="this.style.background='url(/smartcardweb/pages/images/yhqca.gif)'"
                           style="cursor: hand; background: url(/smartcardweb/pages/images/yhqc.gif); <% if (!ConfigMenu.getMenuStatus("bankBiz_authtrade")) { out.print(" display:none; "); }%>"
                           onclick="javascript: window.location='/smartcardweb/authtranslogin.do';"></li>

                          <li onmouseout="this.style.background='url(/smartcardweb/pages/images/yhye.gif)'"
                           onmouseup="this.style.background='url(/smartcardweb/pages/images/yhye.gif)'"
                           onmousedown="this.style.background='url(/smartcardweb/pages/images/yhyea.gif)'"
                           style="cursor: hand; background: url(/smartcardweb/pages/images/yhye.gif); <% if (!ConfigMenu.getMenuStatus("bankBiz_authbalance")) { out.print(" display:none; "); }%>"
                           onclick="javascript: window.location='/smartcardweb/authbankquerylogin.do';"></li>
                           
                           <!-- 银行卡绑定（验证） -->
                           <li onmouseout="this.style.background='url(/smartcardweb/pages/images/qcbd.gif)'"
                           onmouseup="this.style.background='url(/smartcardweb/pages/images/qcbd.gif)'"
                           onmousedown="this.style.background='url(/smartcardweb/pages/images/qcbdz.gif)'"
                           style="cursor: hand; background: url(/smartcardweb/pages/images/qcbd.gif); <% if (!ConfigMenu.getMenuStatus("bankbiz_authbankbind")) { out.print(" display:none; "); }%>"
                           onclick="javascript: window.location='/smartcardweb/authbankbindputin.do';"></li>
						
						 <li>&nbsp;</li>
				
						
					</ul>
				</div>
			</div>
			<div id="Layer3">
				<div id="mid_center2">
					<ul>
 
						 <li>&nbsp;</li>
					   
					   <li>&nbsp;</li>
					   <li>&nbsp;</li>
					
					 <%if(request.getSession().getAttribute("cardphyid")==null){ %>
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/fhcd.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/index.jsp';"></li>
                            <%}else{%>
                            <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/reset.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/reseta.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/reset.gif)"
                            onclick="javascript: window.location='/smartcardweb/usrexit.do';"></li>
                            <%} %>	
							
					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
		<form  method="post" name="logonForm" >
          <object id="RFScanner"
                classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
                height="0"></object>
		</form>								
	</body>
</html>
