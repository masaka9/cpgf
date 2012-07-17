#include "testmetagen.h"
#include "../include/simpleoverridefromscript.h"
#include "../metadata/include/meta_test_simpleoverridefromscript.h"


using namespace meta_test;

namespace {


template <typename T>
void doTestSimpleOverrideFromScript_OverrideFromScriptClass(T * binding, TestScriptContext * context)
{
	if(context->isLua()) {
		QDO(function funcOverride(me) return me.getValue() + 15 end)
	}
	if(context->isV8()) {
		QDO(function funcOverride(me) { return me.getValue() + 15; })
	}
	if(context->isPython()) {
		QDO(def funcOverride(me): return me.getValue() + 15)
	}

	QNEWOBJ(a, mtest.SimpleOverrideWrapper(3))
	QASSERT(a.getValue() == 3);
	QDO(mtest.SimpleOverrideWrapper.getValue = funcOverride)
	QASSERT(a.getValue() == 18);
	
	QNEWOBJ(b, mtest.SimpleOverrideWrapper(5))
	QASSERT(b.getValue() == 20);

	SimpleOverrideWrapper * objA = static_cast<SimpleOverrideWrapper *>(binding->getObject("a"));
	GEQUAL(18, objA->getValue());
}

void testSimpleOverrideFromScript_OverrideFromScriptClass(TestScriptContext * context)
{
	GScriptObject * bindingLib = context->getBindingLib();
	IScriptObject * bindingApi = context->getBindingApi();

	if(bindingLib) {
		doTestSimpleOverrideFromScript_OverrideFromScriptClass(bindingLib, context);
	}
	
	if(bindingApi) {
		doTestSimpleOverrideFromScript_OverrideFromScriptClass(bindingApi, context);
	}
}

#define CASE testSimpleOverrideFromScript_OverrideFromScriptClass
#include "do_testcase.h"


template <typename T>
void doTestSimpleOverrideFromScript_OverrideFromScriptObject(T * binding, TestScriptContext * context)
{
	if(context->isLua()) {
		QDO(function funcOverride(me) return me.getValue() + 5 end)
	}
	if(context->isV8()) {
		QDO(function funcOverride(me) { return me.getValue() + 5; })
	}
	if(context->isPython()) {
		QDO(def funcOverride(me): return me.getValue() + 5)
	}

	QNEWOBJ(a, mtest.SimpleOverrideWrapper(2))
	QASSERT(a.getValue() == 2);
	QDO(a.getValue = funcOverride);
	QASSERT(a.getValue() == 7);

	QNEWOBJ(b, mtest.SimpleOverrideWrapper(6))
	QASSERT(b.getValue() == 6);

	SimpleOverrideWrapper * objA = static_cast<SimpleOverrideWrapper *>(binding->getObject("a"));
	GEQUAL(7, objA->getValue());
}

void testSimpleOverrideFromScript_OverrideFromScriptObject(TestScriptContext * context)
{
	GScriptObject * bindingLib = context->getBindingLib();
	IScriptObject * bindingApi = context->getBindingApi();

	if(bindingLib) {
		doTestSimpleOverrideFromScript_OverrideFromScriptObject(bindingLib, context);
	}
	
	if(bindingApi) {
		doTestSimpleOverrideFromScript_OverrideFromScriptObject(bindingApi, context);
	}
}

#define CASE testSimpleOverrideFromScript_OverrideFromScriptObject
#include "do_testcase.h"



}
