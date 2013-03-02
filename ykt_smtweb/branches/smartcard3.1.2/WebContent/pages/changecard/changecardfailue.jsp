<%@ page contentType="text/html;charset=GBK"%>
<html>
    <head>
        <title>新生换卡失败</title>
        <link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
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
        function ReadCard(){
            var message = writeCardForm.RFScanner.GetRequestRetInfo("errmsg");
            if(message=="新生换卡成功"){
                message = "正式卡写卡失败！<br><br>请到校园卡中心人工处理！";
            }
            if(message==""){
                 message = "新生换卡失败，未知原因！<br><br>请到校园卡中心人工处理！";
            }
            var msg = document.getElementById("msg");
            msg.innerHTML = "新生换卡失败！<br><br> 返回信息："+message+"<br><br>请到校园卡中心人工处理";
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
    <body scroll="no" onload="javascript:ReadCard();">
        <form action="" method="post" name="writeCardForm">
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
                                        <td height="320" align="center" class="样式13" id="msg">

                                        </td>
                                    </tr>

                                </table>
                            </div>
                            <div id="content_buttom">
                                <table>
                                    <tr>
                                        <td align="center">
                                            <a
                                                onclick="javascript: window.location='/smartcardweb/index.do';"
                                                onmouseout="MM_swapImgRestore()"
                                                onmouseover="MM_swapImage('cancel','','/smartcardweb/pages/images/backa.gif',1)"><img
                                                    src="/smartcardweb/pages/images/back.gif" name="cancel"
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

