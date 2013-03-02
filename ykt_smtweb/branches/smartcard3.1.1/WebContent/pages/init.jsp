<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%

String monitortime = KSConfiguration.getInstance().getProperty("monitortime");
String buttonleft = KSConfiguration.getInstance().getProperty("buttonleft","10");
String buttontop = KSConfiguration.getInstance().getProperty("buttontop","140");
String buttonright = KSConfiguration.getInstance().getProperty("buttonright","220");
String buttonmargin = KSConfiguration.getInstance().getProperty("buttonmargin","50");
String read_card_device_port = KSConfiguration.getInstance().getProperty("read_card_device_port","0"); 
String webserverip = KSConfiguration.getInstance().getProperty("webserverip"); 
String webserverport =KSConfiguration.getInstance().getProperty("webserverport"); 
String webserverapp = KSConfiguration.getInstance().getProperty("webserverapp"); 
%>
<style type="text/css">
	   #mid_center ul li{ 
	   list-style:none;width:224px; 
	   margin-bottom:<%=buttonmargin%>px;
	   width:224px; 
	   height:73px;
	   }
	   
	   #Layerleft {
	   position:absolute;
	   left:<%=buttonleft%>px;
	   top:<%=buttontop%>px;
	   width:45%;
	   height:120px;
	   z-index:1;
      }
	#Layerright {
	position:absolute;
	right:<%=buttonright%>px;
	top:<%=buttontop%>px;
	width:30%;
	height:120px;
	z-index:1;
}
	</style>