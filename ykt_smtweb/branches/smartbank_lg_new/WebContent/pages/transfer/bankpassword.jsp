<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>
		<title></title>
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet"
			type="text/css" />
	</head>
	<% 
		String card_no_first = session.getAttribute("card_no_first").toString();	
	%>
 
	<script>
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
		
	  function readCard()
        {  
           var cardno="";
           var serverbase = "http://"+'<%=webserverip%>'+":"+'<%=webserverport%>'+"/"+'<%=webserverapp%>'+"/";
		   pwdForm.all.RFScanner.PortNo=<%=read_card_device_port%>;
		   var ret1=pwdForm.all.RFScanner.DoScan();
           if(ret1==0){//读卡成功
              cardno = document.all.RFScanner.CardNo;
              document.pwdForm.cardno.value=cardno;
           }
           var rrt = pwdForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
		   if(rrt == 0){
				var ret2 = pwdForm.all.RFScanner.ReadCardPocket(1,cardno,"");
				if(ret2 == 0){
					var bala = pwdForm.all.RFScanner.GetPacketInfo("bala");
					var cxCnt =  pwdForm.all.RFScanner.GetPacketInfo("total_cnt");
					pwdForm.all.cardBala.value = bala;
					pwdForm.all.cxCnt.value = cxCnt;
				}
			}
               return cardno;
        }
        
	   function  check(){//这里要判断是否同一张卡
	      
	       var msg = document.getElementById("msg");
	          
	       if(document.pwdForm.password.value=="" || document.pwdForm.password.value.length<6){
	           msg.innerHTML="请输入6位银行密码";
	           document.pwdForm.password.focus();
	           return false;
	       }
	       // document.getElementById("send").style.display='none';
           if(readCard()==<%=card_no_first%>){//前后卡一致,可以转账
              document.pwdForm.deviceId.value=readfile();
              msg.innerHTML="正在转账，请稍候......";
              document.pwdForm.submit();
           }else{//前后卡不一致,到首页面
              msg="转账过程中不能换卡，请重新转账.";
              window.location='<%=path%>/pages/transfer/returninfo.jsp?msg='+msg
           }
	   }
	  
	</script>
   
	<body scroll="no" onload="javascript:document.pwdForm.password.focus();">
	 <html:form   action="dealTransfer.do" method="post">
	 
		<div id="mid_top"></div>
		<div id="middle">
		 <div  id="screencenter">
		 <table> 
			<tr ><td class="msgcenter"><b>请输入银行卡密码</b></td>
			<td>
			<input type="hidden" name="cardno" value=""/>
			<input type="hidden" name="deviceId" value=""/>
			<input type="hidden" name="cardBala" value=""/>
			<input type="hidden" name="cxCnt" value=""/>
			<input class="inputbox"  type="password"  maxlength="10"    size="10" name="password"  /></td>
			</tr>
			<tr>
			<td  align="left" class="msgcenter" id="msg"></td>
			
			</tr>
		 </table>	        
		</div>
		<div id="buttonbottom">
		    <table>       
			        <tr>
						 <td align="left" width="200">
								<a onclick="javascript:check();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','<%=path%>/pages/images/senda.gif',1)"><img
													src="<%=path%>/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
						</td>
						
						<td  align="right" width="200">
								<a 	onclick="javascript: window.location='<%=path%>/index.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('back','','<%=path%>/pages/images/backa.gif',1)"><img
													src="<%=path%>/pages/images/back.gif" name="back"
													width="109" height="48" border="0" id="back" /> </a>
						</td>
					</tr>
			       </table>
		</div>
		</div>
		<div id="bottom"></div>
			<object id="RFScanner"
					classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}"
								width="0" height="0"
				    codebase="<%=path%>/rf35.cab#version=2,0,0,7"></object>
	</html:form>
	</body>
</html>

