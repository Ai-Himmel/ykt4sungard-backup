<%@ include file="../tiles/include.jsp"%>
<%@ page import="java.io.*"%>
<%
   byte[] picture = (byte[]) request.getAttribute("picture");
			response.setContentType("image/gif");
			try {
			OutputStream o = response.getOutputStream();
			o.write(picture);
			o.flush();
			o.close();
           }catch(Exception e){
           }
		%>
