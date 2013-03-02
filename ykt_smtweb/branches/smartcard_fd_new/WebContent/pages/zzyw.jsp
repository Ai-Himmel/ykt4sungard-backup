<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ page language="java" pageEncoding="UTF-8"%>
<%@ include  file="/pages/init.jsp"%>
<html>
<head>

<title></title>

<link href="<%=path%>/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<script language="javascript" src="<%=path%>/pages/js/util.js"></script>
		<script language="javascript" src="<%=path%>/pages/js/other.js"></script>
	</head>
	  <script><!--  
	  
	     function window.document.onkeydown()
		{     
		   var  butt = showKeyName(event);
		   if(butt=="<%=left1%>"){
		     readCard('<%=path%>/queryassistance.do');
		   }
		   if(butt=="<%=left2%>"){
		     window.location='<%=path%>/logsys.do?para=sidylogin';
		   }
		  
		   if(butt=="<%=right1%>"){
		     window.location='<%=path%>/logsys.do?para=updateCardinfo';
		   }
		   
		   if(butt=="<%=right2%>"){
		    // window.location='<%=path%>/logsys.do?para=balanceFee';
		   }
		  
		   if(butt=="<%=right4%>"){
		      window.location='<%=path%>/pages/index.jsp';
		   }
		}
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
         
       
      --></script>
	
	
	<body scroll="no" onkeydown="return (event.keyCode!=8)">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layerleft">
				<div id="mid_center">
					<ul>
						<li
							onmouseup="this.style.background='url(<%=path%>/pages/images/h3.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/h3a.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/h3.gif)"
							onclick="readCard('<%=path%>/queryassistance.do')"></li>
						
					   <li
							onmouseup="this.style.background='url(<%=path%>/pages/images/h4.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/h4a.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/h4.gif)"
							onclick="javascript: window.location='<%=path%>/logsys.do?para=sidylogin';"></li>
					  
					
							
						
					</ul>
				</div>
			</div>
			<div id="Layerright">
				<div id="mid_center">
					<ul>
                        
					    <li
							onmouseup="this.style.background='url(<%=path%>/pages/images/gxkxx.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/gxkxxa.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/gxkxx.gif)"
							onclick="javascript:window.location='<%=path%>/logsys.do?para=updateCard'"></li>
					 
						
					   <li
							onmouseup="this.style.background='url(<%=path%>/pages/images/dhfqs.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/dhfqsa.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/dhfqs.gif)"
							onclick="javascript: window.location='<%=path%>/logsys.do?para=feeBalance';"></li>		
							
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
