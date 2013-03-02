
<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html>
	<head>
		<title>一卡通综合查询系统</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
	</head>
	<%
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
	%>
	<script language="javascript">
	 function readCard()
        {   
          var device_port = <%=read_card_device_port%>;           
          logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
           var ret=logonForm.all.RFScanner.DoScan();
           if(ret==0){//读卡成功
              logonForm.all.cardno.value=document.all.RFScanner.CardNo;
              //alert(logonForm.all.cardno.value);
              logonForm.submit();
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
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h1.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h1.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h1a.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/h1.gif)"
							onclick="javascript: window.location='/smartcardweb/logsys.do';"></li>
							
							<!-- onclick="javascript:readCard();"-->
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
						<!-- <li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/bmjf.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/bmjf.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/bmjfa.gif)'"
							style="cursor: hand; background: url(/smartcardweb/pages/images/bmjf.gif)"
							onclick="javascript: window.location='/smartcardweb/bmjfjsp.do';"></li>-->
							
							<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h4.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h4a.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/h4.gif)"
							onclick="javascript:readCard();"
							></li> 
							<!--onclick="javascript: window.location='/smartcardweb/getsidyquery.do';" -->

					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
		<form action="/smartcardweb/getsidyquery.do" method="post" name="logonForm" >
		<input type="hidden" name="cardno" />
		<object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
								width="0" height="0"
										codebase="/smartcardweb/rf35.cab#version=2,0,0,7"></object>
	</form>
	</body>
</html>

