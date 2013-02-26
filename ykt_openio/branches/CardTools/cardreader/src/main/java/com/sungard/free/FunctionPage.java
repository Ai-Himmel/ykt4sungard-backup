package com.sungard.free;

import com.sungard.card.KsCardInterfaceUtil;
import org.apache.commons.lang.StringUtils;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import java.awt.BorderLayout;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Properties;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-16
 */
public class FunctionPage extends FreePagePane {
    private JPanel centerPane;
    private boolean openPort = false;
    private JComboBox portBox;
    private JComboBox baudBox;
    private JTextField shopIdText;
    private JTextField shopNameText;
    private Properties result = new Properties();

    public FunctionPage() {
        init();
    }

    private void init() {
        setLayout(new BorderLayout());
        centerPane = new JPanel(new GridBagLayout());
        ((GridBagLayout) centerPane.getLayout()).columnWidths = new int[]{80, 160};
        ((GridBagLayout) centerPane.getLayout()).rowHeights = new int[]{30, 30, 30, 30, 30};
        add(centerPane, "Center");

        JLabel portLabel = new JLabel("端口号：");
        JLabel baudLabel = new JLabel("波特率：");
        centerPane.add(portLabel, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(baudLabel, new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));

        portBox = new JComboBox();
        portBox.setEditable(true);
        portBox.setModel(new DefaultComboBoxModel(new String[]{"100"}));
        portBox.setSelectedIndex(0);
        centerPane.add(portBox, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        baudBox = new JComboBox();
        baudBox.setEditable(true);
        baudBox.setModel(new DefaultComboBoxModel(new String[]{"115200", "19200", "38400", "9600"}));
        centerPane.add(baudBox, new GridBagConstraints(1, 1, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));

        JLabel shopIdLabel = new JLabel("商户号：");
        JLabel shopNameLabel = new JLabel("商户名称：");
        centerPane.add(shopIdLabel, new GridBagConstraints(0, 2, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(shopNameLabel, new GridBagConstraints(0, 3, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        shopIdText = new JTextField();
        shopIdText.setEditable(false);
        shopIdText.setFocusable(false);
        shopNameText = new JTextField();
        shopNameText.setEditable(false);
        shopNameText.setFocusable(false);
        centerPane.add(shopIdText, new GridBagConstraints(1, 2, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));
        centerPane.add(shopNameText, new GridBagConstraints(1, 3, 1, 1, 0.0, 0.0, GridBagConstraints.CENTER, GridBagConstraints.BOTH, new Insets(0, 0, 5, 5), 0, 0));

        JButton openPortBtn = new JButton();
        openPortBtn.setText("打开端口");
        openPortBtn.setMaximumSize(new Dimension(80, 23));
        openPortBtn.setMinimumSize(new Dimension(80, 23));
        openPortBtn.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        openPortBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                portAction(e);
            }
        });
        centerPane.add(openPortBtn, new GridBagConstraints(0, 4, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 0, 5, 5), 0, 0));

        JButton signBtn = new JButton();
        signBtn.setText("读卡器签到");
        signBtn.setMaximumSize(new Dimension(80, 23));
        signBtn.setMinimumSize(new Dimension(80, 23));
        signBtn.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        signBtn.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                signAction(e);
            }
        });
        centerPane.add(signBtn, new GridBagConstraints(1, 4, 1, 1, 0.0, 0.0, GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(0, 0, 5, 5), 0, 0));
    }

    private void portAction(ActionEvent e) {
        JButton source = (JButton) e.getSource();
        if (openPort) {
            if (KsCardInterfaceUtil.ksClosePort()) {
                source.setText("打开端口");
                openPort = false;
            } else {
                JOptionPane.showMessageDialog(this, "关闭端口失败", "Error", JOptionPane.ERROR_MESSAGE);
            }
        } else {
            String port = portBox.getSelectedItem().toString();
            String baud = baudBox.getSelectedItem().toString();
            if (StringUtils.isEmpty(port) || StringUtils.isEmpty(baud)) {
                JOptionPane.showMessageDialog(this, "请选择端口和波特率", "Warning", JOptionPane.WARNING_MESSAGE);
            } else {
                if (KsCardInterfaceUtil.ksOpenPort(Integer.parseInt(port), Integer.parseInt(baud))) {
                    source.setText("关闭端口");
                    openPort = true;
                } else {
                    JOptionPane.showMessageDialog(this, "打开端口失败", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        }
    }

    private void signAction(ActionEvent e) {
        if (KsCardInterfaceUtil.ksSignIn(result)) {
            String shopId = result.getProperty("shopId");
            String shopName = result.getProperty("shopName");
            shopIdText.setText(shopId);
            shopNameText.setText(shopName);
            JOptionPane.showMessageDialog(this, "读卡器签到成功[商户ID=" + shopId + ",商户名称=" + shopName + "]", "Info", JOptionPane.INFORMATION_MESSAGE);
        } else {
            shopIdText.setText("");
            shopNameText.setText("");
            String errMsg = result.getProperty("errMsg");
            JOptionPane.showMessageDialog(this, "读卡器签到失败[" + errMsg + "]", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }
}
