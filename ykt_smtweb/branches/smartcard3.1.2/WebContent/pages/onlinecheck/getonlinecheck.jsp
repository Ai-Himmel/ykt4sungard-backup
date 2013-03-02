<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@page import="com.kingstar.itemconfig.Configitem"%>
<%@page import="java.util.HashMap"%>
<%@page import="java.util.Iterator"%>
<%@page import="java.util.Map.Entry"%>
<%@page import="com.kingstargroup.fdykt.util.DateUtil"%>
<html>
	<head>
		<title>联机交易检查</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
        String cardphyid = request.getAttribute("cardphyid")==null?"":request.getAttribute("cardphyid").toString();
		String lvol7 = request.getAttribute("lvol7")==null?"":request.getAttribute("lvol7").toString();
		 String lvol8 = request.getAttribute("lvol8")==null?"":request.getAttribute("lvol8").toString();
		 String damt0 = request.getAttribute("damt0")==null?"":request.getAttribute("damt0").toString();
		 String sdate0 = request.getAttribute("sdate0")==null?"":request.getAttribute("sdate0").toString();
		 String stime0 = request.getAttribute("stime0")==null?"":request.getAttribute("stime0").toString();
		 String snote = request.getAttribute("snote")==null?"":request.getAttribute("snote").toString();
		 String vsmess = request.getAttribute("vsmess")==null?"":request.getAttribute("vsmess").toString();
		 String ipServer= request.getAttribute("ipServer") == null ? "": request.getAttribute("ipServer").toString();
         String drtpPort= request.getAttribute("drtpPort") == null ? "": request.getAttribute("drtpPort").toString();
         String svrFunc= request.getAttribute("svrFunc") == null ? "": request.getAttribute("svrFunc").toString();
        String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
        String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
        String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
        String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
        %>
		<script language="javascript">
		function writeCard(){
			var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
			var device_port = '<%=read_card_device_port%>';
            var cardphyid = '<%=cardphyid%>';
            var lvol8 = '<%=lvol8%>';
            var damt0 = '<%=damt0%>';
            var sdate0 = '<%=sdate0%>';
            var stime0 = '<%=stime0%>';
            var snote = '<%=snote%>';            
            var ipServer= '<%=ipServer%>';
			var drtpPort= '<%=drtpPort%>';
			var svrFunc= '<%=svrFunc%>';
			writeCardForm.all.RFScanner.PortNo=device_port;
			var ret = writeCardForm.all.RFScanner.CardTransWriteCard(lvol8,cardphyid,0,damt0,sdate0,stime0,ipServer,drtpPort,svrFunc);
			if(ret==0){
				writeCardForm.submit();
            }else{
                msg.innerHTML="写卡失败，请重新放置卡片后，点击确定重新写卡。或者点击取消重新操作";
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
			font-size: 20px;
		}
		}
		</style>
	</head>
	<body scroll="no">
		<form action="/smartcardweb/onlinecheckresult.do" method="post" name="writeCardForm">
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
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td height="40" align=center class="样式14"
											colspan="2">
											上次交易写卡失败,需要补写卡余额
										</td>
									</tr>
									
									<tr>
										<td height="40" class="样式13">
											<input type="hidden" name="lvol8" value="<%=lvol8%>"/>
											<input type="hidden" name="damt0" value="<%=damt0%>"/>
											上次交易时间：
										</td>
										<td>
											<%= DateUtil.reFormatTime(sdate0+stime0)%>
										</td>
									</tr>

									<tr>
										<td height="40" class="样式13">
											上次交易名称：
										</td>
										<td>
											<%= snote%>
										</td>
									</tr>
									<tr>
										<td height="40" class="样式13">
											上次交易金额：
										</td>
										<td>
											<%=damt0%> 元
										</td>
									</tr>
									<tr>
										<td height="40" class="样式13">
											卡当前余额：
										</td>
										<td>
											<%=Float.parseFloat(lvol7)/100%> 元
										</td>
									</tr>									
									<tr>
										<td height="40" class="样式13">
											补写后余额：
										</td>
										<td>
											<%=Float.parseFloat(lvol8)/100%> 元
										</td>
									</tr>
									<tr>
										<td height="40" class="样式13">
											描述信息：
										</td>
										<td>
											<%=vsmess%>
										</td>
									</tr>

									<tr>
										<td height="50" align="center" class="show" id="errmsg"
											colspan="2">
										请确认放好卡!点击<font style="font-size: 22px;"><b> 确定 </b></font>补写卡余额 &nbsp;
											<br>
											<html:errors />
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:writeCard();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/index.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel', '', '/smartcardweb/pages/images/cancela.gif', 1)">
												<img src="/smartcardweb/pages/images/cancel.gif" name="cancel"
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

