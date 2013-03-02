/**
 * 
 */
package org.king.checkinmanage.web.action;

import org.king.checkinmanage.domain.Noticemodel;
import org.king.checkinmanage.domain.StuCardfeeInfo;
import org.king.checkinmanage.domain.StuFeeInfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.utils.DateUtil;
import org.king.checkinmanage.web.form.UpLoadForm;
import org.king.classmanage.domain.Studentmodel;
import org.apache.poi.hssf.usermodel.*;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.upload.FormFile;
import org.apache.struts.validator.DynaValidatorForm;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
/**
 * @author jackey
 *
 */
public class StuEnrollNoAction extends BaseAction{
	
    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	public ActionForward load4upload(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		 return mapping.findForward("enrollnoselfile");
	}
	
	/**
	* number of rows in the ResultSet
	*/
	private int rowCount;

	/**
	* number of columns in ResultSet
	*/
	private int colCount;

	/**
	* The names of the columns in the ResultSet
	*/
	private List columnNames = new ArrayList();

	/**
	*  The class types of the columns being displayed.
	*/
	private List columnTypes = new ArrayList();

	/**
	*  Transcribes the data in the ResultSet into a List of lists
	*/
	private List result = new ArrayList();

	/**
	* Name of the spreadsheet table being displayed
	*/
	private String tableName;
	
