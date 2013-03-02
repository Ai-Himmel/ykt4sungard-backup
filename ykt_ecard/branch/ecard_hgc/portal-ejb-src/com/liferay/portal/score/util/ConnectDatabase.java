package com.liferay.portal.score.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.apache.log4j.Logger;
import org.apache.struts.util.LabelValueBean;



public class ConnectDatabase {
	
	
	
	private   Connection  getConnect() {
		
		Connection con = null;
		try {
			Class.forName("oracle.jdbc.driver.OracleDriver");
			con = DriverManager.getConnection(
					url, username, passwd);
			
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
			logger.error("--------装载驱动异常!-----------");
		} catch (SQLException e) {
			logger.error("----------链接教务数据库异常!--------");
			e.printStackTrace();
		}
		return con;
	}
	
	private static ResultSet getSourceData(String sql, Statement statement) {
		ResultSet resultSet = null;

		try {
			resultSet = statement.executeQuery(sql);
		} catch (SQLException e) {
			logger.error("----查询数据异常!-----");
			e.printStackTrace();
		}
		return resultSet;
	}
	
	public List  getStudentYear(String studentno){
		ResultSet resultSet=null;
		try{
		String sql =" select distinct(FIRSTYEAR) as FIRSTYEAR from  ykt.view_ykt_score where studentno=?";
		PreparedStatement ps =conn.prepareStatement(sql);
		ps.setString(1, studentno);
		resultSet = ps.executeQuery();
		ArrayList stuyear = new ArrayList();
		while(resultSet.next()){
			String  firstyear   = String.valueOf(resultSet.getInt("FIRSTYEAR"));
			String  view = firstyear+"--"+(Integer.parseInt(firstyear)+1);
			LabelValueBean   label   =   new   LabelValueBean(view,firstyear);
			stuyear.add(label);	
		}
		return stuyear;
		}catch (Exception e) {
			logger.error("--查询教务数据库失败--学生年份--");
			e.printStackTrace();
			return null;
		}finally {
			try {
				if(resultSet != null){
					resultSet.close();
				}
			/*	if(statement !=null){
					statement.close();
				}*/
				if (conn != null) {
					conn.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
		
	}
	
	

	/*public   List getStudentScore(String studentno) {
	      ResultSet resultSet=null;
		try {
			statement =conn.createStatement();
			ArrayList  scoreList = new ArrayList();

			String sql = " select MAJORNAME,CLASSNAME ,FIRSTYEAR,ENDYEAR,TERMNO,COURSENAME,TOTALSCORENAME"
					    +" from  ykt.view_ykt_score  where studentno=?";
			String sql = " select * "
			    +" from  ykt.view_ykt_score  where studentno='"
			    + studentno  
			    + "'";
		    //logger.info(sql);
		    //resultSet = getSourceData(sql,statement);
			
			PreparedStatement ps =conn.prepareStatement(sql);
			ps.setString(1, studentno);
			resultSet = ps.executeQuery();
				
			while(resultSet.next()){	    
				Score score = new Score();
				score.setMajorName(resultSet.getString("MAJORNAME"));
				score.setClassName(resultSet.getString("CLASSNAME"));
				score.setFirstYear(resultSet.getString("FIRSTYEAR"));
				score.setEndYear(resultSet.getString("ENDYEAR"));
				score.setTermNo(resultSet.getString("TERMNO"));
				score.setCourseName(resultSet.getString("COURSENAME"));
				score.setTotalScoreName(resultSet.getString("TOTALSCORENAME"));
				scoreList.add(score);
			}
			return scoreList;
		} catch (Exception e) {
			logger.error("查询教务数据库失败");
			e.printStackTrace();
			return null;
		}finally {
			try {
				if(resultSet != null){
					resultSet.close();
				}
				if(statement !=null){
					statement.close();
				}
				if (conn != null) {
					conn.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}*/
	
	public   List getStudentScore(String studentno,String firstYear,String termNo) {
	      ResultSet resultSet=null;
	      ArrayList  scoreList = new ArrayList();
		try {
			if(firstYear!=null ){
		//	statement =conn.createStatement();
            StringBuffer sql= new StringBuffer("");
			   sql.append(" select MAJORNAME,CLASSNAME ,FIRSTYEAR,ENDYEAR,TERMNO,COURSENAME,TOTALSCORENAME")
				  .append(" from  ykt.view_ykt_score  " )
				  .append(" where studentno=? " );
			   if(!"".equals(firstYear)){
				   sql.append(" and FIRSTYEAR =?")
				  .append(" and termNo =? ");
			   }
					    
			/*String sql = " select * "
			    +" from  ykt.view_ykt_score  where studentno='"
			    + studentno  
			    + "'";*/
		    //logger.info(sql);
		    //resultSet = getSourceData(sql,statement);
			 
			PreparedStatement ps =conn.prepareStatement(sql.toString());
			ps.setString(1, studentno);
			ps.setInt(2, Integer.parseInt(firstYear));
			ps.setInt(3, Integer.parseInt(termNo));
			//logger.error("----sql----"+sql.toString());
			resultSet = ps.executeQuery();
			int i=0;
			while(resultSet.next()){	    
				++i;
			//	logger.error("-----resultSet------"+i);
				Score score = new Score();
				score.setMajorName(resultSet.getString("MAJORNAME"));
				score.setClassName(resultSet.getString("CLASSNAME"));
				score.setFirstYear(String.valueOf(resultSet.getInt("FIRSTYEAR")));
				score.setEndYear(String.valueOf(resultSet.getInt("ENDYEAR")));
				score.setTermNo(String.valueOf(resultSet.getInt("TERMNO")));
				score.setCourseName(resultSet.getString("COURSENAME"));
				score.setTotalScoreName(resultSet.getString("TOTALSCORENAME"));
			//	logger.error("-----setend------");
				scoreList.add(score);
				  
		    	}
			}
		//	logger.error("--scoreList.size---"+scoreList.size());
			return scoreList;
			
		} catch (SQLException e) {
			logger.error("--查询教务数据库失败--getStudentScore--");
			e.printStackTrace();
			return null;
		}catch (Exception e) {
			logger.error("--查询教务数据出错--getStudentScore--");
			e.printStackTrace();
			return null;
		}
		finally {
			try {
				if(resultSet != null){
					resultSet.close();
				}
			/*	if(statement !=null){
					statement.close();
				}*/
				if (conn != null) {
					conn.close();
				}
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}
	}
	
	
	private static final Logger logger = Logger
	.getLogger(ConnectDatabase.class);
	
	private  String database = KSConfiguration.getInstance().getProperty("database", "oracle");
	private  String instance = KSConfiguration.getInstance().getProperty("instance", "ora9");
	private  String username=KSConfiguration.getInstance().getProperty("username", "ykt");
	private  String passwd=KSConfiguration.getInstance().getProperty("passwd", "ykt_hrbgcdx0807");
	private  String dbIp =KSConfiguration.getInstance().getProperty("dbIp", "192.168.1.21");
	private  String dbServerPort  =KSConfiguration.getInstance().getProperty("dbServerPort", "1521");
	private  String url = "jdbc:oracle:thin:@"+dbIp+":"+dbServerPort+":"+instance;
	private  Connection conn= getConnect();
	private  static Statement statement=null;
	
}
