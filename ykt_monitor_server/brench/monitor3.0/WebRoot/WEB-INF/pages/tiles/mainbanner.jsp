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
      <div class="arrow"><%=userName%> - <%=personName%>，您好！ 
            今天是<script language=JavaScript> var version = 1.0;</script> <script language=JavaScript1.1> var version = 1.1;</script> <script language=JavaScript1.2> var version = 1.2;</script> <script
								language=JavaScript1.3> var version = 1.3;</script> <script language="JavaScript">
								<!--
								var y=new Date();  
								var gy=y.getYear();  
								var dName=new Array("星期天","星期一","星期二","星期三","星期四","星期五","星期六");  
								var mName=new Array("1月","2月","3月","4月","5月","6月","7月","8月","9月","10月","11月","12月");  
								if (version < 1.3)  
								{  
								    if (gy<2000)  
								    {  
										document.write(""+"19"+y.getYear()+"年" + mName[y.getMonth()] + y.getDate() + "日 " + dName[y.getDay()] + "" + "");  
									}  
									else  
										document.write(""+y.getYear()+"年" + mName[y.getMonth()] + y.getDate() + "日 " + dName[y.getDay()] + "" + "");  
									}  
									else  
									{  
										document.write(""+y.getFullYear() +"年"+ mName[y.getMonth()] + y.getDate() + "日 " + dName[y.getDay()] + "");  
									}  
								//-->
								</script></div>
</div>
