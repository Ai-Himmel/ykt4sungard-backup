package com.sungard.ticketsys.page.ticket;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.JTextPane;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.model.Seat;
import com.sungard.ticketsys.model.TicketLog;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.page.MyTableCellRenderer;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;
import com.sungard.ticketsys.service.TicketManager;
import com.sungard.ticketsys.common.Constants;
import com.sungard.ticketsys.common.Page;

public class ReserveTicket extends JPanel {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(ReserveTicket.class);
	private TickePanel tickePanel = null;
	private IndexFrame indexFrame = null;
	private JPanel newuser = null;

	// ��������Ϣ
	private BusserDay sleBusserDay = null;
	private BusSer currBusSer = null;
	private Line currLine = null;

	// Ԥ��Ʊ����
	private JPanel reserve_Ticket = null;
	private JLabel lb_title = null;
	private JPanel left = null;
	private JPanel right = null;

	// �����ֶ�
	private JLabel lb_reservecount = null;
	private JLabel lb_memo = null;
	// ������
	private JTextField tf_reservecount = null;
	private JScrollPane jScrollPane_desc = null;
	private JTextPane jTextPane_desc = null;

	// ����ֵ
	private int reservecount;
	private String desc;

	// Ԥ��Ʊ��ť
	private JButton bt_submit = null;
	// ���ð�ť
	private JButton bt_reset = null;
	// ���ذ�ť
	private JButton bt_cancel = null;

	// Ԥ����λ�б�
	public JTable seatTable = null;
	private List<Seat> reserveSeatS = null;

	// ȡ��Ԥ����λ��
	private int deleteCount = 0;

	// ��ѯ���
	private JPanel serSet_result = null;
	private JScrollPane serSet_list = null;
	private JPanel serSet_op = null;
	private JButton bt_delete = null;
	private MyTableCellRenderer render = null;

	// �б����
	private Object data[][] = new Object[Constants.DEFAULT_PAGE_SIZE][7];
	// private Object columnName[] = { "", "��λ��","���κ�", "����ʱ��",
	// "·������","��ע","��ӡƱ��" };
	private Object columnName[] = { "", "��λID", "��λ��", "����ʱ��", "·������", "��ע",
			"��ӡƱ��" };

	// ��ҳ���
	private int pageNo = 1;
	private long totalCount = 0;
	private long totalPageNo = 0;
	private int pageSize = 0;
	private JCheckBox select_all = null;
	private JButton pre = null;
	private JButton next = null;
	private JLabel lb_total = null;

	// ��ӡƱ��
	private PrintRerTickDlg printRerTickDlg = null;

	public ReserveTicket(TickePanel tickePanel,IndexFrame indexFrame) {
		super();
		this.tickePanel = tickePanel;
		this.indexFrame = indexFrame;
		initialize();
	}

