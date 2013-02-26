package com.sungard.ticketsys.page.ticket;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.TicketManager;
import com.sungard.ticketsys.common.MyFormat;

public class BackTickePanel extends JPanel {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(BackTickePanel.class);

	private IndexFrame indexFrame = null;
	
	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_reset = null;

	private JLabel lb_title = null;
	
	// 字段名
	private JLabel lb_ticketId = null;
	private JLabel lb_handFee = null;
	
	// 输入域
	private JTextField tf_ticketId = null;
	private JTextField tf_handFee = null;
	private JLabel lb_yuan = null;
	
	
	protected BackTickePanel() {
	}

	public BackTickePanel(IndexFrame indexFrame) {
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
			lb_title.setText("退票窗口");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("宋体", Font.BOLD, 24));
			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(20, 20, 750, 600));
			newuser.setBorder(BorderFactory.createTitledBorder("退票窗口"));
			newuser.add(getLeft(), null);
			newuser.add(getRight(), null);
			newuser.add(getBt_submit(), null);
			newuser.add(lb_title, null);
			newuser.add(getBt_reset(), null);
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
			lb_ticketId = new JLabel();
			lb_ticketId.setBounds(new Rectangle(0, 0, 80, 26));
			lb_ticketId.setText("票务记录号：");
			lb_handFee = new JLabel();
			lb_handFee.setBounds(new Rectangle(0, 50, 80, 26));
			lb_handFee.setText("手续费：");
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(200, 92, 68, 100));
			left.add(lb_ticketId, null);
			left.add(lb_handFee, null);
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
			right.add(getTf_ticketId(), null);
			right.add(getTf_handFee(), null);
			right.add(lb_yuan,null);
		}
		return right;
	}
	
	/**
	 * 票务记录号
	 * 
	 * @return
	 */
	private JTextField getTf_ticketId() {
		if (tf_ticketId == null) {
			tf_ticketId = new JTextField();
			tf_ticketId.setBounds(new Rectangle(0, 0, 250, 26));
		}
		return tf_ticketId;
	}
	
	/**
	 * 手续费
	 * 
	 * @return
	 */
	private JTextField getTf_handFee() {
		if (tf_handFee == null) {
			tf_handFee = new JTextField();
			tf_handFee.setBounds(new Rectangle(0, 50, 250, 26));
			tf_handFee.setText("0.00");
			lb_yuan =  new JLabel();
			lb_yuan.setBounds(new Rectangle(250, 50, 20, 26));
			lb_yuan.setText("元");
		}
		return tf_handFee;
	}

	/**
	 * This method initializes bt_submit
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_submit() {
		if (bt_submit == null) {
			bt_submit = new JButton();
			bt_submit.setBounds(new Rectangle(250, 200, 63, 23));
			bt_submit.setText("退票");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			final JPanel jp = this;
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					boolean flag = true;
					if ("".equals(getTf_ticketId().getText().trim())) {
						JOptionPane.showMessageDialog(jp, "票务记录号不能空，请重新输入!", "ERROE!!!",
								JOptionPane.ERROR_MESSAGE);
						flag = false;
					}
					
					
					if (flag&&"".equals(getTf_handFee().getText().trim())) {
						JOptionPane.showMessageDialog(jp, "手续费不能空，请重新输入!", "ERROE!!!",
								JOptionPane.ERROR_MESSAGE);
						flag = false;
					}

					if (flag && !"".equals(getTf_handFee().getText().trim())) {
						flag = MyFormat.checkMoneySdf(getTf_handFee().getText().trim());
						if(!flag){
							JOptionPane.showMessageDialog(jp, "手续费格式不正确，请输入小数位最多两位的正数!",
										"ERROE!!!", JOptionPane.ERROR_MESSAGE);
								}
					}
					 
					if (flag) {
						int response = JOptionPane.showConfirmDialog(jp, "确定提交吗？", "确认对话框", JOptionPane.YES_NO_OPTION);
						if(response == 0){//确定
							
							//退票并记录退票记录
						    try {
						    	String ticketId = getTf_ticketId().getText().trim();
						    	String handFee = getTf_handFee().getText().trim();
								TicketManager.getInstance().backTicket(ticketId,handFee);
								
								//重置输入值
								getTf_ticketId().setText("");
								getTf_handFee().setText("0.00");
								
								JOptionPane.showMessageDialog(jp, "退票成功", "SUCCESS",
										JOptionPane.NO_OPTION);
							} catch (Exception e2) {
								JOptionPane.showMessageDialog(jp, e2.getMessage(),
										"ERROE!!!", JOptionPane.ERROR_MESSAGE);
							}
							
						}
					}
				}
			});
		}
		return bt_submit;
	}


	/**
	 * This method initializes bt_reset
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_reset() {
		if (bt_reset == null) {
			bt_reset = new JButton();
			bt_reset.setBounds(new Rectangle(350, 200, 63, 23));
			bt_reset.setText("重置");
			bt_reset.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_reset.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getTf_ticketId().setText("");
					getTf_handFee().setText("0.00");
				}
			});
		}
		return bt_reset;
	}


}

