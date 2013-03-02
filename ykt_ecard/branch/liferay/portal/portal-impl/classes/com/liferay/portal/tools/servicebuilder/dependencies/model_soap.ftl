package ${packagePath}.model;

<#if entity.hasCompoundPK()>
	import ${packagePath}.service.persistence.${entity.name}PK;
</#if>

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="${entity.name}Soap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>${packagePath}.service.http.${entity.name}ServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see ${packagePath}.service.http.${entity.name}ServiceSoap
 *
 */
public class ${entity.name}Soap implements Serializable {

	public static ${entity.name}Soap toSoapModel(${entity.name} model) {
		${entity.name}Soap soapModel = new ${entity.name}Soap();

		<#list entity.regularColList as column>
			soapModel.set${column.methodName}(model.get${column.methodName}());
		</#list>

		return soapModel;
	}

	public static ${entity.name}Soap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			${entity.name} model = (${entity.name})models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (${entity.name}Soap[])soapModels.toArray(new ${entity.name}Soap[0]);
	}

	public ${entity.name}Soap() {
	}

	public ${entity.PKClassName} getPrimaryKey() {
		<#if entity.hasCompoundPK()>
			return new ${entity.PKClassName}(
				<#list entity.PKList as column>
					_${column.name}

					<#if column_has_next>
						,
					</#if>
				</#list>
			);
		<#else>
			return _${entity.PKList[0].name};
		</#if>
	}

	public void setPrimaryKey(${entity.PKClassName} pk) {
		<#if entity.hasCompoundPK()>
			<#list entity.PKList as column>
				set${column.methodName}(pk.${column.name});
			</#list>
		<#else>
			set${entity.PKList[0].methodName}(pk);
		</#if>
	}

	<#list entity.regularColList as column>
		public ${column.type} get${column.methodName}() {
			return _${column.name};
		}

		<#if column.type== "boolean">
			public ${column.type} is${column.methodName}() {
				return _${column.name};
			}
		</#if>

		public void set${column.methodName}(${column.type} ${column.name}) {
			_${column.name} = ${column.name};
		}
	</#list>

	<#list entity.regularColList as column>
		private ${column.type} _${column.name};
	</#list>

}