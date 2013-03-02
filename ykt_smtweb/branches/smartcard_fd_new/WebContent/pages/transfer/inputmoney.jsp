<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ include  file="/pages/init.jsp"%><html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title></title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<script language="javascript" src="<%=path%>/pages/js/util.js"></script>
	</head>
		
	<script>
	     function window.document.onkeydown()
		{     
		   var  butt = showKeyName(event);
		   if(butt=="<%=left1%>"){
		     inputmoney(50);
		   }
		   
		   if(butt=="<%=left2%>"){
		     inputmoney(100);
		   }
		   
		    if(butt=="<%=left3%>"){
		     window.location='<%=path%>/inputothermoney.do';
		   }
		   
		   if(butt=="<%=right1%>"){
		     inputmoney(150);
		   }
		   
		    if(butt=="<%=right2%>"){
		     tradedetail(200);
		   }
		   	  
		   if(butt=="<%=right4%>"){
		      window.location='<%=path%>/pages/yhkw.jsp';
		   }
		}  
	
	   function inputmoney(pama){
	   	 document.moneyForm.money.value=pama;
	   	 moneyForm.submit();
	   }
	</script>
	
	<body scroll="no" onkeydown="return (event.keyCode!=8)">
	<form name="moneyForm" action="<%=path%>/transferbankpwd.do" method="post">	
	   <input type="hidden"  name="money" value="0" />
	</form>  
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layerleft">
				<div id="mid_center">
					<ul>
					   <li
							onmouseout="this.style.background='url(<%=path%>/pages/images/50.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/50.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/50a.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/50.gif)"
							onclick="inputmoney(50)"></li>
					  <li
							onmouseout="this.style.background='url(<%=path%>/pages/images/100.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/100.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/100a.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/100.gif)"
							onclick="inputmoney(100)"></li>		
					  <li
							onmouseout="this.style.background='url(<%=path%>/pages/images/qt.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/qt.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/qta.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/qt.gif)"
							onclick="javascript: window.location='<%=path%>/inputothermoney.do'"></li>				
							
					</ul>
					</div>
			</div>
			
			<div id="Layerright">
				<div id="mid_center">
					<ul>
							
						 <li
							onmouseout="this.style.background='url(<%=path%>/pages/images/150.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/150.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/150a.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/150.gif)"
							onclick="inputmoney(150)"></li>		
							
						<li
							onmouseout="this.style.background='url(<%=path%>/pages/images/200.gif)'"
							onmouseup="this.style.background='url(<%=path%>/pages/images/200.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/200a.gif)'"
							style="cursor: hand; background: url(<%=path%>/pages/images/200.gif)"
							onclick="inputmoney(200)"></li>
						<li>
						</li>	
						<li
							onmouseup="this.style.background='url(<%=path%>/pages/images/fhcd.gif)'"
							onmousedown="this.style.background='url(<%=path%>/pages/images/fhcda.gif)'"
							style="cursor:hand; background:url(<%=path%>/pages/images/fhcd.gif)"
							onclick="javascript: window.location='<%=path%>/pages/yhkw.jsp';"></li>	
						
					</ul>	
				</div>
			</div>
		 
		</div>
			
		<div id="bottom"></div>
		  
	</body>
</html>

