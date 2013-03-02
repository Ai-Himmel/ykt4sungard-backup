package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.List;

import com.kingstargroup.conference.action.nocardimp.NoCardConstant;

public class ExcelUtil extends BasicUtil {

	public static List readExcel(String filename, ExcelReader readExcel) throws Exception{
      try{
		readExcel.openFile(filename);
		readExcel.setSheetNum(0);
		List list = new ArrayList();
		int count = -1;
		try {
			count = readExcel.getRowCount();
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		for (int a = 0; a <= count; a++) {
			String rows[] = readExcel.readExcelLine(a);
			if(a==0){
			   if(readheadInfo(rows,readExcel)==-1){
				   throw new Exception("excel表不符合规范");
			   }
			}
			list.add(rows);
		}
		return list;
      }catch(Exception e){
    	  throw new Exception("excel表不符合规范");
      }
		
	}
	
	public static int readheadInfo(String[]  row,ExcelReader readExcel){
		
		  if    ((row[0].trim()==null|| row[0].indexOf(NoCardConstant.NAME)==-1) ||
				(row[1].trim()==null || row[1].indexOf(NoCardConstant.SEX)==-1)  ||
				(row[2].trim()==null || row[2].indexOf(NoCardConstant.DUTY)==-1) ||
				(row[3].trim()==null || row[3].indexOf(NoCardConstant.DEPT)==-1) ){			
			return -1;//格式错误 
			
		 }
		 return 0;
				
	}

}
