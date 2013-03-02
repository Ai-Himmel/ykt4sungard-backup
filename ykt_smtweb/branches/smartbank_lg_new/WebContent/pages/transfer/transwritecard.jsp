<%@ page contentType="text/html;charset=GBK"%>
<%@ page import="com.kingstargroup.fdykt.KSConfiguration" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean"%>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html"%>
<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic"%>
<%@ page language="java" import="javax.naming.Context" %>
<%@ page import="javax.naming.InitialContext" %>
<%@ page import="javax.sql.DataSource" %>
<%@ page import="java.sql.Connection" %>
<%@ page import="java.sql.ResultSet" %>
<%@ page import="java.sql.Statement" %>
<%@ page import="com.kingstargroup.fdykt.dao.DB2ActionDAO" %>
<%@ page import="com.kingstargroup.fdykt.util.DateUtil" %>
<%@ page import="java.sql.PreparedStatement"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<%@ include  file="/pages/init.jsp"%><script language="javascript" src="<%=path%>/pages/js/other.js"></script><html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>转账写卡</title>
		<link href="<%=path%>/pages/css/css.css" rel="stylesheet" type="text/css" />		
		<%
		   String cardno =request.getAttribute("cardno").toString();
		   String cardId =request.getAttribute("cardId").toString();
		   String writecardmoney = request.getAttribute("writecardmoney").toString();
		   String showmoney = request.getAttribute("showmoney").toString();
		   String cxCnt = request.getAttribute("cxCnt").toString();
		   String transmoney = request.getAttribute("transmoney").toString();
		   String feemoney = request.getAttribute("feemoney").toString();
		   String SerialNo = request.getAttribute("SerialNo").toString();
		   String deviceId = request.getAttribute("deviceId").toString();
		   //System.out.println("--卡号--"+cardno);
		   //System.out.println("--写卡金额--"+writecardmoney);
		  // System.out.println("--交易次数--"+cxCnt);
		  // System.out.println("--转帐金额--"+transmoney);
		  // System.out.println("--收取搭伙费--"+feemoney);
		  // System.out.println("--卡余额--"+showmoney);
		 //  System.out.println("--流水号--"+SerialNo);
		//   System.out.println("--设备id--"+deviceId);
		  
		   String idvalue="0";
		   Context ctx = null;
           Connection conn = null;
           ResultSet rs = null;
           PreparedStatement stmt = null;
		   // insert into log  ,creattime ,updatetime ,state
		     try {
                         ctx = new InitialContext();
                         DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/db2inst4");
                         conn = ds.getConnection();

                          StringBuffer sql =new StringBuffer();
                         
                          sql.append( " SELECT nextVAL FOR cardwebseq  as  id FROM ykt_cur.cardweblog   ");
                          stmt = conn.prepareStatement(sql.toString());
                          rs = stmt.executeQuery();
                          if(rs.next()) {
                          idvalue = rs.getString("id");
                          }
                          
                          StringBuffer sql2 = new StringBuffer();
                          sql2.append(" insert into ykt_cur.cardweblog  (id,cardno,writecardmoney,deviceid,createtime,state,transmoney,writecount ) ")
                              .append(" values(").append(idvalue).append(",'").append(cardId).append("','").append(writecardmoney).append("','")
                              .append(deviceId).append("','").append(DateUtil.getNow()).append("','1'")
                              .append(",'").append(transmoney).append("','").append(cxCnt).append("')");
                          
                          stmt = conn.prepareStatement(sql2.toString());
			              stmt.execute();
                           
			}catch (Exception e) {
                            System.out.println(e);
                            e.printStackTrace();
            } finally {
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
	<script language="javascript">
		   
		function writeCard(str){		
			
			document.getElementById("send").style.display='none';
	
			var serverbase = "http://"+"<%=webserverip%>"+":"+"<%=webserverport%>"+"/"+"<%=webserverapp%>"+"/";
			var device_port = '<%=read_card_device_port%>';
			document.all.RFScanner.PortNo=device_port;
			ret = document.all.RFScanner.CardTransWriteCard(<%=writecardmoney%>,<%=cardno%>,<%=cxCnt%>);
			if(ret ==0){
				
				//写卡成功，到成功页面
				msg.innerHTML="<b>转账成功<br><br>转帐金额:"+<%=transmoney%>+"元<br><br>收取搭伙费:"
				              +<%=feemoney%>+"元<br><br>卡余额:"+<%=showmoney%>+"元"
				              +"<br><br>按'返回'退出系统</b>";
				              
			}else{
	
			    if(str==1){//第2次补写卡失败，到卡务中心处理。
			    	
			    	window.location="<%=path%>/writecardfail.do?SerialNo="+<%=SerialNo%>+"&deviceId="+<%=deviceId%>;
			    	
			    }
				//转账成功写卡失败
				
				msg.innerHTML="<b>转账成功但写卡失败，请按'确定',重写卡</b>";
				
				document.getElementById("send").style.display='';
			}
			
		}
		
	</script>
	
	</head>
	<body scroll="no" onload="writeCard('0')" onkeydown="return (event.keyCode!=8)">
	<form name="returnform">
	  <div id="mid_top"></div>
			<div id="middle">
				<div id="Layer1">
					<div id="content">
						<div id="content_left"></div>
						<div id="content_middle">
							<div align="center">
								<img src="<%=path%>/pages/images/czjg.gif" width="314"
								height="82" />
							</div>
							<div id="content_input">
								<table width="50%" border="0" align="center" cellpadding="0"
									cellspacing="0" class="box">
									<tr>
										<td height="320" align="center" class="样式13" id="msg">
										  <b>	 正在写卡中，请不要移动校园卡</b>
										</td>
									</tr>

								</table>
							</div>
							<div id="content_buttom">
								<table>
									<tr>
								<td align="left" width="200">
								    <a onclick="writeCard('1')" 
												onmouseup="MM_swapImgRestore()"
												onmousedown="MM_swapImage('send','','<%=path%>/pages/images/senda.gif',1)"><img
													src="<%=path%>/pages/images/send.gif" name="send"
													width="109" height="48" border="0" id="send" /> </a>
						           </td>
										<td align="center">
											<a
												onclick="javascript: window.location='<%=path%>/index.do';"
												onmouseout="MM_swapImgRestore()"
												onmouseover="MM_swapImage('back','','<%=path%>/pages/images/backa.gif',1)"><img
													src="<%=path%>/pages/images/back.gif" name="back"
													width="109" height="48" border="0" id="back" /> </a>
										</td>
									</tr>
								</table>
							</div>
						</div>
						<div id="content_right"></div>
					</div>
				</div>
			</div>
			<div id="bottom"></div>
			<object id="RFScanner"
				classid="clsid:{335AEB92-0D39-4999-A2B5-536A2C718901}" width="0"
				height="0" codebase="<%=path%>/rf35.cab#version=2,0,0,7" />
				
				<%
				  try {
                         ctx = new InitialContext();
                         DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/db2inst4");
                         conn = ds.getConnection();

                          StringBuffer sql3 = new StringBuffer();
			              sql3.append(" update ykt_cur.cardweblog set state='2',updatetime='").append(DateUtil.getNow()).append("'")
			                  .append(" where id=").append(idvalue);
			                  
                          stmt = conn.prepareStatement(sql3.toString());
			              stmt.execute();
                           
			}catch (Exception e) {
                            System.out.println(e);
                            e.printStackTrace();
            } finally {
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
		</form>
	</body>
</html>

