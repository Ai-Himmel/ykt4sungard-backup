package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.JTabbedPane;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.Component;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-1
 */
public class FreeTabbedPane extends JTabbedPane {

    private int preferredUnselectedTabWidth = 100;
    private int preferredTabHeight = FreeUtil.getImageIcon("images/tab_header_background.png").getIconHeight();

    public FreeTabbedPane() {
        init();
    }

    private void init() {
        this.setFont(FreeUtil.FONT_12_BOLD);
        this.setForeground(FreeUtil.DEFAULT_TEXT_COLOR);
        this.setBorder(null);
        this.setFocusable(false);
        this.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);
        this.setOpaque(false);
        this.setUI(new FreeTabbedPaneUI(this));
        this.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                //inform each tab component that select changed.
                updateTabComponents();
            }
        });
    }

    @Override
    public void addTab(String title, Component component) {
        super.addTab(title, component);
        int index = this.getTabCount() - 1;
        FreeTabComponent tabComponent = new FreeTabComponent(this);
        tabComponent.setTitle(title);
        this.setTabComponentAt(index, tabComponent);
        this.setToolTipTextAt(index, title);
        updateTabComponents();
    }

    public int getPreferredTabHeight() {
        return preferredTabHeight;
    }

    private void updateTabComponents() {
        int selectedIndex = this.getSelectedIndex();
        for (int i = 0; i < this.getTabCount(); i++) {
            Component c = this.getTabComponentAt(i);
            if (c instanceof FreeTabComponent) {
                FreeTabComponent component = (FreeTabComponent) c;
                boolean selected = selectedIndex == i;
                component.updateSelection(selected);
            }
        }
    }

    public int getPreferredUnselectedTabWidth() {
        return preferredUnselectedTabWidth;
    }
}
