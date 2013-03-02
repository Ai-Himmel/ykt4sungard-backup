/**
 * 
 */
package org.king.checkinmanage.web.action;

import org.king.checkinmanage.domain.Noticemodel;
import org.king.checkinmanage.domain.StuFeeInfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.framework.web.action.BaseAction;
import org.king.checkinmanage.web.form.UpLoadForm;
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
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
/**
 * @author jackey
 *
 */
public class StufeeAction extends BaseAction{
	
    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	public ActionForward load4upload(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		 return mapping.findForward("selfile");
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
	 	    	return mapping.findForward("importfail");
	 	     }
	 	     
	 	     String contentType = file.getContentType();

	      	 String size = (file.getFileSize() + " bytes");//文件大小
	      	 
	 	     String fileName= file.getFileName();//文件名
	 	     fileName=request.getParameter("filepath");
	 	     InputStream is = file.getInputStream();//把文件读入
	 	    try{  
   	         List list=reloadSpreadsheetModel(is);	 	     
   	         System.out.println("write xls success");
   	         System.out.println(list.size());
   	         if(list!=null&&list.size()>0){
   	        	
   	        	  	        	
   	        	
   	           for(int i=0;i<list.size();i++){
   	        	   
   	        	List rowlist=(List)list.get(i); 
   	        	   	        	
   	        	StuFeeInfo stufeeinfo = new StuFeeInfo();
   	        		
   	        	stufeeinfo.setStudentNo((String)rowlist.get(0));   	        	
   	        	stufeeinfo.setFeeItem((String)rowlist.get(1));   	        	
   	        	stufeeinfo.setShouldPay(Long.parseLong(((Long)rowlist.get(2)).toString()));    	        	
   	        	stufeeinfo.setExactPay(Long.parseLong(((Long)rowlist.get(3)).toString()));    	        	
   	        	stufeeinfo.setUpdatorId(request.getParameter("updatorId"));   	        	
   	        	stufeeinfo.setUpdateTime(new Timestamp(System.currentTimeMillis()));
   	        	
   	            if(checkinmanageservice==null)
				    System.out.println("service is null");
   	            List feeList=checkinmanageservice.find("select new Map(sf.id as id) from StuFeeInfo sf where sf.studentNo='"+stufeeinfo.getStudentNo()+"' and sf.feeItem='"+stufeeinfo.getFeeItem()+"'"); 
   	            if(feeList!=null&&feeList.size()>0){
	        		    Map sfm=(Map)feeList.get(0);
	        			String sfid=((String)sfm.get("id")).trim();
	        			stufeeinfo.setId(sfid);	        			
	        			checkinmanageservice.update(stufeeinfo);	        		
	        	}
   	            else
			        checkinmanageservice.save(stufeeinfo);
 			    
   	        }
   	     }
	    }catch(Exception e){
   		      e.printStackTrace();
   		      System.out.println("write xls faile");
   		      return mapping.findForward("importfail");
   	    }
	    finally{
	    	is.close();
	    }
	 }
	    return mapping.findForward("importsuccess");
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
				
				//for(short j = 0; j <colCount; j++) {
					// Add each cell to the row
//					System.out.println("Getting cell " + j);
					list.add(row.getCell((short)2).getStringCellValue());					
					
					String payitem=row.getCell((short)4).getStringCellValue();
					
					if(payitem.trim().equals("学费"))
					    list.add("01");
					else if(payitem.trim().equals("住宿费"))
						list.add("02");
					else if(payitem.trim().equals("书籍费"))
						list.add("03");		
					else
						list.add("00");
										
					list.add(new Long((new Double(row.getCell((short)6).getNumericCellValue()).longValue())));      
										
					list.add(new Long((new Double(row.getCell((short)7).getNumericCellValue()).longValue())));
					
										
				//}
				// Store the row in a list of lists
				result.add(list);
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
