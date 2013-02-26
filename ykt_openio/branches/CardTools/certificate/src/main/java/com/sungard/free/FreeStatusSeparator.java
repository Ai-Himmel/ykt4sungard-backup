package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JLabel;

/**
 * .
 * User: Yiming.You
 * Date: 2011-8-31
 */
public class FreeStatusSeparator extends JLabel {

    private ImageIcon imageIcon = FreeUtil.getImageIcon("images/statusbar_separator.png");

    public FreeStatusSeparator() {
        init();
    }

    private void init() {
        this.setBorder(BorderFactory.createEmptyBorder(0, 5, 0, 5));
        this.setOpaque(false);
        this.setIcon(imageIcon);
    }
}
