/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010- Facebook, Inc. (http://www.facebook.com)         |
   | Copyright (c) 1997-2010 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef __EXT_CONTINUATION_H__
#define __EXT_CONTINUATION_H__


#include <runtime/base/base_includes.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////
FORWARD_DECLARE_CLASS_BUILTIN(Continuation);

p_Continuation f_hphp_create_continuation(CStrRef clsname, CStrRef funcname, CArrRef args = null_array);
void f_hphp_pack_continuation(CObjRef continuation, int64 label, CVarRef value);
void f_hphp_unpack_continuation(CObjRef continuation);

///////////////////////////////////////////////////////////////////////////////
// class Continuation
class c_Continuation : public ExtObjectData {
 public:
  BEGIN_CLASS_MAP(Continuation)
  PARENT_CLASS(Iterator)
  END_CLASS_MAP(Continuation)
  DECLARE_CLASS(Continuation, Continuation, ObjectData)

  // properties
  public: Object m_obj;
  public: Array m_args;
  public: int64 m_label;
  public: bool m_done;
  public: int64 m_index;
  public: Variant m_value;
  public: bool m_running;
  public: Variant m_received;

  // need to implement
  public: c_Continuation();
  public: ~c_Continuation();
  public: void t___construct(int64 func, int64 extra, bool isMethod, CVarRef obj = null, CArrRef args = null_array);
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: void t_update(int64 label, CVarRef value);
  DECLARE_METHOD_INVOKE_HELPERS(update);
  public: void t_done();
  DECLARE_METHOD_INVOKE_HELPERS(done);
  public: int64 t_getlabel();
  DECLARE_METHOD_INVOKE_HELPERS(getlabel);
  public: int64 t_num_args();
  DECLARE_METHOD_INVOKE_HELPERS(num_args);
  public: Array t_get_args();
  DECLARE_METHOD_INVOKE_HELPERS(get_args);
  public: Variant t_get_arg(int64 id);
  DECLARE_METHOD_INVOKE_HELPERS(get_arg);
  public: Variant t_current();
  DECLARE_METHOD_INVOKE_HELPERS(current);
  public: int64 t_key();
  DECLARE_METHOD_INVOKE_HELPERS(key);
  public: void t_next();
  DECLARE_METHOD_INVOKE_HELPERS(next);
  public: void t_rewind();
  DECLARE_METHOD_INVOKE_HELPERS(rewind);
  public: bool t_valid();
  DECLARE_METHOD_INVOKE_HELPERS(valid);
  public: void t_send(CVarRef v);
  DECLARE_METHOD_INVOKE_HELPERS(send);
  public: Variant t_receive();
  DECLARE_METHOD_INVOKE_HELPERS(receive);
  public: Variant t___clone();
  DECLARE_METHOD_INVOKE_HELPERS(__clone);
  public: Variant t___destruct();
  DECLARE_METHOD_INVOKE_HELPERS(__destruct);

  // implemented by HPHP
  public: c_Continuation *create(int64 func, int64 extra, bool isMethod, Variant obj = null, Array args = null_array);
  public: void dynConstruct(CArrRef Params);
  public: void getConstructor(MethodCallPackage &mcp);
protected:
  virtual bool php_sleep(Variant &ret);
private:
  const CallInfo *m_callInfo;
  void *m_extra;
  bool m_isMethod;
};

///////////////////////////////////////////////////////////////////////////////
// class GenericContinuation

FORWARD_DECLARE_CLASS_BUILTIN(GenericContinuation);
class c_GenericContinuation : public c_Continuation {
 public:
  BEGIN_CLASS_MAP(GenericContinuation)
  RECURSIVE_PARENT_CLASS(Continuation)
  END_CLASS_MAP(GenericContinuation)
  DECLARE_CLASS(GenericContinuation, GenericContinuation, Continuation)

  // properties
  public: Array m_vars;

  // need to implement
  public: c_GenericContinuation();
  public: ~c_GenericContinuation();
  public: void t___construct(int64 func, int64 extra, bool isMethod, CArrRef vars, CVarRef obj = null, CArrRef args = null_array);
  DECLARE_METHOD_INVOKE_HELPERS(__construct);
  public: void t_update(int64 label, CVarRef value, CArrRef vars);
  DECLARE_METHOD_INVOKE_HELPERS(update);
  public: Array t_getvars();
  DECLARE_METHOD_INVOKE_HELPERS(getvars);
  public: Variant t___destruct();
  DECLARE_METHOD_INVOKE_HELPERS(__destruct);

  // implemented by HPHP
  public: c_GenericContinuation *create(int64 func, int64 extra, bool isMethod, Array vars, Variant obj = null, Array args = null_array);
  public: void dynConstruct(CArrRef Params);
  public: void getConstructor(MethodCallPackage &mcp);

};

///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXT_CONTINUATION_H__
