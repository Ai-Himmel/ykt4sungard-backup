<%@ include file="/html/commons/init.jsp"%>
<%@ page import="java.io.*"%>
<%@ page import="java.util.*"%>
<%@ page import="javazoom.upload.*"%>
<%@ page import="uploadutilities.FileMover"%>
<%@ page import="java.text.SimpleDateFormat"%>
<%@ page import="com.kingstargroup.conference.util.ExcelReader"%>
<%@ taglib uri="/WEB-INF/extremecomponents.tld" prefix="ec"%>
<%@ page import="com.kingstargroup.conference.common.GetPropertiesUtil" %>
<%@ page import="com.kingstargroup.conference.util.ConferenceUtil" %>
<%@ page import="org.apache.commons.configuration.PropertiesConfiguration"%>
<%@ page import="com.kingstargroup.conference.action.nocardimp.NoCardConstant"%>
<%@ page import="com.kingstargroup.conference.util.*"%>
<%@ page language="java" pageEncoding="UTF-8"%>
  
<%  
	request.setCharacterEncoding("UTF-8");//设置编码格式，就不用一个个转码了。
    FileMover fileMover = new FileMover();//你也可以使用自带的实例中jsp:useBean的形式。
    PropertiesConfiguration configs = GetPropertiesUtil.getInstance();
	String uploadpath = configs.getString("upload");
    MultipartFormDataRequest mrequest = null;
    Hashtable files = null;
    String cmd = request.getParameter("cmd");
    if(MultipartFormDataRequest.isMultipartFormData(request)){
      try{
		    mrequest = new MultipartFormDataRequest(request,null,10*1024*1024,MultipartFormDataRequest.COSPARSER,"UTF-8");//注意这里也要设置编码参数
		    files = mrequest.getFiles();
      }catch(IOException e){
%>
<script language="javascript">
    alert("请上传小于10M的文件");
    history.back(-1);
</script>
<%
      }
  	}
    String sServerFileName="";
	if (files != null && !files.isEmpty()) {
	           
				UploadFile file = null;
					file = (UploadFile) files.get("filename");
				UploadBean upBean = new UploadBean();
				java.util.Date dt = new java.util.Date(System
						.currentTimeMillis());
				SimpleDateFormat fmt = new SimpleDateFormat("yyyyMMddHHmmssSSS");
				 sServerFileName = fmt.format(dt);
				upBean.setFolderstore(uploadpath);
				upBean.addUploadListener(fileMover);
				fileMover.setNewfilename(sServerFileName);
				upBean.store(mrequest, "filename");
				
    }  
     File f = new File(uploadpath+sServerFileName);
     if (f.exists()) {
     %>
     <html>
      <form   name="ImpDateForm"  method="post" action="<%=ContextUtil.getCtxPath(request)%>/ImpData.do"  >
           <input type="hidden" name="servrfileName" value="<%=uploadpath+sServerFileName%>">
           <input type="hidden" name="cmd" value="<%=cmd%>">
     </form>
     </html>
     <script> 
        document.ImpDateForm.submit();
     </script>
     <%
     }else{
       %>
       <script> 
         alert("上传excel文件失败");
         history.back(-1);
        </script>
       <%
     }
%>   
   