	public ActionForward importExcelFile(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception{
	   	
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
   		ActionMessages messages = new ActionMessages();
	        	
	    if (form instanceof UpLoadForm) {//如果form是UpLoadsForm
	 	           
	        String encoding = request.getCharacterEncoding();

	 	    if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	 	        {
	 	            response.setContentType("text/html; charset=gb2312");
	 	        }
	 	     UpLoadForm theForm = (UpLoadForm ) form;
	 	     FormFile file = theForm.getTheFile();//取得上传的文件
	 	     if(file==null){	 	    	 
	 	    	System.out.println("can not getFormFile.");
	        	return mapping.findForward("enrollnoimportfail");
	 	     }
	 	     
	 	     String contentType = file.getContentType();

	      	 String size = (file.getFileSize() + " bytes");//文件大小
	      	 
	 	     String fileName= file.getFileName();//文件名
	 	     fileName=request.getParameter("filepath");
	 	     InputStream is = file.getInputStream();//把文件读入
	 	    try{  
   	         List list=reloadSpreadsheetModel(is);	 	     
   	         
   	         //System.out.println(list.size());
   	         if(list!=null&&list.size()>0){
   	        	System.out.println("write xls success");
   	        	if(checkinmanageservice==null)
				    System.out.println("service is null");
   	        	
   	        	Comparator comp1 = new Comparator() { 
   					public int compare(Object o1, Object o2){ 
   					List m1 = (List)o1; 
   					List m2 = (List)o2; 
   					String dictCaption1 = (String)m1.get(1); 
   					String dictCaption2 = (String)m2.get(1);      				

   					com.ibm.icu.text.Collator collator = com.ibm.icu.text.Collator.getInstance(java.util.Locale.CHINA);
   					com.ibm.icu.text.CollationKey c1= collator.getCollationKey(dictCaption1);
   					com.ibm.icu.text.CollationKey c2= collator.getCollationKey(dictCaption2);
   	                //注意,返回值是比较的结果>0,=0,或者<0
   				    return collator.compare(c1.getSourceString(),c2.getSourceString());				
   					 } 
   			    } ;				
   				 
   			    Collections.sort(list, comp1);
   	        	   	            
	            	String notfindstu="";
	            	String dupenrollNostu="";
	            	String[][] twoNos=new String[list.size()][2];
	            	String stuNos="";
	            	
	            	for(int i=0;i<list.size();i++){
	    	        	   
	       	        	List rowlist=(List)list.get(i); 
	       	        	String studentNo=(String)rowlist.get(0);
	       	        	String enrollNo=(String)rowlist.get(1);
	       	        	if(enrollNo.length()>15)
	       	        		enrollNo=enrollNo.substring(0,15);	
	       	        	
	       	        	if(enrollNo.length()>0){
	       	        		List stuenroll=checkinmanageservice.find("select a.enterenceNo from Studentmodel a where a.studentNo!='"+studentNo+"' and a.enterenceNo='"+enrollNo+"'");
	       	        	    if(stuenroll!=null&&stuenroll.size()>0&&dupenrollNostu.indexOf(studentNo)==-1){
	       	        	    	dupenrollNostu=dupenrollNostu+studentNo+",";
	       	        	    	twoNos[i][0]="";
	    	       	            twoNos[i][1]="";
	    	       	            continue;
	       	        	    }
	       	        	    else if(dupenrollNostu.indexOf(studentNo)!=-1){
	       	        	    	twoNos[i][0]="";
    	    	       	        twoNos[i][1]="";
    	    	       	        continue;
	       	        	    }
	       	        	    else{
	       	        	    	int j=i+1;
	       	        	    	if(j<list.size()){
	       	        	    	    List curlist=(List)list.get(j); 
	       	        	    	    if(curlist.get(1).equals(enrollNo)&&!curlist.get(0).equals(studentNo)){	       	        	    			
	       	        	    		    dupenrollNostu=dupenrollNostu+studentNo+","+(String)curlist.get(0)+",";
	    	       	        	        twoNos[i][0]="";
	    	    	       	            twoNos[i][1]="";
	    	    	       	            continue;
	       	        	    	    }
	       	        	    	}
	       	        	    }
	       	        	}
	       	        	
	       	        	if(studentNo!=null&&studentNo.length()>0){
	       	        	    stuNos=stuNos+"'"+studentNo+"'"+",";
	       	        	    twoNos[i][0]=studentNo;
	       	                twoNos[i][1]=enrollNo;
	       	        	}
	       	        }
	            	
	            	if(stuNos.length()>0)
	            		stuNos=stuNos.substring(0,stuNos.length()-1);
	            	
	            	if(stuNos.length()>0){
	            		String isgz=request.getParameter("hisgz");
	            		if(isgz!=null&&isgz.equals("1"))
	            		    notfindstu=checkinmanageservice.updateEnrollNo(twoNos,stuNos,isgz);
	            		else{
	            			isgz="0";
	            			notfindstu=checkinmanageservice.updateEnrollNo(twoNos,stuNos,isgz);
	            		}
	            	}
	            	
	            	if(notfindstu.length()>0){	            		
	            	    request.setAttribute("notfindstu",notfindstu);
	            	} 
	            	if(dupenrollNostu.length()>0){
	            		dupenrollNostu=dupenrollNostu.substring(0,dupenrollNostu.length()-1);
	            		if(dupenrollNostu.length()>0)
	            			request.setAttribute("dupenrollNostu", dupenrollNostu);
	            	}
   	        }
   	         else{
   	        	return mapping.findForward("enrollnoimportfail");
   	         }
	    }catch(Exception e){
   		      e.printStackTrace();
   		      System.out.println("write xls faile");
   		      return mapping.findForward("enrollnoimportfail");
   	    }
	    finally{
	    	is.close();
	    }
	 }
	    return mapping.findForward("enrollnoimportsuccess");
 }
	
	/**
	* Method reloadSpreadsheetModel.
	* Reloads the TableModel with the contents of specified fileName.
	* @param tableName table with which to reload the TableModel
	* @exception SQLException if a database error occurs
	* @exception ClassNotFoundException
	*/
	public List reloadSpreadsheetModel(InputStream is) throws IOException {
		// Use POI to read the selected Excel Spreadsheet
		
		HSSFWorkbook wb = new HSSFWorkbook(is);
		// Extract the name of the first worksheet and use this for the tableName
		tableName =  wb.getSheetName(0);
		// Select the first worksheet
		HSSFSheet sheet = wb.getSheet(tableName); 		    
		try {
			clearAll();
//			System.out.println("Updating model...");
			//updateColumnModel(fileName);
			// Use the HFFS functions for the number of rows & columns, instead of computing them ourselves
//			System.out.println("Getting Spreadsheet Dimensions...");
			rowCount = sheet.getPhysicalNumberOfRows();
			colCount = sheet.getRow(0).getPhysicalNumberOfCells();

			for(int i = 1; i < rowCount; i++) {
				// Get row number i
//				System.out.println("Getting row  " + i);
				HSSFRow row = sheet.getRow(i); 
				// Store the row in a list
				ArrayList list = new ArrayList();
				//System.out.println("colCount="+colCount);
				//for(short j = 0; j <colCount; j++) {
					// Add each cell to the row
//					System.out.println("Getting cell " + j);
				if(row.getCell((short)0)!=null&&row.getCell((short)0).getStringCellValue().length()>0){
					list.add(row.getCell((short)0).getStringCellValue());
					if(row.getCell((short)1)!=null)
					   list.add(row.getCell((short)1).getStringCellValue());
					else						
					   list.add("");
				//}
				// Store the row in a list of lists
				    result.add(list);
				}
			}
			// Remove one row from the rowCount, since the first row is assumed to be the column names 
			rowCount--;
			return result;
//			System.out.println("Done");
			//fireTableStructureChanged();
		// Catch all Exceptions, most likely a POI error
		} catch (Exception e) {
			System.out.println("A POI error has occured.");
			e.printStackTrace();
			return null;
		}
    }
	
	/**
	* Method updateColumnModel.
	* Extracts column metadata from the specified fileName.
	* @param fileName
	* @throws IOException
	*/
	private void updateColumnModel(String fileName) throws IOException {
		// Use POI to read the selected Excel Spreadsheet
		HSSFWorkbook wb = new HSSFWorkbook(new FileInputStream(fileName));
		// Extract the name of the first worksheet and use this for the tableName
		String tableName =  wb.getSheetName(0);
		// Select the first worksheet
		HSSFSheet sheet = wb.getSheet(tableName);
		// Extract column names from the first row
		HSSFRow row = sheet.getRow(0);
		try {
//			System.out.println("Updating model...");
			for(short j = 0; j < row.getPhysicalNumberOfCells(); j++) {
//			System.out.println("Getting column name " + j + row.getCell(j).getStringCellValue());
				// Get the Column names from each cell
				columnNames.add(row.getCell(j).getStringCellValue());
				//System.out.print(row.getCell(j).getStringCellValue()+" ");
			}
			// Extract column types from first non-empty row
			// Set a flag when we have found a non-empty row
//			System.out.println("Setting Flag");
			System.out.println("rowcount="+sheet.getPhysicalNumberOfRows());
			boolean found = false;
			// Skip the first row, the column names are extracted from this row.
			for(int i = 1; (i < sheet.getPhysicalNumberOfRows()) && !found; i++) {
				// Get row number i 
//				System.out.println("Getting row " + i);
				row = sheet.getRow(i);
				ArrayList list = new ArrayList();
				// To check if the row is blank, inspect the first column only
				if (row.getCell((short)0).getCellType() != HSSFCell.CELL_TYPE_BLANK) {
//					System.out.println("Non-empty row found");
					found=true;
					for(short j = 0; j < row.getPhysicalNumberOfCells(); j++) {
//						System.out.println("Getting cell " + j);
						columnTypes.add(new Integer(row.getCell(j).getCellType()));
					}
				}
			}
		// Catch all Exceptions, most likely a POI error
		} catch (Exception e) {
			System.out.println("A POI error has occured.");
			e.printStackTrace();
		}
	}

	/**
	* Method clearAll.
	* clears the TableModel
	*/
    private void clearAll() {
    	// Clear each List representing each row
		for (int i = 0; i < result.size(); i++) {
			ArrayList list = (ArrayList) result.get(i);
			list.clear();
		}
		// Clear all rows
		result.clear();
		// Clear Metadata
		columnNames.clear();
		columnTypes.clear();
		// Clear the row and column counts
		colCount = 0;
		rowCount = 0;
	}
        
}
