<%@ page contentType="text/html;charset=GBK"%>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>������Ϣ</title>
		<link href="pages/css/css.css" rel="stylesheet" type="text/css" />
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
	.��ʽ12 {
	font-family: "����"; 
	color: #000000; 
	font-size: 16px; 
	}
	.��ʽ13 {
	font-family: "����"; 
	color: #000000; 
	font-size: 18px; 
	}
}
</style>
	</head>

	<%
		com.kingstargroup.fdykt.dto.AccountDTO acc = (com.kingstargroup.fdykt.dto.AccountDTO) session
				.getAttribute("account");
		String state = acc.getState_id();
		String tmp = "";
		if (state.equals("1000")) {
			tmp = "����";
		} else if (state.equals("2000")) {
			tmp = "ע��";
		} else if (state.equals("1100")) {
			tmp = "��ʧ";
		} else if (state.equals("1010")) {
			tmp = "����";
		} else if (state.equals("1001")) {
			tmp = "д��ʧ��";
		} else if (state.equals("1110")) {
			tmp = "��ʧ����";
		} else if (state.equals("1111")) {
			tmp = "��ʧ����д��ʧ��";
		}
		String open_Date = acc.getOpen_Date();
		String close_Date = acc.getClose_Date();
		if (open_Date != null && open_Date.length() == 8)
			open_Date = open_Date.substring(0, 4) + "��"
			+ open_Date.substring(4, 6) + "��"
			+ open_Date.substring(6, 8) + "��";
		if (close_Date != null && close_Date.length() == 8)
			close_Date = close_Date.substring(0, 4) + "��"
			+ close_Date.substring(4, 6) + "��"
			+ close_Date.substring(6, 8) + "��";
	%>
	<body scroll="no" onload="MM_preloadImages('/smartcardweb/pages/images/backa.gif')">
		<div id="mid_top"></div>
		<div id="middle">
			<div id="Layer1">
				<div id="content">
					<div id="content_left"></div>
					<div id="content_middle">
						<div align="center">
							<img src="/smartcardweb/pages/images/title.gif" width="314"
								height="82" />
						</div>
						<div id="content_input">
							<table width="80%" border="0" align="center" cellpadding="0"
								cellspacing="0" class="box">
								<tr>
									<td height="30" class="��ʽ13">
										��&nbsp;��&nbsp;��
									</td>
									<td>
										<bean:write name="account" property="customer_id" />
										&nbsp;
									</td>
								</tr>
								<tr>
									<td width="320" height="30" class="��ʽ13">
										��&nbsp;��&nbsp;��
									</td>
									<td>
										<bean:write name="account" property="cut_name" />
										&nbsp;
									</td>
								</tr>								
								<tr>
									<td height="30" class="��ʽ13">
										����/ѧ��
									</td>
									<td>
										<bean:write name="account" property="stuEmp_no" />
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="30" class="��ʽ13">
										��&nbsp;&nbsp;&nbsp;&nbsp;��
									</td>
									<td>
										<bean:write name="account" property="classDept_name" />
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="30" class="��ʽ13">
										��&nbsp;&nbsp;&nbsp;&nbsp;��
									</td>
									<td>
										<bean:write name="account" property="account_id" />
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="30" class="��ʽ13">
										��&nbsp;״&nbsp;̬
									</td>
									<td>
										<%=tmp%>
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="30" class="��ʽ13">
										��&nbsp;��&nbsp;��
									</td>
									<td>
										<bean:write name="account" property="type_name" />
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="30" class="��ʽ13">
										�˻����
									</td>
									<td>
										<bean:write name="account" property="cur_FreeBala"
											format="0.00" />
										Ԫ
									</td>
								</tr>
								<tr>
									<td height="30" class="��ʽ13">
										��������
									</td>
									<td>
										<%=open_Date%>
										&nbsp;
									</td>
								</tr>
								<tr>
									<td height="30" class="��ʽ13">
										��Ч����
									</td>
									<td>
										<%=close_Date%>
										&nbsp;
									</td>
								</tr>

							</table>
						</div>
						<div id="content_buttom">
							<a onclick="javascript: window.location='/smartcardweb/main.do';"
								onmouseout="MM_swapImgRestore()"
								onmousedown="MM_swapImage('Image2','','/smartcardweb/pages/images/backa.gif',1)"><img
									src="/smartcardweb/pages/images/back.gif" name="Image2"
									width="109" height="48" border="0" id="Image2" />
							</a>
						</div>
					</div>
					<div id="content_right"></div>
				</div>
			</div>
		</div>
		<div id="bottom"></div>
	</body>
</html>

