<%@ page contentType="text/html; charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ page import="com.kingstargroup.fdykt.ConfigMenu" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<html>
	<head>
		<title>һ��ͨ�ۺϲ�ѯϵͳ</title>
		
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
		 var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
		 document.all.RFScanner.PortNo=device_port;//�������˿�����
		 document.all.RFScanner.PsamCardPosition=psam_position;//������psam������λ��
		 var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
		if(rrt == 0){
			 var ret=document.all.RFScanner.DoOpenCom();
			 if(ret!=0){
				 alert("�������򿪴���ʧ�ܣ�����˿ں�Ӳ������");
			 }
		}else{
			alert("���粻ͨ�����Ժ�����...");
			return false;
		}
		
	}
	 function readYJZCardPocket(){
         var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
         var device_port = '<%=read_card_device_port%>';
         document.all.RFScanner.PortNo=device_port;
         
          var ret=document.all.RFScanner.DoScan();
            if(ret==0){//�����ɹ�         
               var cardphyid = document.all.RFScanner.CardPhyID;
                var cret = document.all.RFScanner.ReadCardPocket(1,cardphyid);
               
             if(cret == 0){
                 var bala = document.all.RFScanner.GetPacketInfo("cardbal");
                 var pret = document.all.RFScanner.ReadWaterCtlPacket(2,cardphyid); 
                 
                 if(0==pret){
                      var sslrsb_waterBala = document.all.RFScanner.GetWaterCtlPacketInfo("money");                           
                       var ppret = document.all.RFScanner.ReadWaterCtlPacket(3,cardphyid); 
                       if(0==ppret){
                          var ksfxyf_waterBala = document.all.RFScanner.GetWaterCtlPacketInfo("money");
                          moneyForm.all.bala.value=bala;
                          moneyForm.all.sslrsb_waterBala.value=sslrsb_waterBala;
                          moneyForm.all.ksfxyf_waterBala.value=ksfxyf_waterBala;
                          moneyForm.submit();
                      }else{
                          alert("ˮ��Ǯ������ʧ��");
                          return false;
                      }                
                  }else{
                      alert("ˮ��Ǯ������ʧ��");
                      return false;
                  }
                         
             }else if(ret == 1){
                 alert("����ÿ�Ƭ...");
                 return false;
             }else{
                 alert("����ȷ���ÿ�Ƭ...");
                 return false;
             }
            }else{
                alert("����ʧ�ܣ�����ÿ�Ƭ...");
            }                   
        }
	function readCardPocket(){    
		var small_packet=<%=small_packet%>;
		var small_packet_number='<%=small_packet_number%>';        
         var ret=document.all.RFScanner.DoScan();
           if(ret==0){//�����ɹ�         
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
                  alert("����ÿ�Ƭ...");
                  return false;
              }else{
                  alert("����ȷ���ÿ�Ƭ...");
                  return false;
              }
            }else{
                alert("����ʧ�ܣ�����ÿ�Ƭ...");
            }                                                  
       }

	 function readCardSidy(){
		var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
		var ret=document.all.RFScanner.DoScan();		
		if(ret==0){
		//�����ɹ�
			var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			if(rrt == 0){
		  	var cardphyid = document.all.RFScanner.CardPhyID;	
		      logonForm.all.cardphyid.value=cardphyid;
		      logonForm.submit();   
			}else{
				alert("���粻ͨ�����Ժ�����...");
				return false;
			}                  
		}else{
		    alert("����ʧ�ܣ�����ÿ�Ƭ...");
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
							onclick="javascript: readCardPocket();"></li>
						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h2.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h2.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h2a.gif)'"
							style="cursor: pointer; background: url(/smartcardweb/pages/images/h2.gif); <% if (!ConfigMenu.getMenuStatus("main_news")) { out.print(" display:none; "); }%>"
							onclick="javascript: window.location='/smartcardweb/viewnews.do';"></li>

						<li
							onmouseout="this.style.background='url(/smartcardweb/pages/images/h6.gif)'"
							onmouseup="this.style.background='url(/smartcardweb/pages/images/h6.gif)'"
							onmousedown="this.style.background='url(/smartcardweb/pages/images/h6a.gif)'"
							style="cursor: pointer; background: url(/smartcardweb/pages/images/h6.gif); <% if (!ConfigMenu.getMenuStatus("main_help")) { out.print(" display:none; "); }%>"
							onclick="javascript: window.location='/smartcardweb/pages/help.jsp';"></li>
							<!--
						<li
                            onmouseup="this.style.background='url(/smartcardweb/pages/images/fhcd.gif)'"
                            onmousedown="this.style.background='url(/smartcardweb/pages/images/fhcda.gif)'"
                            style="cursor: pointer; background: url(/smartcardweb/pages/images/fhcd.gif); <% if (!ConfigMenu.getMenuStatus("main_return")) { out.print(" display:none; "); }%>"
                            onclick="javascript: window.location='http://localhost';"></li>
                            -->
 							<!-- ��������ר�÷��� -->
					</ul>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
		<form action="/smartcardweb/getsidyquerynew.do" method="post" name="logonForm" >
		<input type="hidden" name="cardphyid" />
		<input type="hidden" name="sidyno" />		
        <input type="hidden" name="bala" />       
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

