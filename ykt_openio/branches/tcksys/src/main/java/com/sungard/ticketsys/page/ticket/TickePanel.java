package com.sungard.ticketsys.page.ticket;

import java.awt.Cursor;
import java.awt.Font;
import java.awt.Point;
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
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;

import org.apache.log4j.Logger;

import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.BusserDay;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.page.CalendarDlg;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.page.MyTableCellRenderer;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;
import com.sungard.ticketsys.service.SerSetManager;
import com.sungard.ticketsys.service.TicketManager;
import com.sungard.ticketsys.common.Constants;
import com.sungard.ticketsys.common.Page;

public class TickePanel extends JPanel {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(TickePanel.class);

	private IndexFrame indexFrame = null;

	private JPanel serSet_search = null;

	private JLabel lb_serdayId = null;
	private JLabel lb_serilNo = null;
	private JLabel lb_startaddr = null;
	private JLabel lb_endaddr = null;
	private JLabel lb_departDate = null;

	private JButton bt_search = null;
	private JButton bt_reset = null;
	private JComboBox cb_serilNo = null;
	private JTextField tf_serdayId = null;
	private JTextField tf_startaddr = null;
	private JTextField tf_endaddr = null;

	private JTextField tf_startDate = null;
	private JButton bt_startDate = null;
	private CalendarDlg StartcalendarDlg = new CalendarDlg(indexFrame);

	public JTable serSet = null;

	// ��ѯ���
	private JPanel serSet_result = null;
	private JScrollPane serSet_list = null;
	private JPanel serSet_op = null;
	private JButton bt_delete = null;
	private MyTableCellRenderer render = null;

	// �б����
	private Object data[][] = new Object[Constants.DEFAULT_PAGE_SIZE][11];
	private Object columnName[] = { "", "���κ�", "��������", "����ʱ��", "��Ʊ��", "Ԥ��Ʊ��",
			"ʣ��Ʊ��", "���վ", "�յ�վ", "��Ʊ", "Ԥ��Ʊ" };

	// ��ҳ���
	private int pageNo = 1;
	private long totalCount = 0;
	private long totalPageNo = 0;
	private int pageSize = 0;
	private JCheckBox select_all = null;
	private JButton pre = null;
	private JButton next = null;
	private JLabel lb_total = null;

	public BusserDay searchSerSet = new BusserDay();
	public String DepartTime = null;
	public String startAddr = null;
	public String endAddr = null;
	private List<BusserDay> serSets = null;

	private boolean isSearch = false;

	private int deleteCount = 0;

	// ������ϸ��Ϣҳ��
	public SerSetDetail serSetDetail = null;
	// ��Ʊҳ��
	public SaleTicket saleTicket = null;
	public TicketDlg ticketDlg = null;
	// Ԥ��Ʊҳ��
	public ReserveTicket reserveTicket = null;
	public ReserveTickDlg reserveTickDlg = null;

	protected TickePanel() {
	}

	public TickePanel(IndexFrame indexFrame) {
		this.indexFrame = indexFrame;
		initComponents();
	}

	/**
	 * This method initializes this
	 * 
	 * @return void
	 */
	private void initComponents() {
		this.setSize(890, 630);
		this.setLayout(null);
		// ��ѯpanel
		this.add(getSerSet_search(), null);
		// ��ѯ�б�panel
		this.add(getSerSet_result(), null);
		// ����panel
//		this.add(getSaleTicket(), null);
		// ��ϸpanel
//		this.add(getSerSet_detail(), null);
		// Ԥ��Ʊpanel
//		this.add(getReserveTicket(), null);
	}

//	/**
//	 * Ԥ��Ʊpanel
//	 * 
//	 * @return
//	 */
//	public ReserveTicket getReserveTicket() {
//		if (reserveTicket == null) {
//			reserveTicket = new ReserveTicket(this,indexFrame);
//			reserveTicket.setVisible(false);
//		}
//		return reserveTicket;
//	}

//	/**
//	 * ������ϸpanel
//	 * 
//	 * @return
//	 */
//	public SerSetDetail getSerSet_detail() {
//		if (serSetDetail == null) {
//			serSetDetail = new SerSetDetail(this);
//			serSetDetail.setVisible(false);
//		}
//		return serSetDetail;
//	}

//	/**
//	 * ��Ʊpanel
//	 * 
//	 * @return
//	 */
//	public SaleTicket getSaleTicket() {
//		if (saleTicket == null) {
//			saleTicket = new SaleTicket(this);
//			saleTicket.setVisible(false);
//		}
//		return saleTicket;
//	}

