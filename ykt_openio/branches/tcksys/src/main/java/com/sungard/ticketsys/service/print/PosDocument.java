package com.sungard.ticketsys.service.print;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import com.sungard.ticketsys.common.Configuration;
import com.sungard.ticketsys.common.Constants;

import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.print.PageFormat;

/**
 * 用于收据打印机，打印时不分页
 * User: Yiming.You
 * Date: 2011-7-6
 */
public class PosDocument extends AbstractDocument {

    private static final Logger logger = Logger.getLogger(PosDocument.class);

    @Override
    public void configPage(Graphics2D graphics2D, PageFormat pageFormat, int pageIndex) {
        graphics2D.setPaint(Color.black);
        //创建字体
        int fontSize = Configuration.getIntProperty(Constants.FONT_SIZE, 16);
        String fontName = Configuration.getProperty(Constants.FONT_NAME);
        if (StringUtils.isBlank(fontName)) {
            Font font = new Font(fontName, Font.PLAIN, fontSize);
            graphics2D.setFont(font);
        }
        pageFormat.getPaper().setImageableArea(0,0,56,100);
    }

    /**
     * 实现打印当前页的规则
     *
     * @param graphics2D .
     * @param pageFormat .
     * @param pageIndex  .
     */
    @Override
    public void drawCurrentPage(Graphics2D graphics2D, PageFormat pageFormat, int pageIndex) {
        String content = this.getPageContent(pageIndex);
        if (StringUtils.isBlank(content)) {
            return;
        }
        String[] data = StringUtils.split(content, "<br>");
        int fontSize = graphics2D.getFont().getSize();
        //startRow=1代表从第一行开始打印，startColumn=0代表从第一列开始打印
        int startRow = Configuration.getIntProperty(Constants.START_ROW, 1) * fontSize;
        int startColumn = (Configuration.getIntProperty(Constants.START_COLUMN, 1) - 1) * fontSize;
        for (String line : data) {
            graphics2D.drawString(line, startColumn, startRow);
            startRow += graphics2D.getFont().getSize();
        }
    }
}
