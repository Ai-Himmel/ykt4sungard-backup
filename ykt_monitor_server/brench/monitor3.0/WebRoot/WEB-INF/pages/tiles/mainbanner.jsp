<%@page pageEncoding="GBK"%>
<%@ include file="include.jsp"%>
<%@page import="java.text.SimpleDateFormat"%>

<%String style = (session != null && session.getAttribute("STYLE") != null) ? (String) session
					.getAttribute("STYLE")
					: "default";
			String context = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ request.getContextPath();
			String stylePath = context + "/pages/style/" + style;

            String userName = (String) session.getAttribute("userName");
            if (userName == null) {
				userName = "";
			}
			String personName = (String) session.getAttribute("personName");
			if (personName == null) {
				personName = "";
			}
%>

<div class="title">
      <div class="arrow"><%=userName%> - <%=personName%>�����ã� 
            ������<script language=JavaScript> var version = 1.0;</script> <script language=JavaScript1.1> var version = 1.1;</script> <script language=JavaScript1.2> var version = 1.2;</script> <script
								language=JavaScript1.3> var version = 1.3;</script> <script language="JavaScript">
								<!--
								var y=new Date();  
								var gy=y.getYear();  
								var dName=new Array("������","����һ","���ڶ�","������","������","������","������");  
								var mName=new Array("1��","2��","3��","4��","5��","6��","7��","8��","9��","10��","11��","12��");  
								if (version < 1.3)  
								{  
								    if (gy<2000)  
								    {  
										document.write(""+"19"+y.getYear()+"��" + mName[y.getMonth()] + y.getDate() + "�� " + dName[y.getDay()] + "" + "");  
									}  
									else  
										document.write(""+y.getYear()+"��" + mName[y.getMonth()] + y.getDate() + "�� " + dName[y.getDay()] + "" + "");  
									}  
									else  
									{  
										document.write(""+y.getFullYear() +"��"+ mName[y.getMonth()] + y.getDate() + "�� " + dName[y.getDay()] + "");  
									}  
								//-->
								</script></div>
</div>
