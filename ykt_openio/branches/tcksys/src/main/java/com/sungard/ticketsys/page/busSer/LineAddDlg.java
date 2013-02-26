package com.sungard.ticketsys.page.busSer;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.LineManager;

public class LineAddDlg extends JDialog {

	private static final long serialVersionUID = 1L;

	private static final Logger logger = Logger.getLogger(LineAddDlg.class);

	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;

	private JLabel lb_error = null;

	private JLabel lb_Linename = null;

	private JLabel lb_startaddr = null;

	private JLabel lb_endaddr = null;

	private JTextField tf_linename = null;

	private JTextField tf_startaddr = null;

	private JTextField tf_endaddr = null;

	private JButton bt_reset = null;

	private LinePanel linePanel = null;

	public LineAddDlg(JFrame parentFrame, LinePanel linePanel) {
		super(parentFrame, " ", true);
		this.linePanel = linePanel;
		this.setModal(true);
		setTitle("����·��");
		try {
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
		this.setSize(400, 300);
		this.setLocationRelativeTo(linePanel);
	}

	private void jbInit() throws Exception {
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		this.setResizable(false);
		this.setLayout(null);
		this.add(getNewuser(), null);
		this.requestFocus();
	}

	/**
	 * This method initializes detail
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getNewuser() {
		if (newuser == null) {
			lb_title = new JLabel();
			lb_title.setBounds(new Rectangle(0, 15, 400, 30));
			lb_title.setText("����·����Ϣ");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("����", Font.BOLD, 20));

			lb_error = new JLabel();
			lb_error.setBounds(new Rectangle(0, 200, 400, 30));
			lb_error.setHorizontalAlignment(JLabel.CENTER);
			lb_error.setForeground(Color.RED);

			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(0, 0, 400, 300));
			newuser.add(getLeft(), null);
			newuser.add(getRight(), null);
			newuser.add(lb_title, null);

			newuser.add(getBt_submit(), null);
			newuser.add(getBt_cancel(), null);
			newuser.add(getBt_reset(), null);

			newuser.add(lb_error, null);
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
			lb_Linename = new JLabel();
			lb_Linename.setBounds(new Rectangle(0, 0, 66, 26));
			lb_Linename.setText("·�����ƣ�");
			lb_startaddr = new JLabel();
			lb_startaddr.setBounds(new Rectangle(0, 50, 66, 26));
			lb_startaddr.setText("���վ��");
			lb_endaddr = new JLabel();
			lb_endaddr.setBounds(new Rectangle(0, 100, 66, 26));
			lb_endaddr.setText("�յ�վ��");
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(30, 60, 68, 130));
			left.add(lb_Linename, null);
			left.add(lb_startaddr, null);
			left.add(lb_endaddr, null);
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
			right.setBounds(new Rectangle(100, 60, 260, 130));
			right.add(getTf_linename(), null);
			right.add(getTf_startaddr(), null);
			right.add(getTf_endaddr(), null);
		}
		return right;
	}

	/**
	 * This method initializes bt_submit
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_submit() {
		if (bt_submit == null) {
			bt_submit = new JButton();
			bt_submit.setBounds(new Rectangle(60, 240, 63, 23));
			bt_submit.setText("�ύ");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			final JDialog jp = this;
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {

					// ��֤����������Ƿ�Ϸ�
					boolean flag = checkLineData();

					if (flag) {
						try {
							// ����·����Ϣ
							Line line = new Line();
							line.setLineName(getTf_linename().getText().trim());
							line.setStartAddr(getTf_startaddr().getText()
									.trim());
							line.setEndAddr(getTf_endaddr().getText().trim());
							LineManager.getInstance().saveLine(line);

							// ��ձ༭ҳ��
							getTf_linename().setText("");
							getTf_startaddr().setText("");
							getTf_endaddr().setText("");

							// �رնԻ���
							dispose();

							// ��ʾ�����ɹ�
							JOptionPane.showMessageDialog(jp, "����·����Ϣ�ɹ�",
									"SUCCESS", JOptionPane.NO_OPTION);

							// ˢ�²�ѯҳ��
							linePanel.getLine();
							linePanel.getSelect_all().setSelected(false);

						} catch (Exception e2) {
							logger.error("����·��ʧ�ܣ�ʧ��ԭ��:" + e2.getMessage());
							dispose();
							JOptionPane.showMessageDialog(linePanel, "����·��ʧ��!",
									"ERROE!!!", JOptionPane.ERROR_MESSAGE);
						}

					}
				}
			});
		}
		return bt_submit;
	}

	/**
	 * ��֤����������Ƿ�Ϸ�
	 * 
	 * @return
	 */
	private boolean checkLineData() {
		if ("".equals(getTf_linename().getText().trim())) {
			lb_error.setText("�ύʧ�ܣ�·�����Ʋ���Ϊ��!");
			return false;
		} else {
			if (LineManager.getInstance().checkLineIsUsed(
					getTf_linename().getText().trim())) {
				lb_error.setText("�ύʧ�ܣ�·�������Ѵ��ڣ�����������!");
				return false;
			}
			if (getTf_linename().getText().trim().length() > 12) {
				lb_error.setText("�ύʧ�ܣ��������·������̫�����벻Ҫ����12λ!");
				return false;
			}
		}

		if ("".equals(getTf_startaddr().getText().trim())) {
			lb_error.setText("�ύʧ�ܣ����վ����Ϊ�գ�������!");
			return false;
		} else {
			if (getTf_startaddr().getText().trim().length() > 12) {
				lb_error.setText("�ύʧ�ܣ�����������վ̫�����벻Ҫ����12λ!");
				return false;
			}
		}
		if ("".equals(getTf_endaddr().getText().trim())) {
			lb_error.setText("�ύʧ�ܣ��յ�վ����Ϊ�գ�������!");
			return false;
		} else {
			if (getTf_endaddr().getText().trim().length() > 12) {
				lb_error.setText("�ύʧ�ܣ���������յ�վ̫�����벻Ҫ����12λ!");
				return false;
			}
		}
		return true;
	}

	/**
	 * This method initializes bt_concel
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_cancel() {
		if (bt_cancel == null) {
			bt_cancel = new JButton();
			bt_cancel.setBounds(new Rectangle(250, 240, 63, 23));
			bt_cancel.setText("ȡ��");
			bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_cancel.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getTf_linename().setText("");
					getTf_startaddr().setText("");
					getTf_endaddr().setText("");
					lb_error.setText("");
					dispose();
				}
			});
		}
		return bt_cancel;
	}

	/**
	 * This method initializes tf_linename
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_linename() {
		if (tf_linename == null) {
			tf_linename = new JTextField();
			tf_linename.setName("·������");
			tf_linename.setBounds(new Rectangle(0, 0, 250, 26));
		}
		return tf_linename;
	}

	/**
	 * This method initializes tf_startaddr
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_startaddr() {
		if (tf_startaddr == null) {
			tf_startaddr = new JTextField();
			tf_startaddr.setBounds(new Rectangle(0, 50, 250, 26));
		}
		return tf_startaddr;
	}

	/**
	 * This method initializes tf_linename
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_endaddr() {
		if (tf_endaddr == null) {
			tf_endaddr = new JTextField();
			tf_endaddr.setBounds(new Rectangle(0, 100, 250, 26));
		}
		return tf_endaddr;
	}

	/**
	 * This method initializes bt_reset
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_reset() {
		if (bt_reset == null) {
			bt_reset = new JButton();
			bt_reset.setBounds(new Rectangle(160, 240, 63, 23));
			bt_reset.setText("����");
			bt_reset.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_reset.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getTf_linename().setText("");
					getTf_startaddr().setText("");
					getTf_endaddr().setText("");
					lb_error.setText("");
				}
			});
		}
		return bt_reset;
	}

}
