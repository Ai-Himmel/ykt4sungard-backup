<%@ page language="java" import="javax.naming.Context" %>
<%@ page import="javax.naming.InitialContext" %>
<%@ page import="javax.sql.DataSource" %>
<%@ page import="java.sql.Connection" %>
<%@ page import="java.sql.ResultSet" %>
<%@ page import="java.sql.Statement" %>
<%@ page import="java.util.ArrayList" %>
<%@ page import="java.util.HashMap" %>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Map" %>
<%@ page pageEncoding="UTF-8" %>
<%
    String stuempNo = request.getParameter("shmtu");
    String authcode = request.getParameter("authcode");
    String md5str = "";
    String displayString = "身份验证失败";
    List list = new ArrayList();

    double cardbala = 0;
    int count = 0;
    if (stuempNo != null && !"".equals(stuempNo) && !"null".equals(stuempNo)) {
        char hexDigits[] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        try {
            String eid = stuempNo + "shmaritimeecard";
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
            e.printStackTrace();
        }
        if (md5str.length() >= 30) {
            md5str = md5str.substring(9, 13) + md5str.substring(18, 29) + md5str.substring(1, 4) + md5str.substring(10, 19);
        }

        if (md5str.equals(authcode)) {
            Context ctx = null;
            Connection conn = null;
            ResultSet rs = null;
            Statement stmt = null;
            try {
                ctx = new InitialContext();
                DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/LiferayPool");
                conn = ds.getConnection();
                stmt = conn.createStatement();
                String nSql = "select CARD_BALANCE from YKT_CUR.T_AIF_ACCOUNT where current_state='1' and STUEMP_NO='" + stuempNo + "'";
                rs = stmt.executeQuery(nSql);
                if (rs.next()) {
                    cardbala = rs.getDouble("CARD_BALANCE");
                }
                rs.close();
                nSql = "select att.cust_id, cust.cut_name,cust.stuemp_no, att.att_date,count(*) attnum  " +
                        "  from v_att_date att left join ykt_cur.t_cif_customer cust on att.cust_id=cust.cut_id  " +
                        "where cust.stuemp_no='" + stuempNo + "' and substr(att.att_date,1,6) =to_char(sysdate,'yyyymm')  " +
                        "group by att.cust_id, cust.cut_name,cust.stuemp_no, att.att_date order by att.att_date ";
                rs = stmt.executeQuery(nSql);
                if (rs != null) {
                    while (rs.next()) {
                        Map m = new HashMap();
                        m.put("num", rs.getString("attnum"));
                        m.put("txdate", rs.getString("att_date"));
                        list.add(m);
                    }
                }
                count = list.size();
                rs.close();
                displayString = "<a href=\"javascript:goOK()\"><font size=\"2\">欢迎进入一卡通系统" + "</font></a>";
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
        } else {
            displayString = "身份验证失败";
        }
    } else {
        displayString = "未登录";
    }
%>
<table border="0" cellpadding="0" cellspacing="0" width="95%">
    <tr>
        <td valign="top">
            <font class="gamma" size="2">  
			<b>卡内余额：<%=String.valueOf(cardbala) %>元</b><br/>
			<!--
			<span title="<%
                    if (list!=null&&list.size()>0){
	                    for(int i=0;i<list.size();i++){
		                    Map m=new HashMap();
		                    m=(Map)list.get(i);
		                    String tmpDate=(String)m.get("txdate");
                    %>
<%=tmpDate.substring(0,4)%>-<%=tmpDate.substring(4,6)%>-<%=tmpDate.substring(6,8)%> <%=m.get("num")%>次 <%  }   }  %>  ">

                    
                    <b>本月实际考勤刷卡天数：<%=String.valueOf(count) %>次</b>
                    
                </span>
				-->
            </font>
        </td>
    </tr>
    <tr>
        <td><img border="0" src="ahu.jpg" width="33" height="33" align="absmiddle">
            <%=displayString%>
        </td>
</table>
<form name="ssoForm" action="http://ecard.shmtu.edu.cn/c/portal/layout" method="post" target="_blank">
    <input type=hidden name="p_l_id" value="1">
    <input type=hidden name="shmtu" value="<%=stuempNo%>">
</form>
<script language="javascript">
    function goOK() {
        ssoForm.submit();
    }
    function Click() {
        if (event.button == 2) {
            alert('SunGard版权所有');
        }
    }
    document.onmousedown = Click
</script>
