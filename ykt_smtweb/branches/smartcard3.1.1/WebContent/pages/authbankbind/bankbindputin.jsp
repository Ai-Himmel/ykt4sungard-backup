<%@ page contentType="text/html; charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<html>
	<head>
		<title>圈存绑定</title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		 <%
		   String stuempno = request.getAttribute("stuempno") == null ? ""
					: request.getAttribute("stuempno").toString();
		   String bankacc = request.getAttribute("bankacc") == null ? ""
					: request.getAttribute("bankacc").toString();
		   String authcode = request.getAttribute("authcode") == null ? ""
					: request.getAttribute("authcode").toString();
					
		%>
		<script language="javascript">
        function addnum(num)
        {
		if(putinForm.all.nowinput.value=="1" && putinForm.all.bankacc.value.length < 20 ){
			putinForm.all.bankacc.value+=num;
		}
		else if(putinForm.all.nowinput.value=="2" && putinForm.all.authcode.value.length < 6 ){
			putinForm.all.authcode.value+=num;
		}
		else if(putinForm.all.nowinput.value=="3" && putinForm.all.reauthcode.value.length < 6 ){
			putinForm.all.reauthcode.value+=num;
		}
        }
        function cancelnum()
        {
		if(putinForm.all.nowinput.value=="1")
			putinForm.all.bankacc.value=putinForm.all.bankacc.value.substring(0,putinForm.all.bankacc.value.length-1);
		else if(putinForm.all.nowinput.value=="2")
			putinForm.all.authcode.value=putinForm.all.authcode.value.substring(0,putinForm.all.authcode.value.length-1);
		else if(putinForm.all.nowinput.value=="3")
			putinForm.all.reauthcode.value=putinForm.all.reauthcode.value.substring(0,putinForm.all.reauthcode.value.length-1);	
        }        
        function tab()
        {
              if(putinForm.all.nowinput.value=="1")
                 putinForm.all.authcode.focus();
              else if(putinForm.all.nowinput.value=="2")
                 putinForm.all.reauthcode.focus();
              else if(putinForm.all.nowinput.value=="3")
                  putinForm.all.bankacc.focus();
        }
        
        function binksubmit(){
    	 if(putinForm.all.bankacc.value==''){
    	 		alert("请输入银行卡号！");
    	 		putinForm.all.bankacc.focus();
    	 		return false;
    	 	}
    	 	
    	 if(putinForm.all.authcode.value==''){
    	 		alert("请输入圈存密码！");
    	 		putinForm.all.authcode.focus();
    	 		return false;
    	 	}
    	 if(putinForm.all.authcode.value!=''&&putinForm.all.authcode.value.length < 6){
    	 	     alert("圈存密码长度为6位！");
    	 		putinForm.all.authcode.focus();
    	 		return false;
    	 	   }
    	 	
    	 if(!fucCheckNUM(putinForm.all.authcode.value)){
    	 	 	alert("圈存密码为数字！");
    	 		putinForm.all.authcode.focus();
    	 		return false;
    	 	}
    	 	
    	 if(putinForm.all.authcode.value!=putinForm.all.reauthcode.value){
              	alert("您两次输入的圈存密码不一致！");
              	putinForm.all.reauthcode.focus();
              	return false;
              }
    	 	
    	 	putinForm.submit(); 
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
		<link href="pages/css/css.css" rel="stylesheet" type="text/css" />
	</head>
	<body scroll="no" >
		<form action="/smartcardweb/authbankbind.do" method="post"
			name="putinForm">

			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="login">
						<div id="login_left"></div>
						<div id="login_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/inputqc.gif" width="343"
									height="57" />
							</div>
							<div>
								<ul>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/0.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/0a.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/0.gif)"
									onclick="javascript:addnum(0)"></li>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/1.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/1a.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/1.gif)"
									onclick="javascript:addnum(1)"></li>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/2.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/2a.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/2.gif)"
									onclick="javascript:addnum(2)"></li>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/3.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/3a.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/3.gif)"
									onclick="javascript:addnum(3)"></li>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/4.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/4a.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/4.gif)"
									onclick="javascript:addnum(4)"></li>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/5.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/5a.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/5.gif)"
									onclick="javascript:addnum(5)"></li>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/6.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/6a.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/6.gif)"
									onclick="javascript:addnum(6)"></li>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/7.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/7a.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/7.gif)"
									onclick="javascript:addnum(7)"></li>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/8.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/8a.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/8.gif)"
									onclick="javascript:addnum(8)"></li>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/9.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/9a.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/9.gif)"
									onclick="javascript:addnum(9)"></li>
									<li onmouseup="this.style.background='url(/smartcardweb/pages/images/del.gif)'" onmousedown="this.style.background='url(/smartcardweb/pages/images/dela.gif)'" style="cursor:hand; background:url(/smartcardweb/pages/images/del.gif)"
									onclick="javascript:cancelnum()"></li>									
								</ul>
							</div>
							<div id="login_input">
								<table width="800" border="0" cellpadding="0"
									cellspacing="0">
									
									
									<tr>
										<td width="206" align="right">
											<img src="/smartcardweb/pages/images/yhkh.gif" width="114"
												height="24" />
												<input type="hidden" name="nowinput" value="1"/>
												<input type="hidden" name="stuempno" value="<%=stuempno%>"/>
										</td>
										<td >
											<input type="text" name="bankacc" value="<%=bankacc%>" size="20" maxlength="20" class="info"
												onfocus="javascript:putinForm.nowinput.value='1'"/>【请使用银行卡卡号，不能使用存折号】
										</td>
									</tr>
									<tr>
										<td width="206" align="right">
											<img src="/smartcardweb/pages/images/qcmm.gif"
												 />
										</td>
										<td>
											<input  type="password" name="authcode" value="<%=authcode%>"
												onfocus="javascript:putinForm.nowinput.value='2'" class="info"
												size="20" maxlength="8"/>【圈存密码为6位长度的数字】
										</td>
									</tr>
									
									<tr>
										<td width="206" align="right">
											<img src="/smartcardweb/pages/images/reqcmm.gif"  />
										</td>
										<td>
											<input type="password" name="reauthcode" maxlength="8"
												class="info" size="20"
												onfocus="javascript:putinForm.nowinput.value='3';" />【需与圈存密码输入一致】
										</td>
									</tr>
									
									<tr>
										<td colspan="2" class="info" align="center">
											<html:errors />&nbsp;
										</td>
									</tr>
									
								</table>
							</div>
							<div id="login_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:binksubmit();" onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" />
											</a>
										</td>
										<td>
											<a onclick="javascript: window.location='/smartcardweb/g_yhkw.do';" onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
													src="/smartcardweb/pages/images/cancel.gif" name="cancel"
													width="109" height="48" border="0" id="cancel" />
											</a>
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
                height="0"></object>
		</form>
	</body>
</html>