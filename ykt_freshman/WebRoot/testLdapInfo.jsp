<%@ page language="java" contentType="text/html; charset=GB2312" pageEncoding="GBK" 
import="com.wiscom.is.*, java.net.* ,org.king.security.util.*"%>
<HTML>
<HEAD>
<TITLE>测试统一身份的用户属性</TITLE>
</HEAD>

<%
     //String is_config=application.getRealPath("/client.properties");
		
	String configFile = request.getSession().getServletContext().getInitParameter("configFile");
		
		LdapFromSunDS ldap = new LdapFromSunDS();
		
		ldap.init("");
		
		
	String is_config = ldap.getPreference("constant.ldap.path")+"/client.properties";
		
   out.println("is_config = "+is_config+"<br>");

     Cookie all_cookies[] = request.getCookies();
     Cookie myCookie;
				String decodedCookieValue = null;
				if (all_cookies != null) {
					for (int i = 0; i < all_cookies.length; i++) {
						myCookie = all_cookies[i];
						if (myCookie.getName().equals("iPlanetDirectoryPro")) {
							decodedCookieValue = URLDecoder.decode(myCookie
									.getValue(), "GB2312");
						}
					}
				}


				IdentityFactory factory = IdentityFactory
						.createFactory(is_config);
				IdentityManager im = factory.getIdentityManager();
                String userName = im.getUserNameByID("04534");
               System.out.println("userName="+userName);
                String uid = "";
                String type = "";
                String cn = "";
                String sex = "";
                String org = "";
                String aff = "";
                String [] types = im.getUserAttribute("04534","UID");
                if(types!=null){
                     uid = types[0];
                }
                
               // types = im.getUserAttribute("04534","CN");
               // if(types!=null){
               //      cn = types[0];
               // }
                
                 //  String dn = "";
	             //   String[] dns = im.getUserAttribute("111","DN");
	             //   dn = dns[0];
	                
	                
	             //   String [] result = dn.split(",");
	                
	             //   type = result[1].substring(3);

	                
	         
	              //  org = result[2].substring(2);

                
           //     types = im.getUserAttribute("04534","ou");
            //    if(types!=null){
            //         type = types[0];
            //    }
                
                
                types = im.getUserAttribute("06076","eduPersonSex");
                if(types!=null&&types.length!=0){
                     aff = types[0];
                }
                
                
                

%>

姓名:<%=userName%><br>

uid:<%=uid%><br>

 cn: = <%=cn%><br>
 type: = <%=type%><br>
 
 sex: = <%=sex%><br>
 org: = <%=org%><br>
 aff: = <%=aff%><br>

