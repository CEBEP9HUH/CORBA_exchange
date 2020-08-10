// This file is generated by omniidl (C++ backend)- omniORB_4_2. Do not edit.

#include "sendToServer.hh"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_2;



sendToServer_ptr sendToServer_Helper::_nil() {
  return ::sendToServer::_nil();
}

::CORBA::Boolean sendToServer_Helper::is_nil(::sendToServer_ptr p) {
  return ::CORBA::is_nil(p);

}

void sendToServer_Helper::release(::sendToServer_ptr p) {
  ::CORBA::release(p);
}

void sendToServer_Helper::marshalObjRef(::sendToServer_ptr obj, cdrStream& s) {
  ::sendToServer::_marshalObjRef(obj, s);
}

sendToServer_ptr sendToServer_Helper::unmarshalObjRef(cdrStream& s) {
  return ::sendToServer::_unmarshalObjRef(s);
}

void sendToServer_Helper::duplicate(::sendToServer_ptr obj) {
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
}

sendToServer_ptr
sendToServer::_duplicate(::sendToServer_ptr obj)
{
  if (obj && !obj->_NP_is_nil())  omni::duplicateObjRef(obj);
  return obj;
}

sendToServer_ptr
sendToServer::_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


sendToServer_ptr
sendToServer::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if (!obj || obj->_NP_is_nil() || obj->_NP_is_pseudo()) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

sendToServer_ptr
sendToServer::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_sendToServer _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_sendToServer* _the_nil_ptr = 0;
  if (!_the_nil_ptr) {
    omni::nilRefLock().lock();
    if (!_the_nil_ptr) {
      _the_nil_ptr = new _objref_sendToServer;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* sendToServer::_PD_repoId = "IDL:sendToServer:1.0";


_objref_sendToServer::~_objref_sendToServer() {
  
}


_objref_sendToServer::_objref_sendToServer(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::sendToServer::_PD_repoId, ior, id, 1)
   
   
{
  _PR_setobj(this);
}

void*
_objref_sendToServer::_ptrToObjRef(const char* id)
{
  if (id == ::sendToServer::_PD_repoId)
    return (::sendToServer_ptr) this;
  
  if (id == ::CORBA::Object::_PD_repoId)
    return (::CORBA::Object_ptr) this;

  if (omni::strMatch(id, ::sendToServer::_PD_repoId))
    return (::sendToServer_ptr) this;
  
  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (::CORBA::Object_ptr) this;

  return 0;
}


//
// Code for sendToServer::sendCharToServer

// Proxy call descriptor class. Mangled signature:
//  void_i_cchar
class _0RL_cd_ea63e64832a318fb_00000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_ea63e64832a318fb_00000000(LocalCallFn lcfn, const char* op_, size_t oplen, _CORBA_Boolean upcall=0)
    : omniCallDescriptor(lcfn, op_, oplen, 0, _user_exns, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

    
  
  static const char* const _user_exns[];

  ::CORBA::Char arg_0;
};

void _0RL_cd_ea63e64832a318fb_00000000::marshalArguments(cdrStream& _n)
{
  _n.marshalChar(arg_0);

}

void _0RL_cd_ea63e64832a318fb_00000000::unmarshalArguments(cdrStream& _n)
{
  arg_0 = _n.unmarshalChar();

}

const char* const _0RL_cd_ea63e64832a318fb_00000000::_user_exns[] = {
  0
};

// Local call call-back function.
static void
_0RL_lcfn_ea63e64832a318fb_10000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_ea63e64832a318fb_00000000* tcd = (_0RL_cd_ea63e64832a318fb_00000000*)cd;
  _impl_sendToServer* impl = (_impl_sendToServer*) svnt->_ptrToInterface(sendToServer::_PD_repoId);
  impl->sendCharToServer(tcd->arg_0);


}

void _objref_sendToServer::sendCharToServer(::CORBA::Char character)
{
  _0RL_cd_ea63e64832a318fb_00000000 _call_desc(_0RL_lcfn_ea63e64832a318fb_10000000, "sendCharToServer", 17);
  _call_desc.arg_0 = character;

  _invoke(_call_desc);



}

_pof_sendToServer::~_pof_sendToServer() {}


omniObjRef*
_pof_sendToServer::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::_objref_sendToServer(ior, id);
}


::CORBA::Boolean
_pof_sendToServer::is_a(const char* id) const
{
  if (omni::ptrStrMatch(id, ::sendToServer::_PD_repoId))
    return 1;
  
  return 0;
}

const _pof_sendToServer _the_pof_sendToServer;

_impl_sendToServer::~_impl_sendToServer() {}


::CORBA::Boolean
_impl_sendToServer::_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if (omni::strMatch(op, "sendCharToServer")) {

    _0RL_cd_ea63e64832a318fb_00000000 _call_desc(_0RL_lcfn_ea63e64832a318fb_10000000, "sendCharToServer", 17, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }


  return 0;
}

void*
_impl_sendToServer::_ptrToInterface(const char* id)
{
  if (id == ::sendToServer::_PD_repoId)
    return (::_impl_sendToServer*) this;
  
  if (id == ::CORBA::Object::_PD_repoId)
    return (void*) 1;

  if (omni::strMatch(id, ::sendToServer::_PD_repoId))
    return (::_impl_sendToServer*) this;
  
  if (omni::strMatch(id, ::CORBA::Object::_PD_repoId))
    return (void*) 1;
  return 0;
}

const char*
_impl_sendToServer::_mostDerivedRepoId()
{
  return ::sendToServer::_PD_repoId;
}

POA_sendToServer::~POA_sendToServer() {}
