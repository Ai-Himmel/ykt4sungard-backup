<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>写卡失败补写</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
		String cardphyid = request.getAttribute("cardphyid") == null ? ""
				: request.getAttribute("cardphyid").toString();
		String money = request.getAttribute("money") == null ? "" : request
				.getAttribute("money").toString();					
        String txCnt1 = request.getAttribute("txCnt1") == null ? ""
                : request.getAttribute("txCnt1").toString(); 	
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
		String webserverip = KSConfiguration.getInstance().getProperty(
					"webserverip");
		String webserverport = KSConfiguration.getInstance().getProperty(
					"webserverport");
		String webserverapp = KSConfiguration.getInstance().getProperty(
					"webserverapp");
		String read_card_device_port = KSConfiguration.getInstance()
					.getProperty("read_card_device_port", "0");
		String small_packet_number = KSConfiguration.getInstance().getProperty("small_packet_number","5"); 
		%>
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
		<script language="javascript">
		
		function ReWriteWaterPacket(){
			var cardphyid = '<%=cardphyid%>';
			var money = '<%=money%>';
            var txCnt1 = '<%=txCnt1%>';
            var outCardAmount = '<%=outCardAmount%>';
			var outCardAmount1 = '<%=outCardAmount1%>';
			var sdate3 = '<%=sdate3%>';
            var stime3 = '<%=stime3%>';
            var validatedate = '<%=validatedate%>';
			var watertype = '<%=small_packet_number%>';
			var wret = writeCardForm.all.RFScanner.WriteWaterCtlPacket(outCardAmount1,cardphyid,txCnt1,watertype,money,sdate3+stime3,0,0,0,validatedate);
			if(wret==0){				
				window.location='/smartcardweb/pages/waterctl/cardwritesuccess.jsp?money='+money+'&outCardAmount='+outCardAmount+'&outCardAmount1='+outCardAmount1;
			}else{
				alert("水控钱包写卡失败,请重新放好卡片,点击确定补写!");
			}
		}
		function NoWriteCard(){
			window.location='/smartcardweb/pages/waterctl/cardwriteerror.jsp';
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
								<table width="60%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td height="320" align="center" class="样式13">
											水控钱包写卡失败！请正确放置卡片！
											<br />
											<br />
											按
											<b>确定</b> 补写卡！如果仍不行，
											<b>必须</b> 按
											<b>取消</b> 退出。
										</td>
									</tr>

								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:ReWriteWaterPacket();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a onclick="javascript:NoWriteCard();"
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
				height="0" />
		</form>
	</body>
</html>