	protected ReserveTicket() {
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
			newuser = new JPanel();
			newuser.setLayout(null);
			newuser.setBounds(new Rectangle(0, 0, 800, 620));

			// Ԥ��Ʊpanel
			newuser.add(getReserve_Ticket(), null);
			// Ԥ����λ�б�panel
			newuser.add(getSeat_result(), null);
		}
		return newuser;
	}

	/**
	 * Ԥ��panel
	 * 
	 * @return
	 */
	public JPanel getReserve_Ticket() {
		if (reserve_Ticket == null) {
			reserve_Ticket = new JPanel();
			reserve_Ticket.setLayout(null);
			reserve_Ticket.setBounds(new Rectangle(10, 10, 780, 245));
			reserve_Ticket.setBorder(BorderFactory.createTitledBorder("Ԥ��Ʊ"));
			lb_title = new JLabel();
			lb_title.setBounds(new Rectangle(30, 16, 700, 50));
			lb_title.setText("Ԥ��Ʊ����");
			lb_title.setHorizontalAlignment(JLabel.CENTER);
			lb_title.setForeground(Color.BLUE);
			lb_title.setFont(new Font("����", Font.BOLD, 24));
			reserve_Ticket.add(lb_title, null);
			reserve_Ticket.add(getLeft(), null);
			reserve_Ticket.add(getRight(), null);
			reserve_Ticket.add(getBt_submit(), null);
			reserve_Ticket.add(getBt_cancel(), null);
			reserve_Ticket.add(getBt_reset(), null);

		}
		return reserve_Ticket;
	}

	/**
	 * ��ѯ�б�panel
	 * 
	 * @return javax.swing.JPanel
	 */
	public JPanel getSeat_result() {
		if (serSet_result == null) {
			serSet_result = new JPanel();
			serSet_result.setLayout(null);
			serSet_result.setBounds(new Rectangle(10, 260, 780, 375));
			serSet_result.setBorder(BorderFactory.createTitledBorder("Ԥ����λ�б�"));
			serSet_result.add(getSerSet_list(), null);
			serSet_result.add(getSerSet_op(), null);
		}
		return serSet_result;
	}

	/**
	 * This method initializes bt_submit
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_submit() {
		if (bt_submit == null) {
			bt_submit = new JButton();
			bt_submit.setBounds(new Rectangle(250, 210, 80, 25));
			bt_submit.setText("Ԥ��Ʊ");
			bt_submit.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			final JPanel jp = this;
			bt_submit.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					boolean flag = true;

					// ��֤�����ֵ�Ƿ�ϸ�
					flag = checkeData(flag, jp);

					if (flag) {
						int response = JOptionPane.showConfirmDialog(jp,
								"ȷ���ύ��", "ȷ�϶Ի���", JOptionPane.YES_NO_OPTION);
						if (response == 0) {// ȷ��
							// Ԥ��Ʊ
							try {
								TicketManager.getInstance().reserveTicket(
										sleBusserDay, reservecount,
										getJTextPane_desc().getText());
								JOptionPane.showMessageDialog(jp, "��ӡƱ��ɹ�",
										"SUCCESS", JOptionPane.NO_OPTION);
							} catch (Exception e2) {
								JOptionPane.showMessageDialog(jp, e2
										.getMessage(), "ERROE!!!",
										JOptionPane.ERROR_MESSAGE);
							}

							// ��������
							getLb_reservecount().setText("");
							getJTextPane_desc().setText("");

							// ˢ��Ԥ����λ�б�
							getSeatTable();
						}
					}

				}

			});
		}
		return bt_submit;
	}

	private boolean checkeData(boolean flag, JPanel jp) {
		if ("".equals(getLb_reservecount().getText().trim())) {
			JOptionPane.showMessageDialog(jp, "Ԥ��Ʊ�����ܿգ�����������!", "ERROE!!!",
					JOptionPane.ERROR_MESSAGE);
			flag = false;
		}

		if (flag && !"".equals(getLb_reservecount().getText().trim())) {
			try {
				reservecount = Integer.parseInt(getLb_reservecount().getText()
						.trim());
				if (reservecount < 1) {
					JOptionPane.showMessageDialog(jp, "Ԥ��Ʊ��ֻ������������������������������!",
							"ERROE!!!", JOptionPane.ERROR_MESSAGE);
					flag = false;
				}
			} catch (Exception e2) {
				JOptionPane.showMessageDialog(jp, "Ԥ��Ʊ��ֻ������������������������������!",
						"ERROE!!!", JOptionPane.ERROR_MESSAGE);
				flag = false;
			}
		}

		// �жϳ����Ƿ��ѹ���
		Date now = new Date();
		Calendar cnow = Calendar.getInstance();
		cnow.setTime(now);

		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		Date departTime = null;
		try {
			departTime = sdf.parse(sleBusserDay.getDepartDate()
					+ currBusSer.getDepartTime());
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Calendar cdepartTime = Calendar.getInstance();
		cdepartTime.setTime(departTime);
		if (cnow.after(cdepartTime)) {
			logger.error("����ʱ���ѹ���������Ʊ");
			JOptionPane.showMessageDialog(jp, "����ʱ���ѹ���������Ʊ!", "ERROE!!!",
					JOptionPane.ERROR_MESSAGE);
			flag = false;
		}

		return flag;
	}

	/**
	 * This method initializes bt_reset
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_reset() {
		if (bt_reset == null) {
			bt_reset = new JButton();
			bt_reset.setBounds(new Rectangle(350, 210, 80, 25));
			bt_reset.setText("����");
			bt_reset.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_reset.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getLb_reservecount().setText("");
					getJTextPane_desc().setText("");

				}
			});
		}
		return bt_reset;
	}

	/**
	 * This method initializes bt_concel
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_cancel() {
		if (bt_cancel == null) {
			bt_cancel = new JButton();
			bt_cancel.setBounds(new Rectangle(440, 210, 80, 25));
			bt_cancel.setText("����");
			bt_cancel.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_cancel.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getLb_reservecount().setText("");
					getJTextPane_desc().setText("");
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
	 * This method initializes left
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getLeft() {
		if (left == null) {
			lb_reservecount = new JLabel();
			lb_reservecount.setBounds(new Rectangle(0, 0, 66, 26));
			lb_reservecount.setText("Ԥ��Ʊ����");

			lb_memo = new JLabel();
			lb_memo.setBounds(new Rectangle(0, 50, 66, 26));
			lb_memo.setText("��ע��");

			left = new JPanel();
			left.setLayout(null);
			left.setBounds(new Rectangle(220, 85, 68, 120));
			left.add(lb_reservecount, null);
			left.add(lb_memo, null);
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
			right.setBounds(new Rectangle(290, 85, 260, 120));
			right.add(getLb_reservecount(), null);
			right.add(getJScrollPane_desc(), null);
		}
		return right;
	}

	/**
	 * Ԥ��Ʊ��
	 * 
	 * @return
	 */
	private JTextField getLb_reservecount() {
		if (tf_reservecount == null) {
			tf_reservecount = new JTextField();
			tf_reservecount.setBounds(new Rectangle(0, 0, 250, 26));
		}
		return tf_reservecount;
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
			jScrollPane_desc.setBounds(new Rectangle(0, 50, 250, 60));
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
	 * This method initializes user_list1
	 * 
	 * @return javax.swing.JScrollPane
	 */
	private JScrollPane getSerSet_list() {
		if (serSet_list == null) {
			serSet_list = new JScrollPane();
			serSet_list.setBounds(new Rectangle(20, 30, 750, 292));
			serSet_list.setViewportView(getSeatTable());
		}
		return serSet_list;
	}

	/**
	 * This method initializes serSet_op
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getSerSet_op() {
		if (serSet_op == null) {
			serSet_op = new JPanel();
			serSet_op.setLayout(null);
			serSet_op.setBounds(new Rectangle(20, 330, 750, 40));
			serSet_op.add(getSelect_all(), null);
			serSet_op.add(getPre(), null);
			serSet_op.add(getNext(), null);
			serSet_op.add(getBt_delete(), null);
			serSet_op.add(getLb_total(), null);
		}
		return serSet_op;
	}

	/**
	 * ��λ�б�
	 * 
	 * @return javax.swing.JTable
	 */
	public JTable getSeatTable() {
		if (reserveSeatS != null) {
			if (deleteCount == reserveSeatS.size() && pageNo > 1) {
				pageNo--;
			}
			deleteCount = 0;
		}
		reserveSeatS = TicketManager.getInstance().getReserveSeat(pageNo,
				Constants.DEFAULT_PAGE_SIZE, sleBusserDay, "seatNo");

		if (reserveSeatS != null && reserveSeatS.size() > 0) {
			this.getPre().setVisible(true);
			this.getNext().setVisible(true);
			Page curretPage = TicketManager.getInstance().getReserveSeat(
					pageNo, Constants.DEFAULT_PAGE_SIZE, sleBusserDay);
			totalPageNo = curretPage.getTotalPageCount();
			totalCount = curretPage.getTotalCount();
			pageSize = curretPage.getPageSize();
			getLb_total().setText(
					"�ܼ�" + Long.toString(totalCount) + "�� ÿҳ"
							+ Integer.toString(pageSize) + "�� ��"
							+ Integer.toString(pageNo) + "ҳ/��"
							+ Long.toString(totalPageNo) + "ҳ");
		} else {
			this.getPre().setVisible(false);
			this.getNext().setVisible(false);
			getLb_total().setText("û���ҵ���¼��");
		}
		// �����б�ֵ
		setData(reserveSeatS);

		if (seatTable == null) {
			seatTable = new JTable(new DefaultTableModel(data, columnName) {
				private static final long serialVersionUID = 1L;

				public boolean isCellEditable(int row, int clo) {
					if (clo == 0 && row < reserveSeatS.size()) {
						return true;
					} else {
						return false;
					}
				}

				public void setValueAt(Object value, int row, int col) {
					data[row][col] = value;
				}

				public Object getValueAt(int row, int col) {
					return data[row][col];
				}

				@SuppressWarnings("unchecked")
				public Class getColumnClass(int c) {
					if (c == 6) {
						return ImageIcon.class;
					} else {
						return super.getColumnClass(c);
					}
				}
			});
			seatTable.setRowHeight(27);
			seatTable.getTableHeader().setFont(new Font("����", Font.BOLD, 16));

			// ���õ�һ������ΪBoolean����
			TableColumn column0 = seatTable.getColumnModel().getColumn(0);
			column0.setCellEditor(seatTable.getDefaultEditor(Boolean.class));
			column0
					.setCellRenderer(seatTable
							.getDefaultRenderer(Boolean.class));
			column0.setPreferredWidth(20);
			// ����render����
			render = new MyTableCellRenderer();
			render.setHorizontalAlignment(JLabel.CENTER);
			// render.setToolTipText("˫�����κŲ鿴��ϸ��Ϣ");

			TableColumn column1 = seatTable.getColumnModel().getColumn(1);
			column1.setCellRenderer(render);

			TableColumn column2 = seatTable.getColumnModel().getColumn(2);
			column2.setCellRenderer(render);

			TableColumn column3 = seatTable.getColumnModel().getColumn(3);
			column3.setCellRenderer(render);

			TableColumn column4 = seatTable.getColumnModel().getColumn(4);
			column4.setCellRenderer(render);

			TableColumn column5 = seatTable.getColumnModel().getColumn(5);
			column5.setCellRenderer(render);

			TableColumn column6 = seatTable.getColumnModel().getColumn(6);
			column6.setPreferredWidth(60);

			final JPanel jp = this;
			seatTable.addMouseListener(new MouseAdapter() {
				public void mouseClicked(MouseEvent e) {
					// ��ӡƱ����Ϣ
					if ((e.getClickCount() == 1)
							&& (e.getButton() == MouseEvent.BUTTON1)) {
						if (seatTable.getSelectedColumn() == 6) {
							int row = seatTable.getSelectedRow();
							if (data[row][1] != null) {
								// ��֤����ʱ���Ƿ����
								Boolean flag = tickePanel.checkdate(sleBusserDay);
								if (flag) {
									int seatNo = Integer.parseInt(data[row][2]
											.toString());

									// ���Ʊ����Ϣ
									TicketLog ticketLog = new TicketLog();
									ticketLog.setBusSerno(sleBusserDay.getBusSerNo());
									ticketLog.setSerdayId(sleBusserDay.getSerdayId());
									ticketLog.setStartAddr(currLine.getStartAddr());
									ticketLog.setEndAddr(currLine.getEndAddr());
									ticketLog.setDepartDate(sleBusserDay.getDepartDate());
									ticketLog.setDepartTime(currBusSer.getDepartTime());
									ticketLog.setMemo(getJTextPane_desc().getText());
									ticketLog.setBusSerno(sleBusserDay.getBusSerNo());
									ticketLog.setSeatNo(seatNo);
									ticketLog.setPrintTime(new Date());

									//����֧����ʽ��Ʊ������
								    printRerTickDlg = new PrintRerTickDlg(indexFrame,ticketLog);
									printRerTickDlg.show(); 
									if (printRerTickDlg.getIsOk()) {
										ticketLog = printRerTickDlg.getTicketLog();
										// ��ӡ��Ʊ����¼��Ʊ��¼
										try {
											TicketManager.getInstance().PrintRerTicket(ticketLog);
											JOptionPane.showMessageDialog(jp,"��ӡԤ��Ʊ��ɹ�", "SUCCESS",JOptionPane.NO_OPTION);
										} catch (Exception e2) {
											JOptionPane.showMessageDialog(jp,e2.getMessage(),"ERROE!!!",JOptionPane.ERROR_MESSAGE);
										}
										data[row][0] = Boolean.FALSE;
										deleteCount++;
										getSeatTable();
										getSeat_result().setVisible(false);
										getSeat_result().setVisible(true);
									}
								}
							}

						}
					}
				}
			});
		} else {
			seatTable.updateUI();
			seatTable.repaint();
		}
		return seatTable;
	}

	/**
	 * This method initializes bt_delete
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_delete() {
		if (bt_delete == null) {
			bt_delete = new JButton();
			bt_delete.setBounds(new Rectangle(110, 4, 87, 27));
			bt_delete.setText("ȡ��Ԥ��");
			final JPanel jp = this;
			bt_delete.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_delete.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					boolean select_one = false; // �ж���û��ѡ��ı�־������Ҫѡ��һ��
					for (int i = 0; i < data.length; i++) {
						if (data[i][0] == Boolean.TRUE) {
							select_one = Boolean.TRUE;
						}
					}
					if (select_one == Boolean.FALSE) { // û��ѡ��
						JOptionPane.showMessageDialog(jp, "����ѡ��һ��", "ȡ��Ԥ��Ʊ",
								JOptionPane.WARNING_MESSAGE);
					} else { // ����ѡ����һ��
						int result = JOptionPane.showConfirmDialog(jp,
								"ȷ����ѡԤ��Ʊȡ��Ԥ��", "ȡ��Ԥ��Ʊ",
								JOptionPane.WARNING_MESSAGE);
						if (result == 0) { // ȷ��ֵΪ0��ȡ��ֵΪ1
							List<Seat> selSeatS = new ArrayList<Seat>();
							for (int i = 0; i < data.length; i++) {
								if (data[i][0] == Boolean.TRUE) { // data[i][0]==Boolean.TRUE��ʾ�������ݱ�ѡ��
									String seatId = data[i][1].toString();
									@SuppressWarnings("unused")
									Seat sleSeat = TicketManager.getInstance()
											.getSeat(seatId);
									selSeatS.add(sleSeat);
									data[i][0] = Boolean.FALSE;
									deleteCount++;
								}
							}
							// ��Ԥ��Ʊ��Ϊ������Ʊ
							if (selSeatS.size() > 0) {
								try {
									TicketManager.getInstance().cancelReserve(
											selSeatS);
								} catch (Exception e1) {
									JOptionPane.showMessageDialog(jp, e1
											.getMessage(), "ERROE!!!",
											JOptionPane.ERROR_MESSAGE);
									e1.printStackTrace();
								}
							}
							getSeatTable();
							getSelect_all().setSelected(false);
							getSeat_result().setVisible(false);
							getSeat_result().setVisible(true);
						}
					}
				}
			});

		}
		return bt_delete;
	}

	/**
	 * ����Ԥ����λ�б�ֵ
	 * 
	 * @param reserveSeatS
	 */
	private void setData(List<Seat> reserveSeatS) {
		if (reserveSeatS != null) {
			for (int i = 0; i < data.length; i++) {
				data[i][0] = false;
				data[i][1] = null;
				data[i][2] = null;
				data[i][3] = null;
				data[i][4] = null;
				data[i][5] = null;
				data[i][6] = null;
			}
			for (int i = 0; i < reserveSeatS.size(); i++) {
				data[i][0] = false;
				Seat mySeat = (Seat) reserveSeatS.get(i);
				// data[i][1] = mySeat.getSeatNo();
				// data[i][2] = sleBusserDay.getSerdayId();
				data[i][1] = mySeat.getId();
				data[i][2] = mySeat.getSeatNo();
				// ��ȡ��������
				String oldDepartDate = sleBusserDay.getDepartDate();
				String departDate = oldDepartDate.substring(0, 4) + "-"
						+ oldDepartDate.substring(4, 6) + "-"
						+ oldDepartDate.substring(6, oldDepartDate.length());

				String oldDepartTime = currBusSer.getDepartTime();
				String departTime = oldDepartTime.substring(0, 2) + ":"
						+ oldDepartTime.substring(2, 4) + ":"
						+ oldDepartTime.substring(4, oldDepartTime.length());
				data[i][3] = departDate + " " + departTime;
				// ��ȡ��Ӧ�İ����Ϣ
				data[i][4] = currBusSer.getLineName();
				// ��ȡ·����Ϣ
				data[i][5] = mySeat.getMemo();
				data[i][6] = this
						.getIcon("com/sungard/ticketsys/image/print.png");
			}
		}
	}

	private JLabel getLb_total() {
		if (lb_total == null) {
			lb_total = new JLabel();
			lb_total.setBounds(new Rectangle(550, 8, 220, 18));
		}
		return lb_total;
	}

	/**
	 * This method initializes select_all
	 * 
	 * @return javax.swing.JCheckBox
	 */
	public JCheckBox getSelect_all() {
		if (select_all == null) {
			select_all = new JCheckBox();
			select_all.setBounds(new Rectangle(9, 4, 96, 21));
			select_all.setText("ȫѡ/ȡ��");
			select_all.addItemListener(new ItemListener() {
				public void itemStateChanged(ItemEvent e) {
					if (select_all.isSelected()) {
						for (int i = 0; i < reserveSeatS.size(); i++) {
							data[i][0] = Boolean.TRUE;
						}
					} else {
						for (int i = 0; i < data.length; i++) {
							data[i][0] = Boolean.FALSE;
						}
					}
					// repaint()�ػ�����ͼ��user.updateUI()ˢ��user��
					seatTable.repaint();
					getSerSet_list().setVisible(false);
					getSerSet_list().setVisible(true);
				}
			});
		}
		return select_all;
	}

	/**
	 * This method initializes pre
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getPre() {
		if (pre == null) {
			pre = new JButton();
			pre.setBounds(new Rectangle(430, 8, 55, 18));
			pre.setText("<<<");
			pre.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			pre.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (pageNo > 1) {
						pageNo--;
						getSeatTable();
						getSelect_all().setSelected(false);
						getSeat_result().setVisible(false);
						getSeat_result().setVisible(true);
					}
				}
			});
		}
		return pre;
	}

	/**
	 * This method initializes next
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getNext() {
		if (next == null) {
			next = new JButton();
			next.setBounds(new Rectangle(490, 8, 55, 18));
			next.setText(">>>");
			next.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			next.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (pageNo < totalPageNo) {
						pageNo++;
						getSeatTable();
						getSelect_all().setSelected(false);
						getSeat_result().setVisible(false);
						getSeat_result().setVisible(true);
					}
				}
			});
		}
		return next;
	}

	/**
	 * ��ȡͼƬ��Դ
	 * 
	 * @param url
	 * @return
	 */
	private ImageIcon getIcon(String url) {
		ClassLoader cl = this.getClass().getClassLoader();
		ImageIcon icon = new ImageIcon(cl.getResource(url));
		return icon;
	}

	public void setInfo_BusserDay(BusserDay sleBusserDay) {
		this.sleBusserDay = sleBusserDay;
		this.currBusSer = BusSerManager.getInstance().getBusSer(
				sleBusserDay.getBusSerNo());
		this.currLine = LineManager.getInstance().getLine(
				currBusSer.getLineName());
	}

}
