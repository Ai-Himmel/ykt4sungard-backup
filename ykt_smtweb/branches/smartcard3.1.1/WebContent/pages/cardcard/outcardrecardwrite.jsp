<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
    <head>
        <title>����ת�˲�д��</title>
        <link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
            type="text/css" />
        <%
             String outcardphyno =  request.getAttribute("outcardphyno") == null ? "" : request
                    .getAttribute("outcardphyno").toString();
            String outcardbalance =  request.getAttribute("outcardbalance") == null ? "" : request
                    .getAttribute("outcardbalance").toString();
            String outcardcnt =  request.getAttribute("outcardcnt") == null ? "" : request
                    .getAttribute("outcardcnt").toString();
            String money = request.getAttribute("money") == null ? "" : request
                    .getAttribute("money").toString();  
            String outCardAmount = request.getAttribute("outCardAmount") == null ? ""
                    : request.getAttribute("outCardAmount").toString();        
            String sdate3 =request.getAttribute("sdate3") == null ? ""
                    : request.getAttribute("sdate3").toString();
			String stime3 = request.getAttribute("stime3") == null ? ""
                    : request.getAttribute("stime3").toString();
			String ipServer= request.getAttribute("ipServer") == null ? ""
                    : request.getAttribute("ipServer").toString();
            String drtpPort= request.getAttribute("drtpPort") == null ? ""
                    : request.getAttribute("drtpPort").toString();
            String svrFunc= request.getAttribute("svrFunc") == null ? ""
                    : request.getAttribute("svrFunc").toString();
              String webserverip = KSConfiguration.getInstance().getProperty(
                    "webserverip");
            String webserverport = KSConfiguration.getInstance().getProperty(
                    "webserverport");
            String webserverapp = KSConfiguration.getInstance().getProperty(
                    "webserverapp");

            String read_card_device_port = KSConfiguration.getInstance()
                    .getProperty("read_card_device_port", "0");    
        %>
        <script type="text/JavaScript">     
        function NoWriteCard(){
            if(confirm("ת�������ۿ��δд��ת�뿨���Ƿ�ȷ��ֱ�ӷ��أ�")){
               window.location='/smartcardweb/pages/cardcard/gettransfailue.jsp'; 
            }
        }
        function ReWriteCard(){ 
            var outcardphyno ='<%=outcardphyno%>';
            var outCardAmount = '<%=outCardAmount%>';
            var outcardcnt = '<%=outcardcnt%>';
            var t_money = '<%=money%>';
            var sdate3= '<%=sdate3%>';
			var stime3= '<%=stime3%>';
			var ipServer= '<%=ipServer%>';
			var drtpPort= '<%=drtpPort%>';
			var svrFunc= '<%=svrFunc%>';
            var device_port = '<%=read_card_device_port%>';
            var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
            writeCardForm.all.RFScanner.PortNo=device_port;
            var rrt = writeCardForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");        
           if(rrt == 0){
            var ret = writeCardForm.all.RFScanner.ReadCardPocket(1,outcardphyno);
            if(ret == 0){
                 var doworkret = writeCardForm.all.RFScanner.CardTransWriteCard(outCardAmount,outcardphyno,outcardcnt,t_money,sdate3,stime3,ipServer,drtpPort,svrFunc);
                 if(doworkret == 0){
                 //д���ɹ�
                     window.location='/smartcardweb/pages/cardcard/cardwritesuccess.jsp'; 
                 }else{
                     window.location='/smartcardweb/pages/cardcard/gettransfailue.jsp';   
                 }
            }else if(ret == 1){
                alert("����ÿ�Ƭ...");
            }else{
                alert("����ȷ���ÿ�Ƭ...");
            }
            }else{
                alert("���粻ͨ�����Ժ�����...");
            }           
        }
        function MM_swapImgRestore() { //v3.0
          var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
        }
        
        function MM_preloadImages() { //v3.0
          var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
            var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
            if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
        }
        
        function MM_findObj(n, d) { //v4.01
          var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
            d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
          if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
          for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
          if(!x && d.getElementById) x=d.getElementById(n); return x;
        }
        
        function MM_swapImage() { //v3.0
          var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
           if ((x=MM_findObj(a[i]))!=null){document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; x.src=a[i+2];}
        }
        </script>
        <style type="text/css">
		.��ʽ5 {
		    font-family: "����";
		    color: #000000;
		    font-size: 18px;
		}
		
		.��ʽ13 {
		    font-family: "����";
		    color: #ff0000;
		    font-size: 18px;
		}
</style>
    </head>
    <body scroll="no">
        <form action="/smartcardweb/cardtransnext.do" method="post" name="writeCardForm">
            <div id="mid_top"></div>
            <div id="middle">
                <div id="Layer1">
                    <div id="content">
                        <div id="content_left"></div>
                        
                        <div id="content_middle">
                            <div align="center">
                                <img src="/smartcardweb/pages/images/czjg.gif" width="314"
                                height="82" />
                            </div>
                            <div id="content_input">
                                <table width="70%" border="0" align="center" cellpadding="0"
                                    cellspacing="0" class="box">
                                    <tr>
                                        <td height="320" align="center" class="show">
                                            д�����ʧ��,��Ҫ��д������ȷ���ÿ�Ƭ��
                                            <br />
                                            <br />
                                                    �� <b><font class="showbig">ȷ��</font></b> ��д��������Բ��У�
                                            ��  <b><font class="showbig">ȡ��</font></b> �˳���
                                       <input type="hidden" name="money" value="<%=money%>" />
                                       <input type="hidden" name="outcardphyno" value="<%=outcardphyno%>" />
                                       <input type="hidden" name="outcardbalance" value="<%=outcardbalance%>" />
                                       <input type="hidden" name="outcardcnt" value="<%=outcardcnt%>" />
                                       <input type="hidden" name="outCardAmount" value="<%=outCardAmount%>" />
                                       <input type="hidden" name="sdate3" value="<%=sdate3%>" />
										<input type="hidden" name="stime3" value="<%=stime3%>" />
                                        </td>
                                    </tr>

                                </table>
                            </div>
                            <div id="content_buttom">
                                <table>
                                    <tr>
                                        <td align="center">
                                            <a onclick="javascript:ReWriteCard();"
                                                onmouseup="MM_swapImgRestore()"
                                                onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
                                                    src="/smartcardweb/pages/images/send.gif" name="send"
                                                    width="109" height="48" border="0" id="send" /> </a>
                                        </td>
                                        <td>
                                            <a onclick="javascript:NoWriteCard();"
                                                onmouseup="MM_swapImgRestore()"
                                                onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
                                                    src="/smartcardweb/pages/images/cancel.gif" name="cancel"
                                                    width="109" height="48" border="0" id="cancel" /> </a>
                                        </td>
                                    </tr>
                                </table>
                            </div>
                        </div>
                        <div id="content_right"></div>
                    </div>
                </div>
            </div>
            <div id="bottom"></div>
            <object id="RFScanner"
                classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
                height="0" />
        </form>
    </body>
</html>

