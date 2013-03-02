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
		      //建立SAX解析工厂
		      SAXParserFactory spfactory = SAXParserFactory.newInstance();
		      //生成SAX解析对象
		      SAXParser parser = spfactory.newSAXParser();
		      //指定XML文件，进行XML解析
		      parser.parse(new File("fname"), new SaxParse());
		    } catch (Exception e) {
		      e.printStackTrace();
		    }
		
		
		
	}
	


public static void main(String[] argv) {
    try {
      //建立SAX解析工厂
      SAXParserFactory spfactory = SAXParserFactory.newInstance();
      //生成SAX解析对象
      SAXParser parser = spfactory.newSAXParser();
      //指定XML文件，进行XML解析
      parser.parse(new File("dataSources.xml"), new SaxParse());
    } catch (Exception e) {
      e.printStackTrace();
    }
  }




  public void startElement(String uri,
                           String localName,
                           String qName,
                           Attributes attributes) throws SAXException {

    System.out.println("节点开始：" + qName);
    for(int i=0;i<attributes.getLength();i++){
     System.out.println("节点属性名称：" + attributes.getQName(i));
     System.out.println("节点属性值："+attributes.getValue(i));
    }
  }



}
