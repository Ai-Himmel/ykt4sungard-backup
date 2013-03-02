/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.utils.XmlUtil.java
 * �������ڣ� 2006-6-7 15:36:30
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-7 15:36:30      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.utils;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.Reader;
import java.io.StringReader;
import java.util.Properties;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Text;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

/**
 * <p> XmlUtil.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="XmlUtil.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-7
 * 
 *
 */
public class XmlUtil {

	/** 
	 * Normalizes the given string. */
	public static String normalize(String s) {
		StringBuffer str = new StringBuffer();

		int len = (s != null) ? s.length() : 0;
		for (int i = 0; i < len; i++) {
			char ch = s.charAt(i);
			switch (ch) {
				case '<' :
					{
						str.append("&lt;");
						break;
					}
				case '>' :
					{
						str.append("&gt;");
						break;
					}
				case '&' :
					{
						str.append("&amp;");
						break;
					}
				case '"' :
					{
						str.append("&quot;");
						break;
					}
					/*
					  case '\r':
					  case '\n': {
					  str.append("&#");
					  str.append(Integer.toString(ch));
					  str.append(';');
					  break;
					  } 
					**/
				default :
					{
						str.append(ch);
					}
			}
		}
		return str.toString();
	}

	/**/
	public static Document parseFile(String filename)
		throws SAXException, ParserConfigurationException {
		Properties props;
		props = new Properties();
		return parseFile(filename, props);
	}

	/**/
	public static Document parseFile(String filename, String propfilename)
		throws SAXException, ParserConfigurationException {
		Properties props;
		props = new Properties();
		try {
			InputStream propsStream = new FileInputStream(propfilename);
			props.load(propsStream);
		} catch (FileNotFoundException ex) {
			ex.printStackTrace();
		} catch (IOException ex1) {
			ex1.printStackTrace();
		}
		return parseFile(filename, props);
	}

	/**/
	public static Document parseFile(String filename, Properties props)
		throws SAXException, ParserConfigurationException {
		InputStream input = null;
		try {
			input = new FileInputStream(filename);
		} catch (FileNotFoundException ex) {
			ex.printStackTrace();
			return null;
		}
		return parse(input, props);
	}

	/**/
	public static Document parse(InputStream input, Properties props)
		throws SAXException, ParserConfigurationException {
		return parse(new InputSource(input), props);
	}

	/**/
	public static Document parse(String input)
		throws SAXException, ParserConfigurationException {
		return parse(new StringReader(input), null);
	}

	/**/
	public static Document parse(Reader input)
		throws SAXException, ParserConfigurationException {
		return parse(new InputSource(input), null);
	}

	/**/
	public static Document parse(Reader input, Properties props)
		throws SAXException, ParserConfigurationException {
		return parse(new InputSource(input), props);
	}

	/**/
	public static Document parse(InputSource input, Properties props)
		throws SAXException, ParserConfigurationException {

		Document doc = null;
		try {
			DocumentBuilderFactory docBuilderFactory =
				DocumentBuilderFactory.newInstance();
			DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
			doc = docBuilder.parse(input);
		} catch (IOException e) {
			e.printStackTrace(System.out);
			//throw e;
		}

		return doc;
	}

	/**
	 * Saves a given XML document to the given output stram.
	 */
	public static void writeXML(Document document, OutputStream os)
		throws IOException {
		DOMSource src = new DOMSource(document);
		StreamResult res = new StreamResult(os);
		TransformerFactory tf = TransformerFactory.newInstance();
		try {
			Transformer t = tf.newTransformer();
			t.transform(src, res);
		} catch (TransformerException e) {
			throw new IOException(e.getMessage());
		}
	}

	/**
	 *Creates an XML document XML information.
	 */

	public static Document CreateDoc() {
		DocumentBuilderFactory dbf = null;
		Document doc = null;
		dbf = DocumentBuilderFactory.newInstance();
		try {
			doc = dbf.newDocumentBuilder().newDocument();
		} catch (javax.xml.parsers.ParserConfigurationException ex) {
			throw new RuntimeException(ex.getMessage());
		}
		return doc;
	}

	/**
	 * Creates ElementNode for given tag with particular text as content.
	 */
	public static Element createTextNode(String tag, String content)
		throws ParserConfigurationException {
		DocumentBuilderFactory docBuilderFactory =
			DocumentBuilderFactory.newInstance();
		DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();
		Document doc = docBuilder.newDocument();
		Element node = doc.createElement(tag);
		Text t = doc.createTextNode(content);
		node.appendChild(t);

		return node;
	}
}
