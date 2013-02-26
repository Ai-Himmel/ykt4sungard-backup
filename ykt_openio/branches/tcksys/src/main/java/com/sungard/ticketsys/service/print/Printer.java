package com.sungard.ticketsys.service.print;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import com.sungard.ticketsys.common.Configuration;

import javax.print.Doc;
import javax.print.DocFlavor;
import javax.print.DocPrintJob;
import javax.print.PrintException;
import javax.print.PrintService;
import javax.print.PrintServiceLookup;
import javax.print.ServiceUI;
import javax.print.SimpleDoc;
import javax.print.attribute.DocAttributeSet;
import javax.print.attribute.HashAttributeSet;
import javax.print.attribute.HashDocAttributeSet;
import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;
import javax.print.attribute.Size2DSyntax;
import javax.print.attribute.standard.MediaSize;
import javax.print.attribute.standard.MediaSizeName;
import javax.print.attribute.standard.PrinterName;

/**
 * 打印机客户端
 * User: Yiming.You
 * Date: 2011-7-6
 */
public class Printer {

    private static final Logger logger = Logger.getLogger(Printer.class);

    private AbstractDocument document;

    public AbstractDocument getDocument() {
        return document;
    }

    public void setDocument(AbstractDocument document) {
        this.document = document;
    }

    public void print() {
        try {
            //指定打印输出格式
            DocFlavor flavor = DocFlavor.SERVICE_FORMATTED.PRINTABLE;
            //设置打印属性
            PrintRequestAttributeSet parameters = new HashPrintRequestAttributeSet();
            // 设置纸张大小,也可以新建MediaSize类来自定义大小
            //宽56mm 高100mm
//            int pageWidth = Configuration.getIntProperty(Constants.PAGE_WIDTH, 50);
//            int pageHeight = Configuration.getIntProperty(Constants.PAGE_HEIGHT, 100);
//            MediaSize mediaSize = new MediaSize(pageWidth, pageHeight, Size2DSyntax.MM, MediaSizeName.INVOICE);
//            parameters.add(mediaSize.getMediaSizeName());
            parameters.add(MediaSizeName.ISO_A4);

            DocAttributeSet docAttributeSet = new HashDocAttributeSet();

            PrintService printService = getPrintService(flavor, parameters);
            if (printService == null) {
                logger.error("Can't find printer");
            } else {
                //指定打印内容
                Doc doc = new SimpleDoc(document, flavor, docAttributeSet);
                //创建打印作业
                DocPrintJob job = printService.createPrintJob();
                //进行每一页的具体打印操作
                job.print(doc, parameters);
            }
        } catch (Exception e) {
            logger.error("打印失败:" + e.getMessage());
            
        }
    }

    /**
     * 寻找打印机
     *
     * @param flavor     .
     * @param parameters .
     * @return
     */
    public PrintService getPrintService(DocFlavor flavor, PrintRequestAttributeSet parameters) {
        PrintService printService;

        //获得默认打印机,如果用户在配置文件中配置了打印机名称,那么将配置的打印机作为默认打印机,否则寻找系统默认打印机
        PrintService defaultPrintService;
        String printServiceName = Configuration.getProperty("printService");
        if (StringUtils.isNotBlank(printServiceName)) {
            logger.info("start finding printer " + printServiceName);
            HashAttributeSet attributeSet = new HashAttributeSet();
            attributeSet.add(new PrinterName(printServiceName, null));
            PrintService[] printServices = PrintServiceLookup.lookupPrintServices(null, attributeSet);
            defaultPrintService = printServices != null && printServices.length > 0 ? printServices[0] : null;
        } else {
            defaultPrintService = PrintServiceLookup.lookupDefaultPrintService();
        }

        //如果showDialog为true,那么弹出对话框由用户自己选择打印机
        String showDialog = Configuration.getProperty("showDialog");
        if ("true".equals(showDialog)) {
            printService = ServiceUI.printDialog(null, 100, 200, PrintServiceLookup.lookupPrintServices(null, null), defaultPrintService, flavor, parameters);
        } else {
            printService = defaultPrintService;
        }

        return printService;
    }
}
