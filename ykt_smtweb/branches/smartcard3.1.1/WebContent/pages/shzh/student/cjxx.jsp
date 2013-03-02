<%@ page contentType="text/html;charset=GBK" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%
	int totalPage = Integer.parseInt(request.getAttribute("totalPage").toString());
	int currentPage = Integer.parseInt(request.getAttribute("currentPage").toString());
%>
<html>
	<head>
		<title>成绩信息</title>
		<link href="/smartcardweb/pages/css/css.css" rel="stylesheet" type="text/css" />
		<link href="/smartcardweb/pages/css/menu.css" rel="stylesheet" type="text/css" />
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
				document.pagequery.currentPage.value = page;
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
		<script type="text/javascript">
			function easytabs(active,url) {
				var tabcount = 2;
				for (i = 1; i <= tabcount; i++) {
					document.getElementById("tablink" + i).className = 'tab' + i;
				}
				document.getElementById("tablink" + active).className = 'tab' + active + ' tabactive';
				for (i = 1; i <= tabcount; i++) {
					document.getElementById("li" + i).className = 'tab' + i;
				}
				document.getElementById("li" + active).className = 'tab' + active + ' tabactive';
				window.location= url;
			}											
		</script>
	</head>
	<body scroll="no"
		onload="MM_preloadImages('/smartcardweb/pages/images/previcea.gif','/smartcardweb/pages/images/nexta.gif','/smartcardweb/pages/images/backa.gif')">
		<form name="pagequery" action="/smartcardweb/student/cjxx.do" method="post">
			<input name="currentPage" type="hidden" value="1" />
		</form>
		<div id="mid_top">
			<div class="menu">
				<ul style="width:280px;">
					<li id="li1">
						<a href="javascript:easytabs('1','/smartcardweb/pages/shzh/funcinfo.jsp');" id="tablink1" class="tab1">课程信息</a>
					</li>
					<li id="li2" class="tabactive">
						<a href="javascript:easytabs('2','/smartcardweb/student/cjxx.do');" id="tablink2" class="tab2 tabactive">成绩信息</a>
					</li>
				</ul>
			</div>
		</div>
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
								<tr align="center">
									<td align="center" class="样式13" height="20" width="13%">
										学年
									</td>
									<td align="center" class="样式13" width="7%">
										学期
									</td>
									<td align="center" class="样式13" width="30%">
										课程名称
									</td>
									<td align="center" class="样式13" width="10%">
										学分
									</td>
									<td align="center" class="样式13" width="10%">
										平时成绩
									</td>
									<td align="center" class="样式13" width="10%">
										期中成绩
									</td>
									<td align="center" class="样式13" width="10%">
										期末成绩
									</td>
									<td align="center" class="样式13" width="10%">
										总评成绩
									</td>
								</tr>
								<%
									int count = 0;
								%>
								<logic:iterate id="row" name="result" offset="0">
								<%
									count++;
								%>
									<tr align="center">
										<td height="20" class="样式12">
											<bean:write name="row" property="XN" />
										</td>
										<td height="20" class="样式12" nowrap="nowrap">
											<bean:write name="row" property="XQ" />
										</td>
										<td height="20" class="样式12">
										 	<bean:write name="row" property="KCMC"/>                                    
										</td>
										<td height="20" class="样式12">
											<bean:write name="row" property="XF"/>    
										</td>
										<td height="20" class="样式12">
                                        	<bean:write name="row" property="PSCJ"/>    
										</td>
										<td height="20" class="样式12" nowrap="nowrap">
                                            <bean:write name="row" property="QZCJ" />
                                        </td>
                                        <td height="20" class="样式12" nowrap="nowrap">
                                            <bean:write name="row" property="QMCJ" />
                                        </td>
                                        <td height="20" class="样式12" nowrap="nowrap">
                                            <bean:write name="row" property="ZPCJ2" />
                                        </td>
									</tr>
								</logic:iterate>
								<%
									for (int i = count; i < 10; i++) {
								%>
								<tr>
									<td height="20" class="样式12">&nbsp;</td>
									<td height="20" class="样式12">&nbsp;</td>
									<td height="20" class="样式12">&nbsp;</td>
									<td height="20" class="样式12">&nbsp;</td>
									<td height="20" class="样式12">&nbsp;</td>
									<td height="20" class="样式12">&nbsp;</td>
									<td height="20" class="样式12">&nbsp;</td>
									<td height="20" class="样式12">&nbsp;</td>
								</tr>
								<%
									}
								%>
								<tr>
									<td align="left" colspan="7" class="样式14" height="20">
										总共<%=totalPage%>页 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; 当前第<%=currentPage%>页
									</td>
								</tr>
							</table>
						</div>
						<div id="content_buttom">
							<%
								if (currentPage > 1) {
							%>
							<a onclick="javascript:gotoNextPage(<%=currentPage - 1%>)"
								onmouseout="MM_swapImgRestore()"
								onmousedown="MM_swapImage('previce','','/smartcardweb/pages/images/previcea.gif',1)"><img
									src="/smartcardweb/pages/images/previce.gif" name="previce"
									width="109" height="48" border="0" id="previce" /> </a>
							<%
								}
								if (currentPage < totalPage) {
							%>
							<a onclick="javascript:gotoNextPage(<%=currentPage + 1%>)"
								onmouseout="MM_swapImgRestore()"
								onmousedown="MM_swapImage('next','','/smartcardweb/pages/images/nexta.gif',1)"><img
									src="/smartcardweb/pages/images/next.gif" name="next"
									width="109" height="48" border="0" id="next" /> </a>
							<%
								}
							%>
							<a onclick="javascript: window.location='/smartcardweb/shzhstudent.do'"
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

