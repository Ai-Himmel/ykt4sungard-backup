package com.sungard.free;

import com.sungard.bean.Payrecord;
import com.sungard.card.KsCardInterfaceUtil;
import com.sungard.common.Configuration;
import com.sungard.common.Constant;
import com.sungard.print.AbstractDocument;
import com.sungard.print.PosDocument;
import com.sungard.print.Printer;
import com.sungard.service.PayrecordService;
import com.sungard.util.DateUtil;
import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.KeyStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.KeyboardFocusManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.KeyEvent;
import java.math.BigDecimal;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.Date;
import java.util.HashSet;
import java.util.Properties;
import java.util.Set;

/**
 * 医疗付费页面
 * User: Yiming.You
 * Date: 2011-9-16
 */
public class PaymentPage extends FreePagePane {
    private static final Logger logger = Logger.getLogger(PaymentPage.class);
    private JPanel centerPane;
    private JTextField stuempNoText;
    private JTextField custNameText;
    private JTextField balanceText;
    private JTextField medicineText;
    private JTextField dressingText;
    private JTextField injectionText;
    private JTextField vaccineText;
    private JTextField otherText;
    private JLabel medicineTipLabel;
    private JLabel dressingTipLabel;
    private JLabel injectionTipLabel;
    private JLabel vaccineTipLabel;
    private JLabel otherTipLabel;

    private JTextField totalText;
    private JTextField refNoText;
    private JTextField macText;
    private JButton readBtn;
    private JButton chargeBtn;
    private JButton reverseBtn;
    private NumberFormat feeFormat = NumberFormat.getNumberInstance();
    private Properties result = new Properties();

    public PaymentPage() {
        init();
    }

    private void init() {
        //use VK_ENTER to change focus
        Set forwardKeys = getFocusTraversalKeys(KeyboardFocusManager.FORWARD_TRAVERSAL_KEYS);
        Set newForwardKeys = new HashSet(forwardKeys);
        newForwardKeys.add(KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0));
        setFocusTraversalKeys(KeyboardFocusManager.FORWARD_TRAVERSAL_KEYS, newForwardKeys);

        setLayout(new BorderLayout());
        centerPane = new JPanel(new GridBagLayout());
        ((GridBagLayout) centerPane.getLayout()).columnWidths = new int[]{100, 160, 100};
        ((GridBagLayout) centerPane.getLayout()).rowHeights = new int[]{30, 30, 30, 30, 30, 30, 30, 30, 30, 30};
        add(centerPane, "Center");

        JLabel stuempNoLabel = new JLabel("学工号：");
        JLabel custNameLabel = new JLabel("姓   名：");
        JLabel balanceLabel = new JLabel("余   额：");
        JLabel medicineLabel = new JLabel("药   费（元）：");
        JLabel dressingLabel = new JLabel("敷料费（元）：");
        JLabel injectionLabel = new JLabel("注射费（元）：");
        JLabel vaccineLabel = new JLabel("疫   苗（元）：");
        JLabel otherLabel = new JLabel("其   它（元）：");
        JLabel totalLabel = new JLabel("合   计（元）：");
        JLabel refNoLabel = new JLabel("交易参考号：");
        JLabel macLabel = new JLabel("MAC校验码：");

