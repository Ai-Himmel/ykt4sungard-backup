package org.king.framework.util;

import org.apache.commons.betwixt.io.BeanWriter;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.SAXReader;
import org.dom4j.io.XMLWriter;
import org.xml.sax.SAXException;

import java.beans.IntrospectionException;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.io.Writer;
import java.util.Collection;
import java.util.Iterator;

public final class XMLUtils {
    private static Log log = LogFactory.getLog(XMLUtils.class);

    public static Element getRootElement(Document doc) {
        return doc.getRootElement();
    }

    public static void main(String[] args) {
        String path = XMLUtils.class.getResource("/log4j.properties").getPath();
        path = path.substring(1, path.length());

        if ((!path.substring(0, 1).equals("/")) && (!path.substring(1, 2).equals(":"))) {
            path = "/" + path;
        }

        Document doc = read(path);
        Element root = getRootElement(doc);

        for (Iterator i = root.elementIterator(); i.hasNext();) {
            Element item = (Element) i.next();

        }
        Iterator ii;
        Element node;
        Element item = root.addElement("protected-resource");
        item.addElement("box").addText("102");
        item.addElement("desc").addText("the three page");
        item.addElement("url").addText("three.do");
    }

    public static Document read(String fileName) {
        SAXReader reader = new SAXReader();
        Document document = null;
        try {
            document = reader.read(fileName);
        } catch (DocumentException e) {
            log.error(e.getMessage());
        }

        return document;
    }

    public static void write(Document doc, String path) {
        try {
            OutputFormat format = OutputFormat.createPrettyPrint();
            XMLWriter output = new XMLWriter(new FileWriter(new File(path)), format);

            output.write(doc);
            output.close();
        } catch (IOException e) {
            log.error(e.getMessage());
        }
    }

    public static void write(Collection beans, String path) {
        File f = new File(path);

        if (!f.exists()) {
            try {
                f.createNewFile();
            } catch (IOException e1) {
                log.error("create file error", e1);
            }
        }

        PrintWriter pw = null;
        try {
            Writer wr = new OutputStreamWriter(new FileOutputStream(f), "UTF-8");

            pw = new PrintWriter(wr);
        } catch (FileNotFoundException e) {
            log.error("file not found error", e);
        } catch (UnsupportedEncodingException e) {
            log.error("file encoding error", e);
        }

        pw.write("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
        pw.write("<!DOCTYPE acl-config SYSTEM \"acl-config.dtd\">\n");

        BeanWriter beanWriter = new BeanWriter(pw);

        beanWriter.getXMLIntrospector().setAttributesForPrimitives(false);

        beanWriter.enablePrettyPrint();
        try {
            beanWriter.write("acl-config", beans);
            pw.close();
        } catch (IOException e) {
            log.error("write file error", e);
        } catch (SAXException e) {
            log.error("write file error", e);
        } catch (IntrospectionException e) {
            log.error("write file error", e);
        }
    }
}