<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html>
	<head>
		<title></title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
	</head>
	
	
	<script>
	   function choosepaycode(pama){
	   	 document.all.moneyForm.tradecode.value=pama;
	   	 moneyForm.submit();
	   }
	</script>
	
	<body scroll="no" >
	<form name="moneyForm" action="/smartcardweb/waterbusiness.do" method="post">	
	   <input type="hidden"  name="tradecode" value="0" />
	</form>  
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layer2">
				<div id="mid_center1">
					<ul>
					<li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/ksskzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/ksskzza.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/ksskzz.gif)"
                            onclick="javascript: choosepaycode(1231);"></li>    
                      <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/lyskzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/lyskzza.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/lyskzz.gif)"
                            onclick="javascript: choosepaycode(1232);"></li>    	
							
					</ul>
					</div>
			</div>
			
			<div id="Layer3">
				<div id="mid_center2">
					<ul>
							
						  <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/lyskcsh.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/lyskcsha.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/lyskcsh.gif)"
                            onclick="window.location='/smartcardweb/pages/waterctl/initwaterpocket.jsp'; "></li> 
							
						<li></li>
							
						<li>
						</li>	
						
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/fhcd.gif)"
							onclick="javascript: window.location='/smartcardweb/index.do';"></li>	
						
					</ul>	
				</div>
			</div>
		 
		</div>
			
		<div id="bottom"></div>
		   <object id="RFScanner" classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0" height="0"></object>
	</body>
</html>

