<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>����ת��д��</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
			String logincardphyid =  session.getAttribute("cardphyid") == null ? ""
                    : session.getAttribute("cardphyid").toString();					
		     String webserverip = KSConfiguration.getInstance().getProperty(
                    "webserverip");
            String webserverport = KSConfiguration.getInstance().getProperty(
                    "webserverport");
            String webserverapp = KSConfiguration.getInstance().getProperty(
                    "webserverapp");

			String read_card_device_port = KSConfiguration.getInstance()
					.getProperty("read_card_device_port", "0");
		%>
		<script type="text/JavaScript">		
		function docancel(){
		      window.location='/smartcardweb/index.do';
		}
		function doCardCharge(){		      
           var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
           var device_port = '<%=read_card_device_port%>'; 
           var logincardphyid = '<%=logincardphyid%>'
           writeCardForm.all.RFScanner.PortNo=device_port;//�������˿�����
           var ret=writeCardForm.all.RFScanner.DoScan();
           if(ret==0){
           //�����ɹ�
               var cardphyid = writeCardForm.all.RFScanner.CardPhyID; 	
               if(cardphyid==logincardphyid){
                    alert("�˿�Ϊת������������տ��");
                    return false;
               }else{
	               var rrt = writeCardForm.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");    
	               if(rrt == 0){
	                 var pktret = writeCardForm.all.RFScanner.ReadCardPocket(1,cardphyid);      
	                 if(pktret==0){
	                     writeCardForm.action='/smartcardweb/cardcardoutcheck.do';    
	                     writeCardForm.all.outcardphyno.value=cardphyid;                     
	                     writeCardForm.all.outcardbalance.value=writeCardForm.all.RFScanner.GetPacketInfo("cardbal");                     
	                     writeCardForm.all.outcardcnt.value=writeCardForm.all.RFScanner.GetPacketInfo("pay_card_cnt");      
	                     writeCardForm.submit();
	                  }else{
	                     alert("����ʧ�ܣ�����ȷ���ÿ�Ƭ...");
	                     return false;
	                  }
	               }else{
	                    alert("���粻ͨ�����Ժ�����...");
	                    return false;
	                }
               }      
           }else{
               alert("����ʧ�ܣ�����ÿ�Ƭ...");
               return false;
           }
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
		<style type="text/css">
.��ʽ5 {
	font-family: "����";
	color: #000000;
	font-size: 18px;
}

.��ʽ13 {
	font-family: "����";
	color: #ff0000;
	font-size: 18px;
}
</style>
	</head>
	<body scroll="no">
		<form action="/smartcardweb/cardcardoutcheck" method="post" name="writeCardForm">
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
										<td height="320" align="center" class="show" id="msg">
											�뽫  <font style="font-size: 22px;"><b>ת�뿨</b></font> �����ڶ������ϣ���� <font style="font-size: 22px;"><b>ȷ��</b></font> ������Ϣȷ��
											<br/>
											<br/>
											����� <font style="font-size: 22px;"><b>ȷ��</b></font> ����ȴ� ����Ҫ�ƶ���Ƭ����  
											<input type="hidden" name="outcardphyno" />
											<input type="hidden" name="outcardbalance" />
											<input type="hidden" name="outcardcnt" />
										</td>
									</tr>

								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:doCardCharge();"
												onmouseup="MM_swapImgRestore()"
												onmouseout="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
                                            <a
                                                onclick="javascript:docancel();"
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



