<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>水控转账成功</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
					String cardId = request.getAttribute("cardId") == null ? ""
					: request.getAttribute("cardId").toString();
			String money = request.getAttribute("money") == null ? "" : request
					.getAttribute("money").toString();
					
			String cardBala = request.getAttribute("cardBala") == null ? ""
					: request.getAttribute("cardBala").toString();
			String waterBala = request.getAttribute("waterBala") == null ? ""
					: request.getAttribute("waterBala").toString();
			String tradecode = request.getAttribute("tradecode") == null ? ""
                    : request.getAttribute("tradecode").toString();
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
					
			String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
			String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
			String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
			String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		%>
		<script type="text/JavaScript">		
		function writeCard(){
			var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
			var device_port = '<%=read_card_device_port%>';
			var msg = document.getElementById("msg");
			var cardId = '<%=cardId%>';
			var money = '<%=money%>';
			var cardBala = '<%=cardBala%>';
			var waterBala = '<%=waterBala%>';
			var tradecode = '<%=tradecode%>';
            var txCnt = '<%=txCnt%>';
            var txCnt1 = '<%=txCnt1%>';
            var sphone3 = '<%=sphone3%>';
            var saddr = '<%=saddr%>';
			var outCardAmount = '<%=outCardAmount%>';
			var outCardAmount1 = '<%=outCardAmount1%>';
			var url = serverbase+"getWaterTrans999.do";
			
			writeCardForm.all.RFScanner.PortNo=device_port;
			var packetno = 2;
			 if("1181"==tradecode){
                 packetno = 2;
             }else if("1182"==tradecode){
                packetno = 3;
             }else if("1183"==tradecode){
               packetno = 4;
             }
             var parms = "cardId="+cardId+"&cardBala="+cardBala+"&waterBala="+waterBala+"&money="+money+"&txCnt="+txCnt+"&txCnt1="+txCnt1+"&tradecode="+tradecode+"&sphone3="+sphone3+"&saddr="+saddr+"&outCardAmount="+outCardAmount+"&outCardAmount1="+outCardAmount1+"&packetno="+packetno;
			var ret = writeCardForm.all.RFScanner.WaterTransWriteCard(url,cardId,outCardAmount,outCardAmount1,packetno,parms);
			if(ret==0){
				msg.innerHTML="水控转账成功，<br><br>转账金额 "+money+" 元，<br><br>一卡通卡余额 "+parseFloat(outCardAmount)/100+" 元，<br><br> 水控钱包卡余额 "+parseFloat(outCardAmount1)/100 +"元";
			}else if(ret==-3){
				window.location='/smartcardweb/pages/waterctl999/recardwrite1.jsp';
			}else{
                window.location='/smartcardweb/pages/waterctl999/recardwrite.jsp';
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
								<table width="50%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">

									<tr>
										<td height="320" align="center" class="样式13" id="msg">
										
											正在写卡、充值!请稍后...
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
												onclick="javascript: window.location='/smartcardweb/main.do';"
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



