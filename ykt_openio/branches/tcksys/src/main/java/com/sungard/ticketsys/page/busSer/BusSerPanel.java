package com.sungard.ticketsys.page.busSer;

import java.awt.Cursor;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
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

import com.sungard.ticketsys.common.Constants;
import com.sungard.ticketsys.model.BusSer;
import com.sungard.ticketsys.model.Line;
import com.sungard.ticketsys.IndexFrame;
import com.sungard.ticketsys.page.MyTableCellRenderer;
import com.sungard.ticketsys.service.BusSerManager;
import com.sungard.ticketsys.service.LineManager;
import com.sungard.ticketsys.common.MyFormat;
import com.sungard.ticketsys.common.Page;

public class BusSerPanel extends JPanel {

	private static final long serialVersionUID = 1L;
	private static final Logger logger = Logger.getLogger(BusSerPanel.class);

	private IndexFrame indexFrame = null;

	private JPanel busSer_search = null;
	private JButton bt_reset = null;

	private JLabel lb_serilNo = null;
	private JLabel lb_linename = null;

	private JButton bt_search = null;
	private JTextField tf_serilNo = null;
	private JComboBox cb_linename = null;

	public JTable busSer = null;

	// ��ѯ���
	private JPanel busSer_result = null;
	private JScrollPane busSer_list = null;
	private JPanel busSer_op = null;
	private JButton bt_delete = null;
	private MyTableCellRenderer render = null;

	// �б����
	private Object data[][] = new Object[Constants.DEFAULT_PAGE_SIZE][8];
	private Object columnName[] = { "", "��κ�", "����ʱ��", "·������", "��ͨƱ��(Ԫ)","�ڲ�Ʊ��(Ԫ)","Ʊ������","����" };

	// ��ҳ���
	private int pageNo = 1;
	private long totalCount = 0;
	private long totalPageNo = 0;
	private int pageSize = 0;
	private JCheckBox select_all = null;
	private JButton pre = null;
	private JButton next = null;
	private JLabel lb_total = null;

	// ����
	private JButton bt_add = null;

	public BusSer searchBusSer = new BusSer();

	private List<BusSer> busSers = null;

	private boolean isSearch = false;

	private int deleteCount = 0;

	private BusSerAddDlg newBusSerDlg = null;

	private BusSerDetDlg busSerDetDlg = null;

	private BusSerModifyDlg busSerModDlg = null;

	protected BusSerPanel() {
	}

	public BusSerPanel(IndexFrame indexFrame) {
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
		this.add(getBusSer_search(), null);
		// ��ѯ�б�panel
		this.add(getBusSer_result(), null);
	}

