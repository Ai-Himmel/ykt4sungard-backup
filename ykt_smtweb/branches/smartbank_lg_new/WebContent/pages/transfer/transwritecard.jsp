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
		<title>ת��д��</title>
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
		   //System.out.println("--����--"+cardno);
		   //System.out.println("--д�����--"+writecardmoney);
		  // System.out.println("--���״���--"+cxCnt);
		  // System.out.println("--ת�ʽ��--"+transmoney);
		  // System.out.println("--��ȡ����--"+feemoney);
		  // System.out.println("--�����--"+showmoney);
		 //  System.out.println("--��ˮ��--"+SerialNo);
		//   System.out.println("--�豸id--"+deviceId);
		  
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
				
				//д���ɹ������ɹ�ҳ��
				msg.innerHTML="<b>ת�˳ɹ�<br><br>ת�ʽ��:"+<%=transmoney%>+"Ԫ<br><br>��ȡ����:"
				              +<%=feemoney%>+"Ԫ<br><br>�����:"+<%=showmoney%>+"Ԫ"
				              +"<br><br>��'����'�˳�ϵͳ</b>";
				              
			}else{
	
			    if(str==1){//��2�β�д��ʧ�ܣ����������Ĵ���
			    	
			    	window.location="<%=path%>/writecardfail.do?SerialNo="+<%=SerialNo%>+"&deviceId="+<%=deviceId%>;
			    	
			    }
				//ת�˳ɹ�д��ʧ��
				
				msg.innerHTML="<b>ת�˳ɹ���д��ʧ�ܣ��밴'ȷ��',��д��</b>";
				
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
										<td height="320" align="center" class="��ʽ13" id="msg">
										  <b>	 ����д���У��벻Ҫ�ƶ�У԰��</b>
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

