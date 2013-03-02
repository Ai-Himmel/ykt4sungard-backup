<%@ page contentType="text/html;charset=GBK"	errorPage="/smartbank/index.do"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>  
		<title>查询结果</title>
		<link href="pages/css/css.css" rel="stylesheet" type="text/css" />
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
			function gotoNextPage(page){
				document.pagequery.page.value = page;
				document.pagequery.submit();
			}
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
	
	<body scroll="no"   onkeydown="return (event.keyCode!=8)"
		onload="MM_preloadImages('<%=path%>/pages/images/previcea.gif','<%=path%>/pages/images/nexta.gif','<%=path%>/pages/images/backa.gif')">
		<form name="pagequery" action="<%=path%>/pagequery.do"
			method="post">
			<input name="page" type="hidden" value="1" />
		</form>
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layer1">
				<div id="content">
					<div id="content_left"></div>
					<div id="content_middle">
						<div align="center">
							<img src="<%=path%>/pages/images/result.gif" width="314"
								height="82" />
						</div>
						<div id="content_input">
							<table width="100%" border="0" align="center" cellpadding="0"
								cellspacing="0" class="box">
								<tr>
									<td colspan="7" class="样式14" height="20">
										您前10笔银行转账明细如下：
									</td>
								</tr>
								<tr align="center">
									<td align="center" class="样式13" height="20" width="8%">
										序号
									</td>
									<td align="center" class="样式13" width="13%">
										银行卡号
									</td>
									<td align="center" class="样式13" width="22%">
										日期
									</td>
									
									<td align="center" class="样式13" width="22%">
										时间
									</td>
									<td align="center" class="样式13" width="22%">
										转账金额
									</td>
									
								</tr>
								<%
									int serial_no = 1;
									int count = 0;
								%>
								<logic:iterate id="tradeserial" name="tradeserials" offset="0">
									<%
											com.kingstargroup.fdykt.dto.TradeSerialDTO ts = (com.kingstargroup.fdykt.dto.TradeSerialDTO) tradeserial;
											String operate_Date = ts.getOperate_Date();
											String operate_time = ts.getOperate_time();
											if (operate_Date != null && operate_Date.length() == 8)
												operate_Date = operate_Date.substring(0, 4) + "-"
												+ operate_Date.substring(4, 6) + "-"
												+ operate_Date.substring(6, 8) + "　";
											if (operate_time != null && operate_time.length() == 6)
												operate_time = operate_time.substring(0, 2) + ":"
												+ operate_time.substring(2, 4) + ":"
												+ operate_time.substring(4, 6);

											count++;
									%>
									<tr align="center">
										<td height="20" class="样式12">
											<%=serial_no++%>
										</td>
										
										<td height="20" class="样式12">
										
											<%=ts.getB_Act_id()%>
												
										</td>
										
										<td height="20" class="样式12">
											<%=operate_Date%>
										</td>
										<td height="20" class="样式12">
											<%=operate_time%>
										</td>
										
										<td height="20" class="样式12">
											<bean:write name="tradeserial" property="trade_Fee"
												format="0.00" />
										</td>
										
									</tr>
								</logic:iterate>
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
									
								</tr>
								<%
								}
								%>
								<tr>
									<td align="left" colspan="7" class="样式14" height="20">
										
									</td>
								</tr>
							</table>
						</div>
						<div id="content_buttom">
							
							<a onclick="javascript: window.location='<%=path%>/pages/yhkw.jsp'"
								onmouseout="MM_swapImgRestore()"
								onmousedown="MM_swapImage('back','','<%=path%>/pages/images/backa.gif',1)"><img
									src="<%=path%>/pages/images/back.gif" name="back"
									width="109" height="48" border="0" id="back" /> </a>
						</div>
					</div>
					<div id="content_right"></div>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
	</body>
</html>

