<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>
		<title>密码修改</title>
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet" type="text/css" />
		
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
		function writeCard(){
			var device_port = <%=read_card_device_port%>;
            customerPwdUpdateForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
			var msg = document.getElementById("msg");
			 var ret=customerPwdUpdateForm.all.RFScanner.ChangePassWord(
              	customerPwdUpdateForm.all.paramKey.value,
              	customerPwdUpdateForm.all.newPwd.value,
              	customerPwdUpdateForm.all.cardno.value);
              if(ret==0)//修改密码成功
              {
              	msg.innerHTML = "密码修改成功。";
              }else{
              	msg.innerHTML = "密码修改成功。但写卡失败，可以用新密码补改一次密码！";
              }
		}
		</script>
		<style type="text/css">
	
		.样式13 {
			font-family: "黑体"; 
			color: #ff0000; 
			font-size: 18px; 
			}
		</style>
	</head>
	<body scroll="no" onload="javascript:writeCard();" onkeydown="return (event.keyCode!=8)">
	<form action="<%=path%>/editpwd.do" method="post"
			name="customerPwdUpdateForm">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layer1">
				<div id="content">
					<div id="content_left"></div>
					<div id="content_middle">
					<div align="center">
								<img src="<%=path%>/pages/images/czjg.gif" width="314"
								height="82" />
							</div>

						<div id="content_input">
							<table width="50%" border="0" align="center" cellpadding="0"
								cellspacing="0" class="box">

								<tr>
									<td height="320" align="center" class="样式13" id="msg">
										<input type="hidden" name="paramKey"
												value="<%=request.getAttribute("paramKey") == null ? ""
					: request.getAttribute("paramKey")%>" />
											<input type="hidden" name="cardno"
												value="<%=request.getAttribute("cardno") == null ? ""
					: request.getAttribute("cardno")%>" />
										<input type="hidden" name="newPwd"
												value="<%=request.getAttribute("newpwd") == null ? ""
					: request.getAttribute("newpwd")%>" />&nbsp;										
									</td>
								</tr>

							</table>
						</div>
						<div id="content_buttom">
							<table>
								<tr>
									<td align="center">
										<a
											onclick="javascript: window.location='<%=path%>/main.do';"
											onmouseout="MM_swapImgRestore()"
											onmouseover="MM_swapImage('send','','<%=path%>/pages/images/senda.gif',1)"><img
												src="<%=path%>/pages/images/send.gif" name="send"
												width="109" height="48" border="0" id="send" /> </a>
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
