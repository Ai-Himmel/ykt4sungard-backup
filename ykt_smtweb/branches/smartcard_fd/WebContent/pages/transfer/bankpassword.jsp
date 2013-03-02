<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<html>
	<head>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
		<title>输入银行卡密码</title>
		<%
		    String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		    String bankno = request.getParameter("bankno");
		    session.setAttribute("bankno",bankno);
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
     
        function tab()
        {
            passForm.password.focus();
        }
        
        function check()
        {
            if(passForm.password.value.length < 6){
               alert("请输入6位密码！" );
               return;   
            }
            passForm.submit();
        }
     


 	</script>

	<style type="text/css">
		.样式12 {
		font-family: "宋体"; 
		color: #000000; 
		font-size: 16px; 
		}
	</style>




	<body scroll="no" onload="javascript:tab();">
		<form action="/smartcardweb/inputmoney.do" method="post"  name="passForm" >
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="login">
						<div id="login_left"></div>
						<div id="login_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/bankpw.gif" width="343"
									height="57" />
							</div>
							<div>
								<ul>
									<li >&nbsp;</li>
									<li >&nbsp;</li>
									<li >&nbsp;</li>
									<li >&nbsp;</li>
									<li >&nbsp;</li>
									<li >&nbsp;</li>
									<li >&nbsp;</li>
									<li >&nbsp;</li>
									<li >&nbsp;</li>
									<li >&nbsp;</li>
									<li >&nbsp;</li>
								</ul>
							</div>
							<div id="login_input">
								<img src="/smartcardweb/pages/images/pw.gif" align="absmiddle" />
								<input name="password" type="password" class="info" size="12" maxlength="6" />
								<input type="hidden" name="cardno" />
							</div>
							<div id="login_blank1" class="样式12">
								<html:errors />
								&nbsp;
							</div>
							 <div id="login_blank1" class="样式12">
                                 <p >注意：本机只支持中国农业应行转账服务</p>
                             </div>
							
							<div id="login_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:check();"
												onmouseup="MM_swapImgRestore()"
												onmouseout="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" />
											</a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/index.do';"
												onmouseup="MM_swapImgRestore()"
												onmouseout="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
													src="/smartcardweb/pages/images/cancel.gif" name="cancel"
													width="109" height="48" border="0" id="cancel" />
											</a>
											<object id="RFScanner"
												classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
												width="0" height="0"
												codebase="/smartcardweb/rf35.cab#version=2,0,0,7"></object>
										</td>
									</tr>
								</table>

							</div>
						</div>
						<div id="login_right"></div>
						<div class="clear"></div>

					</div>
				</div>
			</div>
			<div id="bottom"></div>

		</form>
	</body>
</html>

