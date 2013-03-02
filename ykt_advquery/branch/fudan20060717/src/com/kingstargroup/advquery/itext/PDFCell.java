/*
 * Created on 2005-7-1
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package com.kingstargroup.advquery.itext;

import com.lowagie.text.BadElementException;
import com.lowagie.text.Chunk;
import com.lowagie.text.Font;
import com.lowagie.text.rtf.table.RtfCell;

/**
 * @author jcoder
 * 
 * TODO To change the template for this generated type comment go to Window -
 * Preferences - Java - Code Style - Code Templates
 */
public class PDFCell extends RtfCell {

	public PDFCell(String content, int rowspan, int colspan)
			throws BadElementException {
		super(new Chunk(content, PDFChineseFont.createChineseFont(12,
				Font.NORMAL)));
		setRowspan(rowspan);
		setColspan(colspan);
		setHeader(false);
	}
}