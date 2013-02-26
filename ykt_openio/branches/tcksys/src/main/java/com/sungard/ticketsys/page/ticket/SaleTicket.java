package com.sungard.ticketsys.page.ticket;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextPane;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.model.TicketLog;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;
import com.sungard.ticketsys.service.TicketManager;

public class SaleTicket extends JPanel {

	private static final long serialVersionUID = 1L;

	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;

	// �ֶ���
	private JLabel lb_serdayId = null;
	private JLabel lb_Linename = null;
	private JLabel lb_startaddr = null;
	private JLabel lb_endaddr = null;
	private JLabel lb_departTime = null;
	private JLabel lb_payType = null;
	private JLabel lb_ticketType = null;
	private JLabel lb_price = null;
	private JLabel lb_memo = null;

	// �ֶ�ֵ
	private JLabel lb_serdayIdD = null;
	private JLabel lb_LinenameD = null;
	private JLabel lb_startaddrD = null;
	private JLabel lb_endaddrD = null;
	private JLabel lb_departTimeD = null;
	private JComboBox cb_payType = null;
	private JComboBox cb_ticketType = null;
	private JLabel lb_priceD = null;
	private JScrollPane jScrollPane_desc = null;
	private JTextPane jTextPane_desc = null;
	

	private JButton bt_reset = null;

	private TickePanel tickePanel = null;

	// ������Ϣ
	private BusserDay sleBusserDay = null;
	private BusSer currBusSer = null;
	private Line currLine = null;

	protected SaleTicket() {
	}

