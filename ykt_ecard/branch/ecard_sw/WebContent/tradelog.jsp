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
<html>
<head>
<title>Welcome to 51Timing</title>
<meta HTTP-EQUIV="Window-target" content="_top" />
<meta HTTP-EQUIV="pragma" content="no-cache" />
<meta HTTP-EQUIV="Cache-Control" content="no-cache, must-revalidate" />
<meta HTTP-EQUIV="expires" content="Wed, 26 Feb 1997 08:21:57 GMT" />
<meta HTTP-EQUIV="Content-Type" content="text/html; charset=UTF-8" />
<meta name="robots" content="all" />
<meta name="keywords" content="微博,sina,timing,定时器" />
<meta name="description" content="微博,sina,timing,定时器" />
<link href="/css/app.css" rel="stylesheet" type="text/css" />

</head>

<body>
<table border="1" cellpadding="0" cellspacing="0" width="95%">
	<tr>
		<th>交易地点</th>
		<th>交易时间</th>
		<th>交易金额</th>
		<th>账户余额</th>
	</tr>

<%
    String stuempNo = request.getParameter("stuempno");
    List list = new ArrayList();

    double cardbala = 0;
    int count = 0;
    
            Context ctx = null;
            Connection conn = null;
            ResultSet rs = null;
            Statement stmt = null;
            try {
                ctx = new InitialContext();
                DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/LiferayPool");
                conn = ds.getConnection();
                stmt = conn.createStatement();
                String nSql = "	select * from " 
					+ " (select nvl(t2.dict_caption,' ') as dict_caption,substr(t1.tx_date,1,4)||'-'||substr(t1.tx_date,5,2)||'-'||substr(t1.tx_date,7,2)||' '||substr(t1.tx_time,1,2)||':'||substr(t1.tx_time,3,2)||':'||substr(t1.tx_time,5,2) as optime,"
					+ " t1.amount/100 as opfee,out_bala/100 as opbala,t1.total_cnt"
					+ " from ykt_cur.t_tif_rcvdtl t1 left join "
					+ " (select a1.devphy999_id,a1.device_name as dict_caption from ykt_cur.t_pif_device a1 left join ykt_cur.t_pif_dictionary a2 on a1.area=a2.dict_value and a2.dict_no=37) t2"
					+ " on t1.device_id=t2.devphy999_id"
					+ " where t1.card_no=(select c1.card_id from t_pif_card c1 left join t_cif_customer c2 on c1.cosumer_id=c2.cut_id"
					+ " where c1.state_id=1000 and c2.stuemp_no='"+ stuempNo +"') and t1.tx_code=930031 order by t1.total_cnt desc) s1 "
					+ " where rownum<=6 order by total_cnt desc"
				;
                rs = stmt.executeQuery(nSql);
                if (rs != null) {
                    while (rs.next()) {
                        out.println("<tr>");
                        out.println("<td>");
                        out.println(rs.getString(1));
                        out.println("</td>");

                        out.println("<td>");
                        out.println(rs.getString(2));
                        out.println("</td>");

                        out.println("<td>");
                        out.println(rs.getString(3));
                        out.println("</td>");

                        out.println("<td>");
                        out.println(rs.getString(4));
                        out.println("</td>");
						
                        out.println("</tr>");
                    }
                }
                rs.close();
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
        
     
%>
    <tr>
        <td valign="top">
        </td>
    </tr>
</table>

</body>
</html>