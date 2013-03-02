<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<html>
	<head>
		<title>手机充值输入</title>
		<%
		String cardno = (String) request.getAttribute("cardno");
		String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
		String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
		String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		%>
		<script language="javascript">			
	        function addnum(num)
	        {
			if(putinForm.all.nowinput.value=="1" && putinForm.all.cellphone.value.length < 11 ){
				putinForm.all.cellphone.value+=num;
			}
			else if(putinForm.all.nowinput.value=="2" && putinForm.all.cellphone1.value.length < 11 ){
				putinForm.all.cellphone1.value+=num;
			}
	        }
	        function cancelnum()
	        {
			if(putinForm.all.nowinput.value=="1")
				putinForm.all.cellphone.value=putinForm.all.cellphone.value.substring(0,putinForm.all.cellphone.value.length-1);
			else if(putinForm.all.nowinput.value=="2")
				putinForm.all.cellphone1.value=putinForm.all.cellphone1.value.substring(0,putinForm.all.cellphone1.value.length-1);	
	        }
		   	 function readCard(){
		   	 	if(putinForm.all.cellphone.value==''){
		   	 		alert("请输入充值手机号！");
		   	 		putinForm.all.cellphone.focus();
		   	 		return false;
		   	 	}
		   	 	if(putinForm.all.cellphone1.value==''){
		   	 		alert("请输入充值确认手机号！");
		   	 		putinForm.all.cellphone1.focus();
		   	 		return false;
		   	 	}
		   	 	if(!fucCheckNUM(putinForm.all.cellphone.value)){
		   	 	 	alert("手机号码为数字！");
		   	 		putinForm.all.cellphone.focus();
		   	 		return false;
		   	 	}
		   	 	if(!fucCheckNUM(putinForm.all.cellphone1.value)){
		   	 	 	alert("手机号码为数字！");
		   	 		putinForm.all.cellphone1.focus();
		   	 		return false;
		   	 	}
		   	 	if(putinForm.all.cellphone.value.length<11){
		   	 		alert("手机号码长度不正确！");
		   	 		putinForm.all.cellphone.focus();
		   	 		return false;
		   	 	}
		   	 	if(putinForm.all.cellphone1.value.length<11){
		   	 		alert("手机号码长度不正确！");
		   	 		putinForm.all.cellphone1.focus();
		   	 		return false;
		   	 	}
		   	 	if(putinForm.all.cellphone.value!=putinForm.all.cellphone1.value){
		   	 		alert("两次输入的手机号不相同！");
		   	 		putinForm.all.cellphone.focus();
		   	 		return false;
		   	 	}
		   	 	if(putinForm.all.money.value==''){
		   	 		alert("请选择充值金额！");
		   	 		putinForm.all.money.focus();
		   	 		return false;
		   	 	}
		   	 	var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
				var device_port = '<%=read_card_device_port%>';
		       	var cardId ='<%=cardno%>';
				putinForm.all.RFScanner.PortNo=device_port;
				var rrt = putinForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
				if(rrt == 0){
					var ret = putinForm.all.RFScanner.ReadCardPocket(1,cardId,"");
					if(ret == 0){
						var bala = putinForm.all.RFScanner.GetPacketInfo("bala");
						var cxCnt =  putinForm.all.RFScanner.GetPacketInfo("total_cnt");
						if(parseInt(putinForm.all.money.value)*100<=parseInt(bala)){
							putinForm.all.cardId.value=cardId;
							putinForm.all.cardBala.value = bala;
							putinForm.all.txCnt.value = cxCnt;
							putinForm.submit();
						}else{
							alert("充值金额超过了卡片余额");
							return false;
						}
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
		       }
       
		     function fucCheckNUM(NUM)
			{
			 var i,j,strTemp;
			 strTemp="0123456789";
			 if ( NUM.length== 0)
			  return true
			 for (i=0;i<NUM.length;i++)
			 {
			  j=strTemp.indexOf(NUM.charAt(i)); 
			  if (j==-1)
			  {
			  //说明有字符不是数字
			   return false;
			  }
			 }
			 //说明是数字
			 return true;
			}
   		 </script>
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
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<style type="text/css">
			.样式12 {
			font-family: "宋体"; 
			color: #000000; 
			font-size: 14px;
			}
			.样式11 {
			font-family: "宋体"; 
			color: #000000; 
			font-size: 16px;
			font-weight: bold;
			}
			.样式13 {
			font-family: "宋体"; 
			color: #000000; 
			font-size: 20px;
			font-weight: bold;
			}
			.样式10 {
			font-family: "黑体"; 
			color: #606060; 
			font-size: 20px;
			font-weight: bold;			
			}
			.样式9 {
			font-family: "宋体"; 
			color: #ff0000; 
			font-size: 18px;
			}
			
		</style>
	</head>
	<body scroll="no">
		<form action="/smartcardweb/mobileputin.do" method="post"
			name="putinForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="login">
						<div id="login_left"></div>
						<div id="login_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/input.gif" width="343"
									height="57" />
							</div>
							<div>
								<ul>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/0.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/0a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/0.gif)"
										onclick="javascript:addnum(0)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/1.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/1a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/1.gif)"
										onclick="javascript:addnum(1)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/2.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/2a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/2.gif)"
										onclick="javascript:addnum(2)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/3.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/3a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/3.gif)"
										onclick="javascript:addnum(3)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/4.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/4a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/4.gif)"
										onclick="javascript:addnum(4)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/5.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/5a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/5.gif)"
										onclick="javascript:addnum(5)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/6.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/6a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/6.gif)"
										onclick="javascript:addnum(6)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/7.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/7a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/7.gif)"
										onclick="javascript:addnum(7)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/8.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/8a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/8.gif)"
										onclick="javascript:addnum(8)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/9.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/9a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/9.gif)"
										onclick="javascript:addnum(9)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/del.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/dela.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/del.gif)"
										onclick="javascript:cancelnum()"></li>
								</ul>
							</div>
							<div id="login_input">
								<table width="560" border="0" cellpadding="0" cellspacing="0">
									<tr>
										<td width="206" align="right">
											<img src="/smartcardweb/pages/images/phone.gif"
												width="114" height="24" align="absmiddle"/>
											<input type="hidden" name="nowinput" value="1" />
											<input type="hidden" name="cardId" />
											<input type="hidden" name="cardBala" />
											<input type="hidden" name="txCnt" />
										</td>
										<td width="314">
											<input name="cellphone" type="text" class="样式11"
												onfocus="javascript:putinForm.nowinput.value='1'" size="20"
												maxlength="11" />
										</td>
									</tr>
									<tr>
										<td width="206" align="right">
											<img src="/smartcardweb/pages/images/phone1.gif"
												width="114" height="24" align="absmiddle"/>
										</td>
										<td width="314">
											<input name="cellphone1" type="text" class="样式11"
												onfocus="javascript:putinForm.nowinput.value='2'" size="20"
												maxlength="11" />
										</td>
									</tr>									
									<tr>
										<td align="right">
											<img src="/smartcardweb/pages/images/money1.gif"
												width="114" height="24" align="absmiddle"/>
										</td>
										<td>
											<input name="money" type="text" class="样式11" size="20"
												maxlength="4" readonly="readonly"/>
										</td>
									</tr>
									<tr>
										<td class="info" colspan="2" align="center">
											<font class="样式13"><a href="#" onclick="javascript: putinForm.all.money.value=30">30元</a>&nbsp;</font>
											<font class="样式13"><a href="#" onclick="javascript: putinForm.all.money.value=50">50元</a>&nbsp;</font>
											<font class="样式13"><a href="#" onclick="javascript: putinForm.all.money.value=100">100元</a>&nbsp;</font>
											<font class="样式13"><a href="#" onclick="javascript: putinForm.all.money.value=300">300元</a></font>
											<html:errors />&nbsp;
										</td>
									</tr>
								</table>
							</div>
							<div id="login_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:readCard();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/main.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
													src="/smartcardweb/pages/images/cancel.gif" name="cancel"
													width="109" height="48" border="0" id="cancel" /> </a>
										</td>
									</tr>
								</table>
							</div>
						</div>
						<div id="login_right"></div>
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
