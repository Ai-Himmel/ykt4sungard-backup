package com.sungard.ticketsys.page.pos;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Properties;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.card.KsCardInterfaceUtil;

public class SignInPanel extends JPanel {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(SignInPanel.class);

	private IndexFrame indexFrame = null;
	
	public boolean isSignIn = false;
	
	private Properties result = new Properties();
	
	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_reset = null;

	private JLabel lb_title = null;
	
	// ×Ö¶ÎÃû
	private JLabel lb_ticketId = null;
	private JLabel lb_handFee = null;
	
	// ÊäÈëÓò
	private JTextField tf_shopId = null;
	private JTextField tf_shopName = null;
	
	
	protected SignInPanel() {
	}

	public SignInPanel(IndexFrame indexFrame) {
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
			lb_title.setText("¶Á¿¨Æ÷Ç©µ½");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("ËÎÌå", Font.BOLD, 24));
			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(20, 20, 750, 600));
			newuser.setBorder(BorderFactory.createTitledBorder("¶Á¿¨Æ÷Ç©µ½"));
			newuser.add(getLeft(), null);
			newuser.add(getRight(), null);
			newuser.add(getBt_submit(), null);
			newuser.add(lb_title, null);
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
			lb_ticketId.setText("ÉÌ»§ºÅ£º");
			lb_handFee = new JLabel();
			lb_handFee.setBounds(new Rectangle(0, 50, 80, 26));
			lb_handFee.setText("ÉÌ»§Ãû³Æ£º");
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
			right.add(getTf_shopId(), null);
			right.add(getTf_shopName(), null);
		}
		return right;
	}
	
	
	private JTextField getTf_shopId() {
		if (tf_shopId == null) {
			tf_shopId = new JTextField();
			tf_shopId.setBounds(new Rectangle(0, 0, 250, 26));
			tf_shopId.setEditable(false);
		}
		return tf_shopId;
	}
	
	private JTextField getTf_shopName() {
		if (tf_shopName == null) {
			tf_shopName = new JTextField();
			tf_shopName.setBounds(new Rectangle(0, 50, 250, 26));
			tf_shopName.setEditable(false);
			
		}
		return tf_shopName;
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
			bt_submit.setText("¶Á¿¨Æ÷Ç©µ½");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			final JPanel jp = this;
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					boolean flag = true;
					if(!indexFrame.getOpenPortPanel().openPort){
						flag = false;
						JOptionPane.showMessageDialog(jp, "¶Á¿¨Æ÷Ç©µ½Ê§°Ü,¶Ë¿ÚÎ´´ò¿ª£¡", "¶Á¿¨Æ÷Ç©µ½", JOptionPane.WARNING_MESSAGE);
					}
					if(flag){
						 if (KsCardInterfaceUtil.ksSignIn(result)) {
					            String shopId = result.getProperty("shopId");
					            String shopName = result.getProperty("shopName");
					            getTf_shopId().setText(shopId);
					            getTf_shopName().setText(shopName);
					            isSignIn = true;
					            JOptionPane.showMessageDialog(jp, "¶Á¿¨Æ÷Ç©µ½³É¹¦[ÉÌ»§ID=" + shopId + ",ÉÌ»§Ãû³Æ=" + shopName + "]", "Info", JOptionPane.INFORMATION_MESSAGE);
					        } else {
					            String errMsg = result.getProperty("errMsg");
					            JOptionPane.showMessageDialog(jp, "¶Á¿¨Æ÷Ç©µ½Ê§°Ü[" + errMsg + "]", "Error", JOptionPane.ERROR_MESSAGE);
					        }
					}
				}
			});
		}
		return bt_submit;
	}


}
