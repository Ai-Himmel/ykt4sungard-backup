<%@ include file="/tagslib.jsp"%>
<%@ page language="java" import="java.util.*" %>
<%@ page contentType="text/html;charset=GBK"%>

<%String path = request.getContextPath();
			String basePath = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ path + "/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
	<head>
		<base href="<%=basePath%>">

		<title>????</title>

		<meta http-equiv="pragma" content="no-cache">
		<meta http-equiv="cache-control" content="no-cache">
		<meta http-equiv="expires" content="0">
		<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
		<meta http-equiv="description" content="This is my page">

		<!--
    <link rel="stylesheet" type="text/css" href="styles.css">
    -->
		<SCRIPT language="javascript">
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
    </SCRIPT>
	</head>

	<body>
		<form name=form1>
			<input type="hidden" name="cmd" />
			<table>
				<tr>
				  
				    <logic:notPresent  name="Send">
				     
                                    ???????
                       
				   </logic:notPresent>
				 </tr>
				 <tr>  
					<logic:notEmpty name="Send">
						<td>
							<logic:equal name="Send" value="begin">
                                    ???????......
                            </logic:equal>
							<logic:equal name="Send" value="stop">
                                    ???????
                            </logic:equal>
						</td>
					</logic:notEmpty>
				</tr>
				<tr>
				  <logic:notPresent name="Receive">
				      
                                    ???????
                       
				    </logic:notPresent>
				 </tr>
				 <tr>
					<logic:notEmpty name="Receive">
						<td>
							<logic:equal name="Receive" value="begin">
                                    ???????......
                            </logic:equal>
							<logic:equal name="Receive" value="stop">
                                    ???????
                            </logic:equal>
						</td>
					</logic:notEmpty>
				</tr>
				<tr>
				<td>
			 <%String send = (String) application.getAttribute("Send");
		     	if (send == null || "stop".equals(send)) {
			  %>
			       <html:button property="beginSend" onclick="beginsend();">
                       ??????
                   </html:button>
		     <%}
			   if (send != null && "begin".equals(send)) {%>
				   <html:button property="beginSend" onclick="stopsend();">
                          ??????
                   </html:button>
					<%}%>
                </td>
                
               <td>
                 <%String receive = (String) application.getAttribute("Receive");
		     	   if (receive == null || "stop".equals(receive)) {
			     %>
			        <html:button property="beginRec" onclick="beginreceive();">
                         ??????
                    </html:button>
			     <%}%>
				 <% if (receive != null && "begin".equals(receive)) {%>
						<html:button property="beginRec" onclick="stopreceive();">
                           ??????
                       </html:button>
				 <%}%>
					</td>
				</tr>
			</table>
		</form>
		<br>
	</body>
</html>
