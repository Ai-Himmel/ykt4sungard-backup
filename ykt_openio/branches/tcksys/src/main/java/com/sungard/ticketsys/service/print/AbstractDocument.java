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
        //转换坐标，确定打印边界
        graphics2D.translate(pageFormat.getImageableX(), pageFormat.getImageableY());
        configPage(graphics2D, pageFormat, pageIndex);
        //当打印页号大于需要打印的总页数时，打印工作结束
        if (pageIndex >= pages.size()) {
            return Printable.NO_SUCH_PAGE;
        }
        //打印当前页文本
        drawCurrentPage(graphics2D, pageFormat, pageIndex);
        //存在打印页时，继续打印工作
        return Printable.PAGE_EXISTS;
    }

    /**
     * 获取指定下标的页面内容
     *
     * @param pageIndex 页面下标，从0开始
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
     * 增加一页内容
     *
     * @param content .
     */
    public void addPage(String content) {
        pages.add(content);
    }

    /**
     * 获得总页数
     *
     * @return .
     */
    public int getPagesCount() {
        return pages.size();
    }
}
