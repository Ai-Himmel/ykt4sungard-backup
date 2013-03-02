 
<%@ include file="tagslib.jsp"%>
<%@ page import="com.kingstargroup.mobileMessage.util.KSConfiguration"%>
<%@ page contentType="text/html;charset=GBK"%>
<% long  seconds = KSConfiguration.getInstance().getPropertyAsInt("sendSeconds",10);%>
<html >
<head>
<logic:notEmpty name="Send">
  <logic:equal name="Send" value="begin">
<!-- <meta   http-equiv="refresh"   content="<%=seconds%>">   -->
 </logic:equal>
</logic:notEmpty>
<title>发送/接受服务</title>
<script language="JavaScript">
window.onload = maxWindow;
function maxWindow()
{
window.moveTo(300,100);
if (document.all)
{
  top.window.resizeTo(600,500);
}
else if (document.layers||document.getElementById)
{
  if (top.window.outerHeight<screen.availHeight||top.window.outerWidth<screen.availWidth)
  {
    top.window.outerHeight = screen.availHeight;
    top.window.outerWidth = screen.availWidth;
  }
}
}
 function  beginsend(){
          
       	   document.form1.action="/mobileMessage/send.do?";
       	   document.form1.cmd.value="begin";
       	   form1.submit();
       }
        function  stopsend(){
       	   document.form1.action="/mobileMessage/send.do?";
       	   document.form1.cmd.value="stop";
       	   form1.submit();
       }
       function beginreceive(){
           document.form1.action="/mobileMessage/receive.do?";
           document.form1.cmd.value="begin";
           form1.submit();
       }
         function stopreceive(){
           document.form1.action="/mobileMessage/receive.do?";
           document.form1.cmd.value="stop";
           form1.submit();
       }

</script>
</head>
<body>
<form name="form1">
<input type="hidden" name="cmd" />
<table width="400" height="220" align="center" border="0" cellpadding="0" cellspacing="0" style="border:1px solid #ccc; background:#DADADA;">
  <tr>
    <td><table width="380" height="200" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#FFFFFF" style="border:1px solid #ccc">
      <tr>
        <td><table width="80%" border="0" align="center" cellpadding="0" cellspacing="0">
          <tr>
            <td align="center" style="font-weight:bold; color:#FF6600; font-size:14px; line-height:38px;">
                  <logic:notPresent  name="Send">
                                    发送服务未启动
				  </logic:notPresent>
				  <logic:notEmpty name="Send">
							<logic:equal name="Send" value="begin">
                                   发送服务已启动
                            </logic:equal>
							<logic:equal name="Send" value="stop">
                                   发送服务已停止
                            </logic:equal>
					</logic:notEmpty>
            </td>
          
          </tr>
          <tr>
            <td colspan="2" align="center"></td>
          </tr>
          <tr>
            <%String send = (String) application.getAttribute("Send");
		     	if (send == null || "stop".equals(send)) {
			  %>
               <td align="center"><img src="images/start_send.gif" width="106" height="21" onclick="beginsend();"/></td>
               <%}if (send != null && "begin".equals(send)) {%>
			   <td align="center"><img src="images/start_send.gif" width="106" height="21" /></td>
			   <%}%>
			   
          </tr>
        </table></td>
      </tr>
    </table></td>
  </tr>
</table>
</form>
</body>
</html>
