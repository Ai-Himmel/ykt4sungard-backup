<%@ page language="java" import="javax.naming.Context" %>
<%@ page import="javax.naming.InitialContext" %>
<%@ page import="javax.sql.DataSource" %>
<%@ page import="java.sql.Connection" %>
<%@ page import="java.sql.ResultSet" %>
<%@ page import="java.sql.Statement" %>
<%@ page pageEncoding="UTF-8" %>

<table border="0" cellpadding="0" cellspacing="0" width="95%">
    <tr>
        <td valign="top">
            <%
				String advqueryRealURL ="http://172.20.32.7:8080" + "/advquery/usermanage/login.do"; //advquery real http path
                String stuempNo = request.getParameter("un");
                String authcode = request.getParameter("verify");
                String md5str = "";
                String displayString ="";

                if (stuempNo != null && !"".equals(stuempNo) && !"null".equals(stuempNo)) {
                    char hexDigits[] = {
                            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
                    try {
                        String eid= stuempNo + "shouecard2010ldcx";
                        java.security.MessageDigest md = java.security.MessageDigest.getInstance("MD5");
                        md.update(eid.getBytes());
                        byte tmp[] = md.digest();
                        char str[] = new char[16 * 2];
                        int k = 0;
                        for (int i = 0; i < 16; i++) {
                            byte byte0 = tmp[i];
                            str[k++] = hexDigits[byte0 >>> 4 & 0xf];
                            str[k++] = hexDigits[byte0 & 0xf];
                        }
                        md5str = new String(str);
                    } catch (Exception e) {
                        System.out.println(e);
                    }
                    if (md5str.length() >= 30) {
                        //md5str = md5str.substring(8, 12) + md5str.substring(20, 29) + md5str.substring(1, 5) + md5str.substring(15, 19);
                    }

                    if (md5str.equals(authcode)) {
                        Context ctx = null;
                        Connection conn = null;
                        ResultSet rs = null;
                        Statement stmt = null;
                        try {
                            ctx = new InitialContext();
                            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/advquery");
                            conn = ds.getConnection();
							stmt = conn.createStatement();
							String nSql = "select count(*) totalCount from ykt_query.T_LEADQUERY_OPERATOR where upper(oper_code)='" + stuempNo.toUpperCase() + "'";
							rs = stmt.executeQuery(nSql);
                            int rowCount = 0; 
                            if(rs.next()) {
                                rowCount=rs.getInt("totalCount");
                            } 
							//rs.close();
                            if (rowCount >0) {
                                session.setAttribute("username", stuempNo);
                                response.sendRedirect(advqueryRealURL);
                                //displayString = "<a href='"+advqueryRealURL+"'>欢迎进入一卡通系统</a>";
                            }else{
                                displayString = "未找到此用户";
                            }
                        } catch (Exception e) {
                            System.out.println(e);
                            e.printStackTrace();
                        }
                        finally {
                            if (rs != null)
                                rs.close();
                            if (stmt != null)
                                stmt.close();
                            if (conn != null)
                                conn.close();
                            if (ctx != null)
                                ctx.close();
                        }
                    }else{
                        displayString = "身份验证失败";
                    }
                }else{
                    displayString = "未登录";
                }
            %>
        </td>
    </tr>
    <tr>
        <td>
            <%=displayString%>
        </td>
    </tr>
</table>