<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>
		<title>城市热点转账输入</title>
		<%
		String cardno = (String) request.getAttribute("cardno");
		String pwd = (String) request.getAttribute("pwd");
		%>
		<script language="javascript"><!--
        function addnum(num)
        {
			if(putinForm.all.nowinput.value=="1" && putinForm.all.room.value.length < 7 ){
				putinForm.all.room.value+=num;
			}else if(putinForm.all.nowinput.value=="2" && putinForm.all.money.value.length < 5 ){
				putinForm.all.money.value+=num;
			}
        }
        function backnum()
        {
		if(putinForm.all.nowinput.value=="1")
			putinForm.all.room.value=putinForm.all.room.value.substring(0,putinForm.all.room.value.length-1);
		else if(putinForm.all.nowinput.value=="2")
			putinForm.all.money.value=putinForm.all.money.value.substring(0,putinForm.all.money.value.length-1);		
        }
        
   
    	function readCard(){
    	 
    	 	var re =/^[0-9]*[1-9][0-9]*$/;　　
	        //var msg = document.getElementById("msg");
	        var money =  document.all.money.value;
	      
	        if(money==''){
	          putinForm.all.money.focus();
	          msg.innerHTML="请输入转账金额(单位：元)";
	          return false;
	        }
	        if(money>100){
	          msg.innerHTML="最大限额100元";
	          document.putinForm.money.focus();
	          return false;
	        }
	        if(!re.test(money)){
	          msg.innerHTML="请输入整数金额";
	          document.putinForm.money.focus();
	          return false;
	        }	
	        
    	 	var serverbase = "http://"+'<%=webserverip%>'+":"+'<%=webserverport%>'+"/"+'<%=webserverapp%>'+"/";
			var device_port = '<%=read_card_device_port%>';
        	var cardno ='<%=cardno%>';
			putinForm.all.RFScanner.PortNo=device_port;
			var rrt = putinForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			if(rrt == 0){
				var ret = putinForm.all.RFScanner.ReadCardPocket(1,cardno,"");
				if(ret == 0){
					var bala = putinForm.all.RFScanner.GetPacketInfo("bala");
					var cxCnt =  putinForm.all.RFScanner.GetPacketInfo("total_cnt");
					if(parseInt(document.all.money.value)*100<=parseInt(bala)){
					    putinForm.all.deviceId.value=readfile();
						putinForm.all.cardno.value=cardno;
						putinForm.all.cardBala.value = bala;
						putinForm.all.cxCnt.value = cxCnt;
						putinForm.submit();
					}else{
						msg.innerHTML="转账金额超过了卡片余额";
						return false;
					}
				}else if(ret == 1){
					msg.innerHTML="请放置卡片";
					return false;
				}else{
					msg.innerHTML="请正确放置卡片";
					return false;
				}
			}else{
				msg.innerHTML="网络不通，请稍后重试";
				return false;
			}
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
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<style type="text/css">

			.样式11 {
			font-family: "宋体"; 
			color: #000000; 
			font-size: 16px;
			font-weight: bold;
			}
		</style>
	</head>
	<body scroll="no" onload="javascript:document.putinForm.money.focus();">
		<form action="<%=path%>/cityhotspotPutin.do" method="post"
			name="putinForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="login">
						<div id="login_left"></div>
						<div id="login_middle">
							<div align="center">
								<img src="<%=path%>/pages/images/input-money.gif" width="343"
									height="57" />
							</div>
							<div>
								<ul>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/0.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/0a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/0.gif)"
										onclick="javascript:addnum(0)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/1.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/1a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/1.gif)"
										onclick="javascript:addnum(1)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/2.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/2a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/2.gif)"
										onclick="javascript:addnum(2)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/3.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/3a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/3.gif)"
										onclick="javascript:addnum(3)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/4.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/4a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/4.gif)"
										onclick="javascript:addnum(4)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/5.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/5a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/5.gif)"
										onclick="javascript:addnum(5)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/6.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/6a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/6.gif)"
										onclick="javascript:addnum(6)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/7.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/7a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/7.gif)"
										onclick="javascript:addnum(7)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/8.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/8a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/8.gif)"
										onclick="javascript:addnum(8)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/9.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/9a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/9.gif)"
										onclick="javascript:addnum(9)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/del.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/dela.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/del.gif)"
										onclick="javascript:backnum()"></li>
								</ul>
							</div>
							<div id="login_input">
								<table width="360" border="0" cellpadding="0" cellspacing="0">
									<tr>
										<td colspan="2" height="10">
										&nbsp;
										</td>
									</tr>
									      
									
									<tr>
									        <input type="hidden" name="nowinput" value="1" />
											<input type="hidden" name="cardno" />
											<input type="hidden" name="cardBala" />
											<input type="hidden" name="cxCnt" />
											<input type="hidden" name="pwd" value="<%=pwd%>"/>
											<input type="hidden" name="deviceId">
										<td width="206" align="right">
											<img src="<%=path%>/pages/images/money2.gif"
												width="114" height="24" />
										</td>
										<td>
											<input name="money" type="text" class="样式11"
												onfocus="javascript:putinForm.nowinput.value='2'" size="20"
												maxlength="4" />
										</td>
									</tr>
									<tr>
										<td colspan="2" class="show" align="center" height="10" id="msg">
										&nbsp;
										</td>
									</tr>
								</table>
							</div>
							<div id="login_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript: readCard();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','<%=path%>/pages/images/senda.gif',1)"><img
													src="<%=path%>/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='<%=path%>/main.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('back','','<%=path%>/pages/images/backa.gif',1)"><img
													src="<%=path%>/pages/images/back.gif" name="back"
													width="109" height="48" border="0" id="back" /> </a>
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
