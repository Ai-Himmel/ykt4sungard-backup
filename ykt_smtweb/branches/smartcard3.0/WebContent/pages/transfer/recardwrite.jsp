<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <title>写卡失败补写</title>
        <link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
        <% String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
        String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
        String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
        String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
        %>
        <script type="text/JavaScript">
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
    <script language="javascript">
        
        function ReWriteCard(){     
            var ret ;
            var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
            var device_port = '<%=read_card_device_port%>';
            document.all.RFScanner.PortNo=device_port;      
            ret = document.all.RFScanner.RewriteCardInfo();
            if(ret ==0){        
             window.location='/smartcardweb/pages/transfer/transfersuccess.jsp';  
            }else{
               NoWriteCard();
            }
        }
        function NoWriteCard(){
             var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
            var device_port = <%=read_card_device_port%>;
            var sphone3 = writeCardForm.all.RFScanner.GetRequestRetInfo("refno");
            var saddr = writeCardForm.all.RFScanner.GetRequestRetInfo("radomstr");
            var cardBala = writeCardForm.all.RFScanner.GetRequestRetInfo("cardBala");
            var outCardAmount = writeCardForm.all.RFScanner.GetRequestRetInfo("OutCardAmount");            
          var params = "sphone3="+sphone3+"&saddr="+saddr+"&cardBala="+cardBala+"&outCardAmount="+outCardAmount;
            var ret = 0;
            ret = writeCardForm.all.RFScanner.ReportWriteCardFailure(serverbase+"dealTransCardExp.do",params);
            if(ret == 0){
                window.location='/smartcardweb/pages/transfer/cardwriteerror.jsp';
            }else{
                window.location='/smartcardweb/pages/transfer/cardwriteerror.jsp';
            }
        }
    </script>
        <style type="text/css">
        .样式5 {
            font-family: "宋体"; 
            color: #000000;
            font-size: 18px;
        }
        .样式13 {
            font-family: "黑体"; 
            color: #ff0000; 
            font-size: 18px; 
            }
        </style>
    </head>
    <body scroll="no">
        <form action="/smartcardweb/sidyList.do" method="post"
            name="writeCardForm">
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
                                <table width="50%" border="0" align="center" cellpadding="0"
                                    cellspacing="0" class="box">

                                    <tr>
                                        <td height="320" align="center" class="样式13">
                                            写卡失败！请正确放置卡片！
                                            <br/>
                                            <br/>
                                            按
                                            <b>确定</b> 补写卡！如果仍不行，
                                            <b>必须</b> 按
                                            <b>取消</b> 退出。
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
                height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7" />
        </form>
    </body>
</html>

