<%@ page import = "java.io.*"%>
<%@ page import="java.sql.*"%>
<%@ page import="com.ekingstar.zcgl.bean.*"%>
<%@ page import="sun.jdbc.rowset.CachedRowSet"%>
<%
if(true){
	String uid=(String)session.getAttribute("userId");
	if (uid==null || "".equals(uid) || uid=="" || uid.equals("null")){
		//���SESSION��û��ֵ�����ж��Ƿ��Ǵ��Ż���½
		String id = request.getParameter("id");
		String authcode = request.getParameter("authcode");
		String md5str = "";
		if (!(id==null || "".equals(id))){
			id=id+"zcglneusoft2008";
			//******���²��ֶ�id����MD5����*******
			char hexDigits[] = {       // �������ֽ�ת���� 16 ���Ʊ�ʾ���ַ�
				 '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd',  'e', 'f'}; 
			try{
				java.security.MessageDigest md = java.security.MessageDigest.getInstance( "MD5" );
				md.update(id.getBytes());
				byte tmp[] = md.digest();          // MD5 �ļ�������һ�� 128 λ�ĳ�������
															// ���ֽڱ�ʾ���� 16 ���ֽ�
				char str[] = new char[16 * 2];   // ÿ���ֽ��� 16 ���Ʊ�ʾ�Ļ���ʹ�������ַ���
															 // ���Ա�ʾ�� 16 ������Ҫ 32 ���ַ�
				int k = 0;                                // ��ʾת������ж�Ӧ���ַ�λ��
				for (int i = 0; i < 16; i++) {          // �ӵ�һ���ֽڿ�ʼ���� MD5 ��ÿһ���ֽ�
															 // ת���� 16 �����ַ���ת��
					byte byte0 = tmp[i];                 // ȡ�� i ���ֽ�
					str[k++] = hexDigits[byte0 >>> 4 & 0xf];  // ȡ�ֽ��и� 4 λ������ת��, 
																		 // >>> Ϊ�߼����ƣ�������λһ������
					str[k++] = hexDigits[byte0 & 0xf];            // ȡ�ֽ��е� 4 λ������ת��
				} 
				md5str = new String(str);                                 // ����Ľ��ת��Ϊ�ַ���
			}catch( Exception e ){
				e.printStackTrace();
			}

			//******���²��ֶ�MD5���ܺ���ַ������д���ȡ����ĳһ����*******
			if (md5str.length() >= 30){
				md5str = md5str.substring(8,12)+md5str.substring(20,29)+md5str.substring(1,5)+md5str.substring(15,19);
			}
		}
		if (id==null || "".equals(id) || !md5str.equals(authcode)){
			//�Ż���֤ʧ��
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
				session.setMaxInactiveInterval(7200); //SESSIONʧЧʱ��Ϊ2Сʱ
				session.setAttribute("userId",uid_zc);	
				session.setAttribute("userGroupId", rs.getString("yhzbh"));
				session.setAttribute("departmentId", rs.getString("bmbh"));
				session.setAttribute("userName", rs.getString("xm")); 			
				com.ekingstar.zcgl.bean.Common cm =new com.ekingstar.zcgl.bean.Common();
				session.setAttribute("dbtype",cm.getProValue("DBTYPE"));

				//��ѯ�û�����Ȩ��
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
				//�ʲ�ϵͳ���ݿ����޸��û�
				String URI=request.getRequestURI();
				String project = URI.split("/")[1];
				response.sendRedirect("/"+project+"/login.jsp");
			}
		}
	}
}
%> 
