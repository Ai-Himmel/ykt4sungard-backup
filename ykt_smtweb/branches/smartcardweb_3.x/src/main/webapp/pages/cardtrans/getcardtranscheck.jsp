<%@ page contentType="text/html;charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>卡卡转账确认</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
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
		
		function dochecktrans()
        {
                writeCardForm.submit();
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
}
</style>
	</head>
	<body scroll="no">
		<form action="/smartcardweb/cardchecktrans.do" method="post"
			name="writeCardForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/zz.gif" width="314"
									height="82" />
							</div>

							<div id="content_input">
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td height="50" class="样式13">
											老卡卡号
											<input type="hidden" name="oldCardNo"
												value="<%=request.getAttribute("oldCardNo") == null ? "0"
					: request.getAttribute("oldCardNo")%>" />
											<input type="hidden" name="oldCardBalance"
												value="<%=request.getAttribute("oldCardBalance") == null ? "0"
					: request.getAttribute("oldCardBalance")%>" />
											<input type="hidden" name="oldCardPwd"
												value="<%=request.getAttribute("oldCardPwd") == null ? ""
					: request.getAttribute("oldCardPwd")%>" />
					<input type="hidden" name="reqcardno"
                                                value="<%=request.getAttribute("reqcardno") == null ? "0"
                    : request.getAttribute("reqcardno")%>" />
                                            <input type="hidden" name="reqcardBalance"
                                                value="<%=request.getAttribute("reqcardBalance") == null ? "0"
                    : request.getAttribute("reqcardBalance")%>" />
                                            <input type="hidden" name="reqcardcnt"
                                                value="<%=request.getAttribute("reqcardcnt") == null ? ""
                    : request.getAttribute("reqcardcnt")%>" />
										</td>
										<td>
											<%=request.getAttribute("oldCardNo") == null ? ""
					: request.getAttribute("oldCardNo")%>
										</td>
									</tr>

									<tr>
										<td width="320" height="50" class="样式13">
											老卡余额
										</td>
										<td>
											<%=request.getAttribute("oldCardBalance") == null?0
					: Float.parseFloat(request.getAttribute("oldCardBalance").toString())/100%>
											元
										</td>
									</tr>
									
									<tr>
                                        <td width="320" height="50" class="样式13">
                                            老卡姓名
                                        </td>
                                        <td>
                                            <%=request.getAttribute("oldCardName") == null ? ""
                    : request.getAttribute("oldCardName")%>
                                        </td>
                                    </tr>

									<tr>
										<td height="170" align="center" class="show" id="errmsg"
											colspan="2">
											<html:errors />
											<br>
											<br>
                                           
											请确认将老卡放置于读卡器上! &nbsp;点击确定进行扣款操作
											 <br>
											<b>请不要移动卡片！</b> 
											<br>
											<br>
											<br>
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:dochecktrans();"
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
						<div id="content_right"></div>
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

