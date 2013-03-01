<%@ page pageEncoding="gbk" %>
<%@ page contentType="text/html;charset=gbk" language="java" %>
<%@ page  import="java.util.*"%>
<%@ page  import="java.math.*"%>
<%@ page import="com.kingstargroup.advquery.common.GetProperty"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">

<%
response.setHeader("Cache-Control","no-cache");
response.setHeader("Cache-Control","no-store"); 
response.setDateHeader("Expires", 0); 
response.setHeader("Pragma","no-cache");
%>

<%@ page buffer="100kb"%>


<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gbk">
<title>住训培训服务费打印</title>
<style type="text/css">
@media  print{.noPrint{visibility:hidden !important}}  
<!--
.style1 {
	font-family: "仿宋_GB2312";
	font-weight: bold;
	color: #ECE9D8;
}
.style3 {color: #000000}
.style4 {font-family: "方正舒体", "方正姚体", "黑体", "华文仿宋", "华文彩云", "宋体", "隶书", "楷体_GB2312"}
.style6 {
	font-family: "华文新魏";
	font-size: 40px;
}
.style7 {font-family: "华文仿宋"}
　P   {page-break-after:   always}     
-->
</style>
</head>

<body>
<form  name="printform">

<table width="80%"  align="center" border="1" cellpadding="1" cellspacing="1" bordercolor="#CCCCCC">
    <tr >
       <td align="center" width="150"><%= GetProperty.getProperties("serfee.name",getServletContext())%><td>
       <td align="center" width="150"><%= GetProperty.getProperties("serfee.stuempno",getServletContext())%><td>
       <td align="center" width="150"><%= GetProperty.getProperties("serfee.classno",getServletContext())%><td>
       <td align="center" width="150"><%= GetProperty.getProperties("serfee.manId",getServletContext())%></td>
       <td align="center" width="60"><%= GetProperty.getProperties("serfee.fillserfee",getServletContext())%></td>
       <td align="center" width="60"><%= GetProperty.getProperties("serfee.fillself",getServletContext())%></td>
       <td align="center" width="60"><%= GetProperty.getProperties("serfee.accountbal",getServletContext())%></td>
       <td align="center" width="60"><%= GetProperty.getProperties("serfee.smlbalance",getServletContext())%> </td>
       <td align="center" width="60"><%= GetProperty.getProperties("serfee.facttotlebal",getServletContext())%></td>
       <td align="center" width="60"><%= GetProperty.getProperties("serfee.backbal",getServletContext())%></td>
       <td align="center" width="60"><%= GetProperty.getProperties("serfee.consbal",getServletContext())%></td>
        
    <tr>
    <%
      List list  = new ArrayList();
      list = (List)session.getAttribute("SerFeeQuery");
      if(list !=null && list.size()>0){ 
         for(int i=0;i<list.size();i++){
            HashMap  temp =  (HashMap)list.get(i);
           
    %>
      
       <tr>
       <td align="center" width="150"><%=temp.get("custName")%><td>
       <td align="center" width="150"><%=temp.get("stuempNo")%><td>
       <td align="center" width="150"><%=temp.get("classNo")%><td>
       <td align="center" width="150"><%=temp.get("manId")%></td>
       <td align="right" width="60"><%=new BigDecimal(temp.get("fillserfee").toString()).setScale(2, BigDecimal.ROUND_HALF_UP)%></td>
       <td align="right" width="60"><%=new BigDecimal(temp.get("fillselftotle").toString()).setScale(2, BigDecimal.ROUND_HALF_UP)%></td>
       <td align="right" width="60"><%=new BigDecimal(temp.get("accountbal").toString()).setScale(2, BigDecimal.ROUND_HALF_UP)%></td>
       <td align="right" width="60"><%=new BigDecimal(temp.get("smlbalance").toString()).setScale(2, BigDecimal.ROUND_HALF_UP)%> </td>
       <td align="right" width="60"><%=new BigDecimal(temp.get("facttotlebal").toString()).setScale(2, BigDecimal.ROUND_HALF_UP)%></td>
       <td align="right" width="60"><%=new BigDecimal(temp.get("backbal").toString()).setScale(2, BigDecimal.ROUND_HALF_UP)%></td>
       <td align="right" width="60"><%=new BigDecimal(temp.get("consbal").toString()).setScale(2, BigDecimal.ROUND_HALF_UP)%></td>
    <tr>
     
    <%}
    }
    %>
</table>  
</form>
<DIV class="noPrint"> 
<TABLE align="center">
<TR>
<TD aligh="center"> 
	<object id="WebBrowser" width=0 height=0 classid="CLSID:8856F961-340A-11D0-A96B-00C04FD705A2"></object>
	<input name=print type="button" onclick="javascript:selfprint()" value="  打 印  ">&nbsp;&nbsp;
	<input type=button value=页面设置 onclick="javascript:document.all.WebBrowser.ExecWB(8,1)">&nbsp;&nbsp;
	<input type=button value=打印预览 onclick="document.all.WebBrowser.ExecWB(7,1)">&nbsp;&nbsp; 
    <input type="button" onclick="javascript:window.close();" value="关闭窗口"></TD>
</TR>
</TABLE>
</DIV>
</body>
</html>

<script language="javascript">
	var HKEY_Root,HKEY_Path,HKEY_Key; 
	HKEY_Root="HKEY_CURRENT_USER"; 
	HKEY_Path="\\Software\\Microsoft\\Internet Explorer\\PageSetup\\"; 
	//设置网页打印的页眉页脚为空 
	function PageSetup_Null() 
	{ 
		try 
		{ 
			alert("hkey_root = "+HKEY_Root);
			alert("hkey_path = "+HKEY_Path);
			var Wsh=new ActiveXObject("WScript.Shell"); 
			HKEY_Key="header"; 
			Wsh.RegWrite(HKEY_Root+HKEY_Path+HKEY_Key,""); 
			HKEY_Key="footer"; 
			Wsh.RegWrite(HKEY_Root+HKEY_Path+HKEY_Key,""); 
		} 
		catch(e)
		{
			alert("错误是 "+e);
		} 
	}

	function selfprint(){
		PageSetup_Null();
		window.print();
	}



</script>

