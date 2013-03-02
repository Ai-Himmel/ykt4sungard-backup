<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>解锁写卡</title>
		<%
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		 %>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
		<%
		String cardphyid = request.getAttribute("cardphyid")==null?"":request.getAttribute("cardphyid").toString();
		String cxCnt = request.getAttribute("cxCnt")==null?"0":request.getAttribute("cxCnt").toString();
		String sdate0 = request.getAttribute("sdate0")==null?"":request.getAttribute("sdate0").toString();
		String stime0 = request.getAttribute("stime0")==null?"":request.getAttribute("stime0").toString();
		String outCardAmount = request.getAttribute("outCardAmount")==null?"0":request.getAttribute("outCardAmount").toString();
		String amount = request.getAttribute("amount")==null?"0":request.getAttribute("amount").toString();
		String CARDSTAT = request.getAttribute("CARDSTAT")==null?"0":request.getAttribute("CARDSTAT").toString();
		 String ipServer= request.getAttribute("ipServer") == null ? ""
                 : request.getAttribute("ipServer").toString();
         String drtpPort= request.getAttribute("drtpPort") == null ? ""
                 : request.getAttribute("drtpPort").toString();
         String svrFunc= request.getAttribute("svrFunc") == null ? ""
                 : request.getAttribute("svrFunc").toString();
		%>
		<script language="JavaScript" type="text/JavaScript">
			function writeCard(){
				var outCardAmount='<%=outCardAmount%>';
				var cardphyid='<%=cardphyid%>';
				var cxCnt = '<%=cxCnt%>';
				var sdate0='<%=sdate0%>';
				var stime0='<%=stime0%>';				
				var amount='<%=amount%>';
				var ipServer= '<%=ipServer%>';
				var drtpPort= '<%=drtpPort%>';
				var svrFunc= '<%=svrFunc%>';
				var CARDSTAT='<%=CARDSTAT%>';
			    var ret=writeCardForm.RFScanner.UnlockWriteCard(outCardAmount,cardphyid,cxCnt,amount,sdate0,stime0,ipServer,drtpPort,svrFunc,CARDSTAT);
			    if(ret==0){
			    	msg.innerHTML = "解锁成功！<br><br>卡片余额 "+parseFloat(outCardAmount)/100.00+"元.<br><br>扣款金额 "+parseFloat(amount)/100.00+"元";
			    }else if(ret==-10){//卡余额写失败
			    	 window.location='/smartcardweb/pages/cancellock/recardwrite.jsp';
				}else if(ret==-20){//写标识失败
					 window.location='/smartcardweb/pages/cancellock/recardwrite1.jsp';
			    }else{
			    	msg.innerHTML = "解锁失败！ 请返回重新解锁。";
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
								<table width="70%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td height="320" align="center" id="msg" class="样式13">
											<strong>解锁中请不要移动卡片...请稍等...</strong>
										</td>
									</tr>


								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/main.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/backa.gif',1)"><img
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
			 <object id="RFScanner" classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0" height="0"></object>
		</form>
	</body>
</html>

