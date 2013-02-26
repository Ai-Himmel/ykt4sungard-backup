package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.JTable;
import javax.swing.border.Border;
import javax.swing.table.DefaultTableCellRenderer;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Insets;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-17
 */
public class FreeTableHeaderRenderer extends DefaultTableCellRenderer {

    private Color background = FreeUtil.TABLE_HEADER_BACKGROUND_COLOR;
    private Color textColor = new Color(126, 104, 127);
    private Color borderLightColor = FreeUtil.TABLE_HEADER_BORDER_BRIGHT_COLOR;
    private Color borderDarkColor = FreeUtil.TABLE_HEADER_BORDER_DARK_COLOR;
    private int tableHeaderHeight = 20;
    private Border border = new Border() {

        public void paintBorder(Component c, Graphics g, int x, int y, int width, int height) {
            g.setColor(borderDarkColor);
            g.drawRect(x, y, width - 1, height - 1);
            //draw brigher border.
            g.setColor(borderLightColor);
            g.drawLine(x, y, x, height - 1);
        }

        public Insets getBorderInsets(Component c) {
            return new Insets(1, FreeUtil.TABLE_CELL_LEADING_SPACE, 1, 1);
        }

        public boolean isBorderOpaque() {
            return true;
        }
    };

    @Override
    public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
        super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
        this.setFont(FreeUtil.TABLE_HEADER_FONT);
        this.setBackground(background);
        this.setForeground(textColor);
        this.setBorder(border);
        return this;
    }

    @Override
    public Dimension getPreferredSize() {
        Dimension size = super.getPreferredSize();
        return new Dimension(size.width, tableHeaderHeight);
    }
}