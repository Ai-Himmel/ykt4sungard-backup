<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>ˮ��Ǯ����ʼ��</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%

			String webserverip = KSConfiguration.getInstance().getProperty(
					"webserverip");
			String webserverport = KSConfiguration.getInstance().getProperty(
					"webserverport");
			String webserverapp = KSConfiguration.getInstance().getProperty(
					"webserverapp");
			String read_card_device_port = KSConfiguration.getInstance()
					.getProperty("read_card_device_port", "0");
		%>
		<script language="javascript">
		function doinit(){
		 	var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
            var device_port = '<%=read_card_device_port%>';
            document.all.RFScanner.PortNo=device_port;
			var ret=document.all.RFScanner.DoScan();
	           if(ret==0){//�����ɹ�         
	        	   var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
		   			if(rrt == 0){
		   			  var cardphyid = document.all.RFScanner.CardPhyID;
		              var pret = writeCardForm.all.RFScanner.ReadWaterCtlPacket(3,cardphyid); 
						if(0==pret){
								alert("��ԡˮ��Ǯ���ѳ�ʼ��������Ҫʹ�ô˹��ܡ�����ֱ��ʹ��ˮ��ת��");
								return false;
							}else{
								var iret = writeCardForm.all.RFScanner.InitWaterCtlPocket(serverbase+"getpocketinit.do",3,cardphyid); 
								if(0==iret){
									 window.location='/smartcardweb/pages/waterctl/initwaterpocketsuccess.jsp'; 
									 return false;
								}else if(-1==iret){
									return false;
								}else if(1==iret){
									 window.location='/smartcardweb/pages/waterctl/initwaterpocketerror.jsp'; 
									return false;
								}else{
									alert("��ԡˮ��Ǯ������δ֪�������Ժ����ԣ�������="+iret);
									return false;
								}
							}	
		   			}else{
						alert("���粻ͨ�����Ժ�����...");
						return false;
					}    
	              
	           }else{
                  alert("����ʧ�ܣ�����ÿ�Ƭ...");
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
		<style type="text/css">
		.��ʽ12 {
		font-family: "����"; 
		color: #000000; 
		font-size: 16px; 
		}
		.��ʽ13 {
		font-family: "����"; 
		color: #000000; 
		font-size: 18px; 
		}
		.��ʽ14 {
		font-family: "����"; 
		color: #ff0000; 
		font-size: 18px; 
		}
	}
	</style>
	</head>
	<body scroll="no">
		<form action="" method="post"
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
								<table width="70%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td height="300" align="left" class="show" id="errmsg" colspan="2">
											��ԡˮ��Ǯ����ʼ��ע�����<br><br>
											1��	��Ǯ����ʼ��ֻ��Բ���δ��ͨ��ԡˮ��Ǯ�����û�<br>
											2��	��ʼ��ˮ��Ǯ�����Ǯ������<br>
											3��   �Ѿ���ͨ��ʹ��ˮ��Ǯ�����û������Դ˹���<br>
											<br>
											<br>
											<br>
											<br>
											<html:errors />
											&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��ȷ�Ϸźÿ�! &nbsp;
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:doinit();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='/smartcardweb/usrexit.do';"
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
				classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
				height="0" codebase="/smartcardweb/rf35.cab#version=2,0,0,7" />
		</form>
	</body>
</html>

