<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
    <head>
        <title>卡卡转账扣</title>
        <link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
            type="text/css" />
        <%
            String oldCardNo = request.getAttribute("oldCardNo") == null ? ""
                    : request.getAttribute("oldCardNo").toString();
            String oldCardBalance = request.getAttribute("oldCardBalance") == null ? "" : request
                    .getAttribute("oldCardBalance").toString();
            String oldCardPwd = request.getAttribute("oldCardPwd") == null ? ""
                    : request.getAttribute("oldCardPwd").toString();
            String newCardName = request.getAttribute("newCardName") == null ? ""
                    : request.getAttribute("newCardName").toString();
            
        %>
        <script type="text/JavaScript">     
        function ReWriteCard(){
            var old_card_no = '<%=oldCardNo%>';
            var old_card_balance='<%=oldCardBalance%>';
            var old_card_pwd='<%=oldCardPwd%>';
            var new_card_name = '<%=newCardName%>';
            
            var ret = writeCardForm.all.RFScanner.getMoneyFromOldCard(old_card_no,old_card_balance,old_card_pwd,new_card_name);
            if(ret==0){//扣款成功
                writeCardForm.action='/smartcardweb/cardtransnext.do';
                writeCardForm.submit();                
            }else{//扣款失败            
                window.location='/smartcardweb/pages/cardtrans/oldcardwriteerror.jsp';
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
        <form action="/nettransresverse.do" method="post" name="writeCardForm">
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
                                <table width="60%" border="0" align="center" cellpadding="0"
                                    cellspacing="0" class="box1">
                                    <tr>
                                        <td height="320" align="center" class="样式13">
                                            扣卡金额失败,需要补写！请正确放置老卡片！
                                            <br />
                                            <br />
                                                    按
                                            <b>确定</b> 重扣卡！如果仍不行，
                                            <b>按取消</b> 退出。
                                         <input type="hidden" name="oldCardNo"
                                                value="<%=request.getAttribute("oldCardNo") == null ? "0"
                    : request.getAttribute("oldCardNo")%>" />
                                            <input type="hidden" name="oldCardBalance"
                                                value="<%=request.getAttribute("oldCardBalance") == null ? "0"
                    : request.getAttribute("oldCardBalance")%>" />
                                            <input type="hidden" name="oldCardPwd"
                                                value="<%=request.getAttribute("oldCardPwd") == null ? ""
                    : request.getAttribute("oldCardPwd")%>" />
                                            <input type="hidden" name="reqcardno"
                                                value="<%=request.getAttribute("reqcardno") == null ? "0"
                    : request.getAttribute("reqcardno")%>" />
                                            <input type="hidden" name="reqcardBalance"
                                                value="<%=request.getAttribute("reqcardBalance") == null ? "0"
                    : request.getAttribute("reqcardBalance")%>" />
                                            <input type="hidden" name="reqcardcnt"
                                                value="<%=request.getAttribute("reqcardcnt") == null ? ""
                    : request.getAttribute("reqcardcnt")%>" />
                                            <input type="hidden" name="serialNo"
                                                value="<%=request.getAttribute("serialNo") == null ? ""
                    : request.getAttribute("serialNo")%>" />
                                            <input type="hidden" name="sdate3"
                                                value="<%=request.getAttribute("sdate3") == null ? ""
                    : request.getAttribute("sdate3")%>" />
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

