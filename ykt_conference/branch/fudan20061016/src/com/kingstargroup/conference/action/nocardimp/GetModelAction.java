package com.kingstargroup.conference.action.nocardimp;

import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFFont;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

public class GetModelAction extends Action{
	
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
    	
    	String fileName = "conferencemodel.xls";

		// Create the Sheet with the name of the Table
		HSSFWorkbook wb = new HSSFWorkbook();

		// 设置显示的字体以及相关的样式
		HSSFFont font = wb.createFont();
		font.setFontHeightInPoints((short) 8);
		font.setItalic(false);
		font.setStrikeout(false);

		// 设置标题栏单元格的样式
	/*	HSSFCellStyle cellHeadStyle = wb.createCellStyle();
		cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		cellHeadStyle.setBorderBottom((short) 1);
		cellHeadStyle.setBorderLeft((short) 1);
		cellHeadStyle.setBorderRight((short) 1);
		cellHeadStyle.setBorderTop((short) 1);*/
	/*	cellHeadStyle
				.setFillForegroundColor(HSSFColor.GREY_25_PERCENT.index);
		cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);*/

		// 设置数据行的字体以及以及相关的对齐方式
		HSSFCellStyle cellDataStyle = wb.createCellStyle();
		cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
	//	cellDataStyle.setFont(font);

		HSSFSheet sheet1 = wb.createSheet("Sheet1");

		// Grab & populate the Column Names
		HSSFRow row = sheet1.createRow((short) 0);

		// Populate the first row of the spreadsheet with the column names
		List columnNames = new ArrayList();
		
		columnNames.add(0, NoCardConstant.NAME);
		columnNames.add(1, NoCardConstant.SEX);
		columnNames.add(2, NoCardConstant.DUTY);
		columnNames.add(3, NoCardConstant.DEPT);
		
		
		
						
		/*HSSFCellStyle keycellHeadStyle = wb.createCellStyle();//必填字段的标题栏格式
		keycellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
		keycellHeadStyle.setBorderBottom((short) 1);
		keycellHeadStyle.setBorderLeft((short) 1);
		keycellHeadStyle.setBorderRight((short) 1);
		keycellHeadStyle.setBorderTop((short) 1);		
		keycellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_ORANGE.index);   
        keycellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND); */
		
		for (int i = 0; i < columnNames.size(); i++) {
			HSSFCell cname = row.createCell((short) i);	
			/*if(i==0||i==1)
				cname.setCellStyle(keycellHeadStyle);
			else
				cname.setCellStyle(cellHeadStyle);*/
		  	cname.setEncoding(HSSFCell.ENCODING_UTF_16);			
			cname.setCellValue((String) columnNames.get(i));
		}

		// Populate the Row Data to the SpreadSheet
		//int rowCount = 3;
		// goal houses the number of cells in the target spreadsheet
		//int goal = rowCount * columnNames.size();
	
		
			// create row in spreadsheet
			/*row = sheet1.createRow((short)1);

			// populate the spreadsheet with the cell
			HSSFCell ctitle = row.createCell((short) 0);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("王家欢");
			
			ctitle = row.createCell((short) 1);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("男");
			
			ctitle = row.createCell((short) 2);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("办公室主任");
			
			ctitle = row.createCell((short) 3);
			ctitle.setCellStyle(cellDataStyle);
			ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
			ctitle.setCellValue("办公室");*/
			
		
		
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
