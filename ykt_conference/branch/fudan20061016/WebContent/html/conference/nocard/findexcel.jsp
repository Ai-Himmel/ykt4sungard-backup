<%@ include file="/html/commons/init.jsp"%>
<%@ page import="java.io.*"%>
<%@ page import="java.util.*"%>
<%@ page import="javazoom.upload.*"%>
<%@ page import="uploadutilities.FileMover"%>
<%@ page import="java.text.SimpleDateFormat"%>
<%@ page import="com.kingstargroup.conference.util.ExcelReader"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetProperty" %>
<%@ page import="com.kingstargroup.conference.util.ConferenceUtil" %>
<%@ page import="org.apache.commons.configuration.PropertiesConfiguration"%>

<%@ include file="/html/commons/permission.jsp" %>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312"> 
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/html/commons/js/util.js"></script>
<%@ page language="java" pageEncoding="UTF-8"%>

<head>
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/css/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/html/commons/styles/extremecomponents.css" rel="stylesheet"
	type="text/css" />
<html:base/>
</head>

<body bgcolor="#EFEFEF" leftmargin="0" topmargin="0">
   
	
	<table width="800" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr> 
		<td>&nbsp;</td>
	</tr>
	<tr> 
		<td height="25" align="left" valign="middle" background="<%= ContextUtil.getCtxPath(request)%>/html/commons/images/image_lines.jpg">&nbsp;&nbsp;&nbsp;
		<span class="mediumwhite"><strong></strong></span>&nbsp;<span class="mediumwhite"><strong><bean:message key="conflist.nocard"/></strong></span></td>
	</tr>
	 <form  name="modelForm"  method="post" action="<%= ContextUtil.getCtxPath(request)%>/getModel.do" >
   
    <tr>
    <td width="20%" align="left" >
			<a href="#" onclick="DoExportModel();return false;">人员数据导入模板<IMG src="/conference/html/commons/images/xls.gif" border="0"></a>
	</td>
	</tr>
    </form>
	<form   name="FindExcelForm"  method="post" action=""  ENCTYPE="multipart/form-data">
	<tr> 
		<td align="left" valign="top" >&nbsp;</td>
	</tr>
		<td align="left" valign="top">
					<table width="80%" border="1" cellspacing="0" cellpadding="2"
						bordercolor="#FFFFFF" bordercolordark="#F2F2F2">
						<tr>  
						  <td width="5%" align="left"> 
						     <bean:message key="open.excel" />
						  </td>
						  <td width="20%" align="left" >
						       <input name="filename" size="50" type="file">
						   </td>
						 
						</tr>
						<tr>
						   <td width="25%" align="center" colspan="2" >
						   <input type="button" name="button" class="button_nor" value='<bean:message key="button.addimp"/>' onclick="uploadExcel('add')">
						    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
						   <input type="button" name="button" class="button_nor" value='<bean:message key="button.delimp"/>' onclick="uploadExcel('del')">
						   </td>
						 
						    
						</tr>
					</table>
			</td>
	</tr>    
   </tr>
 </table>
 <%%>
 <table width="800" border="0" align="center" cellpadding="0"	cellspacing="0">
     
  </table>		
</form>
</body>
</html>
<script>
   function uploadExcel(str){
    var upload = document.FindExcelForm.filename.value;
    var ext=upload.substring(upload.lastIndexOf(".")+1,upload.length);
    if(document.FindExcelForm.filename.value==""){
       alert("没有选择Excel文件");
       return false;
    }
    if(ext!="xls"){
		alert("你打开的文件不是Excel文件");
		return false;
	}	 
	 if(str=='add'){
             if(confirm("此操作将在已导入的与会名单基础上增加名单，确定要导入？"))
                {}
             else
                 return;
     }
     if(str=='del'){
             if(confirm("此操作将删除已导入的与会名单，确定要导入？"))
                {}
             else
                 return;
     }
     
	 document.FindExcelForm.action="upload.jsp?cmd="+str;
     document.FindExcelForm.submit();
   }
   function DoExportModel(){
     document.modelForm.submit();
   }
</script>
