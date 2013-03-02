<%@ page contentType="text/html; charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<title>密码修改</title>
	
		<script language="javascript"><!--
        function addnum(num)
        {
		if(customerPwdUpdateForm.all.nowinput.value=="1" && customerPwdUpdateForm.all.pwd.value.length < 6){
			customerPwdUpdateForm.all.pwd.value+=num;
		}
		else if(customerPwdUpdateForm.all.nowinput.value=="2"  && customerPwdUpdateForm.all.newPwd.value.length < 6){
			customerPwdUpdateForm.all.newPwd.value+=num;
		}
 		else if(customerPwdUpdateForm.all.nowinput.value=="3" && customerPwdUpdateForm.all.againPwd.value.length < 6){
			customerPwdUpdateForm.all.againPwd.value+=num;
		}
        }
        function backnum()
        {
		if(customerPwdUpdateForm.all.nowinput.value=="1")
			customerPwdUpdateForm.all.pwd.value=customerPwdUpdateForm.all.pwd.value.substring(0,customerPwdUpdateForm.all.pwd.value.length-1);
		else if(customerPwdUpdateForm.all.nowinput.value=="2")
			customerPwdUpdateForm.all.newPwd.value=customerPwdUpdateForm.all.newPwd.value.substring(0,customerPwdUpdateForm.all.newPwd.value.length-1);
		else if(customerPwdUpdateForm.all.nowinput.value=="3")
			customerPwdUpdateForm.all.againPwd.value=customerPwdUpdateForm.all.againPwd.value.substring(0,customerPwdUpdateForm.all.againPwd.value.length-1);
        }     
        function tab()
        {
               if(customerPwdUpdateForm.all.nowinput.value=="1")
                   customerPwdUpdateForm.all.newPwd.focus();
               else if(customerPwdUpdateForm.all.nowinput.value=="2")
                   customerPwdUpdateForm.all.againPwd.focus();
               else if(customerPwdUpdateForm.all.nowinput.value=="3")
                   customerPwdUpdateForm.all.pwd.focus();
        }
         function writeCard()
        {
             
             
               if(customerPwdUpdateForm.all.newPwd.value.length < 6){
              	msg.innerHTML = '密码长度为6位';
              	customerPwdUpdateForm.all.newPwd.focus();
              	return false;
              }
               if(customerPwdUpdateForm.all.againPwd.value.length < 6){
              	msg.innerHTML = '密码长度为6位';
              	customerPwdUpdateForm.all.againPwd.focus();
              	return false;
              }
              if(customerPwdUpdateForm.all.newPwd.value!=customerPwdUpdateForm.all.againPwd.value){
              	msg.innerHTML = '两次新密码不匹配';
              	customerPwdUpdateForm.all.newPwd.focus();
              	return false;
              }
              
            
              
              if(!fucCheckNUM(customerPwdUpdateForm.all.newPwd.value)){
              	msg.innerHTML = '密码必须为数字';
              	customerPwdUpdateForm.all.newPwd.focus();
              	return false;
              }
              
              if(!fucCheckNUM(customerPwdUpdateForm.all.againPwd.value)){
              	msg.innerHTML = '密码必须为数字';
              	customerPwdUpdateForm.all.againPwd.focus();
              	return false;
              }              
           var device_port = <%=read_card_device_port%>;           
           logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
           var ret=logonForm.all.RFScanner.DoScan();
           if(ret==0){///读卡成功
             //alert(url+"?cardno="+document.all.RFScanner.CardNo);
              document.customerPwdUpdateForm.cardno.value=document.all.RFScanner.CardNo;
              customerPwdUpdateForm.submit(); 
           }else if(ret==-1){
              alert('系统暂时不可用'+ret);
           } 
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
		
		
		 function toup(){
           document.customerPwdUpdateForm.newPwd.focus();
        }
        function todown(){
           document.customerPwdUpdateForm.againPwd.focus();
        }
        function init(){
            document.getElementById("previce").style.display='none';
            document.getElementById("next").style.display='none';
		    javascript:document.customerPwdUpdateForm.newPwd.focus();
        }

        --></script>
        
        
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
			font-size: 16; 
			}
		</style>
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet" type="text/css" />
	</head>
	<body scroll="no" onload="init();" >
		<form action="<%=path%>/editpwd.do" method="post"
			name="customerPwdUpdateForm">
			<input name="cardno" type="hidden"/>
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="login">
						<div id="login_left"></div>
						<div id="login_middle">
							<div align="center">
								<img src="<%=path%>/pages/images/password.gif" width="343"
									height="57" />
							</div>
							<div>
								<ul>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/0.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/0a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/0.gif)"
										onclick="javascript:addnum(0)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/1.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/1a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/1.gif)"
										onclick="javascript:addnum(1)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/2.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/2a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/2.gif)"
										onclick="javascript:addnum(2)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/3.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/3a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/3.gif)"
										onclick="javascript:addnum(3)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/4.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/4a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/4.gif)"
										onclick="javascript:addnum(4)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/5.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/5a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/5.gif)"
										onclick="javascript:addnum(5)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/6.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/6a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/6.gif)"
										onclick="javascript:addnum(6)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/7.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/7a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/7.gif)"
										onclick="javascript:addnum(7)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/8.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/8a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/8.gif)"
										onclick="javascript:addnum(8)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/9.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/9a.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/9.gif)"
										onclick="javascript:addnum(9)"></li>
									<li
										onmouseup="this.style.background='url(<%=path%>/pages/images/del.gif)'"
										onmousedown="this.style.background='url(<%=path%>/pages/images/dela.gif)'"
										style="cursor:hand; background:url(<%=path%>/pages/images/del.gif)"
										onclick="javascript:backnum()"></li>
								</ul>
							</div>
							<div id="login_input">
								<table width="520" border="0" cellpadding="0" cellspacing="0">
									<tr>
										<td width="162" rowspan="3">
											<img src="<%=path%>/pages/images/put.gif" width="152"
												height="40" />
											<input type="hidden" name="nowinput" value="1" />											

										</td>
										<!--<td width="134" align="right">
											<img src="<%=path%>/pages/images/q1.gif" width="90"
												height="24" />
										</td>
										<td width="304">
											<input type="password" name="pwd" size="20" maxlength="6"
												class="info"
												onfocus="javascript:customerPwdUpdateForm.nowinput.value='1';" />
										</td>
									--></tr>
									<tr>
										<td align="right">
											<img src="<%=path%>/pages/images/q2.gif" width="90"
												height="23" />
										</td>
										<td>
											<input type="password" name="newPwd" maxlength="6" size="20"
												class="info"
												onfocus="javascript:customerPwdUpdateForm.nowinput.value='2';" />
										</td>
									</tr>
									<tr>
										<td align="right">
											<img src="<%=path%>/pages/images/q3.gif" width="134"
												height="24" />
										</td>
										<td>
											<input type="password" name="againPwd" maxlength="6"
												class="info" size="20"
												onfocus="javascript:customerPwdUpdateForm.nowinput.value='3';" />
										</td>
									</tr>
									<tr>
										<td class="样式13" id="msg" align="center" colspan="3">
											<html:errors />
											&nbsp;
											<%
											     String    msg = request.getAttribute("msg")==null?"": request.getAttribute("msg").toString();
											%>
											<%=msg%>
										</td>
									</tr>
								</table>
							</div>
							<div id="login_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:writeCard();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','<%=path%>/pages/images/senda.gif',1)"><img
													src="<%=path%>/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a onclick="javascript: window.location='<%=path%>/xykw.do';" onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('back','','<%=path%>/pages/images/backa.gif',1)"><img
													src="<%=path%>/pages/images/back.gif" name="back"
													width="109" height="48" border="0" id="back" /> </a>
										</td>
									</tr>
									
									<tr>
											<td align="right" colspan="2">
								   <a onclick="javascript:toup()"
								            onmouseout="MM_swapImgRestore()"
								            onmousedown="MM_swapImage('previce','','<%=path%>/pages/images/previcea.gif',1)"><img
									        src="<%=path%>/pages/images/previce.gif" name="previce"
									        width="109" height="48" border="0" id="previce" /> </a>

									<a onclick="javascript:todown()"
								    onmouseout="MM_swapImgRestore()"
								    onmousedown="MM_swapImage('next','','<%=path%>/pages/images/nexta.gif',1)"><img
									src="<%=path%>/pages/images/next.gif" name="next"
									width="109" height="48" border="0" id="next" /> </a>
														
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
		</form>
		<form  method="post" name="logonForm" >
		<object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
								width="0" height="0"
										codebase="<%=path%>/rf35.cab#version=2,0,0,7"></object>
	</form>
	</body>
</html>


