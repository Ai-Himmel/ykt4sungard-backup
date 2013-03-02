package org.king.check.student.web.action;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFFont;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.upload.FormFile;
import org.king.check.domain.TRoom;
import org.king.check.domain.TRoomdevice;
import org.king.check.domain.TRoomdeviceId;
import org.king.check.service.RoomService;
import org.king.framework.web.action.BaseAction;
import org.king.upload.web.form.UpLoadForm;

public class RoomAction extends BaseAction {
	
	private RoomService roomService;
	
	
	public void setRoomService(RoomService roomService) {
		this.roomService = roomService;
	}
	
	  public ActionForward roomImpInit(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
		throws Exception {
		   HttpSession session = request.getSession(false);
			if (session == null) {
				session = request.getSession(true);
			}
		       session.removeAttribute("resultstring");
		     return mapping.findForward("roomImp");
	     
	    }
		  
    public ActionForward impRoom(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
    	
    	HttpSession session = request.getSession(false);
		if (session == null) {
			session = request.getSession(true);
		}
   	    if (form instanceof UpLoadForm) {//如果form是UpLoadsForm
	 	           
	      String encoding = request.getCharacterEncoding();

	 	    if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8")))
	 	        {
	 	            response.setContentType("text/html; charset=gb2312");
	 	        }
	 	     UpLoadForm theForm = (UpLoadForm ) form;
	 	     FormFile file = theForm.getTheFile();//取得上传的文件
	 	     if(file==null){	 	    	
	 	    	return mapping.findForward("importfail");
	 	     }	 	     
	 	     InputStream checkis = file.getInputStream();//把文件读入,用于检查格式
	 	 	 String resultstring="";

	 	    try{
	 	    	
	 		HSSFWorkbook wb = new HSSFWorkbook(checkis);		
			String tableName =  wb.getSheetName(0);		
			HSSFSheet sheet = wb.getSheet(tableName); 	
			resultstring = roomService.ifRoomCanImp(sheet);
			
   	         if(!"".equals(resultstring)){
   	        	session.setAttribute("resultstring",resultstring); 
   	        	return mapping.findForward("importfail");
   	         }
   	         resultstring = roomService.saveRoomImp(sheet);
   	         session.setAttribute("resultstring",resultstring); 
   	         if(!"".equals(resultstring)) {
   	        	return mapping.findForward("importfail");
   	        }
	    }catch(Exception e){
   		      e.printStackTrace();
   		      return mapping.findForward("importfail");
   	    }
	    finally{
	    	checkis.close();
	    }
	  }
	    return mapping.findForward("importsuccess");	
	}

	public ActionForward searchRoom(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		List  roomList = new ArrayList();
		DynaActionForm   dform =(DynaActionForm)form; 
	    TRoom room = new TRoom();
		BeanUtils.copyProperties(room,dform);
		roomList = roomService.findRoom(room);
		request.setAttribute("roomList", roomList);
		return mapping.findForward("roomSearch");	
	}
	
	public ActionForward updateRoom(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		  TRoom  room = new TRoom();
		  DynaActionForm   dform =(DynaActionForm)form; 
		  BeanUtils.copyProperties(room,dform);		  
		  roomService.updateRoom(room);		  
		  return mapping.findForward("roomEdit");
	}
	
	public ActionForward addRoom(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		  TRoom  room = new TRoom();
		  DynaActionForm   dform =(DynaActionForm)form; 
		  BeanUtils.copyProperties(room,dform);
		  roomService.saveRoom(room);	  
		  return mapping.findForward("roomEdit");
	}
	
	public ActionForward deleteRoom(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		String  roomid = request.getParameter("rommid");
		TRoom room = roomService.getRoom(roomid);
		roomService.deleteRoom(room);
		return searchRoom(mapping,form,request,response);
	}
	
	public ActionForward updateRoomdevice(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		
		String  roomId = request.getParameter("rommId");
		String[]  deviceIds = request.getParameterValues("deviceId");
		TRoomdevice roomdevice = new TRoomdevice();
		roomdevice.getId().setRoomId(roomId);
		
		List list = roomService.findRoomDevice(roomdevice);
	    Iterator it = list.iterator();
	    while(it.hasNext()){
	    	TRoomdevice rd=(TRoomdevice)it.next();
	    	 roomService.deleteRoomDevice(rd);
	    }
	    if(deviceIds!=null && deviceIds.length>0){
	    	for(int j=0;j<deviceIds.length;j++){
	    		TRoomdeviceId   id = new TRoomdeviceId(roomId,Integer.getInteger(deviceIds[j]));
	    		TRoomdevice  trd = new  TRoomdevice(id);
	    		roomService.saveRoomDevice(trd);
	    	}
	    }
	    return searchRoom(mapping,form,request,response);
		}
		
	
	public ActionForward getModel(
            ActionMapping mapping,
            ActionForm form, 
            HttpServletRequest request,
            HttpServletResponse response) throws Exception {
	 
	
	    	String fileName = "room.xls";

			// Create the Sheet with the name of the Table
			HSSFWorkbook wb = new HSSFWorkbook();

			// 设置显示的字体以及相关的样式
			HSSFFont font = wb.createFont();
			font.setFontHeightInPoints((short) 8);
			font.setItalic(false);
			font.setStrikeout(false);

			// 设置标题栏单元格的样式
			HSSFCellStyle cellHeadStyle = wb.createCellStyle();
			cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
			cellHeadStyle.setBorderBottom((short) 1);
			cellHeadStyle.setBorderLeft((short) 1);
			cellHeadStyle.setBorderRight((short) 1);
			cellHeadStyle.setBorderTop((short) 1);
			cellHeadStyle
					.setFillForegroundColor(HSSFColor.GREY_25_PERCENT.index);
			cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

			// 设置数据行的字体以及以及相关的对齐方式
			HSSFCellStyle cellDataStyle = wb.createCellStyle();
			cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
			cellDataStyle.setFont(font);

			HSSFSheet sheet1 = wb.createSheet("Sheet1");

			// Grab & populate the Column Names
			HSSFRow row = sheet1.createRow((short) 0);

			// Populate the first row of the spreadsheet with the column names
			List columnNames = new ArrayList();
													

			columnNames.add(0, "校区");
			columnNames.add(1, "楼宇");
			columnNames.add(2, "教室");
			
			
			HSSFCellStyle keycellHeadStyle = wb.createCellStyle();//必填字段的标题栏格式
			keycellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
			keycellHeadStyle.setBorderBottom((short) 1);
			keycellHeadStyle.setBorderLeft((short) 1);
			keycellHeadStyle.setBorderRight((short) 1);
			keycellHeadStyle.setBorderTop((short) 1);		
			keycellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_ORANGE.index);   
	        keycellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND); 
			
			for (int i = 0; i < columnNames.size(); i++) {
				HSSFCell cname = row.createCell((short) i);	
				if(i==0||i==1)
					cname.setCellStyle(keycellHeadStyle);
				else
					cname.setCellStyle(cellHeadStyle);
				cname.setEncoding(HSSFCell.ENCODING_UTF_16);			
				cname.setCellValue((String) columnNames.get(i));
			}

				// create row in spreadsheet
				row = sheet1.createRow((short)1);

				// populate the spreadsheet with the cell
				HSSFCell ctitle = row.createCell((short) 0);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue("国顺路");

				ctitle = row.createCell((short) 1);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue("新大楼");
				
				ctitle = row.createCell((short) 2);
				ctitle.setCellStyle(cellDataStyle);
				ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
				ctitle.setCellValue("307");
				
   		
			response.setContentType("application/x-msdownload");
			response.setHeader("Content-Disposition", "attachment;"
					+ " filename="
					+ new String(fileName.getBytes(), "ISO-8859-1"));

			OutputStream os = response.getOutputStream();
			wb.write(os);
			/*-----------------------------------------------------------------------*/
			return null;
	    }
	}


