<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ page import="com.kingstargroup.fdykt.ConfigMenu" %>
<html>
	<head>
		<title>一卡通综合查询系统</title>
		
		<meta http-equiv="Content-Type" content="text/html; charset=GBK" />
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet"
			type="text/css" />
	</head>
	<%
		String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
		String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
		String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		String psam_card_position = KSConfiguration.getInstance().getProperty("psam_card_position","0"); 
		boolean small_packet = ConfigMenu.getMenuStatus("small_packet");
		String small_packet_number=KSConfiguration.getInstance().getProperty("small_packet_number","1"); 
		%>
	<script language="javascript">
	function iniOpenCom(){
		 var device_port = '<%=read_card_device_port%>';
		 var psam_position = '<%=psam_card_position%>';
		 document.all.RFScanner.PortNo=device_port;//读卡器端口设置
		 document.all.RFScanner.PsamCardPosition=psam_position;//读卡器psam卡卡槽位置
		 var ret=document.all.RFScanner.DoOpenCom();
		 if(ret!=0){
			 alert("读卡器打开串口失败，请检查端口和硬件配置");
		 }
	}
	
	function readCardPocket(){    
		var small_packet=<%=small_packet%>;
		var small_packet_number='<%=small_packet_number%>';        
         var ret=document.all.RFScanner.DoScan();
           if(ret==0){//读卡成功         
              var cardphyid = document.all.RFScanner.CardPhyID;
              var cret = document.all.RFScanner.ReadCardPocket(1,cardphyid); 
			 if(cret == 0){
			     var bala = document.all.RFScanner.GetPacketInfo("cardbal");
			     if(small_packet==true){
			    	 var pret = document.all.RFScanner.ReadWaterCtlPacket(small_packet_number,cardphyid); 
	                  if(0==pret){
	                  	  var sslrsb_waterBala = document.all.RFScanner.GetWaterCtlPacketInfo("money");                           
	                       moneyForm.all.bala.value=bala;
	                       moneyForm.all.sslrsb_waterBala.value=sslrsb_waterBala;
	                       moneyForm.submit();            
	                   }else{
	                	   moneyForm.all.sslrsb_waterBala.value=-1;
	                       moneyForm.all.bala.value=bala;
	                       moneyForm.submit();    
	                   }			    	     
			     }else{
			    	 moneyForm.all.sslrsb_waterBala.value=-1;
                     moneyForm.all.bala.value=bala;
                     moneyForm.submit();
			     }                                              
              }else if(ret == 1){
                  alert("请放置卡片...");
                  return false;
              }else{
                  alert("请正确放置卡片...");
                  return false;
              }
            }else{
                alert("读卡失败，请放置卡片...");
            }                                                  
       }

	function readdlmuCardPocket(){    
		var small_packet=<%=small_packet%>;
         var ret=document.all.RFScanner.DoScan();
           if(ret==0){//读卡成功         
              var cardphyid = document.all.RFScanner.CardPhyID;
              var cret = document.all.RFScanner.ReadCardPocket(1,cardphyid); 
			 if(cret == 0){
			     var bala = document.all.RFScanner.GetPacketInfo("cardbal");
			     if(small_packet==true){
			    	 var pret = document.all.RFScanner.ReadWaterCtlPacket(5,cardphyid); 
	                  if(0==pret){
	                  	  var sslrsb_waterBala = document.all.RFScanner.GetWaterCtlPacketInfo("money");                           
	                       moneyForm.all.sslrsb_waterBala.value=sslrsb_waterBala;	                             
	                   }else{
	                	   moneyForm.all.sslrsb_waterBala.value=-1;
	                   }	
	                  var cpret = document.all.RFScanner.ReadWaterCtlPacket(3,cardphyid); 
	                  if(0==cpret){
	                  	  var ksfxyf_waterBala = document.all.RFScanner.GetWaterCtlPacketInfo("money");                           
	                       moneyForm.all.ksfxyf_waterBala.value=ksfxyf_waterBala;        
	                   }else{
	                	   moneyForm.all.ksfxyf_waterBala.value=-1;   
	                   }	
                      moneyForm.all.bala.value=bala;
                      moneyForm.submit();    		    	     
			     }else{
			    	 moneyForm.all.sslrsb_waterBala.value=-1;
			    	 moneyForm.all.ksfxyf_waterBala.value=-1;   
                     moneyForm.all.bala.value=bala;
                     moneyForm.submit();
			     }                                              
              }else if(ret == 1){
                  alert("请放置卡片...");
                  return false;
              }else{
                  alert("请正确放置卡片...");
                  return false;
              }
            }else{
                alert("读卡失败，请放置卡片...");
            }                                                  
       }
    

	 function readCardSidy(){
		var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
		var ret=document.all.RFScanner.DoScan();		
		if(ret==0){
		//读卡成功
			var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			if(rrt == 0){
		  	  var cardphyid = document.all.RFScanner.CardPhyID;	
		      logonForm.all.cardphyid.value= cardphyid;
              ret = document.all.RFScanner.ReadCardPocket(1,cardphyid);
              if(ret == 0){
              	var cardbal = document.all.RFScanner.GetPacketInfo("cardbal");
   				var dptCardCnt =  document.all.RFScanner.GetPacketInfo("dpt_card_cnt");
   				var payCardCnt = document.all.RFScanner.GetPacketInfo("pay_card_cnt");
                logonForm.all.cardBala.value = cardbal;
                logonForm.all.dptCardCnt.value = dptCardCnt;
                logonForm.all.payCardCnt.value = payCardCnt;
                logonForm.submit();
              }else if(ret == 1){
                  alert("请放置卡片...");
                  return false;
              }else{
                  alert("请正确放置卡片...");
                  return false;
              }
			}else{
				alert("网络不通，请稍后重试...");
				return false;
			}                  
		}else{
		    alert("读卡失败，请放置卡片...");
		}
      }
	</script>
	<body scroll="no" onload="javascript:iniOpenCom();">

		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layer2">
				<div id="mid_center1">
					<ul>
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/yhkw.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/yhkw.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/yhkwa.gif)'"
							style="cursor: pointer; background: url(/smartcardweb/pages/images/yhkw.gif); <% if (!ConfigMenu.getMenuStatus("main_bankBiz")) { out.print(" display:none; "); }%>"
							onclick="javascript: window.location='/smartcardweb/pages/yhkw.jsp';"></li>
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/xykw.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/xykw.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/xykwa.gif)'"
							style="cursor: pointer; background: url(/smartcardweb/pages/images/xykw.gif); <% if (!ConfigMenu.getMenuStatus("main_compusBiz")) { out.print(" display:none; "); }%>"
							onclick="javascript: window.location='/smartcardweb/xykw.do';"></li>
						 <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/zysf.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/zysf2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/zysf.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_cfgfeebusiness")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/cfgfeebusiness.do';"></li>
                          <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/kkzz.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/kkzz2.gif)'"
                            style="cursor: hand; background: url(/smartcardweb/pages/images/kkzz.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_card_card")) { out.print(" display:none; "); }%>"
                            onclick="javascript:window.location='/smartcardweb/cardcardbusiness.do';"></li>                          
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/zzyw.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/zzyw.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/zzywa.gif)'"
							style="cursor: pointer; background: url(/smartcardweb/pages/images/zzyw.gif); <% if (!ConfigMenu.getMenuStatus("main_addtionalBiz")) { out.print(" display:none; "); }%>"
							onclick="javascript: window.location='/smartcardweb/pages/zzyw.jsp';"></li>								
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h5.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h5.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h5a.gif)'"
							style="cursor: pointer; background: url(/smartcardweb/pages/images/h5.gif); <% if (!ConfigMenu.getMenuStatus("main_lostCard")) { out.print(" display:none; "); }%>"
							onclick="javascript: window.location='/smartcardweb/lossquery.do';"></li>

					</ul>
				</div>
			</div>
			<div id="Layer3">
				<div id="mid_center2">
					<ul>

						<li
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h4.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h4a.gif)'"
							style="cursor: pointer; background: url(/smartcardweb/pages/images/h4.gif); <% if (!ConfigMenu.getMenuStatus("main_sidy")) { out.print(" display:none; "); }%>"
							onclick="javascript: readCardSidy();"></li>
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/kye.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/kye.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/kyea.gif)'"
							style="cursor: pointer; background: url(/smartcardweb/pages/images/kye.gif); <% if (!ConfigMenu.getMenuStatus("main_cardBalane")) { out.print(" display:none; "); }%>"
							onclick="javascript: readdlmuCardPocket();"></li>
						 <li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/sk.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/ska.gif)'"
                            style="cursor:hand; background:url(/smartcardweb/pages/images/sk.gif); <% if (!ConfigMenu.getMenuStatus("addtionalBiz_water")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='/smartcardweb/watershopchoose.do';"></li>
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h2.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h2.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h2a.gif)'"
							style="cursor: pointer; background: url(/smartcardweb/pages/images/h2.gif); <% if (!ConfigMenu.getMenuStatus("main_news")) { out.print(" display:none; "); }%>"
							onclick="javascript: window.location='/smartcardweb/pages/news.jsp';"></li>

						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h6.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h6.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h6a.gif)'"
							style="cursor: pointer; background: url(/smartcardweb/pages/images/h6.gif); <% if (!ConfigMenu.getMenuStatus("main_help")) { out.print(" display:none; "); }%>"
							onclick="javascript: window.location='/smartcardweb/pages/help.jsp';"></li>
							
						<li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/fhcd.gif); <% if (!ConfigMenu.getMenuStatus("main_return")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='http://localhost';"></li>
					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
		<form action="/smartcardweb/getsidyquerynew.do" method="post" name="logonForm" >
		<input type="hidden" name="cardphyid" />
		<input type="hidden" name="dptCardCnt" />	
		<input type="hidden" name="payCardCnt" />	
        <input type="hidden" name="cardBala" />
         <input type="hidden" name="tradetype" value="S"/>
	   </form>
		<form name="moneyForm" action="/smartcardweb/waterbalayjz.do" method="post">
            <input type="hidden" name="bala" value="0" />
            <input type="hidden" name="sslrsb_waterBala" value="0" />
            <input type="hidden" name="ksfxyf_waterBala" value="0" />
       </form>
       <object id="RFScanner"
                classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
                height="0"></object>
	</body>
</html>

