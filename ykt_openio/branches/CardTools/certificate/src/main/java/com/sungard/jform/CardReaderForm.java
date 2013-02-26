/*
 * Created by JFormDesigner on Fri Jul 22 11:41:05 CST 2011
 */

package com.sungard.jform;

import com.sungard.card.KsCardInterfaceUtil;
import org.apache.commons.lang.StringUtils;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.WindowConstants;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import java.awt.Container;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Properties;

/**
 * @author yiming you
 */
public class CardReaderForm extends JFrame {
    private boolean openPort = false;

    private Properties result = new Properties();

    public CardReaderForm() {
        initComponents();
    }

    private void button6ActionPerformed(ActionEvent e) {
        JButton source = (JButton) e.getSource();
        if (openPort) {
            if (KsCardInterfaceUtil.ksClosePort()) {
                source.setText("打开端口");
                openPort = false;
            } else {
                JOptionPane.showMessageDialog(CardReaderForm.this, "关闭端口失败", "Error", JOptionPane.ERROR_MESSAGE);
            }
        } else {
            String port = comboBox1.getSelectedItem().toString();
            String baud = comboBox2.getSelectedItem().toString();
            if (StringUtils.isEmpty(port) || StringUtils.isEmpty(baud)) {
                JOptionPane.showMessageDialog(CardReaderForm.this, "请选择端口和波特率", "Warning", JOptionPane.WARNING_MESSAGE);
            } else {
                if (KsCardInterfaceUtil.ksOpenPort(Integer.parseInt(port), Integer.parseInt(baud))) {
                    source.setText("关闭端口");
                    openPort = true;
                } else {
                    JOptionPane.showMessageDialog(CardReaderForm.this, "打开端口失败", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        }
    }

    private void button2ActionPerformed(ActionEvent e) {
        if (KsCardInterfaceUtil.ksSignIn(result)) {
            String shopId = result.getProperty("shopId");
            String shopName = result.getProperty("shopName");
            textField1.setText(shopId);
            textField2.setText(shopName);
            JOptionPane.showMessageDialog(CardReaderForm.this, "读卡器签到成功[商户ID=" + shopId + ",商户名称=" + shopName + "]", "Info", JOptionPane.INFORMATION_MESSAGE);
        } else {
            String errMsg = result.getProperty("errMsg");
            JOptionPane.showMessageDialog(CardReaderForm.this, "读卡器签到失败[" + errMsg + "]", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void button1ActionPerformed(ActionEvent e) {
        KsCardInterfaceUtil.ksReset();
        KsCardInterfaceUtil.ksSetReadFieldName("CARDNO");
        KsCardInterfaceUtil.ksSetReadFieldName("SHOWCARDNO");
        KsCardInterfaceUtil.ksSetReadFieldName("FEETYPE");
        KsCardInterfaceUtil.ksSetReadFieldName("CARDSTATUS");
        KsCardInterfaceUtil.ksSetReadFieldName("EXPIREDATE");
        KsCardInterfaceUtil.ksSetReadFieldName("STUEMPNO");
        KsCardInterfaceUtil.ksSetReadFieldName("NAME");
        KsCardInterfaceUtil.ksSetReadFieldName("SEX");
        KsCardInterfaceUtil.ksSetReadFieldName("DEPTCODE");
        KsCardInterfaceUtil.ksSetReadFieldName("IDNO");
        KsCardInterfaceUtil.ksSetReadFieldName("IDTYPE");
        KsCardInterfaceUtil.ksSetReadFieldName("CARDBAL");
        KsCardInterfaceUtil.ksSetReadFieldName("PAYCNT");
        KsCardInterfaceUtil.ksSetReadFieldName("DPSCNT");
        KsCardInterfaceUtil.ksReadCard();
        KsCardInterfaceUtil.ksGetFieldVal("CARDNO", result);
        KsCardInterfaceUtil.ksGetFieldVal("SHOWCARDNO", result);
        KsCardInterfaceUtil.ksGetFieldVal("FEETYPE", result);
        KsCardInterfaceUtil.ksGetFieldVal("CARDSTATUS", result);
        KsCardInterfaceUtil.ksGetFieldVal("EXPIREDATE", result);
        KsCardInterfaceUtil.ksGetFieldVal("STUEMPNO", result);
        KsCardInterfaceUtil.ksGetFieldVal("NAME", result);
        KsCardInterfaceUtil.ksGetFieldVal("SEX", result);
        KsCardInterfaceUtil.ksGetFieldVal("DEPTCODE", result);
        KsCardInterfaceUtil.ksGetFieldVal("IDNO", result);
        KsCardInterfaceUtil.ksGetFieldVal("IDTYPE", result);
        KsCardInterfaceUtil.ksGetFieldVal("CARDBAL", result);
        KsCardInterfaceUtil.ksGetFieldVal("PAYCNT", result);
        KsCardInterfaceUtil.ksGetFieldVal("DPSCNT", result);

        label44.setText(result.getProperty("CARDNO"));
        label43.setText(result.getProperty("SHOWCARDNO"));
        label39.setText(result.getProperty("STUEMPNO"));
        label38.setText(result.getProperty("NAME"));
        label37.setText(result.getProperty("DEPTCODE"));
        label36.setText(result.getProperty("IDNO"));
        label35.setText(result.getProperty("IDTYPE"));
        label34.setText(result.getProperty("CARDSTATUS"));
        label33.setText(result.getProperty("EXPIREDATE"));
        label32.setText(result.getProperty("FEETYPE"));
        label31.setText(result.getProperty("SEX"));
        label30.setText(result.getProperty("CARDBAL"));
        label29.setText(result.getProperty("DPSCNT"));
        label28.setText(result.getProperty("PAYCNT"));

        textField3.setText(result.getProperty("CARDBAL"));

        dialog1.setVisible(true);
    }

    private void button7ActionPerformed(ActionEvent e) {
        dialog1.dispose();
    }

    private void button3ActionPerformed(ActionEvent e) {
        String tramsAmt = textField4.getText();
        if (StringUtils.isBlank(tramsAmt)) {
            JOptionPane.showMessageDialog(CardReaderForm.this, "请输入扣款金额", "Warning", JOptionPane.WARNING_MESSAGE);
        } else {
            KsCardInterfaceUtil.ksRequestCard(result);
            String cardPhyId = result.getProperty("cardPhyId");
            int cardno = Integer.parseInt(result.getProperty("CARDNO"));
            int cardBal = Integer.parseInt(result.getProperty("CARDBAL"));
            int payCnt = Integer.parseInt(result.getProperty("PAYCNT"));
            KsCardInterfaceUtil.ksPayPrepare(cardPhyId, cardno, cardBal, payCnt, Integer.parseInt(tramsAmt), result);
            KsCardInterfaceUtil.ksCardBalanceDec(result);
            KsCardInterfaceUtil.ksPayProcess(result);
            String refNo = result.getProperty("refNo");
            String mac = result.getProperty("mac");
            textField5.setText(refNo);
            textField6.setText(mac);

            KsCardInterfaceUtil.getFieldValue("CARDBAL", result);
            textField3.setText(result.getProperty("CARDBAL"));

            KsCardInterfaceUtil.ksBeep();
        }
    }

    private void button4ActionPerformed(ActionEvent e) {
        int cardno = Integer.parseInt(result.getProperty("CARDNO"));
        int cardBal = Integer.parseInt(result.getProperty("CARDBAL"));
        KsCardInterfaceUtil.getFieldValue("DPSCNT", result);
        int dpsCnt = Integer.parseInt(result.getProperty("DPSCNT"));
        String refNo = textField5.getText();
        String mac = textField6.getText();
        KsCardInterfaceUtil.ksRequestCard(result);
        String cardPhyId = result.getProperty("cardPhyId");
        KsCardInterfaceUtil.ksPayCancelProcess(refNo, mac, cardPhyId, cardno, cardBal, dpsCnt,result);
        KsCardInterfaceUtil.ksCardBalanceDec(result);
        KsCardInterfaceUtil.ksPayProcess(result);
        textField7.setText(String.valueOf(cardBal));
        KsCardInterfaceUtil.getFieldValue("CARDBAL", result);
        textField8.setText(result.getProperty("CARDBAL"));

        KsCardInterfaceUtil.ksBeep();
    }

    private void initComponents() {
        // JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
        // Generated using JFormDesigner Evaluation license - yiming you
        panel2 = new JPanel();
        panel4 = new JPanel();
        panel6 = new JPanel();
        label9 = new JLabel();
        comboBox1 = new JComboBox();
        label10 = new JLabel();
        comboBox2 = new JComboBox();
        panel5 = new JPanel();
        button6 = new JButton();
        panel3 = new JPanel();
        button1 = new JButton();
        button2 = new JButton();
        button3 = new JButton();
        button4 = new JButton();
        button5 = new JButton();
        panel1 = new JPanel();
        label1 = new JLabel();
        textField1 = new JTextField();
        label2 = new JLabel();
        textField2 = new JTextField();
        label3 = new JLabel();
        textField3 = new JTextField();
        label4 = new JLabel();
        textField4 = new JTextField();
        label5 = new JLabel();
        textField5 = new JTextField();
        label6 = new JLabel();
        textField6 = new JTextField();
        label7 = new JLabel();
        textField7 = new JTextField();
        label8 = new JLabel();
        textField8 = new JTextField();
        dialog1 = new JDialog();
        label11 = new JLabel();
        label44 = new JLabel();
        label12 = new JLabel();
        label43 = new JLabel();
        label13 = new JLabel();
        label42 = new JLabel();
        label14 = new JLabel();
        label41 = new JLabel();
        label15 = new JLabel();
        label40 = new JLabel();
        label16 = new JLabel();
        label39 = new JLabel();
        label17 = new JLabel();
        label38 = new JLabel();
        label18 = new JLabel();
        label37 = new JLabel();
        label19 = new JLabel();
        label36 = new JLabel();
        label20 = new JLabel();
        label35 = new JLabel();
        label21 = new JLabel();
        label34 = new JLabel();
        label22 = new JLabel();
        label33 = new JLabel();
        label23 = new JLabel();
        label32 = new JLabel();
        label24 = new JLabel();
        label31 = new JLabel();
        label25 = new JLabel();
        label30 = new JLabel();
        label26 = new JLabel();
        label29 = new JLabel();
        label27 = new JLabel();
        label28 = new JLabel();
        button7 = new JButton();

        //======== this ========
        setResizable(false);
        setTitle("KsCardInterFaceDemo");
        setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        setFont(new Font("\u5fae\u8f6f\u96c5\u9ed1", Font.PLAIN, 12));
        Container contentPane = getContentPane();
        contentPane.setLayout(new GridBagLayout());
        ((GridBagLayout) contentPane.getLayout()).columnWidths = new int[]{10, 205, 250, 0};
        ((GridBagLayout) contentPane.getLayout()).rowHeights = new int[]{0, 0};
        ((GridBagLayout) contentPane.getLayout()).columnWeights = new double[]{0.0, 0.0, 0.0, 1.0E-4};
        ((GridBagLayout) contentPane.getLayout()).rowWeights = new double[]{1.0, 1.0E-4};

        //======== panel2 ========
        {

            // JFormDesigner evaluation mark
            panel2.setBorder(new javax.swing.border.CompoundBorder(
                    new javax.swing.border.TitledBorder(new javax.swing.border.EmptyBorder(0, 0, 0, 0),
                            "JFormDesigner Evaluation", javax.swing.border.TitledBorder.CENTER,
                            javax.swing.border.TitledBorder.BOTTOM, new java.awt.Font("Dialog", java.awt.Font.BOLD, 12),
                            java.awt.Color.red), panel2.getBorder()));
            panel2.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
                public void propertyChange(java.beans.PropertyChangeEvent e) {
                    if ("border".equals(e.getPropertyName())) throw new RuntimeException();
                }
            });

            panel2.setLayout(new GridBagLayout());
            ((GridBagLayout) panel2.getLayout()).columnWidths = new int[]{0, 0};
            ((GridBagLayout) panel2.getLayout()).rowHeights = new int[]{130, 0, 0};
            ((GridBagLayout) panel2.getLayout()).columnWeights = new double[]{1.0, 1.0E-4};
            ((GridBagLayout) panel2.getLayout()).rowWeights = new double[]{0.0, 1.0, 1.0E-4};

            //======== panel4 ========
            {
                panel4.setBorder(new CompoundBorder(
                        new TitledBorder("\u8bfb\u5361\u7aef\u53e3"),
                        new EmptyBorder(10, 5, 5, 5)));
                panel4.setLayout(new GridBagLayout());
                ((GridBagLayout) panel4.getLayout()).columnWidths = new int[]{0, 0};
                ((GridBagLayout) panel4.getLayout()).rowHeights = new int[]{56, 0, 0};
                ((GridBagLayout) panel4.getLayout()).columnWeights = new double[]{1.0, 1.0E-4};
                ((GridBagLayout) panel4.getLayout()).rowWeights = new double[]{0.0, 1.0, 1.0E-4};

                //======== panel6 ========
                {
                    panel6.setLayout(new GridBagLayout());
                    ((GridBagLayout) panel6.getLayout()).columnWidths = new int[]{65, 0, 0};
                    ((GridBagLayout) panel6.getLayout()).rowHeights = new int[]{27, 22, 0};
                    ((GridBagLayout) panel6.getLayout()).columnWeights = new double[]{0.0, 1.0, 1.0E-4};
                    ((GridBagLayout) panel6.getLayout()).rowWeights = new double[]{0.0, 0.0, 1.0E-4};

                    //---- label9 ----
                    label9.setText("\u7aef\u53e3\u53f7");
                    panel6.add(label9, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0,
                            GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                            new Insets(0, 0, 5, 5), 0, 0));

                    //---- comboBox1 ----
                    comboBox1.setEditable(true);
                    comboBox1.setModel(new DefaultComboBoxModel(new String[]{
                            "100",
                            "COM3"
                    }));
                    comboBox1.setSelectedIndex(0);
                    panel6.add(comboBox1, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0,
                            GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                            new Insets(0, 0, 5, 0), 0, 0));

                    //---- label10 ----
                    label10.setText("\u6ce2\u7279\u7387");
                    panel6.add(label10, new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0,
                            GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                            new Insets(0, 0, 0, 5), 0, 0));

                    //---- comboBox2 ----
                    comboBox2.setEditable(true);
                    comboBox2.setModel(new DefaultComboBoxModel(new String[]{
                            "115200",
                            "19200",
                            "38400",
                            "9600"
                    }));
                    panel6.add(comboBox2, new GridBagConstraints(1, 1, 1, 1, 0.0, 0.0,
                            GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                            new Insets(0, 0, 0, 0), 0, 0));
                }
                panel4.add(panel6, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0,
                        GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                        new Insets(0, 0, 5, 0), 0, 0));

                //======== panel5 ========
                {
                    panel5.setLayout(new GridBagLayout());
                    ((GridBagLayout) panel5.getLayout()).columnWidths = new int[]{85, 0, 0};
                    ((GridBagLayout) panel5.getLayout()).rowHeights = new int[]{0, 0};
                    ((GridBagLayout) panel5.getLayout()).columnWeights = new double[]{0.0, 1.0, 1.0E-4};
                    ((GridBagLayout) panel5.getLayout()).rowWeights = new double[]{0.0, 1.0E-4};

                    //---- button6 ----
                    button6.setText("\u6253\u5f00\u7aef\u53e3");
                    button6.setMaximumSize(new Dimension(80, 23));
                    button6.setMinimumSize(new Dimension(80, 23));
                    button6.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                    button6.addActionListener(new ActionListener() {
                        public void actionPerformed(ActionEvent e) {
                            button6ActionPerformed(e);
                        }
                    });
                    panel5.add(button6, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0,
                            GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                            new Insets(0, 0, 0, 5), 0, 0));
                }
                panel4.add(panel5, new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0,
                        GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                        new Insets(0, 0, 0, 0), 0, 0));
            }
            panel2.add(panel4, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 0), 0, 0));

            //======== panel3 ========
            {
                panel3.setLayout(new GridBagLayout());
                ((GridBagLayout) panel3.getLayout()).columnWidths = new int[]{10, 85, 0, 0};
                ((GridBagLayout) panel3.getLayout()).rowHeights = new int[]{0, 0, 0, 0, 0, 0};
                ((GridBagLayout) panel3.getLayout()).columnWeights = new double[]{0.0, 0.0, 1.0, 1.0E-4};
                ((GridBagLayout) panel3.getLayout()).rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-4};

                //---- button1 ----
                button1.setText("\u8bfb\u53d6\u5361\u4fe1\u606f");
                button1.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                button1.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        button1ActionPerformed(e);
                    }
                });
                panel3.add(button1, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0,
                        GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                        new Insets(0, 0, 5, 5), 0, 0));

                //---- button2 ----
                button2.setText("\u8bfb\u5361\u5668\u7b7e\u5230");
                button2.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                button2.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        button2ActionPerformed(e);
                    }
                });
                panel3.add(button2, new GridBagConstraints(1, 1, 1, 1, 0.0, 0.0,
                        GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                        new Insets(0, 0, 5, 5), 0, 0));

                //---- button3 ----
                button3.setText("\u6263\u6b3e");
                button3.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                button3.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        button3ActionPerformed(e);
                    }
                });
                panel3.add(button3, new GridBagConstraints(1, 2, 1, 1, 0.0, 0.0,
                        GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                        new Insets(0, 0, 5, 5), 0, 0));

                //---- button4 ----
                button4.setText("\u6263\u6b3e\u51b2\u6b63");
                button4.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                button4.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        button4ActionPerformed(e);
                    }
                });
                panel3.add(button4, new GridBagConstraints(1, 3, 1, 1, 0.0, 0.0,
                        GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                        new Insets(0, 0, 5, 5), 0, 0));

                //---- button5 ----
                button5.setText("\u8bfb\u5bc6\u94a5\u5361");
                button5.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
                panel3.add(button5, new GridBagConstraints(1, 4, 1, 1, 0.0, 0.0,
                        GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                        new Insets(0, 0, 0, 5), 0, 0));
            }
            panel2.add(panel3, new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 0, 0), 0, 0));
        }
        contentPane.add(panel2, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0,
                GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                new Insets(0, 0, 0, 5), 0, 0));

        //======== panel1 ========
        {
            panel1.setBorder(new CompoundBorder(
                    new TitledBorder("\u663e\u793a\u533a"),
                    new EmptyBorder(20, 20, 20, 20)));
            panel1.setLayout(new GridBagLayout());
            ((GridBagLayout) panel1.getLayout()).columnWidths = new int[]{85, 0, 0};
            ((GridBagLayout) panel1.getLayout()).rowHeights = new int[]{0, 0, 0, 0, 0, 0, 0, 0, 0};
            ((GridBagLayout) panel1.getLayout()).columnWeights = new double[]{0.0, 1.0, 1.0E-4};
            ((GridBagLayout) panel1.getLayout()).rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-4};

            //---- label1 ----
            label1.setText("\u5546\u6237\u53f7");
            panel1.add(label1, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 10));

            //---- textField1 ----
            textField1.setEditable(false);
            panel1.add(textField1, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 0), 0, 0));

            //---- label2 ----
            label2.setText("\u5546\u6237\u540d\u79f0");
            panel1.add(label2, new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 10));

            //---- textField2 ----
            textField2.setEditable(false);
            panel1.add(textField2, new GridBagConstraints(1, 1, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 0), 0, 0));

            //---- label3 ----
            label3.setText("\u5361\u4f59\u989d");
            panel1.add(label3, new GridBagConstraints(0, 2, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 10));

            //---- textField3 ----
            textField3.setEditable(false);
            panel1.add(textField3, new GridBagConstraints(1, 2, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 0), 0, 0));

            //---- label4 ----
            label4.setText("\u6263\u6b3e\u91d1\u989d");
            panel1.add(label4, new GridBagConstraints(0, 3, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 10));
            panel1.add(textField4, new GridBagConstraints(1, 3, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 0), 0, 0));

            //---- label5 ----
            label5.setText("\u4ea4\u6613\u53c2\u8003\u53f7");
            panel1.add(label5, new GridBagConstraints(0, 4, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 10));
            panel1.add(textField5, new GridBagConstraints(1, 4, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 0), 0, 0));

            //---- label6 ----
            label6.setText("MAC\u6821\u9a8c\u7801");
            panel1.add(label6, new GridBagConstraints(0, 5, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 10));
            panel1.add(textField6, new GridBagConstraints(1, 5, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 0), 0, 0));

            //---- label7 ----
            label7.setText("\u51b2\u6b63\u524d\u4f59\u989d");
            panel1.add(label7, new GridBagConstraints(0, 6, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 10));

            //---- textField7 ----
            textField7.setEditable(false);
            panel1.add(textField7, new GridBagConstraints(1, 6, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 0), 0, 0));

            //---- label8 ----
            label8.setText("\u51b2\u6b63\u540e\u4f59\u989d");
            panel1.add(label8, new GridBagConstraints(0, 7, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 0, 5), 0, 10));

            //---- textField8 ----
            textField8.setEditable(false);
            panel1.add(textField8, new GridBagConstraints(1, 7, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 0, 0), 0, 0));
        }
        contentPane.add(panel1, new GridBagConstraints(2, 0, 1, 1, 0.0, 0.0,
                GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                new Insets(0, 0, 0, 0), 0, 0));
        pack();
        setLocationRelativeTo(getOwner());

        //======== dialog1 ========
        {
            dialog1.setTitle("\u5361\u4fe1\u606f");
            dialog1.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
            dialog1.setResizable(false);
            dialog1.setModal(true);
            Container dialog1ContentPane = dialog1.getContentPane();
            dialog1ContentPane.setLayout(new GridBagLayout());
            ((GridBagLayout) dialog1ContentPane.getLayout()).columnWidths = new int[]{20, 85, 125, 15};
            ((GridBagLayout) dialog1ContentPane.getLayout()).rowHeights = new int[]{20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0};
            ((GridBagLayout) dialog1ContentPane.getLayout()).rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E-4};

            //---- label11 ----
            label11.setText("\u4ea4\u6613\u5361\u53f7");
            dialog1ContentPane.add(label11, new GridBagConstraints(1, 1, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label44, new GridBagConstraints(2, 1, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label12 ----
            label12.setText("\u663e\u793a\u5361\u53f7");
            dialog1ContentPane.add(label12, new GridBagConstraints(1, 2, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label43, new GridBagConstraints(2, 2, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label13 ----
            label13.setText("\u5361\u7c7b\u522b");
            dialog1ContentPane.add(label13, new GridBagConstraints(1, 3, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label42, new GridBagConstraints(2, 3, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label14 ----
            label14.setText("\u5ba2\u6237\u53f7");
            dialog1ContentPane.add(label14, new GridBagConstraints(1, 4, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label41, new GridBagConstraints(2, 4, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label15 ----
            label15.setText("\u5ba2\u6237\u7c7b\u522b");
            dialog1ContentPane.add(label15, new GridBagConstraints(1, 5, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label40, new GridBagConstraints(2, 5, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label16 ----
            label16.setText("\u5b66\u5de5\u53f7");
            dialog1ContentPane.add(label16, new GridBagConstraints(1, 6, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label39, new GridBagConstraints(2, 6, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label17 ----
            label17.setText("\u59d3\u540d");
            dialog1ContentPane.add(label17, new GridBagConstraints(1, 7, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label38, new GridBagConstraints(2, 7, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label18 ----
            label18.setText("\u90e8\u95e8\u4ee3\u7801");
            dialog1ContentPane.add(label18, new GridBagConstraints(1, 8, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label37, new GridBagConstraints(2, 8, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label19 ----
            label19.setText("\u8bc1\u4ef6\u53f7\u7801");
            dialog1ContentPane.add(label19, new GridBagConstraints(1, 9, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label36, new GridBagConstraints(2, 9, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label20 ----
            label20.setText("\u8bc1\u4ef6\u7c7b\u578b");
            dialog1ContentPane.add(label20, new GridBagConstraints(1, 10, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label35, new GridBagConstraints(2, 10, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label21 ----
            label21.setText("\u5361\u72b6\u6001");
            dialog1ContentPane.add(label21, new GridBagConstraints(1, 11, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label34, new GridBagConstraints(2, 11, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label22 ----
            label22.setText("\u8fc7\u671f\u65e5\u671f");
            dialog1ContentPane.add(label22, new GridBagConstraints(1, 12, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label33, new GridBagConstraints(2, 12, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label23 ----
            label23.setText("\u6536\u8d39\u7c7b\u522b");
            dialog1ContentPane.add(label23, new GridBagConstraints(1, 13, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label32, new GridBagConstraints(2, 13, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label24 ----
            label24.setText("\u6027\u522b");
            dialog1ContentPane.add(label24, new GridBagConstraints(1, 14, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label31, new GridBagConstraints(2, 14, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label25 ----
            label25.setText("\u5361\u4f59\u989d");
            dialog1ContentPane.add(label25, new GridBagConstraints(1, 15, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label30, new GridBagConstraints(2, 15, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label26 ----
            label26.setText("\u5145\u503c\u6b21\u6570");
            dialog1ContentPane.add(label26, new GridBagConstraints(1, 16, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label29, new GridBagConstraints(2, 16, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- label27 ----
            label27.setText("\u6d88\u8d39\u6b21\u6570");
            dialog1ContentPane.add(label27, new GridBagConstraints(1, 17, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1ContentPane.add(label28, new GridBagConstraints(2, 17, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));

            //---- button7 ----
            button7.setText("\u786e\u5b9a");
            button7.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
            button7.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    button7ActionPerformed(e);
                }
            });
            dialog1ContentPane.add(button7, new GridBagConstraints(2, 18, 1, 1, 0.0, 0.0,
                    GridBagConstraints.CENTER, GridBagConstraints.BOTH,
                    new Insets(0, 0, 5, 5), 0, 0));
            dialog1.pack();
            dialog1.setLocationRelativeTo(dialog1.getOwner());
        }
        // JFormDesigner - End of component initialization  //GEN-END:initComponents
    }

    // JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
    // Generated using JFormDesigner Evaluation license - yiming you
    private JPanel panel2;
    private JPanel panel4;
    private JPanel panel6;
    private JLabel label9;
    private JComboBox comboBox1;
    private JLabel label10;
    private JComboBox comboBox2;
    private JPanel panel5;
    private JButton button6;
    private JPanel panel3;
    private JButton button1;
    private JButton button2;
    private JButton button3;
    private JButton button4;
    private JButton button5;
    private JPanel panel1;
    private JLabel label1;
    private JTextField textField1;
    private JLabel label2;
    private JTextField textField2;
    private JLabel label3;
    private JTextField textField3;
    private JLabel label4;
    private JTextField textField4;
    private JLabel label5;
    private JTextField textField5;
    private JLabel label6;
    private JTextField textField6;
    private JLabel label7;
    private JTextField textField7;
    private JLabel label8;
    private JTextField textField8;
    private JDialog dialog1;
    private JLabel label11;
    private JLabel label44;
    private JLabel label12;
    private JLabel label43;
    private JLabel label13;
    private JLabel label42;
    private JLabel label14;
    private JLabel label41;
    private JLabel label15;
    private JLabel label40;
    private JLabel label16;
    private JLabel label39;
    private JLabel label17;
    private JLabel label38;
    private JLabel label18;
    private JLabel label37;
    private JLabel label19;
    private JLabel label36;
    private JLabel label20;
    private JLabel label35;
    private JLabel label21;
    private JLabel label34;
    private JLabel label22;
    private JLabel label33;
    private JLabel label23;
    private JLabel label32;
    private JLabel label24;
    private JLabel label31;
    private JLabel label25;
    private JLabel label30;
    private JLabel label26;
    private JLabel label29;
    private JLabel label27;
    private JLabel label28;
    private JButton button7;
    // JFormDesigner - End of variables declaration  //GEN-END:variables

    public static void main(String[] args) throws InterruptedException {
        CardReaderForm form = new CardReaderForm();
        form.setVisible(true);
    }
}
