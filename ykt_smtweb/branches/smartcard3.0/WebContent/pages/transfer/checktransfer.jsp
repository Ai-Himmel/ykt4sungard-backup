<%@ page contentType="text/html;charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ page import="com.kingstargroup.fdykt.dto.CustomerDTO"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<html>
	<head>
		<title>���п�ת��ȷ��</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
			<%
		CustomerDTO  customer =(CustomerDTO)session.getAttribute("customer"); 
		String refno = request.getAttribute("refno") == null ? "" : request.getAttribute("refno").toString();
		String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
		String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
		String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		String cardBala =request.getAttribute("cardBala") == null ? "" : request.getAttribute("cardBala").toString();
		String money =request.getAttribute("money") == null ? "" : request.getAttribute("money").toString();
		String cardId =request.getAttribute("cardId") == null ? "" : request.getAttribute("cardId").toString();
		String serialNo =request.getAttribute("serialNo") == null ? "" : request.getAttribute("serialNo").toString();
	//	String outCardAmount =request.getAttribute("outCardAmount") == null ? "" : request.getAttribute("outCardAmount").toString();
		String tx_cnt =request.getAttribute("txCnt") == null ? "" : request.getAttribute("txCnt").toString();
		String bankcardno =request.getAttribute("bankcardno") == null ? "" : request.getAttribute("bankcardno").toString();
        String radomstr =request.getAttribute("radomstr") == null ? "" : request.getAttribute("radomstr").toString();
		%>
		<script language="javascript">
		function dobanktrans(){		    
			var cardno ='<%=cardId%>';
			var txCnt = '<%=tx_cnt%>';	
			var refno = '<%=refno%>';    
			var outCardAmount = '<%=0%>';  
			var money='<%=money%>';	
			var bankcardno = '<%=bankcardno%>';  
			var radomstr = '<%=radomstr%>'
			var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
			var device_port = '<%=read_card_device_port%>';
			document.all.RFScanner.PortNo=device_port;			
			var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			if(rrt == 0){
			var ret = document.all.RFScanner.ReadCardPocket(1,cardno,"");
			if(ret == 0){
			    document.all.errmsg.innerHTML="ת���������У����Ժ�...�����Ҫ�ȴ�30�룬�벻Ҫ�������߿�Ƭ"
                document.all.send.style.display="none";
				var doworkret = document.all.RFScanner.BankTransWriteCard(serverbase+"banktransfer.do",cardno,outCardAmount,txCnt,"money="+money+"&cardno="+cardno+"&refno="+refno+"&bankcardno="+bankcardno+"&radomstr="+radomstr);
				if(doworkret == 0){
				//ת�˳ɹ�		
				    window.location='/smartcardweb/pages/transfer/transfersuccess.jsp';		
				}else if(doworkret == -1){
					//д��ʧ��
					window.location='/smartcardweb/pages/transfer/recardwrite.jsp';//�����д�����ɹ�����Ҫ�߳�������					
				}else if(doworkret == 1){
					//ת��ʧ��
					window.location='/smartcardweb/pages/transfer/transferfailue.jsp';					
				}else{
				    //ת��ʧ��
					window.location='/smartcardweb/pages/transfer/transferfailue.jsp';	
				}
				
			}else if(ret == 1){
				alert("����ÿ�Ƭ...");
			}else{
				alert("����ȷ���ÿ�Ƭ...");
			}
			}else{
				alert("���粻ͨ�����Ժ�����...");
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
	<%
	  
	 
	%>
	<body scroll="no">
		<form action="/smartcardweb/transfer.do" method="post"
			name="writeCardForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/zz.gif" width="314"
									height="82" />
									<input type="hidden" name="org.apache.struts.taglib.Html.TOKEN">
							</div>

							<div id="content_input">
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									  <tr>
                                        <td height="40" class="��ʽ13">
                                           ���ײο���
                                        </td>
                                        <td>
                                            <%=refno%>
                                        </td>
                                    </tr>
									   <tr>
                                        <td height="40" class="��ʽ13">
                                           ���п���
                                        </td>
                                        <td>
                                            <%=bankcardno%>
                                        </td>
                                    </tr>
									
									<tr>
										<td height="40" class="��ʽ13">
											����
										</td>
										<td>
											<%=customer.getCustname()%>
										</td>
									</tr>
									
									<tr>
										<td height="40" class="��ʽ13">
											ѧ��
										</td>
										<td>
											<%=customer.getStuempno()%>
										</td>
									</tr>
									<tr>
                                        <td height="40" class="��ʽ13">
                                           һ��ͨ���
                                        </td>
                                        <td>
                                            <%=Double.parseDouble(cardBala)/100%>Ԫ
                                        </td>
                                    </tr>
									<tr>
										<td height="40" class="��ʽ13">
											ת�˽��
										</td>
										<td>
											<%=money%>
											Ԫ
										</td>
									</tr>
									
									<tr>
										<td height="80" align="center" class="show" id="errmsg"
											colspan="2">
											<html:errors />��ȷ�Ϸźÿ�!ת�˹��̿��������Ҫ�ȴ�30�룬�벻Ҫ�������߿�Ƭ��
											&nbsp;
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:dobanktrans();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
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