	/**
	 * ��ѯpanel
	 * 
	 * @return
	 */
	public JPanel getSerSet_search() {
		if (serSet_search == null) {
			lb_serdayId = new JLabel();
			lb_serdayId.setBounds(new Rectangle(50, 30, 80, 30));
			lb_serdayId.setText("���κţ�");
			lb_serilNo = new JLabel();
			lb_serilNo.setBounds(new Rectangle(420, 30, 80, 30));
			lb_serilNo.setText("��κţ�");

			lb_startaddr = new JLabel();
			lb_startaddr.setBounds(new Rectangle(50, 80, 80, 30));
			lb_startaddr.setText("���վ��");
			lb_endaddr = new JLabel();
			lb_endaddr.setBounds(new Rectangle(420, 80, 80, 30));
			lb_endaddr.setText("�յ�վ��");

			lb_departDate = new JLabel();
			lb_departDate.setBounds(new Rectangle(50, 130, 80, 30));
			lb_departDate.setText("�������ڣ�");

			serSet_search = new JPanel();
			serSet_search.setLayout(null);
			serSet_search.setBounds(new Rectangle(10, 10, 780, 180));
			serSet_search.setBorder(BorderFactory.createTitledBorder("��ѯ��������"));
			serSet_search.add(lb_serdayId, null);
			serSet_search.add(getTf_serdayId(), null);
			serSet_search.add(lb_serilNo, null);
			serSet_search.add(getCb_serilNo(), null);

			serSet_search.add(lb_startaddr, null);
			serSet_search.add(getTf_startaddr(), null);
			serSet_search.add(lb_endaddr, null);
			serSet_search.add(getTf_endaddr(), null);

			serSet_search.add(lb_departDate, null);
			serSet_search.add(getTf_startDate(), null);
			serSet_search.add(getBt_startDate(), null);

			serSet_search.add(getBt_search(), null);
			serSet_search.add(getBt_reset(), null);

		}
		return serSet_search;
	}

