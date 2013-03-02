<%@ page import = "java.io.*"%>
<%@ page import="java.sql.*"%>
<%@ page import="com.ekingstar.zcgl.bean.*"%>
<%@ page import="sun.jdbc.rowset.CachedRowSet"%>
<%
if(true){
	String uid=(String)session.getAttribute("userId");
	if (uid==null || "".equals(uid) || uid=="" || uid.equals("null")){
		//如果SESSION里没有值，则判断是否是从门户登陆
		String id = request.getParameter("id");
		String authcode = request.getParameter("authcode");
		String md5str = "";
		if (!(id==null || "".equals(id))){
			id=id+"zcglneusoft2008";
			//******以下部分对id进行MD5加密*******
			char hexDigits[] = {       // 用来将字节转换成 16 进制表示的字符
				 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd',  'e', 'f'}; 
			try{
				java.security.MessageDigest md = java.security.MessageDigest.getInstance( "MD5" );
				md.update(id.getBytes());
				byte tmp[] = md.digest();          // MD5 的计算结果是一个 128 位的长整数，
															// 用字节表示就是 16 个字节
				char str[] = new char[16 * 2];   // 每个字节用 16 进制表示的话，使用两个字符，
															 // 所以表示成 16 进制需要 32 个字符
				int k = 0;                                // 表示转换结果中对应的字符位置
				for (int i = 0; i < 16; i++) {          // 从第一个字节开始，对 MD5 的每一个字节
															 // 转换成 16 进制字符的转换
					byte byte0 = tmp[i];                 // 取第 i 个字节
					str[k++] = hexDigits[byte0 >>> 4 & 0xf];  // 取字节中高 4 位的数字转换, 
																		 // >>> 为逻辑右移，将符号位一起右移
					str[k++] = hexDigits[byte0 & 0xf];            // 取字节中低 4 位的数字转换
				} 
				md5str = new String(str);                                 // 换后的结果转换为字符串
			}catch( Exception e ){
				e.printStackTrace();
			}

			//******以下部分对MD5加密后的字符串进行处理，取其中某一部分*******
			if (md5str.length() >= 30){
				md5str = md5str.substring(8,12)+md5str.substring(20,29)+md5str.substring(1,5)+md5str.substring(15,19);
			}
		}
		if (id==null || "".equals(id) || !md5str.equals(authcode)){
			//门户验证失败
			String URI=request.getRequestURI();
			String project = URI.split("/")[1];
			response.sendRedirect("/"+project+"/login.jsp");
		}else{	
			SQLDirect sdj10 = new SQLDirect();
			String uid_zc=request.getParameter("id");
			String str = "select * from ZC_YH WHERE YHBH= '"+uid_zc+"' and sfsy=1";
			CachedRowSet rs=sdj10.exeQuery(str);
			if(rs.next()){
				//sftz=true;
				session.setMaxInactiveInterval(7200); //SESSION失效时间为2小时
				session.setAttribute("userId",uid_zc);	
				session.setAttribute("userGroupId", rs.getString("yhzbh"));
				session.setAttribute("departmentId", rs.getString("bmbh"));
				session.setAttribute("userName", rs.getString("xm")); 			
				com.ekingstar.zcgl.bean.Common cm =new com.ekingstar.zcgl.bean.Common();
				session.setAttribute("dbtype",cm.getProValue("DBTYPE"));

				//查询用户部门权限
				String sql = "select bmbh from zc_yhbmqx where yhbh='"+uid_zc+"'";
				rs = sdj10.exeQuery(sql);
				String yhbmqx = "";
				while(rs.next()){
					yhbmqx = yhbmqx+rs.getString("BMBH")+"%,";
				}
				rs.close();
				if(yhbmqx.length()>0){
					yhbmqx = yhbmqx.substring(0,yhbmqx.length()-1);
				}
				session.setAttribute("yhbmqx",yhbmqx);
				response.sendRedirect("index.jsp");		
			}else{
				//资产系统数据库里无该用户
				String URI=request.getRequestURI();
				String project = URI.split("/")[1];
				response.sendRedirect("/"+project+"/login.jsp");
			}
		}
	}
}
%> 
