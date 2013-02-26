package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.BorderFactory;
import javax.swing.JTable;
import javax.swing.border.Border;
import javax.swing.table.DefaultTableCellRenderer;
import java.awt.Color;
import java.awt.Component;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-17
 */
public class FreeTableCellRenderer extends DefaultTableCellRenderer {

    private Color backgroundEven = Color.white;
    private Color backgroundOdd = FreeUtil.TABLE_ODD_ROW_COLOR;
    private Color backgroundSelected = new Color(255, 223, 156);
    private Color selectedTextColor = Color.BLACK;
    private Color textColor = FreeUtil.TABLE_TEXT_COLOR;
    private Border border = BorderFactory.createEmptyBorder(0, FreeUtil.TABLE_CELL_LEADING_SPACE, 0, 0);

    @Override
    public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {
        super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
        this.setFont(FreeUtil.TABLE_CELL_FONT);
        this.setBorder(border);
        if (!isSelected) {
            if (row % 2 == 1) {
                this.setBackground(backgroundOdd);
            } else {
                this.setBackground(backgroundEven);
            }
            this.setForeground(textColor);
        } else {
            this.setBackground(backgroundSelected);
            this.setForeground(selectedTextColor);
        }
        return this;
    }
}
