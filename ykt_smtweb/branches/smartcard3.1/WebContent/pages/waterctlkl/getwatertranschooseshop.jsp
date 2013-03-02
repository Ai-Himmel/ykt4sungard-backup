<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title></title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
	</head>
	
	
	<script>
	   function chooseshop(pama){
	   	 document.all.moneyForm.tradecode.value=pama;
	   	 moneyForm.submit();
	   }
	</script>
	
	<body scroll="no" >
	<form name="moneyForm" action="/smartcardweb/waterbusiness999.do" method="post">	
	   <input type="hidden"  name="tradecode" value="0" />
	</form>  
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layer2">
				<div id="mid_center">
					<ul>
					<li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/lyzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/lyzz2.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/lyzz.gif)"
                            onclick="javascript: chooseshop(1001);"></li>    
                      <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/bzkszz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/bzkszz2.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/bzkszz.gif)"
                            onclick="javascript: chooseshop(1002);"></li>    
                       <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/zfkszz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/zfkszz2.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/zfkszz.gif)"
                            onclick="javascript: chooseshop(1003);"></li>    
		
							
					</ul>
					</div>
			</div>
			
			<div id="Layer3">
				<div id="mid_center">
					<ul>
							
						 <li></li>		
							
						<li></li>
							
						<li>
						</li>	
						
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/fhcd.gif)"
							onclick="javascript: window.location='/smartcardweb/main.do';"></li>	
						
					</ul>	
				</div>
			</div>
		 
		</div>
			
		<div id="bottom"></div>
		  
	</body>
</html>

