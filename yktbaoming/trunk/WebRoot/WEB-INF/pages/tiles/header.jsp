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

<table width="100%" height="86" border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td height="56" align="center" valign="top" background="<%=stylePath%>/images/top1bg.gif"><img src="<%=stylePath%>/images/top1.gif" width="997" height="56" border="0" usemap="#Map"></td>
  </tr>
  <tr> 
    <td align="center" valign="top" background="<%=stylePath%>/images/top2bg.jpg"><table width="997" height="30" border="0" cellpadding="0" cellspacing="0">
        <tr>
          <td width="226" align="left" valign="middle" background="<%=stylePath%>/images/top2.gif">&nbsp;</td>
          <td width="771" align="left" valign="middle"><font color="#FFFFFF"><%=userName%> - <%=personName%>�����ã� 
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
								</script></font></td>
        </tr>
      </table> </td>
  </tr>
</table>

<map name="Map">
	<area id='goout' shape="rect" coords="946,35,987,55" href="logoutAction.do?method=logout" target="_parent" onmousedown="doOut(this)">
</map>

<script language="javascript">
function doOut(ar){

var ga=null;
if(window.parent.main.studentForm!=null)
    ga=window.parent.main.studentForm.giveAlert.value;

if(ga!=null&&ga=='1'){  
    var opentop=(screen.height-350)/2;
    var openleft=(screen.width-450)/2;
	window.open('userAccessAction.do?method=load4stuAlertbyWin','newwindow','height=350,width=450,top='+opentop+',left='+openleft+',toolbar=no,menubar=no,scrollbars=yes, resizable=no,location=no, status=no');
}
else{
   if(window.parent.main.testPublishForm!=null)
        ga=window.parent.main.testPublishForm.giveAlert.value;
   
    if(ga!=null&&ga=='1'){  
        var opentop=(screen.height-350)/2;
        var openleft=(screen.width-450)/2;
	    window.open('userAccessAction.do?method=load4stuAlertbyWin','newwindow','height=350,width=450,top='+opentop+',left='+openleft+',toolbar=no,menubar=no,scrollbars=yes, resizable=no,location=no, status=no');
    }
}
 
}
</script>
