<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp" %>
<%@ include file="permission2.jsp" %>
<html>
   <head>
    <title><bean:message key="system.name"/></title>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css"/>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css"/>
    <link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css"/>
   </head>
   
  <body>	
  <form   action="<%= ContextUtil.getCtxPath(request)%>/implunch.do" name="implunchForm" method="post" enctype="multipart/form-data">
       <table width="70%" border="0" align="center" cellpadding="0"  cellspacing="0">
          <tr><td>&nbsp;</td></tr>
          <tr><td>&nbsp;</td></tr>
	        <tr>
	            <td>                        
			        <bean:message key="imp.file"/> <input type="file" name="theFile" size="20"/>
			         &nbsp;&nbsp;
			         <button onclick="document.forms[0].submit();"><bean:message key="btn.imp" /></button>
		        </td>	      
		        <td>
		             <a href="javascript:getModel()"> <bean:message key="upload.model"/></a> 
		       </td>
	        </tr>
	   </table>
	    <table width="70%" border="0" align="center" cellpadding="0"  cellspacing="0">
          <tr><td>&nbsp;</td></tr>
          <tr><td>&nbsp;</td></tr>
	        <tr>
	            <td>                        
			       <% 
			          String result = request.getAttribute("resultstring")==null?"":request.getAttribute("resultstring").toString();
			          out.println(result);
			        %>
		        </td>	      
		        <td><br><br></td>
	        </tr>
	   </table>
   </form>
  </body>
</html>
 <form action="<%= ContextUtil.getCtxPath(request)%>/uploadlunch.do"  method="post" >
 
 </form>
<script language="JavaScript">
function getModel(){
   document.forms[1].submit();
}
</script>