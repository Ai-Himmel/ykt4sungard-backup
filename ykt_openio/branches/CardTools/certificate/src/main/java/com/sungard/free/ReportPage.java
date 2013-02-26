package com.sungard.free;

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
import java.math.BigDecimal;
import java.util.List;
import java.util.Map;
import java.util.Vector;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-17
 */
public class ReportPage extends FreePagePane {
    private static final Logger logger = Logger.getLogger(ReportPage.class);
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

    public ReportPage() {
        init();
    }

    public void initTable() {
        DefaultTableModel model = new DefaultTableModel();
        model.addColumn("编号");
        model.addColumn("日期");
        model.addColumn("人数");
        model.addColumn("人次");
        model.addColumn("火车票（元）");
        model.addColumn("汽车票（元）");
        model.addColumn("证件费（元）");
        model.addColumn("其它一（元）");
        model.addColumn("其它二（元）");
        model.addColumn("合计（元）");
        this.table.setModel(model);
    }

    public static ReportPage getInstance() {
        ReportPage page = new ReportPage();
        return page;
    }

    private void initSearchPanel() {
        this.add(searchPanel, BorderLayout.NORTH);
        searchPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));

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
        String startDate = startText.getText();
        String endDate = endText.getText();

        initTable();
        DefaultTableModel model = (DefaultTableModel) this.table.getModel();
        try {
            List<Map> result = PayrecordService.findPayrecordReport(startDate, endDate);
            int i = 1;
            BigDecimal sumMedicineFee = BigDecimal.valueOf(0);
            BigDecimal sumDressingFee = BigDecimal.valueOf(0);
            BigDecimal sumInjectionFee = BigDecimal.valueOf(0);
            BigDecimal sumVaccineFee = BigDecimal.valueOf(0);
            BigDecimal sumOtherFee = BigDecimal.valueOf(0);
            BigDecimal sumTotalFee = BigDecimal.valueOf(0);
            int sumPersonNumber = 0;
            int sumPayNumber = 0;

            for (Map map : result) {
                Vector row = new Vector();
                row.add(i++);
                row.add(map.get("transDate"));
                row.add(map.get("personNumber"));
                row.add(map.get("payNumber"));
                row.add(map.get("medicineFee"));
                row.add(map.get("dressingFee"));
                row.add(map.get("injectionFee"));
                row.add(map.get("vaccineFee"));
                row.add(map.get("otherFee"));
                row.add(map.get("totalFee"));
                model.addRow(row);
                sumMedicineFee = sumMedicineFee.add(BigDecimal.valueOf(Double.parseDouble(map.get("medicineFee").toString())));
                sumDressingFee = sumDressingFee.add(BigDecimal.valueOf(Double.parseDouble(map.get("dressingFee").toString())));
                sumInjectionFee = sumInjectionFee.add(BigDecimal.valueOf(Double.parseDouble(map.get("injectionFee").toString())));
                sumVaccineFee = sumVaccineFee.add(BigDecimal.valueOf(Double.parseDouble(map.get("vaccineFee").toString())));
                sumOtherFee = sumOtherFee.add(BigDecimal.valueOf(Double.parseDouble(map.get("otherFee").toString())));
                sumTotalFee = sumTotalFee.add(BigDecimal.valueOf(Double.parseDouble(map.get("totalFee").toString())));
                sumPersonNumber += Integer.parseInt(map.get("personNumber").toString());
                sumPayNumber += Integer.parseInt(map.get("payNumber").toString());
            }
            //添加统计行
            if (result.size() > 0) {
                Vector row = new Vector();
                row.add("总计");
                row.add("");
                row.add(sumPersonNumber);
                row.add(sumPayNumber);
                row.add(sumMedicineFee);
                row.add(sumDressingFee);
                row.add(sumInjectionFee);
                row.add(sumVaccineFee);
                row.add(sumOtherFee);
                row.add(sumTotalFee);
                model.addRow(row);
            }
            this.setDescription("共" + result.size() + "条记录。");

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