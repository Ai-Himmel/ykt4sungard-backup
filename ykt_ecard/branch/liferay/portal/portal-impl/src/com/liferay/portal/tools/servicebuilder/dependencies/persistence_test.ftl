package ${packagePath}.service.persistence;

<#assign noSuchEntity = serviceBuilder.getNoSuchEntityException(entity)>

import ${packagePath}.${noSuchEntity}Exception;
import ${packagePath}.model.${entity.name};
import ${basePersistencePackage}.BasePersistenceTestCase;
import ${beanLocatorUtilPackage}.BeanLocatorUtil;

public class ${entity.name}PersistenceTest extends BasePersistenceTestCase {

	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (${entity.name}Persistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		<#if entity.hasCompoundPK()>
			${entity.PKClassName} pk = new ${entity.PKClassName}(

			<#list entity.PKList as column>
				<#if column.type == "int">
					nextInt()
				<#elseif column.type == "long">
					nextLong()
				<#elseif column.type == "String">
					randomString()
				</#if>

				<#if column_has_next>
					,
				</#if>
			</#list>

			);
		<#else>
			<#assign column = entity.PKList[0]>

			${column.type} pk =

			<#if column.type == "int">
				nextInt()
			<#elseif column.type == "long">
				nextLong()
			<#elseif column.type == "String">
				randomString()
			</#if>

			;
		</#if>

		${entity.name} ${entity.varName} = _persistence.create(pk);

		assertNotNull(${entity.varName});

		assertEquals(${entity.varName}.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		${entity.name} new${entity.name} = add${entity.name}();

		_persistence.remove(new${entity.name});

		${entity.name} existing${entity.name} = _persistence.fetchByPrimaryKey(new${entity.name}.getPrimaryKey());

		assertNull(existing${entity.name});
	}

	public void testUpdateNew() throws Exception {
		add${entity.name}();
	}

	public void testUpdateExisting() throws Exception {
		<#if entity.hasCompoundPK()>
			${entity.PKClassName} pk = new ${entity.PKClassName}(

			<#list entity.PKList as column>
				<#if column.type == "int">
					nextInt()
				<#elseif column.type == "long">
					nextLong()
				<#elseif column.type == "String">
					randomString()
				</#if>

				<#if column_has_next>
					,
				</#if>
			</#list>

			);
		<#else>
			<#assign column = entity.PKList[0]>

			${column.type} pk =

			<#if column.type == "int">
				nextInt()
			<#elseif column.type == "long">
				nextLong()
			<#elseif column.type == "String">
				randomString()
			</#if>

			;
		</#if>

		${entity.name} new${entity.name} = _persistence.create(pk);

		<#list entity.regularColList as column>
			<#if !column.primary>
				new${entity.name}.set${column.methodName}(

				<#if column.type == "boolean">
					randomBoolean()
				<#elseif column.type == "double">
					nextDouble()
				<#elseif column.type == "int">
					nextInt()
				<#elseif column.type == "long">
					nextLong()
				<#elseif column.type == "Date">
					nextDate()
				<#elseif column.type == "String">
					randomString()
				</#if>

				);
			</#if>
		</#list>

		_persistence.update(new${entity.name});

		${entity.name} existing${entity.name} = _persistence.findByPrimaryKey(new${entity.name}.getPrimaryKey());

		<#list entity.regularColList as column>
			assertEquals(existing${entity.name}.get${column.methodName}(), new${entity.name}.get${column.methodName}());
		</#list>
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		${entity.name} new${entity.name} = add${entity.name}();

		${entity.name} existing${entity.name} = _persistence.findByPrimaryKey(new${entity.name}.getPrimaryKey());

		assertEquals(existing${entity.name}, new${entity.name});
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		<#if entity.hasCompoundPK()>
			${entity.PKClassName} pk = new ${entity.PKClassName}(

			<#list entity.PKList as column>
				<#if column.type == "int">
					nextInt()
				<#elseif column.type == "long">
					nextLong()
				<#elseif column.type == "String">
					randomString()
				</#if>

				<#if column_has_next>
					,
				</#if>
			</#list>

			);
		<#else>
			<#assign column = entity.PKList[0]>

			${column.type} pk =

			<#if column.type == "int">
				nextInt()
			<#elseif column.type == "long">
				nextLong()
			<#elseif column.type == "String">
				randomString()
			</#if>

			;
		</#if>

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw ${noSuchEntity}Exception");
		}
		catch (${noSuchEntity}Exception nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		${entity.name} new${entity.name} = add${entity.name}();

		${entity.name} existing${entity.name} = _persistence.fetchByPrimaryKey(new${entity.name}.getPrimaryKey());

		assertEquals(existing${entity.name}, new${entity.name});
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		<#if entity.hasCompoundPK()>
			${entity.PKClassName} pk = new ${entity.PKClassName}(

			<#list entity.PKList as column>
				<#if column.type == "int">
					nextInt()
				<#elseif column.type == "long">
					nextLong()
				<#elseif column.type == "String">
					randomString()
				</#if>

				<#if column_has_next>
					,
				</#if>
			</#list>

			);
		<#else>
			<#assign column = entity.PKList[0]>

			${column.type} pk =

			<#if column.type == "int">
				nextInt()
			<#elseif column.type == "long">
				nextLong()
			<#elseif column.type == "String">
				randomString()
			</#if>

			;
		</#if>

		${entity.name} missing${entity.name} = _persistence.fetchByPrimaryKey(pk);

		assertNull(missing${entity.name});
	}

	protected ${entity.name} add${entity.name}() throws Exception {
		<#if entity.hasCompoundPK()>
			${entity.PKClassName} pk = new ${entity.PKClassName}(

			<#list entity.PKList as column>
				<#if column.type == "int">
					nextInt()
				<#elseif column.type == "long">
					nextLong()
				<#elseif column.type == "String">
					randomString()
				</#if>

				<#if column_has_next>
					,
				</#if>
			</#list>

			);
		<#else>
			<#assign column = entity.PKList[0]>

			${column.type} pk =

			<#if column.type == "int">
				nextInt()
			<#elseif column.type == "long">
				nextLong()
			<#elseif column.type == "String">
				randomString()
			</#if>

			;
		</#if>

		${entity.name} ${entity.varName} = _persistence.create(pk);

		<#list entity.regularColList as column>
			<#if !column.primary>
				${entity.varName}.set${column.methodName}(

				<#if column.type == "boolean">
					randomBoolean()
				<#elseif column.type == "double">
					nextDouble()
				<#elseif column.type == "int">
					nextInt()
				<#elseif column.type == "long">
					nextLong()
				<#elseif column.type == "Date">
					nextDate()
				<#elseif column.type == "String">
					randomString()
				</#if>

				);
			</#if>
		</#list>

		_persistence.update(${entity.varName});

		return ${entity.varName};
	}

	private static final String _TX_IMPL = ${entity.name}Persistence.class.getName() + ".transaction";

	private ${entity.name}Persistence _persistence;

}