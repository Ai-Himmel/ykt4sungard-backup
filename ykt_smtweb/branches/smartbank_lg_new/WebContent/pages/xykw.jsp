<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html xmlns="http://www.w3.org/1999/xhtml">
<%@ page language="java" pageEncoding="UTF-8"%>

	<head>
		<title></title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
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
		     readCard('<%=path%>/queryact.do');
		     return;
		   }
		   if(butt=="<%=left2%>"){
		     window.location='<%=path%>/jymx.do';
		   }
		   if(butt=="<%=left3%>"){
		     window.location='<%=path%>/logsys.do?para=updatepwd';
		   }
		   
		    if(butt=="<%=right1%>"){
		     window.location='<%=path%>/pages/userlogon.jsp';
		   }
		   if(butt=="<%=right2%>"){
		      window.location='<%=path%>/logsys.do?para=cancelloss';
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
        
 
     </script>
	
 
	<body scroll="no">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layer2">
				<div id="mid_center">
					<ul>
						<li
							onmouseup="this.style.background='url(<%=path%>/pages/images/zhxx.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/zhxxa.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/zhxx.gif)"
							onclick="readCard('<%=path%>/queryact.do')"></li>
						<li
							onmouseup="this.style.background='url(<%=path%>/pages/images/detail.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/detaila.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/detail.gif)"
							onclick="javascript: window.location='<%=path%>/jymx.do';"></li>
						
							
						<li
							onmouseup="this.style.background='url(<%=path%>/pages/images/pass.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/passa.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/pass.gif)"
							onclick="javascript: window.location='<%=path%>/logsys.do?para=updatepwd';"></li>
						
					</ul>
				</div>
			</div>
			<div id="Layer3">
				<div id="mid_center">
					<ul>
 
					   
					
					   <li
							onmouseout="this.style.background='url(<%=path%>/pages/images/h5.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/h5.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/h5a.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/h5.gif)"
							onclick="javascript: window.location='<%=path%>/pages/userlogon.jsp';"></li>
					  <li
							onmouseup="this.style.background='url(<%=path%>/pages/images/jgsq.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/jgsqa.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/jgsq.gif)"
							onclick="javascript:window.location='<%=path%>/logsys.do?para=cancelloss';"></li>		
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
