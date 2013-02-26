package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.BorderFactory;
import javax.swing.Icon;
import javax.swing.JButton;
import javax.swing.SwingConstants;
import javax.swing.border.Border;
import java.awt.Color;
import java.awt.Component;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Insets;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-19
 */
public class FreeToolbarButton extends JButton {

    private int buttonSize = FreeUtil.DEFAULT_BUTTON_SIZE;
    private Color roverBorderColor = FreeUtil.BUTTON_ROVER_COLOR;
    private Border roverBorder = new Border() {

        public void paintBorder(Component c, Graphics g, int x, int y, int width, int height) {
            g.setColor(roverBorderColor);
            g.drawRect(x, y, width - 1, height - 1);
        }

        public Insets getBorderInsets(Component c) {
            return new Insets(1, 1, 1, 1);
        }

        public boolean isBorderOpaque() {
            return true;
        }
    };
    private Border emptyBorder = BorderFactory.createEmptyBorder(1, 1, 1, 1);

    public FreeToolbarButton() {
        this(null, null);
    }

    public FreeToolbarButton(String text) {
        this(text, null);
    }

    public FreeToolbarButton(Icon icon) {
        this(null, icon);
    }

    public FreeToolbarButton(String text, Icon icon) {
        super(text, icon);
        init();
    }

    private void init() {
        this.setVerticalAlignment(SwingConstants.CENTER);
        this.setFont(FreeUtil.FONT_12_BOLD);
        this.setOpaque(false);
        this.setBorder(emptyBorder);
        this.setContentAreaFilled(false);
        this.setFocusPainted(false);
        this.setRolloverEnabled(true);
        this.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));

        this.addMouseListener(new MouseAdapter() {

            @Override
            public void mouseEntered(MouseEvent e) {
                if (isRolloverEnabled()) {
                    setBorder(roverBorder);
                }
            }

            @Override
            public void mouseExited(MouseEvent e) {
                if (isRolloverEnabled()) {
                    setBorder(emptyBorder);
                }
            }
        });
    }

    @Override
    public void setIcon(final Icon icon) {
        super.setIcon(icon);
        //generate rover icon and pressed icon.

        if (icon == null) {
            this.setPressedIcon(null);
            this.setRolloverIcon(null);
        } else {
            Icon pressedIcon = FreeUtil.createMovedIcon(icon);
            this.setPressedIcon(pressedIcon);
        }
    }

    @Override
    public Dimension getPreferredSize() {
        int width = super.getPreferredSize().width;
        width = Math.max(width, buttonSize);
        int height = buttonSize;
        return new Dimension(width, height);
    }

    public void setRoverBorder(Border roverBorder) {
        this.roverBorder = roverBorder;
        this.repaint();
    }
}
