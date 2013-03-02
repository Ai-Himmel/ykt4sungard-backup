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
	    String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
        String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
        String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
        String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
	%>
	<script language="javascript">
	 function readCard()
      {
         var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
         var device_port = '<%=read_card_device_port%>'; 
         document.all.RFScanner.PortNo=device_port;//读卡器端口设置
         var ret=document.all.RFScanner.DoScan();
         if(ret==0){
         //读卡成功
           	var cardphyid = document.all.RFScanner.CardPhyID;	
               logonForm.all.cardphyid.value=cardphyid;
               logonForm.submit();                     
         }else{
             alert("读卡失败，请放置卡片...");
         }
      }
      
        function readCardPocket(){            
                var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
                var device_port = '<%=read_card_device_port%>';
                document.all.RFScanner.PortNo=device_port;
                
                 var ret=document.all.RFScanner.DoScan();
                   if(ret==0){//读卡成功         
                      var cardphyid = document.all.RFScanner.CardPhyID;
                       var cret = document.all.RFScanner.ReadCardPocket(1,cardphyid);
                      
                    if(cret == 0){
                        var bala = document.all.RFScanner.GetPacketInfo("cardbal");
                        // var ksfxyf_waterBala = document.all.RFScanner.GetWaterCtlPacketInfo("money");
                         moneyForm.all.bala.value=bala;
                         moneyForm.submit();                                
                    }else if(ret == 1){
                        alert("请放置卡片...");
                        return false;
                    }else{
                        alert("请正确放置卡片...");
                        return false;
                    }
                   }else{
                       alert("读卡失败，请放置卡片...");
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
							onclick="javascript: window.location='/smartcardweb/pages/news.jsp';"></li>
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
							onclick="javascript: window.location='/smartcardweb/pages/help.jsp';"></li>
					</ul>
				</div>
			</div>
			<div id="Layer3">
				<div id="mid_center">
					<ul>							
							<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h4.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h4a.gif)'"
							style="cursor:hand; background:url(/smartcardweb/pages/images/h4.gif)"
							onclick="javascript:readCard();"
							></li> 
							<li
                            onmouseout="this.style.background='url(/smartcardweb/pages/images/kye.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/kye.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/kyea.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/kye.gif)"
                            onclick="javascript: readCardPocket();"></li>
							<!--onclick="javascript: window.location='/smartcardweb/getsidyquery.do';" -->

					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
		<form action="/smartcardweb/getsidyquerynew.do" method="post" name="logonForm" >
		<input type="hidden" name="cardphyid" />
		<input type="hidden" name="sidyno" />		
        <input type="hidden" name="bala" />       
	   </form>
	   <form name="moneyForm" action="/smartcardweb/waterbalayjz.do" method="post">
            <input type="hidden" name="bala" value="0" />
            <input type="hidden" name="sslrsb_waterBala" value="0" />
            <input type="hidden" name="ksfxyf_waterBala" value="0" />
       </form>
        <object id="RFScanner"
                    classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
                                width="0" height="0"
                                        codebase="/smartcardweb/rf35.cab#version=2,0,0,7"></object>
	</body>
</html>

