package com.sungard.ticketsys.page.pos;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import com.sungard.ticketsys.component.InputComboBox;
import com.sungard.ticketsys.component.Validate;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.card.KsCardInterfaceUtil;

public class OpenPortPanel extends JPanel {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(OpenPortPanel.class);
	
    public boolean openPort = false;

	private IndexFrame indexFrame = null;
	
	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JLabel lb_title = null;
	
	private JLabel lb_error = null;
	
	// 字段名
	private JLabel lb_port = null;
	private JLabel lb_baud = null;
	
	// 输入域
    private InputComboBox cb_port = null;
	private InputComboBox cb_baud = null;
	
	protected OpenPortPanel() {
	}

	public OpenPortPanel(IndexFrame indexFrame) {
		this.indexFrame = indexFrame;
		initialize();
	}

	/**
	 * This method initializes this
	 * 
	 * @return void
	 */
	private void initialize() {
		this.setSize(890, 630);
		this.setLayout(null);
		this.add(getNewuser(), null);
	}

	/**
	 * This method initializes detail
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getNewuser() {
		if (newuser == null) {
			lb_title = new JLabel();
			lb_title.setBounds(new Rectangle(30, 26, 700, 50));
			lb_title.setText("打开端口");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 24));
			
			lb_error = new JLabel();
			lb_error.setBounds(new Rectangle(0, 200, 700, 30));
			lb_error.setHorizontalAlignment(JLabel.CENTER);
			lb_error.setForeground(Color.RED);
			
			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(20, 20, 750, 600));
			newuser.setBorder(BorderFactory.createTitledBorder("打开端口"));
			newuser.add(getLeft(), null);
			newuser.add(getRight(), null);
			newuser.add(getBt_submit(), null);
			newuser.add(lb_title, null);
//			newuser.add(lb_error, null);
		}
		return newuser;
	}

	/**
	 * This method initializes left
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getLeft() {
		if (left == null) {
			lb_port = new JLabel();
			lb_port.setBounds(new Rectangle(0, 0, 80, 26));
			lb_port.setText("端口号：");
			lb_baud = new JLabel();
			lb_baud.setBounds(new Rectangle(0, 50, 80, 26));
			lb_baud.setText("波特率：");
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(200, 92, 68, 100));
			left.add(lb_port, null);
			left.add(lb_baud, null);
		}
		return left;
	}

	/**
	 * This method initializes right
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getRight() {
		if (right == null) {
			right = new JPanel();
			right.setLayout(null);
			right.setBounds(new Rectangle(290, 92, 280, 100));
			right.add(getCb_port(), null);
			right.add(getCb_baud(), null);
		}
		return right;
	}
	
	/**
	 * 端口号
	 * 
	 * @return
	 */
	private InputComboBox getCb_port() {
		if (cb_port == null) {
			cb_port = new InputComboBox();
			cb_port.setNotNull(true);
			cb_port.setName("端口号");
			cb_port.setBounds(new Rectangle(0, 0, 250, 26));
			cb_port.setEditable(true);
			cb_port.setModel(new DefaultComboBoxModel(new String[]{
                      "100",
                      "COM3"
              }));
			cb_port.setSelectedIndex(0);
			
		}
		return cb_port;
	}

	/**
	 * 波特率
	 * 
	 * @return
	 */
	private InputComboBox getCb_baud() {
		if (cb_baud == null) {
			cb_baud = new InputComboBox();
			cb_baud.setNotNull(true);
			cb_baud.setName("波特率");
			cb_baud.setBounds(new Rectangle(0, 50, 250, 26));
			cb_baud.setEditable(true);
			cb_baud.setModel(new DefaultComboBoxModel(new String[]{
					  "115200",
                      "19200",
                      "38400",
                      "9600"
              }));
			cb_baud.setSelectedIndex(0);
			
		}
		return cb_baud;
	}

	/**
	 * This method initializes bt_submit
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_submit() {
		if (bt_submit == null) {
			bt_submit = new JButton();
			bt_submit.setBounds(new Rectangle(300, 200, 100, 26));
			bt_submit.setText("打开端口");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			final JPanel jp = this;
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					// 验证输入的数据是否合法
					boolean flag = Validate.checkInputData(right, lb_error);
					 if (openPort) {
				            if (KsCardInterfaceUtil.ksClosePort()) {
				            	bt_submit.setText("打开端口");
				                openPort = false;
				            } else {
				                JOptionPane.showMessageDialog(jp, "关闭端口失败", "Error", JOptionPane.ERROR_MESSAGE);
				            }
				        } else {
				            String port = getCb_port().getSelectedItem().toString();
				            String baud = getCb_baud().getSelectedItem().toString();
				            if (StringUtils.isEmpty(port) || StringUtils.isEmpty(baud)) {
				                JOptionPane.showMessageDialog(jp, "请选择端口和波特率", "Warning", JOptionPane.WARNING_MESSAGE);
				            } else {
				                if (KsCardInterfaceUtil.ksOpenPort(Integer.parseInt(port), Integer.parseInt(baud))) {
				                	bt_submit.setText("关闭端口");
				                    openPort = true;
				                } else {
				                    JOptionPane.showMessageDialog(jp, "打开端口失败", "Error", JOptionPane.ERROR_MESSAGE);
				                }
				            }
				        }
				}
			});
		}
		return bt_submit;
	}

}


