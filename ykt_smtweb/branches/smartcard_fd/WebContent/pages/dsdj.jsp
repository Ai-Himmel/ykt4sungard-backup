<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html xmlns="http://www.w3.org/1999/xhtml">

	<head>
		<title></title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<style type="text/css">

</style>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
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
							onmouseup="this.style.background='url(/smartcardweb/pages/images/csrd.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/csrda.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/csrd.gif)"
							onclick="javascript: window.location='/smartcardweb/cityHotspot.do';">
							
							
							
						
					</ul>
				</div>
			</div>
			<div id="Layerright">
				<div id="mid_center">
					<ul>
                        <li></li>
                        <li></li>
                        <li></li>
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/fhcd.gif)"
							onclick="javascript: window.location='/smartcardweb/pages/index.jsp';"></li>	
							
					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>

	</body>
</html>
