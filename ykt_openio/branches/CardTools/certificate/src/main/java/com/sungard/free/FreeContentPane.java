package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.JPanel;
import java.awt.BorderLayout;

/**
 * .
 * User: Yiming.You
 * Date: 2011-8-31
 */
public class FreeContentPane extends JPanel {
    public FreeContentPane() {
        this.setLayout(new BorderLayout());
        setBackground(FreeUtil.CONTENT_PANE_BACKGROUND);
    }
}
