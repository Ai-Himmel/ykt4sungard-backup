package com.kingstargroup.fdykt.util;

import java.sql.SQLException;

import com.kingstargroup.fdykt.dao.ErrCodeDAO;

public class RetMessageUtil {
	
	ErrCodeDAO codedao = new ErrCodeDAO();
	
	public   String  getMsg (int code) throws  Exception{
		
		return codedao.getMsg(code);
		
	}
	

}