	/**
	 * This is the default constructor
	 */
	public SaleTicket(TickePanel tickePanel) {
		super();
		this.tickePanel = tickePanel;
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
			lb_title.setText("Ʊ���ӡ����");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("����", Font.BOLD, 24));
			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(20, 20, 750, 600));
			newuser.setBorder(BorderFactory.createTitledBorder("Ʊ�񴰿�"));
			newuser.add(getLeft(), null);
			newuser.add(getRight(), null);
			newuser.add(getBt_submit(), null);
			newuser.add(lb_title, null);
			newuser.add(getBt_cancel(), null);
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
			lb_serdayId = new JLabel();
			lb_serdayId.setBounds(new Rectangle(0, 0, 66, 26));
			lb_serdayId.setText("���κţ�");
			lb_Linename = new JLabel();
			lb_Linename.setBounds(new Rectangle(0, 50, 66, 26));
			lb_Linename.setText("·�����ƣ�");
			lb_startaddr = new JLabel();
			lb_startaddr.setBounds(new Rectangle(0, 100, 66, 26));
			lb_startaddr.setText("���վ��");
			lb_endaddr = new JLabel();
			lb_endaddr.setBounds(new Rectangle(0, 150, 66, 26));
			lb_endaddr.setText("�յ�վ��");
			lb_departTime = new JLabel();
			lb_departTime.setBounds(new Rectangle(0, 200, 66, 26));
			lb_departTime.setText("����ʱ�䣺");
			lb_payType = new JLabel();
			lb_payType.setBounds(new Rectangle(0, 250, 66, 26));
			lb_payType.setText("֧�����ͣ�");
			lb_ticketType = new JLabel();
			lb_ticketType.setBounds(new Rectangle(0, 300, 66, 26));
			lb_ticketType.setText("Ʊ�����ͣ�");
			lb_price = new JLabel();
			lb_price.setBounds(new Rectangle(0, 350, 66, 26));
			lb_price.setText("Ʊ�ۣ�");
			lb_memo = new JLabel();
			lb_memo.setBounds(new Rectangle(0, 400, 66, 26));
			lb_memo.setText("��ע��");
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(220, 92, 68, 470));
			left.add(lb_serdayId, null);
			left.add(lb_Linename, null);
			left.add(lb_startaddr, null);
			left.add(lb_endaddr, null);
			left.add(lb_departTime, null);
			left.add(lb_payType, null);
			left.add(lb_ticketType, null);
			left.add(lb_price, null);
			left.add(lb_memo,null);
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
			right.setBounds(new Rectangle(290, 92, 260, 470));
			right.add(getLb_serdayId(), null);
			right.add(getLb_Linename(), null);
			right.add(getLb_startaddr(), null);
			right.add(getLb_endaddr(), null);
			right.add(getLb_departTime(), null);
			right.add(getCb__payType(), null);
			right.add(getCb__ticketType(), null);
			right.add(getLb_price(), null);
			right.add(getJScrollPane_desc(), null);
		}
		return right;
	}
	
	/**
	 * 
	 * This method initializes jScrollPane_desc
	 *
	 * @return javax.swing.JScrollPane
	 */
	private JScrollPane getJScrollPane_desc() {
		if (jScrollPane_desc == null) {
			jScrollPane_desc = new JScrollPane();
			jScrollPane_desc.setBounds(new Rectangle(0, 400, 250, 60));
			jScrollPane_desc.setViewportView(getJTextPane_desc());
		}
		return jScrollPane_desc;
	}

	/**
	 * This method initializes jTextPane_desc
	 *
	 * @return javax.swing.JTextPane
	 */
	private JTextPane getJTextPane_desc() {
		if (jTextPane_desc == null) {
			jTextPane_desc = new JTextPane();
		}
		return jTextPane_desc;
	}


	/**
	 * ���κ�
	 * 
	 * @return
	 */
	private JLabel getLb_serdayId() {
		if (lb_serdayIdD == null) {
			lb_serdayIdD = new JLabel();
			lb_serdayIdD.setBounds(new Rectangle(0, 0, 250, 26));
		}
		return lb_serdayIdD;
	}

	/**
	 * ·������
	 * 
	 * @return
	 */
	private JLabel getLb_Linename() {
		if (lb_LinenameD == null) {
			lb_LinenameD = new JLabel();
			lb_LinenameD.setBounds(new Rectangle(0, 50, 250, 26));
		}
		return lb_LinenameD;
	}

	/**
	 * ��ʼ�ص�
	 * 
	 * @return
	 */
	private JLabel getLb_startaddr() {
		if (lb_startaddrD == null) {
			lb_startaddrD = new JLabel();
			lb_startaddrD.setBounds(new Rectangle(0, 100, 250, 26));
		}
		return lb_startaddrD;
	}

	/**
	 * �յ�վ
	 * 
	 * @return
	 */
	private JLabel getLb_endaddr() {
		if (lb_endaddrD == null) {
			lb_endaddrD = new JLabel();
			lb_endaddrD.setBounds(new Rectangle(0, 150, 250, 26));
		}
		return lb_endaddrD;
	}

	/**
	 * ����ʱ��
	 * 
	 * @return
	 */
	private JLabel getLb_departTime() {
		if (lb_departTimeD == null) {
			lb_departTimeD = new JLabel();
			lb_departTimeD.setBounds(new Rectangle(0, 200, 250, 26));
		}
		return lb_departTimeD;
	}

	/**
	 * ���ʽ
	 * 
	 * @return
	 */
	private JComboBox getCb__payType() {
		if (cb_payType == null) {
			cb_payType = new JComboBox();
			cb_payType.setBounds(new Rectangle(0, 250, 250, 26));
			cb_payType.addItem("-------- ��ѡ�� --------");
			cb_payType.addPopupMenuListener(new PopupMenuListener() {
				public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
					cb_payType.removeAllItems();
					cb_payType.addItem("-------- ��ѡ�� --------");
					cb_payType.addItem(TicketLog.PAY_TYPE_CASH);
					cb_payType.addItem(TicketLog.PAY_TYPE_CARD);
				}

				public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
				}

				public void popupMenuCanceled(PopupMenuEvent e) {
				}
			});
		}
		return cb_payType;
	}

	/**
	 * Ʊ��
	 * 
	 * @return
	 */
	private JLabel getLb_price() {
		if (lb_priceD == null) {
			lb_priceD = new JLabel();
			lb_priceD.setBounds(new Rectangle(0, 350, 250, 26));
		}
		return lb_priceD;
	}

	/**
	 * 
	 * @return
	 */
	private JComboBox getCb__ticketType() {
		if (cb_ticketType == null) {
			cb_ticketType = new JComboBox();
			cb_ticketType.setBounds(new Rectangle(0, 300, 250, 26));
			cb_ticketType.addItem(TicketLog.TICKET_TYPE_MORM);
			cb_ticketType.addPopupMenuListener(new PopupMenuListener() {
				public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
					cb_ticketType.removeAllItems();
					cb_ticketType.addItem(TicketLog.TICKET_TYPE_MORM);
					cb_ticketType.addItem(TicketLog.TICKET_TYPE_PER);
				}

				public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
				}

				public void popupMenuCanceled(PopupMenuEvent e) {
				}
			});
			cb_ticketType.addItemListener(new ItemListener() {

				public void itemStateChanged(ItemEvent e) {
					String ticketType = cb_ticketType.getSelectedItem()+"";
					//���Ϊ��ͨƱ����Ʊ��Ϊ��ͨ��
					if(ticketType.equals(TicketLog.TICKET_TYPE_MORM)){
						getLb_price().setText(currBusSer.getPrice());
					}else if(ticketType.equals(TicketLog.TICKET_TYPE_PER)){
						getLb_price().setText(currBusSer.getPerferPrice());
					}

				}
			});
		}
		return cb_ticketType;
	}

	/**
	 * This method initializes bt_submit
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_submit() {
		if (bt_submit == null) {
			bt_submit = new JButton();
			bt_submit.setBounds(new Rectangle(250, 570, 63, 23));
			bt_submit.setText("��ӡ");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			final JPanel jp = this;
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					boolean flag = true;
					if (getCb__payType().getSelectedIndex() == 0) {
						JOptionPane.showMessageDialog(jp, "û��ѡ��֧����ʽ����ѡ��!",
								"ERROE!!!", JOptionPane.ERROR_MESSAGE);
						flag = false;
					}
					
					if (flag) {
						int response = JOptionPane.showConfirmDialog(jp, "ȷ���ύ��", "ȷ�϶Ի���", JOptionPane.YES_NO_OPTION);
						if(response == 0){//ȷ��
							//���Ʊ����Ϣ
							TicketLog ticketLog = new TicketLog();
							ticketLog.setPayType(getCb__payType().getSelectedItem()+"");
							ticketLog.setBusSerno(sleBusserDay.getBusSerNo());
							ticketLog.setSerdayId(sleBusserDay.getSerdayId());
							ticketLog.setStartAddr(currLine.getStartAddr());
							ticketLog.setEndAddr(currLine.getEndAddr());
							ticketLog.setPrice(getLb_price().getText());
							ticketLog.setDepartDate(sleBusserDay.getDepartDate());
							ticketLog.setDepartTime(currBusSer.getDepartTime());
							ticketLog.setTicketType(getCb__ticketType().getSelectedItem()+"");
							ticketLog.setMemo(getJTextPane_desc().getText());
							ticketLog.setBusSerno(sleBusserDay.getBusSerNo());
							
							//��ӡ��Ʊ����¼��Ʊ��¼
						    try {
//								TicketManager.getInstance().saleTicket(ticketLog);
								JOptionPane.showMessageDialog(jp, "��ӡƱ��ɹ�", "SUCCESS",
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
	 * This method initializes bt_concel
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_cancel() {
		if (bt_cancel == null) {
			bt_cancel = new JButton();
			bt_cancel.setBounds(new Rectangle(440, 570, 63, 23));
			bt_cancel.setText("����");
			bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_cancel.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getCb__payType().setSelectedItem(0);
					getCb__ticketType().setSelectedItem(0);
					tickePanel.getSerSet();
					tickePanel.hideOtherPanel();
					tickePanel.getSerSet_search().setVisible(true);
					tickePanel.getSerSet_result().setVisible(true);
				}
			});
		}
		return bt_cancel;
	}

	/**
	 * This method initializes bt_reset
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_reset() {
		if (bt_reset == null) {
			bt_reset = new JButton();
			bt_reset.setBounds(new Rectangle(350, 570, 63, 23));
			bt_reset.setText("����");
			bt_reset.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_reset.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getCb__payType().setSelectedItem(0);
					getCb__ticketType().setSelectedItem(0);
					getLb_price().setText(currBusSer.getPrice());
					getJTextPane_desc().setText("");

				}
			});
		}
		return bt_reset;
	}

	public void setInfo_Ticket(BusserDay sleBusserDay) {
		this.sleBusserDay = sleBusserDay;
		// ��������
		String departDate = sleBusserDay.getDepartDate();
		// ��ȡ��Ӧ�İ����Ϣ
		this.currBusSer = BusSerManager.getInstance().getBusSer(
				sleBusserDay.getBusSerNo());
		// ����ʱ��
		String departTime = currBusSer.getDepartTime();
		// ��ȡ·����Ϣ
		this.currLine = LineManager.getInstance().getLine(
				currBusSer.getLineName());

		// ����lableֵ
		getLb_serdayId().setText(sleBusserDay.getSerdayId());
		getLb_Linename().setText(currLine.getLineName());
		getLb_startaddr().setText(currLine.getStartAddr());
		getLb_endaddr().setText(currLine.getEndAddr());
		getLb_departTime().setText(
				departDate.substring(0, 4) + "-" + departDate.substring(4, 6)
						+ "-" + departDate.substring(6, departDate.length())
						+ " " + departTime.substring(0, 2) + ":"
						+ departTime.substring(2, 4) + ":"
						+ departTime.substring(4, departTime.length()));
		getLb_price().setText(currBusSer.getPrice());
	}

}
