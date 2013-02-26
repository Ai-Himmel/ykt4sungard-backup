package com.sungard.free;

import javax.swing.JComponent;
import javax.swing.JPanel;
import java.awt.BorderLayout;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-1
 */
public class FreePagePane extends JPanel {

    private JPanel centerPane;

    public FreePagePane() {
        this(null);
    }

    public FreePagePane(JComponent contentComponent) {
        centerPane = new JPanel(new BorderLayout());
        init(contentComponent);
    }

    private void init(JComponent contentComponent) {
        setLayout(new BorderLayout());
        add(centerPane, BorderLayout.CENTER);
        if (contentComponent != null) {
            centerPane.add(contentComponent, BorderLayout.CENTER);
        }
    }

    public JPanel getCenterPane() {
        return centerPane;
    }
}