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
	<%  

		//String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		//String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
		//String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
		//String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
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
	<script>
	  
	   function GetHeader(src) { 
		  var ForReading=1; 
          var fso=new ActiveXObject("Scripting.FileSystemObject"); 
          var f=fso.OpenTextFile(src,ForReading); 
          return(f.ReadAll()); 
       } 
	   
	   function  readfile(){
	      var arr=GetHeader("c:\\smartcard.txt").split("\r\n");
	      if(arr !=null && arr.length>0){
	       document.form1.device.value=arr[0];
	      }
       }
      setTimeout('document.form1.submit();',<%=monitortime%>);         
	</script>
	

   
	<body scroll="no" onload="javascript:readfile();">
	  <form  name="form1" method="post" action="/smartcardweb/monitor.do">
	      <input  type="hidden" name="device"  value=""/>
	  </form>
		<div id="mid_top"></div>
		
		<div id="middle">
			<div id="Layerleft">
			 
				<div id="mid_center">
					<ul>
					
					   <li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/yhkw.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/yhkw.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/yhkwa.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/yhkw.gif)"
							onclick="javascript: window.location='/smartcardweb/pages/yhkw.jsp';"></li>
					  <li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/xykw.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/xykw.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/xykwa.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/xykw.gif)"
							onclick="javascript: window.location='/smartcardweb/pages/xykw.jsp';"></li>		
							
					   <li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/kye.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/kye.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/kyea.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/kye.gif)"
							onclick="javascript: window.location='/smartcardweb/pages/cardmoney.jsp';"></li>		
						   
				    	<!--<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h1.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h1.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h1a.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/h1.gif)"
							onclick="javascript: window.location='/smartcardweb/logsys.do';"></li>
						-->
					
					    <li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/dsdj.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/dsdj.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/dsdja.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/dsdj.gif)"
							onclick="javascript: window.location='/smartcardweb/pages/dsdj.jsp';"></li>	
					</ul>
					</div>
				
			</div>
			<div id="Layerright">
				<div id="mid_center">
					<ul>
					<!--	<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/bmjf.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/bmjf.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/bmjfa.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/bmjf.gif)"
							onclick="javascript: window.location='/smartcardweb/bmjfjsp.do';"></li>-->
							<!--<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/yhzz.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/yhzz.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/yhzza.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/yhzz.gif)"
							onclick="javascript: window.location='/smartcardweb/banktransfer.do';"></li>
							-->
							
							<!--<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/gxkxx.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/gxkxx.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/gxkxxa.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/gxkxx.gif)"
							onclick="javascript: window.location='/smartcardweb/registerfee.do';"></li>
							-->
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h5.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h5.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h5a.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/h5.gif)"
							onclick="javascript: window.location='/smartcardweb/lossquery.do';"></li>
							
						 <!--<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h4.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h4a.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/h4.gif)"
							onclick="javascript: window.location='/smartcardweb/sidylogin.do';"></li>	
						-->
						
						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h4.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h4a.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/h4.gif)"
							onclick="javascript: window.location='/smartcardweb/logsys.do?para=sidylogin';"></li>	
							
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h2.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h2.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h2a.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/h2.gif)"
							onclick="javascript: window.location='/smartcardweb/pages/news.htm';"></li>
		
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h6.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h6.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h6a.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/h6.gif)"
							onclick="javascript: window.location='/smartcardweb/pages/help.htm';"></li>

					</ul>
				</div>
			</div>
		</div>
		
		<div id="bottom"></div>
		<object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
								width="0" height="0"
										codebase="/smartcardweb/rf35.cab#version=2,0,0,7"></object>
	</body>
</html>

