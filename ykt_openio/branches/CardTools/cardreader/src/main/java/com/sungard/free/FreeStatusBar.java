package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.border.Border;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.TexturePaint;

/**
 * .
 * User: Yiming.You
 * Date: 2011-8-31
 */
public class FreeStatusBar extends JPanel {

    private String backgroundImageURL = FreeUtil.getImageURL("statusbar_background.png");
    private Image backgroundLeftImage = FreeUtil.getImage("images/statusbar_background_left.png");
    private Image backgroundRightImage = FreeUtil.getImage("images/statusbar_background_right.png");
    private ImageIcon backgroundImageIcon = FreeUtil.getImageIcon(backgroundImageURL);
    private TexturePaint paint = FreeUtil.createTexturePaint(backgroundImageURL);
    private Border border = BorderFactory.createEmptyBorder(2, 10, 0, 0);

    public FreeStatusBar() {
        init();
    }

    private void init() {
        this.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 0));
        this.setBorder(border);
        this.setOpaque(false);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        Graphics2D g2d = (Graphics2D) g;
        g2d.setPaint(paint);
        g2d.fillRect(0, 0, this.getWidth(), this.getHeight());

        //paint left side image.
        g2d.drawImage(backgroundLeftImage, 0, 0, null);

        //paint right side image.
        g2d.drawImage(backgroundRightImage, this.getWidth() - backgroundRightImage.getWidth(null), 0, null);
    }

    public void addSeparator() {
        this.add(new FreeStatusSeparator());
    }

    @Override
    public Dimension getPreferredSize() {
        return new Dimension(super.getPreferredSize().width, backgroundImageIcon.getIconHeight());
    }
}
