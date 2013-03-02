
<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>转账输入</title>
		<%
		String cardno = (String) request.getAttribute("cardno");
		String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
		String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
		String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		%>
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
			font-size: 18px;
			font-weight: bold;
			}
		</style>
		<script language="javascript">
		function readCard(){
    	    if(putinForm.all.chargeID.value==''){
    	 		alert("请输入网络帐号！");
    	 		putinForm.all.chargeID.focus();
    	 		return false;
    	 	}
    	 	
    	 	if(putinForm.all.money.value==''){
    	 		alert("请输入转账金额！");
    	 		putinForm.all.money.focus();
    	 		return false;
    	 	}
    	 	
    	 	if(!fucCheckNUM(putinForm.all.money.value)){
    	 	 	alert("转账金额为数字！");
    	 		putinForm.all.money.focus();
    	 		return false;
    	 	}
    	 	
    	 	if(putinForm.all.money.value<=0){
    	 		alert("转账金额应该大于0！");
    	 		putinForm.all.money.focus();
    	 		return false;
    	 	}
    	 	
    	 	if(putinForm.all.money.value>1000){
    	 		alert("转账金额过大！");
    	 		putinForm.all.money.focus();
    	 		return false;
    	 	}
    	 	var serverbase = "http://"+'<%=webserverip%>'+":"+'<%=webserverport%>'+"/"+'<%=webserverapp%>'+"/";
			var device_port = '<%=read_card_device_port%>';
        	var cardId ='<%=cardno%>';
			putinForm.all.RFScanner.PortNo=device_port;
			var rrt = putinForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");//取密要
			if(rrt == 0){
				var ret = putinForm.all.RFScanner.ReadCardPocket(1,cardId,"");
				if(ret == 0){
					var bala = putinForm.all.RFScanner.GetPacketInfo("bala");
					var cxCnt =  putinForm.all.RFScanner.GetPacketInfo("total_cnt");
					if(parseInt(document.all.money.value)*100<=parseInt(bala)){
						putinForm.all.cardId.value=cardId;
						putinForm.all.cardBala.value = bala;
						putinForm.all.txCnt.value = cxCnt;
						putinForm.submit();
					}else{
						alert("转账金额超过了卡片余额");
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
        function addnum(num)
        {
			if(putinForm.nowinput.value=="1" ){
				if(putinForm.locknum.value=="1"){
					putinForm.chargeID.value+=num;
				}else{
					putinForm.chargeID.value+=num.toUpperCase();
				}
				
			}else if(putinForm.nowinput.value=="2"){
				putinForm.money.value+=num;
			}
        }
        function numlock(){
        	if("1"==putinForm.locknum.value){
        		putinForm.locknum.value="2";
        		document.all.lock.style.background='url(/smartcardweb/pages/images/locka.gif)';
				
        	}else{
        		putinForm.locknum.value="1";
        		document.all.lock.style.background='url(/smartcardweb/pages/images/lock.gif)';
        	}
        }
        
        function cancelnum()
        {
		if(putinForm.nowinput.value=="1")
			putinForm.chargeID.value=putinForm.chargeID.value.substring(0,putinForm.chargeID.value.length-1);
		else if(putinForm.nowinput.value=="2")
			putinForm.money.value=putinForm.money.value.substring(0,putinForm.money.value.length-1);
        }
        function tab()
        {
              if(putinForm.nowinput.value=="1")
                 putinForm.money.focus();
              else if(putinForm.nowinput.value=="2")
                 putinForm.chargeID.focus();
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
	</head>
	<body scroll="no"
		onload="MM_preloadImages('/smartcardweb/pages/images/senda.gif','/smartcardweb/pages/images/cancela.gif')">
		<form action="/smartcardweb/rejiePutin.do" method="post"
			name="putinForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="input_fee">
						<table width="900" border="0" align="center" cellpadding="0"
							cellspacing="0">
							<tr>
								<td height="32" colspan="2">
									&nbsp;<input type="hidden" name="nowinput" value="1" />
									      <input type="hidden" name="locknum" value="1" />
								</td>
							</tr>
							<tr>
								<td width="355" height="81" valign="top">
									&nbsp;
								</td>
								<td width="505" rowspan="2" valign="top">
									<table width="100%" border="0" cellspacing="0" cellpadding="0">
										<tr>
											<td>
												&nbsp;
											</td>
										</tr>
										<tr>
											<td>
												&nbsp;
											</td>
										</tr>
										<tr>
											<td>
												<div id="mis">
													<div>
														<ul>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/a.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/aa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/a.gif)"
																onclick="javascript:addnum('a');"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/b.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ba.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/b.gif)"
																onclick="javascript:addnum('b');"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/c.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ca.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/c.gif)"
																onclick="javascript:addnum('c');"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/d.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/da.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/d.gif)"
																onclick="javascript:addnum('d');"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/e.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ea.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/e.gif)"
																onclick="javascript:addnum('e');"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/f.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/fa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/f.gif)"
																onclick="javascript:addnum('f');"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/g.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ga.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/g.gif)"
																onclick="javascript:addnum('g');"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/h.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ha.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/h.gif)"
																onclick="javascript:addnum('h');"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/i.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ia.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/i.gif)"
																onclick="javascript:addnum('i');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/j.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ja.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/j.gif)"
																onclick="javascript:addnum('j');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/k.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ka.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/k.gif)"
																onclick="javascript:addnum('k');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/l.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/la.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/l.gif)"
																onclick="javascript:addnum('l');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/m.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ma.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/m.gif)"
																onclick="javascript:addnum('m');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/n.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/na.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/n.gif)"
																onclick="javascript:addnum('n');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/o.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/oa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/o.gif)"
																onclick="javascript:addnum('o');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/p.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/pa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/p.gif)"
																onclick="javascript:addnum('p');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/q.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/qa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/q.gif)"
																onclick="javascript:addnum('q');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/r.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ra.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/r.gif)"
																onclick="javascript:addnum('r');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/s.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/sa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/s.gif)"
																onclick="javascript:addnum('s');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/t.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ta.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/t.gif)"
																onclick="javascript:addnum('t');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/u.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ua.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/u.gif)"
																onclick="javascript:addnum('u');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/shx.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/shxa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/shx.gif)"
																onclick="javascript:addnum('-');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/v.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/va.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/v.gif)"
																onclick="javascript:addnum('v');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/w.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/wa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/w.gif)"
																onclick="javascript:addnum('w');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/x.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/xa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/x.gif)"
																onclick="javascript:addnum('x');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/y.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ya.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/y.gif)"
																onclick="javascript:addnum('y');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/z.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/za.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/z.gif)"
																onclick="javascript:addnum('z');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/xhx.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/xhxa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/xhx.gif)"
																onclick="javascript:addnum('_');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/0.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/0a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/0.gif)"
																onclick="javascript:addnum('0');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/1.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/1a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/1.gif)"
																onclick="javascript:addnum('1');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/2.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/2a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/2.gif)"
																onclick="javascript:addnum('2');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/3.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/3a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/3.gif)"
																onclick="javascript:addnum('3');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/4.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/4a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/4.gif)"
																onclick="javascript:addnum('4');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/5.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/5a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/5.gif)"
																onclick="javascript:addnum('5');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/6.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/6a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/6.gif)"
																onclick="javascript:addnum('6');"></li>
															<li id="lock"
																style="cursor:hand; background:url(/smartcardweb/pages/images/lock.gif)"
																onclick="javascript:numlock();"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/7.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/7a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/7.gif)"
																onclick="javascript:addnum('7');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/8.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/8a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/8.gif)"
																onclick="javascript:addnum('8');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/9.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/9a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/9.gif)"
																onclick="javascript:addnum('9');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/del.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/dela.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/del.gif)"
																onclick="javascript:cancelnum();"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/tab.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/taba.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/tab.gif)"
																onclick="javascript:tab();"></li>
														</ul>
													</div>


												</div>
											</td>
										</tr>
										<tr>
											<td>
												&nbsp;
											</td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
							                <input type="hidden" name="nowinput" value="1" />  
											<input type="hidden" name="cardId" />
											<input type="hidden" name="cardBala" />
											<input type="hidden" name="txCnt" />
								<td height="250" align="center" valign="top">
									<p>
										&nbsp;
									</p>
									<table width="90%" border="0" align="right" cellpadding="0"
										cellspacing="0">
										<tr>
										   <td>
											<img src="/smartcardweb/pages/images/wlzh.gif"
												width="100" height="24" />
											</td>
									    <td >
											<input name="chargeID" type="text" class="样式11"
												onfocus="javascript:putinForm.nowinput.value='1'" size="15"
												 /><!--maxlength="6" -->
										</td>
										
										</tr>
										<tr>
											<td align="center">
											<img src="/smartcardweb/pages/images/money2.gif"
												width="100" height="24" />
												</td>
										<td>
											<input name="money" type="text" class="样式11"
												onfocus="javascript:putinForm.nowinput.value='2'" size="15"
												 />
										</td>
										</tr>
										<tr>
											<td colspan="2">
												&nbsp;
											</td>
										</tr>
										<tr>
											<td colspan="2">
												&nbsp;
											</td>
										</tr>
										<tr>
											<td align="right" colspan="2">
											<a onclick="javascript: readCard();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>

												<a
												onclick="javascript: window.location='/smartcardweb/main.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
													src="/smartcardweb/pages/images/cancel.gif" name="cancel"
													width="109" height="48" border="0" id="cancel" /> </a>
											</td>
										</tr>

									</table>

									<div id="login_buttom">
									</div>
									
								</td>
							</tr>
						</table>
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

