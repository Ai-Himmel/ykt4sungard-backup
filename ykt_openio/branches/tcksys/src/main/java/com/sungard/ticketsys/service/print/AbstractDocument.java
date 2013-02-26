package com.sungard.ticketsys.service.print;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-7-6
 */
public abstract class AbstractDocument implements Printable {

    protected List<String> pages = new ArrayList<String>();

    public abstract void configPage(Graphics2D graphics2D, PageFormat pageFormat, int pageIndex);

    public abstract void drawCurrentPage(Graphics2D graphics2D, PageFormat pageFormat, int pageIndex);

    public int print(Graphics graphics, PageFormat pageFormat, int pageIndex) throws PrinterException {
        Graphics2D graphics2D = (Graphics2D) graphics;
        //ת�����꣬ȷ����ӡ�߽�
        graphics2D.translate(pageFormat.getImageableX(), pageFormat.getImageableY());
        configPage(graphics2D, pageFormat, pageIndex);
        //����ӡҳ�Ŵ�����Ҫ��ӡ����ҳ��ʱ����ӡ��������
        if (pageIndex >= pages.size()) {
            return Printable.NO_SUCH_PAGE;
        }
        //��ӡ��ǰҳ�ı�
        drawCurrentPage(graphics2D, pageFormat, pageIndex);
        //���ڴ�ӡҳʱ��������ӡ����
        return Printable.PAGE_EXISTS;
    }

    /**
     * ��ȡָ���±��ҳ������
     *
     * @param pageIndex ҳ���±꣬��0��ʼ
     * @return
     */
    public String getPageContent(int pageIndex) {
        if (pageIndex < 0) {
            throw new RuntimeException("Invalid page index, index couldn't less than 0");
        }
        String pageContent = "";
        if (pageIndex < pages.size()) {
            pageContent = pages.get(pageIndex);
        }
        return pageContent;
    }

    /**
     * ����һҳ����
     *
     * @param content .
     */
    public void addPage(String content) {
        pages.add(content);
    }

    /**
     * �����ҳ��
     *
     * @return .
     */
    public int getPagesCount() {
        return pages.size();
    }
}
