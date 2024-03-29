// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: fir.proto

#ifndef PROTOBUF_fir_2eproto__INCLUDED
#define PROTOBUF_fir_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace fir {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_fir_2eproto();
void protobuf_AssignDesc_fir_2eproto();
void protobuf_ShutdownFile_fir_2eproto();

class stage;
class pipeline;

// ===================================================================

class stage : public ::google::protobuf::Message {
 public:
  stage();
  virtual ~stage();
  
  stage(const stage& from);
  
  inline stage& operator=(const stage& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const stage& default_instance();
  
  void Swap(stage* other);
  
  // implements Message ----------------------------------------------
  
  stage* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const stage& from);
  void MergeFrom(const stage& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required string name = 1;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 1;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  
  // required int32 id = 2;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 2;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:fir.stage)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_id();
  inline void clear_has_id();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* name_;
  ::google::protobuf::int32 id_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_fir_2eproto();
  friend void protobuf_AssignDesc_fir_2eproto();
  friend void protobuf_ShutdownFile_fir_2eproto();
  
  void InitAsDefaultInstance();
  static stage* default_instance_;
};
// -------------------------------------------------------------------

class pipeline : public ::google::protobuf::Message {
 public:
  pipeline();
  virtual ~pipeline();
  
  pipeline(const pipeline& from);
  
  inline pipeline& operator=(const pipeline& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const pipeline& default_instance();
  
  void Swap(pipeline* other);
  
  // implements Message ----------------------------------------------
  
  pipeline* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const pipeline& from);
  void MergeFrom(const pipeline& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // optional .fir.stage fir_stg_1 = 1;
  inline bool has_fir_stg_1() const;
  inline void clear_fir_stg_1();
  static const int kFirStg1FieldNumber = 1;
  inline const ::fir::stage& fir_stg_1() const;
  inline ::fir::stage* mutable_fir_stg_1();
  inline ::fir::stage* release_fir_stg_1();
  
  // optional .fir.stage fir_stg_2 = 2;
  inline bool has_fir_stg_2() const;
  inline void clear_fir_stg_2();
  static const int kFirStg2FieldNumber = 2;
  inline const ::fir::stage& fir_stg_2() const;
  inline ::fir::stage* mutable_fir_stg_2();
  inline ::fir::stage* release_fir_stg_2();
  
  // @@protoc_insertion_point(class_scope:fir.pipeline)
 private:
  inline void set_has_fir_stg_1();
  inline void clear_has_fir_stg_1();
  inline void set_has_fir_stg_2();
  inline void clear_has_fir_stg_2();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::fir::stage* fir_stg_1_;
  ::fir::stage* fir_stg_2_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_fir_2eproto();
  friend void protobuf_AssignDesc_fir_2eproto();
  friend void protobuf_ShutdownFile_fir_2eproto();
  
  void InitAsDefaultInstance();
  static pipeline* default_instance_;
};
// ===================================================================


// ===================================================================

// stage

// required string name = 1;
inline bool stage::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void stage::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void stage::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void stage::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& stage::name() const {
  return *name_;
}
inline void stage::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void stage::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void stage::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* stage::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* stage::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required int32 id = 2;
inline bool stage::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void stage::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void stage::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void stage::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 stage::id() const {
  return id_;
}
inline void stage::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// -------------------------------------------------------------------

// pipeline

// optional .fir.stage fir_stg_1 = 1;
inline bool pipeline::has_fir_stg_1() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void pipeline::set_has_fir_stg_1() {
  _has_bits_[0] |= 0x00000001u;
}
inline void pipeline::clear_has_fir_stg_1() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void pipeline::clear_fir_stg_1() {
  if (fir_stg_1_ != NULL) fir_stg_1_->::fir::stage::Clear();
  clear_has_fir_stg_1();
}
inline const ::fir::stage& pipeline::fir_stg_1() const {
  return fir_stg_1_ != NULL ? *fir_stg_1_ : *default_instance_->fir_stg_1_;
}
inline ::fir::stage* pipeline::mutable_fir_stg_1() {
  set_has_fir_stg_1();
  if (fir_stg_1_ == NULL) fir_stg_1_ = new ::fir::stage;
  return fir_stg_1_;
}
inline ::fir::stage* pipeline::release_fir_stg_1() {
  clear_has_fir_stg_1();
  ::fir::stage* temp = fir_stg_1_;
  fir_stg_1_ = NULL;
  return temp;
}

// optional .fir.stage fir_stg_2 = 2;
inline bool pipeline::has_fir_stg_2() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void pipeline::set_has_fir_stg_2() {
  _has_bits_[0] |= 0x00000002u;
}
inline void pipeline::clear_has_fir_stg_2() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void pipeline::clear_fir_stg_2() {
  if (fir_stg_2_ != NULL) fir_stg_2_->::fir::stage::Clear();
  clear_has_fir_stg_2();
}
inline const ::fir::stage& pipeline::fir_stg_2() const {
  return fir_stg_2_ != NULL ? *fir_stg_2_ : *default_instance_->fir_stg_2_;
}
inline ::fir::stage* pipeline::mutable_fir_stg_2() {
  set_has_fir_stg_2();
  if (fir_stg_2_ == NULL) fir_stg_2_ = new ::fir::stage;
  return fir_stg_2_;
}
inline ::fir::stage* pipeline::release_fir_stg_2() {
  clear_has_fir_stg_2();
  ::fir::stage* temp = fir_stg_2_;
  fir_stg_2_ = NULL;
  return temp;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace fir

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_fir_2eproto__INCLUDED
