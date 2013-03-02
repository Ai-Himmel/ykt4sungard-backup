<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ page import="com.kingstargroup.fdykt.dto.TTifSubsidyDTO"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@page  import="java.util.*"%> 

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="/smartbank/pages/js/other.js"></script><html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>补助领取确认</title>
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet"	type="text/css" />
		<%
		String cardno = (String) session.getAttribute("cardno");
		List   sidys = (List)session.getAttribute("ttifsidys");
		int sidyscount=0;
		if(sidys !=null){
			sidyscount = sidys.size();
		}
		%>
		<script language="javascript">
		
		var deviceId="";
		function readdevice(){
		  deviceId =readfile();
		}
           
		var totalmoney=0;
		function  getsidy(){
	     	document.getElementById("send").style.display='none';
	     	var flag = 0;
			<%
			double amount=0;
			int j=0;
			
			for( j=0;j<sidys.size();j++){//根据补助数循环领取
				TTifSubsidyDTO  subsidy  =  (TTifSubsidyDTO)sidys.get(j);
				String   sidy_no =  subsidy.getSubsidyNo();
				amount  =  subsidy.getAmount();
			%>	
			if(flag==0)
			{
			  if(dogetsubquery(<%=sidy_no%>,<%=amount%>,<%=j+1%>)!=1)
			  	flag = 1;
			}
		  <%}%> 
		    if(flag == 1){
		    	return;
		    }
		    readCard();
		    	
		 }
		 
	
		function dogetsubquery(sidyno,amount,count){
			var cardId ='<%=cardno%>';
			var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
			var device_port = '<%=read_card_device_port%>';
			document.all.RFScanner.PortNo=device_port;
			var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			if(rrt == 0){
			var ret = document.all.RFScanner.ReadCardPocket(1,cardId,"");
			
			if(ret == 0){
				var doworkret = document.all.RFScanner.MySendRequest(serverbase+"getSidy.do?sidyno="+sidyno+"&deviceId="+deviceId,"cardId="+cardId);
				//alert("测试中"+doworkret);
				if(doworkret == 0){
					totalmoney=totalmoney+amount;
					//领取成功,为该条补助显示领取标致
				    var hidimg =	document.getElementById(sidyno);
				    hidimg.innerHTML= "<img  src='/smartbank/pages/images/gou.jpg' 	width='30' height='20' border='0'  />"; 
				    msg.innerHTML="<b>共领取了"+count+"条,"+"共计:"+totalmoney+"元补助</b>";
				    return 1;
				}else if(doworkret == -1){
					//写卡失败，重新写
					window.location='/smartbank/pages/sidy/recardwrite.jsp?sidyno='+sidyno+'&amount='+amount;	
					return 0;
				}else{
					window.location='/smartbank/pages/sidy/getsidyfailue.jsp?sidyno='+sidyno+'&amount='+amount;	
					return 0;
				}
			}else if(ret == 1){
			    msg.innerHTML="请放置卡片...";
			}else{
			    msg.innerHTML="请放置卡片...";
			}
			}else{
			    msg.innerHTML="网络不通，请稍后重试...";
			}
		}
		
		function  readCard()
	  {  
	
		var serverbase = "http://"+'<%=webserverip%>'+":"+'<%=webserverport%>'+"/"+'<%=webserverapp%>'+"/";
	    var cardId ="" ;
		document.all.RFScanner.PortNo=<%=read_card_device_port%>;
		var ret1=document.all.RFScanner.DoScan();
		if(ret1==0){//读卡成功
		cardId=document.all.RFScanner.CardNo;
		}
	    var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			if(rrt == 0){
				var ret = document.all.RFScanner.ReadCardPocket(1,cardId,"");
				if(ret == 0){
					var bala = document.all.RFScanner.GetPacketInfo("bala");
					cardmoney.innerHTML=" 卡余额 "+ bala/100 + " 元 ";
				}else if(ret == 1){
					
				}else{
					
				}
			}else{
				
			}
	}
      </script>
		<script type="text/JavaScript">
	<!--
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
	function gotoNextPage(page){
		document.pagequery.page.value = page;			
		document.pagequery.submit();
	}
	//-->
	</script>
		<style type="text/css">
		.样式12 {
		font-family: "宋体"; 
		color: #000000; 
		font-size: 14px; 		
		}
		.样式13 {
		font-family: "黑体"; 
		color: #000000; 
		font-size: 16px; 
		}
		.样式14 {
		font-family: "宋体"; 
		color: #000000; 
		font-size: 16px; 
		font-weight: bold;
		}
		</style>
	</head>
	<%
		int p = ((Integer) session.getAttribute("page")).intValue();
		String begin = (String) session.getAttribute("begin");
		String end = (String) session.getAttribute("end");
		if (begin != null && begin.length() == 8)
			begin = begin.substring(0, 4) + "年" + begin.substring(4, 6)
			+ "月" + begin.substring(6, 8) + "日";
		if (end != null && end.length() == 8)
			end = end.substring(0, 4) + "年" + end.substring(4, 6) + "月"
			+ end.substring(6, 8) + "日";
	   String cardid = session.getAttribute("cardId").toString();;
	%>
	
	<body scroll="no" onload="readdevice()" onkeydown="return (event.keyCode!=8)">
	    <form  name="writeCardForm" action="/smartbank/sidypagequery.do">
	    	<input type="hidden" name="cardId" />
	    	<input type="hidden" name="subsidyCount" />
	    	<input type="hidden" name="ret"/>
	    </form>
		<form  name="pagequery"  action="/smartbank/sidypagequery.do"  method="post">
		   <input type="hidden" name="cardId" value="<%=cardid%>"/>
           <input name="page" type="hidden" value="1" />
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartbank/pages/images/bz.gif" width="314"
								height="82" />
							</div>
							<div id="content_input">
							<table width="100%" border="0" align="center" cellpadding="0"
								cellspacing="0" class="box">
								<tr>
									<td colspan="8" class="样式14">
										您的补助明细如下：
									</td>
								</tr>
								<tr align="center">

									<td align="center" class="样式13" width="20%">
										补助批次号
									</td>
									<td align="center" class="样式13" width="20%">
										客户号
									</td>
									<td align="center" class="样式13" width="15%">
										补助类型
									</td>
									<td align="center" class="样式13" width="15%">
										发生日期
									</td>
									<td align="center" class="样式13" width="15%">
										补助金额（元）
									</td>
									<td align="center" class="样式13" width="15%">
										领取
									</td>

								</tr>
								<%
									int serial_no = 1;
									int count = 0;
								%>
									<%     for(int i=0;i<sidys.size();i++){ 
											TTifSubsidyDTO ts = (TTifSubsidyDTO) sidys.get(i);
											String tx_date = ts.getTxDate();
											String tx_time = ts.getTxTime();
											String get_date = ts.getGetDate() == null ? "" : ts
											.getGetDate();
											String get_time = ts.getGetTime() == null ? "&nbsp;&nbsp;" : ts
											.getGetTime();
											String expire_date = ts.getExpireDate();
											if (tx_date != null && tx_date.length() == 8)
												tx_date = tx_date.substring(0, 4) + "-"
												+ tx_date.substring(4, 6) + "-"
												+ tx_date.substring(6, 8);
											if (tx_time != null && tx_time.length() == 6)
												tx_time = tx_time.substring(0, 2) + ":"
												+ tx_time.substring(2, 4) + ":"
												+ tx_time.substring(4, 6);
											if (get_date != null && get_date.length() == 8)
												get_date = get_date.substring(0, 4) + "-"
												+ get_date.substring(4, 6) + "-"
												+ get_date.substring(6, 8) + "&nbsp;&nbsp;";
											if (get_time != null && get_time.length() == 6)
												get_time = get_time.substring(0, 2) + ":"
												+ get_time.substring(2, 4) + ":"
												+ get_time.substring(4, 6);
											if (expire_date != null && expire_date.length() == 8)
												expire_date = expire_date.substring(0, 4) + "-"
												+ expire_date.substring(4, 6) + "-"
												+ expire_date.substring(6, 8);
											count++;
									%>
									<tr align="center">
										<td height="20">
											<div align="center" class="样式12">
												<%=ts.getSubsidyNo()%>
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
												
												<%=ts.getCustNo()%>
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
												
												<%=ts.getSubsidytype()%>
												&nbsp;
												
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
												<%=tx_date%>
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
												
												<%=ts.getAmount()%>
												&nbsp;
											</div>
										</td>
										
										<td height="20" > 
											 <div align="center" id="<%=ts.getSubsidyNo()%>" > 
											    
											 </div>
										</td>
									</tr>
								<%}%>
								<%
								for (int i = count; i < 10; i++) {
								%>
								<tr>
									<td height="20" class="样式12">
										&nbsp;
									</td>
									<td>
										&nbsp;
									</td>
									<td>
										&nbsp;
									</td>
									<td>
										&nbsp;
									</td>
									<td>
										&nbsp;
									</td>
								
									<td>
										&nbsp;
									</td>
								</tr>
								<%
								}
								%>
								<tr>
									<td align="left" colspan="2" class="样式14">
										<%
											Integer val = (Integer) session.getAttribute("all");
											if (null == val) {
												pageContext.forward("/smartbank/logsys.do");
												return;
											}
											int max = val.intValue();
											if (max - (max / 10) * 10 > 0)
												max = max / 10 + 1;
											else
												max = max / 10;
										%>
										总共
										<%=max%>
										页 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 当前第
										<%=session.getAttribute("page")%>
										页
										
									</td>
									<td  colspan="2" class="message" id="msg">
									    
									</td>
									<td colspan="2"  class="message" id="cardmoney">
									    
									</td>
								</tr>
							</table>
						</div>
						<div id="content_buttom">
							
							 
							<%
										int cur = ((Integer) session.getAttribute("page")).intValue();
									
										int currows = ((java.util.ArrayList) session
												.getAttribute("ttifsidys")).size();
												
										if (cur > 1) {
									%>
									  
										<a onclick="javascript:gotoNextPage(<%=p - 1%>)"
											onmouseout="MM_swapImgRestore()"
											onmousedown="MM_swapImage('previce','','/smartbank/pages/images/previcea.gif',1)"><img
												src="/smartbank/pages/images/previce.gif" name="previce"
												width="109" height="48" border="0" id="previce" /> </a>
													
									<%
										}
										if (cur < max) {
									%>
										<a onclick="javascript:gotoNextPage(<%=p + 1%>)"
											onmouseout="MM_swapImgRestore()"
											onmousedown="MM_swapImage('next','','<%=path%>pages/images/nexta.gif',1)"><img
												src="/smartbank/pages/images/next.gif" name="next"
												width="109" height="48" border="0" id="next" /> </a>
													
									<%
									}
									%>   
									     
									     		
									   
									 
											<a onclick="javascript:getsidy();"  
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartbank/pages/images/senda.gif',1)"><img
													src="/smartbank/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a> 
									
										  
									   	<a
										  onclick="javascript: window.location='/smartbank/index.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('back','','/smartbank/pages/images/backa.gif',1)"><img
													src="/smartbank/pages/images/back.gif" name="back"  
													width="109" height="48" border="0" id="back" /> </a>	
								      	
								       
							
							</div>
						</div>
						<div id="content_right"></div>
					</div>
				</div>
			</div>
			<div id="bottom"></div>
			<object id="RFScanner"
				classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
				height="0" codebase="/smartbank/rf35.cab#version=2,0,0,7" />
			
		</form>
		
	
	</body>
</html>


