package com.kingstar.db;

import java.sql.Connection;
import java.sql.Driver;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Date;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Vector;

import com.kingstar.basetask.bean.DataSource;
import com.kingstar.files.DOMParse;

/**
 * ������DBConnectionManager֧�ֶ�һ�������������ļ���������ݿ�����
 * 
 */
public class ConnectPool {
	
	static public ConnectPool instance; // Ψһʵ��
	static public int clients;
	public Vector drivers = new Vector(); // ����
	public Hashtable pools = new Hashtable(); // ����


	public static synchronized ConnectPool getInstance() throws Exception {
		if (instance == null) {
			instance = new ConnectPool();
		}

		clients++;

		return instance;
	}


	public ConnectPool() throws Exception {
		init();
	}

	/**
	 * �����Ӷ��󷵻ظ�������ָ�������ӳ�
	 * @param name
	 *    �������ļ��ж�������ӳ�ID����
	 * @param con
	 *     ���Ӷ���
	 */
	public void freeConnection(int id, Connection con) {
		DBConnectionPool pool = (DBConnectionPool) pools.get(new Integer(id));
		if (pool != null) {
			pool.freeConnection(con);
		} else {
			System.out.println("pool ==null");
		}
		clients--;
	}

	/**
	 * ���һ�����õ�(���е�)����.���û�п�������,������������С����������� ����,�򴴽�������������
	 * 
	 * @param name
	 *            �������ļ��ж�������ӳ�����
	 * @return Connection �������ӻ�null
	 */
	public Connection getConnection(int id) {
		DBConnectionPool pool = (DBConnectionPool) pools.get(new Integer(id));
		if (pool != null) {
			// return pool.getConnection();
			return pool.returnConnection();
		}
		return null;
	}

	/**
	 * ���һ����������.��û�п�������,������������С���������������, �򴴽�������������.����,��ָ����ʱ���ڵȴ������߳��ͷ�����.
	 * 
	 * @param name
	 *            ���ӳ�����
	 * @param time
	 *            �Ժ���Ƶĵȴ�ʱ��
	 * @return Connection �������ӻ�null
	 */
	public Connection getConnection(int id, long time) {
		DBConnectionPool pool = (DBConnectionPool) pools.get(new Integer(id));
		if (pool != null) {
			return pool.getConnection(time);
		}
		return null;
	}

	/**
	 * �ر���������,�������������ע��
	 */
	public synchronized void release() {
		// �ȴ�ֱ�����һ���ͻ��������
		if (--clients != 0) {
			return;
		}

		Enumeration allPools = pools.elements();
		while (allPools.hasMoreElements()) {
			DBConnectionPool pool = (DBConnectionPool) allPools.nextElement();
			pool.release();
		}
		Enumeration allDrivers = drivers.elements();
		while (allDrivers.hasMoreElements()) {
			Driver driver = (Driver) allDrivers.nextElement();
			try {
				DriverManager.deregisterDriver(driver);

				System.out.println("����JDBC�������� " + driver.getClass().getName() + "��ע��");
			} catch (SQLException e) {
				System.out.println(e);
			}
		}
	}

	/**
	 * ����ָ�����Դ������ӳ�ʵ��.
	 * 
	 * @param props
	 *            ���ӳ�����
	 * @throws Exception
	 */
	private void createPools() throws Exception {
		DOMParse d1 = new DOMParse("dataSources.xml");
		Vector sv = d1.addDataSourceVector();
		Iterator ite = sv.iterator();
		while (ite.hasNext()) {
			DataSource db = (DataSource) ite.next();

			DBConnectionPool pool = new DBConnectionPool(db.getId(), db
					.getUrl(), db.getUsername(), db.getPassword(), db
					.getMaxconn());

			pools.put(new Integer(db.getId()), pool);
			// log("�ɹ��������ӳ�" + poolName);
		}
	}

	/**
	 * ��ȡ������ɳ�ʼ��
	 * 
	 * @throws Exception
	 */
	private void init() throws Exception {
		loadDrivers();
		createPools();
	}

	/**
	 * װ�غ�ע������JDBC��������
	 * 
	 * @throws Exception
	 */
	private void loadDrivers() throws Exception {
		DOMParse d1 = new DOMParse("dataSources.xml");
		Vector sv = d1.addDataSourceVector();
		Iterator ite = sv.iterator();
		while (ite.hasNext()) {
			DataSource db = (DataSource) ite.next();
			try {
				Driver driver = (Driver) Class.forName(db.getDriver_class())
						.newInstance();
				DriverManager.registerDriver(driver);
				drivers.addElement(db.getDriver_class());
				System.out.println(db.getDriver_class());

			} catch (Exception e) {
				System.out.println("�޷�ע��JDBC��������: " + db.getDriver_class()
						+ ", ����: " + e);
			}
		}
	}



	/**
	 * ���ڲ��ඨ����һ�����ӳ�.���ܹ�����Ҫ�󴴽�������,ֱ��Ԥ������ ��������Ϊֹ.�ڷ������Ӹ��ͻ�����֮ǰ,���ܹ���֤���ӵ���Ч��.
	 */

	class DBConnectionPool {
		// private int checkedOut;
		private Vector freeConnections = new Vector();
		private int maxConn;
		private int id;
		private String password;
		private String URL;
		private String user;

		/**
		 * �����µ����ӳ�
		 * 
		 * @param name
		 *            ���ӳ�����
		 * @param URL
		 *            ���ݿ��JDBC URL
		 * @param user
		 *            ���ݿ��ʺ�,�� null
		 * @param password
		 *            ����,�� null
		 * @param maxConn
		 *            �����ӳ������������������
		 */
		public DBConnectionPool(int dbid, String URL, String user,
				String password, int maxConn) {
			this.id = dbid;
			this.URL = URL;
			this.user = user;
			this.password = password;
			this.maxConn = maxConn;
		}

