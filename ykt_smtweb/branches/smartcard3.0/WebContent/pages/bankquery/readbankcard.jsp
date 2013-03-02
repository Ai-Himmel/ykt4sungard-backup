<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration;"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>请刷银行卡</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
			String read_card_device_port = KSConfiguration.getInstance()
					.getProperty("read_card_device_port", "0");
			String bankno = "";
		%>
		<script type="text/JavaScript">
		 var sn="";
		 function readCard()
        { 
          var msg = document.getElementById("msg");
          var device_port = 2;         
          var time=10;
          readCardForm.all.RFScanner.PortNo=device_port;//读卡器端口设置
         // ret = readCardForm.all.RFScanner.ReadBankCard(device_port,sn,time);
          var  ret=0; 
           if(ret==0){//读卡成功
            //  readCardForm.all.bankno.value=sn;
              
           }else{
            // msg.innerHTML="读卡失败，点确定后，请再次刷卡";    
            msg.innerHTML="读卡失败,请点取消退出系统";   
            return;
           }
        }
        function check(){//判断卡号是否正确,如不正确退出系统
           readCardForm.submit();
        }
        
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
	</head>
	<body scroll="no" onload="readCard()">
		<form action="/smartcardweb/querybankpwd.do" method="post"
			name="readCardForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="screencenter">
					<table>
						<tr align="center">
							<td class="msgcenter">
								<input type="hidden" name="bankno" />
								请刷指定银行卡!
								<br />
							</td>
						</tr>
					</table>
				</div>
				<div id="buttonbottom">
					<table>
						<tr>
							<td align="left" width="200">
								<a onclick="javascript:check();" onmouseup="MM_swapImgRestore()"
									onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
										src="/smartcardweb/pages/images/send.gif" name="send"
										width="109" height="48" border="0" id="send" /> </a>
							</td>
							<td align="right" width="200">
								<a
									onclick="javascript: window.location='/smartcardweb/index.do';"
									onmouseup="MM_swapImgRestore()"
									onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
										src="/smartcardweb/pages/images/cancel.gif" name="cancel"
										width="109" height="48" border="0" id="cancel" /> </a>
							</td>
						</tr>
					</table>
				</div>
			</div>
			<div id="bottom"></div>
			<object id="RFScanner"
				classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
				height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7" />
		</form>
	</body>
</html>