	/**
	 * ��ѯpanel
	 * 
	 * @return
	 */
	public JPanel getBusSer_search() {
		if (busSer_search == null) {
			lb_serilNo = new JLabel();
			lb_serilNo.setBounds(new Rectangle(50, 30, 80, 30));
			lb_serilNo.setText("��κţ�");
			
			lb_linename = new JLabel();
			lb_linename.setBounds(new Rectangle(420, 30, 80, 30));
			lb_linename.setText("·�ߣ�");
			
			busSer_search = new JPanel();
			busSer_search.setLayout(null);
			busSer_search.setBounds(new Rectangle(10, 10, 780, 180));
			busSer_search.setBorder(BorderFactory.createTitledBorder("��ѯ�������"));
			busSer_search.add(lb_serilNo, null);
			busSer_search.add(getTf_serilNo(), null);
			busSer_search.add(lb_linename, null);
			busSer_search.add(getCb_linename(), null);
			busSer_search.add(getBt_search(), null);
			busSer_search.add(getBt_reset(), null);
		}
		return busSer_search;
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
					isSearch = false;
					getBusSer();
					getSelect_all().setSelected(false);
					getBusSer_result().setVisible(false);
					getBusSer_result().setVisible(true);
				}
			});
		}
		return bt_reset;
	}

	/**
	 * This method initializes tf_serilNo
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getTf_serilNo() {
		if (tf_serilNo == null) {
			tf_serilNo = new JTextField();
			tf_serilNo.setBounds(new Rectangle(130, 30, 220, 30));
		}
		return tf_serilNo;
	}

	/**
	 * This method initializes cb_linename
	 * 
	 * @return javax.swing.JComboBox
	 */
	private JComboBox getCb_linename() {
		if (cb_linename == null) {
			cb_linename = new JComboBox();
			cb_linename.setBounds(new Rectangle(500, 30, 220, 30));
			cb_linename.addItem("-------- ��ѡ�� --------");
			List<Line> lines = LineManager.getInstance().getAllLine();
			for (int i = 0; i < lines.size(); i++) {
				Line myLine = (Line) lines.get(i);
				cb_linename.addItem(myLine.getLineName());
			}
			cb_linename.addPopupMenuListener(new PopupMenuListener() {
				public void popupMenuWillBecomeVisible(PopupMenuEvent e) {
					cb_linename.removeAllItems();
					cb_linename.addItem("-------- ��ѡ�� --------");
					List<Line> lines = LineManager.getInstance().getAllLine();
					for (int i = 0; i < lines.size(); i++) {
						Line myLine = (Line) lines.get(i);
						cb_linename.addItem(myLine.getLineName());
					}
				}

				public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
				}

				public void popupMenuCanceled(PopupMenuEvent e) {
				}
			});
		}
		return cb_linename;
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
			bt_search.setText("��ѯ");
			bt_search.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_search.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					pageNo = 1;
					isSearch = true;
					
					getBusSer();
					getSelect_all().setSelected(false);
					getBusSer_result().setVisible(false);
					getBusSer_result().setVisible(true);
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
	public JPanel getBusSer_result() {
		if (busSer_result == null) {
			busSer_result = new JPanel();
			busSer_result.setLayout(null);
			busSer_result.setBounds(new Rectangle(10, 200, 780, 420));
			busSer_result.setBorder(BorderFactory.createTitledBorder("�����Ϣ�б�"));
			busSer_result.add(getBusSer_list(), null);
			busSer_result.add(getBusSer_op(), null);
		}
		return busSer_result;
	}


	/**
	 * This method initializes user_list1
	 * 
	 * @return javax.swing.JScrollPane
	 */
	private JScrollPane getBusSer_list() {
		if (busSer_list == null) {
			busSer_list = new JScrollPane();
			busSer_list.setBounds(new Rectangle(20, 30, 750, 292));
			busSer_list.setViewportView(getBusSer());
		}
		return busSer_list;
	}

	/**
	 * This method initializes busSer_op
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getBusSer_op() {
		if (busSer_op == null) {
			busSer_op = new JPanel();
			busSer_op.setLayout(null);
			busSer_op.setBounds(new Rectangle(20, 330, 750, 80));
			busSer_op.add(getSelect_all(), null);
			busSer_op.add(getPre(), null);
			busSer_op.add(getNext(), null);
			busSer_op.add(getBt_delete(), null);
			busSer_op.add(getBt_add(), null);
			busSer_op.add(getLb_total(), null);
		}
		return busSer_op;
	}

	/**
	 * This method initializes lb_add
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_add() {
		if (bt_add == null) {
			bt_add = new JButton();
			bt_add.setBounds(new Rectangle(13, 39, 87, 27));
			bt_add.setText("��Ӱ��");
			bt_add.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
			bt_add.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
				    newBusSerDlg = new BusSerAddDlg(indexFrame,indexFrame.getBusSerPanel());
					newBusSerDlg.show(); 
				}
			});
		}
		return bt_add;
	}

	/**
	 * This method initializes bt_delete
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getBt_delete() {
		if (bt_delete == null) {
			bt_delete = new JButton();
			bt_delete.setBounds(new Rectangle(121, 39, 87, 27));
			bt_delete.setText("ɾ�����");
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
								.getBusSerPanel(), "����ѡ��һ��", "ɾ�������Ϣ",
								JOptionPane.WARNING_MESSAGE);
					} else { // ����ѡ����һ��
						int result = JOptionPane.showConfirmDialog(indexFrame
								.getBusSerPanel(), "ȷ��ɾ����ѡ����", "ɾ�������Ϣ",
								JOptionPane.WARNING_MESSAGE);
						if (result == 0) { // ȷ��ֵΪ0��ȡ��ֵΪ1
							for (int i = 0; i < data.length; i++) {
								if (data[i][0] == Boolean.TRUE) { // data[i][0]==Boolean.TRUE0��ʾ�������ݱ�ѡ��
									String serilNo = data[i][1].toString();
									boolean isUsed =  BusSerManager.getInstance().busSerIsUsed(serilNo);
									if (isUsed) {
										JOptionPane.showMessageDialog(indexFrame.getBusSerPanel(),"���[" + serilNo+ "]�ѱ�ʹ�ã�����ɾ��","ɾ�����",
														JOptionPane.WARNING_MESSAGE);
									}else{
										try {
											BusSer newBusSer = BusSerManager.getInstance().getBusSer(serilNo);
											BusSerManager.getInstance().removeBusSer(newBusSer);
											data[i][0] = Boolean.FALSE;
											deleteCount++;
										} catch (Exception e2) {
											JOptionPane.showMessageDialog(indexFrame.getBusSerPanel(), "ɾ�����["
													+ serilNo + "]ʧ��!", "ERROE!!!",
													JOptionPane.ERROR_MESSAGE);
										}
										
									}
								
								}
							}
							isSearch = true;
							getBusSer();
							getSelect_all().setSelected(false);
							getBusSer_result().setVisible(false);
							getBusSer_result().setVisible(true);
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
	public JTable getBusSer() {
		if (!isSearch) {
			this.getTf_serilNo().setText("");
			this.getCb_linename().setSelectedIndex(0);
		}
		isSearch = false;
		if (busSers != null) {
			if (deleteCount == busSers.size() && pageNo > 1) {
				pageNo--;
			}
			deleteCount = 0;
		}
		
		// ���ò�ѯ����
		getCondion();
		
		Page curretPage = BusSerManager.getInstance().getBusSerPageByConditions(pageNo, Constants.DEFAULT_PAGE_SIZE,
				searchBusSer,"departTime");
		
		if (curretPage != null && curretPage.getTotalCount() > 0) {
			this.getPre().setVisible(true);
			this.getNext().setVisible(true);
			busSers = (List<BusSer>) curretPage.getResult();
			totalPageNo = curretPage.getTotalPageCount();
			totalCount = curretPage.getTotalCount();
			pageSize = curretPage.getPageSize();
			getLb_total().setText(
					"�ܼ�" + Long.toString(totalCount) + "�� ÿҳ"
							+ Integer.toString(pageSize) + "�� ��"
							+ Integer.toString(pageNo) + "ҳ/��"
							+ Long.toString(totalPageNo) + "ҳ");
		} else {
			busSers =  new ArrayList<BusSer>();
			this.getPre().setVisible(false);
			this.getNext().setVisible(false);
			getLb_total().setText("û���ҵ���¼��");
		}
		//�����б�ֵ
		setData(busSers);
		
		if (busSer == null) {
			busSer = new JTable(new DefaultTableModel(data, columnName) {
				private static final long serialVersionUID = 1L;

				public boolean isCellEditable(int row, int clo) {
					if (clo == 0 && row < busSers.size()) {
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
					if (c == 7) {
						return ImageIcon.class;
					} else {
						return super.getColumnClass(c);
					}
				}
			});
			busSer.setRowHeight(27);
			busSer.getTableHeader().setFont(new Font("����", Font.BOLD, 16));
			
			// ���õ�һ������ΪBoolean����
			TableColumn column0 = busSer.getColumnModel().getColumn(0);
			column0.setCellEditor(busSer.getDefaultEditor(Boolean.class));
			column0.setCellRenderer(busSer.getDefaultRenderer(Boolean.class));
			column0.setPreferredWidth(20);
			// ����render����
			render = new MyTableCellRenderer();
			render.setHorizontalAlignment(JLabel.CENTER);
			render.setToolTipText("˫����κŲ鿴��ϸ��Ϣ");

			TableColumn column1 = busSer.getColumnModel().getColumn(1);
			column1.setCellRenderer(render);

			TableColumn column2 = busSer.getColumnModel().getColumn(2);
			column2.setCellRenderer(render);

			TableColumn column3 = busSer.getColumnModel().getColumn(3);
			column3.setCellRenderer(render);

			TableColumn column4 = busSer.getColumnModel().getColumn(4);
			column4.setCellRenderer(render);
			
			TableColumn column5 = busSer.getColumnModel().getColumn(5);
			column5.setCellRenderer(render);
			
			TableColumn column6 = busSer.getColumnModel().getColumn(6);
			column6.setCellRenderer(render);

			TableColumn column7 = busSer.getColumnModel().getColumn(7);
			column7.setPreferredWidth(30);

			// ������˫���鿴��ϸ��Ϣ�¼�
			busSer.addMouseListener(new MouseAdapter() {
				public void mouseClicked(MouseEvent e) {
					if ((e.getClickCount() == 2)
							&& (e.getButton() == MouseEvent.BUTTON1)) {
						// �鿴��ϸ��Ϣ
						if (busSer.getSelectedColumn() == 1) {
							int row = busSer.getSelectedRow();
							if(data[row][1]!=null){
								try {
									String busSername = data[row][1].toString();
									BusSer busSerinfo = BusSerManager.getInstance().getBusSer(busSername);
									busSerDetDlg= new BusSerDetDlg(indexFrame, indexFrame.getBusSerPanel());
									busSerDetDlg.setInfo_busSer(busSerinfo);
									busSerDetDlg.show(); 
								} catch (Exception e2) {
									logger.error( "��ȡ·��["+ data[row][1] + "]��Ϣʧ��!"+e2.getMessage());
									JOptionPane.showMessageDialog(indexFrame.getBusSerPanel(), "��ȡ·��["
											+ data[row][1] + "]��Ϣʧ��!", "ERROE!!!",
											JOptionPane.ERROR_MESSAGE);
								}
								
							}
						}
					}
					// �༭
					if ((e.getClickCount() == 1)
							&& (e.getButton() == MouseEvent.BUTTON1)) {
						if (busSer.getSelectedColumn() == 7) {
							int row = busSer.getSelectedRow();
							if(data[row][1]!=null){
								try {
									String busSername = data[row][1].toString();
									BusSer busSerinfo = BusSerManager.getInstance().getBusSer(busSername);
									busSerModDlg = new BusSerModifyDlg(indexFrame, indexFrame.getBusSerPanel());
									busSerModDlg.setInfo_BusSer(busSerinfo);
									busSerModDlg.show(); 
								} catch (Exception e2) {
									logger.error( "��ȡ·��["+ data[row][1] + "]��Ϣʧ��!"+e2.getMessage());
									JOptionPane.showMessageDialog(indexFrame.getBusSerPanel(), "��ȡ·��["
											+ data[row][1] + "]��Ϣʧ��!", "ERROE!!!",
											JOptionPane.ERROR_MESSAGE);
								}
							}
							
						}
					}
				}
			});
		} else {
			busSer.updateUI();
			busSer.repaint();
		}
		return busSer;
	}
	
	/**
	 * ��ȡ��ѯ����
	 */
	private void getCondion() {
		searchBusSer.setSerilNo("");
		searchBusSer.setLineName("");
		if (!"".equals(getTf_serilNo().getText().trim())) {
			searchBusSer.setSerilNo(getTf_serilNo().getText()
					.trim());
		}

		if (getCb_linename().getSelectedIndex() != 0) {
			String linename = getCb_linename().getSelectedItem()
					.toString().trim();
			searchBusSer.setLineName(linename);
		}
	}

	/**
	 * �����б�ֵ
	 * @param busSerList
	 */
	private void setData(List<BusSer> busSerList) {
		if (busSerList != null) {
			for (int i = 0; i < data.length; i++) {
				data[i][0] = false;
				data[i][1] = null;
				data[i][2] = null;
				data[i][3] = null;
				data[i][4] = null;
				data[i][5] = null;
				data[i][6] = null;
				data[i][7] = null;
			}
			for (int i = 0; i < busSerList.size(); i++) {
				BusSer myBusSer = (BusSer) busSerList.get(i);
				data[i][1] = myBusSer.getSerilNo();
				data[i][2] = MyFormat.timeSdf(myBusSer.getDepartTime());
				data[i][3] = myBusSer.getLineName();
				data[i][4] = MyFormat.moneySdf(Double.parseDouble(myBusSer.getPrice()));
				data[i][5] = MyFormat.moneySdf(Double.parseDouble(myBusSer.getPerferPrice()));
				data[i][6] =  myBusSer.getMaxCount();
				data[i][7] = this.getIcon("com/sungard/ticketsys/image/btnEdit.gif");
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
						for (int i = 0; i < busSers.size(); i++) {
							data[i][0] = Boolean.TRUE;
						}
					} else {
						for (int i = 0; i < data.length; i++) {
							data[i][0] = Boolean.FALSE;
						}
					}
					// repaint()�ػ�����ͼ��user.updateUI()ˢ��user��
					busSer.repaint();
					getBusSer_list().setVisible(false);
					getBusSer_list().setVisible(true);
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
						getBusSer();
						getSelect_all().setSelected(false);
						getBusSer_result().setVisible(false);
						getBusSer_result().setVisible(true);
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
						getBusSer();
						getSelect_all().setSelected(false);
						getBusSer_result().setVisible(false);
						getBusSer_result().setVisible(true);
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

}
