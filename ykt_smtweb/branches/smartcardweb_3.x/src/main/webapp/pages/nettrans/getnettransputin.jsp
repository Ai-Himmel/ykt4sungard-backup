<%@ page contentType="text/html; charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<html>
	<head>
		<title>网络转账输入</title>
		<script language="javascript">			
	       function addnum(num)
        {
            if(logonForm.all.stuempno.value.length < 15){
                if(logonForm.all.locknum.value=="1"){
                    logonForm.all.stuempno.value+=num;
                }else{
                    logonForm.all.stuempno.value+=num.toUpperCase();
                }
              }

        }
        function numlock(){
            if("1"==logonForm.all.locknum.value){
                logonForm.all.locknum.value="2";
                logonForm.all.lock.style.background='url(/smartcardweb/pages/images/lock.gif)';
                
            }else{
                logonForm.all.locknum.value="1";
                logonForm.all.lock.style.background='url(/smartcardweb/pages/images/locka.gif)';
            }
        }
        
        function cancelnum()
        {
            logonForm.all.stuempno.value=logonForm.all.stuempno.value.substring(0,logonForm.all.stuempno.value.length-1);
  
        }
        function tab()
        {
             logonForm.all.stuempno.focus();
        }
        
	   function readCard(){
	   if(!document.all.send.disabled){
	 	if(logonForm.all.stuempno.value==''){
	            alert("请填写转账账号！");
	            logonForm.all.stuempno.focus();
	            return false;
	        }
	        document.all.send.disabled = true;        
	        logonForm.submit();
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
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
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
	font-size: 16px;
	font-weight: bold;
}

.样式12 {
	font-family: "宋体";
	color: #000000;
	font-size: 20px;
	font-weight: bold;
}

.样式10 {
	font-family: "黑体";
	color: #606060;
	font-size: 20px;
	font-weight: bold;
}

.样式9 {
	font-family: "宋体";
	color: #ff0000;
	font-size: 18px;
}
</style>
	</head>
	<body scroll="no"
		onload="MM_preloadImages('/smartcardweb/pages/images/senda.gif','/smartcardweb/pages/images/cancela.gif')">
		<form action="/smartcardweb/nettransputin.do" method="post"
			name="logonForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="qsrzhh">
						<table width="900" border="0" align="center" cellpadding="0"
							cellspacing="0">
							<tr>
								<td height="32" colspan="2">
									&nbsp;
									<input type="hidden" name="nowinput" value="1" />
									<input type="hidden" name="locknum" value="2" />
								</td>
							</tr>
							<tr>
								<td width="355" height="81" valign="top">
									&nbsp;
								</td>
								<td width="505" rowspan="2" valign="top">
									<table width="100%" border="0" cellspacing="0" cellpadding="0">
										<tr>
											<td>
												&nbsp;
											</td>
										</tr>
										<tr>
											<td>
												&nbsp;
											</td>
										</tr>
										<tr>
											<td>
												<div id="mis">
													<div>
														<ul>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/a.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/aa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/a.gif)"
																onclick="javascript:addnum('a')" ondblclick="javascript:addnum('a')"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/b.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ba.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/b.gif)"
																onclick="javascript:addnum('b')" ondblclick="javascript:addnum('b')"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/c.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ca.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/c.gif)"
																onclick="javascript:addnum('c')" ondblclick="javascript:addnum('c')"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/d.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/da.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/d.gif)"
																onclick="javascript:addnum('d')" ondblclick="javascript:addnum('d')"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/e.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ea.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/e.gif)"
																onclick="javascript:addnum('e')" ondblclick="javascript:addnum('e')"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/f.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/fa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/f.gif)"
																onclick="javascript:addnum('f')" ondblclick="javascript:addnum('f')"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/g.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ga.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/g.gif)"
																onclick="javascript:addnum('g')" ondblclick="javascript:addnum('g')"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/h.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ha.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/h.gif)"
																onclick="javascript:addnum('h')" ondblclick="javascript:addnum('h')"></li>
															<li onmouseup="this.style.background='url(/smartcardweb/pages/images/i.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ia.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/i.gif)"
																onclick="javascript:addnum('i')" ondblclick="javascript:addnum('i')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/j.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ja.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/j.gif)"
																onclick="javascript:addnum('j')" ondblclick="javascript:addnum('j')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/k.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ka.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/k.gif)"
																onclick="javascript:addnum('k')" ondblclick="javascript:addnum('k')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/l.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/la.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/l.gif)"
																onclick="javascript:addnum('l')" ondblclick="javascript:addnum('l')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/m.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ma.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/m.gif)"
																onclick="javascript:addnum('m')" ondblclick="javascript:addnum('m')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/n.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/na.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/n.gif)"
																onclick="javascript:addnum('n')" ondblclick="javascript:addnum('n')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/o.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/oa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/o.gif)"
																onclick="javascript:addnum('o')" ondblclick="javascript:addnum('o')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/p.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/pa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/p.gif)"
																onclick="javascript:addnum('p')" ondblclick="javascript:addnum('p')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/q.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/qa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/q.gif)"
																onclick="javascript:addnum('q')" ondblclick="javascript:addnum('q')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/r.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ra.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/r.gif)"
																onclick="javascript:addnum('r')" ondblclick="javascript:addnum('r')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/s.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/sa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/s.gif)"
																onclick="javascript:addnum('s')" ondblclick="javascript:addnum('s')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/t.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ta.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/t.gif)"
																onclick="javascript:addnum('t')" ondblclick="javascript:addnum('t')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/u.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ua.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/u.gif)"
																onclick="javascript:addnum('u')" ondblclick="javascript:addnum('u')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/xhx.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/xhx2.gif)'"
																style="cursor: hand; background: url(/smartcardweb/pages/images/xhx.gif)"
																onclick="javascript:addnum('_');"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/v.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/va.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/v.gif)"
																onclick="javascript:addnum('v')" ondblclick="javascript:addnum('v')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/w.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/wa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/w.gif)"
																onclick="javascript:addnum('w')" ondblclick="javascript:addnum('w')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/x.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/xa.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/x.gif)"
																onclick="javascript:addnum('x')" ondblclick="javascript:addnum('x')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/y.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/ya.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/y.gif)"
																onclick="javascript:addnum('y')" ondblclick="javascript:addnum('y')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/z.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/za.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/z.gif)"
																onclick="javascript:addnum('z')" ondblclick="javascript:addnum('z')"></li>
															<li onmouseup="this.style.background='url()'"
																onmousedown="this.style.background='url()'"
																style="cursor:hand; background:url()"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/0.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/0a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/0.gif)"
																onclick="javascript:addnum('0')" ondblclick="javascript:addnum('0')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/1.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/1a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/1.gif)"
																onclick="javascript:addnum('1')" ondblclick="javascript:addnum('1')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/2.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/2a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/2.gif)"
																onclick="javascript:addnum('2')" ondblclick="javascript:addnum('2')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/3.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/3a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/3.gif)"
																onclick="javascript:addnum('3')" ondblclick="javascript:addnum('3')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/4.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/4a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/4.gif)"
																onclick="javascript:addnum('4')" ondblclick="javascript:addnum('4')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/5.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/5a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/5.gif)"
																onclick="javascript:addnum('5')" ondblclick="javascript:addnum('5')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/6.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/6a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/6.gif)"
																onclick="javascript:addnum('6')" ondblclick="javascript:addnum('6')"></li>
															<li id="lock"
																style="cursor:hand; background:url(/smartcardweb/pages/images/lock.gif)"
																onclick="javascript:numlock()"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/7.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/7a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/7.gif)"
																onclick="javascript:addnum('7')" ondblclick="javascript:addnum('7')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/8.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/8a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/8.gif)"
																onclick="javascript:addnum('8')" ondblclick="javascript:addnum('8')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/9.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/9a.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/9.gif)"
																onclick="javascript:addnum('9')" ondblclick="javascript:addnum('9')"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/del.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/dela.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/del.gif)"
																onclick="javascript:cancelnum()" ondblclick="javascript:cancelnum()"></li>
															<li
																onmouseup="this.style.background='url(/smartcardweb/pages/images/tab.gif)'"
																onmousedown="this.style.background='url(/smartcardweb/pages/images/taba.gif)'"
																style="cursor:hand; background:url(/smartcardweb/pages/images/tab.gif)"
																onclick="javascript:tab()"></li>
														</ul>
													</div>


												</div>
											</td>
										</tr>
										<tr>
											<td>
												&nbsp;
											</td>
										</tr>
									</table>
								</td>
							</tr>
							<tr>
								<td height="250" align="center" valign="top">
									<p>
										&nbsp;
									</p>
									<table width="90%" border="0" align="right" cellpadding="0"
										cellspacing="0">
										<tr>
											<td align="center">
												<img src="/smartcardweb/pages/images/zhm1.gif" width="99"
													height="31" align="middle" />
											</td>
											<td>
												<input type="text" name="stuempno" class="样式11" size="15"
													maxlength="15" />
											</td>
										</tr>
										<tr>
											<td colspan="2">
												 <li>
                                                        本科生帐户号规则为 B+学号，例如 B123456789
                                                </li>
                                                 <li>
                                                        博士生和研究生请输入完整的学号,例如 DG4321、 MG1234
                                                </li>
                                                 <li>
                                                        充值前请务必确认查询出来的账户名是您需要充值的账户
                                                </li>
												&nbsp;
											</td>
										</tr>
										<tr>
											<td colspan="2">
											<html:errors />
												&nbsp;
											</td>
										</tr>
										<tr>
											<td align="right" colspan="2">
												<a onclick="javascript:readCard();"
													onmouseup="MM_swapImgRestore()"
													onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
														src="/smartcardweb/pages/images/send.gif" name="send"
														width="109" height="48" border="0" id="send" /> </a>

												<a
													onclick="javascript: window.location='/smartcardweb/g_zzyw.do';"
													onmouseup="MM_swapImgRestore()"
													onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
														src="/smartcardweb/pages/images/cancel.gif" name="cancel"
														width="109" height="48" border="0" id="cancel" /> </a>
											</td>
										</tr>

									</table>

									<div id="login_buttom">
									</div>
								</td>
							</tr>
						</table>
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

