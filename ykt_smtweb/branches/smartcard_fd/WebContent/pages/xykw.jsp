<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html xmlns="http://www.w3.org/1999/xhtml">
	<%@ page language="java" pageEncoding="UTF-8"%>
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
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
	  
	%>
	<script>
	function readCard(url)
        {   
         
          var device_port = <%=read_card_device_port%>;           
          logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
           var ret=logonForm.all.RFScanner.DoScan();
           if(ret==0){///读卡成功
             //alert(url+"?cardno="+document.all.RFScanner.CardNo);
              window.location=url+"?cardno="+document.all.RFScanner.CardNo;
           }else if(ret==-1){
              alert('系统暂时不可用'+ret);
           }
        }
     </script>
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
							onmouseup="this.style.background='url(/smartcardweb/pages/images/zhxx.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/zhxxa.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/zhxx.gif)"
							onclick="readCard('/smartcardweb/queryact.do')"></li>
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/detail.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/detaila.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/detail.gif)"
							onclick="javascript: window.location='/smartcardweb/jymx.do';"></li>
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/jgsq.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/jgsqa.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/jgsq.gif)"
							onclick="readCard('/smartcardweb/cancelloss.do')"></li>
							
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
							onclick="readCard('/smartcardweb/queryassistance.do')"></li>
						
					   <li>  </li>
							   
					   <li>   </li>
							  
							
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
         <form  method="post" name="logonForm" >
		
		<object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
								width="0" height="0"
										codebase="/smartcardweb/rf35.cab#version=2,0,0,7"></object>
	</form>
	</body>
</html>
