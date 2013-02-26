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
 * ��ӡ���ͻ���
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
            //ָ����ӡ�����ʽ
            DocFlavor flavor = DocFlavor.SERVICE_FORMATTED.PRINTABLE;
            //���ô�ӡ����
            PrintRequestAttributeSet parameters = new HashPrintRequestAttributeSet();
            // ����ֽ�Ŵ�С,Ҳ�����½�MediaSize�����Զ����С
            //��56mm ��100mm
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
                //ָ����ӡ����
                Doc doc = new SimpleDoc(document, flavor, docAttributeSet);
                //������ӡ��ҵ
                DocPrintJob job = printService.createPrintJob();
                //����ÿһҳ�ľ����ӡ����
                job.print(doc, parameters);
            }
        } catch (Exception e) {
            logger.error("��ӡʧ��:" + e.getMessage());
            
        }
    }

    /**
     * Ѱ�Ҵ�ӡ��
     *
     * @param flavor     .
     * @param parameters .
     * @return
     */
    public PrintService getPrintService(DocFlavor flavor, PrintRequestAttributeSet parameters) {
        PrintService printService;

        //���Ĭ�ϴ�ӡ��,����û��������ļ��������˴�ӡ������,��ô�����õĴ�ӡ����ΪĬ�ϴ�ӡ��,����Ѱ��ϵͳĬ�ϴ�ӡ��
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

        //���showDialogΪtrue,��ô�����Ի������û��Լ�ѡ���ӡ��
        String showDialog = Configuration.getProperty("showDialog");
        if ("true".equals(showDialog)) {
            printService = ServiceUI.printDialog(null, 100, 200, PrintServiceLookup.lookupPrintServices(null, null), defaultPrintService, flavor, parameters);
        } else {
            printService = defaultPrintService;
        }

        return printService;
    }
}
