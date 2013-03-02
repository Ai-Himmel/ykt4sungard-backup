package com.kingstargroup.ecard.util;

import org.displaytag.export.ExcelView;

public class SimpleChineseExcelView extends ExcelView {

	public String getMimeType() {
		 return "application/vnd.ms-excel;charset=utf-8"; 
	}
	

}
