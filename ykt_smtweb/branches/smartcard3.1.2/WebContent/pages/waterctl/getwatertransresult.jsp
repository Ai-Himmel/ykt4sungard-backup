<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>水控转账写卡</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
		String cardphyid = request.getAttribute("cardphyid") == null ? ""
				: request.getAttribute("cardphyid").toString();
		String money = request.getAttribute("money") == null ? "" : request
				.getAttribute("money").toString();					
		String cardBala = request.getAttribute("cardBala") == null ? ""
				: request.getAttribute("cardBala").toString();
		String waterBala = request.getAttribute("waterBala") == null ? ""
				: request.getAttribute("waterBala").toString();
        String txCnt = request.getAttribute("txCnt") == null ? ""
                : request.getAttribute("txCnt").toString();	
        String txCnt1 = request.getAttribute("txCnt1") == null ? ""
                : request.getAttribute("txCnt1").toString(); 	
         String sphone3 = request.getAttribute("sphone3") == null ? ""
                : request.getAttribute("sphone3").toString();
        String saddr = request.getAttribute("saddr") == null ? ""
                : request.getAttribute("saddr").toString();            
		String outCardAmount = request.getAttribute("outCardAmount") == null ? ""
				: request.getAttribute("outCardAmount").toString();
		String outCardAmount1 = request.getAttribute("outCardAmount1") == null ? ""
				: request.getAttribute("outCardAmount1").toString();
		String sdate3 = request.getAttribute("sdate3") == null ? ""
                : request.getAttribute("sdate3").toString();
        String stime3 = request.getAttribute("stime3") == null ? ""
                : request.getAttribute("stime3").toString();	
        String validatedate = request.getAttribute("validatedate") == null ? ""
                : request.getAttribute("validatedate").toString();	
        String ipServer= request.getAttribute("ipServer") == null ? ""
                : request.getAttribute("ipServer").toString();
        String drtpPort= request.getAttribute("drtpPort") == null ? ""
                : request.getAttribute("drtpPort").toString();
        String svrFunc= request.getAttribute("svrFunc") == null ? ""
                : request.getAttribute("svrFunc").toString();
        String price1= request.getAttribute("price1") == null ? "0": request.getAttribute("price1").toString();
        String price2= request.getAttribute("price2") == null ? "0": request.getAttribute("price2").toString();
        String price3= request.getAttribute("price3") == null ? "0": request.getAttribute("price3").toString();
		String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
		String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
		String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		String tradecode = request.getAttribute("tradecode")==null?"0":request.getAttribute("tradecode").toString();
		//String small_packet_number = KSConfiguration.getInstance().getProperty("small_packet_number","5"); 
		%>
		<script type="text/JavaScript">
		var serverbase = "http://"+'<%=webserverip%>'+":"+'<%=webserverport%>'+"/"+'<%=webserverapp%>'+"/";
		var device_port = <%=read_card_device_port%>;
		function writeCard(){
			var msg = document.getElementById("msg");
			var cardphyid = '<%=cardphyid%>';
			var money = '<%=money%>';
            var txCnt = '<%=txCnt%>';
            var txCnt1 = '<%=txCnt1%>';
            var sphone3 = '<%=sphone3%>';
            var saddr = '<%=saddr%>';
			var outCardAmount = '<%=outCardAmount%>';
			var outCardAmount1 = '<%=outCardAmount1%>';
			var sdate3 = '<%=sdate3%>';
            var stime3 = '<%=stime3%>';
            var ipServer= '<%=ipServer%>';
			var drtpPort= '<%=drtpPort%>';
			var svrFunc= '<%=svrFunc%>';
			var price1 = '<%=price1%>';
			var price2 = '<%=price2%>';
			var price3 = '<%=price3%>';
            var validatedate = '<%=validatedate%>';
			var url = serverbase+"getWaterTrans.do";
			var parms = "cardphyid="+cardphyid+"&money="+money+"&sphone3="+sphone3+"&saddr="+saddr;
			var ret = writeCardForm.all.RFScanner.CommonTransWriteCard(url,cardphyid,txCnt,outCardAmount,money,sdate3,stime3,ipServer,drtpPort,svrFunc,parms);
			if(ret==0){
				var tradecode ='<%=tradecode%>';
				var watertype = -1;
				if(tradecode=="1231"){
					watertype=5;
				}else if(tradecode=="1232"){
					watertype=3;
				}
				var wret = writeCardForm.all.RFScanner.WriteWaterCtlPacket(outCardAmount1,cardphyid,txCnt1,watertype,money,sdate3+stime3,price1,price2,price3,validatedate);
				if(wret==0){
					msg.innerHTML="水控转账成功，<br><br>转账金额 "+money+" 元，<br><br>一卡通卡余额 "+parseFloat(outCardAmount)/100+" 元，<br><br> 水控钱包卡余额 "+parseFloat(outCardAmount1)/100 +"元";
				}else{
					document.writeCardForm.submit();
				}
			}else if(ret==2){
				msg.innerHTML="水控转账失败!<br/><br/>失败原因：网络超时！请到卡务中心调整卡卡余额.";
			}else if(ret==-10){
				msg.innerHTML="水控转账失败!<br/><br/>失败原因：写卡失败，请返回后重新操作！";
			}else if(ret==-100){
				msg.innerHTML="水控转账失败!<br/><br/>失败原因：写卡失败，请返回后重新操作！";
			}else if(ret==-99){
				//中途拔卡
				alert("发生中途拔卡，请重新正确放置卡后，点击此确认按钮继续操作!");
				var ckret = writeCardForm.all.RFScanner.CheckTransProve(cardphyid,2,txCnt);
				if(ckret == 1){
					//没有写卡,重新写卡操作
					writeCard();
				}else if(ckret==0){
					var tradecode ='<%=tradecode%>';
					var watertype = -1;
					if(tradecode=="1231"){
						watertype=5;
					}else if(tradecode=="1232"){
						watertype=3;
					}
					var wret = writeCardForm.all.RFScanner.WriteWaterCtlPacket(outCardAmount1,cardphyid,txCnt1,watertype,money,sdate3+stime3,price1,price2,price3,validatedate);
					if(wret==0){
						msg.innerHTML="水控转账成功，<br><br>转账金额 "+money+" 元，<br><br>一卡通卡余额 "+parseFloat(outCardAmount)/100+" 元，<br><br> 水控钱包卡余额 "+parseFloat(outCardAmount1)/100 +"元";
					}else{
						document.writeCardForm.submit();
					}
				}else{
					//发生外部位置错误
					msg.innerHTML="水控转账失败!<br/><br/>失败原因：未能判断卡是否扣款成功<br><br>如果扣款成功了，请到卡务中心补写卡余额！";
				}
				
			}else if(ret==-3){
				msg.innerHTML="水控转账失败!<br/><br/>失败原因：请求无应答！请到卡务中心补写卡信息.";
			}else{
				msg.innerHTML="水控转账失败!<br/><br/>请到卡务中心调整卡余额.<br/><br/>失败原因："+writeCardForm.all.RFScanner.GetRequestRetInfo("errmsg");
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
	<body scroll="no" onload="javascript:writeCard();">
		<form action="/smartcardweb/rewritewaterpacket.do" method="post" name="writeCardForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/czjg.gif" width="314"
								height="82" />
								 <input type="hidden" name="cardphyid"
												value="<%=request.getAttribute("cardphyid") == null ? ""
								: request.getAttribute("cardphyid")%>" />
								<input type="hidden" name="outCardAmount"
															value="<%=request.getAttribute("outCardAmount") == null ? ""
								: request.getAttribute("outCardAmount")%>" />
														<input type="hidden" name="outCardAmount1"
															value="<%=request.getAttribute("outCardAmount1") == null ? ""
								: request.getAttribute("outCardAmount1")%>" />
								<input type="hidden" name="txCnt"
															value="<%=request.getAttribute("txCnt") == null ? ""
								: request.getAttribute("txCnt")%>" />
														<input type="hidden" name="txCnt1"
															value="<%=request.getAttribute("txCnt1") == null ? ""
								: request.getAttribute("txCnt1")%>" />
								<input type="hidden" name="sphone3"
															value="<%=request.getAttribute("sphone3") == null ? ""
								: request.getAttribute("sphone3")%>" />
								<input type="hidden" name="saddr"
															value="<%=request.getAttribute("saddr") == null ? ""
								: request.getAttribute("saddr")%>" />
								<input type="hidden" name="money"
															value="<%=request.getAttribute("money") == null ? ""
								: request.getAttribute("money")%>" />
								<input type="hidden" name="sdate3"
															value="<%=request.getAttribute("sdate3") == null ? ""
								: request.getAttribute("sdate3")%>" />
								<input type="hidden" name="stime3"
															value="<%=request.getAttribute("stime3") == null ? ""
								: request.getAttribute("stime3")%>" />
								<input type="hidden" name="validatedate"
															value="<%=request.getAttribute("validatedate") == null ? ""
								: request.getAttribute("validatedate")%>" />
							</div>

							<div id="content_input">
								<table width="70%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">

									<tr>
										<td height="320" align="center" class="样式13" id="msg">
											
											正在写卡、转账!请稍后...
											<br />(可能需要等待一段时间，请不要移动卡片！)
										</td>
									</tr>

								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center" >
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
				height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7" />
		</form>
	</body>
</html>



