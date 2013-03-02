package com.kingstar.files;

import javax.xml.parsers.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;
import java.io.*;


public class SaxParse extends DefaultHandler {

	public SaxParse() {
		
		}
	public SaxParse(String fname){
		
		 try {
		      //����SAX��������
		      SAXParserFactory spfactory = SAXParserFactory.newInstance();
		      //����SAX��������
		      SAXParser parser = spfactory.newSAXParser();
		      //ָ��XML�ļ�������XML����
		      parser.parse(new File("fname"), new SaxParse());
		    } catch (Exception e) {
		      e.printStackTrace();
		    }
		
		
		
	}
	


public static void main(String[] argv) {
    try {
      //����SAX��������
      SAXParserFactory spfactory = SAXParserFactory.newInstance();
      //����SAX��������
      SAXParser parser = spfactory.newSAXParser();
      //ָ��XML�ļ�������XML����
      parser.parse(new File("dataSources.xml"), new SaxParse());
    } catch (Exception e) {
      e.printStackTrace();
    }
  }




  public void startElement(String uri,
                           String localName,
                           String qName,
                           Attributes attributes) throws SAXException {

    System.out.println("�ڵ㿪ʼ��" + qName);
    for(int i=0;i<attributes.getLength();i++){
     System.out.println("�ڵ��������ƣ�" + attributes.getQName(i));
     System.out.println("�ڵ�����ֵ��"+attributes.getValue(i));
    }
  }



}
