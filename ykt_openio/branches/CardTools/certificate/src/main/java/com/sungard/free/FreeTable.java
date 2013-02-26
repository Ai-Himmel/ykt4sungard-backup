package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.JTable;
import javax.swing.table.TableCellRenderer;
import java.awt.Color;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-17
 */
public class FreeTable extends JTable {

    private Color verticalGridColor = Color.white;
    private FreeTableCellRenderer renderer = new FreeTableCellRenderer();
    private FreeTableHeaderRenderer headerRenderer = new FreeTableHeaderRenderer();

    public FreeTable() {
        init();
    }

    private void init() {
        this.setFont(FreeUtil.FONT_12_PLAIN);
        this.getTableHeader().setFont(FreeUtil.FONT_12_BOLD);
        this.getTableHeader().setDefaultRenderer(headerRenderer);
        this.setBorder(null);
        this.setRowSelectionAllowed(true);
        this.setShowHorizontalLines(false);
        this.setShowVerticalLines(true);
        this.setGridColor(verticalGridColor);
        this.setRowMargin(0);
    }

    @Override
    public TableCellRenderer getCellRenderer(int row, int column) {
        return renderer;
    }

    @Override
    public boolean isCellEditable(int row, int column) {
        return false;
    }
}