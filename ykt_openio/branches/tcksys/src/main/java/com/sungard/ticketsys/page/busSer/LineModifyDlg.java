package com.sungard.ticketsys.page.busSer;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.Toolkit;
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

public class LineModifyDlg extends JDialog {

	private static final long serialVersionUID = 1L;
	
	private static final Logger logger = Logger.getLogger(LineModifyDlg.class);

	private JPanel globPanel = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;
	
	private JLabel lb_error = null;

	private JLabel lb_linename = null;

	private JLabel lb_startaddr = null;
	
	private JLabel lb_endaddr = null;

	private JLabel tf_linename = null;
	
	private JTextField tf_startaddr = null;
	
	private JTextField tf_endaddr = null;
	
	private LinePanel linePanel = null;

	public Line info_line=null;

	public LineModifyDlg(JFrame parentFrame,LinePanel linePanel) {
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
		this.add(getGlobPanel(), null);
		this.requestFocus();
	}


	/**
	 * This method initializes detail
	 *
	 * @return javax.swing.JPanel
	 */
	private JPanel getGlobPanel() {
		if (globPanel == null) {
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
			
			globPanel = new JPanel();
			globPanel.setLayout(null);
			globPanel.setBounds(new Rectangle(0, 0, 400, 300));
			globPanel.add(getLeft(), null);
			globPanel.add(getRight(), null);
			globPanel.add(getBt_submit(), null);
			globPanel.add(lb_title, null);
			globPanel.add(lb_error, null);
			globPanel.add(getBt_cancel(), null);
		}
		return globPanel;
	}

	/**
	 * This method initializes left
	 *
	 * @return javax.swing.JPanel
	 */
	private JPanel getLeft() {
		if (left == null) {
			lb_linename = new JLabel();
			lb_linename.setBounds(new Rectangle(0, 0, 66, 26));
			lb_linename.setText("·�����ƣ�");
			lb_startaddr = new JLabel();
			lb_startaddr.setBounds(new Rectangle(0, 50, 66, 26));
			lb_startaddr.setText("���վ��");
			lb_endaddr = new JLabel();
			lb_endaddr.setBounds(new Rectangle(0, 100, 66, 26));
			lb_endaddr.setText("�յ�վ��");
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(30, 60, 68, 130));
			left.add(lb_linename, null);
			left.add(lb_startaddr, null);
			left.add(lb_endaddr,null);
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
			bt_submit.setBounds(new Rectangle(125, 240, 63, 23));
			bt_submit.setText("�ύ");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					
					//��֤����������Ƿ�Ϸ�
					boolean flag = checkLineData();
					
					if (flag) {
							try {
								//������Ϣ
								info_line.setStartAddr(getTf_startaddr().getText());
								info_line.setEndAddr(getTf_endaddr().getText());
								LineManager.getInstance().updateLine(info_line);
								
								//�رնԻ���
								dispose();
								
								JOptionPane.showMessageDialog(linePanel, "����·��["+ info_line.getLineName() + "]�ɹ�", "����·����Ϣ", JOptionPane.NO_OPTION);
							
								//���ز�ѯҳ��
								linePanel.getLine();
								linePanel.getSelect_all().setSelected(false);
							} catch (Exception e2) {
								logger.error("����·��["+ info_line.getLineName() + "]��Ϣʧ�ܣ�ʧ��ԭ��"+e2.getMessage());
								dispose();
								JOptionPane.showMessageDialog(linePanel, "����·��["+ info_line.getLineName() + "]ʧ��!", "ERROE!!!",
										JOptionPane.ERROR_MESSAGE);
							}
						}
					}
			});
		}
		return bt_submit;
	}
	
	/**
	 * ��֤����������Ƿ�Ϸ�
	 * @return
	 */
	private boolean checkLineData() {
		
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


	public void setInfo_Line(Line info_line) {
		this.info_line = info_line;
		getTf_linename().setText(info_line.getLineName());
		getTf_startaddr().setText(info_line.getStartAddr());
		getTf_endaddr().setText(info_line.getEndAddr());
	}

	/**
	 * This method initializes bt_concel
	 *
	 * @return javax.swing.JButton
	 */
	private JButton getBt_cancel() {
		if (bt_cancel == null) {
			bt_cancel = new JButton();
			bt_cancel.setBounds(new Rectangle(220, 240, 63, 23));
			bt_cancel.setText("ȡ��");
			bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_cancel.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
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
	private JLabel getTf_linename() {
		if (tf_linename == null) {
			tf_linename = new JLabel();
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
	 * This method initializes tf_endaddr
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

	
}

