<%@ page contentType="text/html;charset=GBK"
	errorPage="/smartcardweb/index.do"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>查询结果</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
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
	%>
	<body scroll="no"
		onload="MM_preloadImages('/smartcardweb/pages/images/previcea.gif','/smartcardweb/pages/images/nexta.gif','/smartcardweb/pages/images/backa.gif')">
		<form name="pagequery" action="/smartcardweb/pagequery.do"
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
							<img src="/smartcardweb/pages/images/result.gif" width="314"
								height="82" />
						</div>
						<div id="content_input">
							<table width="100%" border="0" align="center" cellpadding="0"
								cellspacing="0" class="box">
								<tr>
									<td colspan="7" class="样式14" height="20">
										您
										<%=begin%>
										~
										<%=end%>
										的交易明细如下：
									</td>
								</tr>
								<tr align="center">
									<td align="center" class="样式13" height="20" width="8%">
										序号
									</td>
									<td align="center" class="样式13" width="13%">
										交易名称
									</td>
									<td align="center" class="样式13">
										交易地点
									</td>									
									<td align="center" class="样式13" width="22%">
										日期时间
									</td>
									<td align="center" class="样式13" width="11%">
										交易金额
									</td>
									<td align="center" class="样式13" width="11%">
										账户余额
									</td>
									<td align="center" class="样式13" width="12%">
										交易摘要
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
												+ operate_Date.substring(6, 8) + " ";
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
											<bean:write name="tradeserial" property="serial_type" />
										</td>
										<td height="20" class="样式12">
											<bean:write name="tradeserial" property="area_name" />
										</td>										
										<td height="20" class="样式12">
											<%=operate_Date + operate_time%>
										</td>
										<td height="20" class="样式12">
											<bean:write name="tradeserial" property="trade_Fee"
												format="0.00" />
										</td>
										<td height="20" class="样式12">
											<bean:write name="tradeserial" property="freeBala"
												format="0.00" />
										</td>
										<td height="20" class="样式12">
											<bean:write name="tradeserial" property="dict_caption" />
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
										<%
											Integer val = (Integer) session.getAttribute("all");
											if (null == val) {
												pageContext.forward("/smartcardweb/index.do");
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
								</tr>
							</table>
						</div>
						<div id="content_buttom">
							<%
								int cur = ((Integer) session.getAttribute("page")).intValue();
								int currows = ((java.util.ArrayList) session
										.getAttribute("tradeserials")).size();
								if (cur > 1) {
							%>
							<a onclick="javascript:gotoNextPage(<%=p - 1%>)"
								onmouseout="MM_swapImgRestore()"
								onmousedown="MM_swapImage('previce','','/smartcardweb/pages/images/previcea.gif',1)"><img
									src="/smartcardweb/pages/images/previce.gif" name="previce"
									width="109" height="48" border="0" id="previce" /> </a>
							<%
								}
								;
								if (cur < max) {
							%>
							<a onclick="javascript:gotoNextPage(<%=p + 1%>)"
								onmouseout="MM_swapImgRestore()"
								onmousedown="MM_swapImage('next','','/smartcardweb/pages/images/nexta.gif',1)"><img
									src="/smartcardweb/pages/images/next.gif" name="next"
									width="109" height="48" border="0" id="next" /> </a>
							<%
							}
							%>
							<a onclick="javascript: window.location='/smartcardweb/main.do'"
								onmouseout="MM_swapImgRestore()"
								onmousedown="MM_swapImage('back','','/smartcardweb/pages/images/backa.gif',1)"><img
									src="/smartcardweb/pages/images/back.gif" name="back"
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

