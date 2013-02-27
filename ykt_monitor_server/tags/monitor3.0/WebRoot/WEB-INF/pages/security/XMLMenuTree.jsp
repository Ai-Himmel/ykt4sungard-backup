<%@ page language="java" import="java.util.*" pageEncoding="UTF-8"%>
<%String path = request.getContextPath();
			String basePath = request.getScheme() + "://"
					+ request.getServerName() + ":" + request.getServerPort()
					+ path + "/";

			%>
<%String menuTree = (String) request.getAttribute("menuTree");
			request.setCharacterEncoding("GBK");
            
			response.setContentType("text/html; charset=GBK");
//response.reset();
//			response.getOutputStream().write(menuTree.getBytes());
			//response.getOutputStream().close();
out.println(menuTree);
		%>
