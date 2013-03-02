<%@ page contentType="text/html;charset=GBK"%>
<%@page import="com.kingstargroup.fdykt.dto.NewCardInfoDTO"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration"%>
<html>
	<head>
		<title>新生换卡</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<%
			NewCardInfoDTO newcardinfodto = (NewCardInfoDTO) request
					.getAttribute("newcardinfodto");
		    String newcardphyid = (String)request.getAttribute("newcardphyid");
		    String pursetype1 = (String)request.getAttribute("pursetype1");
		    String pursetype2 = (String)request.getAttribute("pursetype2");
		    String pursetype3 = (String)request.getAttribute("pursetype3");
		    String pursetypename1 = (String)request.getAttribute("pursetypename1");
		    String pursetypename2 = (String)request.getAttribute("pursetypename2");
		    String pursetypename3 = (String)request.getAttribute("pursetypename3");
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
		function readOldCard(){	
            if(!document.all.send.disabled){            	
            	 var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
     			var device_port = '<%=read_card_device_port%>';
     			document.all.RFScanner.PortNo=device_port;	
     			var pursetype1 = '<%=pursetype1%>';
     			var pursetype2 = '<%=pursetype2%>';
     			var pursetype3 = '<%=pursetype3%>';		
     			var pursetypename1 = '<%=pursetypename1%>';
     			var pursetypename2 = '<%=pursetypename2%>';
     			var pursetypename3 = '<%=pursetypename3%>';				
     			var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
     			if(rrt == 0){
     			  var sret=oldCardForm.all.RFScanner.DoScan();
     	           if(sret==0){//读卡成功 
     	               var cardphyid = document.all.RFScanner.CardPhyID;
     	               oldCardForm.all.cardphyid.value=cardphyid;
     	                var ret = document.all.RFScanner.ReadCardPocket(1,cardphyid);
     		            if(ret == 0){
     		            	var cardbal = oldCardForm.all.RFScanner.GetPacketInfo("cardbal");
     						var pay_card_cnt =  oldCardForm.all.RFScanner.GetPacketInfo("pay_card_cnt");
     						var dpt_card_cnt =  oldCardForm.all.RFScanner.GetPacketInfo("dpt_card_cnt");
                              oldCardForm.all.cardBala.value = cardbal;
                              oldCardForm.all.pay_card_cnt.value = pay_card_cnt;
                              oldCardForm.all.dpt_card_cnt.value = dpt_card_cnt;
                              oldCardForm.all.RFScanner.CleanReturnMap();
                              oldCardForm.all.RFScanner.SetReturnMap("pursetype1",pursetype1);
                              oldCardForm.all.RFScanner.SetReturnMap("pursetype2",pursetype2);  
                              oldCardForm.all.RFScanner.SetReturnMap("pursetype3",pursetype3);   

                              if(pursetype1!="0"){
                             	 var wret1 = oldCardForm.all.RFScanner.ReadWaterCtlPacket(pursetype1,cardphyid); 
                             	 if(wret1==0){
                             		 var water_money1 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("money");   
                             		 var water_price11 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("price1");
                             		 var water_price21 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("price2");
                             		 var water_price31 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("price3");  
                             		 oldCardForm.all.RFScanner.SetReturnMap("water_money1",water_money1);
                             		 oldCardForm.all.RFScanner.SetReturnMap("water_price11",water_price11);
                             		 oldCardForm.all.RFScanner.SetReturnMap("water_price21",water_price21);
                             		 oldCardForm.all.RFScanner.SetReturnMap("water_price31",water_price31);    
                             		 oldCardForm.all.water_money1.value = water_money1;  
                             		oldCardForm.all.pursetype1.value = pursetype1;                           		   
                             	 }else{
     								alert(pursetypename1+"钱包读取失败");
     								return false;
                             	 }                        	 
                              }
                              if(pursetype2!="0"){
                             	 var wret2 = oldCardForm.all.RFScanner.ReadWaterCtlPacket(pursetype2,cardphyid); 
                             	 if(wret2==0){
                             		 var water_money2 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("money");   
                             		 var water_price12 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("price1");
                             		 var water_price22 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("price2");
                             		 var water_price32 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("price3"); 
                             		oldCardForm.all.RFScanner.SetReturnMap("water_money2",water_money1);
                            		 oldCardForm.all.RFScanner.SetReturnMap("water_price12",water_price12);
                            		 oldCardForm.all.RFScanner.SetReturnMap("water_price22",water_price22);
                            		 oldCardForm.all.RFScanner.SetReturnMap("water_price32",water_price32);      
                            		 oldCardForm.all.water_money2.value = water_money2;  
                            		 oldCardForm.all.pursetype2.value = pursetype2;                         		 
                             	 }else{
     								alert(pursetypename2+"钱包读取失败");
     								return false;
                             	 }                        	 
                              }
                              if(pursetype3!="0"){
                             	 var wret3 = oldCardForm.all.RFScanner.ReadWaterCtlPacket(pursetype3,cardphyid); 
                             	 if(wret3==0){
                             		 var water_money3 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("money");   
                             		 var water_price13 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("price1");
                             		 var water_price23 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("price2");
                             		 var water_price33 =oldCardForm.all.RFScanner.GetWaterCtlPacketInfo("price3");  
                             		oldCardForm.all.RFScanner.SetReturnMap("water_money3",water_money3);
                            		 oldCardForm.all.RFScanner.SetReturnMap("water_price13",water_price13);
                            		 oldCardForm.all.RFScanner.SetReturnMap("water_price23",water_price23);
                            		 oldCardForm.all.RFScanner.SetReturnMap("water_price33",water_price33);  
                            		 oldCardForm.all.water_money3.value = water_money3;  
                            		 oldCardForm.all.pursetype3.value = pursetype3;                            		
                             	 }else{
     								alert(pursetypename3+"钱包读取失败");
     								return false;
                             	 }                        	 
                              }
                              oldCardForm.all.send.disabled = true;
                              oldCardForm.submit();
     		            }else if(ret == 1){
     		                alert("请放置临时卡...");
     		               return false;
     		            }else{
     		                alert("请正确放置临时卡...");
     		               return false;
     		            }
     	            }else{
     	                alert("读卡失败，请放置临时卡...");	
     	               return false;               
     	            }
     	           }else{
     	               alert("网络不通，请稍后重试...");
     	              return false;
     	           }
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
		.样式12 {
			font-family: "宋体";
			color: #000000;
			font-size: 16px;
		}
		
		.样式13 {
			font-family: "黑体";
			color: #000000;
			font-size: 18px;
		}
		
		.样式14 {
			font-family: "黑体";
			color: #ff0000;
			font-size: 18px;
		}
		}
	</style>
	</head>
	<body scroll="no">
		<form action="/smartcardweb/saveoldcardinfo.do" method="post"
			name="oldCardForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/czjg.gif" width="314"
									height="82" />
								<input type="hidden" name="org.apache.struts.taglib.Html.TOKEN">
							</div>

							<div id="content_input">
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td rowspan="3" align="center">
											<img
												src="/smartcardweb/getphoto?custid=<%=String.valueOf(newcardinfodto.getCustid())%>"
												height="140" width="110" align="middle">
										</td>
										<td height="60" class="样式13">
											学工号
											<input type="hidden" name="cardphyid">
											<input type="hidden" name="pay_card_cnt">
											<input type="hidden" name="dpt_card_cnt">
											<input type="hidden" name="cardBala">		
											<input type="hidden" name="water_money1">
											<input type="hidden" name="water_money2">
											<input type="hidden" name="water_money3">		
											<input type="hidden" name="pursetype1" value="0">
											<input type="hidden" name="pursetype2" value="0">
											<input type="hidden" name="pursetype3" value="0">							
											<input type="hidden" name="newcardphyid" value="<%=newcardphyid%>"> 
											<input type="hidden" name="showcardno" value="<%=newcardinfodto.getShowcardno()%>">
											<input type="hidden" name="oldcardphyid" value="<%=newcardinfodto.getOldcardphyid()%>">
										</td>
										<td>
											<%=newcardinfodto.getStuempno()%>
										</td>
									</tr>
									<tr>
										<td height="60" class="样式13">
											姓 名
										</td>
										<td>
											<%=newcardinfodto.getCustname()%>
										</td>
									</tr>

									<tr>
										<td height="60" class="样式13">
											显示卡号
										</td>
										<td>
											<%=newcardinfodto.getShowcardno()%>
										</td>
									</tr>
									<tr>
										<td height="140" align="center" class="show" id="errmsg"
											colspan="3">
											<html:errors />
											请仔细核对您正式卡信息的正确性
											<br>
											如果信息正确，请将 <b>临时卡</b> 放置于读卡区
											<br>
											点击 <b>确定</b> 开始换卡操作 &nbsp;
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								 <table align="center">
									<tr>
										<td align="center">
											<a onclick="javascript:readOldCard();"
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

