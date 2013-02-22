<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%> 
 
 导入成功！导入文件信息如下：
<p>
<b>The File name:</b> <%= request.getAttribute("fileName") %>
</p>
<p>
<b>The File content type:</b> <%= request.getAttribute("contentType") %>
</p>
<p>
<b>The File size:</b> <%= request.getAttribute("size") %>
</p>
<hr />
<hr />
