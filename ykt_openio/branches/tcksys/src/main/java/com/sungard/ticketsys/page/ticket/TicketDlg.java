package com.sungard.ticketsys.page.ticket;

import java.awt.AWTEvent;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.List;
import java.util.Properties;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;


import org.apache.log4j.Logger;

import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.common.MyFormat;
import com.sungard.ticketsys.component.InputComboBox;
import com.sungard.ticketsys.component.InputComponet;
import com.sungard.ticketsys.component.InputTextField;
import com.sungard.ticketsys.component.Validate;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.model.TicketLog;
import com.sungard.ticketsys.page.busSer.BusSerAddDlg;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;
import com.sungard.ticketsys.service.TicketManager;

public class TicketDlg extends JDialog {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(BusSerAddDlg.class);

	private JPanel newuser = null;

	private JPanel left = null;

	private JPanel right = null;

	private JButton bt_submit = null;

	private JButton bt_cancel = null;

	private JLabel lb_title = null;

	private JLabel lb_error = null;

	// �ֶ�����
	private JLabel lb_reserve = null;
	private JLabel lb_payType = null;
	private JLabel lb_ticketType = null;
	private JLabel lb_price = null;

	// �����ֶ�
	private InputComboBox cb_reserve = null;
	private InputComboBox cb_payType = null;
	private InputComboBox cb_ticketType = null;
	private InputTextField tx_priceD = null;
	

	private JButton bt_reset = null;

	private TickePanel tickePanel = null;
	
	// ������Ϣ
	private BusserDay sleBusserDay = null;
	private BusSer currBusSer = null;
	private Line currLine = null;
	private String price = null;
	private String perferPrice = null;
	
	//У԰��֧�����
   private Properties result = new Properties();
   
   private IndexFrame indexFrame = null;
   

	public TicketDlg(IndexFrame indexFrame, TickePanel tickePanel) {
		super(indexFrame, " ", true);
		this.indexFrame = indexFrame;
		this.tickePanel = tickePanel;
		this.setModal(true);
		setTitle("��Ʊ����");
		try {
			jbInit();
			enableEvents(AWTEvent.WINDOW_EVENT_MASK);
		} catch (Exception e) {
			e.printStackTrace();
		}
		this.setSize(400, 350);
		this.setLocationRelativeTo(tickePanel);
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
			lb_title.setText("��Ʊ����");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("����", Font.BOLD, 20));

