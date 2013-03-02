<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <title>一卡通多媒体查询系统</title>
        <meta http-equiv="Content-Type" content="text/html; charset=GBK" />
        <link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
            type="text/css" />
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
     function  readCardPocket()
      {
        var serverbase = "http://"+'<%=webserverip%>'+":"+'<%=webserverport%>'+"/"+'<%=webserverapp%>'+"/";
         var device_port = '<%=read_card_device_port%>'; 
           logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
           var ret=logonForm.all.RFScanner.DoScan();
           if(ret==0){
           //读卡成功
        var cardno = document.all.RFScanner.CardNo;
        var rrt = logonForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
            if(rrt == 0){
                var ret = logonForm.all.RFScanner.ReadCardPocket(1,cardno,"");
                if(ret == 0){
                    var bala = logonForm.all.RFScanner.GetPacketInfo("bala");
                    logonForm.action='/smartcardweb/showcardpacket.do';
                    logonForm.all.money.value=bala;
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
            
             }else{
               alert("读卡失败，请放置卡片...");
           }
    }
    
    
     function readCardSidy()
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
                  var sidyno = logonForm.all.RFScanner.ReadCardSidyNo(cardid,"");
                 if(sidyno>=0){
                     logonForm.action='/smartcardweb/getsidyquery.do';
                     logonForm.all.cardno.value=cardid;
                     logonForm.all.sidyno.value=sidyno;
                     logonForm.submit();
                  }else{
                     alert("读卡失败，请正确放置卡片...");
                  }
               }else{
                    alert("网络不通，请稍后重试...");
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
                            onmouseout="this.style.background='url(/smartcardweb/pages/images/yhkw.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/yhkw.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/yhkwa.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/yhkw.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/yhkw.jsp';"></li>
                        <li
                            onmouseout="this.style.background='url(/smartcardweb/pages/images/xykw.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/xykw.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/xykwa.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/xykw.gif)"
                            onclick="javascript: window.location='/smartcardweb/xykw.do';"></li>
                        <li
                            onmouseout="this.style.background='url(/smartcardweb/pages/images/kye.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/kye.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/kyea.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/kye.gif)"
                            onclick="javascript: readCardPocket();"></li>
                        <li
                            onmouseout="this.style.background='url(/smartcardweb/pages/images/h5.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/h5.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/h5a.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/h5.gif)"
                            onclick="javascript: window.location='/smartcardweb/lossquery.do';"></li>

                    </ul>
                </div>
            </div>
            <div id="Layer3">
                <div id="mid_center">
                    <ul>

                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/h4.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/h4a.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/h4.gif)"
                            onclick="javascript: readCardSidy();"></li>
                        <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/xshk1.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/xshk2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/xshk1.gif)"
                            onclick="javascript: window.location='/smartcardweb/putinnewcard.do';"></li>
                        <li
                            onmouseout="this.style.background='url(/smartcardweb/pages/images/h2.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/h2.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/h2a.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/h2.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/news.htm';"></li>

                        <li
                            onmouseout="this.style.background='url(/smartcardweb/pages/images/h6.gif)'"
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/h6.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/h6a.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/h6.gif)"
                            onclick="javascript: window.location='/smartcardweb/pages/help.htm';"></li>

                    </ul>
                </div>
            </div>
        </div>
        <div id="bottom"></div>
        <form action="/smartcardweb/getsidyquery.do" method="post"
            name="logonForm">
            <input type="hidden" name="cardno" />
            <input type="hidden" name="sidyno" />
            <input type="hidden" name="money" />
            <object id="RFScanner"
                classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
                height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7"></object>
        </form>
    </body>
</html>

