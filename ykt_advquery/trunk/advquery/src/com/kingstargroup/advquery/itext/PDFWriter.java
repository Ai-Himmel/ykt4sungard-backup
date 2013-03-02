/*
 * Created on 2005-7-1
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package com.kingstargroup.advquery.itext;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import com.lowagie.text.Cell;
import com.lowagie.text.Document;
import com.lowagie.text.DocumentException;
import com.lowagie.text.Paragraph;
import com.lowagie.text.Rectangle;
import com.lowagie.text.Table;
import com.lowagie.text.pdf.PdfWriter;

/**
 * @author jcoder
 * 
 * TODO To change the template for this generated type comment go to Window -
 * Preferences - Java - Code Style - Code Templates
 */
abstract public class PDFWriter {
	protected Document document = null;

	protected FileOutputStream out = null;

	protected Rectangle pageSize = null;

	protected String filePath = null;

	protected Cell cell = null;

	protected Paragraph header = null;

	protected Paragraph prg = null;

	protected Table table = null;

	public PDFWriter(String filePath) {
		try {
			this.filePath = filePath;
			document = new Document();
			out = new FileOutputStream(filePath);
			PdfWriter.getInstance(document, out);
			document.open();
		} catch (FileNotFoundException e) {

			e.printStackTrace();
		} catch (DocumentException e) {

			e.printStackTrace();
		}

	}

	public void close() {
		try {
			document.close();
			out.close();
		} catch (IOException e) {

			e.printStackTrace();
		}
	}

}