			lb_error = new JLabel();
			lb_error.setBounds(new Rectangle(0, 250, 400, 30));
			lb_error.setHorizontalAlignment(JLabel.CENTER);
			lb_error.setForeground(Color.RED);

			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(0, 0, 400, 350));
			newuser.add(getLeft(), null);
			newuser.add(getRight(), null);
			newuser.add(getBt_submit(), null);
			newuser.add(lb_title, null);
			newuser.add(lb_error, null);
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
			lb_reserve = new JLabel();
			lb_reserve.setBounds(new Rectangle(0, 0, 66, 26));
			lb_reserve.setText("Ԥ��Ʊ��");
			
			lb_payType = new JLabel();
			lb_payType.setBounds(new Rectangle(0, 50, 66, 26));
			lb_payType.setText("֧�����ͣ�");
			
			lb_ticketType = new JLabel();
			lb_ticketType.setBounds(new Rectangle(0, 100, 66, 26));
			lb_ticketType.setText("Ʊ�����ͣ�");
			
			lb_price = new JLabel();
			lb_price.setBounds(new Rectangle(0, 150, 66, 26));
			lb_price.setText("Ʊ�ۣ�");
			
			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(30, 60, 68, 180));
			left.add(lb_reserve, null);
			left.add(lb_payType, null);
			left.add(lb_ticketType, null);
			left.add(lb_price, null);
			
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
			right.setBounds(new Rectangle(100, 60, 280, 180));
			right.add(getCb_reserve(), null);
			right.add(getCb_payType(), null);
			right.add(getCb_ticketType(), null);
			tx_priceD = InputComponet.moneyField(right, tx_priceD, "Ʊ��", false, 0, 150);
			tx_priceD.setEditable(false);
		}
		return right;
	}
	
	/**
	 * Ԥ��Ʊ
	 * 
	 * @return
	 */
	private InputComboBox getCb_reserve() {
		if (cb_reserve == null) {
			cb_reserve = new InputComboBox();
			cb_reserve.setName("Ԥ��Ʊ");
			cb_reserve.setBounds(new Rectangle(0, 0, 250, 26));
			cb_reserve.addItem("��");
			cb_reserve.addItem("��");
		}
		return cb_reserve;
	}
	
	/**
	 * ���ʽ
	 * 
	 * @return
	 */
	private InputComboBox getCb_payType() {
		if (cb_payType == null) {
			cb_payType = new InputComboBox();
			cb_payType.setName("֧������");
			cb_payType.setBounds(new Rectangle(0, 50, 250, 26));
			cb_payType.addItem(TicketLog.PAY_TYPE_CASH);
			cb_payType.addItem(TicketLog.PAY_TYPE_CARD);
		}
		return cb_payType;
	}

	/**
	 * Ʊ������
	 * @return
	 */
	private InputComboBox getCb_ticketType() {
		if (cb_ticketType == null) {
			cb_ticketType = new InputComboBox();
			cb_ticketType.setName("Ʊ������");
			cb_ticketType.setBounds(new Rectangle(0, 100, 250, 26));
			cb_ticketType.addItem(TicketLog.TICKET_TYPE_MORM);
			cb_ticketType.addItem(TicketLog.TICKET_TYPE_PER);
			
			cb_ticketType.addItemListener(new ItemListener() {

				public void itemStateChanged(ItemEvent e) {
					String ticketType = cb_ticketType.getSelectedItem()+"";
					//���Ϊ��ͨƱ����Ʊ��Ϊ��ͨ��
					if(currBusSer!=null){
							if (ticketType.equals(TicketLog.TICKET_TYPE_MORM)){
								tx_priceD.setText(price);
						}else if(ticketType.equals(TicketLog.TICKET_TYPE_PER)){
							tx_priceD.setText(perferPrice);
						}
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
			bt_submit.setBounds(new Rectangle(60, 290, 63, 23));
			bt_submit.setText("��Ʊ");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {

					// ��֤����������Ƿ�Ϸ�
					boolean flag = Validate.checkInputData(right, lb_error);
					if(flag && getCb_payType().getSelectedItem().toString().equals(TicketLog.PAY_TYPE_CARD)){
						if(flag && !indexFrame.getOpenPortPanel().openPort){
							flag = false;
							lb_error.setText("У԰���ۿ�ʧ��,�������˿�δ�򿪣�");
						}
						
						if(flag && !indexFrame.getSignInItemPanel().isSignIn){
							flag = false;
							lb_error.setText("У԰���ۿ�ʧ��,������δǩ����");
						}
						
					}
					
					if (flag) {
							//���Ʊ����Ϣ
							TicketLog ticketLog = new TicketLog();
							ticketLog.setPayType(getCb_payType().getSelectedItem()+"");
							ticketLog.setBusSerno(sleBusserDay.getBusSerNo());
							ticketLog.setSerdayId(sleBusserDay.getSerdayId());
							ticketLog.setStartAddr(currLine.getStartAddr());
							ticketLog.setEndAddr(currLine.getEndAddr());
							ticketLog.setPrice(tx_priceD.getText());
							ticketLog.setDepartDate(sleBusserDay.getDepartDate());
							ticketLog.setDepartTime(currBusSer.getDepartTime());
							ticketLog.setTicketType(getCb_ticketType().getSelectedItem()+"");
							ticketLog.setBusSerno(sleBusserDay.getBusSerNo());
							if(getCb_reserve().getSelectedItem().toString().equals("��")){
								ticketLog.setIsReserve(true);
							}else{
								ticketLog.setIsReserve(false);
							}
						
							//���ΪУ԰�����ۿ�
//							if(getCb__payType().getSelectedItem().toString().equals(TicketLog.PAY_TYPE_CARD)){
//								bt_submit.setVisible(false);
//								bt_cancel.setVisible(false);
//								bt_reset.setVisible(false);
//							}
//							
							//��ӡ��Ʊ����¼��Ʊ��¼
						    try {
								TicketManager.getInstance().saleTicket(ticketLog,result);
								//�رնԻ���
								dispose();
								//��ʾ�����ɹ�
								JOptionPane.showMessageDialog(tickePanel, "��Ʊ�ɹ�","SUCCESS", JOptionPane.NO_OPTION);
								// ���ز�ѯҳ��
								tickePanel.getSerSet();
								tickePanel.getSelect_all().setSelected(false);
							} catch (Exception e2) {
								lb_error.setText("��Ʊʧ�ܣ�ԭ��:" + e2.getMessage());
								//�ۿ�ɹ�������ӡʧ�ܣ�����ʾ�ظ���ӡ��ť(�ظ���ӡ����������)
								if(getCb_payType().getSelectedItem().equals(TicketLog.PAY_TYPE_CARD)){
									
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
			bt_cancel.setBounds(new Rectangle(250, 290, 63, 23));
			bt_cancel.setText("ȡ��");
			bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_cancel.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					dispose();
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
			bt_reset.setBounds(new Rectangle(160, 290, 63, 23));
			bt_reset.setText("����");
			bt_reset.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_reset.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getCb_reserve().setSelectedIndex(0);
					getCb_payType().setSelectedIndex(0);
					getCb_ticketType().setSelectedIndex(0);
					tx_priceD.setText(price);
					lb_error.setText("");
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
        this.price = MyFormat.moneySdf(Double.parseDouble(currBusSer.getPrice()));
        this.perferPrice = MyFormat.moneySdf(Double.parseDouble(currBusSer.getPerferPrice()));
		
		// ����lableֵ
		tx_priceD.setText(price);
	}

}
