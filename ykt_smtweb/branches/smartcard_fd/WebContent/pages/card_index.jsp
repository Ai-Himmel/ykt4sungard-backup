<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html xmlns="http://www.w3.org/1999/xhtml">

	<head>
		<title></title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<style type="text/css">

</style>
		<link href="pages/css/css.css" rel="stylesheet" type="text/css" />
	</head>
	<%  

		
		String monitortime = KSConfiguration.getInstance().getProperty("monitortime");
		String buttonleft = KSConfiguration.getInstance().getProperty("buttonleft","10");
		String buttontop = KSConfiguration.getInstance().getProperty("buttontop","140");
		String buttonright = KSConfiguration.getInstance().getProperty("buttonright","220");
		String buttonmargin = KSConfiguration.getInstance().getProperty("buttonmargin","50");
		
	  
	%>
	<style type="text/css">
	   #mid_center ul li{ 
	   list-style:none;width:224px; 
	   margin-bottom:<%=buttonmargin%>px;
	   background-image:url(/smartcardweb/pages/images2/h1.gif);
	   width:224px; 
	   height:73px;
	   }
	   
	   #Layerleft {
	   position:absolute;
	   left:<%=buttonleft%>px;
	   top:<%=buttontop%>px;
	   width:45%;
	   height:120px;
	   z-index:1;
      }
	#Layerright {
	position:absolute;
	right:<%=buttonright%>px;
	top:<%=buttontop%>px;
	width:30%;
	height:120px;
	z-index:1;
    }
  </style>
	<body scroll="no">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layerleft">
				<div id="mid_center">
					<ul>
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/count.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/counta.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/count.gif)"
							onclick="javascript: window.location='/smartcardweb/queryact.do';"></li>
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/detail.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/detaila.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/detail.gif)"
							onclick="javascript: window.location='/smartcardweb/tradequery.do';"></li>
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/jie.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/jiea.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/jie.gif)"
							onclick="javascript: window.location='/smartcardweb/cancelloss.do';"></li>
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/pass.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/passa.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/pass.gif)"
							onclick="javascript: window.location='/smartcardweb/updatepwd.do';"></li>
						
					</ul>
				</div>
			</div>
			<div id="Layerright">
				<div id="mid_center">
					<ul>
 
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h3.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h3a.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/h3.gif)"
							onclick="javascript: window.location='/smartcardweb/assistancequery.do';"></li>
						
					  
							
						<!--
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h4.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h4a.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/h4.gif)"
							onclick="javascript: window.location='/smartcardweb/sidylogin.do';"></li>
					  -->
				
					
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/csrd.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/csrda.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/csrd.gif)"
							onclick="javascript: window.location='/smartcardweb/cityHotspot.do';">
							
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/reset.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/reseta.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/reset.gif)"
							onclick="javascript: window.location='/smartcardweb/usrexit.do';"></li>	
						
							
					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>

	</body>
</html>
