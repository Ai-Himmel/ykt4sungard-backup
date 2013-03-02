Liferay.Service.${portletShortName}.${entity.name} = {
	serviceClassName: Liferay.Service.${portletShortName}.servicePackage + "${entity.name}" + Liferay.Service.classNameSuffix,
	<#list methods as method>

	${method}: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "${method}";

		return Liferay.Service.ajax(params, callback);
	}<#if method_has_next>,</#if>
	</#list>
};