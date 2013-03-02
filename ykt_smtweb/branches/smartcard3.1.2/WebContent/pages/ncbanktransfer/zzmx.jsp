<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ page language="java" pageEncoding="UTF-8"%>
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
	    
	    String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
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
      <script>  
           function tradedetail(w)
        {   
          
           var device_port = <%=read_card_device_port%>;           
           logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
           var ret=logonForm.all.RFScanner.DoScan();
           if(ret==0){///读卡成功
              window.location='/smartcardweb/querytransfer.do?week='+w+'&cardno='+document.all.RFScanner.CardNo;  
             //alert('/smartcardweb/querytradeserial.do?week='+w+'&cardno='+document.all.RFScanner.CardNo);
           }else if(ret==-2){
             //alert('读卡失败，请确认放好卡');
           }else if(ret==-1){
             alert('打开端口失败，系统暂时无法使用');
           }
        }
        
      </script>
    
 
	<body scroll="no">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layerleft">
				<div id="mid_center">
					<ul>
							<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/1z.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/1za.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/1z.gif)"
							onclick="tradedetail('0')">
							
							<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/2z.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/2za.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/2z.gif)"
							onclick="tradedetail('1')">
							
					</ul>
				</div>
			</div>
			<div id="Layerright">
				<div id="mid_center">
					<ul>
							<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/3z.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/3za.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/3z.gif)"
							onclick="tradedetail('2');">
							
							<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/4z.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/4za.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/4z.gif)"
							onclick="tradedetail('3');">
							
							<li>
							</li>	
							
							<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/fhcd.gif)"
							onclick="javascript: window.location='/smartcardweb/pages/xykw.jsp';"></li>	
							

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
