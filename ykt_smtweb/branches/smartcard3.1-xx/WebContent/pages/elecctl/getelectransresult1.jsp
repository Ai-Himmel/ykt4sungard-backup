<%@ page contentType="text/html;charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>电控转账成功</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
             String sbank_acc = request.getAttribute("sbank_acc") == null ? ""
                    : request.getAttribute("sbank_acc").toString();
            String cardphyid = request.getAttribute("cardphyid") == null ? ""
                    : request.getAttribute("cardphyid").toString();
            String money = request.getAttribute("money") == null ? "" : request
                    .getAttribute("money").toString();
            String txCnt = request.getAttribute("txCnt") == null ? "" : request
                    .getAttribute("txCnt").toString();      
            String sphone3 = request.getAttribute("sphone3") == null ? ""
                    : request.getAttribute("sphone3").toString();
            String sdate3 =request.getAttribute("sdate3") == null ? ""
                    : request.getAttribute("sdate3").toString();
            String stime3 = request.getAttribute("stime3") == null ? ""
                    : request.getAttribute("stime3").toString();
            String ipServer= request.getAttribute("ipServer") == null ? ""
                    : request.getAttribute("ipServer").toString();
            String drtpPort= request.getAttribute("drtpPort") == null ? ""
                    : request.getAttribute("drtpPort").toString();
            String svrFunc= request.getAttribute("svrFunc") == null ? ""
                    : request.getAttribute("svrFunc").toString();
            String saddr = request.getAttribute("saddr") == null ? ""
                    : request.getAttribute("saddr").toString();         
            String outCardAmount = request.getAttribute("outCardAmount") == null ? ""
                    : request.getAttribute("outCardAmount").toString();
            String room = request.getAttribute("room")== null?"":request.getAttribute("room").toString();
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
		<form action="/smartcardweb/electransok.do" method="post"
			name="writeCardForm">
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
											<%
											if ("".equals(sbank_acc)) {
											%>
											您之前没有绑定过房间,
											<br />
											现在转账的房间号为
											<%=room%>
											！
											<br />
											是否确定继续转账？
											<%
											} else {
											%>
											您之前绑定的房间号为
											<%=sbank_acc%>
											,
											<br />
											与现在转账的房间号
											<%=room%>
											不符！
											<br />
											是否确定继续转账？
											<%
											}
											%>

											<input type="hidden" name="cardphyid" value="<%=cardphyid%>" />
											<input type="hidden" name="money" value="<%=money%>" />
											<input type="hidden" name="txCnt" value="<%=txCnt%>" />
											<input type="hidden" name="sphone3" value="<%=sphone3%>" />
											<input type="hidden" name="saddr" value="<%=saddr%>" />
											<input type="hidden" name="sdate3" value="<%=sdate3%>" />
                                            <input type="hidden" name="stime3" value="<%=stime3%>" />
                                            <input type="hidden" name="ipServer" value="<%=ipServer%>" />
                                            <input type="hidden" name="drtpPort" value="<%=drtpPort%>" />
                                            <input type="hidden" name="svrFunc" value="<%=svrFunc%>" />
											<input type="hidden" name="outCardAmount" value="<%=outCardAmount%>" />
											<input type="hidden" name="room" value="<%=room%>" />
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:writeCardForm.submit();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td align="center">

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



