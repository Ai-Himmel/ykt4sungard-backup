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

			String personName = (String) session.getAttribute("personName");
			if (personName == null) {
				personName = "";
			}
%>

<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td height="63" align="left" valign="top" background="<%=stylePath%>/images/banner_bg.jpg"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td width="63"><img src="<%=stylePath%>/images/banner.jpg" width="525" height="63"></td>
        <td align="left" valign="top"><table width="100%" height="53" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td height="53" align="right" valign="bottom"><a href="logoutAction.do?method=logout" target="_parent" class="black_link">ע��</a> | <a href="changePWDManager.do?method=load4ChangePWD" class="black_link" target="main">�޸�����</a>&nbsp;&nbsp;</td>
          </tr>
        </table></td>
      </tr>
    </table></td>
  </tr>
  <tr>
    <td height="16" align="center" valign="middle" bgcolor="#000000"><span class="smallwhite"><%=personName%>������! 
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
								</script></span></td>
  </tr>
</table>