        centerPane.add(stuempNoLabel, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(custNameLabel, new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(balanceLabel, new GridBagConstraints(0, 2, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(medicineLabel, new GridBagConstraints(0, 3, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(dressingLabel, new GridBagConstraints(0, 4, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(injectionLabel, new GridBagConstraints(0, 5, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(vaccineLabel, new GridBagConstraints(0, 6, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(otherLabel, new GridBagConstraints(0, 7, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(totalLabel, new GridBagConstraints(0, 8, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(refNoLabel, new GridBagConstraints(0, 9, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(macLabel, new GridBagConstraints(0, 10, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));

        stuempNoText = new JTextField();
        stuempNoText.setEditable(false);
        stuempNoText.setFocusable(false);
        custNameText = new JTextField();
        custNameText.setEditable(false);
        custNameText.setFocusable(false);
        balanceText = new JTextField();
        balanceText.setEditable(false);
        balanceText.setFocusable(false);
        feeFormat.setGroupingUsed(false);

        FocusListener verifyListener = getFocusListener();


        medicineText = new JTextField();
        medicineText.addFocusListener(verifyListener);
        dressingText = new JTextField();
        dressingText.addFocusListener(verifyListener);
        injectionText = new JTextField();
        injectionText.addFocusListener(verifyListener);
        vaccineText = new JTextField();
        vaccineText.addFocusListener(verifyListener);
        otherText = new JTextField();
        otherText.addFocusListener(verifyListener);
        totalText = new JTextField(10);
        totalText.setEditable(false);
        totalText.setFocusable(false);
        refNoText = new JTextField();
        refNoText.setEditable(false);
        refNoText.setFocusable(false);
        macText = new JTextField();
        macText.setEditable(false);
        macText.setFocusable(false);
        centerPane.add(stuempNoText, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(custNameText, new GridBagConstraints(1, 1, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(balanceText, new GridBagConstraints(1, 2, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(medicineText, new GridBagConstraints(1, 3, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(dressingText, new GridBagConstraints(1, 4, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(injectionText, new GridBagConstraints(1, 5, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(vaccineText, new GridBagConstraints(1, 6, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(otherText, new GridBagConstraints(1, 7, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(totalText, new GridBagConstraints(1, 8, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(refNoText, new GridBagConstraints(1, 9, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(macText, new GridBagConstraints(1, 10, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));


        medicineTipLabel = new JLabel("");
        dressingTipLabel = new JLabel("");
        injectionTipLabel = new JLabel("");
        vaccineTipLabel = new JLabel("");
        otherTipLabel = new JLabel("");

        centerPane.add(medicineTipLabel, new GridBagConstraints(2, 3, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.BOTH, new Insets(0, 10, 5, 5), 0, 0));
        centerPane.add(dressingTipLabel, new GridBagConstraints(2, 4, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.BOTH, new Insets(0, 10, 5, 5), 0, 0));
        centerPane.add(injectionTipLabel, new GridBagConstraints(2, 5, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.BOTH, new Insets(0, 10, 5, 5), 0, 0));
        centerPane.add(vaccineTipLabel, new GridBagConstraints(2, 6, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.BOTH, new Insets(0, 10, 5, 5), 0, 0));
        centerPane.add(otherTipLabel, new GridBagConstraints(2, 7, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.BOTH, new Insets(0, 10, 5, 5), 0, 0));


        readBtn = new JButton();
        readBtn.setText("读   卡");
        readBtn.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        readBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                readCardAction(e);
            }
        });
        centerPane.add(readBtn, new GridBagConstraints(2, 0, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 10, 5, 5), 0, 0));
        chargeBtn = new JButton();
        chargeBtn.setText("扣   款");
        chargeBtn.setEnabled(true);
        chargeBtn.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        chargeBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                chargeAction(e);
            }
        });
        //当焦点在扣款按钮上时，按下回车，相当于点击扣款按钮
//        chargeBtn.registerKeyboardAction(chargeBtn.getActionForKeyStroke(KeyStroke.getKeyStroke(KeyEvent.VK_SPACE, 0, false)), KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0, false), JComponent.WHEN_FOCUSED);
//        chargeBtn.registerKeyboardAction(chargeBtn.getActionForKeyStroke(KeyStroke.getKeyStroke(KeyEvent.VK_SPACE, 0, true)), KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0, true), JComponent.WHEN_FOCUSED);
        centerPane.add(chargeBtn, new GridBagConstraints(2, 8, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 10, 5, 5), 0, 0));
        reverseBtn = new JButton();
        reverseBtn.setText("冲   正");
        reverseBtn.setEnabled(false);
        reverseBtn.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        reverseBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                reverseAction(e);
            }
        });
//        centerPane.add(reverseBtn, new GridBagConstraints(2, 10, 1, 1, 0.0, 0.0, GridBagConstraints.EAST, GridBagConstraints.NONE, new Insets(0, 0, 0, 5), 0, 0));
    }

    public FocusListener getFocusListener() {
        return new FocusAdapter() {
            @Override
            public void focusLost(FocusEvent e) {
                sum();
            }
        };
    }

    public void sum() {
        //自动计算合计金额
        BigDecimal totalFee = BigDecimal.valueOf(0);
        if (verify(medicineText, medicineTipLabel) && StringUtils.isNotBlank(medicineText.getText())) {
            totalFee = totalFee.add(BigDecimal.valueOf(Double.parseDouble(medicineText.getText())));
        }
        if (verify(dressingText, dressingTipLabel) && StringUtils.isNotBlank(dressingText.getText())) {
            totalFee = totalFee.add(BigDecimal.valueOf(Double.parseDouble(dressingText.getText())));
        }
        if (verify(injectionText, injectionTipLabel) && StringUtils.isNotBlank(injectionText.getText())) {
            totalFee = totalFee.add(BigDecimal.valueOf(Double.parseDouble(injectionText.getText())));
        }
        if (verify(vaccineText, vaccineTipLabel) && StringUtils.isNotBlank(vaccineText.getText())) {
            totalFee = totalFee.add(BigDecimal.valueOf(Double.parseDouble(vaccineText.getText())));
        }
        if (verify(otherText, otherTipLabel) && StringUtils.isNotBlank(otherText.getText())) {
            totalFee = totalFee.add(BigDecimal.valueOf(Double.parseDouble(otherText.getText())));
        }
        totalText.setText(String.valueOf(totalFee));
    }

    public boolean verify(JTextField inputText, JLabel errorLabel) {
        boolean valid = false;
        try {
            if (StringUtils.isNotBlank(inputText.getText())) {
                Object value = feeFormat.parseObject(inputText.getText());
                inputText.setText(value.toString());
            }
            valid = true;
            errorLabel.setText("");
        } catch (ParseException e) {
            errorLabel.setForeground(Color.red);
            errorLabel.setText("请输入合法数字");
            inputText.requestFocusInWindow();
        }
        return valid;
    }

    /**
     * 读取卡信息
     *
     * @param e .
     */
    private void readCardAction(ActionEvent e) {
        boolean success;
        success = KsCardInterfaceUtil.ksRequestCard(result);
        KsCardInterfaceUtil.ksReset();
        KsCardInterfaceUtil.ksSetReadFieldName("CARDNO");
        KsCardInterfaceUtil.ksSetReadFieldName("STUEMPNO");
        KsCardInterfaceUtil.ksSetReadFieldName("NAME");
        KsCardInterfaceUtil.ksSetReadFieldName("CARDBAL");
        KsCardInterfaceUtil.ksSetReadFieldName("PAYCNT");
        KsCardInterfaceUtil.ksReadCard();
        KsCardInterfaceUtil.ksGetFieldVal("CARDNO", result);
        KsCardInterfaceUtil.ksGetFieldVal("STUEMPNO", result);
        KsCardInterfaceUtil.ksGetFieldVal("NAME", result);
        KsCardInterfaceUtil.ksGetFieldVal("CARDBAL", result);
        KsCardInterfaceUtil.ksGetFieldVal("PAYCNT", result);

        medicineText.setText("");
        dressingText.setText("");
        injectionText.setText("");
        vaccineText.setText("");
        otherText.setText("");
        totalText.setText("");
        refNoText.setText("");
        macText.setText("");
        medicineText.requestFocusInWindow();
        reverseBtn.setEnabled(false);
        if (success) {
            stuempNoText.setText(result.getProperty("STUEMPNO"));
            custNameText.setText(result.getProperty("NAME"));
            balanceText.setText(String.valueOf(Double.parseDouble(result.getProperty("CARDBAL")) / 100));
            chargeBtn.setEnabled(true);
            KsCardInterfaceUtil.ksBeep();
        } else {
            stuempNoText.setText("");
            custNameText.setText("");
            balanceText.setText("");
            chargeBtn.setEnabled(false);
            JOptionPane.showMessageDialog(this, "读取卡信息失败", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    /**
     * 扣款
     *
     * @param e .
     */
    private void chargeAction(ActionEvent e) {
        String tramsAmt = totalText.getText();
        if (StringUtils.isBlank(tramsAmt)) {
            JOptionPane.showMessageDialog(this, "请输入扣款金额", "Warning", JOptionPane.WARNING_MESSAGE);
        } else {
            int response = JOptionPane.showConfirmDialog(this, "应支付金额【" + tramsAmt + "元】，是否扣款？", "扣款确认", JOptionPane.YES_NO_OPTION);
            if (0 == response) {
                String cardPhyId = result.getProperty("cardPhyId");
                int cardno = Integer.parseInt(result.getProperty("CARDNO"));
                int cardBal = Integer.parseInt(result.getProperty("CARDBAL"));
                int payCnt = Integer.parseInt(result.getProperty("PAYCNT"));
                boolean success = false;
                BigDecimal payAmt = (new BigDecimal(tramsAmt)).multiply(new BigDecimal(100));
                logger.info("tramsAmt:"+String.valueOf(payAmt));
                if (KsCardInterfaceUtil.ksPayPrepare(cardPhyId, cardno, cardBal, payCnt, payAmt.intValue(), result)) {
                    if (KsCardInterfaceUtil.ksCardBalanceDec(result)) {
                        if (KsCardInterfaceUtil.ksPayProcess(result)) {
                            success = true;
                        }
                    }
                }
                if (success) {
                    String refNo = result.getProperty("refNo");
                    String mac = result.getProperty("mac");
                    refNoText.setText(refNo);
                    macText.setText(mac);
                    KsCardInterfaceUtil.getFieldValue("CARDBAL", result);
                    balanceText.setText(String.valueOf(Double.parseDouble(result.getProperty("CARDBAL")) / 100));
                    chargeBtn.setEnabled(false);
                    reverseBtn.setEnabled(true);
                    Payrecord payrecord = getPayrecord();
                    //1 扣款，0 冲正
                    payrecord.setTransType("1");
                    payrecord.setClassName(PayrecordService.findClassName(payrecord.getStuempno()));
                    if (PayrecordService.savePayrecord(payrecord)) {
                        KsCardInterfaceUtil.ksBeep();
                        //打印
                        String printable = Configuration.getProperty(Constant.PRINTABLE);
                        if ("true".equals(printable)) {
                            print(payrecord);
                        }
                    } else {
                        JOptionPane.showMessageDialog(this, "保存付费记录失败", "Error", JOptionPane.ERROR_MESSAGE);
                    }
                } else {
                	 String errMsg = result.getProperty("errMsg");
                    JOptionPane.showMessageDialog(this, "扣款失败,"+errMsg, "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        }
    }

    private void print(Payrecord payrecord) {
        Printer printer = new Printer();
        AbstractDocument document = new PosDocument();
        String content = "医药费收款单<br>学号：" + payrecord.getStuempno() + "<br>姓名：" + payrecord.getCustname() + "<br>班级：" + payrecord.getClassName()
                + "<br>药费：" + payrecord.getMedicineFee() + "元<br>敷料费:"
                + payrecord.getDressingFee() + "元<br>注射费:" + payrecord.getInjectionFee() + "元<br>疫苗:" + payrecord.getVaccineFee() + "元<br>其它:" + payrecord.getOtherFee()
                + "元<br>费用合计:" + payrecord.getTotalFee() + "元<br>扣款员:" + payrecord.getOperator() + "<br>日期:" + DateUtil.getDate_yyyymmddHHmm(new Date());
        document.addPage(content);
        printer.setDocument(document);
        boolean success = false;
        try {
            success = printer.print();
        } catch (Exception e) {
        }
        if (!success) {
            JOptionPane.showMessageDialog(this, "打印单据失败", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private Payrecord getPayrecord() {
        Payrecord payrecord = new Payrecord();
        payrecord.setCardno(Integer.parseInt(result.getProperty("CARDNO")));
        payrecord.setStuempno(stuempNoText.getText());
        payrecord.setCustname(custNameText.getText());
        payrecord.setMedicineFee(getDouble(medicineText.getText()));
        payrecord.setDressingFee(getDouble(dressingText.getText()));
        payrecord.setInjectionFee(getDouble(injectionText.getText()));
        payrecord.setVaccineFee(getDouble(vaccineText.getText()));
        payrecord.setOtherFee(getDouble(otherText.getText()));
        payrecord.setTotalFee(getDouble(totalText.getText()));
        payrecord.setOperator(Configuration.getProperty(Constant.OPER_CODE));
        payrecord.setTransDate(DateUtil.getCurDateStrYYYYMMDD());
        payrecord.setTransTime("");
        payrecord.setRefno(refNoText.getText());
        payrecord.setMac(macText.getText());
        return payrecord;
    }

    private Double getDouble(String text) {
        if (StringUtils.isBlank(text)) {
            return Double.valueOf(0);
        } else {
            return Double.valueOf(text);
        }
    }

    /**
     * 冲正
     *
     * @param e .
     */
    private void reverseAction(ActionEvent e) {
        int cardno = Integer.parseInt(result.getProperty("CARDNO"));
        int cardBal = Integer.parseInt(result.getProperty("CARDBAL"));
        KsCardInterfaceUtil.getFieldValue("DPSCNT", result);
        int dpsCnt = Integer.parseInt(result.getProperty("DPSCNT"));
        String refNo = refNoText.getText();
        String mac = macText.getText();
        if (KsCardInterfaceUtil.ksRequestCard(result)) {
            String cardPhyId = result.getProperty("cardPhyId");
            boolean success = false;
            if (KsCardInterfaceUtil.ksPayCancelProcess(refNo, mac, cardPhyId, cardno, cardBal, dpsCnt,result)) {
                if (KsCardInterfaceUtil.ksCardBalanceDec(result)) {
                    if (KsCardInterfaceUtil.ksPayProcess(result)) {
                        success = true;
                    }
                }
            }
            KsCardInterfaceUtil.getFieldValue("CARDBAL", result);
            if (success) {
                balanceText.setText(String.valueOf(Double.parseDouble(result.getProperty("CARDBAL")) / 100));
                reverseBtn.setEnabled(false);
                Payrecord payrecord = getPayrecord();
                //1 扣款，0 冲正
                payrecord.setTransType("0");
                if (PayrecordService.savePayrecord(payrecord)) {
                    KsCardInterfaceUtil.ksBeep();
                } else {
                    JOptionPane.showMessageDialog(this, "保存付费记录失败", "Error", JOptionPane.ERROR_MESSAGE);
                }
            } else {
                String errMsg = result.getProperty("errMsg");
                JOptionPane.showMessageDialog(this, "冲正失败,"+errMsg, "Error", JOptionPane.ERROR_MESSAGE);
            }
        } else {
            JOptionPane.showMessageDialog(this, "寻卡失败", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
}