		/**
		 * ������ʹ�õ����ӷ��ظ����ӳ�
		 * 
		 * @param con
		 *            �ͻ������ͷŵ�����
		 */
		public synchronized void freeConnection(Connection con) {
			// ��ָ�����Ӽ��뵽����ĩβ
			try {
				if (con.isClosed()) {
					System.out.println("before freeConnection con is closed");
				}
				freeConnections.addElement(con);
				Connection contest = (Connection) freeConnections.lastElement();
				if (contest.isClosed()) {
					System.out
							.println("after freeConnection contest is closed");
				}
				notifyAll();
			} catch (SQLException e) {
				System.out.println(e);
			}
		}

		/**
		 * �����ӳػ��һ����������.��û�п��е������ҵ�ǰ������С��������� ������,�򴴽�������.��ԭ���Ǽ�Ϊ���õ����Ӳ�����Ч,�������ɾ��֮,
		 * Ȼ��ݹ�����Լ��Գ����µĿ�������.
		 */
		public synchronized Connection getConnection() {
			Connection con = null;
			if (freeConnections.size() > 0) {
				// ��ȡ�����е�һ����������
				con = (Connection) freeConnections.firstElement();
				freeConnections.removeElementAt(0);
				try {
					if (con.isClosed()) {
						System.out.println("�����ӳ�" + id + "ɾ��һ����Ч����");
						System.out.println("�����ӳ�" + id + "ɾ��һ����Ч����");
						// �ݹ�����Լ�,�����ٴλ�ȡ��������
						con = getConnection();
					}
				} catch (SQLException e) {
					System.out.println("�����ӳ�" + id + "ɾ��һ����Ч����ʱ����");
					System.out.println("�����ӳ�" + id + "ɾ��һ����Ч���ӳ���");
					// �ݹ�����Լ�,�����ٴλ�ȡ��������
					con = getConnection();
				}
				if (freeConnections.size() > maxConn) {
					System.out.println(" ɾ��һ��������� ");
					releaseOne();
				}
			}

			else if ((maxConn == 0) || (freeConnections.size() < maxConn)) {
				con = newConnection();
			}

			return con;
		}

		public synchronized Connection returnConnection() {
			Connection con = null;
			// �������С���������,����һ��������
			if (freeConnections.size() < maxConn) {
				con = newConnection();
			}
			// ������ô���������ӣ�����һ�����õľ�����
			else if (freeConnections.size() >= maxConn) {

				con = (Connection) freeConnections.firstElement();
				System.out.println(" [a ���ӳؿ��������� ] : " + "[ "
						+ freeConnections.size() + " ]");
				freeConnections.removeElementAt(0);
				System.out.println(" [b ���ӳؿ��������� ] : " + "[ "
						+ freeConnections.size() + " ]");
				try {
					if (con.isClosed()) {
						System.out.println("�����ӳ�" + id + "ɾ��һ����Ч����");
						System.out.println("�����ӳ�" + id + "ɾ��һ����Ч����");
						returnConnection();
					}
				} catch (SQLException e) {
					System.out.println("�����ӳ�" + id + "ɾ��һ����Ч����ʱ����");
					System.out.println("�����ӳ�" + id + "ɾ��һ����Ч���ӳ���");
					returnConnection();
				}
			}
			return con;
		}

		/**
		 * �����ӳػ�ȡ��������.����ָ���ͻ������ܹ��ȴ����ʱ�� �μ�ǰһ��getConnection()����.
		 * 
		 * @param timeout
		 *            �Ժ���Ƶĵȴ�ʱ������
		 */
		public synchronized Connection getConnection(long timeout) {
			long startTime = new Date().getTime();
			Connection con;
			while ((con = getConnection()) == null) {
				try {
					wait(timeout);
				} catch (InterruptedException e) {
				}
				if ((new Date().getTime() - startTime) >= timeout) {
					// wait()���ص�ԭ���ǳ�ʱ
					return null;
				}
			}
			return con;
		}

		/**
		 * �ر���������
		 */
		public synchronized void release() {
			Enumeration allConnections = freeConnections.elements();
			while (allConnections.hasMoreElements()) {
				Connection con = (Connection) allConnections.nextElement();
				try {
					con.close();
					System.out.println("�ر����ӳ�" + id + "�е�һ������");
				} catch (SQLException e) {
					System.out.println(e);
				}
			}
			freeConnections.removeAllElements();
		}

		/**
		 * �ر�һ������
		 */
		public synchronized void releaseOne() {
			if (freeConnections.firstElement() != null) {
				Connection con = (Connection) freeConnections.firstElement();
				try {
					con.close();
					System.out.println("�ر����ӳ�" + id + "�е�һ������");
					System.out.println("�ر����ӳ�" + id + "�е�һ������");
				} catch (SQLException e) {

					System.out.println("�޷��ر����ӳ�" + id + "�е�һ������");
					
				}
			} else {
				System.out.println("releaseOne() err..........................");

			}
		}


	//�����µ�����
		private Connection newConnection() {
			Connection con = null;
			try {
				if (user == null) {
					con = DriverManager.getConnection(URL);
				} else {
					con = DriverManager.getConnection(URL, user, password);
				}
				System.out.println("���ӳ�" + id + "����һ���µ�����");

			} catch (SQLException e) {
				System.out.println(e);
				return null;
			}
			return con;
		}
	}
}