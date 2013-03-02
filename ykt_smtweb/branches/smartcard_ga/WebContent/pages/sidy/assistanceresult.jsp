<%@ page contentType="text/html;charset=GBK"
	errorPage="/smartcardweb/index.do"%>
<%@ page import="com.kingstargroup.fdykt.dto.AssistanceDTO"%>
<%@ page import="com.kingstargroup.fdykt.dto.TTifSubsidyDTO"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>补助明细查询结果</title>
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
		<form name="pagequery" action="/smartcardweb/sidypagequery.do"
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
									<td colspan="8" class="样式14">
										您
										<%=begin%>
										~
										<%=end%>
										的补助明细如下：
									</td>
								</tr>
								<tr align="center">

									<td align="center" class="样式13" width="120">
										补助批次号
									</td>
									<td align="center" class="样式13" width="80">
										客户号
									</td>
									<td align="center" class="样式13" width="80">
										补助类型
									</td>
									<td align="center" class="样式13" width="80">
										发生时间
									</td>
									<td align="center" class="样式13" width="120">
										领取时间
									</td>
									<td align="center" class="样式13" width="80">
										截至日期
									</td>
									<td align="center" class="样式13" width="120">
										补助金额（元）
									</td>
									<td align="center" class="样式13" width="80">
										状态
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
											<div align="center" class="样式12">
												<bean:write name="ttifsidy" property="batchNo" />
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
												<bean:write name="ttifsidy" property="custNo" />
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
												<bean:write name="ttifsidy" property="subsidytype" />
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
												<%=get_date%>
												<%=get_time%>
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
												<%=expire_date%>
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
												<bean:write name="ttifsidy" property="amount" format="0.00" />
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
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
									<td>
										&nbsp;
									</td>
								</tr>
								<%
								}
								%>
								<tr>
									<td align="left" colspan="8" class="样式14">
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
									%>

										<a
											onclick="javascript: window.location='/smartcardweb/main.do'"
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


