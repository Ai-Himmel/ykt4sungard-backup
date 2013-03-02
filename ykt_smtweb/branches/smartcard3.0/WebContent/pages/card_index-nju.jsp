<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<html>
    <head>
        <title>一卡通综合查询系统</title>
        <meta http-equiv="Content-Type" content="text/html; charset=GBK" />
        <style type="text/css">
</style>
        <link href="pages/css/css.css" rel="stylesheet" type="text/css" />
    </head>

    <%
        String webserverip = KSConfiguration.getInstance().getProperty(
                "webserverip");
        String webserverport = KSConfiguration.getInstance().getProperty(
                "webserverport");
        String webserverapp = KSConfiguration.getInstance().getProperty(
                "webserverapp");
        String read_card_device_port = KSConfiguration.getInstance()
                .getProperty("read_card_device_port", "0");
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
               var cardid = logonForm.all.RFScanner.CardNo;
               var rrt = logonForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");    
               if(rrt == 0){
                  var limitret = logonForm.all.RFScanner.ReadCardConsumerLimit(cardid);              
                 if(limitret==0){      
                     logonForm.action='/smartcardweb/getconsumerlimitquery.do';
                     logonForm.all.cardphyno.value=cardid;            
                     logonForm.all.maxpercount.value=logonForm.all.RFScanner.getComsumerLimit("max_per_count");                     
                     logonForm.all.maxperday.value=logonForm.all.RFScanner.getComsumerLimit("max_per_day");      
                     logonForm.submit();
                  }else{
                     alert("读卡失败，请正确放置卡片...");
                     return false;
                  }
               }else{
                    alert("网络不通，请稍后重试...");
                    return false;
                }                
           }else{
               alert("读卡失败，请放置卡片...");
               return false;
           }
        }
        
      function readCardPocket(){
           var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
           var device_port = '<%=read_card_device_port%>'; 
           logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
           var ret=logonForm.all.RFScanner.DoScan();
           if(ret==0){
           //读卡成功
               var cardid = logonForm.all.RFScanner.CardNo;
               var rrt = logonForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");    
               if(rrt == 0){
                 var pktret = document.all.RFScanner.ReadCardPocket(1,cardid,"");      
                 if(pktret==0){
                     logonForm.action='/smartcardweb/cardtransbusiness.do';    
                     logonForm.all.cardphyno.value=cardid;                     
                     logonForm.all.reqcardbalance.value=logonForm.all.RFScanner.GetPacketInfo("bala");                     
                     logonForm.all.reqcardcnt.value=logonForm.all.RFScanner.GetPacketInfo("total_cnt");      
                     logonForm.submit();
                  }else{
                     alert("读卡失败，请正确放置新卡片...");
                     return false;
                  }
               }else{
                    alert("网络不通，请稍后重试...");
                    return false;
                }                
           }else{
               alert("读新卡失败，请放置新卡片...");
               return false;
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
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/count.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/counta.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/count.gif)"
                            onclick="javascript: window.location='/smartcardweb/queryact.do';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/detail.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/detaila.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/detail.gif)"
                            onclick="javascript: window.location='/smartcardweb/tradequery.do';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/jie.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/jiea.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/jie.gif)"
                            onclick="javascript: window.location='/smartcardweb/cancelloss.do';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/pass.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/passa.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/pass.gif)"
                            onclick="javascript: window.location='/smartcardweb/updatepwd.do';"></li>
                        

                    </ul>
                </div>
            </div>
            <div id="Layer3">
                <div id="mid_center">
                    <ul>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/xexg1.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/xexg2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/xexg1.gif)"
                            onclick="javascript:readCard();"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/wfcz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/wfcz2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/wfcz.gif)"
                            onclick="javascript: window.location='/smartcardweb/nettransbusiness.do';"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/lkzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/lkzz2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/lkzz.gif)"
                            onclick="javascript:readCardPocket();"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/kkzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/kkzz2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/kkzz.gif)"
                            onclick="javascript:window.location='/smartcardweb/cardcardbusiness.do';"></li>    
                            
                       <%if(request.getSession().getAttribute("cutid")==null){ %>
                         <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/fhcd.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/index.jsp';"></li>
                       <%}else{%>                
                          <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/reset.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/reseta.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/reset.gif)"
                            onclick="javascript: window.location='/smartcardweb/usrexit.do';"></li>
                       <%} %>
                       

                    </ul>
                </div>
            </div>
        </div>
        <div id="bottom"></div>
        <form action="/smartcardweb/getconsumerlimitquery.do" method="post"
            name="logonForm">
            <input type="hidden" name="cardphyno" />
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
