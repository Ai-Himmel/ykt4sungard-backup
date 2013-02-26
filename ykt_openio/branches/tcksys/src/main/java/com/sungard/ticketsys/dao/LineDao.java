package com.sungard.ticketsys.dao;

import hibernate.HibernateSessionFactory;

import java.util.LinkedList;
import java.util.List;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.sungard.ticketsys.common.Page;
import com.sungard.ticketsys.model.Line;

public class LineDao extends BaseDao {

	private static LineDao lineDao;

	public static LineDao getInstance() {
		if (lineDao == null) {
			lineDao = new LineDao();
		}
		return lineDao;
	}

	public boolean checkLine(String name) {
		String hql = "from Line t where t.lineName = ? ";
		List lineList = super.find(hql, name);
		if (lineList == null || lineList.size() < 1) {
			return false;
		} else {
			return true;
		}
	}

	public List<Line> getAllLine() {
		return this.getAll(Line.class);
	}

	public Page getLineByCondition(int pageNo, int pageSize, Line line,
			String orderBy) {
		if (line != null) {
			StringBuffer hql = new StringBuffer("from Line t where 1=1 ");
			List<Object> conditions = new LinkedList<Object>();
			if (line.getLineName() != null && !"".equals(line.getLineName())) {
				hql.append(" and t.lineName like ? ");
				conditions.add("%" + line.getLineName().trim()+ "%");
			}

			if (line.getStartAddr() != null && !"".equals(line.getStartAddr())) {
				hql.append(" and t.startAddr like ? ");
				conditions.add("%" + line.getStartAddr().trim()+ "%");
			}

			if (line.getEndAddr() != null && !"".equals(line.getEndAddr())) {
				hql.append(" and t.endAddr like ? ");
				conditions.add("%" + line.getEndAddr().trim()+ "%");
			}

			if (orderBy != null && !"".equals(orderBy)) {
				hql.append(" order by t." + orderBy + " desc");
			} else {
				hql.append(" order by t.id desc");
			}

			return super.pageQuery(hql.toString(), pageNo, pageSize, conditions
					.toArray());
		} else {
			return null;
		}
	}

	public Line getLine(String name) {
		List lineList = super.find("from Line t where t.lineName ='" + name
				+ "'");
		return (Line) lineList.get(0);
	}

	public Line getLineById(Integer lineId) {
		return this.get(Line.class, lineId);
	}

	public void removeLine(Line line) {
		remove(line);

	}

	public void saveLine(Line line) {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();
		session.save(line);
		tx.commit();
	}

	public void updateLine(Line line) {
		Session session = HibernateSessionFactory.getSession();
		Transaction tx = session.beginTransaction();
		session.update(line);
		tx.commit();

	}

	public boolean lineIsUsed(String linename) {
		List busSerList = super.find("from BusSer t where t.lineName ='" + linename
				+ "'");
		if(busSerList.size()>0){
			return true;
		}
		
		return false;
	}

}
