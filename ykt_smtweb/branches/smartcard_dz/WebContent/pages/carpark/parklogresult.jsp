<%@ page contentType="text/html;charset=GBK"
	errorPage="/smartcardweb/login.do"%>
<%@ page import="com.kingstargroup.fdykt.dto.ParklogDTO"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<html>
	<head>
		<title>��ѯ���</title>
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
				document.parkpagequery.page.value = page;
				document.parkpagequery.submit();
			}
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
	%>
	<body scroll="no"
		onload="MM_preloadImages('/smartcardweb/pages/images/previcea.gif','/smartcardweb/pages/images/nexta.gif','/smartcardweb/pages/images/backa.gif')">
		<form name="parkpagequery" action="/smartcardweb/parkpagequery.do" method="post">
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
									<td colspan="7" class="��ʽ14" height="20">
										��
										<%=begin%>
										~
										<%=end%>
										�Ľ�����ϸ���£�
									</td>
								</tr>
								<tr align="center">
								    <td align="center" class="��ʽ13" height="20" width="6%">
                                             ���
                                    </td>
									<td align="center" class="��ʽ13" height="20" width="10%">
										�ͻ�����
									</td>
									<td align="center" class="��ʽ13" width="18%">
										����ʱ��
									</td>
									<td align="center" class="��ʽ13" width="18%">
										����ʱ��
									</td>
									<td align="center" class="��ʽ13" width="18%">
										�����ص�
									</td>
									<td align="center" class="��ʽ13" width="18%">
										�����ص�
									</td>
									<td align="center" class="��ʽ13">
										���ƺ�
									</td>
								</tr>
								<%
									int serial_no = 1;
									int count = 0;
								%>
								<logic:iterate id="parklog" name="parklogs" offset="0">
									<%
											ParklogDTO ts = (ParklogDTO)parklog;
											String checkintime = ts.getCheckintime();
											String checkouttime = ts.getCheckouttime();

											count++;
									%>
									<tr align="center">
										<td height="20" class="��ʽ12">
											<%=serial_no++%>
										</td>
										<td height="20" class="��ʽ12">
                                            <bean:write name="parklog" property="custname" />
                                        </td>
										<td height="20" class="��ʽ12">
											<%=checkintime%>
										</td>
										<td height="20" class="��ʽ12">
											<%=checkintime%>
										</td>
										<td height="20" class="��ʽ12">
											<bean:write name="parklog" property="checkinplace" />
										</td>
										<td height="20" class="��ʽ12">
											<bean:write name="parklog" property="checkoutplace"/>
										</td>
										<td height="20" class="��ʽ12">
											<bean:write name="parklog" property="carnumber"/>
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
									<td>
                                        &nbsp;
                                    </td>
								</tr>
								<%
								}
								%>
								<tr>
									<td align="left" colspan="7" class="��ʽ14" height="20">
										<%
											Integer val = (Integer) session.getAttribute("all");
											if (null == val) {
												pageContext.forward("/smartcardweb/main.do");
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
										.getAttribute("parklogs")).size();
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

