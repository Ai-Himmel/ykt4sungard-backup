<%@ page contentType="text/html;charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html>
	<head>
		<title>ת��ȷ��</title>
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet"
			type="text/css" />
		<script language="javascript">		
		function domobiletrans(){
			errmsg.innerHTML="<b>�벻Ҫ���߿�Ƭ��ϵͳȷ���У����Ժ�...<br/></b>";
			document.writeCardForm.submit();
		}
      </script>
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
	</script>
	
	</head>
	<body scroll="no" onkeydown="return (event.keyCode!=8)">
		<form action="<%=path%>/cityhotspotCheck.do" method="post"
			name="writeCardForm">
			<div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="<%=path%>/pages/images/zz.gif" width="314"
									height="82" />
							</div>

							<div id="content_input">
								<table width="80%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">

											<input type="hidden" name="cardno"
												value="<%=request.getAttribute("cardno") == null ? ""
					: request.getAttribute("cardno")%>" />
											<input type="hidden" name="TransAmount"
												value="<%=request.getAttribute("TransAmount") == null ? "" : request
					.getAttribute("TransAmount")%>" />
											<input type="hidden" name="SerialNo"
												value="<%=request.getAttribute("SerialNo") == null ? ""
					: request.getAttribute("SerialNo")%>" />
											<input type="hidden" name="OutCardAmount"
												value="<%=request.getAttribute("OutCardAmount") == null ? ""
					: request.getAttribute("OutCardAmount")%>" />
					                        <input type="hidden" name="pwd"
												value="<%=request.getAttribute("pwd") == null ? ""
					: request.getAttribute("pwd")%>" />
					 						<input type="hidden" name="cxCnt"
												value="<%=request.getAttribute("cxCnt") == null ? ""
					: request.getAttribute("cxCnt")%>" />
					                        

									<tr>
										<td height="35" class="��ʽ13">
											 ת�˽�
										</td>
										<td>
											<%=request.getAttribute("TransAmount") == null ? "" : request.getAttribute("TransAmount").toString()%>
											 
											 Ԫ
										</td>
									</tr>
									
									<tr>
										<td height="35" class="��ʽ13">
											 ת�˺�һ��ͨ��
										</td>
										<td>
											<%=request.getAttribute("OutCardAmount") == null ? "": request.getAttribute("OutCardAmount").toString()%>
											 
											 Ԫ
										</td>
									</tr>
									<tr>
										<td height="120" align="center" class="��ʽ13" id="errmsg"
											colspan="2">
											<b><html:errors />
											 ��ȷ�Ϸźÿ�&nbsp;</b>
										</td>
									</tr>
								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
										<td align="center">
											<a onclick="javascript:domobiletrans();"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','<%=path%>/pages/images/senda.gif',1)"><img
													src="<%=path%>/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
										</td>
										<td>
											<a
												onclick="javascript: window.location='<%=path%>/main.do';"
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('back','','<%=path%>/pages/images/backa.gif',1)"><img
													src="<%=path%>/pages/images/back.gif" name="back"
													width="109" height="48" border="0" id="back" /> </a>
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
				height="0" codebase="<%=path%>/rf35.cab#version=2,0,0,7" />
		</form>
	</body>
</html>

