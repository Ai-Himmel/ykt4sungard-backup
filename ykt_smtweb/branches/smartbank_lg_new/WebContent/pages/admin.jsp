<%@ page contentType="text/html;charset=GBK"
	errorPage="/smartbank/index.do"%>
<%@ page import="com.kingstargroup.fdykt.dto.AssistanceDTO"%>
<%@ page import="com.kingstargroup.fdykt.dto.TTifSubsidyDTO"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="/smartcardweb/pages/js/other.js"></script><html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title></title>
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
			var  deviceId="deviceId=";
			var  path ="c:\\smartcard.txt";
			function   chk(){   
                var   obj   =   document.getElementsByName('dev');   
                for   (i=0;i<obj.length;i++){   
                if   (obj[i].checked){   
                deviceId = deviceId+obj[i].value;   
                writefile();
                alert("操作成功 ,"+deviceId+"被写入"+path+"文件");
                return;   
              }   
           }   
            alert('你没选');   
           }
		function writefile()
        {
            var fso = new ActiveXObject("Scripting.FileSystemObject");
            var f = fso.CreateTextFile(path, true);
              f.write(deviceId);
              f.WriteBlankLines(1);
              f.Close();
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
		int p = ((Integer) request.getAttribute("page")).intValue();
		int total = ((Integer) request.getAttribute("total")).intValue();
	%>
	<body scroll="no"
		onload="MM_preloadImages('<%=path%>/pages/images/previcea.gif','<%=path%>/pages/images/nexta.gif','<%=path%>/pages/images/backa.gif')">
		<form name="pagequery" action="<%=path%>/adminpagequery.do"
			method="post">
			<input name="page" type="hidden" value="1" />
			<input name="total" type="hidden" value="<%=total%>" /> 
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
									<td colspan="4" class="样式14"  id=msg>
										多媒体自助查询机
									</td>
								</tr>
								<tr >
                                    <td align="center" class="样式13" width="40">
										选择
									</td>
									<td align="center" class="样式13" width="80">
										设备号
									</td>
									<td align="center" class="样式13" width="80"> 设备名称 </td>
									<td align="center" class="样式13" width="80">
										设备类型
									</td>
									
								</tr>
								<%
									int serial_no = 1;
									int count = 0;
								%>
								<logic:iterate id="list" name="list" offset="0">
									<%
										    
											count++;
									%>
									<tr align="center">
									   <td height="20">
											<input  type="radio"    name="dev" value=<bean:write name="list" property="devId" /> />
										</td>
										<td height="20">
											<div align="center" class="样式12">
												<bean:write name="list" property="devId" />
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
												<bean:write name="list" property="devname" />
												&nbsp;
											</div>
										</td>
										<td height="20">
											<div align="center" class="样式12">
												<bean:write name="list" property="dictcaption" />
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
								</tr>
								<%
								}
								%>
								<tr>
									<td align="left" colspan="8" class="样式14">
										<%
											Integer val = (Integer) request.getAttribute("total");
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
										<%=request.getAttribute("page")%>
										页
									</td>
								</tr>
							</table>
						</div>
						<div id="content_buttom">
									<%
										int cur = ((Integer) request.getAttribute("page")).intValue();
										int currows = ((java.util.ArrayList) request
												.getAttribute("list")).size();
										if (cur > 1) {
									%>
										<a onclick="javascript:gotoNextPage(<%=p - 1%>)"
											onmouseout="MM_swapImgRestore()"
											onmousedown="MM_swapImage('previce','','<%=path%>/pages/images/previcea.gif',1)"><img
												src="<%=path%>/pages/images/previce.gif" name="previce"
												width="109" height="48" border="0" id="previce" /> </a>
									<%
										}
										if (cur < max) {
									%>
										<a onclick="javascript:gotoNextPage(<%=p + 1%>)"
											onmouseout="MM_swapImgRestore()"
											onmousedown="MM_swapImage('next','','<%=path%>/pages/images/nexta.gif',1)"><img
												src="<%=path%>/pages/images/next.gif" name="next"
												width="109" height="48" border="0" id="next" /> </a>
									<%
									}
									%>  
									  	<a onclick="javascript:chk();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','<%=path%>/pages/images/senda.gif',1)"><img
													src="<%=path%>/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>

										<a
											onclick="javascript: window.location='<%=path%>/index.do'"
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


