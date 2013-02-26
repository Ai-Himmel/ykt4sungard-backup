package com.sungard.free;

import com.sungard.bean.Payrecord;
import com.sungard.service.PayrecordService;
import com.sungard.util.ExportUtil;
import com.sungard.util.FreeUtil;
import org.apache.log4j.Logger;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;
import javax.swing.border.Border;
import javax.swing.table.DefaultTableModel;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.Vector;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-17
 */
public class DetailPage extends FreePagePane {
    private static final Logger logger = Logger.getLogger(DetailPage.class);
    private FreeTable table = new FreeTable();
    private JScrollPane scroll = new JScrollPane(table);
    private int descriptionHeight = 25;
    private JTextField lbDescription = new JTextField() {
        @Override
        public Dimension getPreferredSize() {
            Dimension size = super.getPreferredSize();
            return new Dimension(size.width, descriptionHeight);
        }
    };
    private Border descriptionBorder = BorderFactory.createEmptyBorder(0, FreeUtil.TABLE_CELL_LEADING_SPACE, 0, 0);
    private Color descriptionTextColor = new Color(120, 123, 154);
    private Color descriptionBackgroundColor = new Color(226, 228, 229);
    private JPanel searchPanel = new JPanel();
    private JPanel toolBarPanel = new JPanel();
    private JPanel toolPanel = new JPanel();
    private JTextField startText;
    private JTextField endText;
    private JTextField stuempNoText;
    private JTextField custNameText;

    public DetailPage() {
        init();
    }

    public void initTable() {
        DefaultTableModel model = new DefaultTableModel();
        model.addColumn("学工号");
        model.addColumn("姓名");
        model.addColumn("班级");
        model.addColumn("火车票（元）");
        model.addColumn("汽车票（元）");
        model.addColumn("证件费（元）");
        model.addColumn("其它一（元）");
        model.addColumn("其它二（元）");
        model.addColumn("合计（元）");
        model.addColumn("日期");
        model.addColumn("交易参考号");
        this.table.setModel(model);
    }

    public static DetailPage getInstance() {
        DetailPage page = new DetailPage();
        return page;
    }

    private void initSearchPanel() {
        this.add(searchPanel, BorderLayout.NORTH);
        searchPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));

        searchPanel.add(new JLabel("学工号："));
        stuempNoText = new JTextField(16);
        searchPanel.add(stuempNoText);
        searchPanel.add(new JLabel("姓名："));
        custNameText = new JTextField(16);
        searchPanel.add(custNameText);

        searchPanel.add(new JLabel("开始日期："));
        startText = new JTextField(12);
        startText.setEditable(false);
        startText.setFocusable(false);
        searchPanel.add(startText);
        JButton startImg = new FreeToolbarButton(FreeUtil.getImageIcon("images/date.png"));
        searchPanel.add(startImg);
        DateChooser startDate = new DateChooser("yyyyMMdd", startText, startImg);
        searchPanel.add(new JLabel("结束日期："));
        endText = new JTextField(12);
        endText.setEditable(false);
        endText.setFocusable(false);
        searchPanel.add(endText);
        JButton endImg = new FreeToolbarButton(FreeUtil.getImageIcon("images/date.png"));
        searchPanel.add(endImg);
        DateChooser endDate = new DateChooser("yyyyMMdd", endText, endImg);
        JButton searchBtn = new JButton("查  找");
        searchBtn.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        searchBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                reportAction(e);
            }
        });
        searchPanel.add(searchBtn);
    }

    private void initToolPanel() {
        this.getCenterPane().add(toolBarPanel, BorderLayout.NORTH);
        this.toolBarPanel.setLayout(new BorderLayout());
        this.toolBarPanel.setBackground(descriptionBackgroundColor);

        this.lbDescription.setForeground(descriptionTextColor);
        this.lbDescription.setBackground(descriptionBackgroundColor);
        this.lbDescription.setOpaque(true);
        this.lbDescription.setBorder(descriptionBorder);
        lbDescription.setEditable(false);
        lbDescription.setFont(FreeUtil.FONT_12_BOLD);

        toolPanel.setLayout(new FlowLayout());
        JButton excelBtn = new FreeToolbarButton(FreeUtil.getImageIcon("images/xls.gif"));
        excelBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                exportAction(e);
            }
        });
        toolPanel.add(excelBtn);
        toolPanel.setBackground(descriptionBackgroundColor);

        this.toolBarPanel.add(lbDescription, BorderLayout.WEST);
        this.toolBarPanel.add(toolPanel, BorderLayout.EAST);
    }

    private void exportAction(ActionEvent e) {
        File file = ExportUtil.saveAs(this);
        try {
            if (file != null) {
                ExportUtil.exportExcel(file, this.table.getModel());
                JOptionPane.showMessageDialog(this, "导出成功", "Info", JOptionPane.INFORMATION_MESSAGE);
            }
        } catch (IOException ex) {
            logger.error(ex);
            JOptionPane.showMessageDialog(this, "导出失败", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    /**
     * 查找办证大厅收费记录
     *
     * @param e .
     */
    private void reportAction(ActionEvent e) {
        String stuempno = stuempNoText.getText();
        String custname = custNameText.getText();
        String startDate = startText.getText();
        String endDate = endText.getText();

        initTable();
        DefaultTableModel model = (DefaultTableModel) this.table.getModel();
        try {
            List<Payrecord> recordList = PayrecordService.findPayrecordDetail(stuempno, custname, startDate, endDate);
            for (Payrecord payrecord : recordList) {
                Vector row = new Vector();
                row.add(payrecord.getStuempno());
                row.add(payrecord.getCustname());
                row.add(payrecord.getClassName());
                row.add(payrecord.getMedicineFee());
                row.add(payrecord.getDressingFee());
                row.add(payrecord.getInjectionFee());
                row.add(payrecord.getVaccineFee());
                row.add(payrecord.getOtherFee());
                row.add(payrecord.getTotalFee());
                row.add(payrecord.getTransDate());
                row.add(payrecord.getRefno());
                model.addRow(row);
            }
            this.setDescription("共" + recordList.size() + "条记录。");
        } catch (Exception ex) {
            JOptionPane.showMessageDialog(this, "查询失败", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void init() {
        initSearchPanel();
        initToolPanel();
        initTable();
        scroll.setBorder(BorderFactory.createEmptyBorder(0, 0, 0, 0));
        this.getCenterPane().add(scroll, BorderLayout.CENTER);

        JLabel lbCorner = new JLabel();
        lbCorner.setOpaque(true);
        lbCorner.setBackground(descriptionBackgroundColor);
        this.scroll.setCorner(ScrollPaneConstants.UPPER_RIGHT_CORNER, lbCorner);
    }

    public void setDescription(String description) {
        this.lbDescription.setText(description);
    }

    public JTable getTable() {
        return table;
    }
}