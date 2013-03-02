<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html>
	<head>
		<title>一卡通综合查询系统</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
	<%
		String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
		String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
		String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
	%>
	<script language="javascript">
			
	 function readCard()
        {   
          	var serverbase = "http://"+'<%=webserverip%>'+":"+'<%=webserverport%>'+"/"+'<%=webserverapp%>'+"/";
			var device_port = '<%=read_card_device_port%>';
			var scan=logonForm.all.RFScanner.DoScan();
			var cardId ="";
			if(scan !=0 ){
			  alert("读卡失败，请请正确放置卡片...");
			  return false;
			}else if(scan ==0 ){
        	 cardId = document.all.RFScanner.CardNo;
        	}
			logonForm.all.RFScanner.PortNo=device_port;
			var rrt = logonForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			if(rrt == 0){
				var ret = logonForm.all.RFScanner.ReadCardPocket(1,cardId,"");
				if(ret == 0){
					var bala = logonForm.all.RFScanner.GetPacketInfo("bala");
					var cxCnt =  logonForm.all.RFScanner.GetPacketInfo("total_cnt");//读卡次数,记录没次操作，如果和流水不一样，那么就是丢流水了。
		
						logonForm.all.cardId.value=cardId;
						logonForm.all.cardBala.value = bala;
						logonForm.all.txCnt.value = cxCnt;
						logonForm.submit();
				}else if(ret == 1){
					alert("请放置卡片...");
					return false;
				}else{
					alert("请正确放置卡片...");
					return false;
				}
			}else{
				alert("网络不通，请稍后重试...");
				return false;
			}
        }
	</script> 
	</head>
	<body scroll="no">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layer2">
				<div id="mid_center">
					<ul>
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h1.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h1.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h1a.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/h1.gif)"
							onclick="javascript: window.location='/smartcardweb/logsys.do';"></li>
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h2.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h2.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h2a.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/h2.gif)"
							onclick="javascript: window.location='/smartcardweb/pages/news.htm';"></li>
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h5.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h5.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h5a.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/h5.gif)"
							onclick="javascript: window.location='/smartcardweb/lossquery.do';"></li>
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h6.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h6.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h6a.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/h6.gif)"
							onclick="javascript: window.location='/smartcardweb/pages/help.htm';"></li>
					</ul>
				</div>
			</div>
			<div id="Layer3">
				<div id="mid_center">
					<ul>
					<!-- 
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/bmjf.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/bmjf.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/bmjfa.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/bmjf.gif)"
							onclick="javascript: window.location='/smartcardweb/bmjfjsp.do';"></li>
							
							<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h4.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h4a.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/h4.gif)"
							onclick="javascript:readCard();"
							></li> 
					 -->

					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
		<form action="/smartcardweb/getsidyquery.do" method="post" name="logonForm" >
		<input type="hidden" name="cardId" />
		<input type="hidden" name="txCnt" />
		<input type="hidden" name="cardBala" />
		
		<object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
								width="0" height="0"
										codebase="/smartcardweb/rf35.cab#version=2,0,0,7"></object>
	</body>
</html>

