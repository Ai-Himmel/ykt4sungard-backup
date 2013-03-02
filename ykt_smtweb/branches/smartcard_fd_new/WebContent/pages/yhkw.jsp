<%@ page contentType="text/html; charset=GBK"%>

<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ include  file="/pages/init.jsp"%>
<html>
<head>
<title></title>


<style type="text/css">
 
</style>
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<script language="javascript" src="<%=path%>/pages/js/util.js"></script>
	</head>
	  <script>  
	  
	     function window.document.onkeydown()
		{     
		   var  butt = showKeyName(event);
		   if(butt=="<%=left1%>"){
		     window.location='<%=path%>/banktransfer.do';
		   }
		   if(butt=="<%=left2%>"){
		     window.location='<%=path%>/bankmoney.do';
		   }
		  
		   if(butt=="<%=right1%>"){
		     tradedetail();
		   }
		  
		   if(butt=="<%=right4%>"){
		      window.location='<%=path%>/pages/index.jsp';
		   }
		}
	    
           function tradedetail()
        {   
           var device_port = <%=read_card_device_port%>;           
           logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
           var ret=logonForm.all.RFScanner.DoScan();
           if(ret==0){///读卡成功
              window.location='<%=path%>/querytransfer.do?cardno='+document.all.RFScanner.CardNo;  
           }else if(ret==-2){
             alert('读卡失败，请确认放好卡');
           }else if(ret==-1){
             alert('打开端口失败，系统暂时无法使用');
           }
        }
       
      </script>
	
	
	<body scroll="no" onkeydown="return (event.keyCode!=8)">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layerleft">
				<div id="mid_center">
					<ul>
						<li
							onmouseout="this.style.background='url(<%=path%>/pages/images/yhzz.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/yhzz.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/yhzza.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/yhzz.gif)"
							onclick="javascript: window.location='<%=path%>/banktransfer.do';">
						
						<li
							onmouseup="this.style.background='url(<%=path%>/pages/images/ye.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/yea.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/ye.gif)"
							onclick="javascript: window.location='<%=path%>/bankmoney.do';"></li>
						
						
					</ul>
				</div>
			</div>
			<div id="Layerright">
				<div id="mid_center">
					<ul>
 
						<li
							onmouseup="this.style.background='url(<%=path%>/pages/images/zzmx.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/zzmxa.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/zzmx.gif)"
							onclick="tradedetail();"></li>
					   
					   <li></li>
					   <li></li>
					   <li
							onmouseup="this.style.background='url(<%=path%>/pages/images/fhcd.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/fhcda.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/fhcd.gif)"
							onclick="javascript: window.location='<%=path%>/pages/index.jsp';"></li>	
							
					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
		<form  method="post" name="logonForm" >
         <object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
								width="0" height="0"
										codebase="<%=path%>/rf35.cab#version=2,0,0,7"></object>
		</form>								
	</body>
</html>
