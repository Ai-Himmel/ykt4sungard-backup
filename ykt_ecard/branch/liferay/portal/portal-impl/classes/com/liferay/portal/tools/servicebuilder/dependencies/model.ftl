package ${packagePath}.model;

<#if entity.hasCompoundPK()>
	import ${packagePath}.service.persistence.${entity.name}PK;
</#if>

import com.liferay.portal.model.BaseModel;
import java.util.Date;

/**
 * <a href="${entity.name}Model.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>${entity.name}</code>
 * table in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see ${packagePath}.service.model.${entity.name}
 * @see ${packagePath}.service.model.impl.${entity.name}Impl
 * @see ${packagePath}.service.model.impl.${entity.name}ModelImpl
 *
 */
public interface ${entity.name}Model extends BaseModel {

	public ${entity.PKClassName} getPrimaryKey();

	public void setPrimaryKey(${entity.PKClassName} pk);

	<#list entity.regularColList as column>
		public ${column.type} get${column.methodName}();

		<#if column.type == "boolean">
			public boolean is${column.methodName}();
		</#if>

		public void set${column.methodName}(${column.type} ${column.name});
	</#list>

	public ${entity.name} toEscapedModel();

}