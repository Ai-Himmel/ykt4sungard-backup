<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.ConfigMenu" %>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html>
	<head>
		<title>校园卡务</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<style type="text/css">

</style>
		<link href="pages/css/css.css" rel="stylesheet" type="text/css" />
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
           logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
           var ret=logonForm.all.RFScanner.DoScan();
           if(ret==0){
           //读卡成功
               var CardPhyId = logonForm.all.RFScanner.CardPhyID;
                 var limitret = logonForm.all.RFScanner.ReadCardConsumerLimit(CardPhyId);              
                 if(limitret==0){      
                     logonForm.action='/smartcardweb/getconsumerlimitquery.do';
                     logonForm.all.CardPhyId.value=CardPhyId;                     
                     logonForm.all.maxpercount.value=logonForm.all.RFScanner.getComsumerLimit("single_max_amt");                     
                     logonForm.all.maxperday.value=logonForm.all.RFScanner.getComsumerLimit("day_max_amt");      
                     logonForm.submit();
                  }else{
                     alert("读卡失败，请正确放置卡片...");
                     return false;
                  }             
           }else{
               alert("读卡失败，请放置卡片...");
               return false;
           }
        }
     function readCardsingle()
     {
        var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
        var device_port = '<%=read_card_device_port%>';         
        logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
        var ret=logonForm.all.RFScanner.DoScan();
        if(ret==0){
        //读卡成功
            var CardPhyId = logonForm.all.RFScanner.CardPhyID;
              var limitret = logonForm.all.RFScanner.ReadCardConsumerLimit(CardPhyId);              
              if(limitret==0){      
                  logonForm.action='/smartcardweb/getconsumerlimitquerysingle.do';
                  logonForm.all.CardPhyId.value=CardPhyId;                     
                  logonForm.all.maxpercount.value=logonForm.all.RFScanner.getComsumerLimit("single_max_amt");                     
                  logonForm.all.maxperday.value=logonForm.all.RFScanner.getComsumerLimit("day_max_amt");      
                  logonForm.submit();
               }else{
                  alert("读卡失败，请正确放置卡片...");
                  return false;
               }             
        }else{
            alert("读卡失败，请放置卡片...");
            return false;
        }
     }
        
    </script> 

    <body scroll="no">
        <div id="mid_top"></div>
        <div id="middle">
            <div id="Layer2">
                <div id="mid_center1">
                    <ul>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/count.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/counta.gif)'"
                            style="cursor:pointer; background: url(/smartcardweb/pages/images/count.gif); <% if (!ConfigMenu.getMenuStatus("compusBiz_account")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/queryact.do';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/detail.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/detaila.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/detail.gif); <% if (!ConfigMenu.getMenuStatus("compusBiz_tradelog")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/tradequery.do';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/jie.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/jiea.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/jie.gif); <% if (!ConfigMenu.getMenuStatus("compusBiz_cancelLost")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/cancelloss.do';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/pass.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/passa.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/pass.gif); <% if (!ConfigMenu.getMenuStatus("compusBiz_changePassword")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/updatepwd.do';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/score.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/scorea.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/score.gif); <% if (!ConfigMenu.getMenuStatus("compusBiz_score_kingosoft")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/pages/thirdsys/score_kingosoft.jsp';"></li>
                    </ul>
                </div>
            </div>
            <div id="Layer3">
                <div id="mid_center2">
                    <ul>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/xexg1.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/xexg2.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/xexg1.gif); <% if (!ConfigMenu.getMenuStatus("compusBiz_cardLimit")) { out.print(" display:none; "); }%>"
                            onclick="javascript:readCard();"></li>
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/xexg1.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/xexg2.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/xexg1.gif); <% if (!ConfigMenu.getMenuStatus("compusBiz_cardLimitSingle")) { out.print(" display:none; "); }%>"
                            onclick="javascript:readCard();"></li>
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/gxkxx.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/gxkxxa.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/gxkxx.gif); <% if (!ConfigMenu.getMenuStatus("compusBiz_updateCardinfo")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/getCardInfo.do';"></li>
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/jssq.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/jssq2.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/jssq.gif); <% if (!ConfigMenu.getMenuStatus("compusBiz_cancelLock")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/cancellock.do';"></li>
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/xshk1.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/xshk2.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/xshk1.gif); <% if (!ConfigMenu.getMenuStatus("compusBiz_changecard")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/putinnewcard.do';"></li>
                            
                       <%if(request.getSession().getAttribute("cardphyid")==null){ %>
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/fhcd.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/index.jsp';"></li>
                       <%}else{%>
                          <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/reset.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/reseta.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/reset.gif)"
                            onclick="javascript: window.location='/smartcardweb/usrexit.do';"></li>
                       <%} %>
                       

                    </ul>
                </div>
            </div>
        </div>
        <div id="bottom"></div>
        <form action="/smartcardweb/getconsumerlimitquery.do" method="post"
            name="logonForm">
            <input type="hidden" name="CardPhyId" />
            <input type="hidden" name="maxpercount" />
            <input type="hidden" name="maxperday" />
            <input type="hidden" name="reqcardbalance" />
            <input type="hidden" name="reqcardcnt" />
            <object id="RFScanner"
                classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
                height="0"></object>
        </form>
    </body>
</html>