	/**
	 * This method initializes bt_reset
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_reset() {
		if (bt_reset == null) {
			bt_reset = new JButton();
			bt_reset.setBounds(new Rectangle(630, 130, 70, 30));
			bt_reset.setText("����");
			bt_reset.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_reset.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					getTf_serdayId().setText("");
					getCb_serilNo().setSelectedIndex(0);
					getTf_endaddr().setText("");
					getTf_startaddr().setText("");
					getTf_startDate().setText("");
					StartcalendarDlg.setValue(null);
					
					getSerSet();
					getSelect_all().setSelected(false);
					getSerSet_result().setVisible(false);
					getSerSet_result().setVisible(true);
				}
			});
		}
		return bt_reset;
	}

	private JButton getBt_startDate() {
		if (bt_startDate == null) {
			bt_startDate = new JButton();
			bt_startDate.setBounds(new Rectangle(330, 134, 20, 20));
			bt_startDate
					.setIcon(getIcon("com/sungard/ticketsys/image/calendar.gif"));
			bt_startDate.setCursor(Cursor
					.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_startDate.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					if (StartcalendarDlg == null) {
						StartcalendarDlg = new CalendarDlg(indexFrame);
					}
					Point p =  bt_startDate.getLocationOnScreen(); 
					p.y = p.y + bt_startDate.getHeight(); 
					StartcalendarDlg.setLocation(p);
					StartcalendarDlg.show();
					if(StartcalendarDlg.getValue()!=null){
						SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
						String date = sdf.format(StartcalendarDlg.getValue());
						getTf_startDate().setText(date);
					}
					
				}
			});
		}

		return bt_startDate;
	}

	private JTextField getTf_startDate() {
		if (tf_startDate == null) {
			tf_startDate = new JTextField();
			tf_startDate.setBounds(new Rectangle(130, 130, 200, 30));
		}
		return tf_startDate;
	}

	/**
	 * This method initializes tf_startaddr
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_startaddr() {
		if (tf_startaddr == null) {
			tf_startaddr = new JTextField();
			tf_startaddr.setBounds(new Rectangle(130, 80, 220, 30));
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
			tf_endaddr.setBounds(new Rectangle(500, 80, 220, 30));
		}
		return tf_endaddr;
	}

	/**
	 * This method initializes tf_serilNo
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_serdayId() {
		if (tf_serdayId == null) {
			tf_serdayId = new JTextField();
			tf_serdayId.setBounds(new Rectangle(130, 30, 220, 30));

		}
		return tf_serdayId;
	}

	/**
	 * This method initializes cb_linename
	 * 
	 * @return javax.swing.JComboBox
	 */
	private JComboBox getCb_serilNo() {
		if (cb_serilNo == null) {
			cb_serilNo = new JComboBox();
			cb_serilNo.setBounds(new Rectangle(500, 30, 220, 30));
			cb_serilNo.addItem("-------- ��ѡ�� --------");
			List<BusSer> busSers = BusSerManager.getInstance()
					.getAllBusSer();
			for (int i = 0; i < busSers.size(); i++) {
				BusSer myBusSer = (BusSer) busSers.get(i);
				cb_serilNo.addItem(myBusSer.getSerilNo());
			}
			
			cb_serilNo.addPopupMenuListener(new PopupMenuListener() {
				public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
					cb_serilNo.removeAllItems();
					cb_serilNo.addItem("-------- ��ѡ�� --------");
					List<BusSer> busSers = BusSerManager.getInstance()
							.getAllBusSer();
					for (int i = 0; i < busSers.size(); i++) {
						BusSer myBusSer = (BusSer) busSers.get(i);
						cb_serilNo.addItem(myBusSer.getSerilNo());
					}
				}

				public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
				}

				public void popupMenuCanceled(PopupMenuEvent e) {
				}
			});
		}
		return cb_serilNo;
	}

	/**
	 * This method initializes bt_search
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_search() {
		if (bt_search == null) {
			bt_search = new JButton();
			bt_search.setBounds(new Rectangle(520, 130, 70, 30));
			bt_search.setText("�� ѯ");
			bt_search.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_search.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					pageNo = 1;
					isSearch = true;
					
					getSerSet();
					getSelect_all().setSelected(false);
					getSerSet_result().setVisible(false);
					getSerSet_result().setVisible(true);
				}
			});
		}

		return bt_search;
	}

	/**
	 * ��ѯ�б�panel
	 * 
	 * @return javax.swing.JPanel
	 */
	public JPanel getSerSet_result() {
		if (serSet_result == null) {
			serSet_result = new JPanel();
			serSet_result.setLayout(null);
			serSet_result.setBounds(new Rectangle(10, 200, 780, 420));
			serSet_result.setBorder(BorderFactory.createTitledBorder("������Ϣ�б�"));
			serSet_result.add(getSerSet_list(), null);
			serSet_result.add(getSerSet_op(), null);
		}
		return serSet_result;
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
			serSet_list.setViewportView(getSerSet());
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
			serSet_op.setBounds(new Rectangle(20, 330, 750, 80));
			serSet_op.add(getSelect_all(), null);
			serSet_op.add(getPre(), null);
			serSet_op.add(getNext(), null);
			serSet_op.add(getBt_delete(), null);
			serSet_op.add(getLb_total(), null);
		}
		return serSet_op;
	}

	/**
	 * This method initializes bt_delete
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_delete() {
		if (bt_delete == null) {
			bt_delete = new JButton();
			bt_delete.setBounds(new Rectangle(13, 39, 87, 27));
			bt_delete.setText("ֹͣ��Ʊ");
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
						JOptionPane.showMessageDialog(indexFrame
								.getSerSetPanel(), "����ѡ��һ��", "ֹͣ������Ʊ",
								JOptionPane.WARNING_MESSAGE);
					} else { // ����ѡ����һ��
						int result = JOptionPane.showConfirmDialog(indexFrame
								.getSerSetPanel(), "ȷ����ѡ����ֹͣ��Ʊ", "ֹͣ������Ʊ",
								JOptionPane.WARNING_MESSAGE);
						if (result == 0) { // ȷ��ֵΪ0��ȡ��ֵΪ1
							List<BusserDay> selBusserDayS = new ArrayList<BusserDay>();
							;
							for (int i = 0; i < data.length; i++) {
								if (data[i][0] == Boolean.TRUE) { // data[i][0]==Boolean.TRUE��ʾ�������ݱ�ѡ��
									String serdayId = data[i][1].toString();
									@SuppressWarnings("unused")
									BusserDay newBusserDay = SerSetManager
											.getInstance().getBusserDay(
													serdayId);
									selBusserDayS.add(newBusserDay);
									data[i][0] = Boolean.FALSE;
									deleteCount++;
								}
							}
							// �ѳ���״̬��Ϊֹͣ��Ʊ
							if (selBusserDayS != null) {
								try {
									TicketManager.getInstance().stopSale(
											selBusserDayS);
								} catch (Exception e1) {
									JOptionPane.showMessageDialog(indexFrame
											.getSerSetPanel(), e1.getMessage(),
											"ERROE!!!",
											JOptionPane.ERROR_MESSAGE);
									e1.printStackTrace();
								}
							}
							isSearch = true;
							getSerSet();
							getSelect_all().setSelected(false);
							getSerSet_result().setVisible(false);
							getSerSet_result().setVisible(true);
						}
					}
				}
			});

		}
		return bt_delete;
	}

	/**
	 * This method initializes user
	 * 
	 * @return javax.swing.JTable
	 */
	public JTable getSerSet() {
		if (!isSearch) {
			getTf_serdayId().setText("");
			getCb_serilNo().setSelectedIndex(0);
			getTf_endaddr().setText("");
			getTf_startaddr().setText("");
			getTf_startDate().setText("");
			StartcalendarDlg.setValue(null);
		}
		isSearch = false;
		if (serSets != null) {
			if (deleteCount == serSets.size() && pageNo > 1) {
				pageNo--;
			}
			deleteCount = 0;
		}
		
		// ���ò�ѯ����
		getCondion();
		
		serSets = SerSetManager.getInstance().getSerSetByConditions(pageNo,
				Constants.DEFAULT_PAGE_SIZE, searchSerSet, DepartTime,
				startAddr, endAddr, "departDate");
		
		

		if (serSets.size() > 0) {
			this.getPre().setVisible(true);
			this.getNext().setVisible(true);
			Page curretPage = SerSetManager.getInstance().getPageByConditions(
					pageNo, Constants.DEFAULT_PAGE_SIZE, searchSerSet,
					DepartTime, startAddr, endAddr, null);
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
		setData(serSets);

		if (serSet == null) {
			serSet = new JTable(new DefaultTableModel(data, columnName) {
				private static final long serialVersionUID = 1L;

				public boolean isCellEditable(int row, int clo) {
					if (clo == 0 && row < serSets.size()) {
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
					if (c == 10 || c == 9) {
						return ImageIcon.class;
					} else {
						return super.getColumnClass(c);
					}
				}
			});
			serSet.setRowHeight(27);
			serSet.getTableHeader().setFont(new Font("����", Font.BOLD, 16));

			// ���õ�һ������ΪBoolean����
			TableColumn column0 = serSet.getColumnModel().getColumn(0);
			column0.setCellEditor(serSet.getDefaultEditor(Boolean.class));
			column0.setCellRenderer(serSet.getDefaultRenderer(Boolean.class));
			column0.setPreferredWidth(20);
			// ����render����
			render = new MyTableCellRenderer();
			render.setHorizontalAlignment(JLabel.CENTER);
//			render.setToolTipText("˫�����κŲ鿴��ϸ��Ϣ");

			TableColumn column1 = serSet.getColumnModel().getColumn(1);
			column1.setCellRenderer(render);

			TableColumn column2 = serSet.getColumnModel().getColumn(2);
			column2.setCellRenderer(render);

			TableColumn column3 = serSet.getColumnModel().getColumn(3);
			column3.setCellRenderer(render);

			TableColumn column4 = serSet.getColumnModel().getColumn(4);
			column4.setCellRenderer(render);

			TableColumn column5 = serSet.getColumnModel().getColumn(5);
			column5.setCellRenderer(render);

			TableColumn column6 = serSet.getColumnModel().getColumn(6);
			column6.setCellRenderer(render);

			TableColumn column7 = serSet.getColumnModel().getColumn(7);
			column7.setCellRenderer(render);

			TableColumn column8 = serSet.getColumnModel().getColumn(8);
			column8.setPreferredWidth(50);
			column8.setCellRenderer(render);

			TableColumn column9 = serSet.getColumnModel().getColumn(9);
			column9.setPreferredWidth(50);

			TableColumn column10 = serSet.getColumnModel().getColumn(10);
			column10.setPreferredWidth(50);

			// ������˫���鿴��ϸ��Ϣ�¼�
			serSet.addMouseListener(new MouseAdapter() {
				public void mouseClicked(MouseEvent e) {
//					if ((e.getClickCount() == 2)
//							&& (e.getButton() == MouseEvent.BUTTON1)) {
//						// �鿴��ϸ��Ϣ
//						if (serSet.getSelectedColumn() == 1) {
//							int row = serSet.getSelectedRow();
//							String sleSerdayId = data[row][1].toString();
//							if (sleSerdayId != null) {
//								BusserDay sleBusserDay = SerSetManager.getInstance().getBusserDay(sleSerdayId);
//									serSetDetail.setInfo_serSet(sleBusserDay);
//									hideOtherPanel();
//									getSerSet_detail().setVisible(true);
//									IndexFrame.target = 3;
//							}
//
//						}
//					}

					if ((e.getClickCount() == 1)
							&& (e.getButton() == MouseEvent.BUTTON1)) {
						// ��Ʊ
						if (serSet.getSelectedColumn() == 9) {
							int row = serSet.getSelectedRow();
							if(data[row][1]!=null){
								String sleSerdayId = data[row][1].toString();
								BusserDay sleBusserDay = SerSetManager.getInstance().getBusserDay(sleSerdayId);
								Boolean flag = checkdate(sleBusserDay);
								if(flag){
									ticketDlg = new TicketDlg(indexFrame, indexFrame.getTickePanel());
									ticketDlg.setInfo_Ticket(sleBusserDay);
									ticketDlg.show();
									
//									saleTicket.setInfo_Ticket(sleBusserDay);
//									hideOtherPanel();
//									getSaleTicket().setVisible(true);
//									IndexFrame.target = 3;
								}
							}
							
						}
						// Ԥ��Ʊ
						if (serSet.getSelectedColumn() == 10) {
							int row = serSet.getSelectedRow();
							if(data[row][1]!=null){
								String sleSerdayId = data[row][1].toString();
								BusserDay sleBusserDay = SerSetManager.getInstance().getBusserDay(sleSerdayId);
								Boolean flag = checkdate(sleBusserDay);
								if(flag){
									
									reserveTickDlg = new ReserveTickDlg(indexFrame, indexFrame.getTickePanel());
									reserveTickDlg.setInfo_BusserDay(sleBusserDay);
									reserveTickDlg.show();
									
//									reserveTicket.setInfo_BusserDay(sleBusserDay);
//									hideOtherPanel();
//									reserveTicket.getSeatTable();
//									getReserveTicket().setVisible(true);
//									IndexFrame.target = 3;
								}
							}
							
						}
					}
				}

			});
		} else {
			serSet.updateUI();
			serSet.repaint();
		}
		return serSet;
	}
	
	/**
	 * ��ȡ��ѯ����
	 */
	private void getCondion() {
		searchSerSet.setSerdayId("");
		searchSerSet.setBusSerNo("");
		if (!"".equals(getTf_serdayId().getText().trim())) {
			try {
				searchSerSet
						.setSerdayId(getTf_serdayId().getText());
			} catch (Exception e2) {
			}
		}

		if (getCb_serilNo().getSelectedIndex() != 0) {
			String serilNo = getCb_serilNo().getSelectedItem()
					.toString().trim();
			searchSerSet.setBusSerNo(serilNo);
		}

		DepartTime = getTf_startDate().getText().trim();
		startAddr = getTf_startaddr().getText().trim();
		endAddr = getTf_endaddr().getText().trim();
	}


	/**
	 * ��֤����ʱ���Ƿ����
	 * @param sleBusserDay
	 * @return
	 */
	public Boolean checkdate(BusserDay sleBusserDay) {
		final JPanel jp = this;
		boolean flag = true;
		//�жϳ����Ƿ��ѹ���
		Date now = new Date();
		Calendar cnow = Calendar.getInstance();
		cnow.setTime(now);

		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		Date departTime = null;
		BusSer currBusSer = BusSerManager.getInstance().getBusSer(sleBusserDay.getBusSerNo());
		
		try {
			departTime = sdf.parse(sleBusserDay.getDepartDate()+ currBusSer.getDepartTime());
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Calendar cdepartTime = Calendar.getInstance();
		cdepartTime.setTime(departTime);
		if (cnow.after(cdepartTime)) {
			logger.error("����ʱ���ѹ���������Ʊ��Ԥ��Ʊ");
			JOptionPane.showMessageDialog(jp, "����ʱ���ѹ���������Ʊ��Ԥ��Ʊ!",
					"ERROE!!!", JOptionPane.ERROR_MESSAGE);
			flag = false;
		}
		
		return flag;
	}

	private void setData(List<BusserDay> serSetList) {
		if (serSetList != null) {
			for (int i = 0; i < data.length; i++) {
				data[i][0] = false;
				data[i][1] = null;
				data[i][2] = null;
				data[i][3] = null;
				data[i][4] = null;
				data[i][5] = null;
				data[i][6] = null;
				data[i][7] = null;
				data[i][8] = null;
				data[i][9] = null;
				data[i][10] = null;
			}

			for (int i = 0; i < serSetList.size(); i++) {
				BusserDay mySerSet = (BusserDay) serSetList.get(i);
				data[i][1] = mySerSet.getSerdayId();
				// ��������
				String oldDepartDate = mySerSet.getDepartDate();
				data[i][2] = oldDepartDate.substring(0, 4) + "-"
						+ oldDepartDate.substring(4, 6) + "-"
						+ oldDepartDate.substring(6, oldDepartDate.length());
				// ��ȡ��Ӧ�İ����Ϣ
				BusSer currBusSer = BusSerManager.getInstance().getBusSer(
						mySerSet.getBusSerNo());
				// ����ʱ��
				String oldDepartTime = currBusSer.getDepartTime();
				data[i][3] = oldDepartTime.substring(0, 2) + ":"
						+ oldDepartTime.substring(2, 4) + ":"
						+ oldDepartTime.substring(4, oldDepartTime.length());
				data[i][4] = mySerSet.getTicketCount();
				data[i][5] = mySerSet.getReserveCount();
				data[i][6] = mySerSet.getRemainCount();

				// ��ȡ·����Ϣ
				Line currLine = LineManager.getInstance().getLine(
						currBusSer.getLineName());
				data[i][7] = currLine.getStartAddr();
				data[i][8] = currLine.getEndAddr();
				data[i][9] = this
						.getIcon("com/sungard/ticketsys/image/print.png");
				data[i][10] = this
						.getIcon("com/sungard/ticketsys/image/viewer.png");
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
						for (int i = 0; i < serSets.size(); i++) {
							data[i][0] = Boolean.TRUE;
						}
					} else {
						for (int i = 0; i < data.length; i++) {
							data[i][0] = Boolean.FALSE;
						}
					}
					// repaint()�ػ�����ͼ��user.updateUI()ˢ��user��
					serSet.repaint();
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
						isSearch = true;
						getSerSet();
						getSelect_all().setSelected(false);
						getSerSet_result().setVisible(false);
						getSerSet_result().setVisible(true);
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
						isSearch = true;
						getSerSet();
						getSelect_all().setSelected(false);
						getSerSet_result().setVisible(false);
						getSerSet_result().setVisible(true);
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

	public void hideOtherPanel() {
		if (serSetDetail != null) {
			serSetDetail.setVisible(false);
		}
		if (saleTicket != null) {
			saleTicket.setVisible(false);
		}
		if (reserveTicket != null) {
			reserveTicket.setVisible(false);
		}
		if (serSet_search != null) {
			serSet_search.setVisible(false);
		}
		if (serSet_result != null) {
			serSet_result.setVisible(false);
		}
	}

}
