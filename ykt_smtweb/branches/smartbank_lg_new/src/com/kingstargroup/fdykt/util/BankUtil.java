package com.kingstargroup.fdykt.util;

import java.sql.SQLException;
import java.util.List;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.dao.DB2BankCardDAO;
import com.kingstargroup.fdykt.dto.BankCheckDTO;

public class BankUtil {
	
	  DB2BankCardDAO  bankCardDao = new DB2BankCardDAO();
	  private static final Logger logger = Logger.getLogger(BankUtil.class);
 
	   public  boolean   checkBankCardHead(String bankno)throws  SQLException, Exception {
		
			boolean flag =false;
			try{
				List list = bankCardDao.getBankCard();
				for(int i=0;i<list.size();i++){
					BankCheckDTO bankcheck = (BankCheckDTO)list.get(i);
					if(bankno.startsWith(bankcheck.getCardHead())){
					  	flag=true;
					}
					if(flag==true){
						break;
					}
				}
				return flag;
			} catch (Exception e) {
				logger.error("读取银行字典表失败");
				throw (e);
	    	}
	   }
	   
	   public  boolean   checkBankCardLength(String bankno)throws  SQLException, Exception {
			
			boolean flag =false;
			try{
				List list = bankCardDao.getBankCard();
				for(int i=0;i<list.size();i++){
					BankCheckDTO bankcheck = (BankCheckDTO)list.get(i);
					if(bankno.length()==bankcheck.getCardLength()){
					  	flag=true;
					}
					if(flag==true){
						break;
					}
				}
				return flag;
			} catch (Exception e) {
				logger.error("读取银行字典表失败");
				throw (e);
	    	}
	   }
	   
	   
	   
	   public static String   hiddenbandcard(String bankno) {
		   int length=bankno.length();
		   String begin = bankno.substring(0,4);
		   String end = bankno.substring(length-4,length);
		   int i=8;
		   while(length-i>0){
			   begin = begin+"*";
			   i++;
		   }
		   bankno=begin+end;
		   return bankno;
	   }
	   
	   public static void main(String[] arg){
		System.out.print(hiddenbandcard("12356789012345"));
		System.out.println(new Integer("5242.0"));
	   }

}
