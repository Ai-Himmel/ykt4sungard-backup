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
	
	// �ֶ���
	private JLabel lb_port = null;
	private JLabel lb_baud = null;
	
	// ������
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
			lb_title.setText("�򿪶˿�");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("����", Font.BOLD, 24));
			
			lb_error = new JLabel();
			lb_error.setBounds(new Rectangle(0, 200, 700, 30));
			lb_error.setHorizontalAlignment(JLabel.CENTER);
			lb_error.setForeground(Color.RED);
			
			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(20, 20, 750, 600));
			newuser.setBorder(BorderFactory.createTitledBorder("�򿪶˿�"));
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
			lb_port.setText("�˿ںţ�");
			lb_baud = new JLabel();
			lb_baud.setBounds(new Rectangle(0, 50, 80, 26));
			lb_baud.setText("�����ʣ�");
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
	 * �˿ں�
	 * 
	 * @return
	 */
	private InputComboBox getCb_port() {
		if (cb_port == null) {
			cb_port = new InputComboBox();
			cb_port.setNotNull(true);
			cb_port.setName("�˿ں�");
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
	 * ������
	 * 
	 * @return
	 */
	private InputComboBox getCb_baud() {
		if (cb_baud == null) {
			cb_baud = new InputComboBox();
			cb_baud.setNotNull(true);
			cb_baud.setName("������");
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
			bt_submit.setText("�򿪶˿�");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			final JPanel jp = this;
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					// ��֤����������Ƿ�Ϸ�
					boolean flag = Validate.checkInputData(right, lb_error);
					 if (openPort) {
				            if (KsCardInterfaceUtil.ksClosePort()) {
				            	bt_submit.setText("�򿪶˿�");
				                openPort = false;
				            } else {
				                JOptionPane.showMessageDialog(jp, "�رն˿�ʧ��", "Error", JOptionPane.ERROR_MESSAGE);
				            }
				        } else {
				            String port = getCb_port().getSelectedItem().toString();
				            String baud = getCb_baud().getSelectedItem().toString();
				            if (StringUtils.isEmpty(port) || StringUtils.isEmpty(baud)) {
				                JOptionPane.showMessageDialog(jp, "��ѡ��˿ںͲ�����", "Warning", JOptionPane.WARNING_MESSAGE);
				            } else {
				                if (KsCardInterfaceUtil.ksOpenPort(Integer.parseInt(port), Integer.parseInt(baud))) {
				                	bt_submit.setText("�رն˿�");
				                    openPort = true;
				                } else {
				                    JOptionPane.showMessageDialog(jp, "�򿪶˿�ʧ��", "Error", JOptionPane.ERROR_MESSAGE);
				                }
				            }
				        }
				}
			});
		}
		return bt_submit;
	}

}


