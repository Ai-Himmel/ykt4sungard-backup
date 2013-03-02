<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>转账写卡</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
			String oldCardBalance = request.getAttribute("oldCardBalance") == null ? ""
					: request.getAttribute("oldCardBalance").toString();

			String reqcardno = request.getAttribute("reqcardno") == null ? ""
					: request.getAttribute("reqcardno").toString();

			String reqcardcnt = request.getAttribute("reqcardcnt") == null ? ""
					: request.getAttribute("reqcardcnt").toString();

			String outCardAmount = request.getAttribute("outCardAmount") == null ? ""
					: request.getAttribute("outCardAmount").toString();
					
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
		function docancel(){
		  if(confirm("老卡所扣款还未写入新卡，是否确认直接返回？")){
		      window.location='/smartcardweb/main.do';
			}
		}
		function doCardCharge(){
            var cardId ='<%=reqcardno%>';
            var out_card_amount = '<%=outCardAmount%>';
            var tx_cnt = '<%=reqcardcnt%>';
            var device_port = '<%=read_card_device_port%>';
            var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
            writeCardForm.all.RFScanner.PortNo=device_port;
            var rrt = writeCardForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");        
           if(rrt == 0){
            var ret = writeCardForm.all.RFScanner.ReadCardPocket(1,cardId,"");
            if(ret == 0){
                    var doworkret = writeCardForm.all.RFScanner.CardTransWriteCard(out_card_amount,cardId,tx_cnt);
                    if(doworkret == 0){
                    //写卡成功
                        window.location='/smartcardweb/pages/cardtrans/cardwritesuccess.jsp'; 
	                }else if(doworkret == 2){
	                    //写卡失败
	                     writeCardForm.action='/smartcardweb/cardtransrewritecard.do';
                        writeCardForm.submit();
	                }else if(doworkret == 10){
                        //写卡失败
                         writeCardForm.action='/smartcardweb/cardtransrewritecard.do';
                         writeCardForm.submit();       
	                }else{
	                    window.location='/smartcardweb/pages/cardtrans/gettransfailue.jsp';   
	                }
            }else if(ret == 1){
                alert("请放置卡片...");
            }else{
                alert("请正确放置卡片...");
            }
            }else{
                alert("网络不通，请稍后重试...");
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

											老卡金额已扣除,扣款金额为<%=Float.parseFloat(oldCardBalance) / 100%>元
											<br>
											<br>
											下一步写校园卡，点击确认前，请将新卡放置于读卡器上
											<br />
											<br>
											(确认后可能需要等待一段时间，请不要移动卡片！)

											<input type="hidden" name="outCardAmount"
												value="<%=request.getAttribute("outCardAmount") == null ? "0"
					: request.getAttribute("outCardAmount")%>" />

											<input type="hidden" name="reqcardno"
												value="<%=request.getAttribute("reqcardno") == null ? "0"
					: request.getAttribute("reqcardno")%>" />

											<input type="hidden" name="reqcardcnt"
												value="<%=request.getAttribute("reqcardcnt") == null ? ""
					: request.getAttribute("reqcardcnt")%>" />
										</td>
									</tr>

								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:doCardCharge();"
												onmouseup="MM_swapImgRestore()"
												onmouseout="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
                                            <a
                                                onclick="javascript:docancel();"
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



