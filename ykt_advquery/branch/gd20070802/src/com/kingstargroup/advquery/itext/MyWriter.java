/*
 * Created on 2005-7-1
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package com.kingstargroup.advquery.itext;

import com.lowagie.text.BadElementException;
import com.lowagie.text.DocumentException;
import com.lowagie.text.Table;

/**
 * @author jcoder
 * 
 * TODO To change the template for this generated type comment go to Window -
 * Preferences - Java - Code Style - Code Templates
 */
public class MyWriter extends PDFWriter {
	public MyWriter(String path) {
		super(path);
		try {
			header = new PDFParagragh("�����豸������",1,12);
			document.add(header);
			table = new Table(14);
			table.setBorderWidth(0);
			table.addCell(new PDFCell("�����ۣ�500Ԫ���Ϻ�500Ԫ��", 1, 5));
			table.addCell(new PDFCell("2005��7��1��", 1, 9));
			document.add(table);
			table = new Table(14);
			table.setBorderWidth(1);
			table.addCell(new PDFCell("�豸���", 1, 2));
			table.addCell(new PDFCell("�豸����", 1, 3));
			table.addCell(new PDFCell("�ͺŹ��", 1, 2));
			table.addCell(new PDFCell("����", 1, 1));
			table.addCell(new PDFCell("����", 1, 1));
			table.addCell(new PDFCell("�ܼ�", 1, 1));
			table.addCell(new PDFCell("����", 1, 2));
			table.addCell(new PDFCell("��ע", 1, 2));
			table.endHeaders();// ����
			table.addCell(new PDFCell("0126242245", 1, 2));
			table.addCell(new PDFCell("IBM���ͻ�", 1, 3));
			table.addCell(new PDFCell("5465-445GH", 1, 2));
			table.addCell(new PDFCell("3", 1, 1));
			table.addCell(new PDFCell("299,000", 1, 1));
			table.addCell(new PDFCell("2,230,200", 1, 1));
			table.addCell(new PDFCell("��", 1, 2));
			table.addCell(new PDFCell("���ѧԺ����", 1, 2));
			table.endHeaders();
			table.addCell(new PDFCell("������λ�����", 1, 11));
			table.addCell(new PDFCell("Ժ��ϵ��ǩ��", 1, 3));
			table.endHeaders();
			table.addCell(new PDFCell("������뵥λ�����", 1, 11));
			table.addCell(new PDFCell("Ժ��ϵ��ǩ��", 1, 3));
			table.endHeaders();
			table.addCell(new PDFCell("�豸�����������", 1, 5));
			table.addCell(new PDFCell("ʵ�������豸��������", 1, 4));
			table.addCell(new PDFCell("У��������", 1, 5));
			table.endHeaders();
			document.add(table);
			close();// �����ǹر�
		} catch (BadElementException e) {
			e.printStackTrace();
		} catch (DocumentException e) {
			e.printStackTrace();
		}
	}
}