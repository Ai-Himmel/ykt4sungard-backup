package com.kingstargroup.conference.util;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import net.sf.jxls.transformer.XLSTransformer;

import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFFont;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.HSSFColor;

import com.kingstargroup.conference.hibernate.form.DeptCustForm;
import com.kingstargroup.conference.hibernate.form.TConference;

public class ExportUtil {
	
	private static String report = "template"+File.separator+"report.xls";
	private static String attendee = "template"+File.separator+"attendee.xls";
	
	public static HSSFWorkbook exportReport(String webPath,Map beans) {
		if (!webPath.endsWith(File.separator)) {
			webPath = webPath + File.separator;
		}
		String fileName = webPath + report;
		File reportTemplate = new File(fileName);
		InputStream is = null;
		try {
			is = new FileInputStream(reportTemplate);
			XLSTransformer transformer = new XLSTransformer();
			HSSFWorkbook workBook = transformer.transformXLS(is, beans);
			return workBook;
		} catch (FileNotFoundException e) {
			throw new RuntimeException("模板不存在！");
		} finally{
			try {
				if (is != null) {
					is.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static HSSFWorkbook exportAttendee(String webPath,Map beans) {
		if (!webPath.endsWith(File.separator)) {
			webPath = webPath + File.separator;
		}
		String fileName = webPath + attendee;
		File reportTemplate = new File(fileName);
		InputStream is = null;
		try {
			is = new FileInputStream(reportTemplate);
			XLSTransformer transformer = new XLSTransformer();
			HSSFWorkbook workBook = transformer.transformXLS(is, beans);
			return workBook;
		} catch (FileNotFoundException e) {
			throw new RuntimeException("模板不存在！");
		} finally{
			try {
				if (is != null) {
					is.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	public static HSSFWorkbook exportAttendeeDirect(List confList,List deptCustList,List confCheckRate,List confLateRate) {
		// Create the Sheet with the name of the Table
        HSSFWorkbook wb = new HSSFWorkbook();

        // 设置显示的字体以及相关的样式
        HSSFFont font = wb.createFont();
        font.setFontHeightInPoints((short) 10);
        font.setItalic(false);
        font.setStrikeout(false);

        // 设置标题栏单元格的样式
        HSSFCellStyle cellHeadStyle = wb.createCellStyle();
        cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        cellHeadStyle.setBorderBottom((short) 1);
        cellHeadStyle.setBorderLeft((short) 1);
        cellHeadStyle.setBorderRight((short) 1);
        cellHeadStyle.setBorderTop((short) 1);
        cellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_BLUE.index);
        cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

        // 设置数据行的字体以及以及相关的对齐方式
        HSSFCellStyle cellDataStyle = wb.createCellStyle();
        cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        cellDataStyle.setFont(font);
        
        HSSFCellStyle groupDataStyle = wb.createCellStyle();
        groupDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        groupDataStyle.setFont(font);
        groupDataStyle.setFillForegroundColor(HSSFColor.GREY_25_PERCENT.index);
        groupDataStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);
        
        HSSFSheet sheet1 = wb.createSheet("Sheet1");
        sheet1.setDefaultColumnWidth(( short ) 20 ); 
        int rowCount = 0;
		// 处理标题
        HSSFRow row = sheet1.createRow((short) rowCount++);
		List columnNames = new ArrayList();

		int column = 0;
		columnNames.add(column++, "部门");
		columnNames.add(column++, "学工号");
		columnNames.add(column++, "姓名");
		for (int i = 0; i < confList.size(); i++) {
			TConference conference = (TConference) confList.get(i);
			columnNames.add(column++, conference.getConName());
		}
		columnNames.add(column++, "应出席人数");
		columnNames.add(column++, "实际出席人数");
		columnNames.add(column++, "个人出席率");

		for (int i = 0; i < columnNames.size(); i++) {
			HSSFCell cname = row.createCell((short) i);
			cname.setCellStyle(cellHeadStyle);
			cname.setEncoding(HSSFCell.ENCODING_UTF_16);
			cname.setCellValue((String) columnNames.get(i));
		}

		// 处理个人出勤记录以及部门出勤率
		for (int i = 0; i < deptCustList.size(); i++) {
			DeptCustForm dc = (DeptCustForm) deptCustList.get(i);
			row = sheet1.createRow(rowCount++);
			List columns = new ArrayList();
			int columnCount = 0;
			columns.add(columnCount++, dc.getDeptName());
			columns.add(columnCount++, dc.getStuempNo());
			columns.add(columnCount++, dc.getCustName());
			List configSignList = dc.getConfSignList();
			for (int j = 0; j < configSignList.size(); j++) {
				columns.add(columnCount++, configSignList.get(j));
			}
			columns.add(columnCount++, dc.getPlan());
			columns.add(columnCount++, dc.getPresent());
			columns.add(columnCount++, dc.getCheckRate());

			for (int k = 0; k < columns.size(); k++) {
				Object value = columns.get(k);
				HSSFCell cell = row.createCell((short) k);
				if(dc.getCustId()==null){
					cell.setCellStyle(groupDataStyle);
				} else {
					cell.setCellStyle(cellDataStyle);
				}
				cell.setEncoding(HSSFCell.ENCODING_UTF_16);
				cell.setCellValue(value==null?"":value.toString());
			}
		}
        
		// 处理单次会议出勤率
		row = sheet1.createRow(rowCount++);
		columnNames = new ArrayList();
		column = 0;
		columnNames.add(column++, "单次会议出勤率");
		columnNames.add(column++, "");
		columnNames.add(column++, "");
		for (int i = 0; i < confCheckRate.size(); i++) {
			columnNames.add(column++, confCheckRate.get(i));
		}
		columnNames.add(column++, "");
		columnNames.add(column++, "");
		columnNames.add(column++, "");

		for (int i = 0; i < columnNames.size(); i++) {
			HSSFCell cell = row.createCell((short) i);
			cell.setCellStyle(groupDataStyle);
			cell.setEncoding(HSSFCell.ENCODING_UTF_16);
			cell.setCellValue((String) columnNames.get(i));
		}
        
		// 处理单次会议迟到率
		row = sheet1.createRow(rowCount++);
		columnNames = new ArrayList();
		column = 0;
		columnNames.add(column++, "单次会议迟到率");
		columnNames.add(column++, "");
		columnNames.add(column++, "");
		for (int i = 0; i < confLateRate.size(); i++) {
			columnNames.add(column++, confLateRate.get(i));
		}
		columnNames.add(column++, "");
		columnNames.add(column++, "");
		columnNames.add(column++, "");

		for (int i = 0; i < columnNames.size(); i++) {
			HSSFCell cell = row.createCell((short) i);
			cell.setCellStyle(groupDataStyle);
			cell.setEncoding(HSSFCell.ENCODING_UTF_16);
			cell.setCellValue((String) columnNames.get(i));
		}
        return wb;
	}
}
