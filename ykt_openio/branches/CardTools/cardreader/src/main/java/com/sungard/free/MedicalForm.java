package com.sungard.free;

import com.sungard.util.FreeUtil;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Locale;

/**
 * .
 * User: Yiming.You
 * Date: 2011-8-31
 */
public class MedicalForm extends JFrame {
    private ActionListener menuAction = new ActionListener() {
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();
            changeTab(command);
        }
    };
    private String title = "Sungard Medical System V1.0";
    private FreeMenuBar menubar;
    private FreeContentPane contentPane = new FreeContentPane();
    private FreeStatusBar statusBar = new FreeStatusBar();
    private FreeMemoryBar memoryBar = new FreeMemoryBar();
    private FreeStatusTimeLabel lbStatusTime = new FreeStatusTimeLabel();
    private FreeTabbedPane tab = new FreeTabbedPane();

    public MedicalForm() {
        Locale.setDefault(Locale.SIMPLIFIED_CHINESE);
        initMenuBar();
        initSwing();
        initTab();
        initStatusBar();
    }

    /**
     * 加载菜单
     */
    public void initMenuBar() {
        menubar = new FreeMenuBar();
        FreeRootMenu rootMenu = new FreeRootMenu();
        rootMenu.setText("系统");
        menubar.add(rootMenu);

        JMenuItem prepareItem = new FreeMenuItem();
        prepareItem.setText("功能区");
        prepareItem.setActionCommand("功能区");
        prepareItem.addActionListener(menuAction);
        rootMenu.add(prepareItem);

        JMenuItem paymentItem = new FreeMenuItem();
        paymentItem.setText("医疗付费");
        paymentItem.setActionCommand("医疗付费");
        paymentItem.addActionListener(menuAction);
        rootMenu.add(paymentItem);

        JMenuItem detailItem = new FreeMenuItem();
        detailItem.setText("付费明细");
        detailItem.setActionCommand("付费明细");
        detailItem.addActionListener(menuAction);
        rootMenu.add(detailItem);

        JMenuItem reportItem = new FreeMenuItem();
        reportItem.setText("付费统计");
        reportItem.setActionCommand("付费统计");
        reportItem.addActionListener(menuAction);
        rootMenu.add(reportItem);
    }

    private void initSwing() {
        this.setTitle(title);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(800, 500);
        this.setIconImage(FreeUtil.getImage("images/logo.png"));

        this.setContentPane(contentPane);
        FreeUtil.centerWindow(this);
        contentPane.add(menubar, BorderLayout.NORTH);
        contentPane.add(statusBar, BorderLayout.SOUTH);

        JPanel centerPane = new JPanel(new BorderLayout());
        centerPane.setOpaque(true);
        centerPane.setBackground(FreeUtil.CONTENT_PANE_BACKGROUND);
        centerPane.setBorder(BorderFactory.createEmptyBorder(2, 0, 0, 0));

        centerPane.add(tab, BorderLayout.CENTER);
        contentPane.add(centerPane, BorderLayout.CENTER);
    }

    private void initTab() {
        tab.addTab("功能区", new FunctionPage());
    }

    private FreePagePane createPage(String action) {
        FreePagePane page = null;
        if ("功能区".equals(action)) {
            page = new FunctionPage();
        } else if ("医疗付费".equals(action)) {
            page = new PaymentPage();
        } else if ("付费明细".equals(action)) {
            page = DetailPage.getInstance();
        } else if ("付费统计".equals(action)) {
            page = ReportPage.getInstance();
        }
        return page;
    }


    private void initStatusBar() {
        statusBar.add(memoryBar);
        statusBar.addSeparator();
        statusBar.add(lbStatusTime);
    }

    public void changeTab(String action) {
        int tabIndex = -1;
        for (int i = 0; i < tab.getTabCount(); i++) {
            Component c = tab.getTabComponentAt(i);
            if (c instanceof FreeTabComponent) {
                FreeTabComponent component = (FreeTabComponent) c;
                if (component.getTitle().equals(action)) {
                    tabIndex = i;
                }
            }
        }
        if (tabIndex == -1) {
            tab.addTab(action, createPage(action));
            tab.setSelectedIndex(tab.getTabCount() - 1);
        } else {
            tab.setSelectedIndex(tabIndex);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                FreeUtil.setupLookAndFeel();
                MedicalForm shell = new MedicalForm();
                shell.setVisible(true);
            }
        });
    }
}
