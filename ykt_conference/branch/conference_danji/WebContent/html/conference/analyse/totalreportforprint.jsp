<%@ page pageEncoding="GBK"%>
<%@ include file="/html/commons/init.jsp"%>
<%@ include file="/html/commons/top_calendar.jsp"%>

<%@ page import="java.util.ArrayList"%>

<%@ page import="com.kingstargroup.conference.common.GetProperty"%>
<%@ page
	import="com.kingstargroup.conference.hibernate.form.TConference"%>

<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ taglib uri="http://ajaxanywhere.sourceforge.net/" prefix="aa"%>
<head>

	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/style.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css"
		rel="stylesheet" type="text/css" />
	<link
		href="<%=ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css"
		rel="stylesheet" type="text/css" />
	<html:base />
	<style type="text/css">
<!--
.style1 {
	font-size: 36px;
	font-weight: bold;
}
.style2 {font-size: 24px}
-->
</style>
</head>

<% 
	List conflist = (List) request.getAttribute("conflist");
	List conftype = (List) request.getAttribute("conftype");
%>
<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0" ondblclick="holeset();">
	<form action="<%=ContextUtil.getCtxPath(request)%>/totalreport.do"
		name="signAnalyseForm" method="post">
		<table width="95%" height="100%" border="0" align="center" cellpadding="0"
			cellspacing="0">

			<tr>
				<td>
					&nbsp;
				</td>
			</tr>

			<tr>
				<td align="left" valign="top">
					&nbsp;
				</td>
			</tr>
	
			<tr>
				<td align="left" valign="top">
				<!--startprint-->
				
				<table width="75%"  border="0" align="center">
				
					<%  
						TConference con = new TConference();
						boolean ifconf = false;
						boolean iftype = false;
		        		if(null != request.getAttribute("conference")) {
		        			List conlist = (List) request.getAttribute("conference");
		        			if(!conlist.isEmpty()) {
		        				Iterator coniter = conlist.iterator();
		        				if(coniter.hasNext()) {
			        				con = (TConference) coniter.next();
			        				ifconf = true;
			        			}
			        		}
		        		} else if (null != ParamUtil.getString(request,"conType")) {
		        			iftype = true;
		        		}
		        		
		        		ArrayList count = new ArrayList();
		        		boolean if_count = false;
		        		boolean if_per = false;
		        		int all = 0, ///* Ӧ��ϯ */
		        		presented =0;/* ʵ��ϯ */
		        		float percent=0;
		        		if(null != request.getAttribute("concount")) {
		        		count = (ArrayList) request.getAttribute("concount");        			
		        		all= ((Integer) count.get(0)).intValue(); /* Ӧ��ϯ */
		        		presented= ((Integer) count.get(1)).intValue();/* ʵ��ϯ */
		        		if(all>0){
		        			percent = presented * 10000 / all / 100.00f;
		        		}
						
		        		}
		        	%>
  <tr>
    <td height="70"><div align="center"><span class="style1"><%=ifconf==true?con.getConName():"" %></span></div></td>
    
  </tr>
  <tr>
    <td height="60"><div align="center"><span class="style1">��ϯ�����������浥 </span></div></td>
  </tr>
  <tr>
    <td height="33"><div align="center"><span class="style2"> </span></div>      <div align="left"></div></td>
  </tr>
  <tr>
    <td height="60"><span class="style2">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;��ϯ���λ��飬Ӧ������ <%=ifconf==true?all:0 %> �ˣ�ʵ������<%=ifconf==true?presented:0 %>���ˣ�</span></td>
  </tr>
  <tr>
    <td height="60"><span class="style2">ʵ��������� <%=percent %>����</span></td>
  </tr>
  <tr>
    <td height="60"><span class="style2">�ش˱��档 </span></td>
  </tr>
  <tr>
    <td height="60"><div align="right" class="style2">������鴦 </div></td>
  </tr>
  <tr>
    <td height="60"><div align="right" class="style2"><%=ifconf==true?con.getConBegindate().substring(0,4):"" %>��<%=ifconf==true?con.getConBegindate().substring(4,6):"" %>��<%=ifconf==true?con.getConBegindate().substring(6,8):"" %>�� </div></td>
  </tr>
</table>

					<!--endprint-->
				</td>
			</tr>
			
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td height="40" align="right" valign="middle" class="tdborder02">
					<input name="Submit" type="button" class="button_nor"
						value='<bean:message key="button.return"/>'
						onClick="javascript:cancelPage();" >
						<input name="print" type="button" class="button_nor" value='<bean:message key="button.print"/>' onclick="javascript:preview();">
				</td>
			</tr>	
		</table>
	</form>
	<script>
	function holeset(){
		if(parent.document.getElementById('subnavframe').style.display==''){
			parent.document.getElementById('subnavframe').style.display='none';
			parent.document.getElementById('top').style.display='none';
			parent.document.getElementById('bottom').style.display='none';
		}else{
			parent.document.getElementById('subnavframe').style.display='';
			parent.document.getElementById('top').style.display='';
			parent.document.getElementById('bottom').style.display='';
		}	
		
	}
	
	function SetValue(tag){
		var flag = tag;
		document.forms[0].action='<%=ContextUtil.getCtxPath(request)%>/totalreport.do?flag='+flag;
		ajaxAnywhere.submitAJAX();
	}
	function cancelPage() {
      	self.location = '<%= ContextUtil.getCtxPath(request)%>/anal/totalquery.do?flag=print';
	}
	
	function preview()
	{
		parent.document.getElementById('subnavframe').style.display='none';
		parent.document.getElementById('top').style.display='none';
		parent.document.getElementById('bottom').style.display='none';
		bdhtml=window.document.body.innerHTML;
		sprnstr="<!--startprint-->";
		eprnstr="<!--endprint-->";
		prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+17);
		prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
		window.document.body.innerHTML=prnhtml;
		window.print();
	}
	
	function doPrint()
{
		var bdhtml=window.document.body.innerHTML;
		
		sprnstr="<!--startprint-->";
		eprnstr="<!--endprint-->";
		prnhtml=bdhtml.substr(bdhtml.indexOf(sprnstr)+17);
		prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
	var table = prnhtml;

	var html="<html>\n";
	html += "<head>\n";
	html += "<title> ����ǩ��ͳ�Ʊ��� </title>\n";
	html += "<meta http-equiv='content-type' content='text/html; charset=gb2312'>\n";
	html += "</head>\n";
	html += "<body bgcolor=#ffffff topmargin=5 leftmargin=5 marginheight=5 marginwidth=5 onLoad='window.print()'>\n";
	html += "<center>\n";
	html += "<table width=650 border=0 cellspacing=0 cellpadding=0>\n";
	html += "<tr>\n";
	html += "<td height=34 width=150>&nbsp;</td>\n";
	html += "<td align=right valign=bottom><a href='javascript:history.back()'>����</a>��<a href='javascript:window.print()'>��ӡ</a></td>\n";
	html += "</tr>\n";
	html += "<tr>\n";
	html += "<td colspan='2'>\n";
	html += table + "\n";
	html += "</td>\n";
	html += "</tr>\n";
	html += "</table>\n";
	html += "</center>\n";
	html += "<br>\n";
	html += "</body>\n";
	html += "</html>\n";

	document.write(html);
	document.close();
	
}

</script>

</body>
