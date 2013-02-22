<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="userAccessAction.do?method=load4stuAlert" enctype="multipart/form-data">
<body bgcolor="pink">
<center>
    <p>
	<font size="3.5" color="#990000"><b>考 生 提 醒</b></font>
	<p>
	<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr>
	<td height="30" align="left" valign="middle" class="tdborder02">	
	<%
    String[] stubminfo=null;
    if(session.getAttribute("stubminfo")!=null){
        stubminfo=(String[])session.getAttribute("stubminfo");        
    }
    String bmendfirst="";
    if(request.getAttribute("bmendfirst")!=null){        
        bmendfirst=(String)request.getAttribute("bmendfirst");
    }
    String feetotal="";
    if(request.getAttribute("feetotal")!=null){        
        feetotal=(String)request.getAttribute("feetotal");
    }
    %>
	<font size="2.9"><b>您已报名如下考试，但尚未缴费：</b><br>	
	<%
	if(stubminfo!=null){
	    for(int i=0;i<stubminfo.length;i++){
	%>
	<%=(String)stubminfo[i]%><br>
	<%	
	    }	
	}
	%>
	</font>	
	<p>
	<font size="3">
	应缴费总额: <b><%=feetotal%></b> 元。<br><b>请在 <%=bmendfirst%> 前到多媒体机通过一卡通缴费</b>，超过报名截止日期将不能缴费。
	<p>
	在多媒体机缴费时，将按应缴费总额一次性扣款，请确保一卡通内有充足余额。<br><b>若卡内余额不足 <%=feetotal%> 元，将不予扣款！</b>	
	</font>
	</td>
	</tr>
    </table>
	<p>
<input type="button" class="button_nor" value="关 闭" onclick="javascript:self.close()">
</center>
</body>
</html:form>
</html:html>

<script language="JavaScript">

function init(){
   if(opener.goout!=null){
       opener.goout.click();
   }
   else if(opener!=null){
       opener.parent.location="logoutAction.do?method=logout";
   }
}
window.onload=init;
</script>