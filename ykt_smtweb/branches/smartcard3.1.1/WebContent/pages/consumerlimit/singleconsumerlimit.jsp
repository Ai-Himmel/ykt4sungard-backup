<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<html>
	<head>
		<title>消费限额输入</title>
		<%
		String CardPhyId = (String) request.getAttribute("CardPhyId");
		String maxpercount_o= (String)request.getAttribute("maxpercount");
		String maxperday_o = (String)request.getAttribute("maxperday");
		%>
		<script language="javascript">
        function addnum(num)
        {
			if(putinForm.all.maxpercount.value.length < 3 ){
				putinForm.all.maxpercount.value+=num;
			}
        }
        function cancelnum()
        {
			putinForm.all.maxpercount.value=putinForm.all.maxpercount.value.substring(0,putinForm.all.maxpercount.value.length-1);	
        }
    	function readCard(){
    	 
    	 	if(putinForm.all.maxpercount.value==''){
    	 		alert("请输入单次消费限额！");
    	 		putinForm.all.maxpercount.focus();
    	 		return false;
    	 	}

    	 	if(!fucCheckNUM(putinForm.all.maxpercount.value)){
    	 	 	alert("单次消费限额为整数数字！");
    	 		putinForm.all.maxpercount.focus();
    	 		return false;
    	 	}
    	 	
    	 	if(putinForm.all.maxpercount.value<0){
    	 		alert("单次消费限额应该不小于0！");
    	 		putinForm.all.maxpercount.focus();
    	 		return false;
    	 	}

        	var CardPhyId ='<%=CardPhyId%>';
				var ret = putinForm.all.RFScanner.ReadCardPocket(1,CardPhyId);
				if(ret == 0){
					var cardbal = putinForm.all.RFScanner.GetPacketInfo("cardbal");
					var dptCardCnt =  putinForm.all.RFScanner.GetPacketInfo("dpt_card_cnt");
					var payCardCnt = putinForm.all.RFScanner.GetPacketInfo("pay_card_cnt");
					putinForm.all.CardPhyId.value=CardPhyId;
					putinForm.all.cardbal.value = cardbal;
					putinForm.all.dptCardCnt.value = dptCardCnt;
					putinForm.all.payCardCnt.value = payCardCnt;
					putinForm.submit();

				}else if(ret == 1){
					alert("请放置卡片...");
					return false;
				}else{
					alert("请正确放置卡片...");
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
		<form action="/smartcardweb/resetconsumerlimit.do" method="post"
			name="putinForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="login">
						<div id="login_left"></div>
						<div id="login_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/input-money.gif" width="343"
									height="57" />
							</div>
							<div>
								<ul>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/0.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/0a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/0.gif)"
										onclick="javascript:addnum(0)" ondblclick="javascript:addnum(0)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/1.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/1a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/1.gif)"
										onclick="javascript:addnum(1)" ondblclick="javascript:addnum(1)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/2.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/2a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/2.gif)"
										onclick="javascript:addnum(2)" ondblclick="javascript:addnum(2)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/3.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/3a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/3.gif)"
										onclick="javascript:addnum(3)" ondblclick="javascript:addnum(3)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/4.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/4a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/4.gif)"
										onclick="javascript:addnum(4)" ondblclick="javascript:addnum(4)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/5.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/5a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/5.gif)"
										onclick="javascript:addnum(5)" ondblclick="javascript:addnum(5)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/6.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/6a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/6.gif)"
										onclick="javascript:addnum(6)" ondblclick="javascript:addnum(6)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/7.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/7a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/7.gif)"
										onclick="javascript:addnum(7)" ondblclick="javascript:addnum(7)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/8.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/8a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/8.gif)"
										onclick="javascript:addnum(8)" ondblclick="javascript:addnum(8)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/9.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/9a.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/9.gif)"
										onclick="javascript:addnum(9)" ondblclick="javascript:addnum(9)"></li>
									<li
										onmouseup="this.style.background='url(/smartcardweb/pages/images/del.gif)'"
										onmousedown="this.style.background='url(/smartcardweb/pages/images/dela.gif)'"
										style="cursor:hand; background:url(/smartcardweb/pages/images/del.gif)"
										onclick="javascript:cancelnum()" ondblclick="javascript:cancelnum()"></li>
								</ul>
							</div>
							<div id="login_input">
								<table width="800" border="0" cellpadding="0" cellspacing="0">
									<tr>
										<td colspan="2" height="10">
										&nbsp;
										</td>
									</tr>
									<tr>
										<td width="206" align="right">
											<img src="/smartcardweb/pages/images/dc.gif"
												width="206" height="24" />
											<input type="hidden" name="nowinput" value="1" />
											<input type="hidden" name="CardPhyId" />
											<input type="hidden" name="cardbal" />
											<input type="hidden" name="dptCardCnt" />
											<input type="hidden" name="payCardCnt" />
										</td>
										<td>
											<input name="maxpercount" type="text" class="样式11" size="20"
												maxlength="4" />【您卡上的单次消费限额为<b><%=Integer.parseInt(maxpercount_o)/100%></b>元】
										</td>
									</tr>
									<tr>
										<td width="206" align="right">											
											&nbsp;
										</td>
										<td>
											<input name="maxperday" type="hidden" class="样式11" value="100" size="20"
												maxlength="4" />
										</td>
									</tr>
									<tr>
										<td colspan="2" valign="bottom" class="样式9" align="center">
											此功能仅对普通卡有效，手机卡无限额！<br/><html:errors />
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
