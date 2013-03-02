<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>
		<title>更新卡信息</title>
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet"
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
		<%
		//String cardno = (String) request.getAttribute("cardno");不登陆，
		String cardno="";
			%>
		<script language="javascript">
        function   readCard()
        {
            var serverbase = "http://"+'<%=webserverip%>'+":"+'<%=webserverport%>'+"/"+'<%=webserverapp%>'+"/";
			var device_port = '<%=read_card_device_port%>';
        	var cardNo ='';
			logonForm.all.RFScanner.PortNo=device_port;
            var dk=logonForm.all.RFScanner.DoScan();
            if(dk==0){//读卡成功
              cardNo=document.all.RFScanner.CardNo;
           }else{
           	  alert("读卡失败,请正确放置卡片...");
           	  window.location="<%=path%>/pages/index.jsp"
           	  return false;
           }
            
			var rrt = logonForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			if(rrt == 0){
				var ret = logonForm.all.RFScanner.ReadCardPocket(1,cardNo,"");
				if(ret == 0){
				    logonForm.all.cardno.value=cardNo;
					logonForm.submit();
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

	<body scroll="no" onload="readCard();">
	<form name="logonForm" action="<%=path%>/checkuser.do"  method="post">
		<input type="hidden" name="cardno" />
	  <div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<table width="100%" border="0" cellspacing="0" cellpadding="0">
									<tr>
										<td height="80"></td>
									</tr>
								</table>
							</div>
							<div id="content_input">
								<table width="50%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td height="320" align="center" class="样式13" id="msg">
											读卡中......
										</td>
									</tr>

								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a
												onclick="javascript: window.location='<%=path%>/index.do';"
												onmouseout="MM_swapImgRestore()"
												onmouseover="MM_swapImage('cancel','','<%=path%>/pages/images/backa.gif',1)"><img
													src="<%=path%>/pages/images/back.gif" name="cancel"
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
	</body>
</html>

