<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ page import="com.kingstargroup.fdykt.dto.TTifSubsidyDTO"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>������ȡȷ��</title>
		<link href="pages/css/css.css" rel="stylesheet" type="text/css" />
		<%
		String cardno = (String) session.getAttribute("cardno");
		String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
		String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
		String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		%>
		<script language="javascript">
		function dogetsubquery(finishcount){
			var cardId ='<%=cardno%>';
			//alert(cardId);
			var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
			var device_port = '<%=read_card_device_port%>';
			document.all.RFScanner.PortNo=device_port;
			var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			//alert(rrt);
			
			if(rrt == 0){
			var ret = document.all.RFScanner.ReadCardPocket(1,cardId,"");
			
			if(ret == 0){
				var doworkret = document.all.RFScanner.MySendRequest(serverbase+"getSidy.do","cardId="+cardId);
				
				if(doworkret == 0){
					//��ȡ�ɹ�
					document.forms[0].cardId.value=cardId;
					document.forms[0].subsidyCount.value=finishcount;
					document.forms[0].submit();
				}else if(doworkret == -1){
					//д��ʧ��
					window.location='/smartcardweb/pages/sidy/recardwrite.jsp';
				}else if(doworkret == 1){
					//��ȡʧ��
					window.location='/smartcardweb/pages/sidy/getsidyfailue.jsp';					
				}else{
					window.location='/smartcardweb/pages/sidy/getsidyfailue.jsp';	
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
		.��ʽ12 {
		font-family: "����"; 
		color: #000000; 
		font-size: 14px; 		
		}
		.��ʽ13 {
		font-family: "����"; 
		color: #000000; 
		font-size: 16px; 
		}
		.��ʽ14 {
		font-family: "����"; 
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
			begin = begin.substring(0, 4) + "��" + begin.substring(4, 6)
			+ "��" + begin.substring(6, 8) + "��";
		if (end != null && end.length() == 8)
			end = end.substring(0, 4) + "��" + end.substring(4, 6) + "��"
			+ end.substring(6, 8) + "��";
	   String cardid = session.getAttribute("cardid").toString();;
	%>
	<!-- action="/smartcardweb/sidyList.do"  name="writeCardForm"  -->
	<body scroll="no" >
	    <form  name="writeCardForm" action="/smartcardweb/sidyList.do">
	    	<input type="hidden" name="cardId" />
	    	<input type="hidden" name="subsidyCount" />
	    </form>
		<form  name="pagequery"  action="/smartcardweb/sidypagequery.do"  method="post">
		   <input type="hidden" name="cardId" value="<%=cardid%>"/>
           <input name="page" type="hidden" value="1" />
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="/smartcardweb/pages/images/bz.gif" width="314"
								height="82" />
							</div>
							<div id="content_input">
							<table width="100%" border="0" align="center" cellpadding="0"
								cellspacing="0" class="box">
								<tr>
									<td colspan="8" class="��ʽ14">
										���Ĳ�����ϸ���£�
									</td>
								</tr>
								<tr align="center">

									<td align="center" class="��ʽ13" width="20%">
										�������κ�
									</td>
									<td align="center" class="��ʽ13" width="20%">
										�ͻ���
									</td>
									<td align="center" class="��ʽ13" width="15%">
										��������
									</td>
									<td align="center" class="��ʽ13" width="15%">
										��������
									</td>
									<!-- <td align="center" class="��ʽ13" width="120">
										��ȡʱ��
									</td>
									<td align="center" class="��ʽ13" width="80">
										��������
									</td>-->
									<td align="center" class="��ʽ13" width="15%">
										������Ԫ��
									</td>
									<td align="center" class="��ʽ13" width="15%">
										״̬
									</td>

								</tr>
								<%
									int serial_no = 1;
									int count = 0;
								%>
								<logic:iterate id="ttifsidy" name="ttifsidys" offset="0">
									<%
											TTifSubsidyDTO ts = (TTifSubsidyDTO) ttifsidy;
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
											<div align="center" class="��ʽ12">
												<bean:write name="ttifsidy" property="subsidyNo" />
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="��ʽ12">
												<bean:write name="ttifsidy" property="custNo" />
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="��ʽ12">
												<bean:write name="ttifsidy" property="subsidytype" />
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="��ʽ12">
												<%=tx_date%>
											</div>
										</td>
										<!-- <td height="20">
											<div align="center" class="��ʽ12">
												<%=get_date%>
												
											</div>
										</td>
										<td height="20">
											<div align="center" class="��ʽ12"> 
												<%=expire_date%>
											</div>
										</td>-->  
										<td height="20">
											<div align="center" class="��ʽ12">
												<bean:write name="ttifsidy" property="amount" format="0.00" />
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="��ʽ12">
												<bean:write name="ttifsidy" property="status" />
												&nbsp;
											</div>
										</td>
									</tr>
								</logic:iterate>
								<%
								for (int i = count; i < 10; i++) {
								%>
								<tr>
									<td height="20" class="��ʽ12">
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
									<td align="left" colspan="8" class="��ʽ14">
										<%
											Integer val = (Integer) session.getAttribute("all");
											if (null == val) {
												pageContext.forward("/smartcardweb/logsys.do");
												return;
											}
											int max = val.intValue();
											if (max - (max / 10) * 10 > 0)
												max = max / 10 + 1;
											else
												max = max / 10;
										%>
										�ܹ�
										<%=max%>
										ҳ &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ��ǰ��
										<%=session.getAttribute("page")%>
										ҳ
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
											onmousedown="MM_swapImage('previce','','/smartcardweb/pages/images/previcea.gif',1)"><img
												src="/smartcardweb/pages/images/previce.gif" name="previce"
												width="109" height="48" border="0" id="previce" /> </a>
													
									<%
										}
										if (cur < max) {
									%>
										<a onclick="javascript:gotoNextPage(<%=p + 1%>)"
											onmouseout="MM_swapImgRestore()"
											onmousedown="MM_swapImage('next','','/smartcardweb/pages/images/nexta.gif',1)"><img
												src="/smartcardweb/pages/images/next.gif" name="next"
												width="109" height="48" border="0" id="next" /> </a>
													
									<%
									}
									   if( cur == max ){  
									%>   
									      
											<a onclick="javascript:dogetsubquery('<%=count%>');"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','/smartcardweb/pages/images/senda.gif',1)"><img
													src="/smartcardweb/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
									<%} %>
										
											<a
												onclick="javascript: window.location='/smartcardweb/index.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('cancel','','/smartcardweb/pages/images/cancela.gif',1)"><img
													src="/smartcardweb/pages/images/cancel.gif" name="cancel"  
													width="109" height="48" border="0" id="cancel" /> </a>
									
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


