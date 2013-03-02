<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<html>
	<head>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
		<title>登录</title>
	 <%
        String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
        String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
        String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
        String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
    %>
		<script language="javascript">
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
        function addnum(num){
			if(logonForm.all.nowinput.value=="1" && logonForm.all.password.value.length < 6){
				logonForm.all.password.value+=num;
			}else if(logonForm.all.nowinput.value=="2" && logonForm.all.authcode.value.length < 6){
				logonForm.all.authcode.value+=num;
			} 
        }
        function cancelnum()
        {
			if(logonForm.all.nowinput.value=="1"){
				logonForm.all.password.value=logonForm.all.password.value.substring(0,logonForm.all.password.value.length-1);
			} else if(logonForm.all.nowinput.value=="2"){
				logonForm.all.authcode.value=logonForm.all.authcode.value.substring(0,logonForm.all.authcode.value.length-1);
			}
        }
        function tab()
        {
            if(logonForm.all.nowinput.value=="1"){
            	logonForm.all.authcode.focus();
            }else if(logonForm.all.nowinput.value=="2"){
            	 logonForm.all.password.focus();
            }
        }
        function readCard()
        {
           var device_port = '<%=read_card_device_port%>';         
           logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
           var ret=logonForm.all.RFScanner.DoScan();
           if(ret==0){//读卡成功          
              logonForm.all.cardphyid.value=logonForm.all.RFScanner.CardPhyID;
              logonForm.submit();
           }else{
               alert("读卡失败，请放置卡片...");
           }
        }


 	</script>

	<style type="text/css">
		.样式12 {
		font-family: "宋体"; 
		color: #000000; 
		font-size: 16px; 
		}
	</style>

	</head>



	<body scroll="no">
		<form action="/smartcardweb/authbankquerycheck.do" method="post" name="logonForm" >
		<input type="hidden" name="nowinput" value="1" />
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="login">
						<div id="login_left"></div>
						<div id="login_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/password.gif" width="343"
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
							<div id="login_blank">
								&nbsp;
							</div>
							<div id="login_blank">
								&nbsp;
							</div>
							<div id="login_input" style="margin-top: 10px">
								<font size="5" color="#1940CF"><strong>请放入卡</strong></font><font size="5">&nbsp;&nbsp;&nbsp;&nbsp;密&nbsp;&nbsp;码：</font>
								<input name="password" type="password" class="info" size="20"
									maxlength="6" onfocus="javascript:logonForm.nowinput.value='1'"/><font size="5">【校园卡密码】&nbsp;&nbsp;</font>
								<input type="hidden" name="cardphyid" />
							</div>
							<div id="login_input" style="margin-top: 10px">
								<font size="5">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;校验码：</font>
								<input name="authcode" type="password" class="info" size="20"
									maxlength="6" onfocus="javascript:logonForm.nowinput.value='2'"/><font size="5">【银行卡校验码】</font>
							</div>
							<div id="login_blank1" class="样式12">
								<html:errors />
								&nbsp;
							</div>
							<div id="login_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:readCard();"
												onmouseup="MM_swapImgRestore()"
												onmouseout="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" />
											</a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/index.do';"
												onmouseup="MM_swapImgRestore()"
												onmouseout="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
													src="/smartcardweb/pages/images/cancel.gif" name="cancel"
													width="109" height="48" border="0" id="cancel" />
											</a>
											
										</td>
									</tr>
								</table>

							</div>
						</div>
						<div id="login_right"></div>
						<div class="clear"></div>

					</div>
				</div>
			</div>
			<div id="bottom"></div>
 <object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
					width="0" height="0"
			codebase="/smartcardweb/rf35.cab#version=2,0,0,7"></object>
		</form>
	</body>
</html>

