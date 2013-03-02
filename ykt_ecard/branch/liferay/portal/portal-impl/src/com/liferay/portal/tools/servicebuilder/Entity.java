/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.tools.servicebuilder;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.TextFormatter;

import java.util.List;

/**
 * <a href="Entity.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Entity {

	public static EntityColumn getColumn(String name, List columnList) {
		int pos = columnList.indexOf(new EntityColumn(name));

		if (pos == -1) {
			throw new RuntimeException("Column " + name + " not found");
		}

		return (EntityColumn)columnList.get(pos);
	}

	public Entity(String name) {
		this(
			null, null, null, name, null, false, false, true, null, null, null,
			null, null, null, null, null, null, null, null, null, null);
	}

	public Entity(
		String packagePath, String portletName, String portletShortName,
		String name, String table, boolean uuid, boolean localService,
		boolean remoteService, String persistenceClass, String finderClass,
		String dataSource, String sessionFactory, String txManager, List pkList,
		List regularColList, List collectionList, List columnList,
		EntityOrder order, List finderList, List referenceList,
		List txRequiredList) {

		_packagePath = packagePath;
		_portletName = portletName;
		_portletShortName = portletShortName;
		_name = name;
		_table = table;
		_uuid = uuid;
		_localService = localService;
		_remoteService = remoteService;
		_persistenceClass = persistenceClass;
		_finderClass = finderClass;
		_dataSource = GetterUtil.getString(dataSource, "liferayDataSource");
		_sessionFactory = GetterUtil.getString(
			sessionFactory, "liferaySessionFactory");
		_txManager = GetterUtil.getString(
			txManager, "liferayTransactionManager");
		_pkList = pkList;
		_regularColList = regularColList;
		_collectionList = collectionList;
		_columnList = columnList;
		_order = order;
		_finderList = finderList;
		_referenceList = referenceList;
		_txRequiredList = txRequiredList;
	}

	public String getPackagePath() {
		return _packagePath;
	}

	public String getPortletName() {
		return _portletName;
	}

	public String getPortletShortName() {
		return _portletShortName;
	}

	public String getName() {
		return _name;
	}

	public String getNames() {
		return TextFormatter.formatPlural(new String(_name));
	}

	public String getVarName() {
		return TextFormatter.format(_name, TextFormatter.I);
	}

	public String getVarNames() {
		return TextFormatter.formatPlural(new String(getVarName()));
	}

	public String getTable() {
		return _table;
	}

	public boolean hasUuid() {
		return _uuid;
	}

	public boolean hasLocalService() {
		return _localService;
	}

	public boolean hasRemoteService() {
		return _remoteService;
	}

	public String getPersistenceClass() {
		return _persistenceClass;
	}

	public String getFinderClass() {
		return _finderClass;
	}

	public boolean hasFinderClass() {
		if (Validator.isNull(_finderClass)) {
			return false;
		}
		else {
			return true;
		}
	}

	public String getDataSource() {
		return _dataSource;
	}

	public String getSessionFactory() {
		return _sessionFactory;
	}

	public String getTXManager() {
		return _txManager;
	}

	public String getPKClassName() {
		if (hasCompoundPK()) {
			return _name + "PK";
		}
		else {
			EntityColumn col = (EntityColumn)_pkList.get(0);

			return col.getType();
		}
	}

	public String getPKVarName() {
		if (hasCompoundPK()) {
			return getVarName() + "PK";
		}
		else {
			EntityColumn col = (EntityColumn)_pkList.get(0);

			return col.getName();
		}
	}

	public boolean hasPrimitivePK() {
		if (hasCompoundPK()) {
			return false;
		}
		else {
			EntityColumn col = (EntityColumn)_pkList.get(0);

			if (col.isPrimitiveType()) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	public boolean hasCompoundPK() {
		if (_pkList.size() > 1) {
			return true;
		}
		else {
			return false;
		}
	}

	public List getPKList() {
		return _pkList;
	}

	public List getRegularColList() {
		return _regularColList;
	}

	public List getCollectionList() {
		return _collectionList;
	}

	public List getColumnList() {
		return _columnList;
	}

	public boolean hasColumns() {
		if ((_columnList == null) || (_columnList.size() == 0)) {
			return false;
		}
		else {
			return true;
		}
	}

	public EntityOrder getOrder() {
		return _order;
	}

	public boolean isOrdered() {
		if (_order != null) {
			return true;
		}
		else {
			return false;
		}
	}

	public List getFinderList() {
		return _finderList;
	}

	public List getReferenceList() {
		return _referenceList;
	}

	public List getTxRequiredList() {
		return _txRequiredList;
	}

	public EntityColumn getColumn(String name) {
		return getColumn(name, _columnList);
	}

	public EntityColumn getColumnByMappingTable(String mappingTable) {
		for (int i = 0; i < _columnList.size(); i++) {
			EntityColumn col = (EntityColumn)_columnList.get(i);

			if (col.getMappingTable() != null &&
				col.getMappingTable().equals(mappingTable)) {

				return col;
			}
		}

		return null;
	}

	public boolean equals(Object obj) {
		Entity entity = (Entity)obj;

		String name = entity.getName();

		if (_name.equals(name)) {
			return true;
		}
		else {
			return false;
		}
	}

	private String _packagePath;
	private String _portletName;
	private String _portletShortName;
	private String _name;
	private String _table;
	private boolean _uuid;
	private boolean _localService;
	private boolean _remoteService;
	private String _persistenceClass;
	private String _finderClass;
	private String _dataSource;
	private String _sessionFactory;
	private String _txManager;
	private List _pkList;
	private List _regularColList;
	private List _collectionList;
	private List _columnList;
	private EntityOrder _order;
	private List _finderList;
	private List _referenceList;
	private List _txRequiredList;

}