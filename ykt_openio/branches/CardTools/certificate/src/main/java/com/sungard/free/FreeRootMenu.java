package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.BorderFactory;
import javax.swing.JMenu;
import javax.swing.border.Border;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.TexturePaint;

/**
 * .
 * User: Yiming.You
 * Date: 2011-8-31
 */
public class FreeRootMenu extends JMenu {

    private Color foregroundColor = FreeUtil.DEFAULT_TEXT_COLOR;

    private String selectedBackgroundImageURL = FreeUtil.getImageURL("menubar_background_selected.png");

    private TexturePaint paint = FreeUtil.createTexturePaint(selectedBackgroundImageURL);

    private Border border = BorderFactory.createEmptyBorder(0, 5, 0, 4);

    public FreeRootMenu() {
        init();
    }

    public FreeRootMenu(String text) {
        super(text);
        init();
    }

    private void init() {
        this.setFont(FreeUtil.FONT_14_BOLD);
        this.setBorder(border);
        this.setForeground(foregroundColor);
    }

    @Override
    protected void paintComponent(Graphics g) {

        if (this.isSelected()) {
            Graphics2D g2d = (Graphics2D) g;
            g2d.setPaint(paint);
            g2d.fillRect(0, 0, this.getWidth(), this.getHeight());

            super.paintComponent(g);
        } else {
            super.paintComponent(g);
        }
    }
}