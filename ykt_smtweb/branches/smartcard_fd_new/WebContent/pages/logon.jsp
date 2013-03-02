<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet" type="text/css" />
		<title>登录</title>
		<%
         // String para = request.getAttribute("para").toString();;
         String para = request.getAttribute("para")==null?"": request.getAttribute("para").toString();
         String group = request.getAttribute("group")==null?"":request.getAttribute("group").toString();
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
        function addnum(num)
        {
		if(logonForm.all.password.value.length < 6){
			logonForm.all.password.value+=num;
		}
        }
        function backnum()
        {
			logonForm.all.password.value=logonForm.all.password.value.substring(0,logonForm.all.password.value.length-1);
        }
        function tab()
        {
            logonForm.all.password.focus();
        }
        
        function readCard()
        { 
          
          var serverbase = "http://"+'<%=webserverip%>'+":"+'<%=webserverport%>'+"/"+'<%=webserverapp%>'+"/";
          var device_port = <%=read_card_device_port%>;      
          logonForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
          
           var ret=logonForm.all.RFScanner.DoScan();
           var  cardno ="";
           var rrt = logonForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
           if(rrt == 0){
           	if(ret==0){//读卡成功
              cardno = document.all.RFScanner.CardNo;
			  logonForm.all.cardno.value = cardno;
              document.logonForm.para.value='<%=para%>';
              document.logonForm.deviceId.value=readfile();
             
          	 }
          	 var ret2 = logonForm.all.RFScanner.ReadCardPocket(1,cardno,"");
          	 if(ret2==0){
           	   var bala = logonForm.all.RFScanner.GetPacketInfo("bala");
			   var cxCnt =  logonForm.all.RFScanner.GetPacketInfo("total_cnt");
			   logonForm.all.cardBala.value = bala;
			   logonForm.all.cxCnt.value = cxCnt;
			   logonForm.submit();
             }else if(ret == 1){
					//msg.innerHTML="请放置卡片";
					return false;
			 }else{
					//msg.innerHTML="请正确放置卡片";
					return false;
			 }
           
           }else{
				//msg.innerHTML="网络不通，请稍后重试";
				return false;
			}
        }


 	</script>


	</head>



	<body scroll="no" onload="javascript:document.logonForm.password.focus();">
		<form action="<%=path%>/logon.do" method="post" name="logonForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="login">
						<div id="login_left"></div>
						<div id="login_middle">
							<div align="center">
								<img src="<%=path%>/pages/images/password.gif" width="343" height="57" />
							</div>
							
							<div>
								<ul>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/0.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/0a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/0.gif)"
										onclick="javascript:addnum(0)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/1.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/1a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/1.gif)"
										onclick="javascript:addnum(1)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/2.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/2a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/2.gif)"
										onclick="javascript:addnum(2)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/3.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/3a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/3.gif)"
										onclick="javascript:addnum(3)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/4.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/4a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/4.gif)"
										onclick="javascript:addnum(4)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/5.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/5a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/5.gif)"
										onclick="javascript:addnum(5)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/6.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/6a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/6.gif)"
										onclick="javascript:addnum(6)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/7.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/7a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/7.gif)"
										onclick="javascript:addnum(7)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/8.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/8a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/8.gif)"
										onclick="javascript:addnum(8)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/9.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/9a.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/9.gif)"
										onclick="javascript:addnum(9)"></li>
									<li onmouseup="this.style.background='url(<%=path%>/pages/images/del.gif)'" onmousedown="this.style.background='url(<%=path%>/pages/images/dela.gif)'" style="cursor:hand; background:url(<%=path%>/pages/images/del.gif)"
										onclick="javascript:backnum()"></li>
								</ul>
							</div>
							<div id="login_blank">
								&nbsp;
							</div>
							<div id="login_blank">
								&nbsp;
							</div>
							<div id="login_input">
								<img src="<%=path%>/pages/images/card.gif" align="absmiddle" />
								<input name="password" type="password" class="info" size="20" maxlength="6" /> 
								<%if("1".equals(group)){ %>
								<p>本功能仅限邯郸校区内5号楼，东区学生公寓13-16号楼</p>
								<%}%>
								
								<input type="hidden" name="cardno" />
								<input type="hidden" name="para"/>
								<input type="hidden" name="deviceId"/>
								<input type="hidden" name="cardBala"/>
								<input type="hidden" name="cxCnt"/>
							</div>
							<div id="login_blank1" class="样式13">
								<html:errors />
								&nbsp;
							</div>
							 
							<div id="login_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:readCard();" onmouseup="MM_swapImgRestore()" onmouseout="MM_swapImgRestore()" onmousedown="MM_swapImage('send','','<%=path%>/pages/images/senda.gif',1)"><img src="<%=path%>/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a onclick="javascript: window.location='<%=path%>/index.do';" onmouseup="MM_swapImgRestore()" onmouseout="MM_swapImgRestore()" onmousedown="MM_swapImage('back','','<%=path%>/pages/images/backa.gif',1)"><img
													src="<%=path%>/pages/images/back.gif" name="back" width="109" height="48" border="0" id="back" /> </a>
											<object id="RFScanner" classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0" height="0" codebase="<%=path%>/rf35.cab#version=2,0,0,7"></object>
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

