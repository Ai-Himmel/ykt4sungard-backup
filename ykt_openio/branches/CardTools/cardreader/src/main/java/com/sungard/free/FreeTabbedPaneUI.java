package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.plaf.metal.MetalTabbedPaneUI;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Rectangle;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-1
 */
public class FreeTabbedPaneUI extends MetalTabbedPaneUI {

    private FreeTabbedPane tab = null;
    private int firstTabIndent = 0;

    public FreeTabbedPaneUI(FreeTabbedPane tab) {
        this.tab = tab;
    }

    @Override
    protected Rectangle getTabBounds(int tabIndex, Rectangle dest) {
        Rectangle bounds = super.getTabBounds(tabIndex, dest);
        //give first tab a leading space.
        bounds.x += firstTabIndent;
        return bounds;
    }

    @Override
    protected void paintTabBorder(Graphics g, int tabPlacement, int tabIndex, int x, int y, int w, int h, boolean isSelected) {

        //paint nothing, expect the bottom line in the leading indent.
        g.setColor(FreeUtil.TAB_BOTTOM_LINE_COLOR);
        int lineY = tab.getPreferredTabHeight() - 1;
        g.drawLine(0, lineY, firstTabIndent, lineY);
    }

    @Override
    protected void paintTabBackground(Graphics g, int tabPlacement, int tabIndex, int x, int y, int w, int h, boolean isSelected) {
        //paint nothing
    }

    @Override
    protected int calculateTabWidth(int tabPlacement, int tabIndex, FontMetrics metrics) {
        int width = super.calculateTabWidth(tabPlacement, tabIndex, metrics);
        //use this to remove the tab between tabs.
        return width - 5;
    }

    @Override
    protected int calculateTabHeight(int tabPlacement, int tabIndex, int fontHeight) {
        return tab.getPreferredTabHeight();
    }
}
