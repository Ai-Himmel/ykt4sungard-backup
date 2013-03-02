package ${packagePath}.service.http;

import ${packagePath}.service.${entity.name}ServiceUtil;
import org.json.JSONArray;
import org.json.JSONObject;

/**
 * <a href="${entity.name}ServiceJSON.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a JSON utility for the
 * <code>${packagePath}.service.${entity.name}ServiceUtil</code>
 * service utility. The static methods of this class calls the same methods of
 * the service utility. However, the signatures are different because it is
 * difficult for JSON to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to a <code>org.json.JSONArray</code>. If the method in the
 * service utility returns a <code>${packagePath}.model.${entity.name}</code>,
 * that is translated to a <code>org.json.JSONObject</code>. Methods that JSON
 * cannot safely use are skipped. The logic for the translation is encapsulated
 * in <code>${packagePath}.service.http.${entity.name}JSONSerializer</code>.
 * </p>
 *
 * <p>
 * This allows you to call the the backend services directly from JavaScript.
 * See <code>portal-web/docroot/html/portlet/tags_admin/unpacked.js</code> for a
 * reference of how that portlet uses the generated JavaScript in
 * <code>portal-web/docroot/html/js/service.js</code> to call the backend
 * services directly from JavaScript.
 * </p>
 *
 * <p>
 * The JSON utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see ${packagePath}.service.${entity.name}ServiceUtil
 * @see ${packagePath}.service.http.${entity.name}JSONSerializer
 *
 */
public class ${entity.name}ServiceJSON {

	<#list methods as method>
		<#if !method.isConstructor() && method.isPublic() && serviceBuilder.isCustomMethod(method) && serviceBuilder.isSoapMethod(method)>
			<#assign returnValueName = method.returns.value>
			<#assign returnValueDimension = serviceBuilder.getDimensions(method.returns.dimensions)>
			<#assign extendedModelName = packagePath + ".model." + entity.name>
			<#assign soapModelName = "JSONObject">

			public static
				<#if returnValueName == extendedModelName>
					${soapModelName}${returnValueDimension}
				<#elseif returnValueName == "java.util.List">
					<#if entity.hasColumns()>
						JSONArray
					<#else>
						java.util.List
					</#if>
				<#elseif returnValueName == "com.liferay.portal.kernel.json.JSONArrayWrapper">
					JSONArray
				<#elseif returnValueName == "com.liferay.portal.kernel.json.JSONObjectWrapper">
					JSONObject
				<#else>
					${returnValueName}${returnValueDimension}
				</#if>

				${method.name}(

				<#list method.parameters as parameter>
					<#assign parameterTypeName = parameter.type.value + serviceBuilder.getDimensions(parameter.type.dimensions)>

					<#if parameterTypeName == "java.util.Locale">
						<#assign parameterTypeName = "String">
					</#if>

					${parameterTypeName} ${parameter.name}

					<#if parameter_has_next>
						,
					</#if>
				</#list>

				) throws

				<#if !method.exceptions?seq_contains("java.rmi.RemoteException")>
					java.rmi.RemoteException

					<#if method.exceptions?size gt 0>
						,
					</#if>
				</#if>

				<#list method.exceptions as exception>
					${exception.value}

					<#if exception_has_next>
						,
					</#if>
				</#list>{

				<#if returnValueName != "void">
					${returnValueName}${returnValueDimension} returnValue =
				</#if>

				${entity.name}ServiceUtil.${method.name}(
					<#list method.parameters as parameter>
						<#assign parameterTypeName = parameter.type.value + serviceBuilder.getDimensions(parameter.type.dimensions)>

						<#if parameterTypeName == "java.util.Locale">
							new java.util.Locale(
						</#if>

						${parameter.name}

						<#if parameterTypeName == "java.util.Locale">
							)
						</#if>

						<#if parameter_has_next>
							,
						</#if>
					</#list>
				);

				<#if returnValueName != "void">
					<#if returnValueName == extendedModelName>
						return ${entity.name}JSONSerializer.toJSONObject(returnValue);
					<#elseif entity.hasColumns() && returnValueName == "java.util.List">
						return ${entity.name}JSONSerializer.toJSONArray(returnValue);
					<#elseif returnValueName == "com.liferay.portal.kernel.json.JSONArrayWrapper">
						return (JSONArray)returnValue.getValue();
					<#elseif returnValueName == "com.liferay.portal.kernel.json.JSONObjectWrapper">
						return (JSONObject)returnValue.getValue();
					<#else>
						return returnValue;
					</#if>
				</#if>
			}
		</#if>
	</#list>

}