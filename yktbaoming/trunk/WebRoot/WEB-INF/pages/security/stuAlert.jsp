<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<html:html>
<html:errors/>
<html:form action="userAccessAction.do?method=load4stuAlert" enctype="multipart/form-data">
<body bgcolor="pink">
<center>
    <p>
	<font size="3.5" color="#990000"><b>�� �� �� ��</b></font>
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
	<font size="2.9"><b>���ѱ������¿��ԣ�����δ�ɷѣ�</b><br>	
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
	Ӧ�ɷ��ܶ�: <b><%=feetotal%></b> Ԫ��<br><b>���� <%=bmendfirst%> ǰ����ý���ͨ��һ��ͨ�ɷ�</b>������������ֹ���ڽ����ܽɷѡ�
	<p>
	�ڶ�ý����ɷ�ʱ������Ӧ�ɷ��ܶ�һ���Կۿ��ȷ��һ��ͨ���г�����<br><b>���������� <%=feetotal%> Ԫ��������ۿ</b>	
	</font>
	</td>
	</tr>
    </table>
	<p>
<input type="button" class="button_nor" value="�� ��" onclick="javascript:self.close()">
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