/**
 * 
 */
package org.king.yangong.checkinmanage.web.action;

import org.king.framework.web.action.BaseAction;

/**
 * @author jackey
 *
 */

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.sql.Timestamp;
import java.sql.Time;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;
import java.util.Map;
import java.sql.Date;
import java.sql.Clob;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.checkinmanage.domain.Noticemodel;
import org.king.checkinmanage.domain.Stucheckininfo;
import org.king.checkinmanage.domain.Stuhealthinfo;
import org.king.checkinmanage.service.CheckinmanageService;
import org.king.framework.web.action.BaseAction;
import org.king.rcvmanage.domain.Stuarriveinfo;


public class NoticeAction  extends BaseAction{
	
    private CheckinmanageService checkinmanageservice;
	
	public void setCheckinmanageService(CheckinmanageService checkinmanageservice) {
		this.checkinmanageservice = checkinmanageservice;
	}
	
	public ActionForward add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		//ActionMessages msg = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		Noticemodel notice = (Noticemodel)aform.get("notice");
		String msg="";
		try {
			
			if(request.getParameter("notice.noticeNo").length()==0)
			   notice.setNoticeNo("0003");
			
			notice.setCreateTime(new Timestamp(System.currentTimeMillis()));		    
		    notice.setUpdateTime(new Timestamp(System.currentTimeMillis()));
		
 		// 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 if (isTokenValid(request, true)) {
				 msg="1";
			     checkinmanageservice.save(notice);
			 }
			 else{
				 msg="9";
				 saveToken(request);
			 }
			 request.setAttribute("show", "添加成功！");
			 //System.out.println("add success");			 
			 return mapping.findForward("noticelistall");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("add error");
			request.setAttribute("msg","1");
			return load4add(mapping, form, request, response);
		}

	}
	
	public ActionForward list(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 //指定班级的新生报到信息列表,classNo要从session中取得
			 List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni order by ni.updateTime desc");
			
			 if(noticeList!=null&&noticeList.size()!=0){
				 
                 List resultList=new ArrayList();
                 
				 if(noticeList.size()>5)
				     resultList=noticeList.subList(0,5);//只显示前5条记录
				 else
					 resultList=noticeList;
				 
				 if(resultList!=null&&resultList.size()>0){
				 request.setAttribute("noticelist",resultList);
				 
				 request.setAttribute("listcount",new Integer(resultList.size()));
				 
				 }
				 System.out.println("list success");
				 return mapping.findForward("success");
			 }
			 else
				 return mapping.findForward("success");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward load4add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			 	 
			 //System.out.println("begin add success");
			 saveToken(request);
			 return mapping.findForward("notice");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("begin add error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward view(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       
		ActionMessages errors = new ActionMessages();
		
		String id=request.getParameter("updateid");
		
			 try {
				 	    
 		         // 数据库验证
		   
			     if(checkinmanageservice==null)
				     System.out.println("service is null");
			     List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.id='"+id+"'");
			    
			     request.setAttribute("noticelist",noticeList);
				 System.out.println("view success");
				 return mapping.findForward("noticeview");
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("view error");
				return mapping.findForward("faile");
			}

	}
	
	public ActionForward load4update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();
		
		
		//String[] userid=request.getParameterValues("cb");
		String updateid=request.getParameter("updateid");

 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.id='"+updateid+"'");
			    
		     request.setAttribute("noticelist",noticeList);
			 System.out.println("find 4 update success");
			 return mapping.findForward("noticeedit");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find 4 update error");
			return load4update(mapping, form, request, response);
		}

	}
	
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages msg = new ActionMessages();
		DynaValidatorForm aform = (DynaValidatorForm) form;	
		Noticemodel notice = (Noticemodel)aform.get("notice");
        
		try {
			if(request.getParameter("notice.noticeNo").length()==0)
			   notice.setNoticeNo("0003");
			 			 						 
			notice.setCreateTime(new Timestamp(Integer.parseInt(request.getParameter("createTime").substring(0,4))-1900,Integer.parseInt(request.getParameter("createTime").substring(5,7))-1,Integer.parseInt(request.getParameter("createTime").substring(8,10)),Integer.parseInt(request.getParameter("createTime").substring(11,13)),Integer.parseInt(request.getParameter("createTime").substring(14,16)),Integer.parseInt(request.getParameter("createTime").substring(17,19)),0));		    
		    notice.setUpdateTime(new Timestamp(System.currentTimeMillis()));
				
		    notice.setId(request.getParameter("updateid"));

 		     // 数据库验证
		
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 checkinmanageservice.update(notice);
			 System.out.println("update success");
			 request.setAttribute("msg","0");
			 request.setAttribute("show", "修改成功！");
			 return mapping.findForward("noticelistall");
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("update error");
			request.setAttribute("msg","1");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       
		ActionMessages errors = new ActionMessages();
		
		String[] ids=request.getParameterValues("cbgroup");
		for(int i=0;i<ids.length;i++){
		                
			 try {
				 Noticemodel notice = findbyId(ids[i]);
		    
 		         // 数据库验证
		   
			     if(checkinmanageservice==null)
				     System.out.println("service is null");
			     checkinmanageservice.delete(notice);
			     request.setAttribute("show", "删除成功！");		     
			     System.out.println("delete success");			     
		    } catch (Exception e) {
			     e.printStackTrace();
			     System.out.println("delete error");
			     return mapping.findForward("faile");
		    }
		}
		return mapping.findForward("noticelist");
	}
	
	public  Noticemodel findbyId(String id)
	throws Exception {
		
       ActionMessages errors = new ActionMessages();

	
       try {
	      if(checkinmanageservice==null)
	     	 System.out.println("service is null");
	      Noticemodel notice=checkinmanageservice.findbyId(id);
	 			 
	      System.out.println("find by id success");
	      return notice;
      } catch (Exception e) {
	    e.printStackTrace();
	    System.out.println("find by id error");
      }
      return null;

      }
	
	public ActionForward find(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();
		
		DynaValidatorForm aform = (DynaValidatorForm) form;	
        
		Noticemodel notice = (Noticemodel)aform.get("notice");
		
        //起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}

 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 String sqlstring="select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.noticeNo='0003' ";
			 
//			 if(request.getParameter("notice.noticeNo")!=null&&request.getParameter("notice.noticeNo").length()!=0)
//				 sqlstring=sqlstring+" and ni.noticeNo like '%"+request.getParameter("notice.noticeNo")+"%'";
//			 
			 if(request.getParameter("notice.title")!=null&&request.getParameter("notice.title").length()!=0)
				 sqlstring=sqlstring+" and ni.title like '%"+request.getParameter("notice.title")+"%'";
 			 
			 sqlstring=sqlstring+" order by ni.updateTime desc";
			 
			 System.out.println(sqlstring);
			 
			 List noticeList=checkinmanageservice.find(sqlstring);
			 
			 if(noticeList!=null&&noticeList.size()!=0){
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=noticeList;
				 else if((Integer.parseInt(offset))<noticeList.size()||(Integer.parseInt(offset))==noticeList.size())
					 resultList=noticeList.subList((Integer.parseInt(offset)),noticeList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("noticeform",notice);
				     request.setAttribute("noticelist",resultList);
				     request.setAttribute("listcount",new Integer(noticeList.size()));
				 }
				 System.out.println("find success");
				 return mapping.findForward("success");				 
			 }
			 
			 else
				 return mapping.findForward("success"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward findall(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();		
				
        //起始页
		String offset = request.getParameter("pager.offset");
		if (offset == null) {
			offset = "0";
		}

 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 String sqlstring="select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.noticeNo='0003' ";
			 			 
			 sqlstring=sqlstring+" order by ni.updateTime desc";
			 
			 System.out.println(sqlstring);
			 
			 List noticeList=checkinmanageservice.find(sqlstring);
			 
			 if(noticeList!=null&&noticeList.size()!=0){
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=noticeList;
				 else if((Integer.parseInt(offset))<noticeList.size()||(Integer.parseInt(offset))==noticeList.size())
					 resultList=noticeList.subList((Integer.parseInt(offset)),noticeList.size());
				 
				 if(resultList!=null&&resultList.size()>0){					 
				     request.setAttribute("noticelist",resultList);
				     request.setAttribute("listcount",new Integer(noticeList.size()));
				 }
				 System.out.println("find success");
				 return mapping.findForward("listallsuccess");				 
			 }
			 
			 else
				 return mapping.findForward("listallsuccess"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}	
	
	//新生查看入学事项公告
	public ActionForward listview(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		ActionMessages errors = new ActionMessages();
		
 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 			
			 List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni order by ni.updateTime desc");
			
			 if(noticeList!=null&&noticeList.size()!=0){
				 
                 List resultList=new ArrayList();                 
				 if(noticeList.size()>5)
				     resultList=noticeList.subList(0,5);//只显示前5条记录
				 else
					 resultList=noticeList;
				 
				 if(resultList!=null&&resultList.size()>0){
				 request.setAttribute("noticelist",resultList);
				 
				 request.setAttribute("listcount",new Integer(resultList.size()));
				 
				 }
				 System.out.println("list success");
				 return mapping.findForward("success2");
			 }
			 else
				 return mapping.findForward("success2");
			 
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("action list error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward stufind(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
		
		ActionMessages errors = new ActionMessages();

 		// 数据库验证
		try {
			 if(checkinmanageservice==null)
				 System.out.println("service is null");
			 
			 DynaValidatorForm aform = (DynaValidatorForm) form;	
		        
			 Noticemodel notice = (Noticemodel)aform.get("notice");
				
		        //起始页
				String offset = request.getParameter("pager.offset");
				if (offset == null) {
					offset = "0";
				}
			 
			 String sqlstring="select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.noticeNo='0003' ";
			 
//			 if(request.getParameter("notice.noticeNo")!=null&&request.getParameter("notice.noticeNo").length()!=0)
//				 sqlstring=sqlstring+" and ni.noticeNo like '%"+request.getParameter("notice.noticeNo")+"%'";
//			 
			 if(request.getParameter("notice.title")!=null&&request.getParameter("notice.title").length()!=0)
				 sqlstring=sqlstring+" and ni.title like '%"+request.getParameter("notice.title")+"%'";
 			 
			 sqlstring=sqlstring+" order by ni.updateTime desc";
			 
			 System.out.println(sqlstring);
			 
			 List noticeList=checkinmanageservice.find(sqlstring);
			 
			 if(noticeList!=null&&noticeList.size()!=0){
				 List resultList=new ArrayList();
                 //起始页设置
				 if(offset.equals("0"))
				     resultList=noticeList;
				 else if((Integer.parseInt(offset))<noticeList.size()||(Integer.parseInt(offset))==noticeList.size())
					 resultList=noticeList.subList((Integer.parseInt(offset)),noticeList.size());
				 
				 if(resultList!=null&&resultList.size()>0){
					 request.setAttribute("noticeform",notice);
				     request.setAttribute("noticelist",resultList);
				     request.setAttribute("listcount",new Integer(noticeList.size()));
				 }
				 System.out.println("find success");
				 return mapping.findForward("success2");				 
			 }
			 
			 else
				 return mapping.findForward("success2"); 
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("find error");
			return mapping.findForward("faile");
		}

	}
	
	public ActionForward stuview(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
       
		ActionMessages errors = new ActionMessages();
		
		String id=request.getParameter("updateid");
		
			 try {
				 	    
 		         // 数据库验证
		   
			     if(checkinmanageservice==null)
				     System.out.println("service is null");
			     List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.id='"+id+"'");
			    
			     request.setAttribute("noticelist",noticeList);
				 System.out.println("view success");
				 return mapping.findForward("noticestuview");
			} catch (Exception e) {
				e.printStackTrace();
				System.out.println("view error");
				return mapping.findForward("faile");
			}

	}
	
	//测试POI导入DB2
	
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
	
	public ActionForward excel2db(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception{
   	 try{
   		 
   		DynaValidatorForm aform = (DynaValidatorForm) form;			
   		 
   		List list=reloadSpreadsheetModel("workbook.xls");
   	    System.out.println("write xls success");
   	    System.out.println(list.size());
   	    if(list!=null&&list.size()>0){
   	        for(int i=0;i<list.size();i++){
   	        	List rowlist=(List)list.get(i); 
   	        	Noticemodel notice = (Noticemodel)aform.get("notice");
   	        		
   	        	notice.setNoticeNo((String)rowlist.get(0));
   	        	
   	        	String createTime=(String)rowlist.get(1);
   	        	notice.setCreateTime(new Timestamp(System.currentTimeMillis()));
   	        	
   	        	notice.setTitle((String)rowlist.get(2));
   	        	
   	        	notice.setBody((String)rowlist.get(3));
   	        	
   	        	String updateTime=(String)rowlist.get(4);
   	        	notice.setUpdateTime(new Timestamp(System.currentTimeMillis()));
   	        	
   	        	notice.setIfDeleted((String)rowlist.get(5));
   	        	
   	        	notice.setCreatorId((String)rowlist.get(6));
   	        	
   	        	notice.setUpdatorId((String)rowlist.get(7));
   	        	
   	            if(checkinmanageservice==null)
				    System.out.println("service is null");
			    checkinmanageservice.save(notice);
			    //System.out.println("add success");
			   
   	        }
   	    }
   	    
   	 }catch(Exception e){
   		 e.printStackTrace();
   		System.out.println("write xls faile");
   		return mapping.findForward("faile");
   	 }
   	 return mapping.findForward("noticelist");
    }
	
	/**
	* Method reloadSpreadsheetModel.
	* Reloads the TableModel with the contents of specified fileName.
	* @param tableName table with which to reload the TableModel
	* @exception SQLException if a database error occurs
	* @exception ClassNotFoundException
	*/
	public List reloadSpreadsheetModel(String fileName) throws IOException {
		// Use POI to read the selected Excel Spreadsheet
		HSSFWorkbook wb = new HSSFWorkbook(new FileInputStream(fileName));
		// Extract the name of the first worksheet and use this for the tableName
		tableName =  wb.getSheetName(0);
		// Select the first worksheet
		HSSFSheet sheet = wb.getSheet(tableName); 		    
		try {
			clearAll();
//			System.out.println("Updating model...");
			updateColumnModel(fileName);
			// Use the HFFS functions for the number of rows & columns, instead of computing them ourselves
//			System.out.println("Getting Spreadsheet Dimensions...");
			rowCount = sheet.getPhysicalNumberOfRows();
			colCount = sheet.getRow(0).getPhysicalNumberOfCells();
//			System.out.println("Number of rows ==" + rowCount);
//			System.out.println("Number of cols ==" + colCount);
			// Skip the first row, the column names are extracted from this row.
			for(int i = 1; i < rowCount; i++) {
				// Get row number i
//				System.out.println("Getting row  " + i);
				HSSFRow row = sheet.getRow(i); 
				// Store the row in a list
				ArrayList list = new ArrayList();
				System.out.println("colCount="+colCount);
				for(short j = 0; j <colCount; j++) {
					// Add each cell to the row
//					System.out.println("Getting cell " + j);
					list.add(row.getCell(j).getStringCellValue());
					System.out.println("cell"+j+"type:"+row.getCell(j).getCellType());
					/*
					if(row.getCell(j).getCellType()== HSSFCell.CELL_TYPE_STRING)
					   System.out.print(row.getCell(j).getStringCellValue()+" ");
					if(row.getCell(j).getCellType()== HSSFCell.CELL_TYPE_BOOLEAN)
						System.out.print(row.getCell(j).getBooleanCellValue()+" ");
					if(row.getCell(j).getCellType()== HSSFCell.CELL_TYPE_NUMERIC)
						System.out.print(row.getCell(j).getNumericCellValue()+" ");		
				    */	
					
				}
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
				System.out.print(row.getCell(j).getStringCellValue()+" ");
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
    
    //测试导入excel表
    public ActionForward db2excel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception{
    	try
		{
			
			// Create the Excel File
	 		FileOutputStream fileOut = new FileOutputStream("c:/output.xls");
				
			// Create the Sheet with the name of the Table
			HSSFWorkbook wb = new HSSFWorkbook();
			HSSFSheet sheet1 = wb.createSheet("notice");
 		    
			// Grab & populate the Column Names
			HSSFRow row = sheet1.createRow((short)0);
			
			List noticeList=checkinmanageservice.find("select new Map(ni.id as id,ni.noticeNo as noticeNo,ni.title as title,ni.body as body,ni.ifDeleted as ifDeleted,ni.creatorId as creatorId,ni.createTime as createTime,ni.updatorId as updatorId,ni.updateTime as updateTime) from Noticemodel ni where ni.ifDeleted='0' order by ni.updateTime desc");
			
			// Populate the first row of the spreadsheet with the column names
			List columnNames =new ArrayList();
			columnNames.add(0,"id");
			columnNames.add(1,"noticeNo");
			columnNames.add(2,"title");
			columnNames.add(3,"body");
			columnNames.add(4,"ifDeleted");
			columnNames.add(5,"creatorId");
			columnNames.add(6,"createTime");
			columnNames.add(7,"updatorId");
			columnNames.add(8,"updateTime");
			// System.out.println(columnNames.size());
			for (int i=0; i<columnNames.size(); i++)
			{
				//System.out.println((String)columnNames.get(i));
				row.createCell((short)i).setCellValue((String)columnNames.get(i));
			}
			
			// Populate the Row Data to the SpreadSheet
			int rowCount = noticeList.size();
			// goal houses the number of cells in the target spreadsheet
			int goal = rowCount*columnNames.size();			
			
			//actual population of target spreadsheet
			int currentCell = 0;
			
			for (int i=0; i<rowCount; i++)
			{
				Map tableData = (Map)noticeList.get(i);
				// create row in spreadsheet
				row = sheet1.createRow((short)(i+1));
				
					// populate the spreadsheet with the cell
					row.createCell((short)0).setCellValue((String)tableData.get("id"));
					row.createCell((short)1).setCellValue((String)tableData.get("noticeNo"));
					HSSFCell ctitle=row.createCell((short)2);
					 ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
					 ctitle.setCellValue((String)tableData.get("title"));
					row.createCell((short)3).setCellValue((String)tableData.get("body"));
					row.createCell((short)4).setCellValue((String)tableData.get("ifDeleted"));
					row.createCell((short)5).setCellValue((String)tableData.get("creatorId"));
					row.createCell((short)6).setCellValue(((Timestamp)tableData.get("createTime")).toString());
					row.createCell((short)7).setCellValue((String)tableData.get("updatorId"));
					row.createCell((short)8).setCellValue(((Timestamp)tableData.get("updateTime")).toString());
					//System.out.println(columnData);
					currentCell++;

			}			
			// clean up resources
		   	wb.write(fileOut);
	 	 	fileOut.close();
   		 	
		}catch(Exception e){
   		 e.printStackTrace();
   		System.out.println("write xls faile");
   		return mapping.findForward("faile");
   	 }
   	 return mapping.findForward("noticelist");
    }
	
}
