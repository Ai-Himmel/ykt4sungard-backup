package com.kingstargroup.utils;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

import junit.framework.TestCase;

public class XMLGenerateUtilTest extends TestCase {

	public void testXMLGenerate() {
		String XMLTemp = "<?xml version=\"1.0\" encoding=\"GBK\"?><table></table>";
		try {
			Document document = DocumentHelper.parseText(XMLTemp);
			Element root = document.getRootElement();
			Element head = root.addElement("head");
			// head.addElement("ErrorCode",errorCode);
			head.addElement("ErrorCode").addText("0000");
			// head.addElement("ErrorMessage",errorMessage);
			head.addElement("ErrorMessage").addText("ok");
			head.addElement("Flag").addText("1");
			Element content = root.addElement("content");
			
			Element record = content.addElement("record");
			record.addElement("aaa")
			.addText("bbb");
			XMLTemp = document.asXML();
			System.out.println(XMLTemp);
		}catch (Exception e) {
			// TODO: handle exception
		}
	}

}
