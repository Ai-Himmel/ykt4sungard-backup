<%@ page contentType="text/html;charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ page import="com.kingstargroup.fdykt.dto.CustomerDTO"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>银行卡转帐确认</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
		<script type="text/javascript" src="/smartcardweb/pages/javascript/lightbox.js"></script>
		<%
			CustomerDTO customer = (CustomerDTO) session.getAttribute("customer");
			String refno = request.getAttribute("refno") == null ? "" : request.getAttribute("refno").toString();
			String webserverip = KSConfiguration.getInstance().getProperty("webserverip");
			String webserverport = KSConfiguration.getInstance().getProperty("webserverport");
			String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp");
			String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port", "0");
			String cardBala = request.getAttribute("cardBala") == null ? "" : request.getAttribute("cardBala").toString();
			String money = request.getAttribute("money") == null ? "" : request.getAttribute("money").toString();
			String cardphyid = request.getAttribute("cardphyid") == null ? "" : request.getAttribute("cardphyid").toString();
			String payCardCnt = request.getAttribute("payCardCnt") == null ? "" : request.getAttribute("payCardCnt").toString();
			String dptCardCnt = request.getAttribute("dptCardCnt") == null ? "" : request.getAttribute("dptCardCnt").toString();
			String bankcardno = request.getAttribute("bankcardno") == null ? "" : request.getAttribute("bankcardno").toString();
			String radomstr = request.getAttribute("radomstr") == null ? "" : request.getAttribute("radomstr").toString();
		%>
		<script language="javascript">
		function dobanktrans(){	
			closeAuthCode();
			var cardphyid ='<%=cardphyid%>';
			var payCardCnt = '<%=payCardCnt%>';	
			var dptCardCnt = '<%=dptCardCnt%>';	
			var refno = '<%=refno%>';    
			var outCardAmount = '<%=0%>';  
			var money='<%=money%>';	
			var bankcardno = '<%=bankcardno%>';  
			var radomstr = '<%=radomstr%>';
			var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";	
			var authcode = document.getElementById("authcode").value;
			var ret = document.all.RFScanner.ReadCardPocket(1,cardphyid);
			if(ret == 0){
			    document.all.errmsg.innerHTML="转账请求发送中，请稍后...最多需要等待30秒，请不要轻易移走卡片"
                document.all.send.style.display="none";
				var doworkret = document.all.RFScanner.BankTransWriteCard(serverbase+"authbanktransfer.do",cardphyid,outCardAmount,dptCardCnt,"money="+money+"&cardphyid="+cardphyid+"&payCardCnt="+payCardCnt+"&refno="+refno+"&bankcardno="+bankcardno+"&radomstr="+radomstr+"&authcode="+authcode);
				if(doworkret == 0){
				//转账成功		
				    window.location='/smartcardweb/pages/authbanktransfer/transfersuccess.jsp';		
				}else if(doworkret == -1){
					//写卡失败
					window.location='/smartcardweb/pages/authbanktransfer/recardwrite.jsp';//如果重写还不成功，就要走冲正流程					
				}else if(doworkret == 1){
					//转账失败
					window.location='/smartcardweb/pages/authbanktransfer/transferfailue.jsp';					
				}else{
				    //转账失败
					window.location='/smartcardweb/pages/authbanktransfer/transferfailue.jsp';	
				}
				
			}else if(ret == 1){
				alert("请放置卡片...");
			}else{
				alert("请正确放置卡片...");
			}
		}
		var box;
		function openAuthCode(){ 
			if(!box){
				box = new LightBox("lightbox");		
			}
			document.all.send1.style.display="";
			box.OverLay.Color = "#000";
			box.Center = true;
			box.Over = true;
			box.OverLay.Opacity = 50;
			box.Fixed = true;
			box.Show(); 
			writeCardForm.all.authcode.focus();
		}
		function closeAuthCode(){
			document.all.send1.style.display="none";
			box.Close(); 
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
		function addnum(num) {
			if(writeCardForm.all.authcode.value.length < 6){
				writeCardForm.all.authcode.value+=num;
			}
        }
        function cancelnum(){
        	writeCardForm.all.authcode.value=writeCardForm.all.authcode.value.substring(0,writeCardForm.all.authcode.value.length-1);
        }
        function tab(){
        	writeCardForm.all.authcode.focus();
        }
	</script>
	<style type="text/css">
		.样式12 {
			font-family: "宋体"; 
			color: #000000; 
			font-size: 16px; 
		}
		.样式13 {
			font-family: "黑体"; 
			color: #000000; 
			font-size: 18px; 
		}
		.样式14 {
			font-family: "黑体"; 
			color: #ff0000; 
			font-size: 18px; 
		}
	</style>
	</head>
	<%%>
	<body scroll="no">
		<form action="/smartcardweb/authtransfer.do" method="post" name="writeCardForm">
			<div id="lightbox" align="center" style="background-color: white;display:none">
				<table>
					<tr><td><input id="authcode" name="authcode" type="password" style="margin-top: 20px;font-size: 24px;font-weight: normal;line-height: normal;" size="12" maxlength="8" />【校验码】</td></tr>	
				</table>
				<ul>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/0.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/0a.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/0.gif)"
						onclick="javascript:addnum('0')" ondblclick="javascript:addnum('0')"></li>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/1.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/1a.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/1.gif)"
						onclick="javascript:addnum('1')" ondblclick="javascript:addnum('1')"></li>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/2.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/2a.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/2.gif)"
						onclick="javascript:addnum('2')" ondblclick="javascript:addnum('2')"></li>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/3.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/3a.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/3.gif)"
						onclick="javascript:addnum('3')" ondblclick="javascript:addnum('3')"></li>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/4.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/4a.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/4.gif)"
						onclick="javascript:addnum('4')" ondblclick="javascript:addnum('4')"></li>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/5.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/5a.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/5.gif)"
						onclick="javascript:addnum('5')" ondblclick="javascript:addnum('5')"></li>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/6.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/6a.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/6.gif)"
						onclick="javascript:addnum('6')" ondblclick="javascript:addnum('6')"></li>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/7.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/7a.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/7.gif)"
						onclick="javascript:addnum('7')" ondblclick="javascript:addnum('7')"></li>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/8.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/8a.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/8.gif)"
						onclick="javascript:addnum('8')" ondblclick="javascript:addnum('8')"></li>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/9.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/9a.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/9.gif)"
						onclick="javascript:addnum('9')" ondblclick="javascript:addnum('9')"></li>
					<li
						onmouseup="this.style.background='url(/smartcardweb/pages/images/del.gif)'"
						onmousedown="this.style.background='url(/smartcardweb/pages/images/dela.gif)'"
						style="cursor:hand; background:url(/smartcardweb/pages/images/del.gif)"
						onclick="javascript:cancelnum()" ondblclick="javascript:cancelnum()"></li>
				</ul>
				<a onclick="javascript:dobanktrans();"
										onmouseup="MM_swapImgRestore()"
										onmousedown="MM_swapImage('send1','','/smartcardweb/pages/images/senda.gif',1)"><img
											src="/smartcardweb/pages/images/send.gif" name="send1"
											width="109" height="48" border="0" id="send1" style="margin-top: 10px"/> </a>
						<a onclick="javascript:closeAuthCode();"
										onmouseup="MM_swapImgRestore()"
										onmousedown="MM_swapImage('cancel1','','/smartcardweb/pages/images/cancela.gif',1)"><img
											src="/smartcardweb/pages/images/cancel.gif" name="cancel1"
											width="109" height="48" border="0" id="cancel1" /> </a>
			</div>
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/zz.gif" width="314"
									height="82" />
									<input type="hidden" name="org.apache.struts.taglib.Html.TOKEN">
							</div>

							<div id="content_input">
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									  <tr>
                                        <td height="40" class="样式13">
                                           交易参考号
                                        </td>
                                        <td>
                                            <%=refno%>
                                        </td>
                                    </tr>
									   <tr>
                                        <td height="40" class="样式13">
                                           银行卡号
                                        </td>
                                        <td>
                                            <%=bankcardno%>
                                        </td>
                                    </tr>
									
									<tr>
										<td height="40" class="样式13">
											姓名
										</td>
										<td>
											<%=customer.getCustname()%>
										</td>
									</tr>
									
									<tr>
										<td height="40" class="样式13">
											学号
										</td>
										<td>
											<%=customer.getStuempno()%>
										</td>
									</tr>
									<tr>
                                        <td height="40" class="样式13">
                                           一卡通余额
                                        </td>
                                        <td>
                                            <%=Double.parseDouble(cardBala) / 100%>元
                                        </td>
                                    </tr>
									<tr>
										<td height="40" class="样式13">
											转账金额
										</td>
										<td>
											<%=money%>
											元
										</td>
									</tr>
									
									<tr>
										<td height="80" align="center" class="show" id="errmsg"
											colspan="2">
											<html:errors />请确认放好卡!转账过程可能最多需要等待30秒，请不要轻易移走卡片！
											&nbsp;
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom" align="center">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:openAuthCode();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/index.do';"
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