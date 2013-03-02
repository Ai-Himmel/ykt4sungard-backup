<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ page import="com.kingstargroup.fdykt.dto.TTifSubsidyDTO"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>补助领取确认</title>
		<link href="pages/css/css.css" rel="stylesheet" type="text/css" />
		<%
		String card_id = (String) request.getAttribute("card_id");
		String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
		String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
		String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
		String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
		%>
		<script language="javascript">
		function dogetsubquery(){
			var cardId ='<%=card_id%>';
			var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
			var device_port = '<%=read_card_device_port%>';
			document.all.RFScanner.PortNo=device_port;
			var rrt = document.all.RFScanner.GetMainKey(serverbase+"getSysPara.do");
			if(rrt == 0){
			var ret = document.all.RFScanner.ReadCardPocket(1,cardId,"");
			//alert(ret);
			if(ret == 0){
				var doworkret = document.all.RFScanner.MySendRequest(serverbase+"getSidy.do","cardId="+cardId);
				if(doworkret == 0){
					//领取成功
					
					document.all.cardId.value=cardId;
					document.forms[0].submit();
				}else if(doworkret == -1){
					//写卡失败
					window.location='/smartcardweb/pages/sidy/recardwrite.jsp';
				}else if(doworkret == 1){
					//领取失败
					window.location='/smartcardweb/pages/sidy/getsidyfailue.jsp';					
				}else{
					window.location='/smartcardweb/pages/sidy/getsidyfailue.jsp';	
				}
				
			}else if(ret == 1){
				alert("请放置卡片...");
			}else{
				alert("请正确放置卡片...");
			}
			}else{
				alert("网络不通，请稍后重试...");
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
	//-->
	</script>
		<style type="text/css">
	.样式5 {
		color: #000000;
		font-size: 14px;
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
	</style>
	</head>
	<%String outCardAmount = (String)request.getAttribute("outCardAmount")==null?"":(String)request.getAttribute("outCardAmount");%>
	<body scroll="no">
		<form action="/smartcardweb/sidyList.do" method="post"
			name="writeCardForm">
            <input type="hidden" name="outCardAmount" value=<%=outCardAmount%> />  <!--出卡值 -->
            <input type="hidden" name="cardId" />
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
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									
									<tr>
										<td width="320" height="30" class="样式13">
											学号
										</td>
										<td>
											<%=request.getAttribute("stuemp_no") == null ? ""
					: request.getAttribute("stuemp_no")%>
											&nbsp;
										</td>
									</tr>
									<tr>
										<td height="30" class="样式13">
											客&nbsp;户&nbsp;名
											
										</td>
										<td >
											<%=request.getAttribute("cut_name") == null ? ""
					: request.getAttribute("cut_name")%>
											&nbsp;
										</td>
									</tr>
									<tr>
										<td height="30" class="样式13">
											补助批次号
										</td>
										<td>
											
											&nbsp;
										</td>
									</tr>
									
									<tr>
										<td height="30" class="样式13">
											补助总金额
										</td>
										<td>
											<%=request.getAttribute("allSidyAmount")==null?"" :request.getAttribute("allSidyAmount")%>
											
											&nbsp;元
										</td>
									</tr>
									<tr>
										<td height="30" class="样式13">
											可领取金额
										</td>
										<td>
											<%=request.getAttribute("getSidyAmount")==null?"":request.getAttribute("getSidyAmount")%>
											&nbsp;元
										</td>
									</tr>
									
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:dogetsubquery();"
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


